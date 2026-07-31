#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CharacterDomainEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	struct CharacterDomainParam
	{
		CharacterDomain domain;
		std::string expected_string;
	};

	class CharacterDomainEnumManagerTest: public ::testing::Test
	{
	public:
		CharacterDomainEnumManager manager;

		std::string get_value_thread_safe(const CharacterDomain& domain)
		{
			return manager.convert_enum_to_string(domain);
		}

		CharacterDomain convert_string_thread_safe(const std::string& value)
		{
			return manager.convert_string_to_enum(value);
		}
	};

	class CharacterDomainEnumManagerParameterizedTest:
		public CharacterDomainEnumManagerTest,
		public ::testing::WithParamInterface<CharacterDomainParam>
	{
	};

	const CharacterDomainParam character_domain_params[] =
	{
		{CharacterDomain::BINARY,"BINARY"},
		{CharacterDomain::OCTAL,"OCTAL"},
		{CharacterDomain::NUMERIC,"NUMERIC"},
		{CharacterDomain::LOWERCASE_ALPHABETIC,"LOWERCASE_ALPHABETIC"},
		{CharacterDomain::UPPERCASE_ALPHABETIC,"UPPERCASE_ALPHABETIC"},
		{CharacterDomain::ALPHABETIC,"ALPHABETIC"},
		{CharacterDomain::ALPHANUMERIC,"ALPHANUMERIC"},
		{CharacterDomain::ALPHANUMERIC_LOWERCASE,"ALPHANUMERIC_LOWERCASE"},
		{CharacterDomain::ALPHANUMERIC_UPPERCASE,"ALPHANUMERIC_UPPERCASE"},
		{CharacterDomain::ALPHANUMERIC_UNDERSCORE,"ALPHANUMERIC_UNDERSCORE"},
		{CharacterDomain::HEX_LOWERCASE,"HEX_LOWERCASE"},
		{CharacterDomain::HEX_UPPERCASE,"HEX_UPPERCASE"},
		{CharacterDomain::BASE32_RFC4648,"BASE32_RFC4648"},
		{CharacterDomain::BASE32_CROCKFORD,"BASE32_CROCKFORD"},
		{CharacterDomain::BASE58_BITCOIN,"BASE58_BITCOIN"},
		{CharacterDomain::BASE62,"BASE62"},
		{CharacterDomain::BASE64_RFC4648,"BASE64_RFC4648"},
		{CharacterDomain::BASE64_URL,"BASE64_URL"},
		{CharacterDomain::ASCII,"ASCII"},
		{CharacterDomain::ASCII_PRINTABLE,"ASCII_PRINTABLE"},
		{CharacterDomain::ASCII_VISIBLE,"ASCII_VISIBLE"},
		{CharacterDomain::ASCII_NON_WHITESPACE_PRINTABLE,"ASCII_NON_WHITESPACE_PRINTABLE"},
		{CharacterDomain::PUNCTUATION,"PUNCTUATION"},
		{CharacterDomain::SYMBOLS,"SYMBOLS"},
		{CharacterDomain::WHITESPACE,"WHITESPACE"},
		{CharacterDomain::CONTROL,"CONTROL"},
		{CharacterDomain::HIGH_ENTROPY_PRINTABLE,"HIGH_ENTROPY_PRINTABLE"},
		{CharacterDomain::HIGH_ENTROPY_ALPHANUMERIC,"HIGH_ENTROPY_ALPHANUMERIC"},
		{CharacterDomain::HIGH_ENTROPY_ASCII_VISIBLE,"HIGH_ENTROPY_ASCII_VISIBLE"},
		{CharacterDomain::HUMAN_READABLE,"HUMAN_READABLE"},
		{CharacterDomain::PASSWORD_SAFE,"PASSWORD_SAFE"},
		{CharacterDomain::PIN_CODE,"PIN_CODE"},
		{CharacterDomain::SLUG_SAFE,"SLUG_SAFE"},
		{CharacterDomain::URL_SAFE_RFC3986,"URL_SAFE_RFC3986"},
		{CharacterDomain::FILE_NAME_SAFE,"FILE_NAME_SAFE"},
		{CharacterDomain::PATH_SEGMENT_SAFE,"PATH_SEGMENT_SAFE"},
		{CharacterDomain::JSON_SAFE,"JSON_SAFE"},
		{CharacterDomain::XML_SAFE,"XML_SAFE"},
		{CharacterDomain::SHELL_SAFE,"SHELL_SAFE"},
		{CharacterDomain::FUZZ_PRINTABLE,"FUZZ_PRINTABLE"},
		{CharacterDomain::FUZZ_ASCII,"FUZZ_ASCII"},
		{CharacterDomain::EDGE_CASE_ASCII,"EDGE_CASE_ASCII"},
		{CharacterDomain::MIXED_CASE_STRESS,"MIXED_CASE_STRESS"},
		{CharacterDomain::EXTENDED_ASCII,"EXTENDED_ASCII"},
		{CharacterDomain::CUSTOM,"CUSTOM"},
		{CharacterDomain::NONE,"NONE"}
	};
}

#endif
