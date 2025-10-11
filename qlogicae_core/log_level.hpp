#pragma once

#include <cstdint>

namespace QLogicaeCore
{
    enum class LogLevel : uint8_t
    {
        ALL,
        INFO,
        DEBUG,
        WARNING,
        SUCCESS,
        CRITICAL,
        EXCEPTION,
        HIGHLIGHTED_INFO
    };
}
