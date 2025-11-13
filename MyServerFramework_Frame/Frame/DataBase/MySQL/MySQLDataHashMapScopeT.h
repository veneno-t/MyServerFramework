#pragma once
#ifdef _MYSQL

#include "HashMap.h"
#include "MySQLDataPool.h"
#include "CounterThreadPool.h"

template<typename T>
class MySQLDataHashMapScopeT
{
    typedef typename unordered_map<llong, T*>::iterator iterator;
    typedef typename unordered_map<llong, T*>::const_iterator const_iterator;
private:
    HashMap<llong, T*> mList;       // 原始数据
    Counter* mCounter = nullptr;    // 引用计数
public:
    // 默认构造函数
    MySQLDataHashMapScopeT() {}
    explicit MySQLDataHashMapScopeT(HashMap<llong, T*>&& list)
    {
        if (list.isEmpty())
        {
            return;
        }
        mList = move(list);
        mCounter = mCounterThreadPool->newClass();
        mCounter->increase();
    }
    // 拷贝构造函数
    MySQLDataHashMapScopeT(const MySQLDataHashMapScopeT& other) :
        mCounter(other.mCounter)
    {
        if (other.mList.isEmpty())
        {
            return;
        }
        other.mList.clone(mList);
        mCounter->increase();
    }
    // 移动构造函数
    MySQLDataHashMapScopeT(MySQLDataHashMapScopeT&& other) noexcept :
        mList(move(other.mList)),
        mCounter(other.mCounter)
    {
        other.mCounter = nullptr;
    }
    // 移动赋值操作符
    MySQLDataHashMapScopeT& operator=(MySQLDataHashMapScopeT&& other) noexcept
    {
        if (this != &other)
        {
            // 先减少当前指针的引用计数
            release();

            // 复制新对象的内容
            mList = move(other.mList);
            mCounter = other.mCounter;
            other.mCounter = nullptr;
        }
        return *this;
    }
    // 析构函数
    ~MySQLDataHashMapScopeT()
    {
        release();
    }
    iterator begin()                { return mList.begin(); }
    iterator end()                  { return mList.end(); }
    const_iterator begin() const    { return mList.begin(); }
    const_iterator end()  const     { return mList.end(); }
    const_iterator cbegin() const   { return mList.cbegin(); }
    const_iterator cend() const     { return mList.cend(); }
    // 指针访问操作符,只允许左值调用,右值不能调用,因为容易产生析构后才返回的问题
    const HashMap<llong, T*>& get() const& { return mList; }
    const HashMap<llong, T*>& get() const&& = delete;
    bool isValid() const { return mList.size() != 0; }
    // 如果已经确认data在外部被销毁了,则可以从当前列表中移除
    void erase(T* data) { mList.erase(data->mID); }
    void erase(const Vector<T*>& dataList)
    {
        for (MySQLData* data : dataList)
        {
            mList.erase(data->mID);
        }
    }
    void release()
    {
        // 先减少当前指针的引用计数
        if (mCounter != nullptr && mCounter->decrease() == 0)
        {
            mMySQLDataPool->destroyClassList(mList);
            mCounterThreadPool->destroyClass(mCounter);
        }
    }
    void releaseNoDestroy()
    {
        // 先减少当前指针的引用计数
        if (mCounter != nullptr)
        {
            if (mCounter->decrease() == 0)
            {
                mList.clear();
                mCounterThreadPool->destroyClass(mCounter);
            }
            else
            {
                ERROR("计数不为0");
            }
        }
    }
};

#endif