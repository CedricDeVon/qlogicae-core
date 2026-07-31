#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEntityEnumManager \
	)

#include "../includes/file_system_entity_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(FileSystemEntityEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		FileSystemEntity result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, FileSystemEntity::NONE);
	}

	TEST_F(FileSystemEntityEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		FileSystemEntityEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(FileSystemEntity::FILE);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(FileSystemEntityEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		FileSystemEntityEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		FileSystemEntity result = manager.convert_string_to_enum("FILE");
		EXPECT_EQ(result, FileSystemEntity::NONE);
	}

	TEST_F(FileSystemEntityEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		FileSystemEntityEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(FileSystemEntity::FOLDER);
		EXPECT_EQ(converted, "FOLDER");

		FileSystemEntity result = manager.convert_string_to_enum("FOLDER");
		EXPECT_EQ(result, FileSystemEntity::FOLDER);
	}

	TEST_F(FileSystemEntityEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public FileSystemEntityEnumManager
		{
		public:
			std::string convert_enum_to_string(const FileSystemEntity&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(FileSystemEntity::ALL), std::runtime_error);
	}

	TEST_F(FileSystemEntityEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		FileSystemEntityEnumManagerConfigurations configurations;
		configurations.type = FileSystemEntity::FILE;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(FileSystemEntity::FILE);
		});

		EXPECT_EQ(future_result.get(), "FILE");
	}

	TEST_F(FileSystemEntityEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(FileSystemEntity::FOLDER);
					FileSystemEntity result = manager.convert_string_to_enum(converted);
					if (result == FileSystemEntity::FOLDER)
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

	TEST_F(FileSystemEntityEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		FileSystemEntityEnumManager& first_instance = SingletonManager::get_singleton<FileSystemEntityEnumManager>();
		FileSystemEntityEnumManager& second_instance = SingletonManager::get_singleton<FileSystemEntityEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		FileSystemEntityEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("ALL", FileSystemEntity::ALL),
			std::make_pair("FOLDER", FileSystemEntity::FOLDER),
			std::make_pair("FILE", FileSystemEntity::FILE),
			std::make_pair("NONE", FileSystemEntity::NONE),
			std::make_pair("", FileSystemEntity::NONE),
			std::make_pair("INVALID", FileSystemEntity::NONE)
		)
	);

	TEST_P(FileSystemEntityEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		FileSystemEntity expected = param.second;

		FileSystemEntity result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		FileSystemEntityEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			FileSystemEntity::ALL,
			FileSystemEntity::FOLDER,
			FileSystemEntity::FILE,
			FileSystemEntity::NONE
		)
	);

	TEST_P(FileSystemEntityEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		FileSystemEntity input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case FileSystemEntity::ALL: EXPECT_EQ(result, "ALL"); break;
			case FileSystemEntity::FOLDER: EXPECT_EQ(result, "FOLDER"); break;
			case FileSystemEntity::FILE: EXPECT_EQ(result, "FILE"); break;
			case FileSystemEntity::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
