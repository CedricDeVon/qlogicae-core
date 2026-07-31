#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CharacterDomainEnumManager \
	)

#include "../includes/character_domain_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	CharacterDomainEnumManager
		::CharacterDomainEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<CharacterDomainEnumManagerConfigurations>()
    {
		
    }

	std::string
		CharacterDomainEnumManager
			::convert_enum_to_string(
				const CharacterDomain&
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
				case (CharacterDomain::BINARY):
				{
					return "BINARY";
				}
				case (CharacterDomain::OCTAL):
				{
					return "OCTAL";
				}
				case (CharacterDomain::NUMERIC):
				{
					return "NUMERIC";
				}
				case (CharacterDomain::LOWERCASE_ALPHABETIC):
				{
					return "LOWERCASE_ALPHABETIC";
				}
				case (CharacterDomain::UPPERCASE_ALPHABETIC):
				{
					return "UPPERCASE_ALPHABETIC";
				}
				case (CharacterDomain::ALPHABETIC):
				{
					return "ALPHABETIC";
				}
				case (CharacterDomain::ALPHANUMERIC):
				{
					return "ALPHANUMERIC";
				}
				case (CharacterDomain::ALPHANUMERIC_LOWERCASE):
				{
					return "ALPHANUMERIC_LOWERCASE";
				}
				case (CharacterDomain::ALPHANUMERIC_UPPERCASE):
				{
					return "ALPHANUMERIC_UPPERCASE";
				}
				case (CharacterDomain::ALPHANUMERIC_UNDERSCORE):
				{
					return "ALPHANUMERIC_UNDERSCORE";
				}
				case (CharacterDomain::HEX_LOWERCASE):
				{
					return "HEX_LOWERCASE";
				}
				case (CharacterDomain::HEX_UPPERCASE):
				{
					return "HEX_UPPERCASE";
				}
				case (CharacterDomain::BASE32_RFC4648):
				{
					return "BASE32_RFC4648";
				}
				case (CharacterDomain::BASE32_CROCKFORD):
				{
					return "BASE32_CROCKFORD";
				}
				case (CharacterDomain::BASE58_BITCOIN):
				{
					return "BASE58_BITCOIN";
				}
				case (CharacterDomain::BASE62):
				{
					return "BASE62";
				}
				case (CharacterDomain::BASE64_RFC4648):
				{
					return "BASE64_RFC4648";
				}
				case (CharacterDomain::BASE64_URL):
				{
					return "BASE64_URL";
				}
				case (CharacterDomain::ASCII):
				{
					return "ASCII";
				}
				case (CharacterDomain::ASCII_PRINTABLE):
				{
					return "ASCII_PRINTABLE";
				}
				case (CharacterDomain::ASCII_VISIBLE):
				{
					return "ASCII_VISIBLE";
				}
				case (CharacterDomain::ASCII_NON_WHITESPACE_PRINTABLE):
				{
					return "ASCII_NON_WHITESPACE_PRINTABLE";
				}
				case (CharacterDomain::PUNCTUATION):
				{
					return "PUNCTUATION";
				}
				case (CharacterDomain::SYMBOLS):
				{
					return "SYMBOLS";
				}
				case (CharacterDomain::WHITESPACE):
				{
					return "WHITESPACE";
				}
				case (CharacterDomain::CONTROL):
				{
					return "CONTROL";
				}
				case (CharacterDomain::HIGH_ENTROPY_PRINTABLE):
				{
					return "HIGH_ENTROPY_PRINTABLE";
				}
				case (CharacterDomain::HIGH_ENTROPY_ALPHANUMERIC):
				{
					return "HIGH_ENTROPY_ALPHANUMERIC";
				}
				case (CharacterDomain::HIGH_ENTROPY_ASCII_VISIBLE):
				{
					return "HIGH_ENTROPY_ASCII_VISIBLE";
				}
				case (CharacterDomain::HUMAN_READABLE):
				{
					return "HUMAN_READABLE";
				}
				case (CharacterDomain::PASSWORD_SAFE):
				{
					return "PASSWORD_SAFE";
				}
				case (CharacterDomain::PIN_CODE):
				{
					return "PIN_CODE";
				}
				case (CharacterDomain::SLUG_SAFE):
				{
					return "SLUG_SAFE";
				}
				case (CharacterDomain::URL_SAFE_RFC3986):
				{
					return "URL_SAFE_RFC3986";
				}
				case (CharacterDomain::FILE_NAME_SAFE):
				{
					return "FILE_NAME_SAFE";
				}
				case (CharacterDomain::PATH_SEGMENT_SAFE):
				{
					return "PATH_SEGMENT_SAFE";
				}
				case (CharacterDomain::JSON_SAFE):
				{
					return "JSON_SAFE";
				}
				case (CharacterDomain::XML_SAFE):
				{
					return "XML_SAFE";
				}
				case (CharacterDomain::SHELL_SAFE):
				{
					return "SHELL_SAFE";
				}
				case (CharacterDomain::FUZZ_PRINTABLE):
				{
					return "FUZZ_PRINTABLE";
				}
				case (CharacterDomain::FUZZ_ASCII):
				{
					return "FUZZ_ASCII";
				}
				case (CharacterDomain::EDGE_CASE_ASCII):
				{
					return "EDGE_CASE_ASCII";
				}
				case (CharacterDomain::MIXED_CASE_STRESS):
				{
					return "MIXED_CASE_STRESS";
				}
				case (CharacterDomain::EXTENDED_ASCII):
				{
					return "EXTENDED_ASCII";
				}
				case (CharacterDomain::CUSTOM):
				{
					return "CUSTOM";
				}
				case (CharacterDomain::NONE):
				{
					return "NONE";
				}
				default:
				{
					return "NONE";
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
		CharacterDomainEnumManager
		::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	CharacterDomain
		CharacterDomainEnumManager
			::convert_string_to_enum(
				const std::string&
				value
			)
	{
		try
		{			
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				CharacterDomain::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			if (value == "BINARY")
			{
				return
					CharacterDomain::BINARY;
			}
			else if (value == "OCTAL")
			{
				return
					CharacterDomain::OCTAL;
			}
			else if (value == "NUMERIC")
			{
				return
					CharacterDomain::NUMERIC;
			}
			else if (value == "LOWERCASE_ALPHABETIC")
			{
				return
					CharacterDomain::LOWERCASE_ALPHABETIC;
			}
			else if (value == "UPPERCASE_ALPHABETIC")
			{
				return
					CharacterDomain::UPPERCASE_ALPHABETIC;
			}
			else if (value == "ALPHABETIC")
			{
				return
					CharacterDomain::ALPHABETIC;
			}
			else if (value == "ALPHANUMERIC")
			{
				return
					CharacterDomain::ALPHANUMERIC;
			}
			else if (value == "ALPHANUMERIC_LOWERCASE")
			{
				return
					CharacterDomain::ALPHANUMERIC_LOWERCASE;
			}
			else if (value == "ALPHANUMERIC_UPPERCASE")
			{
				return
					CharacterDomain::ALPHANUMERIC_UPPERCASE;
			}
			else if (value == "ALPHANUMERIC_UNDERSCORE")
			{
				return
					CharacterDomain::ALPHANUMERIC_UNDERSCORE;
			}
			else if (value == "HEX_LOWERCASE")
			{
				return
					CharacterDomain::HEX_LOWERCASE;
			}
			else if (value == "HEX_UPPERCASE")
			{
				return
					CharacterDomain::HEX_UPPERCASE;
			}
			else if (value == "BASE32_RFC4648")
			{
				return
					CharacterDomain::BASE32_RFC4648;
			}
			else if (value == "BASE32_CROCKFORD")
			{
				return
					CharacterDomain::BASE32_CROCKFORD;
			}
			else if (value == "BASE58_BITCOIN")
			{
				return
					CharacterDomain::BASE58_BITCOIN;
			}
			else if (value == "BASE62")
			{
				return
					CharacterDomain::BASE62;
			}
			else if (value == "BASE64_RFC4648")
			{
				return
					CharacterDomain::BASE64_RFC4648;
			}
			else if (value == "BASE64_URL")
			{
				return
					CharacterDomain::BASE64_URL;
			}
			else if (value == "ASCII")
			{
				return
					CharacterDomain::ASCII;
			}
			else if (value == "ASCII_PRINTABLE")
			{
				return
					CharacterDomain::ASCII_PRINTABLE;
			}
			else if (value == "ASCII_VISIBLE")
			{
				return
					CharacterDomain::ASCII_VISIBLE;
			}
			else if (value == "ASCII_NON_WHITESPACE_PRINTABLE")
			{
				return
					CharacterDomain::ASCII_NON_WHITESPACE_PRINTABLE;
			}
			else if (value == "PUNCTUATION")
			{
				return
					CharacterDomain::PUNCTUATION;
			}
			else if (value == "SYMBOLS")
			{
				return
					CharacterDomain::SYMBOLS;
			}
			else if (value == "WHITESPACE")
			{
				return
					CharacterDomain::WHITESPACE;
			}
			else if (value == "CONTROL")
			{
				return
					CharacterDomain::CONTROL;
			}
			else if (value == "HIGH_ENTROPY_PRINTABLE")
			{
				return
					CharacterDomain::HIGH_ENTROPY_PRINTABLE;
			}
			else if (value == "HIGH_ENTROPY_ALPHANUMERIC")
			{
				return
					CharacterDomain::HIGH_ENTROPY_ALPHANUMERIC;
			}
			else if (value == "HIGH_ENTROPY_ASCII_VISIBLE")
			{
				return
					CharacterDomain::HIGH_ENTROPY_ASCII_VISIBLE;
			}
			else if (value == "HUMAN_READABLE")
			{
				return
					CharacterDomain::HUMAN_READABLE;
			}
			else if (value == "PASSWORD_SAFE")
			{
				return
					CharacterDomain::PASSWORD_SAFE;
			}
			else if (value == "PIN_CODE")
			{
				return
					CharacterDomain::PIN_CODE;
			}
			else if (value == "SLUG_SAFE")
			{
				return
					CharacterDomain::SLUG_SAFE;
			}
			else if (value == "URL_SAFE_RFC3986")
			{
				return
					CharacterDomain::URL_SAFE_RFC3986;
			}
			else if (value == "FILE_NAME_SAFE")
			{
				return
					CharacterDomain::FILE_NAME_SAFE;
			}
			else if (value == "PATH_SEGMENT_SAFE")
			{
				return
					CharacterDomain::PATH_SEGMENT_SAFE;
			}
			else if (value == "JSON_SAFE")
			{
				return
					CharacterDomain::JSON_SAFE;
			}
			else if (value == "XML_SAFE")
			{
				return
					CharacterDomain::XML_SAFE;
			}
			else if (value == "SHELL_SAFE")
			{
				return
					CharacterDomain::SHELL_SAFE;
			}
			else if (value == "FUZZ_PRINTABLE")
			{
				return
					CharacterDomain::FUZZ_PRINTABLE;
			}
			else if (value == "FUZZ_ASCII")
			{
				return
					CharacterDomain::FUZZ_ASCII;
			}
			else if (value == "EDGE_CASE_ASCII")
			{
				return
					CharacterDomain::EDGE_CASE_ASCII;
			}
			else if (value == "MIXED_CASE_STRESS")
			{
				return
					CharacterDomain::MIXED_CASE_STRESS;
			}
			else if (value == "EXTENDED_ASCII")
			{
				return
					CharacterDomain::EXTENDED_ASCII;
			}
			else if (value == "CUSTOM")
			{
				return
					CharacterDomain::CUSTOM;
			}
			else if (value == "NONE")
			{
				return
					CharacterDomain::NONE;
					}
			else
			{
				return
					CharacterDomain::NONE;
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				CharacterDomain::NONE
			);
		}
	}

	CharacterDomain
		CharacterDomainEnumManager
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
