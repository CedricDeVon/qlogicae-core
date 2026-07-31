#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogLevelEnumManager \
	)

#include "../includes/log_level_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(LogLevelEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		LogLevel result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, LogLevel::NONE);
	}

	TEST_F(LogLevelEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		LogLevelEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(LogLevel::INFO);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(LogLevelEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		LogLevelEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		LogLevel result = manager.convert_string_to_enum("INFO");
		EXPECT_EQ(result, LogLevel::NONE);
	}

	TEST_F(LogLevelEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		LogLevelEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(LogLevel::DEBUG);
		EXPECT_EQ(converted, "DEBUG");

		LogLevel result = manager.convert_string_to_enum("DEBUG");
		EXPECT_EQ(result, LogLevel::DEBUG);
	}

	TEST_F(LogLevelEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public LogLevelEnumManager
		{
		public:
			std::string convert_enum_to_string(const LogLevel&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(LogLevel::ALL), std::runtime_error);
	}

	TEST_F(LogLevelEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		LogLevelEnumManagerConfigurations configurations;
		configurations.type = LogLevel::INFO;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(LogLevel::INFO);
		});

		EXPECT_EQ(future_result.get(), "INFO");
	}

	TEST_F(LogLevelEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(LogLevel::DEBUG);
					LogLevel result = manager.convert_string_to_enum(converted);
					if (result == LogLevel::DEBUG)
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

	TEST_F(LogLevelEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		LogLevelEnumManager& first_instance = SingletonManager::get_singleton<LogLevelEnumManager>();
		LogLevelEnumManager& second_instance = SingletonManager::get_singleton<LogLevelEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		LogLevelEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("ALL", LogLevel::ALL),
			std::make_pair("INFO", LogLevel::INFO),
			std::make_pair("DEBUG", LogLevel::DEBUG),
			std::make_pair("WARNING", LogLevel::WARNING),
			std::make_pair("SUCCESS", LogLevel::SUCCESS),
			std::make_pair("CRITICAL", LogLevel::CRITICAL),
			std::make_pair("ERROR_TYPE", LogLevel::ERROR_TYPE),
			std::make_pair("HIGHLIGHTED_INFO", LogLevel::HIGHLIGHTED_INFO),
			std::make_pair("NONE", LogLevel::NONE),
			std::make_pair("", LogLevel::NONE),
			std::make_pair("INVALID", LogLevel::NONE)
		)
	);

	TEST_P(LogLevelEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		LogLevel expected = param.second;

		LogLevel result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		LogLevelEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			LogLevel::ALL,
			LogLevel::INFO,
			LogLevel::DEBUG,
			LogLevel::WARNING,
			LogLevel::SUCCESS,
			LogLevel::CRITICAL,
			LogLevel::ERROR_TYPE,
			LogLevel::NONE
		)
	);

	TEST_P(LogLevelEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		LogLevel input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case LogLevel::ALL: EXPECT_EQ(result, "ALL"); break;
			case LogLevel::INFO: EXPECT_EQ(result, "INFO"); break;
			case LogLevel::DEBUG: EXPECT_EQ(result, "DEBUG"); break;
			case LogLevel::WARNING: EXPECT_EQ(result, "WARNING"); break;
			case LogLevel::SUCCESS: EXPECT_EQ(result, "SUCCESS"); break;
			case LogLevel::CRITICAL: EXPECT_EQ(result, "CRITICAL"); break;
			case LogLevel::ERROR_TYPE: EXPECT_EQ(result, "ERROR_TYPE"); break;
			case LogLevel::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
