#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TemperatureUnitEnumManager \
	)

#include "../includes/temperature_unit_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(TemperatureUnitEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		TemperatureUnit result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, TemperatureUnit::NONE);
	}

	TEST_F(TemperatureUnitEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		TemperatureUnitEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(TemperatureUnit::CELSIUS);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(TemperatureUnitEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		TemperatureUnitEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		TemperatureUnit result = manager.convert_string_to_enum("CELSIUS");
		EXPECT_EQ(result, TemperatureUnit::NONE);
	}

	TEST_F(TemperatureUnitEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		TemperatureUnitEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(TemperatureUnit::FAHRENHEIT);
		EXPECT_EQ(converted, "FAHRENHEIT");

		TemperatureUnit result = manager.convert_string_to_enum("FAHRENHEIT");
		EXPECT_EQ(result, TemperatureUnit::FAHRENHEIT);
	}

	TEST_F(TemperatureUnitEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public TemperatureUnitEnumManager
		{
		public:
			std::string convert_enum_to_string(const TemperatureUnit&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(TemperatureUnit::FAHRENHEIT), std::runtime_error);
	}

	TEST_F(TemperatureUnitEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		TemperatureUnitEnumManagerConfigurations configurations;
		configurations.type = TemperatureUnit::CELSIUS;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
			{
				return manager.convert_enum_to_string(TemperatureUnit::CELSIUS);
			});

		EXPECT_EQ(future_result.get(), "CELSIUS");
	}

	TEST_F(TemperatureUnitEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
						std::string converted = manager.convert_enum_to_string(TemperatureUnit::FAHRENHEIT);
						TemperatureUnit result = manager.convert_string_to_enum(converted);
						if (result == TemperatureUnit::FAHRENHEIT)
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

	TEST_F(TemperatureUnitEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		TemperatureUnitEnumManager& first_instance = SingletonManager::get_singleton<TemperatureUnitEnumManager>();
		TemperatureUnitEnumManager& second_instance = SingletonManager::get_singleton<TemperatureUnitEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		TemperatureUnitEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("CELSIUS", TemperatureUnit::CELSIUS),
			std::make_pair("FAHRENHEIT", TemperatureUnit::FAHRENHEIT),
			std::make_pair("KELVIN", TemperatureUnit::KELVIN),
			std::make_pair("NONE", TemperatureUnit::NONE),
			std::make_pair("", TemperatureUnit::NONE),
			std::make_pair("INVALID", TemperatureUnit::NONE)
		)
	);

	TEST_P(TemperatureUnitEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		TemperatureUnit expected = param.second;

		TemperatureUnit result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		TemperatureUnitEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			TemperatureUnit::CELSIUS,
			TemperatureUnit::FAHRENHEIT,
			TemperatureUnit::KELVIN,
			TemperatureUnit::NONE
		)
	);

	TEST_P(TemperatureUnitEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		TemperatureUnit input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case TemperatureUnit::CELSIUS: EXPECT_EQ(result, "CELSIUS"); break;
			case TemperatureUnit::FAHRENHEIT: EXPECT_EQ(result, "FAHRENHEIT"); break;
			case TemperatureUnit::KELVIN: EXPECT_EQ(result, "KELVIN"); break;
			case TemperatureUnit::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
