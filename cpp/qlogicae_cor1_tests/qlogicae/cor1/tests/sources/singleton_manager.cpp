#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SingletonManager \
	)

#include "../includes/singleton_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
    TEST_F(
        SingletonManagerTest,
        Should_ReturnSameReference_Expect_SameAddress_When_GetSingletonManager
    )
    {
        SingletonManager& first_reference =
            SingletonManager::get_this_singleton();

        SingletonManager& second_reference =
            SingletonManager::get_this_singleton();

        ASSERT_EQ(
            static_cast<void*>(&first_reference),
            static_cast<void*>(&second_reference)
        );
    }

    TEST_F(
        SingletonManagerTest,
        Should_ReturnTrue_Expect_Success_When_ConstructCalled
    )
    {
        SingletonManager instance_manager;
            

        bool result = instance_manager.construct();

        ASSERT_TRUE(result);
    }

    TEST_F(
        SingletonManagerTest,
        Should_ReturnTrue_Expect_Success_When_DestructCalled
    )
    {
        SingletonManager instance_manager;
            

        bool result = instance_manager.destruct();

        ASSERT_TRUE(result);
    }

    TEST_F(
        SingletonManagerTest,
        Should_ReturnSameTypedInstance_Expect_SameAddress_When_GetInstanceCalled
    )
    {
        SingletonManager instance_manager;
            

        int& first_instance =
            SingletonManager::get_singleton<int>();

        int& second_instance =
            SingletonManager::get_singleton<int>();

        ASSERT_EQ(
            static_cast<void*>(&first_instance),
            static_cast<void*>(&second_instance)
        );
    }

    TEST_F(
        SingletonManagerTest,
        Should_ReturnDifferentTypedInstances_Expect_DifferentAddresses_When_GetInstanceCalled
    )
    {
        SingletonManager instance_manager;
            

        int& integer_instance =
            SingletonManager::get_singleton<int>();

        double& double_instance =
            SingletonManager::get_singleton<double>();

        ASSERT_NE(
            static_cast<void*>(&integer_instance),
            static_cast<void*>(&double_instance)
        );
    }

    TEST_F(
        SingletonManagerTest,
        Should_CompleteSuccessfully_Expect_NoException_When_CalledAsynchronously
    )
    {
		SingletonManager instance_manager;

        std::future<SingletonManager*> async_result =
            std::async(
                std::launch::async,
                [&instance_manager]
                {                                           
                    instance_manager.construct();

                    return static_cast<SingletonManager*>(&instance_manager);
                }
            );

        SingletonManager* result_pointer = async_result.get();

        ASSERT_NE(result_pointer, nullptr);
    }

    TEST_F(
        SingletonManagerTest,
        Should_ExecuteConcurrently_Expect_NoDataRace_When_MultipleThreadsCallGetInstance
    )
    {
        std::atomic<bool> execution_completed{ true };

        std::vector<std::thread> worker_threads;

        std::size_t const THREAD_COUNT = static_cast<std::size_t>(16);

        for (std::size_t index = 0; index < THREAD_COUNT; ++index)
        {
            worker_threads.emplace_back(
                [&execution_completed]
                {
                    SingletonManager instance_manager;
                        

                    int& instance_value =
                        SingletonManager::get_singleton<int>();

                    instance_value = static_cast<int>(1);

                    execution_completed.store(
                        execution_completed.load(std::memory_order_acquire),
                        std::memory_order_release
                    );
                }
            );
        }

        for (std::thread& worker_thread : worker_threads)
        {
            worker_thread.join();
        }

        ASSERT_TRUE(execution_completed.load());
    }

    TEST_F(
        SingletonManagerTest,
        Should_CompleteUnderLoad_Expect_NoFailure_When_StressTested
    )
    {
        SingletonManager instance_manager;
            

        std::size_t const ITERATION_COUNT =
            static_cast<std::size_t>(1'000'000);

        bool is_successful = false;

        for (std::size_t index = 0; index < ITERATION_COUNT; ++index)
        {
            is_successful = instance_manager.construct();
            is_successful = instance_manager.destruct();
        }

        ASSERT_TRUE(is_successful);
    }

    TEST_F(
        SingletonManagerTest,
        Should_NotThrow_Expect_NoException_When_RepeatedCallsMade
    )
    {
        SingletonManager instance_manager;
            

        ASSERT_NO_THROW(
            {
                for (std::size_t index = 0;
                     index < static_cast<std::size_t>(1000);
                     ++index)
                {
                    SingletonManager::get_singleton<int>();
                    SingletonManager::get_singleton<double>();
                }
            }
        );
    }
	    TEST_P(
        SingletonManagerStructParameterizedTest,
        Should_PersistAssignedValue_Expect_SameValue_When_Reaccessed
    )
    {
        TestPlainStruct& instance =
            SingletonManager::get_singleton<TestPlainStruct>();

        instance.value = GetParam();

        TestPlainStruct& reaccessed =
            SingletonManager::get_singleton<TestPlainStruct>();

        ASSERT_EQ(
            instance.value,
            reaccessed.value
        );
    }

    TEST_P(
        SingletonManagerStructParameterizedTest,
        Should_RemainStableAcrossMultipleWrites_Expect_SameAddress
    )
    {
        TestPlainStruct& first =
            SingletonManager::get_singleton<TestPlainStruct>();

        first.value = GetParam();

        TestPlainStruct& second =
            SingletonManager::get_singleton<TestPlainStruct>();

        second.value = GetParam() + 1;

        ASSERT_EQ(
            static_cast<void*>(&first),
            static_cast<void*>(&second)
        );
    }

    TEST_P(
        SingletonManagerClassParameterizedTest,
        Should_PersistAssignedValue_Expect_SameValue_When_Reaccessed
    )
    {
        TestPlainClass& instance =
            SingletonManager::get_singleton<TestPlainClass>();

        instance.value = GetParam();

        TestPlainClass& reaccessed =
            SingletonManager::get_singleton<TestPlainClass>();

        ASSERT_EQ(
            instance.value,
            reaccessed.value
        );
    }

    TEST_P(
        SingletonManagerClassParameterizedTest,
        Should_RemainStableAcrossMultipleWrites_Expect_SameAddress
    )
    {
        TestPlainClass& first =
            SingletonManager::get_singleton<TestPlainClass>();

        first.value = GetParam();

        TestPlainClass& second =
            SingletonManager::get_singleton<TestPlainClass>();

        second.value = GetParam() * 2;

        ASSERT_EQ(
            static_cast<void*>(&first),
            static_cast<void*>(&second)
        );
    }

    TEST_P(
        SingletonManagerEnumParameterizedTest,
        Should_PersistAssignedEnum_Expect_SameValue_When_Reaccessed
    )
    {
        TestPlainEnum& instance =
            SingletonManager::get_singleton<TestPlainEnum>();

        instance = GetParam();

        TestPlainEnum& reaccessed =
            SingletonManager::get_singleton<TestPlainEnum>();

        ASSERT_EQ(
            instance,
            reaccessed
        );
    }

    TEST_P(
        SingletonManagerEnumParameterizedTest,
        Should_OverwriteEnumValue_Expect_LastAssignment
    )
    {
        TestPlainEnum& instance =
            SingletonManager::get_singleton<TestPlainEnum>();

        instance = TestPlainEnum::ZERO;
        instance = GetParam();

        TestPlainEnum& reaccessed =
            SingletonManager::get_singleton<TestPlainEnum>();

        ASSERT_EQ(
            reaccessed,
            GetParam()
        );
    }

    TEST_P(
        SingletonManagerMixedTypeParameterizedTest,
        Should_PreserveIsolationBetweenTypes_Expect_IndependentValues
    )
    {
        TestPlainStruct& struct_instance =
            SingletonManager::get_singleton<TestPlainStruct>();

        TestPlainClass& class_instance =
            SingletonManager::get_singleton<TestPlainClass>();

        struct_instance.value = GetParam();
        class_instance.value = GetParam() + 10;

        ASSERT_NE(
            struct_instance.value,
            class_instance.value
        );
    }

    TEST_P(
        SingletonManagerMixedTypeParameterizedTest,
        Should_MaintainAddressStability_AcrossRepeatedAccess
    )
    {
        TestPlainStruct& struct_first =
            SingletonManager::get_singleton<TestPlainStruct>();

        TestPlainStruct& struct_second =
            SingletonManager::get_singleton<TestPlainStruct>();

        TestPlainClass& class_first =
            SingletonManager::get_singleton<TestPlainClass>();

        TestPlainClass& class_second =
            SingletonManager::get_singleton<TestPlainClass>();

        ASSERT_EQ(
            static_cast<void*>(&struct_first),
            static_cast<void*>(&struct_second)
        );

        ASSERT_EQ(
            static_cast<void*>(&class_first),
            static_cast<void*>(&class_second)
        );
    }

    INSTANTIATE_TEST_CASE_P(
        ExtendedStructTypeInstantiation,
        SingletonManagerStructParameterizedTest,
        ::testing::Values(
            static_cast<int>(-100),
            static_cast<int>(0),
            static_cast<int>(999)
        )
    );

    INSTANTIATE_TEST_CASE_P(
        ExtendedClassTypeInstantiation,
        SingletonManagerClassParameterizedTest,
        ::testing::Values(
            static_cast<int>(-10),
            static_cast<int>(10),
            static_cast<int>(1000)
        )
    );

    INSTANTIATE_TEST_CASE_P(
        ExtendedEnumTypeInstantiation,
        SingletonManagerEnumParameterizedTest,
        ::testing::Values(
            TestPlainEnum::ZERO,
            TestPlainEnum::ONE
        )
    );

    INSTANTIATE_TEST_CASE_P(
        ExtendedMixedTypeInstantiation,
        SingletonManagerMixedTypeParameterizedTest,
        ::testing::Values(
            static_cast<int>(1),
            static_cast<int>(42),
            static_cast<int>(256)
        )
    );

    TEST_F(
        SingletonManagerTest,
        Should_AllowGetSingletonBeforeConstruct_Expect_StableInstance
    )
    {
        int& first =
            SingletonManager::get_singleton<int>();

        int& second =
            SingletonManager::get_singleton<int>();

        ASSERT_EQ(
            static_cast<void*>(&first),
            static_cast<void*>(&second)
        );
    }

    TEST_F(
        SingletonManagerTest,
        Should_ReturnTrue_When_ConstructCalledMultipleTimes
    )
    {
        SingletonManager manager;
            

        ASSERT_TRUE(manager.construct());
        ASSERT_TRUE(manager.construct());
    }

    TEST_F(
        SingletonManagerTest,
        Should_ReturnTrue_When_DestructCalledWithoutConstruct
    )
    {
        SingletonManager manager;
            

        ASSERT_TRUE(manager.destruct());
    }

    TEST_F(
        SingletonManagerTest,
        Should_ResetStateSuccessfully_When_ResetCalledRepeatedly
    )
    {
        SingletonManager manager;
            
        ASSERT_TRUE(manager.reset());
        ASSERT_TRUE(manager.reset());
    }

    TEST_F(
        SingletonManagerTest,
        Should_PreserveSingletonIdentity_Across_ConstructDestructCycles
    )
    {
        SingletonManager manager;
            

        int& first =
            SingletonManager::get_singleton<int>();

        manager.construct();
        manager.destruct();
        manager.construct();

        int& second =
            SingletonManager::get_singleton<int>();

        ASSERT_EQ(
            static_cast<void*>(&first),
            static_cast<void*>(&second)
        );
    }

    TEST_F(
        SingletonManagerTest,
        Should_InvokeDestructor_OnProgramTermination
    )
    {
        {
            DestructionTracker& instance =
                SingletonManager::get_singleton<DestructionTracker>();

            static_cast<void>(instance);
        }

        ASSERT_GE(
            DestructionTracker::destruction_count.load(),
            0
        );
    }

    TEST_F(
        SingletonManagerTest,
        Should_MaintainOrdering_When_ConstructThen_DestructCalled
    )
    {
        SingletonManager manager;
            

        ASSERT_TRUE(manager.construct());
        ASSERT_TRUE(manager.destruct());
    }

    TEST_F(
        SingletonManagerTest,
        Should_MaintainOrdering_When_DestructThen_ConstructCalled
    )
    {
        SingletonManager manager;
            

        ASSERT_TRUE(manager.destruct());
        ASSERT_TRUE(manager.construct());
    }

    TEST_F(
        SingletonManagerTest,
        Should_HandleResetBetweenConstructAndDestruct
    )
    {
        SingletonManager manager;
            

        ASSERT_TRUE(manager.construct());
        ASSERT_TRUE(manager.reset());
        ASSERT_TRUE(manager.destruct());
    }

    TEST_F(
        SingletonManagerTest,
        Should_NotThrow_When_ResetCalledWithoutPriorOperations
    )
    {
        SingletonManager manager;
            

        ASSERT_NO_THROW(
            {
                manager.reset();
            }
        );
    }

	TEST_F(
		SingletonManagerTest,
		Should_NotDeadlock_When_MultipleThreadsConstructAndDestruct
	)
	{
		std::vector<std::thread> threads;

		for (int i = 0; i < 32; ++i)
		{
			threads.emplace_back(
				[]
				{
					SingletonManager manager;						

					manager.construct();
					manager.reset();
					manager.destruct();
				}
			);
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		SUCCEED();
	}

	TEST_F(
		SingletonManagerTest,
		Should_PreserveSingletonIdentity_UnderConcurrentLifecycleCalls
	)
	{
		int* first_address = nullptr;

		std::thread t1(
			[&first_address]
			{
				first_address =
					&SingletonManager::get_singleton<int>();
			}
		);

		std::thread t2(
			[]
			{
				SingletonManager manager;

				manager.construct();
				manager.destruct();
			}
		);

		t1.join();
		t2.join();

		int* second_address =
			&SingletonManager::get_singleton<int>();

		ASSERT_EQ(
			static_cast<void*>(first_address),
			static_cast<void*>(second_address)
		);
	}

	TEST_F(
		SingletonManagerTest,
		Should_FailToCompile_For_NonDefaultConstructibleType
	)
	{
		SUCCEED();
	}

	TEST_F(
		SingletonManagerTest,
		Should_PropagateException_When_TypeConstructorThrows
	)
	{
		ASSERT_THROW(
			{
				SingletonManager::get_singleton<ThrowingConstructor>();
			},
			std::runtime_error
		);
	}

	TEST_F(
		SingletonManagerTest,
		Should_RemainUsable_After_ExceptionDuringInstantiation
	)
	{
		try
		{
			SingletonManager::get_singleton<ThrowingConstructor>();
		}
		catch (...)
		{
		}

		int& instance =
			SingletonManager::get_singleton<int>();

		instance = 42;

		ASSERT_EQ(instance, 42);
	}

	TEST_F(
		SingletonManagerTest,
		Should_MaintainCorrectOrdering_UnderInterleavedCalls
	)
	{
		SingletonManager manager;
			

		ASSERT_TRUE(manager.construct());
		ASSERT_TRUE(manager.reset());
		ASSERT_TRUE(manager.construct());
		ASSERT_TRUE(manager.destruct());
	}

	TEST_F(
		SingletonManagerTest,
		Should_AllowConcurrentTypeInstantiation
	)
	{
		std::thread t1(
			[]
			{
				SingletonManager::get_singleton<int>() = 1;
			}
		);

		std::thread t2(
			[]
			{
				SingletonManager::get_singleton<double>() = 2.0;
			}
		);

		t1.join();
		t2.join();

		ASSERT_EQ(
			SingletonManager::get_singleton<int>(),
			1
		);

		ASSERT_EQ(
			SingletonManager::get_singleton<double>(),
			2.0
		);
	}

	TEST_F(
		SingletonManagerTest,
		Should_NotInvalidateInstances_OnReset
	)
	{
		int& first =
			SingletonManager::get_singleton<int>();

		first = 7;

		SingletonManager::get_this_singleton().reset();

		int& second =
			SingletonManager::get_singleton<int>();

		ASSERT_EQ(
			static_cast<void*>(&first),
			static_cast<void*>(&second)
		);

		ASSERT_EQ(second, 7);
	}
	TEST_F(
		SingletonManagerTest,
		Should_IgnoreIsEnabledFlag_When_GetSingletonCalled
	)
	{
		SingletonManager manager;
			

		SingletonManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;

		manager.setup(configurations);

		ASSERT_NO_THROW(
			{
				SingletonManager::get_singleton<int>();
			}
		);
	}

	TEST_F(
		SingletonManagerTest,
		Should_NotEnforceThreadSafetyFlag_OnTypedSingletonMutation
	)
	{
		SingletonManager manager;
			

		SingletonManagerConfigurations configurations;
		configurations.is_thread_safety_handling_override_enabled = true;

		manager.setup(configurations);

		std::vector<std::thread> threads;

		for (int i = 0; i < 64; ++i)
		{
			threads.emplace_back(
				[]
				{
					int& value =
						SingletonManager::get_singleton<int>();

					value++;
				}
			);
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		SUCCEED();
	}

	TEST_F(
		SingletonManagerTest,
		Should_ReturnTrue_When_DestructCalledBeforeConstruct
	)
	{
		SingletonManager manager;


		ASSERT_TRUE(
			manager.destruct()
		);
	}

	TEST_F(
		SingletonManagerTest,
		Should_ReturnTrue_When_ConstructCalledAfterDestruct
	)
	{
		SingletonManager manager;


		ASSERT_TRUE(manager.construct());
		ASSERT_TRUE(manager.destruct());
		ASSERT_TRUE(manager.construct());
	}

	TEST_F(
		SingletonManagerTest,
		Should_PreserveTypedSingletonInstances_When_ResetCalled
	)
	{
		int& first =
			SingletonManager::get_singleton<int>();

		first = 99;

		SingletonManager::get_this_singleton().reset();

		int& second =
			SingletonManager::get_singleton<int>();

		ASSERT_EQ(
			static_cast<void*>(&first),
			static_cast<void*>(&second)
		);
	}

	TEST_F(
		SingletonManagerTest,
		Should_PreserveTypedSingletonValues_When_ResetCalled
	)
	{
		int& value =
			SingletonManager::get_singleton<int>();

		value = 123;

		SingletonManager::get_this_singleton().reset();

		ASSERT_EQ(
			SingletonManager::get_singleton<int>(),
			123
		);
	}

	TEST_F(
		SingletonManagerTest,
		Should_RetryInstantiation_When_ConstructorThrows
	)
	{
		ASSERT_THROW(
			{
				SingletonManager::get_singleton<ThrowingConstructor>();
			},
			std::runtime_error
		);

		ASSERT_THROW(
			{
				SingletonManager::get_singleton<ThrowingConstructor>();
			},
			std::runtime_error
		);
	}

	TEST_F(
		SingletonManagerTest,
		Should_NotDestroyTypedSingleton_On_ManagerDestruct
	)
	{
		{
			DestructionTracker& instance =
				SingletonManager::get_singleton<DestructionTracker>();

			static_cast<void>(instance);

			SingletonManager::get_this_singleton().destruct();
		}

		ASSERT_EQ(
			DestructionTracker::destruction_count.load(),
			0
		);
	}

	TEST_F(
		SingletonManagerTest,
		Should_AllowTypedSingletonAccess_After_ManagerDestruct
	)
	{
		SingletonManager manager;


		manager.construct();
		manager.destruct();

		ASSERT_NO_THROW(
			{
				SingletonManager::get_singleton<int>();
			}
		);
	}

	TEST_F(
		SingletonManagerTest,
		Should_Allow_Concurrent_Construct_And_GetSingleton
	)
	{
		SingletonManager manager;


		std::thread t1(
			[&]
			{
				manager.construct();
			}
		);

		std::thread t2(
			[]
			{
				SingletonManager::get_singleton<int>();
			}
		);

		t1.join();
		t2.join();

		SUCCEED();
	}

	TEST_F(
		SingletonManagerTest,
		Should_ReturnFalse_When_RuntimeExecutionDisabledForUtilityHandling
	)
	{
		SingletonManagerConfigurations configurations;
		configurations.is_utility_runtime_execution_handling_enabled = false;
		configurations.is_runtime_execution_handling_override_enabled = false;

		SingletonManager manager;
		manager.setup(configurations);

		ASSERT_TRUE(manager.construct());
		ASSERT_TRUE(manager.destruct());

		manager.reset();
	}

	TEST_F(
		SingletonManagerTest,
		Should_NotAcquireMutex_When_ThreadSafetyDisabledForUtilityHandling
	)
	{
		SingletonManagerConfigurations configurations;
		configurations.is_utility_thread_safety_handling_enabled = false;
		configurations.is_thread_safety_handling_override_enabled = false;

		SingletonManager manager;

		ASSERT_TRUE(manager.construct());
		ASSERT_TRUE(manager.destruct());

		manager.reset();
	}

	TEST_F(
		SingletonManagerTest,
		Should_EnableEdgeCaseHandling_When_OverrideEnabled
	)
	{
		SingletonManagerConfigurations configurations;
		configurations.is_edge_case_handling_override_enabled = true;
		configurations.is_utility_edge_case_handling_enabled = false;
		configurations.is_feature_edge_case_handling_enabled = false;
		configurations.is_error_edge_case_handling_enabled = false;

		SingletonManager manager;
		manager.setup(
			configurations
		);

		ASSERT_TRUE(
			manager
				.configurations.is_edge_case_enabled_for_utility_handling()
		);

		ASSERT_TRUE(
			manager
				.configurations.is_edge_case_enabled_for_feature_handling()
		);

		ASSERT_TRUE(
			manager
				.configurations.is_edge_case_enabled_for_error_handling()
		);

		manager.reset();
	}

	TEST_F(
		SingletonManagerTest,
		Should_HandleExceptions_From_ConstructAndDestruct
	)
	{
		struct ExceptionManager : SingletonManager
		{
			bool construct()
			{
				throw std::runtime_error("construct error");
			}

			bool destruct()
			{
				throw std::runtime_error("destruct error");
			}
		};

		ExceptionManager manager;

		ASSERT_THROW(manager.construct(), std::runtime_error);
		ASSERT_THROW(manager.destruct(), std::runtime_error);
	}
}

#endif
