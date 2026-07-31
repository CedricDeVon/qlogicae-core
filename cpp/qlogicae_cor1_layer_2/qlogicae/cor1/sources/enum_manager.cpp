#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EnumManager \
	)

#include "../includes/enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	EnumManager
		::EnumManager() :
			AbstractClass<EnumManagerConfigurations>()
    {
        
    }

	std::string
		EnumManager
			::convert_enum_string(
				const std::string&
					value,
				const TextCase&
					original_text_case,
				const TextCase&
					target_text_case
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				value,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!configurations
					.is_text_case_conversion_enabled ||						
				value
					.empty() ||
				original_text_case == target_text_case
			);	

			return
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextCaseManager>()					
					.convert_text(
						value,
						target_text_case
					);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {	
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				value
			);
        }
	}

	std::string
		EnumManager
			::convert_enum_string(
				const std::string&
					value,
				const TextCase&
					target_text_case
			)
	{
		return
			convert_enum_string(
				value,
				configurations
					.text_case,
				target_text_case				
			);
	}

	std::string
		EnumManager
			::convert_enum_string(
				const std::string&
					value
			)
	{
		return
			convert_enum_string(
				value,
				configurations
					.text_case,
				configurations
					.text_case
			);
	}

	std::string
		EnumManager
			::convert_default_enum_string(
				const std::string&
					value
			)
	{
		return
			convert_enum_string(
				value,
				TextCase
					::NONE,
				configurations
					.text_case
			);
	}

	std::string
		EnumManager
			::get_none_string(
				const TextCase&
					text_case
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

			switch (text_case)
			{
				case (TextCase::UPPERCASE):
				{
					return
						"NONE";
				}
				case (TextCase::LOWERCASE):
				{
					return
						"none";
				}
				case (TextCase::CAPITALIZE):
				{
					return
						"None";
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
		EnumManager
			::get_none_string()
	{
		return
			get_none_string(
				configurations
					.text_case
			);
	}
}

#endif
