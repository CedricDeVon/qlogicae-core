#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EmailBodyEnumManager \
	)

#include "../includes/email_body_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	EmailBodyEnumManager
		::EmailBodyEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<EmailBodyEnumManagerConfigurations>()
    {
        
    }

	std::string
		EmailBodyEnumManager
			::convert_enum_to_string(
				const EmailBody&
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
				case (EmailBody::HTML):
				{
					return
						"HTML";
				}
				case (EmailBody::PLAIN):
				{
					return
						"PLAIN";
				}
				case (EmailBody::NONE):
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
		EmailBodyEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	EmailBody
		EmailBodyEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				EmailBody::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			if
			(
				value == "HTML"
			)
			{
				return
					EmailBody
						::HTML;
			}
			else if
			(
				value == "PLAIN"
			)
			{
				return
					EmailBody
						::PLAIN;
			}
			else if
			(
				value == "NONE"
			)
			{
				return
					EmailBody
						::NONE;
			}
			else
			{
				return
					EmailBody
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
				EmailBody::NONE
			);			
        }
	}

	EmailBody
		EmailBodyEnumManager
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
