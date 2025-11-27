#pragma once

#include "FrameDefine.h"
#include "Profiler.h"

// 性能查看器
// 用法,在需要查看性能消耗的地方添加PROFILE()即可
struct MICRO_LEGEND_FRAME_API ProfilerScope
{
    ProfilerData* d = nullptr;
    uint64_t start = 0;
    ProfilerScope(int _id, const char* file, const char* func)
    {
        d = &Profiler::get(_id, file, func);
        start = readTSC();
    }
    ~ProfilerScope()
    {
        const uint64_t end = readTSC();
        d->mTotalTicks += (end - start);
        ++d->mCount;
    }
};