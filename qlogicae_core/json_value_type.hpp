#pragma once

namespace QLogicaeCore
{
    enum class JsonValueType : uint8_t
    {
        NONE,
        NUMBER,
        FLOAT,
        STRING,
        ARRAY,
        OBJECT
    };
}
