#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeFormatEnumManager \
	)

#include "../includes/time_format_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        
	TimeFormatEnumManager
		::TimeFormatEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TimeFormatEnumManagerConfigurations>()
    {
        
    }

	std::string
		TimeFormatEnumManager
			::convert_enum_to_string(
				const TimeFormat&
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
				case (TimeFormat::UNIX):
				{
					return
						"UNIX";
				}
				case (TimeFormat::ISO8601):
				{
					return
						"ISO8601";
				}
				case (TimeFormat::SECOND_LEVEL_TIMESTAMP):
				{
					return
						"SECOND_LEVEL_TIMESTAMP";
				}
				case (TimeFormat::MILLISECOND_LEVEL_TIMESTAMP):
				{
					return
						"MILLISECOND_LEVEL_TIMESTAMP";
				}
				case (TimeFormat::MICROSECOND_LEVEL_TIMESTAMP):
				{
					return
						"MICROSECOND_LEVEL_TIMESTAMP";
				}
				case (TimeFormat::FULL_TIMESTAMP):
				{
					return
						"FULL_TIMESTAMP";
				}
				case (TimeFormat::FULL_DASHED_TIMESTAMP):
				{
					return
						"FULL_DASHED_TIMESTAMP";
				}
				case (TimeFormat::HOUR_12):
				{
					return
						"HOUR_12";
				}
				case (TimeFormat::HOUR_24):
				{
					return
						"HOUR_24";
				}
				case (TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND):
				{
					return
						"MILLISECOND_MICROSECOND_NANOSECOND";
				}
				case (TimeFormat::DATE_DASHED):
				{
					return
						"DATE_DASHED";
				}
				case (TimeFormat::DATE_MDY_SLASHED):
				{
					return
						"DATE_MDY_SLASHED";
				}
				case (TimeFormat::DATE_DMY_SLASHED):
				{
					return
						"DATE_DMY_SLASHED";
				}
				case (TimeFormat::DATE_DMY_SPACED):
				{
					return
						"DATE_DMY_SPACED";
				}
				case (TimeFormat::DATE_VERBOSE):
				{
					return
						"DATE_VERBOSE";
				}
				case (TimeFormat::NONE):
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
		TimeFormatEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	TimeFormat
		TimeFormatEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				TimeFormat::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);	

			if
			(
				value == "UNIX"
			)
			{
				return
					TimeFormat
						::UNIX;
			}
			else if
			(
				value == "ISO8601"
			)
			{
				return
					TimeFormat
						::ISO8601;
			}	
			else if
			(
				value == "SECOND_LEVEL_TIMESTAMP"
			)
			{
				return
					TimeFormat
						::SECOND_LEVEL_TIMESTAMP;
			}
			else if
			(
				value == "MILLISECOND_LEVEL_TIMESTAMP"
			)
			{
				return
					TimeFormat
						::MILLISECOND_LEVEL_TIMESTAMP;
			}	
			else if
			(
				value == "MICROSECOND_LEVEL_TIMESTAMP"
			)
			{
				return
					TimeFormat
						::MICROSECOND_LEVEL_TIMESTAMP;
			}
			else if
			(
				value == "FULL_TIMESTAMP"
			)
			{
				return
					TimeFormat
						::FULL_TIMESTAMP;
			}	
			else if
			(
				value == "FULL_DASHED_TIMESTAMP"
			)
			{
				return
					TimeFormat
						::FULL_DASHED_TIMESTAMP;
			}
			else if
			(
				value == "HOUR_12"
			)
			{
				return
					TimeFormat
						::HOUR_12;
			}	
			else if
			(
				value == "HOUR_24"
			)
			{
				return
					TimeFormat
						::HOUR_24;
			}
			else if
			(
				value == "MILLISECOND_MICROSECOND_NANOSECOND"
			)
			{
				return
					TimeFormat
						::MILLISECOND_MICROSECOND_NANOSECOND;
			}	
			else if
			(
				value == "DATE_DASHED"
			)
			{
				return
					TimeFormat
						::DATE_DASHED;
			}
			else if
			(
				value == "DATE_MDY_SLASHED"
			)
			{
				return
					TimeFormat
						::DATE_MDY_SLASHED;
			}	
			else if
			(
				value == "DATE_DMY_SLASHED"
			)
			{
				return
					TimeFormat
						::DATE_DMY_SLASHED;
			}
			else if
			(
				value == "DATE_DMY_SPACED"
			)
			{
				return
					TimeFormat
						::DATE_DMY_SPACED;
			}
			else if
			(
				value == "DATE_VERBOSE"
			)
			{
				return
					TimeFormat
						::DATE_VERBOSE;
			}
			else if
			(
				value == "NONE"
			)
			{
				return
					TimeFormat
						::NONE;
			}
			else
			{
				return
					TimeFormat
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
				TimeFormat::NONE
			);			
        }
	}

	TimeFormat
		TimeFormatEnumManager
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

