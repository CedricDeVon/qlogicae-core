#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextCaseEnumManager \
	)

#include "../includes/text_case_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(TextCaseEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		TextCase result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, TextCase::NONE);
	}

	TEST_F(TextCaseEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		TextCaseEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(TextCase::LOWERCASE);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(TextCaseEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		TextCaseEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		TextCase result = manager.convert_string_to_enum("LOWERCASE");
		EXPECT_EQ(result, TextCase::NONE);
	}

	TEST_F(TextCaseEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		TextCaseEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(TextCase::UPPERCASE);
		EXPECT_EQ(converted, "UPPERCASE");

		TextCase result = manager.convert_string_to_enum("UPPERCASE");
		EXPECT_EQ(result, TextCase::UPPERCASE);
	}

	TEST_F(TextCaseEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public TextCaseEnumManager
		{
		public:
			std::string convert_enum_to_string(const TextCase&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(TextCase::UPPERCASE), std::runtime_error);
	}

	TEST_F(TextCaseEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		TextCaseEnumManagerConfigurations configurations;
		configurations.type = TextCase::LOWERCASE;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
			{
				return manager.convert_enum_to_string(TextCase::LOWERCASE);
			});

		EXPECT_EQ(future_result.get(), "LOWERCASE");
	}

	TEST_F(TextCaseEnumManagerTest, Should_SupportHighConcurrencyStressTest)
	{
		constexpr int num_threads = 16;
		constexpr int iterations = 10000;

		std::vector<std::thread> threads;
		std::atomic<int> success_count{ 0 };

		for (int i = 0; i < num_threads; ++i)
		{
			threads.emplace_back([&]()
				{
					for (int j = 0; j < iterations; ++j)
					{
						std::string converted = manager.convert_enum_to_string(TextCase::UPPERCASE);
						TextCase result = manager.convert_string_to_enum(converted);
						if (result == TextCase::UPPERCASE)
						{
							success_count++;
						}
					}
				});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		EXPECT_EQ(success_count.load(), num_threads * iterations);
	}

	TEST_F(TextCaseEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		TextCaseEnumManager& first_instance = SingletonManager::get_singleton<TextCaseEnumManager>();
		TextCaseEnumManager& second_instance = SingletonManager::get_singleton<TextCaseEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		TextCaseEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("LOWERCASE", TextCase::LOWERCASE),
			std::make_pair("UPPERCASE", TextCase::UPPERCASE),
			std::make_pair("CAPITALIZE", TextCase::CAPITALIZE),
			std::make_pair("TITLE", TextCase::TITLE),
			std::make_pair("SENTENCE", TextCase::SENTENCE),
			std::make_pair("NONE", TextCase::NONE),
			std::make_pair("", TextCase::NONE),
			std::make_pair("INVALID", TextCase::NONE)
		)
	);

	TEST_P(TextCaseEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		TextCase expected = param.second;

		TextCase result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		TextCaseEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			TextCase::LOWERCASE,
			TextCase::UPPERCASE,
			TextCase::CAPITALIZE,
			TextCase::TITLE,
			TextCase::SENTENCE,
			TextCase::NONE
		)
	);

	TEST_P(TextCaseEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		TextCase input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case TextCase::LOWERCASE: EXPECT_EQ(result, "LOWERCASE"); break;
			case TextCase::UPPERCASE: EXPECT_EQ(result, "UPPERCASE"); break;
			case TextCase::CAPITALIZE: EXPECT_EQ(result, "CAPITALIZE"); break;
			case TextCase::TITLE: EXPECT_EQ(result, "TITLE"); break;
			case TextCase::SENTENCE: EXPECT_EQ(result, "SENTENCE"); break;
			case TextCase::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
