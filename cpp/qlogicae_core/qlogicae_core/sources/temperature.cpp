#include "pch.hpp"

#include "../includes/temperature.hpp"

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
                case TemperatureUnitType::CELSIUS:
                    return value_in_celsius;
                
                case TemperatureUnitType::FAHRENHEIT:
                    return (value_in_celsius * 9.0 / 5.0) + 32.0;

                case TemperatureUnitType::KELVIN:
                    return value_in_celsius + 273.15;

                default:
                    return value;
            }
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Temperature::convert()",
                exception.what()
            );
        }
    }

    void Temperature::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    void Temperature::get_instance(
        Result<Temperature*>& result
    )
    {
        static Temperature instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }

    void Temperature::convert(
        Result<double>& result,
        const double& value,
        const TemperatureUnitType& from_unit,
        const TemperatureUnitType& to_unit
    )
    {
        if (from_unit == TemperatureUnitType::NONE ||
            to_unit == TemperatureUnitType::NONE)
        {
            result.set_to_good_status_with_value(value);

            return;
        }

        double value_in_celsius = 0.0;

        switch (from_unit)
        {
        case TemperatureUnitType::CELSIUS:
            value_in_celsius =
                value;
            break;
        case TemperatureUnitType::FAHRENHEIT:
            value_in_celsius =
                (value - 32.0) * 5.0 / 9.0;
            break;
        case TemperatureUnitType::KELVIN:
            value_in_celsius =
                value - 273.15;
            break;
        default:
            value_in_celsius =
                value;
            break;
        }

        switch (to_unit)
        {
        case TemperatureUnitType::CELSIUS:
            result.set_to_good_status_with_value(
                value_in_celsius
            );
            break;
        case TemperatureUnitType::FAHRENHEIT:
            result.set_to_good_status_with_value(
                (value_in_celsius * 9.0 / 5.0) + 32.0
            );
            break;
        case TemperatureUnitType::KELVIN:
            result.set_to_good_status_with_value(
                value_in_celsius + 273.15
            );
            break;
        default:
            result.set_to_good_status_with_value(
                value
            );
            break;
        }
    }
}
