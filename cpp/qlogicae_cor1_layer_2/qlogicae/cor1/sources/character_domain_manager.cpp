#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CharacterDomainManager \
	)

#include "../includes/character_domain_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	CharacterDomainManager
		::CharacterDomainManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<CharacterDomainManagerConfigurations>()
    {
		construct();
    }
	
	CharacterDomainManager
		::~CharacterDomainManager()
	{
		destruct();
	}

    bool
        CharacterDomainManager
			::construct()
    {
        try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

    bool
        CharacterDomainManager
			::destruct()
    {
        try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

	std::string
		CharacterDomainManager
			::get_value(
				const CharacterDomain&
					character_domain
			)
	{		
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			switch (character_domain)
			{
				case CharacterDomain::BINARY: return "01";
				case CharacterDomain::OCTAL: return "01234567";
				case CharacterDomain::NUMERIC: return "0123456789";
				case CharacterDomain::LOWERCASE_ALPHABETIC: return "abcdefghijklmnopqrstuvwxyz";
				case CharacterDomain::UPPERCASE_ALPHABETIC: return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
				case CharacterDomain::ALPHABETIC: return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
				case CharacterDomain::ALPHANUMERIC: return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
				case CharacterDomain::ALPHANUMERIC_LOWERCASE: return "abcdefghijklmnopqrstuvwxyz0123456789";
				case CharacterDomain::ALPHANUMERIC_UPPERCASE: return "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
				case CharacterDomain::ALPHANUMERIC_UNDERSCORE: return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
				case CharacterDomain::HEX_LOWERCASE: return "0123456789abcdef";
				case CharacterDomain::HEX_UPPERCASE: return "0123456789ABCDEF";
				case CharacterDomain::BASE32_RFC4648: return "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
				case CharacterDomain::BASE32_CROCKFORD: return "0123456789ABCDEFGHJKMNPQRSTVWXYZ";
				case CharacterDomain::BASE58_BITCOIN: return "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
				case CharacterDomain::BASE62: return "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
				case CharacterDomain::BASE64_RFC4648: return "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
				case CharacterDomain::BASE64_URL: return "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
				case CharacterDomain::ASCII: return
					"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
					"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
					" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7F";
				case CharacterDomain::ASCII_PRINTABLE: return
					" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
				case CharacterDomain::ASCII_VISIBLE: return
					"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
				case CharacterDomain::ASCII_NON_WHITESPACE_PRINTABLE: return
					"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
				case CharacterDomain::PUNCTUATION: return "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
				case CharacterDomain::SYMBOLS: return "$%&*+-/<=>^_`|~";
				case CharacterDomain::WHITESPACE: return " \t\n\r\v\f";
				case CharacterDomain::CONTROL: return
					"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
					"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x7F";
				case CharacterDomain::HIGH_ENTROPY_PRINTABLE: return
					"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+[]{}|;:,.<>?/~";
				case CharacterDomain::HIGH_ENTROPY_ALPHANUMERIC: return
					"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+";
				case CharacterDomain::HIGH_ENTROPY_ASCII_VISIBLE: return
					"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!@#$%^&*()-_=+";
				case CharacterDomain::HUMAN_READABLE: return "ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz23456789";
				case CharacterDomain::PASSWORD_SAFE: return
					" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
				case CharacterDomain::PIN_CODE: return "0123456789";
				case CharacterDomain::SLUG_SAFE: return "abcdefghijklmnopqrstuvwxyz-";
				case CharacterDomain::URL_SAFE_RFC3986: return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-._~";
				case CharacterDomain::FILE_NAME_SAFE: return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-";
				case CharacterDomain::PATH_SEGMENT_SAFE: return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-";
				case CharacterDomain::JSON_SAFE: return
					" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
				case CharacterDomain::XML_SAFE: return
					" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
				case CharacterDomain::SHELL_SAFE: return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@%+=:,./-";
				case CharacterDomain::FUZZ_PRINTABLE: return
					" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
				case CharacterDomain::FUZZ_ASCII: return
					"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
					"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
					" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7F";
				case CharacterDomain::EDGE_CASE_ASCII: return "\x00\x01\x7F";
				case CharacterDomain::MIXED_CASE_STRESS: return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
				case CharacterDomain::EXTENDED_ASCII: return
					"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
					"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
					" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
					"\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F"
					"\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F"
					"\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF"
					"\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF"
					"\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF"
					"\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF"
					"\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF"
					"\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";
				case CharacterDomain::CUSTOM:
				case CharacterDomain::NONE:
				default: return "";
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }		
	}

	std::string
		CharacterDomainManager
			::get_value()
	{		
		return
			get_value(
				configurations
					.type
			);
	}
}

#endif
