#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsRegistryRootPathEnumManager \
	)

#include "../includes/windows_registry_root_path_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(WindowsRegistryRootPathEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		WindowsRegistryRootPath result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, WindowsRegistryRootPath::NONE);
	}

	TEST_F(WindowsRegistryRootPathEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		WindowsRegistryRootPathEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(WindowsRegistryRootPath::HKCU);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(WindowsRegistryRootPathEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		WindowsRegistryRootPathEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		WindowsRegistryRootPath result = manager.convert_string_to_enum("HKCU");
		EXPECT_EQ(result, WindowsRegistryRootPath::NONE);
	}

	TEST_F(WindowsRegistryRootPathEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		WindowsRegistryRootPathEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(WindowsRegistryRootPath::HKLM);
		EXPECT_EQ(converted, "HKLM");

		WindowsRegistryRootPath result = manager.convert_string_to_enum("HKLM");
		EXPECT_EQ(result, WindowsRegistryRootPath::HKLM);
	}

	TEST_F(WindowsRegistryRootPathEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public WindowsRegistryRootPathEnumManager
		{
		public:
			std::string convert_enum_to_string(const WindowsRegistryRootPath&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(WindowsRegistryRootPath::HKCU), std::runtime_error);
	}

	TEST_F(WindowsRegistryRootPathEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		WindowsRegistryRootPathEnumManagerConfigurations configurations;
		configurations.type = WindowsRegistryRootPath::HKCU;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(WindowsRegistryRootPath::HKCU);
		});

		EXPECT_EQ(future_result.get(), "HKCU");
	}

	TEST_F(WindowsRegistryRootPathEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(WindowsRegistryRootPath::HKCU);
					WindowsRegistryRootPath result = manager.convert_string_to_enum(converted);
					if (result == WindowsRegistryRootPath::HKCU)
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

	TEST_F(WindowsRegistryRootPathEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		WindowsRegistryRootPathEnumManager& first_instance = SingletonManager::get_singleton<WindowsRegistryRootPathEnumManager>();
		WindowsRegistryRootPathEnumManager& second_instance = SingletonManager::get_singleton<WindowsRegistryRootPathEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		WindowsRegistryRootPathEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("HKLM", WindowsRegistryRootPath::HKLM),
			std::make_pair("HKCU", WindowsRegistryRootPath::HKCU),
			std::make_pair("NONE", WindowsRegistryRootPath::NONE),
			std::make_pair("", WindowsRegistryRootPath::NONE),
			std::make_pair("INVALID", WindowsRegistryRootPath::NONE)
		)
	);

	TEST_P(WindowsRegistryRootPathEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		WindowsRegistryRootPath expected = param.second;

		WindowsRegistryRootPath result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		WindowsRegistryRootPathEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			WindowsRegistryRootPath::HKLM,
			WindowsRegistryRootPath::HKCU,
			WindowsRegistryRootPath::NONE
		)
	);

	TEST_P(WindowsRegistryRootPathEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		WindowsRegistryRootPath input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case WindowsRegistryRootPath::HKLM: EXPECT_EQ(result, "HKLM"); break;
			case WindowsRegistryRootPath::HKCU: EXPECT_EQ(result, "HKCU"); break;
			case WindowsRegistryRootPath::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
