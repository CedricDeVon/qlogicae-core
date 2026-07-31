#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogMediumEnumManager \
	)

#include "../includes/log_medium_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	LogMediumEnumManager
		::LogMediumEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<LogMediumEnumManagerConfigurations>()
    {
        
    }

	std::string
		LogMediumEnumManager
			::convert_enum_to_string(
				const LogMedium&
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
				case (LogMedium::ALL):
				{
					return
						"ALL";
				}
				case (LogMedium::FILE):
				{
					return
						"FILE";
				}
				case (LogMedium::CONSOLE):
				{
					return
						"CONSOLE";
				}
				case (LogMedium::NONE):
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
		LogMediumEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	LogMedium
		LogMediumEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				LogMedium::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);				

			if
			(
				value == "ALL"
			)
			{
				return
					LogMedium
						::ALL;
			}
			else if
			(
				value == "FILE"
			)
			{
				return
					LogMedium
						::FILE;
			}
			else if
			(
				value == "CONSOLE"
			)
			{
				return
					LogMedium
						::CONSOLE;
			}			
			else if
			(
				value == "NONE"
			)
			{
				return
					LogMedium
						::NONE;
			}
			else
			{
				return
					LogMedium
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
				LogMedium::NONE
			);
        }
	}

	LogMedium
		LogMediumEnumManager
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

