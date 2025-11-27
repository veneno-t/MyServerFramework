#pragma once

#include "ClassPoolBase.h"
#include "ClassObject.h"
#include "Utility.h"
#include "ErrorProfile.h"

// 传入的参数就是模板类型
// 仅限于在主线程使用
template<typename BaseClassType, typename TypeCheck = typename IsSubClassOf<ClassObject, BaseClassType>::mType>
class ClassBaseTypePool : public ClassPoolBase
{
	BASE(ClassBaseTypePool, ClassPoolBase);
public:
	template<typename T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	void initDefault(const int count)
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(BaseClassType).name());
			return;
		}
#endif
		Vector<BaseClassType*> list(count);
		FOR(count)
		{
			BaseClassType* obj = new T();
			obj->resetProperty();
			list.push_back(obj);
		}
		mUnusedList.insertOrGet(typeid(T).hash_code()).addRange(list);
		mTotalCount.insertOrGet(typeid(T).hash_code(), make_pair(typeid(T).name(), 0)).second += count;
	}
	void quit() override
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(BaseClassType).name());
			return;
		}
#endif
		for (auto& item : mUnusedList)
		{
			DELETE_LIST(item.second);
		}
		mUnusedList.clear();
	}
	template<typename T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	void newClassList(Vector<BaseClassType*>& classList, const int dataCount)
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(BaseClassType).name());
			return;
		}
#endif
		classList.clearAndReserve(dataCount);
		const size_t typeHash = typeid(T).hash_code();
		if (mUnusedList.size() > 0)
		{
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
	template<class T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	T* newClass()
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(BaseClassType).name());
			return nullptr;
		}
#endif
		T* obj = nullptr;
		if (mUnusedList.size() > 0)
		{
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
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(BaseClassType).name());
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
			ERROR_PROFILE((string("0重复销毁对象:") + typeid(T).name()).c_str());
			return;
		}
		// 添加到未使用列表中
		mUnusedList.insertOrGet(typeid(*obj).hash_code()).push_back(obj);
		obj = nullptr;
	}
	// 由于允许传入BaseClassType子类的列表,所以重新定义了一个类型
	template<typename T0, typename T1, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T1>::mType>
	void destroyClassList(HashMap<T0, T1*>& objMap)
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(BaseClassType).name());
			return;
		}
#endif
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (objMap.isEmpty() || mDestroied)
		{
			return;
		}

		// 加入到列表,并重置所有属性
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
		}
		objMap.clear();
	}
	// 由于允许传入BaseClassType子类的列表,所以重新定义了一个类型
	template<typename T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	void destroyClassList(Vector<T*>& objList)
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(BaseClassType).name());
			return;
		}
#endif
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (objList.isEmpty() || mDestroied)
		{
			return;
		}

		// 加入到列表,并重置所有属性
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
		}
		objList.clear();
	}
	template<int Length, typename T, typename TypeCheck0 = typename IsSubClassOf<BaseClassType, T>::mType>
	void destroyClassList(ArrayList<Length, T*>& objList)
	{
#ifdef WINDOWS
		if (!isMainThread())
		{
			ERROR(string("只能在主线程调用,type:") + typeid(BaseClassType).name());
			return;
		}
#endif
		// 如果当前对象池已经被销毁,则不能再重复销毁任何对象
		if (objList.isEmpty() || mDestroied)
		{
			return;
		}

		// 加入到列表,并重置所有属性
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
		}
		objList.clear();
	}
	void dump() override
	{
		for (const auto& item : mTotalCount)
		{
			const int itemCount = item.second.second;
			if (itemCount > 1000)
			{
				const int unuseCount = mUnusedList.tryGet(item.first).size();
				LOG("ClassBaseTypePool: " + item.second.first + "的数量:" + IToS(itemCount) + ",总大小:" + LLToS(itemCount * sizeof(BaseClassType) / 1024) + "KB" + ", 未使用数量:" + IToS(unuseCount));
			}
		}
	}
	//------------------------------------------------------------------------------------------------------------------
protected:
	HashMap<size_t, Vector<BaseClassType*>> mUnusedList;// 未使用对象的列表
	HashMap<size_t, pair<string, int>> mTotalCount;		// 创建的对象总数
	bool mShowCountLog = true;							// 当对象池创建总数达到一定数量时,是否打印日志信息,一般打印,但是日志的对象池不能打印
	llong mAssignIDSeed = 0;							// 对象的分配ID种子
};