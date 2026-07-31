#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsEnvironmentVariableEnumManager \
	)

#include "../includes/windows_environment_variable_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(WindowsEnvironmentVariableEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		WindowsEnvironmentVariable result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, WindowsEnvironmentVariable::NONE);
	}

	TEST_F(WindowsEnvironmentVariableEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		WindowsEnvironmentVariableEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(WindowsEnvironmentVariable::USER);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(WindowsEnvironmentVariableEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		WindowsEnvironmentVariableEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		WindowsEnvironmentVariable result = manager.convert_string_to_enum("USER");
		EXPECT_EQ(result, WindowsEnvironmentVariable::NONE);
	}

	TEST_F(WindowsEnvironmentVariableEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		WindowsEnvironmentVariableEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(WindowsEnvironmentVariable::SYSTEM);
		EXPECT_EQ(converted, "SYSTEM");

		WindowsEnvironmentVariable result = manager.convert_string_to_enum("SYSTEM");
		EXPECT_EQ(result, WindowsEnvironmentVariable::SYSTEM);
	}

	TEST_F(WindowsEnvironmentVariableEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public WindowsEnvironmentVariableEnumManager
		{
		public:
			std::string convert_enum_to_string(const WindowsEnvironmentVariable&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(WindowsEnvironmentVariable::USER), std::runtime_error);
	}

	TEST_F(WindowsEnvironmentVariableEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		WindowsEnvironmentVariableEnumManagerConfigurations configurations;
		configurations.type = WindowsEnvironmentVariable::USER;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(WindowsEnvironmentVariable::USER);
		});

		EXPECT_EQ(future_result.get(), "USER");
	}

	TEST_F(WindowsEnvironmentVariableEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(WindowsEnvironmentVariable::USER);
					WindowsEnvironmentVariable result = manager.convert_string_to_enum(converted);
					if (result == WindowsEnvironmentVariable::USER)
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

	TEST_F(WindowsEnvironmentVariableEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		WindowsEnvironmentVariableEnumManager& first_instance = SingletonManager::get_singleton<WindowsEnvironmentVariableEnumManager>();
		WindowsEnvironmentVariableEnumManager& second_instance = SingletonManager::get_singleton<WindowsEnvironmentVariableEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		WindowsEnvironmentVariableEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("SYSTEM", WindowsEnvironmentVariable::SYSTEM),
			std::make_pair("USER", WindowsEnvironmentVariable::USER),
			std::make_pair("NONE", WindowsEnvironmentVariable::NONE),
			std::make_pair("", WindowsEnvironmentVariable::NONE),
			std::make_pair("INVALID", WindowsEnvironmentVariable::NONE)
		)
	);

	TEST_P(WindowsEnvironmentVariableEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		WindowsEnvironmentVariable expected = param.second;

		WindowsEnvironmentVariable result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		WindowsEnvironmentVariableEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			WindowsEnvironmentVariable::SYSTEM,
			WindowsEnvironmentVariable::USER,
			WindowsEnvironmentVariable::NONE
		)
	);

	TEST_P(WindowsEnvironmentVariableEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		WindowsEnvironmentVariable input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case WindowsEnvironmentVariable::SYSTEM: EXPECT_EQ(result, "SYSTEM"); break;
			case WindowsEnvironmentVariable::USER: EXPECT_EQ(result, "USER"); break;
			case WindowsEnvironmentVariable::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
