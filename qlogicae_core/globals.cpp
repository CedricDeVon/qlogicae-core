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

    std::unordered_map<std::string_view, TemperatureUnitType> Constants::TEMPERATURE_UNIT_TYPE_STRINGS =
    {
        { TEMPERATURE_UNIT_TYPE_CELSIUS, TemperatureUnitType::CELSIUS },
        { TEMPERATURE_UNIT_TYPE_FAHRENHEIT, TemperatureUnitType::FAHRENHEIT },
        { TEMPERATURE_UNIT_TYPE_KELVIN, TemperatureUnitType::KELVIN },
        { TEMPERATURE_UNIT_TYPE_NONE, TemperatureUnitType::NONE }
    };

    std::unordered_map<TemperatureUnitType, std::string_view> Constants::TEMPERATURE_UNIT_TYPE_ENUMS =
    {
        { TemperatureUnitType::CELSIUS, TEMPERATURE_UNIT_TYPE_CELSIUS },
        { TemperatureUnitType::FAHRENHEIT, TEMPERATURE_UNIT_TYPE_FAHRENHEIT },
        { TemperatureUnitType::KELVIN, TEMPERATURE_UNIT_TYPE_KELVIN },
        { TemperatureUnitType::NONE, TEMPERATURE_UNIT_TYPE_NONE }
    };

}

