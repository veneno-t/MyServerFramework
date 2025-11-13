#include "FrameHeader.h"

void TimeTaskSystem::quit()
{
	DELETE_LIST(mTimeTaskList);
}

void TimeTaskSystem::update(const float elapsedTime)
{
	for (TimeTask* task : mTimeTaskList)
	{
		task->update(elapsedTime);
	}
}