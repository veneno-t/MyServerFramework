#pragma once

#include "ThreadLock.h"
#include "ThreadLockScope.h"
#include "ClassPoolBase.h"
#include "ClassObject.h"
#include "Utility.h"
#include "ErrorProfile.h"

// 传入的参数就是模板类型
// 线程安全的
template<typename BaseClassType, typename TypeCheck = typename IsSubClassOf<ClassObject, BaseClassType>::mType>
class ClassBaseTypePoolThread : public ClassPoolBase
{
	BASE(ClassBaseTypePoolThread, ClassPoolBase);
public:
	ClassBaseTypePoolThread():
		mAssignIDSeed(0)
	{}
	template<typename T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	void initDefault(const int count)
	{
		Vector<BaseClassType*> list(count);
		FOR(count)
		{
			BaseClassType* obj = new T();
			obj->resetProperty();
			list.push_back(obj);
		}
		{
			THREAD_LOCK(mLock);
			mUnusedList.insertOrGet(typeid(T).hash_code()).addRange(list);
		}
		{
			THREAD_LOCK(mTotalCountLock);
			mTotalCount.insertOrGet(typeid(T).hash_code(), make_pair(typeid(T).name(), 0)).second += count;
		}
	}
	void quit() override
	{
		THREAD_LOCK(mLock);
		for (auto& item : mUnusedList)
		{
			DELETE_LIST(item.second);
		}
		mUnusedList.clear();
	}
	// 这里函数名中的Temp的意思是创建的对象必须在一定时间内被回收,否则就会报错,提示内存泄露
	template<typename T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	void newClassListTemp(Vector<BaseClassType*>& classList, const int dataCount)
	{
		newClassList<T>(classList, dataCount);
#ifdef WINDOWS
		const string stack = mEnableStackTrace ? getStackTrace(TRACE_DEPTH) : "";
		THREAD_LOCK(mRemainTimeLock);
		for (BaseClassType* obj : classList)
		{
			mClassRemainTimeList.insert(obj, make_pair(DEFAULT_LIFE_TIME, stack));
		}
#endif
	}
	template<typename T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	void newClassList(Vector<BaseClassType*>& classList, const int dataCount)
	{
		classList.clearAndReserve(dataCount);
		const size_t typeHash = typeid(T).hash_code();
		if (mUnusedList.size() > 0)
		{
			THREAD_LOCK(mLock);
			if (auto* listPtr = mUnusedList.getPtr(typeHash))
			{
				FOR(dataCount)
				{
					// 首先从未使用的列表中获取,获取不到再重新创建一个
					BaseClassType* obj = listPtr->popBack(nullptr);
					if (obj == nullptr)
					{
						break;
					}
					classList.push_back(obj);
				}
			}
		}

		if (classList.size() < dataCount)
		{
			const int needCreateCount = dataCount - classList.size();
			FOR(needCreateCount)
			{
				BaseClassType* obj = new T();
				// 为了跟复用时的状态统一
				obj->resetProperty();
				classList.push_back(obj);
			}
			THREAD_LOCK(mTotalCountLock);
			auto& totalCount = mTotalCount.insertOrGet(typeHash, make_pair(typeid(T).name(), 0));
			totalCount.second += needCreateCount;
			if (mShowCountLog && (totalCount.second & (4096 - 1)) == 0)
			{
				LOG(string(typeid(*classList[0]).name()) + "的数量已经达到了" + IToS(totalCount.second) + "个");
			}
		}
		
		for (BaseClassType* item : classList)
		{
			item->markUsable(this, ++mAssignIDSeed);
		}
	}
	// 这里函数名中的Temp的意思是创建的对象必须在一定时间内被回收,否则就会报错,提示内存泄露
	template<typename T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	void newClassListTemp(Vector<T*>& classList, const int dataCount)
	{
		newClassList(classList, dataCount);
#ifdef WINDOWS
		const string stack = mEnableStackTrace ? getStackTrace(TRACE_DEPTH) : "";
		THREAD_LOCK(mRemainTimeLock);
		for (T* obj : classList)
		{
			mClassRemainTimeList.insert(obj, make_pair(DEFAULT_LIFE_TIME, stack));
		}
#endif
	}
	template<typename T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	void newClassList(Vector<T*>& classList, const int dataCount)
	{
		classList.clearAndReserve(dataCount);
		const size_t typeHash = typeid(T).hash_code();
		if (mUnusedList.size() > 0)
		{
			THREAD_LOCK(mLock);
			if (auto* listPtr = mUnusedList.getPtr(typeHash))
			{
				FOR(dataCount)
				{
					// 首先从未使用的列表中获取,获取不到再重新创建一个
					BaseClassType* obj = listPtr->popBack(nullptr);
					if (obj == nullptr)
					{
						break;
					}
					classList.push_back(static_cast<T*>(obj));
				}
			}
		}

		if (classList.size() < dataCount)
		{
			const int needCreateCount = dataCount - classList.size();
			FOR(needCreateCount)
			{
				T* obj = new T();
				// 为了跟复用时的状态统一
				obj->resetProperty();
				classList.push_back(obj);
			}
			THREAD_LOCK(mTotalCountLock);
			auto& totalCount = mTotalCount.insertOrGet(typeHash, make_pair(typeid(T).name(), 0));
			totalCount.second += needCreateCount;
			if (mShowCountLog && (totalCount.second & (4096 - 1)) == 0)
			{
				LOG(string(typeid(*classList[0]).name()) + "的数量已经达到了" + IToS(totalCount.second) + "个");
			}
		}

		for (T* item : classList)
		{
			item->markUsable(this, ++mAssignIDSeed);
		}
	}
	// 这里函数名中的Temp的意思是创建的对象必须在一定时间内被回收,否则就会报错,提示内存泄露
	template<class T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	T* newClassTemp()
	{
		T* obj = newClass<T>();
#ifdef WINDOWS
		const string stack = mEnableStackTrace ? getStackTrace(TRACE_DEPTH) : "";
		THREAD_LOCK(mRemainTimeLock);
		mClassRemainTimeList.insert(obj, make_pair(DEFAULT_LIFE_TIME, stack));
#endif
		return obj;
	}
	template<class T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	T* newClass()
	{
		T* obj = nullptr;
		if (mUnusedList.size() > 0)
		{
			THREAD_LOCK(mLock);
			// 首先从未使用的列表中获取,获取不到再重新创建一个
			if (auto* listPtr = mUnusedList.getPtr(typeid(T).hash_code()))
			{
				obj = static_cast<T*>(listPtr->popBack(nullptr));
			}
		}

		// 没有找到可以用的,则创建一个
		if (obj == nullptr)
		{
			obj = new T();
			obj->resetProperty();
			THREAD_LOCK(mTotalCountLock);
			auto& totalCount = mTotalCount.insertOrGet(typeid(T).hash_code(), make_pair(typeid(T).name(), 0));
			++totalCount.second;
			if (mShowCountLog && (totalCount.second & (4096 - 1)) == 0)
			{
				LOG(string(typeid(*obj).name()) + "的数量已经达到了" + IToS(totalCount.second) + "个");
			}
		}

		// 设置为可用状态
		obj->markUsable(this, ++mAssignIDSeed);
		return obj;
	}
	// 由于允许传入BaseClassType子类的列表,所以重新定义了一个类型
	template<typename T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	void destroyClass(T*& obj)
	{
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (mDestroied || obj == nullptr)
		{
			return;
		}
		obj->destroy();
		if (!obj->markDispose(this))
		{
			ERROR_PROFILE((string("0重复销毁对象:") + typeid(T).name()).c_str());
			return;
		}
#ifdef WINDOWS
		{
			THREAD_LOCK(mRemainTimeLock);
			mClassRemainTimeList.erase(obj);
		}
#endif
		// 添加到未使用列表中
		{
			THREAD_LOCK(mLock);
			mUnusedList.insertOrGet(typeid(*obj).hash_code()).push_back(obj);
		}
		obj = nullptr;
	}
	// 由于允许传入BaseClassType子类的列表,所以重新定义了一个类型
	template<typename T0, typename T1, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T1>::mType>
	void destroyClassList(HashMap<T0, T1*>& objMap)
	{
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (objMap.isEmpty() || mDestroied)
		{
			return;
		}

		// 加入到列表,并重置所有属性
		THREAD_LOCK(mLock);
#ifdef WINDOWS
		THREAD_LOCK(mRemainTimeLock);
#endif
		for (const auto& iter : objMap)
		{
			BaseClassType* obj = iter.second;
			if (obj == nullptr)
			{
				continue;
			}
			obj->destroy();
			if (!obj->markDispose(this))
			{
				ERROR_PROFILE((string("2重复销毁对象:") + typeid(T1).name()).c_str());
				continue;
			}
			mUnusedList.insertOrGet(typeid(*obj).hash_code()).push_back(obj);
#ifdef WINDOWS
			mClassRemainTimeList.erase(obj);
#endif
		}
		objMap.clear();
	}
	// 由于允许传入BaseClassType子类的列表,所以重新定义了一个类型
	template<typename T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	void destroyClassList(Vector<T*>& objList)
	{
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (objList.isEmpty() || mDestroied)
		{
			return;
		}

		// 加入到列表,并重置所有属性
		THREAD_LOCK(mLock);
#ifdef WINDOWS
		THREAD_LOCK(mRemainTimeLock);
#endif
		for (T* obj : objList)
		{
			if (obj == nullptr)
			{
				continue;
			}
			obj->destroy();
			if (!obj->markDispose(this))
			{
				ERROR_PROFILE((string("3重复销毁对象:") + typeid(T).name()).c_str());
				continue;
			}
			mUnusedList.insertOrGet(typeid(*obj).hash_code()).push_back(obj);
#ifdef WINDOWS
			mClassRemainTimeList.erase(obj);
#endif
		}
		objList.clear();
	}
	template<int Length, typename T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	void destroyClassList(ArrayList<Length, T*>& objList)
	{
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (objList.isEmpty() || mDestroied)
		{
			return;
		}

		// 加入到列表,并重置所有属性
		THREAD_LOCK(mLock);
#ifdef WINDOWS
		THREAD_LOCK(mRemainTimeLock);
#endif
		for (T* obj : objList)
		{
			if (obj == nullptr)
			{
				continue;
			}
			obj->destroy();
			if (!obj->markDispose(this))
			{
				ERROR_PROFILE((string("4重复销毁对象:") + typeid(T).name()).c_str());
				continue;
			}
			mUnusedList.insertOrGet(typeid(*obj).hash_code()).push_back(obj);
#ifdef WINDOWS
			mClassRemainTimeList.erase(obj);
#endif
		}
		objList.clear();
	}
	void clearPool()
	{
		THREAD_LOCK(mLock);
		THREAD_LOCK(mTotalCountLock);
		for (auto& item : mUnusedList)
		{
			DELETE_LIST(item.second);
		}
		mUnusedList.clear(true);
		mTotalCount.clear(true);
#ifdef WINDOWS
		THREAD_LOCK(mRemainTimeLock);
		mClassRemainTimeList.clear(true);
#endif
	}
	bool setEnableStackTrace(bool enable) 
	{
		const bool last = mEnableStackTrace;
		mEnableStackTrace = enable;
		return last;
	}
	void dump() override
	{
		THREAD_LOCK(mTotalCountLock);
		for (const auto& item : mTotalCount)
		{
			const int itemCount = item.second.second;
			if (itemCount > 1000)
			{
				const int unuseCount = mUnusedList.tryGet(item.first).size();
				LOG("ClassBaseTypePoolThread: " + item.second.first + "的数量:" + IToS(itemCount) + ",总大小:" + LLToS(itemCount * sizeof(BaseClassType) / 1024) + "KB" + ", 未使用数量:" + IToS(unuseCount));
			}
		}
	}
protected:
	void onSecond() override
	{
#ifdef WINDOWS
		THREAD_LOCK(mRemainTimeLock);
		for (auto& item : mClassRemainTimeList)
		{
			item.second.first -= 1.0f;
			if (item.second.first <= 0.0f)
			{
				ERROR(string("ClassBaseTypePoolThread: ") + typeid(*item.first).name() + ",对象内存泄漏,stack:" + item.second.second);
			}
		}
#endif
	}
protected:
	HashMap<size_t, Vector<BaseClassType*>> mUnusedList;// 未使用对象的列表
	HashMap<size_t, pair<string, int>> mTotalCount;		// 创建的对象总数
	HashMap<BaseClassType*, pair<float, string>> mClassRemainTimeList;// 创建对象的销毁倒计时,如果倒计时结束还没有被销毁,就认为忘了被销毁,需要报错提示
	ThreadLock mLock;									// mUnusedList的锁
	ThreadLock mTotalCountLock;							// mTotalCount的锁
	ThreadLock mRemainTimeLock;							// mClassRemainTimeList的锁
	bool mShowCountLog = true;							// 当对象池创建总数达到一定数量时,是否打印日志信息,一般打印,但是日志的对象池不能打印
	bool mEnableStackTrace = false;						// 是否启用堆栈追踪
	const int TRACE_DEPTH = 10;							// 追踪的堆栈深度
	atomic<llong> mAssignIDSeed;						// 对象的分配ID种子
};