#include "FrameHeader.h"

void TickerSystem::quit()
{
	mTickerPool->destroyClassList(mTickerList);
}

void TickerSystem::update(const float elapsedTime)
{
	SAFE_VECTOR_SCOPE(mTickerList, readList);
	for (Ticker* cor : readList)
	{
		cor->update(elapsedTime);
		if (cor->isFinish())
		{
			mTickerList.eraseElement(cor);
			mTickerPool->destroyClass(cor);
		}
	}
}

void TickerSystem::createTicker(BoolFunction callback)
{
	Ticker* cor = mTickerPool->newClass();
	cor->setCallback(callback);
	mTickerList.push_back(cor);
}