#include "pch.hpp"

#include "temperature.hpp"

namespace QLogicaeCore
{
    Temperature& Temperature::get_instance()
    {
        static Temperature instance;

        return instance;
    }

    double Temperature::convert(
        const double& value,
        const TemperatureUnitType& from_unit,
        const TemperatureUnitType& to_unit
    )
    {
        try
        {
            if (from_unit == TemperatureUnitType::NONE ||
                to_unit == TemperatureUnitType::NONE)
            {
                return value;
            }

            double value_in_celsius = 0.0;

            switch (from_unit)
            {
            case TemperatureUnitType::CELSIUS:
                value_in_celsius = value;
                break;
            case TemperatureUnitType::FAHRENHEIT:
                value_in_celsius = (value - 32.0) * 5.0 / 9.0;
                break;
            case TemperatureUnitType::KELVIN:
                value_in_celsius = value - 273.15;
                break;
            default:
                value_in_celsius = value;
                break;
            }

            switch (to_unit)
            {
                case TemperatureUnitType::CELSIUS: return value_in_celsius;
                case TemperatureUnitType::FAHRENHEIT: return (value_in_celsius * 9.0 / 5.0) + 32.0;
                case TemperatureUnitType::KELVIN: return value_in_celsius + 273.15;
                default: return value;
            }
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at Temperature::convert(): " + exception.what());
        }
    }
}
