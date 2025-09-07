#pragma once

#include "pch.h"

#include "encoder.hpp"

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

    protected:
        Temperature() = default;
        ~Temperature() = default;
        Temperature(const Temperature&) = delete;
        Temperature(Temperature&&) noexcept = delete;
        Temperature& operator = (Temperature&&) = delete;
        Temperature& operator = (const Temperature&) = delete;
    };

    inline static Temperature& TEMPERATURE =
        Temperature::get_instance();
}


