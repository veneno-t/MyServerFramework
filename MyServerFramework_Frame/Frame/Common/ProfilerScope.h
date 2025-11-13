#pragma once

#include "FrameDefine.h"
#include "Profiler.h"

// 性能查看器
// 用法,在需要查看性能消耗的地方添加PROFILE()即可
struct MICRO_LEGEND_FRAME_API ProfilerScope
{
    int id = 0;
    uint64_t start = 0;
    ProfilerScope(const char* file, const char* func, int _id) :
        id(_id), 
        start(readTSC())
    {
        Profiler::get(id, file, func);
    }
    ~ProfilerScope()
    {
        auto end = readTSC();
        auto& d = Profiler::mData[id];
        d.mTotalTicks += (end - start);
        ++d.mCount;
    }
};