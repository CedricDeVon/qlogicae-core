#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogOutputEnumManager \
	)

#include "../includes/log_output_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	LogOutputEnumManager
		::LogOutputEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<LogOutputEnumManagerConfigurations>()
    {
        
    }

	std::string
		LogOutputEnumManager
			::convert_enum_to_string(
				const LogOutput&
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
				case (LogOutput::ALL):
				{
					return
						"ALL";
				}
				case (LogOutput::FOREGROUND):
				{
					return
						"FOREGROUND";
				}
				case (LogOutput::BACKGROUND):
				{
					return
						"BACKGROUND";
				}
				case (LogOutput::NONE):
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
		LogOutputEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	LogOutput
		LogOutputEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				LogOutput::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			if
			(
				value == "ALL"
			)
			{
				return
					LogOutput
						::ALL;
			}
			else if
			(
				value == "FOREGROUND"
			)
			{
				return
					LogOutput
						::FOREGROUND;
			}
			else if
			(
				value == "BACKGROUND"
			)
			{
				return
					LogOutput
						::BACKGROUND;
			}			
			else if
			(
				value == "NONE"
			)
			{
				return
					LogOutput
						::NONE;
			}
			else
			{
				return
					LogOutput
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
				LogOutput::NONE
			);
        }
	}

	LogOutput
		LogOutputEnumManager
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

