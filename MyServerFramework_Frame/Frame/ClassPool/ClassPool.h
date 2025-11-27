#pragma once

#include "ClassPoolBase.h"
#include "ClassObject.h"
#include "ErrorProfile.h"
#include "SafeHashMap.h"

// 固定类型的对象池
// 仅在主线程用
template<typename ClassType, typename TypeCheck = typename IsSubClassOf<ClassObject, ClassType>::mType>
class ClassPool : public ClassPoolBase
{
	BASE(ClassPool, ClassPoolBase);
public:
	void initDefault(const int count)
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(ClassType).name());
			return;
		}
#endif
		Vector<ClassType*> list(count);
		FOR(count)
		{
			ClassType* obj = new ClassType();
			obj->resetProperty();
			list.push_back(obj);
		}
		mUnusedList.addRange(list);
		mTotalCount += count;
	}
	void quit() override
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(ClassType).name());
			return;
		}
#endif
		DELETE_LIST(mUnusedList);
	}
	ClassType* newClass()
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(ClassType).name());
			return nullptr;
		}
#endif
		ClassType* obj = nullptr;
		// 首先从未使用的列表中获取,获取不到再重新创建一个
		while (mUnusedList.size() > 0 && obj == nullptr)
		{
			obj = mUnusedList.popBack(nullptr);
		}

		// 没有找到可以用的,则创建一个
		if (obj == nullptr)
		{
			obj = new ClassType();
			obj->resetProperty();
			++mTotalCount;
			if (mShowCountLog && (mTotalCount & (4096 - 1)) == 0)
			{
				LOG(string(typeid(*obj).name()) + "的数量已经达到了" + IToS(mTotalCount) + "个");
			}
		}

		// 设置为可用状态
		obj->markUsable(this, ++mAssignIDSeed);
		return obj;
	}
	void destroyClass(ClassType*& obj)
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(ClassType).name());
			return;
		}
#endif
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (mDestroied || obj == nullptr)
		{
			return;
		}

		obj->destroy();
		if (!obj->markDispose(this))
		{
			ERROR_PROFILE((string("0重复销毁对象:") + typeid(ClassType).name()).c_str());
			return;
		}
		// 添加到未使用列表中
		mUnusedList.push_back(obj);
		obj = nullptr;
	}
	void destroyClassList(SafeVector<ClassType*>& objList)
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(ClassType).name());
			return;
		}
#endif
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (mDestroied || objList.isEmpty())
		{
			return;
		}

		// 再添加到列表
		mUnusedList.reserve(mUnusedList.size() + objList.size());
		for (ClassType* obj : objList.getMainList())
		{
			if (obj == nullptr)
			{
				continue;
			}
			obj->destroy();
			if (!obj->markDispose(this))
			{
				ERROR_PROFILE((string("1重复销毁对象:") + typeid(ClassType).name()).c_str());
				continue;
			}
		}
		mUnusedList.addRange(objList.getMainList());
		objList.clear();
	}
	void destroyClassList(Vector<ClassType*>& objList)
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(ClassType).name());
			return;
		}
#endif
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (mDestroied || objList.isEmpty())
		{
			return;
		}
		
		// 再添加到列表
		mUnusedList.reserve(mUnusedList.size() + objList.size());
		for (ClassType* obj : objList)
		{
			if (obj == nullptr)
			{
				continue;
			}
			obj->destroy();
			if (!obj->markDispose(this))
			{
				ERROR_PROFILE((string("1重复销毁对象:") + typeid(ClassType).name()).c_str());
				continue;
			}
		}
		mUnusedList.addRange(objList);
		objList.clear();
	}
	template<int Length>
	void destroyClassList(ArrayList<Length, ClassType*>& objList)
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(ClassType).name());
			return;
		}
#endif
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (mDestroied || objList.isEmpty())
		{
			return;
		}

		// 再添加到列表
		mUnusedList.reserve(mUnusedList.size() + objList.size());
		for (ClassType* obj : objList)
		{
			if (obj == nullptr)
			{
				continue;
			}
			obj->destroy();
			if (!obj->markDispose(this))
			{
				ERROR_PROFILE((string("1重复销毁对象:") + typeid(ClassType).name()).c_str());
				continue;
			}
		}
		mUnusedList.addRange(objList);
		objList.clear();
	}
	template<typename T0>
	void destroyClassList(HashMap<T0, ClassType*>& objMap)
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(ClassType).name());
			return;
		}
#endif
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (mDestroied || objMap.isEmpty())
		{
			return;
		}

		// 添加到未使用列表中
		mUnusedList.reserve(mUnusedList.size() + objMap.size());
		for (const auto& objPair : objMap)
		{
			ClassType* obj = objPair.second;
			if (obj == nullptr)
			{
				continue;
			}
			obj->destroy();
			if (!obj->markDispose(this))
			{
				ERROR_PROFILE((string("2重复销毁对象:") + typeid(ClassType).name()).c_str());
				continue;
			}
			mUnusedList.push_back(obj);
		}
		objMap.clear();
	}
	template<typename T0>
	void destroyClassList(SafeHashMap<T0, ClassType*>& objMap)
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(ClassType).name());
			return;
		}
#endif
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (mDestroied || objMap.isEmpty())
		{
			return;
		}

		// 添加到未使用列表中
		mUnusedList.reserve(mUnusedList.size() + objMap.size());
		for (const auto& objPair : objMap.getMainList())
		{
			ClassType* obj = objPair.second;
			if (obj == nullptr)
			{
				continue;
			}
			obj->destroy();
			if (!obj->markDispose(this))
			{
				ERROR_PROFILE((string("2重复销毁对象:") + typeid(ClassType).name()).c_str());
				continue;
			}
			mUnusedList.push_back(obj);
		}
		objMap.clear();
	}
	void dump() override
	{
		if (mTotalCount > 1000)
		{
			LOG("ClassPool: " + string(typeid(ClassType).name()) + "的数量:" + IToS(mTotalCount) + ",总大小:" + LLToS(mTotalCount * sizeof(ClassType) / 1024) + "KB" + ", 未使用数量:" + IToS(mUnusedList.size()));
		}
	}
protected:
	Vector<ClassType*> mUnusedList;		// 未使用列表
	llong mAssignIDSeed = 0;			// 对象的分配ID种子
	int mTotalCount = 0;				// 创建的对象总数
	bool mShowCountLog = true;			// 当对象池创建总数达到一定数量时,是否打印日志信息,一般打印,但是日志的对象池不能打印
};