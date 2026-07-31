#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TemperatureUnitEnumManager \
	)

#include "../includes/temperature_unit_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	TemperatureUnitEnumManager
		::TemperatureUnitEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TemperatureUnitEnumManagerConfigurations>()
    {
        
    }

	std::string
		TemperatureUnitEnumManager
			::convert_enum_to_string(
				const TemperatureUnit&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				"NONE",
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			switch (value)
			{
				case (TemperatureUnit::CELSIUS):
				{
					return
						"CELSIUS";
				}
				case (TemperatureUnit::FAHRENHEIT):
				{
					return
						"FAHRENHEIT";
				}
				case (TemperatureUnit::KELVIN):
				{
					return
						"KELVIN";
				}
				case (TemperatureUnit::NONE):
				{
					return
						"NONE";
				}				
				default:
				{
					return
						"NONE";
				}
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {	
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				"NONE"
			);
        }
	}

	std::string
		TemperatureUnitEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	TemperatureUnit
		TemperatureUnitEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				TemperatureUnit::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			if
			(
				value == "CELSIUS"
			)
			{
				return
					TemperatureUnit
						::CELSIUS;
			}
			else if
			(
				value == "FAHRENHEIT"
			)
			{
				return
					TemperatureUnit
						::FAHRENHEIT;
			}
			else if
			(
				value == "KELVIN"
			)
			{
				return
					TemperatureUnit
						::KELVIN;
			}			
			else if
			(
				value == "NONE"
			)
			{
				return
					TemperatureUnit
						::NONE;
			}
			else
			{
				return
					TemperatureUnit
						::NONE;
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				TemperatureUnit::NONE
			);			
        }
	}

	TemperatureUnit
		TemperatureUnitEnumManager
			::convert_string_to_enum()
	{
		return
			convert_string_to_enum(
				convert_enum_to_string(
					configurations
						.type
				)
			);
	}
}

#endif

