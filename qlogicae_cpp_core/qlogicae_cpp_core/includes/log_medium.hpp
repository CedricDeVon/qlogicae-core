#pragma once

#include <cstdint>

namespace QLogicaeCore
{
    enum class LogMedium :
        uint8_t
    {
        ALL,

        FILE,

        CONSOLE,

        NONE
    };
}
