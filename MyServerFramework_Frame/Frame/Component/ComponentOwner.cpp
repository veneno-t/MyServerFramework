#include "FrameHeader.h"

ComponentOwner::~ComponentOwner()
{
	DELETE(mFrameTickList);
	DELETE(mLateFrameTickList);
	DELETE(mSecondTickList);
	DELETE(mBreakbleComponentList);
	DELETE(mComponentArray);
	destroyAllComponents();
	DELETE(mComponentTypeMap);
	DELETE(mComponentTypeList);
}

void ComponentOwner::update(const float elapsedTime)
{
	// 每帧都更新的组件
	if (mFrameTickList != nullptr)
	{
		SAFE_VECTOR_SCOPE(*mFrameTickList, readList);
		for (const auto& item : readList)
		{
			FrameTickCallback tickFunction = item.second;
			// 可能会存在遍历过程中被禁用的组件
			if (tickFunction == nullptr)
			{
				continue;
			}
			tickFunction(item.first, elapsedTime);
			// 对象即将被销毁时,不应该再执行任何逻辑
			if (isPendingDestroy())
			{
				return;
			}
			// 如果当前对象已经被销毁了则不能再执行后续的组件更新,不过正常不应该在Tick中销毁对象
			if (isDestroy())
			{
				ERROR_PROFILE((string("0当前对象已经被销毁:") + typeid(*this).name()).c_str());
				mFrameTickList->clear();
				return;
			}
		}
	}

	// 每秒更新的逻辑跟上面每帧更新的完全一样
	if (mSecondTickList != nullptr && tickTimerLoop(mTickTimer, elapsedTime, 1.0f))
	{
		SAFE_VECTOR_SCOPE(*mSecondTickList, readList);
		for (const auto& item : readList)
		{
			SecondTickCallback tickFunction = item.second;
			// 可能会存在遍历过程中被禁用的组件
			if (tickFunction == nullptr)
			{
				continue;
			}
			tickFunction(item.first);
			// 对象即将被销毁时,不应该再执行任何逻辑
			if (isPendingDestroy())
			{
				return;
			}
			// 如果当前对象已经被销毁了则不能再执行后续的组件更新,不过正常不应该在Tick中销毁对象
			if (isDestroy())
			{
				ERROR_PROFILE((string("0当前对象已经被销毁:") + typeid(*this).name()).c_str());
				mSecondTickList->clear();
				return;
			}
		}
	}
}

void ComponentOwner::lateUpdate(float elapsedTime)
{
	// 每帧都更新的组件
	if (mLateFrameTickList != nullptr)
	{
		SAFE_VECTOR_SCOPE(*mLateFrameTickList, readList);
		for (const auto& item : readList)
		{
			FrameTickCallback tickFunction = item.second;
			// 可能会存在遍历过程中被禁用的组件
			if (tickFunction == nullptr)
			{
				continue;
			}
			tickFunction(item.first, elapsedTime);
			// 对象即将被销毁时,不应该再执行任何逻辑
			if (isPendingDestroy())
			{
				return;
			}
			// 如果当前对象已经被销毁了则不能再执行后续的组件更新,不过正常不应该在Tick中销毁对象
			if (isDestroy())
			{
				ERROR_PROFILE((string("0当前对象已经被销毁:") + typeid(*this).name()).c_str());
				mLateFrameTickList->clear();
				return;
			}
		}
	}
}

void ComponentOwner::destroyComponent(GameComponent* component)
{
	if (component == nullptr || component->isDestroy())
	{
		return;
	}
	// 禁用组件,这样可以使组件的tick函数从下面的列表中移除,避免正在遍历时访问到了已经被销毁的组件tick
	component->setActive(false);
	if (mFrameTickList != nullptr)
	{
		auto& mainList = mFrameTickList->getMainList();
		FOR_VECTOR(mainList)
		{
			if (mainList[i].first == component)
			{
				mFrameTickList->eraseAt(i);
				break;
			}
		}
	}
	if (mLateFrameTickList != nullptr)
	{
		auto& mainList = mLateFrameTickList->getMainList();
		FOR_VECTOR(mainList)
		{
			if (mainList[i].first == component)
			{
				mLateFrameTickList->eraseAt(i);
				break;
			}
		}
	}
	if (mSecondTickList != nullptr)
	{
		auto& mainList = mSecondTickList->getMainList();
		FOR_VECTOR(mainList)
		{
			if (mainList[i].first == component)
			{
				mSecondTickList->eraseAt(i);
				break;
			}
		}
	}
	if (mComponentTypeMap != nullptr)
	{
		mComponentTypeMap->erase(component->getType());
	}
	if (mComponentTypeList != nullptr)
	{
		mComponentTypeList->eraseElement(component);
	}
	if (mBreakbleComponentList != nullptr)
	{
		mBreakbleComponentList->eraseElement(component);
	}
	if (mComponentArray != nullptr)
	{
		mComponentArray->eraseElement(component);
	}
}

