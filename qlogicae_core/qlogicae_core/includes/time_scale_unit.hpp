#pragma once

#include <cstdint>

namespace QLogicaeCore
{
    enum class TimeScaleUnit :
        uint8_t
    {
        NANOSECONDS,
        
        MICROSECONDS,
        
        MILLISECONDS,
        
        SECONDS,
        
        MINUTES,
        
        HOURS,
        
        DAYS,
        
        WEEKS,
        
        MONTHS,
        
        YEARS
    };
}
