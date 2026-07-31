#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeScaleUnitEnumManager \
	)

#include "../includes/time_scale_unit_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(TimeScaleUnitEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		TimeScaleUnit result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, TimeScaleUnit::NONE);
	}

	TEST_F(TimeScaleUnitEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		TimeScaleUnitEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(TimeScaleUnit::YEARS);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(TimeScaleUnitEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		TimeScaleUnitEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		TimeScaleUnit result = manager.convert_string_to_enum("YEARS");
		EXPECT_EQ(result, TimeScaleUnit::NONE);
	}

	TEST_F(TimeScaleUnitEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		TimeScaleUnitEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(TimeScaleUnit::MONTHS);
		EXPECT_EQ(converted, "MONTHS");

		TimeScaleUnit result = manager.convert_string_to_enum("MONTHS");
		EXPECT_EQ(result, TimeScaleUnit::MONTHS);
	}

	TEST_F(TimeScaleUnitEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public TimeScaleUnitEnumManager
		{
		public:
			std::string convert_enum_to_string(const TimeScaleUnit&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(TimeScaleUnit::WEEKS), std::runtime_error);
	}

	TEST_F(TimeScaleUnitEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		TimeScaleUnitEnumManagerConfigurations configurations;
		configurations.type = TimeScaleUnit::YEARS;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(TimeScaleUnit::YEARS);
		});

		EXPECT_EQ(future_result.get(), "YEARS");
	}

	TEST_F(TimeScaleUnitEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(TimeScaleUnit::MONTHS);
					TimeScaleUnit result = manager.convert_string_to_enum(converted);
					if (result == TimeScaleUnit::MONTHS)
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

	TEST_F(TimeScaleUnitEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		TimeScaleUnitEnumManager& first_instance = SingletonManager::get_singleton<TimeScaleUnitEnumManager>();
		TimeScaleUnitEnumManager& second_instance = SingletonManager::get_singleton<TimeScaleUnitEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		TimeScaleUnitEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("SECONDS", TimeScaleUnit::SECONDS),
			std::make_pair("YEARS", TimeScaleUnit::YEARS),
			std::make_pair("MONTHS", TimeScaleUnit::MONTHS),
			std::make_pair("WEEKS", TimeScaleUnit::WEEKS),
			std::make_pair("DAYS", TimeScaleUnit::DAYS),
			std::make_pair("HOURS", TimeScaleUnit::HOURS),
			std::make_pair("MINUTES", TimeScaleUnit::MINUTES),
			std::make_pair("MILLISECONDS", TimeScaleUnit::MILLISECONDS),
			std::make_pair("MICROSECONDS", TimeScaleUnit::MICROSECONDS),
			std::make_pair("NANOSECONDS", TimeScaleUnit::NANOSECONDS),
			std::make_pair("NONE", TimeScaleUnit::NONE),
			std::make_pair("", TimeScaleUnit::NONE),
			std::make_pair("INVALID", TimeScaleUnit::NONE)
		)
	);

	TEST_P(TimeScaleUnitEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		TimeScaleUnit expected = param.second;

		TimeScaleUnit result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		TimeScaleUnitEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			TimeScaleUnit::SECONDS,
			TimeScaleUnit::YEARS,
			TimeScaleUnit::MONTHS,
			TimeScaleUnit::WEEKS,
			TimeScaleUnit::DAYS,
			TimeScaleUnit::HOURS,
			TimeScaleUnit::MINUTES,
			TimeScaleUnit::MILLISECONDS,
			TimeScaleUnit::MICROSECONDS,
			TimeScaleUnit::NANOSECONDS,
			TimeScaleUnit::NONE
		)
	);

	TEST_P(TimeScaleUnitEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		TimeScaleUnit input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case TimeScaleUnit::SECONDS: EXPECT_EQ(result, "SECONDS"); break;
			case TimeScaleUnit::YEARS: EXPECT_EQ(result, "YEARS"); break;
			case TimeScaleUnit::MONTHS: EXPECT_EQ(result, "MONTHS"); break;
			case TimeScaleUnit::WEEKS: EXPECT_EQ(result, "WEEKS"); break;
			case TimeScaleUnit::DAYS: EXPECT_EQ(result, "DAYS"); break;
			case TimeScaleUnit::HOURS: EXPECT_EQ(result, "HOURS"); break;
			case TimeScaleUnit::MINUTES: EXPECT_EQ(result, "MINUTES"); break;
			case TimeScaleUnit::MILLISECONDS: EXPECT_EQ(result, "MILLISECONDS"); break;
			case TimeScaleUnit::MICROSECONDS: EXPECT_EQ(result, "MICROSECONDS"); break;
			case TimeScaleUnit::NANOSECONDS: EXPECT_EQ(result, "NANOSECONDS"); break;
			case TimeScaleUnit::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
