#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ValidationManager \
	)

#include "../includes/validation_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(ValidationManagerTest, Should_ConstructSuccessfully_When_Normal)
	{
		ASSERT_TRUE(manager.construct());
	}

	TEST_F(ValidationManagerTest, Should_DestructSuccessfully_When_Normal)
	{
		ASSERT_TRUE(manager.destruct());
	}

	TEST_F(ValidationManagerTest, Should_HandleException_When_ConstructThrows)
	{
		auto& configurations = manager.configurations;
		configurations.is_utility_thread_safety_handling_enabled = false;
		ASSERT_NO_THROW(manager.construct());
	}

	TEST_F(ValidationManagerTest, Should_HandleException_When_DestructThrows)
	{
		auto& configurations = manager.configurations;
		configurations.is_utility_thread_safety_handling_enabled = false;
		ASSERT_NO_THROW(manager.destruct());
	}

	TEST_F(ValidationManagerTest, Should_BeCallableMultipleTimes_When_ConstructAndDestruct)
	{
		for (int i = 0; i < 5; ++i)
		{
			ASSERT_TRUE(manager.construct());
			ASSERT_TRUE(manager.destruct());
		}
	}

	INSTANTIATE_TEST_CASE_P(
		CallbackVariants,
		ValidationManagerValidateTest,
		::testing::Values(
			[]() { return true; },
			[]() { return false; }
		)
	);

	TEST_P(ValidationManagerValidateTest, Should_ReturnBoolOrHandleException_When_ValidateWithCallback)
	{
		auto callback = GetParam();
		if (callback)
		{
			ASSERT_NO_THROW(manager.validate(callback));
		}
		else
		{
			ASSERT_FALSE(manager.validate(callback));
		}
	}

	TEST_F(ValidationManagerTest, Should_ReturnFalse_When_ValidateWithoutCallback)
	{
		manager.configurations.conditional_callback = nullptr;
		ASSERT_FALSE(manager.validate());
	}

	TEST_F(ValidationManagerTest, Should_HandleAsync_When_Validate)
	{
		auto future_result = std::async(std::launch::async, [&]()
			{
				return manager.validate([]() { return true; });
			});
		ASSERT_TRUE(future_result.get());
	}

	TEST_F(ValidationManagerTest, Should_HandleMultithreadedAccess_When_Validate)
	{
		std::atomic<int> completed_count = 0;

		std::thread thread1([&]()
			{
				if (manager.validate([]() { return true; })) ++completed_count;
			});

		std::thread thread2([&]()
			{
				if (manager.validate([]() { return true; })) ++completed_count;
			});

		thread1.join();
		thread2.join();

		ASSERT_EQ(completed_count.load(), 2);
	}

	TEST_F(ValidationManagerTest, Should_HandleStress_When_ValidateManyTimes)
	{
		for (int i = 0; i < 1000; ++i)
		{
			ASSERT_TRUE(manager.validate([]() { return true; }));
		}
	}

	TEST_F(ValidationManagerTest, Should_HandleCombinedAsyncStress_When_ValidateManyTimes)
	{
		std::vector<std::future<bool>> futures;
		for (int i = 0; i < 50; ++i)
		{
			futures.push_back(std::async(std::launch::async, [&]()
				{
					bool result = true;
					for (int j = 0; j < 20; ++j)
					{
						result &= manager.validate([]() { return true; });
					}
					return result;
				}));
		}

		for (auto& future : futures)
		{
			ASSERT_TRUE(future.get());
		}
	}

	TEST_F(ValidationManagerTest, Should_HandleExceptionPath_When_ValidateCallbackThrows)
	{
		ASSERT_THROW(manager.validate([]() -> bool { throw std::runtime_error("fail"); }), std::runtime_error);
		ASSERT_NO_THROW(manager.validate());
	}

	TEST_F(ValidationManagerTest, Should_UpdateConfigurations_When_SetupCalled)
	{
		ValidationManagerConfigurations new_config;
		new_config.conditional_callback = []() { return false; };
		ASSERT_TRUE(manager.setup(new_config));
		ASSERT_FALSE(manager.validate());
	}

	TEST_F(ValidationManagerTest, Should_ResetConfigurations_When_ResetCalled)
	{
		ValidationManagerConfigurations new_config;
		new_config.conditional_callback = []() { return false; };
		ASSERT_TRUE(manager.setup(new_config));
		ASSERT_TRUE(manager.reset());
		ASSERT_TRUE(manager.validate());
	}

	TEST_F(ValidationManagerTest, Should_HandleMultithreadedAccess_When_SetupAndResetCalledConcurrently)
	{
		std::atomic<int> completed_count = 0;
		ValidationManagerConfigurations new_config;
		new_config.conditional_callback = []() { return true; };

		std::thread thread1([&]()
			{
				if (manager.setup(new_config)) ++completed_count;
			});

		std::thread thread2([&]()
			{
				if (manager.reset()) ++completed_count;
			});

		thread1.join();
		thread2.join();

		ASSERT_EQ(completed_count.load(), 2);
	}

	TEST_F(ValidationManagerTest, Should_HandleEmptyCallbackEdgeCase_When_Validate)
	{
		manager.configurations.conditional_callback = nullptr;
		ASSERT_FALSE(manager.validate());
	}

	TEST_F(ValidationManagerTest, Should_HandleSequentialConstructDestructEdgeCase)
	{
		for (int i = 0; i < 10; ++i)
		{
			ASSERT_TRUE(manager.construct());
			ASSERT_TRUE(manager.destruct());
		}
	}
}

#endif
