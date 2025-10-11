#pragma once

#include <cstdint>

namespace QLogicaeCore
{
    enum class FileMode : uint8_t
    {
        READ,
        WRITE,
        APPEND
    };
}
