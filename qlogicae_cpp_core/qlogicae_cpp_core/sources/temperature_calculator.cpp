#include "pch.hpp"

#include "../includes/temperature_calculator.hpp"

namespace QLogicaeCppCore
{       
    TemperatureCalculator::TemperatureCalculator()
    {
        
    }

    TemperatureCalculator::~TemperatureCalculator()
    {
        
    }

    void TemperatureCalculator::convert(
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
            {
                value_in_celsius =
                    value;
                break;
            }
            case TemperatureUnitType::FAHRENHEIT:
            {
                value_in_celsius =
                    (value - 32.0) * 5.0 / 9.0;
                break;
            }
            case TemperatureUnitType::KELVIN:
            {
                value_in_celsius =
                    value - 273.15;
                break;
            }
            default:
            {
                value_in_celsius =
                    value;
                break;
            }
        }

        switch (to_unit)
        {
            case TemperatureUnitType::CELSIUS:
            {
                result.set_to_good_status_with_value(
                    value_in_celsius
                );
                break;
            }
            case TemperatureUnitType::FAHRENHEIT:
            {
                result.set_to_good_status_with_value(
                    (value_in_celsius * 9.0 / 5.0) + 32.0
                );
                break;
            }
            case TemperatureUnitType::KELVIN:
            {
                result.set_to_good_status_with_value(
                    value_in_celsius + 273.15
                );
                break;
            }
            default:
            {
                result.set_to_good_status_with_value(
                    value
                );
                break;
            }
        }
    }
}
