#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeFormatEnumManager \
	)

#include "../includes/time_format_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(TimeFormatEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		TimeFormat result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, TimeFormat::NONE);
	}

	TEST_F(TimeFormatEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		TimeFormatEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(TimeFormat::UNIX);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(TimeFormatEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		TimeFormatEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		TimeFormat result = manager.convert_string_to_enum("UNIX");
		EXPECT_EQ(result, TimeFormat::NONE);
	}

	TEST_F(TimeFormatEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		TimeFormatEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(TimeFormat::ISO8601);
		EXPECT_EQ(converted, "ISO8601");

		TimeFormat result = manager.convert_string_to_enum("ISO8601");
		EXPECT_EQ(result, TimeFormat::ISO8601);
	}

	TEST_F(TimeFormatEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public TimeFormatEnumManager
		{
		public:
			std::string convert_enum_to_string(const TimeFormat&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(TimeFormat::UNIX), std::runtime_error);
	}

	TEST_F(TimeFormatEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		TimeFormatEnumManagerConfigurations configurations;
		configurations.type = TimeFormat::UNIX;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(TimeFormat::UNIX);
		});

		EXPECT_EQ(future_result.get(), "UNIX");
	}

	TEST_F(TimeFormatEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(TimeFormat::ISO8601);
					TimeFormat result = manager.convert_string_to_enum(converted);
					if (result == TimeFormat::ISO8601)
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

	TEST_F(TimeFormatEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		TimeFormatEnumManager& first_instance = SingletonManager::get_singleton<TimeFormatEnumManager>();
		TimeFormatEnumManager& second_instance = SingletonManager::get_singleton<TimeFormatEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		TimeFormatEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("UNIX", TimeFormat::UNIX),
			std::make_pair("ISO8601", TimeFormat::ISO8601),
			std::make_pair("SECOND_LEVEL_TIMESTAMP", TimeFormat::SECOND_LEVEL_TIMESTAMP),
			std::make_pair("MILLISECOND_LEVEL_TIMESTAMP", TimeFormat::MILLISECOND_LEVEL_TIMESTAMP),
			std::make_pair("MICROSECOND_LEVEL_TIMESTAMP", TimeFormat::MICROSECOND_LEVEL_TIMESTAMP),
			std::make_pair("FULL_TIMESTAMP", TimeFormat::FULL_TIMESTAMP),
			std::make_pair("FULL_DASHED_TIMESTAMP", TimeFormat::FULL_DASHED_TIMESTAMP),
			std::make_pair("HOUR_12", TimeFormat::HOUR_12),
			std::make_pair("HOUR_24", TimeFormat::HOUR_24),
			std::make_pair("MILLISECOND_MICROSECOND_NANOSECOND", TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND),
			std::make_pair("DATE_DASHED", TimeFormat::DATE_DASHED),
			std::make_pair("DATE_MDY_SLASHED", TimeFormat::DATE_MDY_SLASHED),
			std::make_pair("DATE_DMY_SLASHED", TimeFormat::DATE_DMY_SLASHED),
			std::make_pair("DATE_DMY_SPACED", TimeFormat::DATE_DMY_SPACED),
			std::make_pair("DATE_VERBOSE", TimeFormat::DATE_VERBOSE),
			std::make_pair("NONE", TimeFormat::NONE),
			std::make_pair("", TimeFormat::NONE),
			std::make_pair("INVALID", TimeFormat::NONE)
		)
	);

	TEST_P(TimeFormatEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		TimeFormat expected = param.second;

		TimeFormat result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		TimeFormatEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			TimeFormat::UNIX,
			TimeFormat::ISO8601,
			TimeFormat::SECOND_LEVEL_TIMESTAMP,
			TimeFormat::MILLISECOND_LEVEL_TIMESTAMP,
			TimeFormat::MICROSECOND_LEVEL_TIMESTAMP,
			TimeFormat::FULL_TIMESTAMP,
			TimeFormat::FULL_DASHED_TIMESTAMP,
			TimeFormat::HOUR_12,
			TimeFormat::HOUR_24,
			TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND,
			TimeFormat::DATE_DASHED,
			TimeFormat::DATE_MDY_SLASHED,
			TimeFormat::DATE_DMY_SLASHED,
			TimeFormat::DATE_DMY_SPACED,
			TimeFormat::DATE_VERBOSE,
			TimeFormat::NONE
		)
	);

	TEST_P(TimeFormatEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		TimeFormat input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{		
			case TimeFormat::UNIX: EXPECT_EQ(result, "UNIX"); break;
			case TimeFormat::ISO8601: EXPECT_EQ(result, "ISO8601"); break;
			case TimeFormat::SECOND_LEVEL_TIMESTAMP: EXPECT_EQ(result, "SECOND_LEVEL_TIMESTAMP"); break;
			case TimeFormat::MILLISECOND_LEVEL_TIMESTAMP: EXPECT_EQ(result, "MILLISECOND_LEVEL_TIMESTAMP"); break;
			case TimeFormat::MICROSECOND_LEVEL_TIMESTAMP: EXPECT_EQ(result, "MICROSECOND_LEVEL_TIMESTAMP"); break;
			case TimeFormat::FULL_TIMESTAMP: EXPECT_EQ(result, "FULL_TIMESTAMP"); break;
			case TimeFormat::FULL_DASHED_TIMESTAMP: EXPECT_EQ(result, "FULL_DASHED_TIMESTAMP"); break;
			case TimeFormat::HOUR_12: EXPECT_EQ(result, "HOUR_12"); break;
			case TimeFormat::HOUR_24: EXPECT_EQ(result, "HOUR_24"); break;
			case TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND: EXPECT_EQ(result, "MILLISECOND_MICROSECOND_NANOSECOND"); break;
			case TimeFormat::DATE_DASHED: EXPECT_EQ(result, "DATE_DASHED"); break;
			case TimeFormat::DATE_MDY_SLASHED: EXPECT_EQ(result, "DATE_MDY_SLASHED"); break;
			case TimeFormat::DATE_DMY_SLASHED: EXPECT_EQ(result, "DATE_DMY_SLASHED"); break;
			case TimeFormat::DATE_DMY_SPACED: EXPECT_EQ(result, "DATE_DMY_SPACED"); break;
			case TimeFormat::DATE_VERBOSE: EXPECT_EQ(result, "DATE_VERBOSE"); break;
			case TimeFormat::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
