#include "FrameHeader.h"

MovableObject::~MovableObject()
{
	DELETE(mDestroyCallbackList);
}

void MovableObject::destroy()
{
	base::destroy();
	if (mDestroyCallbackList != nullptr && mDestroyCallbackList->size() > 0)
	{
		for (const auto& pair : *mDestroyCallbackList)
		{
			pair.first(this, pair.second);
		}
		mDestroyCallbackList->clear();
	}
	mComMove = nullptr;
}

void MovableObject::resetProperty()
{
	base::resetProperty();
	if (mDestroyCallbackList != nullptr)
	{
		mDestroyCallbackList->clear();
	}
	mComMove = nullptr;
	mLastPosition.clear();
	mPosition.clear();
	mEnableLastPosition = false;
	mMovedDuringFrame = false;
	mHasLastPosition = false;
}

void MovableObject::update(const float elapsedTime)
{
	base::update(elapsedTime);
	if (mEnableLastPosition)
	{
		mMovedDuringFrame = mHasLastPosition && !isVectorEqual(mPosition, mLastPosition);
		mLastPosition = mPosition;
		mHasLastPosition = true;
	}
}

MovableObjectComponentMove* MovableObject::getComponentMove()
{
	if (mComMove == nullptr)
	{
		mComMove = getComponent<MovableObjectComponentMove>();
		if (mComMove == nullptr)
		{
			mComMove = addComponent<MovableObjectComponentMove>();
		}
	}
	return mComMove;
}

void MovableObject::removeDestroyCallback(const OnObjectDestroy callback, const void* userData)
{
	if (mDestroyCallbackList == nullptr || mDestroyCallbackList->isEmpty())
	{
		return;
	}
	FOR_VECTOR(*mDestroyCallbackList)
	{
		const auto& value = (*mDestroyCallbackList)[i];
		if (value.first == callback && value.second == userData)
		{
			mDestroyCallbackList->eraseAt(i);
			break;
		}
	}
}