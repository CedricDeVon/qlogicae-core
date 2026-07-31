#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeScaleUnitEnumManager \
	)

#include "../includes/time_scale_unit_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	TimeScaleUnitEnumManager
		::TimeScaleUnitEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TimeScaleUnitEnumManagerConfigurations>()
    {
        
    }

	std::string
		TimeScaleUnitEnumManager
			::convert_enum_to_string(
				const TimeScaleUnit&
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
				case (TimeScaleUnit::YEARS):
				{
					return
						"YEARS";
				}
				case (TimeScaleUnit::MONTHS):
				{
					return
						"MONTHS";
				}
				case (TimeScaleUnit::WEEKS):
				{
					return
						"WEEKS";
				}
				case (TimeScaleUnit::DAYS):
				{
					return
						"DAYS";
				}
				case (TimeScaleUnit::HOURS):
				{
					return
						"HOURS";
				}
				case (TimeScaleUnit::MINUTES):
				{
					return
						"MINUTES";
				}
				case (TimeScaleUnit::SECONDS):
				{
					return
						"SECONDS";
				}
				case (TimeScaleUnit::MILLISECONDS):
				{
					return
						"MILLISECONDS";
				}
				case (TimeScaleUnit::MICROSECONDS):
				{
					return
						"MICROSECONDS";
				}
				case (TimeScaleUnit::NANOSECONDS):
				{
					return
						"NANOSECONDS";
				}
				case (TimeScaleUnit::NONE):
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
		TimeScaleUnitEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	TimeScaleUnit
		TimeScaleUnitEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				TimeScaleUnit::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			if
			(
				value == "YEARS"
			)
			{
				return
					TimeScaleUnit
						::YEARS;
			}
			else if
			(
				value == "MONTHS"
			)
			{
				return
					TimeScaleUnit
						::MONTHS;
			}
			else if
			(
				value == "WEEKS"
			)
			{
				return
					TimeScaleUnit
						::WEEKS;
			}			
			else if
			(
				value == "DAYS"
			)
			{
				return
					TimeScaleUnit
						::DAYS;
			}
			else if
			(
				value == "HOURS"
			)
			{
				return
					TimeScaleUnit
						::HOURS;
			}
			else if
			(
				value == "MINUTES"
			)
			{
				return
					TimeScaleUnit
						::MINUTES;
			}			
			else if
			(
				value == "SECONDS"
			)
			{
				return
					TimeScaleUnit
						::SECONDS;
			}
			else if
			(
				value == "MILLISECONDS"
			)
			{
				return
					TimeScaleUnit
						::MILLISECONDS;
			}
			else if
			(
				value == "MICROSECONDS"
			)
			{
				return
					TimeScaleUnit
						::MICROSECONDS;
			}			
			else if
			(
				value == "NANOSECONDS"
			)
			{
				return
					TimeScaleUnit
						::NANOSECONDS;
			}
			else if
			(
				value == "NONE"
			)
			{
				return
					TimeScaleUnit
						::NONE;
			}
			else
			{
				return
					TimeScaleUnit
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
				TimeScaleUnit::NONE
			);		
        }
	}

	TimeScaleUnit
		TimeScaleUnitEnumManager
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

