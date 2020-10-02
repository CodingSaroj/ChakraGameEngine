#ifndef CHAKRA_CORE_PROFILER_HPP
#define CHAKRA_CORE_PROFILER_HPP

#include "core/Common.hpp"

namespace Chakra
{
    struct ProfilerStats
    {
        size_t MemoryUsage;
        double FPS;
        double FrameTime;
        double RenderTime;
    };

    extern ProfilerStats s_ProfilerStats;
}

#endif
