#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ResultsStatusEnumManager \
	)

#include "../includes/results_status_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(ResultsStatusEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		ResultsStatus result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, ResultsStatus::NONE);
	}

	TEST_F(ResultsStatusEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		ResultsStatusEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(ResultsStatus::GOOD);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(ResultsStatusEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		ResultsStatusEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		ResultsStatus result = manager.convert_string_to_enum("GOOD");
		EXPECT_EQ(result, ResultsStatus::NONE);
	}

	TEST_F(ResultsStatusEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		ResultsStatusEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(ResultsStatus::BAD);
		EXPECT_EQ(converted, "BAD");

		ResultsStatus result = manager.convert_string_to_enum("BAD");
		EXPECT_EQ(result, ResultsStatus::BAD);
	}

	TEST_F(ResultsStatusEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public ResultsStatusEnumManager
		{
		public:
			std::string convert_enum_to_string(const ResultsStatus&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(ResultsStatus::BAD), std::runtime_error);
	}

	TEST_F(ResultsStatusEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		ResultsStatusEnumManagerConfigurations configurations;
		configurations.type = ResultsStatus::GOOD;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
			{
				return manager.convert_enum_to_string(ResultsStatus::GOOD);
			});

		EXPECT_EQ(future_result.get(), "GOOD");
	}

	TEST_F(ResultsStatusEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
						std::string converted = manager.convert_enum_to_string(ResultsStatus::BAD);
						ResultsStatus result = manager.convert_string_to_enum(converted);
						if (result == ResultsStatus::BAD)
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

	TEST_F(ResultsStatusEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		ResultsStatusEnumManager& first_instance = SingletonManager::get_singleton<ResultsStatusEnumManager>();
		ResultsStatusEnumManager& second_instance = SingletonManager::get_singleton<ResultsStatusEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		ResultsStatusEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("GOOD", ResultsStatus::GOOD),
			std::make_pair("BAD", ResultsStatus::BAD),
			std::make_pair("INFO", ResultsStatus::INFO),
			std::make_pair("DEBUG", ResultsStatus::DEBUG),
			std::make_pair("WARNING", ResultsStatus::WARNING),
			std::make_pair("EXCEPTION", ResultsStatus::EXCEPTION),
			std::make_pair("ERROR_TYPE", ResultsStatus::ERROR_TYPE),
			std::make_pair("NONE", ResultsStatus::NONE),
			std::make_pair("", ResultsStatus::NONE),
			std::make_pair("INVALID", ResultsStatus::NONE)
		)
	);

	TEST_P(ResultsStatusEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		ResultsStatus expected = param.second;

		ResultsStatus result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		ResultsStatusEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			ResultsStatus::GOOD,
			ResultsStatus::BAD,
			ResultsStatus::INFO,
			ResultsStatus::DEBUG,
			ResultsStatus::WARNING,
			ResultsStatus::EXCEPTION,
			ResultsStatus::ERROR_TYPE,
			ResultsStatus::NONE
		)
	);

	TEST_P(ResultsStatusEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		ResultsStatus input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case ResultsStatus::GOOD: EXPECT_EQ(result, "GOOD"); break;
			case ResultsStatus::BAD: EXPECT_EQ(result, "BAD"); break;
			case ResultsStatus::INFO: EXPECT_EQ(result, "INFO"); break;
			case ResultsStatus::DEBUG: EXPECT_EQ(result, "DEBUG"); break;
			case ResultsStatus::WARNING: EXPECT_EQ(result, "WARNING"); break;
			case ResultsStatus::EXCEPTION: EXPECT_EQ(result, "EXCEPTION"); break;
			case ResultsStatus::ERROR_TYPE: EXPECT_EQ(result, "ERROR_TYPE"); break;
			case ResultsStatus::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
