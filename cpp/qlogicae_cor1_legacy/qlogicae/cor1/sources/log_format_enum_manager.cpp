#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogFormatEnumManager \
	)

#include "../includes/log_format_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	LogFormatEnumManager
		::LogFormatEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<LogFormatEnumManagerConfigurations>()
    {
        
    }

	std::string
		LogFormatEnumManager
			::convert_enum_to_string(
				const LogFormat&
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
				case (LogFormat::STANDARD):
				{
					return
						"STANDARD";
				}
				case (LogFormat::CUSTOM):
				{
					return
						"CUSTOM";
				}
				case (LogFormat::NONE):
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
		LogFormatEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	LogFormat
		LogFormatEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				LogFormat::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			if
			(
				value == "STANDARD"
			)
			{
				return
					LogFormat
						::STANDARD;
			}	
			else if
			(
				value == "CUSTOM"
			)
			{
				return
					LogFormat
						::CUSTOM;
			}
						
			else if
			(
				value == "NONE"
			)
			{
				return
					LogFormat
						::NONE;
			}
			else
			{
				return
					LogFormat
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
				LogFormat::NONE
			);
        }
	}

	LogFormat
		LogFormatEnumManager
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
