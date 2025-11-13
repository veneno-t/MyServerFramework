#pragma once

#include "FrameDefine.h"

struct MICRO_LEGEND_FRAME_API ProfilerData
{
    uint64_t mTotalTicks = 0;
    llong mCount = 0;
    const char* mFileName = nullptr;
    const char* mFunction = nullptr;
};