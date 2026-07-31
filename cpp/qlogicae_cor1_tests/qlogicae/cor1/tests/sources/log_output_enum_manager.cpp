#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogOutputEnumManager \
	)

#include "../includes/log_output_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	TEST_F(LogOutputEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		LogOutput result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, LogOutput::NONE);
	}

	TEST_F(LogOutputEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		LogOutputEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(LogOutput::BACKGROUND);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(LogOutputEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		LogOutputEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		LogOutput result = manager.convert_string_to_enum("BACKGROUND");
		EXPECT_EQ(result, LogOutput::NONE);
	}

	TEST_F(LogOutputEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		LogOutputEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(LogOutput::FOREGROUND);
		EXPECT_EQ(converted, "FOREGROUND");

		LogOutput result = manager.convert_string_to_enum("FOREGROUND");
		EXPECT_EQ(result, LogOutput::FOREGROUND);
	}

	TEST_F(LogOutputEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public LogOutputEnumManager
		{
		public:
			std::string convert_enum_to_string(const LogOutput&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(LogOutput::ALL), std::runtime_error);
	}

	TEST_F(LogOutputEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		LogOutputEnumManagerConfigurations configurations;
		configurations.type = LogOutput::BACKGROUND;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(LogOutput::BACKGROUND);
		});

		EXPECT_EQ(future_result.get(), "BACKGROUND");
	}

	TEST_F(LogOutputEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(LogOutput::FOREGROUND);
					LogOutput result = manager.convert_string_to_enum(converted);
					if (result == LogOutput::FOREGROUND)
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

	TEST_F(LogOutputEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		LogOutputEnumManager& first_instance = SingletonManager::get_singleton<LogOutputEnumManager>();
		LogOutputEnumManager& second_instance = SingletonManager::get_singleton<LogOutputEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		LogOutputEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("ALL", LogOutput::ALL),
			std::make_pair("FOREGROUND", LogOutput::FOREGROUND),
			std::make_pair("BACKGROUND", LogOutput::BACKGROUND),
			std::make_pair("NONE", LogOutput::NONE),
			std::make_pair("", LogOutput::NONE),
			std::make_pair("INVALID", LogOutput::NONE)
		)
	);

	TEST_P(LogOutputEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		LogOutput expected = param.second;

		LogOutput result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		LogOutputEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			LogOutput::ALL,
			LogOutput::FOREGROUND,
			LogOutput::BACKGROUND,
			LogOutput::NONE
		)
	);

	TEST_P(LogOutputEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		LogOutput input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case LogOutput::ALL: EXPECT_EQ(result, "ALL"); break;
			case LogOutput::FOREGROUND: EXPECT_EQ(result, "FOREGROUND"); break;
			case LogOutput::BACKGROUND: EXPECT_EQ(result, "BACKGROUND"); break;
			case LogOutput::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
