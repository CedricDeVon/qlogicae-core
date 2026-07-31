#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextEncodingEnumManager \
	)

#include "../includes/text_encoding_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    TextEncodingEnumManager
		::TextEncodingEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextEncodingEnumManagerConfigurations>()
	{
		
	}

	std::string
		TextEncodingEnumManager
			::convert_enum_to_string(
				const TextEncoding&
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
				case (TextEncoding::BASE16):
				{
					return
						"BASE16";
				}
				case (TextEncoding::BASE32):
				{
					return
						"BASE32";
				}
				case (TextEncoding::BASE64):
				{
					return
						"BASE64";
				}
				case (TextEncoding::NONE):
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
		TextEncodingEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	TextEncoding
		TextEncodingEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				TextEncoding::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			if
			(
				value == "BASE16"
			)
			{
				return
					TextEncoding
						::BASE16;
			}
			else if
			(
				value == "BASE32"
			)
			{
				return
					TextEncoding
						::BASE32;
			}
			else if
			(
				value == "BASE64"
			)
			{
				return
					TextEncoding
						::BASE64;
			}			
			else if
			(
				value == "NONE"
			)
			{
				return
					TextEncoding
						::NONE;
			}
			else
			{
				return
					TextEncoding
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
				TextEncoding::NONE
			);			
        }
	}

	TextEncoding
		TextEncodingEnumManager
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

