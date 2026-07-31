#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		MutexManager \
	)

#include "../includes/mutex_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
    TEST_F(MutexManagerTest, Should_ConstructSuccessfully_When_Called)
    {
        ASSERT_TRUE(mutex_manager_instance.construct());
    }

    TEST_F(MutexManagerTest, Should_DestructSuccessfully_When_Called)
    {
        ASSERT_TRUE(mutex_manager_instance.destruct());
    }

    TEST_F(MutexManagerTest, Should_HandleMultipleConstructDestructCalls_When_CalledRepeatedly)
    {
        for (std::size_t iteration_index = 0; iteration_index < 10; ++iteration_index)
        {
            ASSERT_TRUE(mutex_manager_instance.construct());
            ASSERT_TRUE(mutex_manager_instance.destruct());
        }
    }

    TEST_F(MutexManagerTest, Should_BeExceptionSafe_When_ConstructThrows)
    {
        try
        {
            mutex_manager_instance.construct();
        }
        catch (...)
        {
            FAIL();
        }
    }

    TEST_F(MutexManagerTest, Should_BeExceptionSafe_When_DestructThrows)
    {
        try
        {
            mutex_manager_instance.destruct();
        }
        catch (...)
        {
            FAIL();
        }
    }

    TEST_F(MutexManagerTest, Should_HandleConcurrentAsyncAccess_When_UsingFutures)
    {
        std::future<bool> future_1 = std::async(std::launch::async, [&]()
            {
                return mutex_manager_instance.construct();
            });

        std::future<bool> future_2 = std::async(std::launch::async, [&]()
            {
                return mutex_manager_instance.destruct();
            });

        ASSERT_TRUE(future_1.get());
        ASSERT_TRUE(future_2.get());
    }

    TEST_F(MutexManagerTest, Should_HandleConcurrentThreadAccess_When_UsingThreads)
    {
        std::atomic<int> success_counter = 0;

        auto thread_function = [&](bool construct_call)
            {
                if (construct_call)
                {
                    if (mutex_manager_instance.construct())
                    {
                        success_counter.fetch_add(1);
                    }
                }
                else
                {
                    if (mutex_manager_instance.destruct())
                    {
                        success_counter.fetch_add(1);
                    }
                }
            };

        std::vector<std::thread> thread_collection;
        for (std::size_t iteration_index = 0; iteration_index < 10; ++iteration_index)
        {
            thread_collection.emplace_back(thread_function, true);
            thread_collection.emplace_back(thread_function, false);
        }

        for (auto& active_thread : thread_collection)
        {
            active_thread.join();
        }

        ASSERT_EQ(success_counter.load(), 20);
    }

    TEST_F(MutexManagerTest, Should_PerformStressTest_When_CalledMultipleTimesRapidly)
    {
        for (std::size_t iteration_index = 0; iteration_index < 1000; ++iteration_index)
        {
            ASSERT_TRUE(mutex_manager_instance.construct());
            ASSERT_TRUE(mutex_manager_instance.destruct());
        }
    }

    TEST_P(MutexManagerParameterizedTest, Should_HandleParameterizedBehavior_When_ConstructOrDestructCalled)
    {
        auto test_data = GetParam();

        if (test_data.construct_first)
        {
            ASSERT_TRUE(mutex_manager_instance.construct());
            ASSERT_TRUE(mutex_manager_instance.destruct());
        }
        else
        {
            ASSERT_TRUE(mutex_manager_instance.destruct());
            ASSERT_TRUE(mutex_manager_instance.construct());
        }
    }

    INSTANTIATE_TEST_CASE_P(
        MutexManagerParameterizedInstantiation,
        MutexManagerParameterizedTest,
        ::testing::Values(
            MutexManagerParameterizedTestData{ true },
            MutexManagerParameterizedTestData{ false }
        )
    );

    TEST_P(MutexManagerLockMutexTest, Should_LockMutexSuccessfully_When_Called)
    {
        auto test_data = GetParam();

        bool lock_result = false;

        if (test_data.mutex_type_name == "std::mutex")
        {
            lock_result = mutex_manager_instance.lock_mutex<
                std::unique_lock<std::mutex>, std::mutex>(test_pointer);
        }
        else if (test_data.mutex_type_name == "std::timed_mutex")
        {
            lock_result = mutex_manager_instance.lock_mutex<
                std::unique_lock<std::timed_mutex>, std::timed_mutex>(test_pointer);
        }
        else if (test_data.mutex_type_name == "std::recursive_mutex")
        {
            lock_result = mutex_manager_instance.lock_mutex<
                std::unique_lock<std::recursive_mutex>, std::recursive_mutex>(test_pointer);
        }
        else if (test_data.mutex_type_name == "std::recursive_timed_mutex")
        {
            lock_result = mutex_manager_instance.lock_mutex<
                std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(test_pointer);
        }
        else if (test_data.mutex_type_name == "std::shared_mutex")
        {
            lock_result = mutex_manager_instance.lock_mutex<
                std::shared_lock<std::shared_mutex>, std::shared_mutex>(test_pointer);
        }

        ASSERT_TRUE(lock_result);
    }

    TEST_P(MutexManagerLockMutexTest, Should_HandleConcurrentAsyncLock_When_Called)
    {
        auto test_data = GetParam();

        auto async_task_1 = std::async(std::launch::async, [&]()
            {
                bool lock_result_inner = false;

                if (test_data.mutex_type_name == "std::mutex")
                {
                    lock_result_inner = mutex_manager_instance.lock_mutex<
                        std::unique_lock<std::mutex>, std::mutex>(test_pointer);
                }
                else if (test_data.mutex_type_name == "std::timed_mutex")
                {
                    lock_result_inner = mutex_manager_instance.lock_mutex<
                        std::unique_lock<std::timed_mutex>, std::timed_mutex>(test_pointer);
                }
                else if (test_data.mutex_type_name == "std::recursive_mutex")
                {
                    lock_result_inner = mutex_manager_instance.lock_mutex<
                        std::unique_lock<std::recursive_mutex>, std::recursive_mutex>(test_pointer);
                }
                else if (test_data.mutex_type_name == "std::recursive_timed_mutex")
                {
                    lock_result_inner = mutex_manager_instance.lock_mutex<
                        std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(test_pointer);
                }
                else if (test_data.mutex_type_name == "std::shared_mutex")
                {
                    lock_result_inner = mutex_manager_instance.lock_mutex<
                        std::shared_lock<std::shared_mutex>, std::shared_mutex>(test_pointer);
                }

                return lock_result_inner;
            });

        auto async_task_2 = std::async(std::launch::async, [&]()
            {
                bool lock_result_inner = false;

                if (test_data.mutex_type_name == "std::mutex")
                {
                    lock_result_inner = mutex_manager_instance.lock_mutex<
                        std::unique_lock<std::mutex>, std::mutex>(test_pointer);
                }
                else if (test_data.mutex_type_name == "std::timed_mutex")
                {
                    lock_result_inner = mutex_manager_instance.lock_mutex<
                        std::unique_lock<std::timed_mutex>, std::timed_mutex>(test_pointer);
                }
                else if (test_data.mutex_type_name == "std::recursive_mutex")
                {
                    lock_result_inner = mutex_manager_instance.lock_mutex<
                        std::unique_lock<std::recursive_mutex>, std::recursive_mutex>(test_pointer);
                }
                else if (test_data.mutex_type_name == "std::recursive_timed_mutex")
                {
                    lock_result_inner = mutex_manager_instance.lock_mutex<
                        std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(test_pointer);
                }
                else if (test_data.mutex_type_name == "std::shared_mutex")
                {
                    lock_result_inner = mutex_manager_instance.lock_mutex<
                        std::shared_lock<std::shared_mutex>, std::shared_mutex>(test_pointer);
                }

                return lock_result_inner;
            });

        ASSERT_TRUE(async_task_1.get());
        ASSERT_TRUE(async_task_2.get());
    }

    TEST_P(MutexManagerLockMutexTest, Should_PerformStressLock_When_CalledMultipleTimes)
    {
        auto test_data = GetParam();

        for (std::size_t iteration_index = 0; iteration_index < 1000; ++iteration_index)
        {
            bool lock_result = false;

            if (test_data.mutex_type_name == "std::mutex")
            {
                lock_result = mutex_manager_instance.lock_mutex<
                    std::unique_lock<std::mutex>, std::mutex>(test_pointer);
            }
            else if (test_data.mutex_type_name == "std::timed_mutex")
            {
                lock_result = mutex_manager_instance.lock_mutex<
                    std::unique_lock<std::timed_mutex>, std::timed_mutex>(test_pointer);
            }
            else if (test_data.mutex_type_name == "std::recursive_mutex")
            {
                lock_result = mutex_manager_instance.lock_mutex<
                    std::unique_lock<std::recursive_mutex>, std::recursive_mutex>(test_pointer);
            }
            else if (test_data.mutex_type_name == "std::recursive_timed_mutex")
            {
                lock_result = mutex_manager_instance.lock_mutex<
                    std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(test_pointer);
            }
            else if (test_data.mutex_type_name == "std::shared_mutex")
            {
                lock_result = mutex_manager_instance.lock_mutex<
                    std::shared_lock<std::shared_mutex>, std::shared_mutex>(test_pointer);
            }

            ASSERT_TRUE(lock_result);
        }
    }

    INSTANTIATE_TEST_CASE_P(
        MutexManagerLockMutexParameterizedInstantiation,
        MutexManagerLockMutexTest,
        ::testing::Values(
            MutexLockCombinationTestData{ "std::mutex", true },
            MutexLockCombinationTestData{ "std::mutex", false },
            MutexLockCombinationTestData{ "std::timed_mutex", true },
            MutexLockCombinationTestData{ "std::timed_mutex", false },
            MutexLockCombinationTestData{ "std::recursive_mutex", true },
            MutexLockCombinationTestData{ "std::recursive_mutex", false },
            MutexLockCombinationTestData{ "std::recursive_timed_mutex", true },
            MutexLockCombinationTestData{ "std::recursive_timed_mutex", false },
            MutexLockCombinationTestData{ "std::shared_mutex", true },
            MutexLockCombinationTestData{ "std::shared_mutex", false }
        )
    );

    TEST_F(MutexManagerLockMutexTest, Should_ReturnFalse_When_PointerIsNull)
    {
        bool lock_result = mutex_manager_instance.lock_mutex<
            std::unique_lock<std::mutex>, std::mutex>(nullptr);
        ASSERT_FALSE(lock_result);
    }

    TEST_F(MutexManagerLockMutexTest, Should_HandleEmptyName_When_Called)
    {
        bool lock_result = mutex_manager_instance.lock_mutex<
            std::unique_lock<std::mutex>, std::mutex>(test_pointer, "");
        ASSERT_FALSE(lock_result);
    }

    TEST_F(MutexManagerLockMutexTest, Should_HandleSharedMutexConcurrentRead)
    {
        std::atomic<int> success_count = 0;
        auto task = [&]()
            {
                if (mutex_manager_instance.lock_mutex<
                    std::shared_lock<std::shared_mutex>, std::shared_mutex>(test_pointer))
                {
                    success_count.fetch_add(1);
                }
            };

        std::vector<std::thread> threads(5);
        for (auto& t : threads) t = std::thread(task);
        for (auto& t : threads) t.join();

        ASSERT_EQ(success_count.load(), 5);
    }

    TEST_P(MutexManagerLockMutexTest, Should_PerformStressLock_AllMutexTypes)
    {
        auto test_data = GetParam();

        for (std::size_t i = 0; i < 1000; ++i)
        {
            bool lock_result = false;

            if (test_data.mutex_type_name == "std::mutex")
            {
                lock_result = mutex_manager_instance.lock_mutex<
                    std::unique_lock<std::mutex>, std::mutex>(test_pointer);
            }
            else if (test_data.mutex_type_name == "std::timed_mutex")
            {
                lock_result = mutex_manager_instance.lock_mutex<
                    std::unique_lock<std::timed_mutex>, std::timed_mutex>(test_pointer);
            }
            else if (test_data.mutex_type_name == "std::recursive_mutex")
            {
                lock_result = mutex_manager_instance.lock_mutex<
                    std::unique_lock<std::recursive_mutex>, std::recursive_mutex>(test_pointer);
            }
            else if (test_data.mutex_type_name == "std::recursive_timed_mutex")
            {
                lock_result = mutex_manager_instance.lock_mutex<
                    std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(test_pointer);
            }
            else if (test_data.mutex_type_name == "std::shared_mutex")
            {
                lock_result = mutex_manager_instance.lock_mutex<
                    std::shared_lock<std::shared_mutex>, std::shared_mutex>(test_pointer);
            }

            ASSERT_TRUE(lock_result);
        }
    }

    TEST_F(MutexManagerTest, Should_ReturnFalse_When_LockMutexCalledWithNullptr)
    {
        bool lock_result = mutex_manager_instance.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(nullptr);
        ASSERT_FALSE(lock_result);
    }

    TEST_F(MutexManagerTest, Should_HandleEmptyBaseName_When_ConstructCalled)
    {
        MutexManagerConfigurations config;
        config.name = "";
        config.name = "";
        ASSERT_TRUE(mutex_manager_instance.construct());
        ASSERT_TRUE(mutex_manager_instance.destruct());
    }

    TEST_P(MutexManagerLockMutexTest, Should_AllowRecursiveLock_When_UsingRecursiveMutex)
    {
        auto test_data = GetParam();
        if (test_data.mutex_type_name == "std::recursive_mutex" ||
            test_data.mutex_type_name == "std::recursive_timed_mutex")
        {
            bool first_lock = false;
            bool second_lock = false;
            if (test_data.mutex_type_name == "std::recursive_mutex")
            {
                first_lock = mutex_manager_instance.lock_mutex<std::unique_lock<std::recursive_mutex>, std::recursive_mutex>(test_pointer);
                second_lock = mutex_manager_instance.lock_mutex<std::unique_lock<std::recursive_mutex>, std::recursive_mutex>(test_pointer);
            }
            else
            {
                first_lock = mutex_manager_instance.lock_mutex<std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(test_pointer);
                second_lock = mutex_manager_instance.lock_mutex<std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(test_pointer);
            }
            ASSERT_TRUE(first_lock);
            ASSERT_TRUE(second_lock);
        }
    }

    TEST_P(MutexManagerLockMutexTest, Should_AllowMultipleSharedLocksConcurrently)
    {
        auto test_data = GetParam();
        if (test_data.mutex_type_name == "std::shared_mutex")
        {
            auto shared_lock_task_1 = std::async(std::launch::async, [&]()
                {
                    return mutex_manager_instance.lock_mutex<std::shared_lock<std::shared_mutex>, std::shared_mutex>(test_pointer);
                });
            auto shared_lock_task_2 = std::async(std::launch::async, [&]()
                {
                    return mutex_manager_instance.lock_mutex<std::shared_lock<std::shared_mutex>, std::shared_mutex>(test_pointer);
                });
            ASSERT_TRUE(shared_lock_task_1.get());
            ASSERT_TRUE(shared_lock_task_2.get());
        }
    }

    TEST_P(MutexManagerLockMutexTest, Should_HandleTimedMutexTimeout)
    {
        auto test_data = GetParam();

        if (test_data.mutex_type_name == "std::timed_mutex")
        {
            std::timed_mutex timed_mutex_instance;
            std::unique_lock<std::timed_mutex> lock(timed_mutex_instance, std::defer_lock);
            bool lock_result = mutex_manager_instance.lock_mutex<std::unique_lock<std::timed_mutex>, std::timed_mutex>(test_pointer);
            ASSERT_TRUE(lock_result);
        }
        else if (test_data.mutex_type_name == "std::recursive_timed_mutex")
        {
            std::recursive_timed_mutex recursive_timed_mutex_instance;
            std::unique_lock<std::recursive_timed_mutex> lock(recursive_timed_mutex_instance, std::defer_lock);
            bool lock_result = mutex_manager_instance.lock_mutex<std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(test_pointer);
            ASSERT_TRUE(lock_result);
        }
        else if (test_data.mutex_type_name == "std::recursive_mutex")
        {
            std::recursive_mutex recursive_mutex_instance;
            std::unique_lock<std::recursive_mutex> lock(recursive_mutex_instance, std::defer_lock);
            bool lock_result = mutex_manager_instance.lock_mutex<std::unique_lock<std::recursive_mutex>, std::recursive_mutex>(test_pointer);
            ASSERT_TRUE(lock_result);
        }
    }

    TEST_F(MutexManagerTest, Should_BeExceptionSafe_When_MutexConstructorThrows)
    {
        try
        {
            FailingMutex failing_mutex_instance;
            std::unique_lock<FailingMutex> lock(failing_mutex_instance);
            FAIL();
        }
        catch (...)
        {
        }
    }

    TEST_F(MutexManagerBoostTest, BoostMutexLockWithoutName)
    {
        bool locked = manager.lock_mutex<boost::unique_lock<boost::mutex>, boost::mutex>(test_ptr);
        EXPECT_TRUE(locked);
    }

    TEST_F(MutexManagerBoostTest, BoostMutexLockWithName)
    {
        bool locked = manager.lock_mutex<boost::unique_lock<boost::mutex>, boost::mutex>(test_ptr, "test_mutex");
        EXPECT_TRUE(locked);
    }

    TEST_F(MutexManagerBoostTest, BoostTimedMutexLockWithoutName)
    {
        bool locked = manager.lock_mutex<boost::unique_lock<boost::timed_mutex>, boost::timed_mutex>(test_ptr);
        EXPECT_TRUE(locked);
    }

    TEST_F(MutexManagerBoostTest, BoostTimedMutexLockWithName)
    {
        bool locked = manager.lock_mutex<boost::unique_lock<boost::timed_mutex>, boost::timed_mutex>(test_ptr, "test_timed_mutex");
        EXPECT_TRUE(locked);
    }

    TEST_F(MutexManagerBoostTest, BoostRecursiveMutexReentrancy)
    {
        bool first_lock = manager.lock_mutex<boost::unique_lock<boost::recursive_mutex>, boost::recursive_mutex>(test_ptr);
        bool second_lock = manager.lock_mutex<boost::unique_lock<boost::recursive_mutex>, boost::recursive_mutex>(test_ptr);
        EXPECT_TRUE(first_lock);
        EXPECT_TRUE(second_lock);
    }

    TEST_F(MutexManagerBoostTest, BoostRecursiveTimedMutexReentrancy)
    {
        bool first_lock = manager.lock_mutex<boost::unique_lock<boost::recursive_timed_mutex>, boost::recursive_timed_mutex>(test_ptr);
        bool second_lock = manager.lock_mutex<boost::unique_lock<boost::recursive_timed_mutex>, boost::recursive_timed_mutex>(test_ptr);
        EXPECT_TRUE(first_lock);
        EXPECT_TRUE(second_lock);
    }

    TEST_F(MutexManagerBoostTest, BoostSharedMutexMultipleReaders)
    {
        bool reader1 = manager.lock_mutex<boost::shared_lock<boost::shared_mutex>, boost::shared_mutex>(test_ptr);
        bool reader2 = manager.lock_mutex<boost::shared_lock<boost::shared_mutex>, boost::shared_mutex>(test_ptr);
        EXPECT_TRUE(reader1);
        EXPECT_TRUE(reader2);
    }

    TEST_F(MutexManagerBoostTest, NullPointerReturnsFalse)
    {
        bool locked = manager.lock_mutex<boost::unique_lock<boost::mutex>, boost::mutex>(nullptr);
        EXPECT_FALSE(locked);
    }

    TEST_F(MutexManagerBoostTest, NullPointerWithNameReturnsFalse)
    {
        bool locked = manager.lock_mutex<boost::unique_lock<boost::mutex>, boost::mutex>(nullptr, "null_mutex");
        EXPECT_FALSE(locked);
    }

    TEST_F(MutexManagerBoostTest, EmptyNameStringLock)
    {
        bool locked = manager.lock_mutex<boost::unique_lock<boost::mutex>, boost::mutex>(test_ptr, "");
        EXPECT_FALSE(locked);
    }

    TEST_F(MutexManagerBoostTest, MultiThreadedBoostMutex)
    {
        bool result1 = false, result2 = false;
        std::thread t1([&]() { result1 = manager.lock_mutex<boost::unique_lock<boost::mutex>, boost::mutex>(test_ptr, "thread_mutex"); });
        std::thread t2([&]() { result2 = manager.lock_mutex<boost::unique_lock<boost::mutex>, boost::mutex>(test_ptr, "thread_mutex"); });
        t1.join();
        t2.join();
        EXPECT_TRUE(result1);
        EXPECT_TRUE(result2);
    }

    TEST_F(MutexManagerBoostTest, MultiThreadedBoostSharedMutex)
    {
        bool result1 = false, result2 = false;
        std::thread t1([&]() { result1 = manager.lock_mutex<boost::shared_lock<boost::shared_mutex>, boost::shared_mutex>(test_ptr, "shared_mutex"); });
        std::thread t2([&]() { result2 = manager.lock_mutex<boost::shared_lock<boost::shared_mutex>, boost::shared_mutex>(test_ptr, "shared_mutex"); });
        t1.join();
        t2.join();
        EXPECT_TRUE(result1);
        EXPECT_TRUE(result2);
    }

	TEST_F(MutexManagerTest, Should_HonorRuntimeExecutionDisabledForUtilityHandling)
	{
		mutex_manager_instance.configurations.is_utility_runtime_execution_handling_enabled = false;
		ASSERT_FALSE(mutex_manager_instance.configurations.is_runtime_execution_enabled_for_utility_handling());
	}

	TEST_F(MutexManagerTest, Should_HonorRuntimeExecutionDisabledForFeatureHandling)
	{
		mutex_manager_instance.configurations.is_feature_runtime_execution_handling_enabled = false;
		ASSERT_FALSE(mutex_manager_instance.configurations.is_runtime_execution_enabled_for_feature_handling());
	}

	TEST_F(MutexManagerTest, Should_HonorRuntimeExecutionDisabledForErrorHandling)
	{
		mutex_manager_instance.configurations.is_error_runtime_execution_handling_enabled = false;
		ASSERT_FALSE(mutex_manager_instance.configurations.is_runtime_execution_enabled_for_error_handling());
	}

	TEST_F(MutexManagerTest, Should_HonorEdgeCaseDisabledForUtilityHandling)
	{
		mutex_manager_instance.configurations.is_utility_edge_case_handling_enabled = false;
		ASSERT_FALSE(mutex_manager_instance.configurations.is_edge_case_enabled_for_utility_handling());
	}

	TEST_F(MutexManagerTest, Should_HonorEdgeCaseDisabledForFeatureHandling)
	{
		mutex_manager_instance.configurations.is_feature_edge_case_handling_enabled = false;
		ASSERT_FALSE(mutex_manager_instance.configurations.is_edge_case_enabled_for_feature_handling());
	}

	TEST_F(MutexManagerTest, Should_HonorEdgeCaseDisabledForErrorHandling)
	{
		mutex_manager_instance.configurations.is_error_edge_case_handling_enabled = false;
		ASSERT_FALSE(mutex_manager_instance.configurations.is_edge_case_enabled_for_error_handling());
	}

	TEST_F(MutexManagerTest, Should_HonorThreadSafetyDisabledForUtilityHandling)
	{
		mutex_manager_instance.configurations.is_utility_thread_safety_handling_enabled = false;
		ASSERT_FALSE(mutex_manager_instance.configurations.is_thread_safety_enabled_for_utility_handling());
	}

	TEST_F(MutexManagerTest, Should_HonorThreadSafetyDisabledForFeatureHandling)
	{
		mutex_manager_instance.configurations.is_feature_thread_safety_handling_enabled = false;
		ASSERT_FALSE(mutex_manager_instance.configurations.is_thread_safety_enabled_for_feature_handling());
	}

	TEST_F(MutexManagerTest, Should_HonorThreadSafetyDisabledForErrorHandling)
	{
		mutex_manager_instance.configurations.is_error_thread_safety_handling_enabled = false;
		ASSERT_FALSE(mutex_manager_instance.configurations.is_thread_safety_enabled_for_error_handling());
	}

	TEST_F(MutexManagerTest, Should_HandleMultipleConcurrentFutures)
	{
		std::atomic<int> counter = 0;
		auto future_task = [&](int id)
		{
			if (mutex_manager_instance.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(&id))
				counter.fetch_add(1);
		};
		std::vector<std::future<void>> futures;
		for (int i = 0; i < 50; ++i)
		{
			futures.emplace_back(std::async(std::launch::async, future_task, i));
		}
		for (auto& f : futures) f.get();
		ASSERT_EQ(counter.load(), 50);
	}

	TEST_P(MutexManagerLockMutexTest, Should_HandleTimedMutexLockTimeout)
	{
		auto test_data = GetParam();

		if (test_data.mutex_type_name == "std::timed_mutex")
		{
			std::timed_mutex timed_mutex_instance;
			std::unique_lock<std::timed_mutex> lock(timed_mutex_instance, std::defer_lock);
			bool lock_result = mutex_manager_instance.lock_mutex<
				std::unique_lock<std::timed_mutex>, std::timed_mutex>(&timed_mutex_instance);
			ASSERT_TRUE(lock_result);
		}
		else if (test_data.mutex_type_name == "std::recursive_timed_mutex")
		{
			std::recursive_timed_mutex recursive_timed_mutex_instance;
			std::unique_lock<std::recursive_timed_mutex> lock(recursive_timed_mutex_instance, std::defer_lock);
			bool lock_result = mutex_manager_instance.lock_mutex<
				std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(&recursive_timed_mutex_instance);
			ASSERT_TRUE(lock_result);
		}
	}

	TEST_F(MutexManagerTest, Should_HandleDestructDuringActiveLocks)
	{
		std::mutex active_mutex;
		std::unique_lock<std::mutex> lock(active_mutex);

		bool destruct_result = mutex_manager_instance.destruct();
		ASSERT_TRUE(destruct_result);
	}

	TEST_F(MutexManagerLockMutexTest, Should_HandleLockMutexRuntimeException)
	{
		struct ThrowingMutex
		{
			void lock() { throw std::runtime_error("Lock failure"); }
			void unlock() {}
		};

		ThrowingMutex throwing_mutex;
		try
		{
			std::unique_lock<ThrowingMutex> lock(throwing_mutex);
			FAIL();
		}
		catch (...)
		{
		}
	}

	TEST_F(MutexManagerTest, Should_HandleDestructDuringMultipleActiveLocks)
	{
		std::mutex mutex1, mutex2, mutex3;
		std::unique_lock<std::mutex> lock1(mutex1);
		std::unique_lock<std::mutex> lock2(mutex2);
		std::unique_lock<std::mutex> lock3(mutex3);

		bool destruct_result = mutex_manager_instance.destruct();
		ASSERT_TRUE(destruct_result);
	}

	TEST_F(MutexManagerTest, Should_HandleExtremeConcurrencyWithFutures)
	{
		std::atomic<int> counter = 0;
		auto future_task = [&](int id)
		{
			if (mutex_manager_instance.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(&id))
				counter.fetch_add(1);
		};

		std::vector<std::future<void>> futures;
		for (int i = 0; i < 200; ++i)
			futures.emplace_back(std::async(std::launch::async, future_task, i));
		for (auto& f : futures) f.get();

		ASSERT_EQ(counter.load(), 200);
	}

	TEST_F(MutexManagerTest, Should_HandleDestructConcurrentlyWithActiveLocks)
	{
		std::atomic<int> counter = 0;
		auto thread_task = [&](int id)
		{
			if (mutex_manager_instance.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(&id))
				counter.fetch_add(1);
		};

		std::vector<std::thread> threads;
		for (int i = 0; i < 50; ++i)
			threads.emplace_back(thread_task, i);

		bool destruct_result = mutex_manager_instance.destruct();
		for (auto& t : threads) t.join();

		ASSERT_TRUE(destruct_result);
		ASSERT_EQ(counter.load(), 50);
	}

	TEST_F(MutexManagerTest, Should_HandleCustomMutexTypes)
	{
		struct CustomMutex
		{
			void lock() {}
			void unlock() {}
		};

		CustomMutex custom_mutex;
		bool lock_result = mutex_manager_instance.lock_mutex<std::unique_lock<CustomMutex>, CustomMutex>(&custom_mutex);
		ASSERT_FALSE(lock_result);
	}

}

#endif
