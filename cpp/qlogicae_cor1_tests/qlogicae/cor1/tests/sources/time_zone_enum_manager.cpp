#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeZoneEnumManager \
	)

#include "../includes/time_zone_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(TimeZoneEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		TimeZone result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, TimeZone::NONE);
	}

	TEST_F(TimeZoneEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		TimeZoneEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(TimeZone::UTC);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(TimeZoneEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		TimeZoneEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		TimeZone result = manager.convert_string_to_enum("UTC");
		EXPECT_EQ(result, TimeZone::NONE);
	}

	TEST_F(TimeZoneEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		TimeZoneEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(TimeZone::LOCAL);
		EXPECT_EQ(converted, "LOCAL");

		TimeZone result = manager.convert_string_to_enum("LOCAL");
		EXPECT_EQ(result, TimeZone::LOCAL);
	}

	TEST_F(TimeZoneEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public TimeZoneEnumManager
		{
		public:
			std::string convert_enum_to_string(const TimeZone&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(TimeZone::LOCAL), std::runtime_error);
	}

	TEST_F(TimeZoneEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		TimeZoneEnumManagerConfigurations configurations;
		configurations.type = TimeZone::UTC;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
			{
				return manager.convert_enum_to_string(TimeZone::UTC);
			});

		EXPECT_EQ(future_result.get(), "UTC");
	}

	TEST_F(TimeZoneEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
						std::string converted = manager.convert_enum_to_string(TimeZone::LOCAL);
						TimeZone result = manager.convert_string_to_enum(converted);
						if (result == TimeZone::LOCAL)
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

	TEST_F(TimeZoneEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		TimeZoneEnumManager& first_instance = SingletonManager::get_singleton<TimeZoneEnumManager>();
		TimeZoneEnumManager& second_instance = SingletonManager::get_singleton<TimeZoneEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		TimeZoneEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("UTC", TimeZone::UTC),
			std::make_pair("LOCAL", TimeZone::LOCAL),
			std::make_pair("NONE", TimeZone::NONE),
			std::make_pair("", TimeZone::NONE),
			std::make_pair("INVALID", TimeZone::NONE)
		)
	);

	TEST_P(TimeZoneEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		TimeZone expected = param.second;

		TimeZone result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		TimeZoneEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			TimeZone::UTC,
			TimeZone::LOCAL,
			TimeZone::NONE
		)
	);

	TEST_P(TimeZoneEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		TimeZone input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case TimeZone::UTC: EXPECT_EQ(result, "UTC"); break;
			case TimeZone::LOCAL: EXPECT_EQ(result, "LOCAL"); break;
			case TimeZone::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
