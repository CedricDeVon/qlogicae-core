#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		UuidManager \
	)

#include "../includes/uuid_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(UuidManagerTest, Should_ReturnSameInstance_When_AccessedMultipleTimes)
	{
		auto& instance1 = SingletonManager::get_singleton<UuidManager>();
		auto& instance2 = SingletonManager::get_singleton<UuidManager>();
		ASSERT_EQ(&instance1, &instance2);
	}

	TEST_F(UuidManagerTest, Should_ConstructSuccessfully_When_Normal)
	{
		ASSERT_TRUE(manager.construct());
	}

	TEST_F(UuidManagerTest, Should_DestructSuccessfully_When_Normal)
	{
		ASSERT_TRUE(manager.destruct());
	}

	INSTANTIATE_TEST_CASE_P(
		UuidValidationVariants,
		UuidManagerIsValidTest,
		::testing::Values(
			std::make_tuple(Uuid::V4, boost::uuids::to_string(boost::uuids::random_generator()()), true),
			std::make_tuple(Uuid::V4, "", false),
			std::make_tuple(Uuid::V4, "invalid-uuid", false),
			std::make_tuple(Uuid::NONE, boost::uuids::to_string(boost::uuids::random_generator()()), false)
		)
	);

	TEST_P(UuidManagerIsValidTest, Should_ReturnBool_When_IsValid)
	{
		auto [uuid_type, value, expected] = GetParam();
		bool result = manager.is_valid(uuid_type, value);
		ASSERT_EQ(result, expected);
	}

	TEST_F(UuidManagerTest, Should_DelegateToDefaultType_When_IsValidWithoutType)
	{
		std::string valid_uuid = boost::uuids::to_string(boost::uuids::random_generator()());
		ASSERT_TRUE(manager.is_valid(valid_uuid));
	}

	TEST_F(UuidManagerTest, Should_HandleAsync_When_IsValid)
	{
		auto future_result = std::async(std::launch::async, [&]()
			{
				std::string valid_uuid = boost::uuids::to_string(boost::uuids::random_generator()());
				return manager.is_valid(valid_uuid);
			});
		ASSERT_TRUE(future_result.get());
	}

	TEST_F(UuidManagerTest, Should_HandleMultithreadedAccess_When_IsValid)
	{
		std::atomic<int> completed_count = 0;

		std::string valid_uuid1 = boost::uuids::to_string(boost::uuids::random_generator()());
		std::string valid_uuid2 = boost::uuids::to_string(boost::uuids::random_generator()());

		std::thread thread1([&]()
			{
				if (manager.is_valid(valid_uuid1)) ++completed_count;
			});

		std::thread thread2([&]()
			{
				if (manager.is_valid(valid_uuid2)) ++completed_count;
			});

		thread1.join();
		thread2.join();

		ASSERT_EQ(completed_count.load(), 2);
	}

	TEST_F(UuidManagerTest, Should_HandleStress_When_IsValidManyTimes)
	{
		for (int i = 0; i < 1000; ++i)
		{
			std::string valid_uuid = boost::uuids::to_string(boost::uuids::random_generator()());
			ASSERT_TRUE(manager.is_valid(valid_uuid));
		}
	}

	INSTANTIATE_TEST_CASE_P(
		UuidTypeVariants,
		UuidManagerGenerateUuidTest,
		::testing::Values(Uuid::V4, Uuid::NONE)
	);

	TEST_P(UuidManagerGenerateUuidTest, Should_ReturnString_When_GenerateUuid)
	{
		Uuid type = GetParam();
		std::string result = manager.generate_uuid(type);
		switch (type)
		{
			case Uuid::V4:
				ASSERT_FALSE(result.empty());
				break;

			case Uuid::NONE:
				ASSERT_TRUE(result.empty());
				break;			
		}		
	}

	TEST_F(UuidManagerTest, Should_DelegateToDefaultType_When_GenerateUuidWithoutType)
	{
		std::string result = manager.generate_uuid();
		ASSERT_FALSE(result.empty());
	}

	TEST_F(UuidManagerTest, Should_HandleAsync_When_GenerateUuid)
	{
		auto future_result = std::async(std::launch::async, [&]()
			{
				return manager.generate_uuid(Uuid::V4);
			});
		ASSERT_FALSE(future_result.get().empty());
	}

	TEST_F(UuidManagerTest, Should_HandleMultithreadedAccess_When_GenerateUuid)
	{
		std::atomic<int> completed_count = 0;

		std::thread thread1([&]()
			{
				if (!manager.generate_uuid(Uuid::V4).empty()) ++completed_count;
			});

		std::thread thread2([&]()
			{
				if (!manager.generate_uuid(Uuid::V4).empty()) ++completed_count;
			});

		thread1.join();
		thread2.join();

		ASSERT_EQ(completed_count.load(), 2);
	}

	TEST_F(UuidManagerTest, Should_HandleStress_When_GenerateUuidManyTimes)
	{
		for (int i = 0; i < 1000; ++i)
		{
			ASSERT_FALSE(manager.generate_uuid(Uuid::V4).empty());
		}
	}

	TEST_F(UuidManagerTest, Should_HandleExceptionPath_When_IsValidWithInvalidString)
	{
		std::string invalid_uuid = "this-is-not-valid";
		ASSERT_NO_THROW(manager.is_valid(Uuid::V4, invalid_uuid));
	}

	TEST_F(UuidManagerTest, Should_HandleExceptionPath_When_GenerateUuidWithUnsupportedType)
	{
		ASSERT_NO_THROW(manager.generate_uuid(Uuid::NONE));
	}

	TEST_F(UuidManagerTest, Should_SetupAndResetConfigurationsSuccessfully)
	{
		UuidManagerConfigurations new_config;
		new_config.type = Uuid::V4;
		ASSERT_TRUE(manager.setup(new_config));
		ASSERT_TRUE(manager.reset());
	}

	TEST_F(UuidManagerTest, Should_HandleException_When_ConstructThrows)
	{
		UuidManagerConfigurations original_config = manager.configurations;
		manager.configurations.is_thread_safety_handling_override_enabled = true;
		ASSERT_NO_THROW(manager.construct());
		manager.configurations = original_config;
	}

	TEST_F(UuidManagerTest, Should_HandleException_When_DestructThrows)
	{
		UuidManagerConfigurations original_config = manager.configurations;
		manager.configurations.is_thread_safety_handling_override_enabled = true;
		ASSERT_NO_THROW(manager.destruct());
		manager.configurations = original_config;
	}

	TEST_F(UuidManagerTest, Should_HandleAsyncStress_When_GenerateUuidManyTimes)
	{
		std::atomic<int> completed_count = 0;
		const int iterations = 1000;

		auto worker = [&]()
		{
			for (int i = 0; i < iterations; ++i)
			{
				if (!manager.generate_uuid(Uuid::V4).empty()) ++completed_count;
			}
		};

		auto future1 = std::async(std::launch::async, worker);
		auto future2 = std::async(std::launch::async, worker);
		auto future3 = std::async(std::launch::async, worker);

		future1.get();
		future2.get();
		future3.get();

		ASSERT_EQ(completed_count.load(), iterations * 3);
	}

	TEST_F(UuidManagerTest, Should_HandleAsyncStress_When_IsValidManyTimes)
	{
		std::atomic<int> completed_count = 0;
		const int iterations = 1000;

		auto worker = [&]()
		{
			for (int i = 0; i < iterations; ++i)
			{
				std::string uuid_value = boost::uuids::to_string(
					boost::uuids::random_generator()());
				if (manager.is_valid(uuid_value)) ++completed_count;
			}
		};

		auto future1 = std::async(std::launch::async, worker);
		auto future2 = std::async(std::launch::async, worker);
		auto future3 = std::async(std::launch::async, worker);

		future1.get();
		future2.get();
		future3.get();

		ASSERT_EQ(completed_count.load(), iterations * 3);
	}
}

#endif
