#pragma once

#include "FrameCallback.h"

// 为了避免头文件的互相包含,将errorProfile单独放到一个文件中
namespace ErrorProfile
{
	void MICRO_LEGEND_FRAME_API errorProfile(string&& log, string&& file);
	MICRO_LEGEND_FRAME_API extern ErrorProfileEvent mOnErrorProfileEvent;
};