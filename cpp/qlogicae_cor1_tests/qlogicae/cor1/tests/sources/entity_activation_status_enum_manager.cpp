#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EntityActivationStatusEnumManager \
	)

#include "../includes/entity_activation_status_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(EntityActivationStatusEnumManagerTest, Should_ReturnNone_When_InvalidString)
	{
		std::string invalid_string = "INVALID_VALUE";
		EntityActivationStatus result = manager.convert_string_to_enum(invalid_string);
		EXPECT_EQ(result, EntityActivationStatus::NONE);
	}

	TEST_F(EntityActivationStatusEnumManagerTest, Should_ReturnNoneString_When_RuntimeExecutionDisabled)
	{
		EntityActivationStatusEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		std::string converted = manager.convert_enum_to_string(EntityActivationStatus::INACTIVE);
		EXPECT_EQ(converted, "NONE");
	}

	TEST_F(EntityActivationStatusEnumManagerTest, Should_ReturnNoneEnum_When_RuntimeExecutionDisabled)
	{
		EntityActivationStatusEnumManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);
		EntityActivationStatus result = manager.convert_string_to_enum("INACTIVE");
		EXPECT_EQ(result, EntityActivationStatus::NONE);
	}

	TEST_F(EntityActivationStatusEnumManagerTest, Should_HandleThreadSafetyDisabled)
	{
		EntityActivationStatusEnumManagerConfigurations configurations;
		configurations.is_thread_safety_handling_enabled = false;
		manager.setup(configurations);

		std::string converted = manager.convert_enum_to_string(EntityActivationStatus::ACTIVE);
		EXPECT_EQ(converted, "ACTIVE");

		EntityActivationStatus result = manager.convert_string_to_enum("ACTIVE");
		EXPECT_EQ(result, EntityActivationStatus::ACTIVE);
	}

	TEST_F(EntityActivationStatusEnumManagerTest, Should_HandleExceptionsGracefully)
	{
		class ExceptionThrower : public EntityActivationStatusEnumManager
		{
		public:
			std::string convert_enum_to_string(const EntityActivationStatus&)
			{
				throw std::runtime_error("forced exception");
			}
		};

		ExceptionThrower test_manager;
		EXPECT_THROW(test_manager.convert_enum_to_string(EntityActivationStatus::INACTIVE), std::runtime_error);
	}

	TEST_F(EntityActivationStatusEnumManagerTest, Should_HandleAsyncConversionWithDifferentConfigurations)
	{
		EntityActivationStatusEnumManagerConfigurations configurations;
		configurations.type = EntityActivationStatus::INACTIVE;
		manager.setup(configurations);

		auto future_result = std::async(std::launch::async, [&]()
		{
			return manager.convert_enum_to_string(EntityActivationStatus::INACTIVE);
		});

		EXPECT_EQ(future_result.get(), "INACTIVE");
	}

	TEST_F(EntityActivationStatusEnumManagerTest, Should_SupportHighConcurrencyStressTest)
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
					std::string converted = manager.convert_enum_to_string(EntityActivationStatus::INACTIVE);
					EntityActivationStatus result = manager.convert_string_to_enum(converted);
					if (result == EntityActivationStatus::INACTIVE)
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

	TEST_F(EntityActivationStatusEnumManagerTest, Should_ReturnSingletonInstanceConsistently)
	{
		EntityActivationStatusEnumManager& first_instance = SingletonManager::get_singleton<EntityActivationStatusEnumManager>();
		EntityActivationStatusEnumManager& second_instance = SingletonManager::get_singleton<EntityActivationStatusEnumManager>();
		EXPECT_EQ(&first_instance, &second_instance);
	}

	INSTANTIATE_TEST_CASE_P(
		StringToEnumConversions,
		EntityActivationStatusEnumManagerParameterizedTest,
		::testing::Values(
			std::make_pair("ACTIVE", EntityActivationStatus::ACTIVE),
			std::make_pair("INACTIVE", EntityActivationStatus::INACTIVE),
			std::make_pair("PENDING", EntityActivationStatus::PENDING),
			std::make_pair("NONE", EntityActivationStatus::NONE),
			std::make_pair("", EntityActivationStatus::NONE),
			std::make_pair("INVALID", EntityActivationStatus::NONE)
		)
	);

	TEST_P(EntityActivationStatusEnumManagerParameterizedTest, Should_ConvertStringToEnumCorrectly)
	{
		auto param = GetParam();
		std::string input = param.first;
		EntityActivationStatus expected = param.second;

		EntityActivationStatus result = manager.convert_string_to_enum(input);
		EXPECT_EQ(result, expected);
	}

	INSTANTIATE_TEST_CASE_P(
		EnumToStringConversions,
		EntityActivationStatusEnumManagerEnumToStringParameterizedTest,
		::testing::Values(
			EntityActivationStatus::ACTIVE,
			EntityActivationStatus::INACTIVE,
			EntityActivationStatus::NONE
		)
	);

	TEST_P(EntityActivationStatusEnumManagerEnumToStringParameterizedTest, Should_ConvertEnumToStringCorrectly)
	{
		EntityActivationStatus input = GetParam();
		std::string result = manager.convert_enum_to_string(input);

		switch (input)
		{
			case EntityActivationStatus::ACTIVE: EXPECT_EQ(result, "ACTIVE"); break;
			case EntityActivationStatus::INACTIVE: EXPECT_EQ(result, "INACTIVE"); break;
			case EntityActivationStatus::PENDING: EXPECT_EQ(result, "PENDING"); break;
			case EntityActivationStatus::NONE: EXPECT_EQ(result, "NONE"); break;
		}
	}
}

#endif
