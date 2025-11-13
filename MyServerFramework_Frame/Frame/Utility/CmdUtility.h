#pragma once

#include "FrameDefine.h"
#include "CommandThreadPool.h"
#include "CommandPool.h"

namespace CmdUtility
{
	template<typename T>
	T* CMD_THREAD()
	{
		auto* cmd = mCommandThreadPool->newClass<T>();
		cmd->setThreadCommand(true);
		return cmd;
	}
	template<typename T>
	T* CMD_DELAY()
	{
		auto* cmd = mCommandPool->newClass<T>();
		cmd->setDelayCommand(true);
		return cmd;
	}
	template<typename T>
	T* CMD_THREAD_DELAY()
	{
		auto* cmd = mCommandThreadPool->newClass<T>();
		cmd->setThreadCommand(true);
		cmd->setDelayCommand(true);
		return cmd;
	}
}

using namespace CmdUtility;