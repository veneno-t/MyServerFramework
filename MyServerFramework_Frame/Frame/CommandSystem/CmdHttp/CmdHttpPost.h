#pragma once

#include "GameCommand.h"

// 执行Http的Post请求
class MICRO_LEGEND_FRAME_API CmdHttpPost : public GameCommand
{
	BASE(CmdHttpPost, GameCommand);
public:
	void reset() override
	{
		mURL = "";
		mContentType = "";
		mPostData = "";
		mCallback = nullptr;
	}
	void execute() override;
public:
	string mURL;
	string mContentType;
	string mPostData;
	StringCallback mCallback = nullptr;
};