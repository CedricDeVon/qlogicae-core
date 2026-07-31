#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerMetadataFlagsEnumManager \
	)

#include "../includes/file_system_event_listener_metadata_flags_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(FileSystemEventListenerMetadataFlagsEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		FileSystemEventListenerMetadataFlags result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, FileSystemEventListenerMetadataFlags::NONE);
	}

	TEST_F(FileSystemEventListenerMetadataFlagsEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		FileSystemEventListenerMetadataFlagsEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(FileSystemEventListenerMetadataFlags::OWNERSHIP);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(FileSystemEventListenerMetadataFlagsEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		FileSystemEventListenerMetadataFlagsEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		FileSystemEventListenerMetadataFlags result = manager.convert_string_to_enum("OWNERSHIP");
		EXPECT_EQ(result, FileSystemEventListenerMetadataFlags::NONE);
	}

	TEST_F(FileSystemEventListenerMetadataFlagsEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		FileSystemEventListenerMetadataFlagsEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(FileSystemEventListenerMetadataFlags::TIMESTAMP);
		EXPECT_EQ(converted, "TIMESTAMP");

		FileSystemEventListenerMetadataFlags result = manager.convert_string_to_enum("TIMESTAMP");
		EXPECT_EQ(result, FileSystemEventListenerMetadataFlags::TIMESTAMP);
	}

	TEST_F(FileSystemEventListenerMetadataFlagsEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public FileSystemEventListenerMetadataFlagsEnumManager
		{
		public:
			std::string convert_enum_to_string(const FileSystemEventListenerMetadataFlags&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(FileSystemEventListenerMetadataFlags::PERMISSIONS), std::runtime_error);
	}

	TEST_F(FileSystemEventListenerMetadataFlagsEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		FileSystemEventListenerMetadataFlagsEnumManagerConfigurations configurations;
		configurations.type = FileSystemEventListenerMetadataFlags::OWNERSHIP;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(FileSystemEventListenerMetadataFlags::OWNERSHIP);
		});

		EXPECT_EQ(future_result.get(), "OWNERSHIP");
	}

	TEST_F(FileSystemEventListenerMetadataFlagsEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(FileSystemEventListenerMetadataFlags::TIMESTAMP);
					FileSystemEventListenerMetadataFlags result = manager.convert_string_to_enum(converted);
					if (result == FileSystemEventListenerMetadataFlags::TIMESTAMP)
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

	TEST_F(FileSystemEventListenerMetadataFlagsEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		FileSystemEventListenerMetadataFlagsEnumManager& first_instance = SingletonManager::get_singleton<FileSystemEventListenerMetadataFlagsEnumManager>();
		FileSystemEventListenerMetadataFlagsEnumManager& second_instance = SingletonManager::get_singleton<FileSystemEventListenerMetadataFlagsEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		FileSystemEventListenerMetadataFlagsEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("PERMISSIONS", FileSystemEventListenerMetadataFlags::PERMISSIONS),
			std::make_pair("TIMESTAMP", FileSystemEventListenerMetadataFlags::TIMESTAMP),
			std::make_pair("OWNERSHIP", FileSystemEventListenerMetadataFlags::OWNERSHIP),
			std::make_pair("NONE", FileSystemEventListenerMetadataFlags::NONE),
			std::make_pair("", FileSystemEventListenerMetadataFlags::NONE),
			std::make_pair("INVALID", FileSystemEventListenerMetadataFlags::NONE)
		)
	);

	TEST_P(FileSystemEventListenerMetadataFlagsEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		FileSystemEventListenerMetadataFlags expected = param.second;

		FileSystemEventListenerMetadataFlags result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		FileSystemEventListenerMetadataFlagsEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			FileSystemEventListenerMetadataFlags::PERMISSIONS,
			FileSystemEventListenerMetadataFlags::TIMESTAMP,
			FileSystemEventListenerMetadataFlags::OWNERSHIP,
			FileSystemEventListenerMetadataFlags::NONE
		)
	);

	TEST_P(FileSystemEventListenerMetadataFlagsEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		FileSystemEventListenerMetadataFlags input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case FileSystemEventListenerMetadataFlags::PERMISSIONS: EXPECT_EQ(result, "PERMISSIONS"); break;
			case FileSystemEventListenerMetadataFlags::TIMESTAMP: EXPECT_EQ(result, "TIMESTAMP"); break;
			case FileSystemEventListenerMetadataFlags::OWNERSHIP: EXPECT_EQ(result, "OWNERSHIP"); break;
			case FileSystemEventListenerMetadataFlags::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
