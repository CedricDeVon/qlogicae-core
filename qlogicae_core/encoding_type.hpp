#pragma once

#include <cstdint>

namespace QLogicaeCore
{
    enum class EncodingType :
        uint8_t
    {
        HEX,
        UTF8,
        BASE64
    };
}
