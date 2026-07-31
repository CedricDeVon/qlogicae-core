#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogFormatEnumManager \
	)

#include "../includes/log_format_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(LogFormatEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		LogFormat result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, LogFormat::NONE);
	}

	TEST_F(LogFormatEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		LogFormatEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(LogFormat::STANDARD);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(LogFormatEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		LogFormatEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		LogFormat result = manager.convert_string_to_enum("STANDARD");
		EXPECT_EQ(result, LogFormat::NONE);
	}

	TEST_F(LogFormatEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		LogFormatEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(LogFormat::CUSTOM);
		EXPECT_EQ(converted, "CUSTOM");

		LogFormat result = manager.convert_string_to_enum("CUSTOM");
		EXPECT_EQ(result, LogFormat::CUSTOM);
	}

	TEST_F(LogFormatEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public LogFormatEnumManager
		{
		public:
			std::string convert_enum_to_string(const LogFormat&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(LogFormat::STANDARD), std::runtime_error);
	}

	TEST_F(LogFormatEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		LogFormatEnumManagerConfigurations configurations;
		configurations.type = LogFormat::STANDARD;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(LogFormat::STANDARD);
		});

		EXPECT_EQ(future_result.get(), "STANDARD");
	}

	TEST_F(LogFormatEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(LogFormat::STANDARD);
					LogFormat result = manager.convert_string_to_enum(converted);
					if (result == LogFormat::STANDARD)
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

	TEST_F(LogFormatEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		LogFormatEnumManager& first_instance = SingletonManager::get_singleton<LogFormatEnumManager>();
		LogFormatEnumManager& second_instance = SingletonManager::get_singleton<LogFormatEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		LogFormatEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("CUSTOM", LogFormat::CUSTOM),
			std::make_pair("STANDARD", LogFormat::STANDARD),
			std::make_pair("NONE", LogFormat::NONE),
			std::make_pair("", LogFormat::NONE),
			std::make_pair("INVALID", LogFormat::NONE)
		)
	);

	TEST_P(LogFormatEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		LogFormat expected = param.second;

		LogFormat result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		LogFormatEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			LogFormat::CUSTOM,
			LogFormat::STANDARD,
			LogFormat::NONE
		)
	);

	TEST_P(LogFormatEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		LogFormat input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case LogFormat::CUSTOM: EXPECT_EQ(result, "CUSTOM"); break;
			case LogFormat::STANDARD: EXPECT_EQ(result, "STANDARD"); break;
			case LogFormat::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
