#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextEncodingEnumManager \
	)

#include "../includes/text_encoding_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(TextEncodingEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		TextEncoding result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, TextEncoding::NONE);
	}

	TEST_F(TextEncodingEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		TextEncodingEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(TextEncoding::BASE16);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(TextEncodingEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		TextEncodingEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		TextEncoding result = manager.convert_string_to_enum("BASE16");
		EXPECT_EQ(result, TextEncoding::NONE);
	}

	TEST_F(TextEncodingEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		TextEncodingEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(TextEncoding::BASE32);
		EXPECT_EQ(converted, "BASE32");

		TextEncoding result = manager.convert_string_to_enum("BASE32");
		EXPECT_EQ(result, TextEncoding::BASE32);
	}

	TEST_F(TextEncodingEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public TextEncodingEnumManager
		{
		public:
			std::string convert_enum_to_string(const TextEncoding&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(TextEncoding::BASE32), std::runtime_error);
	}

	TEST_F(TextEncodingEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		TextEncodingEnumManagerConfigurations configurations;
		configurations.type = TextEncoding::BASE16;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
			{
				return manager.convert_enum_to_string(TextEncoding::BASE16);
			});

		EXPECT_EQ(future_result.get(), "BASE16");
	}

	TEST_F(TextEncodingEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
						std::string converted = manager.convert_enum_to_string(TextEncoding::BASE32);
						TextEncoding result = manager.convert_string_to_enum(converted);
						if (result == TextEncoding::BASE32)
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

	TEST_F(TextEncodingEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		TextEncodingEnumManager& first_instance = SingletonManager::get_singleton<TextEncodingEnumManager>();
		TextEncodingEnumManager& second_instance = SingletonManager::get_singleton<TextEncodingEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		TextEncodingEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("BASE16", TextEncoding::BASE16),
			std::make_pair("BASE32", TextEncoding::BASE32),
			std::make_pair("BASE64", TextEncoding::BASE64),
			std::make_pair("NONE", TextEncoding::NONE),
			std::make_pair("", TextEncoding::NONE),
			std::make_pair("INVALID", TextEncoding::NONE)
		)
	);

	TEST_P(TextEncodingEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		TextEncoding expected = param.second;

		TextEncoding result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		TextEncodingEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			TextEncoding::BASE16,
			TextEncoding::BASE32,
			TextEncoding::BASE64,
			TextEncoding::NONE
		)
	);

	TEST_P(TextEncodingEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		TextEncoding input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case TextEncoding::BASE16: EXPECT_EQ(result, "BASE16"); break;
			case TextEncoding::BASE32: EXPECT_EQ(result, "BASE32"); break;
			case TextEncoding::BASE64: EXPECT_EQ(result, "BASE64"); break;
			case TextEncoding::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
