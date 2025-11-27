#pragma once

#include "FrameDefine.h"

class MICRO_LEGEND_FRAME_API Line2
{
public:
	Line2(Vector2 start, Vector2 end):
		mStart(start),
		mEnd(end)
	{}
public:
	Vector2 mStart;
	Vector2 mEnd;
};