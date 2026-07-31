#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsEnvironmentVariableEnumManager \
	)

#include "../includes/windows_environment_variable_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	WindowsEnvironmentVariableEnumManager
		::WindowsEnvironmentVariableEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<WindowsEnvironmentVariableEnumManagerConfigurations>()
    {
        
    }

	std::string
		WindowsEnvironmentVariableEnumManager
			::convert_enum_to_string(
				const WindowsEnvironmentVariable&
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
				case (WindowsEnvironmentVariable::USER):
				{
					return
						"USER";
				}
				case (WindowsEnvironmentVariable::SYSTEM):
				{
					return
						"SYSTEM";
				}
				case (WindowsEnvironmentVariable::NONE):
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
		WindowsEnvironmentVariableEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	WindowsEnvironmentVariable
		WindowsEnvironmentVariableEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				WindowsEnvironmentVariable::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			if
			(
				value == "USER"
			)
			{
				return
					WindowsEnvironmentVariable
						::USER;
			}
			else if
			(
				value == "SYSTEM"
			)
			{
				return
					WindowsEnvironmentVariable
						::SYSTEM;
			}		
			else if
			(
				value == "NONE"
			)
			{
				return
					WindowsEnvironmentVariable
						::NONE;
			}
			else
			{
				return
					WindowsEnvironmentVariable
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
				WindowsEnvironmentVariable::NONE
			);			
        }
	}

	WindowsEnvironmentVariable
		WindowsEnvironmentVariableEnumManager
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

