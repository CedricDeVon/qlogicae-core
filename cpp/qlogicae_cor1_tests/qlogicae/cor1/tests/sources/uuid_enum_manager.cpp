#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		UuidEnumManager \
	)

#include "../includes/uuid_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(UuidEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		Uuid result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, Uuid::NONE);
	}

	TEST_F(UuidEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		UuidEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(Uuid::V4);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(UuidEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		UuidEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		Uuid result = manager.convert_string_to_enum("V4");
		EXPECT_EQ(result, Uuid::NONE);
	}

	TEST_F(UuidEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		UuidEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(Uuid::V4);
		EXPECT_EQ(converted, "V4");

		Uuid result = manager.convert_string_to_enum("V4");
		EXPECT_EQ(result, Uuid::V4);
	}

	TEST_F(UuidEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public UuidEnumManager
		{
		public:
			std::string convert_enum_to_string(const Uuid&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(Uuid::V4), std::runtime_error);
	}

	TEST_F(UuidEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		UuidEnumManagerConfigurations configurations;
		configurations.type = Uuid::V4;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
			{
				return manager.convert_enum_to_string(Uuid::V4);
			});

		EXPECT_EQ(future_result.get(), "V4");
	}

	TEST_F(UuidEnumManagerTest, Should_SupportHighConcurrencyStressTest)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = true;

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
						std::string converted = manager.convert_enum_to_string(Uuid::V4);
						Uuid result = manager.convert_string_to_enum(converted);
						if (result == Uuid::V4)
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

	TEST_F(UuidEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		UuidEnumManager& first_instance = SingletonManager::get_singleton<UuidEnumManager>();
		UuidEnumManager& second_instance = SingletonManager::get_singleton<UuidEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		UuidEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("V4", Uuid::V4),
			std::make_pair("NONE", Uuid::NONE),
			std::make_pair("", Uuid::NONE),
			std::make_pair("INVALID", Uuid::NONE)
		)
	);

	TEST_P(UuidEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		Uuid expected = param.second;

		Uuid result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		UuidEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			Uuid::V4,
			Uuid::NONE
		)
	);

	TEST_P(UuidEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		Uuid input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
		case Uuid::V4: EXPECT_EQ(result, "V4"); break;
		case Uuid::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
