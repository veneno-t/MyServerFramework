#pragma once

#include "LogInfo.h"
#include "ClassPoolThread.h"

class LogInfoPool : public ClassPoolThread<LogInfo>
{
	BASE(LogInfoPool, ClassPoolThread<LogInfo>);
public:
	LogInfoPool()
	{
		mShowCountLog = false;
	}
};