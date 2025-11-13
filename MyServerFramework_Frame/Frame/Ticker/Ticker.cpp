#include "FrameHeader.h"

void Ticker::update(const float elapsedTime)
{
	if (mCallback != nullptr)
	{
		mFinish = !mCallback();
	}
}

void Ticker::resetProperty()
{
	base::resetProperty();
	mCallback = nullptr;
	mFinish = false;
}