#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TemperatureManager \
	)

#include "../includes/temperature_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{       
	TemperatureManager
		::TemperatureManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TemperatureManagerConfigurations>()
	{
				
	}

	double
		TemperatureManager
			::convert_unit(
				const double&
					value,
				const TemperatureUnit&
					original_unit,
				const TemperatureUnit&
					target_unit
			)
	{
		try
		{					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				original_unit == TemperatureUnit::NONE ||
				target_unit == TemperatureUnit::NONE
			);			

			double
				result = value;

			switch (original_unit)
			{
				case TemperatureUnit::CELSIUS:
				{
					break;
				}
				case TemperatureUnit::FAHRENHEIT:
				{
					result =
						(result - 32.0) * 5.0 / 9.0;

					break;
				}
				case TemperatureUnit::KELVIN:
				{
					result =
						result - 273.15;

					break;
				}
				default:
				{
					break;
				}
			}

			switch (target_unit)
			{
				case TemperatureUnit::CELSIUS:
				{
					break;
				}
				case TemperatureUnit::FAHRENHEIT:
				{
					result =
						(result * 9.0 / 5.0) + 32.0;

					break;
				}
				case TemperatureUnit::KELVIN:
				{
					result =
						result + 273.15;

					break;
				}
				default:
				{
					break;
				}
			}

			return
				result;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	double
		TemperatureManager
			::convert_unit(
				const double&
					value
			)
	{
		return
			convert_unit(
				value,
				configurations
					.original_unit,
				configurations
					.target_unit
			);
	}
}

#endif

