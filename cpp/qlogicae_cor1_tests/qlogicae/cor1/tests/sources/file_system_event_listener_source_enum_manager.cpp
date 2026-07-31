#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerSourceEnumManager \
	)

#include "../includes/file_system_event_listener_source_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(FileSystemEventListenerSourceEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		FileSystemEventListenerSource result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, FileSystemEventListenerSource::NONE);
	}

	TEST_F(FileSystemEventListenerSourceEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		FileSystemEventListenerSourceEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(FileSystemEventListenerSource::SYNTHETIC);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(FileSystemEventListenerSourceEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		FileSystemEventListenerSourceEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		FileSystemEventListenerSource result = manager.convert_string_to_enum("SYNTHETIC");
		EXPECT_EQ(result, FileSystemEventListenerSource::NONE);
	}

	TEST_F(FileSystemEventListenerSourceEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		FileSystemEventListenerSourceEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(FileSystemEventListenerSource::SYNTHETIC);
		EXPECT_EQ(converted, "SYNTHETIC");

		FileSystemEventListenerSource result = manager.convert_string_to_enum("SYNTHETIC");
		EXPECT_EQ(result, FileSystemEventListenerSource::SYNTHETIC);
	}

	TEST_F(FileSystemEventListenerSourceEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public FileSystemEventListenerSourceEnumManager
		{
		public:
			std::string convert_enum_to_string(const FileSystemEventListenerSource&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(FileSystemEventListenerSource::NATIVE), std::runtime_error);
	}

	TEST_F(FileSystemEventListenerSourceEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		FileSystemEventListenerSourceEnumManagerConfigurations configurations;
		configurations.type = FileSystemEventListenerSource::SYNTHETIC;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(FileSystemEventListenerSource::SYNTHETIC);
		});

		EXPECT_EQ(future_result.get(), "SYNTHETIC");
	}

	TEST_F(FileSystemEventListenerSourceEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(FileSystemEventListenerSource::SYNTHETIC);
					FileSystemEventListenerSource result = manager.convert_string_to_enum(converted);
					if (result == FileSystemEventListenerSource::SYNTHETIC)
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

	TEST_F(FileSystemEventListenerSourceEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		FileSystemEventListenerSourceEnumManager& first_instance = SingletonManager::get_singleton<FileSystemEventListenerSourceEnumManager>();
		FileSystemEventListenerSourceEnumManager& second_instance = SingletonManager::get_singleton<FileSystemEventListenerSourceEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		FileSystemEventListenerSourceEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("NATIVE", FileSystemEventListenerSource::NATIVE),
			std::make_pair("SYNTHETIC", FileSystemEventListenerSource::SYNTHETIC),
			std::make_pair("", FileSystemEventListenerSource::NONE),
			std::make_pair("INVALID", FileSystemEventListenerSource::NONE)
		)
	);

	TEST_P(FileSystemEventListenerSourceEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		FileSystemEventListenerSource expected = param.second;

		FileSystemEventListenerSource result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		FileSystemEventListenerSourceEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			FileSystemEventListenerSource::NATIVE,
			FileSystemEventListenerSource::SYNTHETIC,
			FileSystemEventListenerSource::NONE
		)
	);

	TEST_P(FileSystemEventListenerSourceEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		FileSystemEventListenerSource input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case FileSystemEventListenerSource::NATIVE: EXPECT_EQ(result, "NATIVE"); break;
			case FileSystemEventListenerSource::SYNTHETIC: EXPECT_EQ(result, "SYNTHETIC"); break;
			case FileSystemEventListenerSource::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
