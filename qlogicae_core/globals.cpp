#pragma once

#include "pch.h"

#include "globals.hpp"

namespace QLogicaeCore
{
    bool convert_to_rapidjson_value(
        const Json& source,
        rapidjson::Value& target,
        rapidjson::Document::AllocatorType& allocator)
    {
        std::visit(JsonVisitor { target, allocator }, source.value);

        return true;
    }
}

