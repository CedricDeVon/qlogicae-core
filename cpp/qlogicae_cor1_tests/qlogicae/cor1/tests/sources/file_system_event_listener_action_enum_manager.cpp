#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerActionEnumManager \
	)

#include "../includes/file_system_event_listener_action_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(FileSystemEventListenerActionEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		FileSystemEventListenerAction result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, FileSystemEventListenerAction::NONE);
	}

	TEST_F(FileSystemEventListenerActionEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		FileSystemEventListenerActionEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(FileSystemEventListenerAction::DELETED);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(FileSystemEventListenerActionEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		FileSystemEventListenerActionEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		FileSystemEventListenerAction result = manager.convert_string_to_enum("DELETED");
		EXPECT_EQ(result, FileSystemEventListenerAction::NONE);
	}

	TEST_F(FileSystemEventListenerActionEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		FileSystemEventListenerActionEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(FileSystemEventListenerAction::DELETED);
		EXPECT_EQ(converted, "DELETED");

		FileSystemEventListenerAction result = manager.convert_string_to_enum("DELETED");
		EXPECT_EQ(result, FileSystemEventListenerAction::DELETED);
	}

	TEST_F(FileSystemEventListenerActionEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public FileSystemEventListenerActionEnumManager
		{
		public:
			std::string convert_enum_to_string(const FileSystemEventListenerAction&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(FileSystemEventListenerAction::CREATED), std::runtime_error);
	}

	TEST_F(FileSystemEventListenerActionEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		FileSystemEventListenerActionEnumManagerConfigurations configurations;
		configurations.type = FileSystemEventListenerAction::DELETED;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(FileSystemEventListenerAction::DELETED);
		});

		EXPECT_EQ(future_result.get(), "DELETED");
	}

	TEST_F(FileSystemEventListenerActionEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(FileSystemEventListenerAction::DELETED);
					FileSystemEventListenerAction result = manager.convert_string_to_enum(converted);
					if (result == FileSystemEventListenerAction::DELETED)
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

	TEST_F(FileSystemEventListenerActionEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		FileSystemEventListenerActionEnumManager& first_instance = SingletonManager::get_singleton<FileSystemEventListenerActionEnumManager>();
		FileSystemEventListenerActionEnumManager& second_instance = SingletonManager::get_singleton<FileSystemEventListenerActionEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		FileSystemEventListenerActionEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("CREATED", FileSystemEventListenerAction::CREATED),
			std::make_pair("DELETED", FileSystemEventListenerAction::DELETED),
			std::make_pair("MODIFIED",FileSystemEventListenerAction::MODIFIED),
			std::make_pair("RENAMED",FileSystemEventListenerAction::RENAMED),
			std::make_pair("MOVED",FileSystemEventListenerAction::MOVED),
			std::make_pair("METADATA_CHANGED",FileSystemEventListenerAction::METADATA_CHANGED),
			std::make_pair("UNKNOWN",FileSystemEventListenerAction::UNKNOWN),
			std::make_pair("NONE",FileSystemEventListenerAction::NONE),
			std::make_pair("", FileSystemEventListenerAction::NONE),
			std::make_pair("INVALID", FileSystemEventListenerAction::NONE)
		)
	);

	TEST_P(FileSystemEventListenerActionEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		FileSystemEventListenerAction expected = param.second;

		FileSystemEventListenerAction result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		FileSystemEventListenerActionEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			FileSystemEventListenerAction::CREATED,
			FileSystemEventListenerAction::DELETED,
			FileSystemEventListenerAction::MODIFIED,
			FileSystemEventListenerAction::RENAMED,
			FileSystemEventListenerAction::MOVED,
			FileSystemEventListenerAction::METADATA_CHANGED,
			FileSystemEventListenerAction::UNKNOWN,
			FileSystemEventListenerAction::NONE
		)
	);

	TEST_P(FileSystemEventListenerActionEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		FileSystemEventListenerAction input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case FileSystemEventListenerAction::CREATED: EXPECT_EQ(result, "CREATED"); break;
			case FileSystemEventListenerAction::DELETED: EXPECT_EQ(result, "DELETED"); break;
			case FileSystemEventListenerAction::MODIFIED: EXPECT_EQ(result,"MODIFIED"); break;
			case FileSystemEventListenerAction::RENAMED: EXPECT_EQ(result,"RENAMED"); break;
			case FileSystemEventListenerAction::MOVED: EXPECT_EQ(result,"MOVED"); break;
			case FileSystemEventListenerAction::METADATA_CHANGED: EXPECT_EQ(result,"METADATA_CHANGED"); break;
			case FileSystemEventListenerAction::UNKNOWN: EXPECT_EQ(result,"UNKNOWN"); break;
			case FileSystemEventListenerAction::NONE: EXPECT_EQ(result,"NONE"); break;
		}
	}
}

#endif
