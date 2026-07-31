#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogLevelEnumManager \
	)

#include "../includes/log_level_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	LogLevelEnumManager
		::LogLevelEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<LogLevelEnumManagerConfigurations>()
    {
        
    }

	std::string
		LogLevelEnumManager
			::convert_enum_to_string(
				const LogLevel&
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
				case (LogLevel::ALL):
				{
					return
						"ALL";
				}
				case (LogLevel::INFO):
				{
					return
						"INFO";
				}
				case (LogLevel::DEBUG):
				{
					return
						"DEBUG";
				}
				case (LogLevel::WARNING):
				{
					return
						"WARNING";
				}
				case (LogLevel::SUCCESS):
				{
					return
						"SUCCESS";
				}
				case (LogLevel::CRITICAL):
				{
					return
						"CRITICAL";
				}			
				case (LogLevel::ERROR_TYPE):
				{
					return
						"ERROR_TYPE";
				}
				case (LogLevel::HIGHLIGHTED_INFO):
				{
					return
						"HIGHLIGHTED_INFO";
				}
				case (LogLevel::NONE):
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
		LogLevelEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	LogLevel
		LogLevelEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				LogLevel::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			if
			(
				value == "ALL"
			)
			{
				return
					LogLevel
						::ALL;
			}
			else if
			(
				value == "INFO"
			)
			{
				return
					LogLevel
						::INFO;
			}			
			else if
			(
				value == "DEBUG"
			)
			{
				return
					LogLevel
						::DEBUG;
			}
			else if
			(
				value == "WARNING"
			)
			{
				return
					LogLevel
						::WARNING;
			}			
			else if
			(
				value == "SUCCESS"
			)
			{
				return
					LogLevel
						::SUCCESS;
			}
			else if
			(
				value == "CRITICAL"
			)
			{
				return
					LogLevel
						::CRITICAL;
			}			
			else if
			(
				value == "ERROR_TYPE"
			)
			{
				return
					LogLevel
						::ERROR_TYPE;
			}
			else if
			(
				value == "HIGHLIGHTED_INFO"
			)
			{
				return
					LogLevel
						::HIGHLIGHTED_INFO;
			}			
			else
			{
				return
					LogLevel
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
				LogLevel::NONE
			);
        }
	}

	LogLevel
		LogLevelEnumManager
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

