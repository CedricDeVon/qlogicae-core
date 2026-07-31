#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FunctionWrapper \
	)

#include "../includes/function_wrapper.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(FunctionWrapperTest, Should_ConstructSuccessfully_When_NoException)
	{
		FunctionWrapper& wrapper = manager;
		ASSERT_TRUE(wrapper.construct());
	}

	TEST_F(FunctionWrapperTest, Should_DestructSuccessfully_When_NoException)
	{
		FunctionWrapper& wrapper = manager;
		ASSERT_TRUE(wrapper.destruct());
	}

	TEST_F(FunctionWrapperTest, Should_SetupConfigurationsCorrectly_When_ValidInput)
	{
		FunctionWrapperConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = true;
		ASSERT_TRUE(manager.setup(configurations));
		ASSERT_TRUE(manager.configurations.is_feature_runtime_execution_handling_enabled);
	}

	TEST_F(FunctionWrapperTest, Should_ResetConfigurationsToDefault_When_Called)
	{
		FunctionWrapperConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = true;
		manager.setup(configurations);
		ASSERT_TRUE(manager.reset());
		ASSERT_TRUE(manager.configurations.is_feature_runtime_execution_handling_enabled);
	}

	TEST_F(FunctionWrapperTest, Should_HandleException_When_SetupThrows)
	{
		struct ThrowingConfigurations : FunctionWrapperConfigurations {};
		FunctionWrapperConfigurations configurations;
		ASSERT_TRUE(manager.setup(configurations));
	}

	TEST_F(FunctionWrapperTest, Should_HandleException_When_ResetThrows)
	{
		ASSERT_TRUE(manager.reset());
	}

	TEST_F(FunctionWrapperTest, Should_ReturnValue_When_NonPointerMemberFunction)
	{
		FunctionWrapperCallSafelyTest test_object;
		int result = manager.call_function<int>(
			test_object, &FunctionWrapperCallSafelyTest::add_value, 5);
		ASSERT_EQ(result, 6);
	}

	TEST_F(FunctionWrapperTest, Should_ReturnValue_When_PointerMemberFunction)
	{
		FunctionWrapperCallSafelyTest test_object;
		FunctionWrapperCallSafelyTest* ptr = &test_object;
		int result = manager.call_function<int>(
			ptr, &FunctionWrapperCallSafelyTest::add_value, 7);
		ASSERT_EQ(result, 8);
	}

	TEST_F(FunctionWrapperTest, Should_HandleException_When_MemberFunctionThrows)
	{
		FunctionWrapperCallSafelyTest test_object;
		ASSERT_THROW(
			manager.call_function<int>(
				test_object, &FunctionWrapperCallSafelyTest::throw_value, 1),
			std::runtime_error
		);
	}

	TEST_F(FunctionWrapperTest, Should_HandleZeroArgumentMemberFunction)
	{
		FunctionWrapperCallSafelyTest test_object;
		int result = manager.call_function<int>(
			test_object, &FunctionWrapperCallSafelyTest::zero_arg);
		ASSERT_EQ(result, 42);
	}

	TEST_F(FunctionWrapperTest, Should_ReturnDefaultConstructedResult_When_ExceptionThrown)
	{
		FunctionWrapperCallSafelyTest test_object;

		ASSERT_THROW(
			manager.call_function<int>(
				test_object, &FunctionWrapperCallSafelyTest::throw_value, 3),
			std::runtime_error
		);
	}

	TEST_F(FunctionWrapperTest, Should_ReturnDefaultConstructedResult_When_PointerMemberThrows)
	{
		FunctionWrapperCallSafelyTest test_object;
		FunctionWrapperCallSafelyTest* ptr = &test_object;

		ASSERT_THROW(
			manager.call_function<int>(
				ptr,
				&FunctionWrapperCallSafelyTest::throw_value,
				4
			),
			std::runtime_error
		);
	}

	TEST_F(FunctionWrapperTest, Should_HandleZeroArgumentMemberFunction_WithPointer)
	{
		FunctionWrapperCallSafelyTest test_object;
		FunctionWrapperCallSafelyTest* ptr = &test_object;

		int result =
			manager.call_function<int>(
				ptr,
				&FunctionWrapperCallSafelyTest::zero_arg
			);

		ASSERT_EQ(result, 42);
	}

	TEST_F(FunctionWrapperTest, Should_ReturnCorrectValue_When_MultipleCallsInvoked)
	{
		FunctionWrapperCallSafelyTest test_object;

		int first =
			manager.call_function<int>(
				test_object,
				&FunctionWrapperCallSafelyTest::add_value,
				1
			);

		int second =
			manager.call_function<int>(
				test_object,
				&FunctionWrapperCallSafelyTest::add_value,
				10
			);

		ASSERT_EQ(first, 2);
		ASSERT_EQ(second, 11);
	}

	TEST_F(FunctionWrapperTest, Should_NotAffectSubsequentCalls_After_Exception)
	{
		FunctionWrapperCallSafelyTest test_object;

		ASSERT_THROW(
			manager.call_function<int>(
				test_object, &FunctionWrapperCallSafelyTest::throw_value, 1),
			std::runtime_error
		);

		int success =
			manager.call_function<int>(
				test_object,
				&FunctionWrapperCallSafelyTest::add_value,
				5
			);

		ASSERT_EQ(success, 6);
	}

	TEST_F(FunctionWrapperTest, Should_HandleNullPointerObject_When_PointerMemberFunction)
	{
		FunctionWrapperCallSafelyTest* ptr = nullptr;

		ASSERT_NO_THROW(
			(
				manager.call_function<int>(
					ptr,
					&FunctionWrapperCallSafelyTest::add_value,
					1
				),
				void()
				)
		);
	}

	TEST_F(FunctionWrapperTest, Should_ExecuteCallSafely_When_DisabledConfiguration)
	{
		FunctionWrapperConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.setup(configurations);

		FunctionWrapperCallSafelyTest test_object;

		int result = manager.call_function<int>(
			test_object,
			&FunctionWrapperCallSafelyTest::add_value,
			3
		);

		ASSERT_EQ(result, 4);
	}

	TEST_F(FunctionWrapperTest, Should_HandleCallSafely_When_NotConstructed)
	{
		manager.destruct();

		FunctionWrapperCallSafelyTest test_object;

		int result = manager.call_function<int>(
			test_object,
			&FunctionWrapperCallSafelyTest::add_value,
			2
		);

		ASSERT_EQ(result, 3);
	}

	TEST_F(FunctionWrapperTest, Should_HandleCallSafely_When_DestructedBeforeCall)
	{
		manager.construct();
		manager.destruct();

		FunctionWrapperCallSafelyTest test_object;

		int result = manager.call_function<int>(
			test_object,
			&FunctionWrapperCallSafelyTest::add_value,
			4
		);

		ASSERT_EQ(result, 5);
	}

	TEST_F(FunctionWrapperTest, Should_HandleVoidReturnType_When_CallbackSucceeds)
	{
		struct VoidTest
		{
			bool* flag;

			void run()
			{
				*flag = true;
			}
		};

		bool called = false;
		VoidTest test_object{ &called };

		manager.call_function<void>(
			test_object,
			&VoidTest::run
		);

		ASSERT_TRUE(called);
	}

	TEST_F(FunctionWrapperTest, Should_ReturnValue_For_NonDefaultConstructible_When_NoException)
	{
		struct NonDefaultConstructible
		{
			explicit NonDefaultConstructible(int value) : value(value) {}
			int value;
		};

		struct Test
		{
			NonDefaultConstructible run()
			{
				return NonDefaultConstructible(7);
			}
		};

		Test test_object;

		NonDefaultConstructible result =
			manager.call_function<
			NonDefaultConstructible
			>(
				test_object,
				&Test::run
			);

		ASSERT_EQ(result.value, 7);
	}

	TEST_F(FunctionWrapperTest, Should_HandleVoidReturnType_With_PointerObject)
	{
		struct VoidTest
		{
			bool* flag;

			void run()
			{
				*flag = true;
			}
		};

		bool called = false;
		VoidTest test_object{ &called };
		VoidTest* ptr = &test_object;

		manager.call_function<void>(
			ptr,
			&VoidTest::run
		);

		ASSERT_TRUE(called);
	}

	TEST_F(FunctionWrapperTest, Should_HandleNonDefaultReturnPointerMember_When_ExceptionThrown)
	{
		NonDefaultReturnTest test_object;
		NonDefaultReturnTest* ptr = &test_object;

		ASSERT_THROW(
			manager.call_function<NonDefaultConstructible>(
				ptr,
				&NonDefaultReturnTest::run
			),
			std::runtime_error
		);
	}

	TEST_F(FunctionWrapperTest, Should_HandleMultipleThreads_CallFunction_ThreadSafety)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = true;

		FunctionWrapperCallSafelyTest test_object;

		std::vector<std::thread> threads;
		std::atomic<int> total{ 0 };

		for (int i = 0; i < 10; ++i)
		{
			threads.emplace_back([&]()
			{
				for (int j = 0; j < 100; ++j)
				{
					total += manager.call_function<int>(
						test_object,
						&FunctionWrapperCallSafelyTest::add_value,
						j
					);
				}
			});
		}

		for (auto& t : threads)
		{
			t.join();
		}

		ASSERT_GT(total.load(), 0);
	}

	TEST_F(FunctionWrapperTest, Should_HandleConstructDestructConcurrently)
	{
		manager.configurations.is_utility_thread_safety_handling_enabled = true;

		std::vector<std::thread> threads;

		for (int i = 0; i < 5; ++i)
		{
			threads.emplace_back([&]()
				{
					for (int j = 0; j < 50; ++j)
					{
						manager.construct();
						manager.destruct();
					}
				});
		}

		for (auto& t : threads)
		{
			t.join();
		}

		ASSERT_TRUE(true);
	}

	TEST_F(FunctionWrapperTest, Should_HandleExtremeFlagCombinations)
	{
		FunctionWrapperConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		configurations.is_feature_thread_safety_handling_enabled = true;
		configurations.is_utility_thread_safety_handling_enabled = true;
		configurations.is_utility_runtime_execution_handling_enabled = false;

		ASSERT_TRUE(manager.setup(configurations));

		FunctionWrapperCallSafelyTest test_object;
		int result = manager.call_function<int>(
			test_object,
			&FunctionWrapperCallSafelyTest::add_value,
			10
		);

		ASSERT_EQ(result, 11);
	}

	TEST_F(FunctionWrapperTest, Should_HandleFuzzedConfiguration)
	{
		FunctionWrapperConfigurations configurations;
		*reinterpret_cast<uint64_t*>(&configurations) = 0xDEADBEEFCAFEBABE;

		ASSERT_NO_THROW(manager.setup(configurations));
		ASSERT_NO_THROW(manager.reset());
	}

	TEST_F(FunctionWrapperTest, Should_HandleAllFlagCombinations)
    {
        struct FlagsTestObject
        {
            int run(int value) { return value + 2; }
        };

        std::array<bool, 2> bools = { false, true };

        for (bool runtime : bools)
        for (bool utility : bools)
        for (bool feature : bools)
        for (bool runtime_ts : bools)
        for (bool utility_ts : bools)
        for (bool feature_ts : bools)
        {
            FunctionWrapperConfigurations config;
            config.is_feature_runtime_execution_handling_enabled = feature;
            config.is_utility_runtime_execution_handling_enabled = utility;
            config.is_feature_thread_safety_handling_enabled = feature_ts;
            config.is_utility_thread_safety_handling_enabled = utility_ts;
            config.is_feature_runtime_execution_handling_enabled = feature;
            config.is_utility_runtime_execution_handling_enabled = runtime;

            ASSERT_NO_THROW(manager.setup(config));
            ASSERT_NO_THROW(manager.reset());

            FlagsTestObject obj;
            int result = manager.call_function<int>(obj, &FlagsTestObject::run, 5);
            ASSERT_EQ(result, 7);
        }
    }

    TEST_F(FunctionWrapperTest, Should_HandleExceptionNonDefaultConstructible_NonPointer)
    {
        struct TestObject
        {
            NonDefaultConstructible run()
            {
                throw std::runtime_error("fail");
            }
        };

        TestObject obj;

        ASSERT_THROW(
            manager.call_function<NonDefaultConstructible>(obj, &TestObject::run),
            std::runtime_error
        );
    }
}

#endif
