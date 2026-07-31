#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CharacterDomainEnumManager \
	)

#include "../includes/character_domain_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{    
    TEST_F(CharacterDomainEnumManagerTest, Should_ConstructSuccessfully_When_RuntimeEnabled)
    {
        ASSERT_TRUE(manager.construct());
    }

    TEST_F(CharacterDomainEnumManagerTest, Should_DestructSuccessfully_When_RuntimeEnabled)
    {
        ASSERT_TRUE(manager.destruct());
    }

    TEST_F(CharacterDomainEnumManagerTest,
        Should_HandleCustomAndNone_When_CharacterDomainIsCustomOrNone)
    {
        ASSERT_EQ(manager.convert_enum_to_string(CharacterDomain::CUSTOM), "CUSTOM");
        ASSERT_EQ(manager.convert_enum_to_string(CharacterDomain::NONE), "NONE");
    }

    TEST_F(CharacterDomainEnumManagerTest,
        Should_HandleEmptyString_When_ConvertStringToEnum)
    {
        ASSERT_EQ(convert_string_thread_safe(""), CharacterDomain::NONE);
    }

    TEST_F(CharacterDomainEnumManagerTest,
        Should_HandleInvalidCharacters_When_ConvertStringToEnum)
    {
        ASSERT_EQ(convert_string_thread_safe("@@@INVALID@@@"), CharacterDomain::NONE);
    }

	TEST_F(CharacterDomainEnumManagerTest, Should_ReturnNone_When_RuntimeExecutionDisabled)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled = false;
		for (uint8_t i = 0; i <= static_cast<uint8_t>(CharacterDomain::NONE); ++i)
		{
			CharacterDomain domain = static_cast<CharacterDomain>(i);
			ASSERT_EQ(manager.convert_enum_to_string(domain), "NONE");
			std::string str = manager.convert_enum_to_string(domain);
			ASSERT_EQ(manager.convert_string_to_enum(str), CharacterDomain::NONE);
		}
	}

	TEST_F(CharacterDomainEnumManagerTest, Should_HandleCaseMismatch_When_ConvertStringToEnum)
	{
		ASSERT_EQ(convert_string_thread_safe("binary"), CharacterDomain::NONE);
		ASSERT_EQ(convert_string_thread_safe("Octal"), CharacterDomain::NONE);
		ASSERT_EQ(convert_string_thread_safe("nUmErIc"), CharacterDomain::NONE);
	}

	TEST_F(CharacterDomainEnumManagerTest, Should_HandlePartialString_When_ConvertStringToEnum)
	{
		ASSERT_EQ(convert_string_thread_safe("BIN"), CharacterDomain::NONE);
		ASSERT_EQ(convert_string_thread_safe("ALPHA"), CharacterDomain::NONE);
		ASSERT_EQ(convert_string_thread_safe("HEX_LOWER"), CharacterDomain::NONE);
	}

	TEST_F(CharacterDomainEnumManagerTest, Should_HandleConcurrencyForConvertStringToEnum)
	{
		std::vector<std::future<CharacterDomain>> futures;
		const std::vector<std::string> strings = { "BINARY", "OCTAL", "NUMERIC", "LOWERCASE_ALPHABETIC",
			"UPPERCASE_ALPHABETIC", "ALPHABETIC", "ALPHANUMERIC" };

		for (const auto& str : strings)
		{
			futures.emplace_back(std::async(std::launch::async,
				[this, &str]() { return convert_string_thread_safe(str); }));
		}

		for (size_t i = 0; i < futures.size(); ++i)
		{
			ASSERT_EQ(futures[i].get(), convert_string_thread_safe(strings[i]));
		}
	}

	TEST_F(CharacterDomainEnumManagerTest,
		Should_HandleStringToEnumConcurrency)
	{
		const std::vector<std::string> enum_strings = {
			"BINARY","OCTAL","NUMERIC","LOWERCASE_ALPHABETIC","UPPERCASE_ALPHABETIC",
			"ALPHABETIC","ALPHANUMERIC","ALPHANUMERIC_LOWERCASE","ALPHANUMERIC_UPPERCASE",
			"ALPHANUMERIC_UNDERSCORE","HEX_LOWERCASE","HEX_UPPERCASE","BASE32_RFC4648",
			"BASE32_CROCKFORD","BASE58_BITCOIN","BASE62","BASE64_RFC4648","BASE64_URL",
			"ASCII","ASCII_PRINTABLE","ASCII_VISIBLE","ASCII_NON_WHITESPACE_PRINTABLE",
			"PUNCTUATION","SYMBOLS","WHITESPACE","CONTROL","HIGH_ENTROPY_PRINTABLE",
			"HIGH_ENTROPY_ALPHANUMERIC","HIGH_ENTROPY_ASCII_VISIBLE","HUMAN_READABLE",
			"PASSWORD_SAFE","PIN_CODE","SLUG_SAFE","URL_SAFE_RFC3986","FILE_NAME_SAFE",
			"PATH_SEGMENT_SAFE","JSON_SAFE","XML_SAFE","SHELL_SAFE","FUZZ_PRINTABLE",
			"FUZZ_ASCII","EDGE_CASE_ASCII","MIXED_CASE_STRESS","EXTENDED_ASCII","CUSTOM","NONE"
		};

		std::vector<std::future<CharacterDomain>> futures;
		for (const auto& str : enum_strings)
		{
			futures.emplace_back(std::async(std::launch::async,
				[this, &str]() { return convert_string_thread_safe(str); }));
		}

		for (size_t i = 0; i < futures.size(); ++i)
		{
			CharacterDomain result = futures[i].get();
			ASSERT_EQ(result, convert_string_thread_safe(enum_strings[i]));
		}
	}

	TEST_F(CharacterDomainEnumManagerTest,
		Should_HandleExceptionsInConvertEnumToString)
	{
		struct FaultyManager : CharacterDomainEnumManager
		{
			std::string convert_enum_to_string(const CharacterDomain&)
			{
				throw std::runtime_error("Simulated exception");
			}
		} faulty;

		try
		{
			faulty.convert_enum_to_string(CharacterDomain::BINARY);
		}
		catch (const std::exception& e)
		{
			ASSERT_STREQ(e.what(), "Simulated exception");
		}
	}

	TEST_F(CharacterDomainEnumManagerTest,
		Should_HandleExceptionsInConvertStringToEnum)
	{
		struct FaultyManager : CharacterDomainEnumManager
		{
			CharacterDomain convert_string_to_enum(const std::string&)
			{
				throw std::runtime_error("Simulated exception");
			}
		} faulty;

		try
		{
			faulty.convert_string_to_enum("BINARY");
		}
		catch (const std::exception& e)
		{
			ASSERT_STREQ(e.what(), "Simulated exception");
		}
	}

    TEST_P(CharacterDomainEnumManagerParameterizedTest,
        Should_ReturnCorrectString_When_CharacterDomainSpecified)
    {
        const auto& param = GetParam();
        ASSERT_EQ(manager.convert_enum_to_string(param.domain), param.expected_string);
    }

    TEST_P(CharacterDomainEnumManagerParameterizedTest,
        Should_ConvertEnumToStringAndBack_When_ValidEnum)
    {
        const auto& param = GetParam();
        std::string str_value = manager.convert_enum_to_string(param.domain);
        CharacterDomain enum_value = manager.convert_string_to_enum(str_value);
        ASSERT_EQ(enum_value, param.domain);
    }

    TEST_P(CharacterDomainEnumManagerParameterizedTest,
        Should_HandleAsyncStress_When_ConcurrentAsyncCalls)
    {
        const auto& param = GetParam();
        std::vector<std::future<std::string>> futures;
        for (size_t i = 0; i < 50; ++i)
        {
            futures.emplace_back(std::async(std::launch::async,
                [this, &param]() { return get_value_thread_safe(param.domain); }));
        }
        for (auto& future : futures)
        {
            ASSERT_EQ(future.get(), param.expected_string);
        }
    }

	TEST_P(CharacterDomainEnumManagerParameterizedTest,
		Should_HandleMultithreadedStress_When_ConcurrentThreadCalls)
	{
		const auto param = GetParam();
		std::vector<std::thread> threads;
		std::vector<std::string> results(50);

		for (size_t i = 0; i < 50; ++i)
		{
			threads.emplace_back([this, &results, param, i]()
				{
					results[i] = get_value_thread_safe(param.domain);
				});
		}

		for (auto& thread : threads)
			thread.join();

		for (const auto& result : results)
			ASSERT_EQ(result, param.expected_string);
	}

	INSTANTIATE_TEST_CASE_P(
		CharacterDomainEnumManagerTests,
		CharacterDomainEnumManagerParameterizedTest,
		::testing::ValuesIn(character_domain_params));

}

#endif