void ComponentOwner::destroyAllComponents()
{
	if (mFrameTickList != nullptr)
	{
		mFrameTickList->clear();
	}
	if (mLateFrameTickList != nullptr)
	{
		mLateFrameTickList->clear();
	}
	if (mSecondTickList != nullptr)
	{
		mSecondTickList->clear();
	}
	if (mComponentTypeMap != nullptr)
	{
		mComponentTypeMap->clear();
	}
	if (mComponentTypeList != nullptr)
	{
		mGameComponentPool->destroyClassList(*mComponentTypeList);
	}
	if (mBreakbleComponentList != nullptr)
	{
		mBreakbleComponentList->clear();
	}
	if (mComponentArray != nullptr)
	{
		mComponentArray->clear();
	}
}

void ComponentOwner::resetProperty()
{
	base::resetProperty();
	if (mFrameTickList != nullptr)
	{
		mFrameTickList->clear();
	}
	if (mLateFrameTickList != nullptr)
	{
		mLateFrameTickList->clear();
	}
	if (mSecondTickList != nullptr)
	{
		mSecondTickList->clear();
	}
	if (mComponentTypeMap != nullptr)
	{
		mComponentTypeMap->clear();
	}
	if (mComponentTypeList != nullptr)
	{
		mComponentTypeList->clear();
	}
	if (mBreakbleComponentList != nullptr)
	{
		mBreakbleComponentList->clear();
	}
	if (mComponentArray != nullptr)
	{
		mComponentArray->clear();
	}
	mTickTimer = 1.0f;
}

void ComponentOwner::registeFrameTick(GameComponent* component, FrameTickCallback callback)
{
	if (mFrameTickList == nullptr)
	{
		mFrameTickList = new SafeVector<pair<GameComponent*, FrameTickCallback>>();
	}
	mFrameTickList->push_back(make_pair(component, callback));
	if (dynamic_cast<IComponentBreakable*>(component) != nullptr)
	{
		if (mBreakbleComponentList == nullptr)
		{
			mBreakbleComponentList = new Vector<GameComponent*>();
		}
		mBreakbleComponentList->push_back(component);
	}
}

void ComponentOwner::unregisteFrameTick(GameComponent* component, FrameTickCallback callback)
{
	if (mFrameTickList != nullptr)
	{
		mFrameTickList->eraseElement(make_pair(component, callback));
	}
	if (mBreakbleComponentList != nullptr && dynamic_cast<IComponentBreakable*>(component) != nullptr)
	{
		mBreakbleComponentList->eraseElement(component);
	}
}

void ComponentOwner::registeLateFrameTick(GameComponent* component, FrameTickCallback callback)
{
	if (mLateFrameTickList == nullptr)
	{
		mLateFrameTickList = new SafeVector<pair<GameComponent*, FrameTickCallback>>();
	}
	mLateFrameTickList->push_back(make_pair(component, callback));
	if (dynamic_cast<IComponentBreakable*>(component) != nullptr)
	{
		if (mBreakbleComponentList == nullptr)
		{
			mBreakbleComponentList = new Vector<GameComponent*>();
		}
		mBreakbleComponentList->push_back(component);
	}
}

void ComponentOwner::unregisteLateFrameTick(GameComponent* component, FrameTickCallback callback)
{
	if (mLateFrameTickList != nullptr)
	{
		mLateFrameTickList->eraseElement(make_pair(component, callback));
	}
	if (mBreakbleComponentList != nullptr && dynamic_cast<IComponentBreakable*>(component) != nullptr)
	{
		mBreakbleComponentList->eraseElement(component);
	}
}

void ComponentOwner::registeSecondTick(GameComponent* component, SecondTickCallback callback)
{
	if (mSecondTickList == nullptr)
	{
		mSecondTickList = new SafeVector<pair<GameComponent*, SecondTickCallback>>();
	}
	mSecondTickList->push_back(make_pair(component, callback));
	if (dynamic_cast<IComponentBreakable*>(component) != nullptr)
	{
		if (mBreakbleComponentList == nullptr)
		{
			mBreakbleComponentList = new Vector<GameComponent*>();
		}
		mBreakbleComponentList->push_back(component);
	}
}

void ComponentOwner::unregisteSecondTick(GameComponent* component, SecondTickCallback callback)
{
	if (mSecondTickList != nullptr)
	{
		mSecondTickList->eraseElement(make_pair(component, callback));
	}
	if (mBreakbleComponentList != nullptr && dynamic_cast<IComponentBreakable*>(component) != nullptr)
	{
		mBreakbleComponentList->eraseElement(component);
	}
}