#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "encoder.hpp"
#include "utilities.hpp"

namespace QLogicaeCore
{
    class Temperature
    {
    public:
        double convert(
            const double& value,
            const TemperatureUnitType& from_unit,
            const TemperatureUnitType& to_unit
        );

        static Temperature& get_instance();

        void setup(
            Result<void>& result
        );

        void convert(Result<double>& result,
            const double& value,
            const TemperatureUnitType& from_unit,
            const TemperatureUnitType& to_unit
        );

        static void get_instance(
            Result<Temperature*>& result
        );

    protected:
        Temperature() = default;
        
        ~Temperature() = default;
        
        Temperature(
            const Temperature& temperature
        ) = delete;
        
        Temperature(
            Temperature&& temperature
        ) noexcept = delete;
        
        Temperature& operator = (
            Temperature&& temperature
        ) = delete;
        
        Temperature& operator = (
            const Temperature& temperature
        ) = delete;
    };

    inline static Temperature& TEMPERATURE =
        Temperature::get_instance();
}
