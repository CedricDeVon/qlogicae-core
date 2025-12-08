#pragma once

#include "result.hpp"
#include "instance_manager.hpp"
#include "temperature_unit_type.hpp"

namespace QLogicaeCppCore
{
    class TemperatureCalculator
    {
    public:
        TemperatureCalculator();
        
        ~TemperatureCalculator();
        
        TemperatureCalculator(
            const TemperatureCalculator& instance
        ) = delete;
        
        TemperatureCalculator(
            TemperatureCalculator&& instance
        ) noexcept = delete;
        
        TemperatureCalculator& operator = (
            TemperatureCalculator&& instance
        ) = delete;
        
        TemperatureCalculator& operator = (
            const TemperatureCalculator& instance
        ) = delete;

        void convert(
            Result<double>& result,
            const double& value,
            const TemperatureUnitType& from_unit,
            const TemperatureUnitType& to_unit
        );
    };

    inline static TemperatureCalculator& TEMPERATURE_CALCULATOR =
        InstanceManager::get_instance<TemperatureCalculator>();
}
