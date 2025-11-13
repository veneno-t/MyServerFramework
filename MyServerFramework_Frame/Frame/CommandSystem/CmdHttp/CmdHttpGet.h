#pragma once

#include "GameCommand.h"

// 执行Http的Get请求
class MICRO_LEGEND_FRAME_API CmdHttpGet : public GameCommand
{
	BASE(CmdHttpGet, GameCommand);
public:
	void reset() override
	{
		mURL = "";
		mContentType = "";
		mCallback = nullptr;
	}
	void execute() override;
public:
	string mURL;
	string mContentType;
	StringCallback mCallback = nullptr;
};