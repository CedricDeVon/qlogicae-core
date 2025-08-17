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

    std::unordered_map<std::string_view, TimeScaleUnit> Constants::TIME_SCALE_UNIT_ABBREVIATION_STRINGS =
    {
        { Constants::TIME_SCALE_UNIT_ABBREVIATION_NANOSECONDS, TimeScaleUnit::NANOSECONDS },
        { Constants::TIME_SCALE_UNIT_ABBREVIATION_MICROSECONDS, TimeScaleUnit::MICROSECONDS },
        { Constants::TIME_SCALE_UNIT_ABBREVIATION_MILLISECONDS, TimeScaleUnit::MILLISECONDS },
        { Constants::TIME_SCALE_UNIT_ABBREVIATION_SECONDS, TimeScaleUnit::SECONDS },
        { Constants::TIME_SCALE_UNIT_ABBREVIATION_MINUTES, TimeScaleUnit::MINUTES },
        { Constants::TIME_SCALE_UNIT_ABBREVIATION_HOURS, TimeScaleUnit::HOURS },
        { Constants::TIME_SCALE_UNIT_ABBREVIATION_DAYS, TimeScaleUnit::DAYS },
        { Constants::TIME_SCALE_UNIT_ABBREVIATION_WEEKS, TimeScaleUnit::WEEKS },
        { Constants::TIME_SCALE_UNIT_ABBREVIATION_MONTHS, TimeScaleUnit::MONTHS },
        { Constants::TIME_SCALE_UNIT_ABBREVIATION_YEARS, TimeScaleUnit::YEARS }
    };
}

