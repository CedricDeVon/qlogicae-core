#pragma once

#include <cstdint>

namespace QLogicaeCore
{
    enum class TaskPriority :
        uint8_t
    {
        HIGH = 0,

        MEDIUM = 1,
        
        LOW = 2
    };
}
