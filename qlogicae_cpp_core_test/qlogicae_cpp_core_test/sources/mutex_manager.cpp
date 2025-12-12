#include "pch.hpp"

#include "qlogicae_cpp_core/includes/mutex_manager.hpp"

namespace QLogicaeCppCoreTest
{
    class MutexManagerTest : public ::testing::Test
    {
    protected:
        MutexManagerTest() = default;
        ~MutexManagerTest() override = default;

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }

        struct LockTestData
        {
            void* pointer;
            std::string name;
        };
    };

    using LockTypes = ::testing::Types<
        std::mutex,
        std::timed_mutex,
        std::recursive_mutex,
        std::recursive_timed_mutex,
        std::shared_mutex
    >;

    struct MutexTestParam
    {
        void* pointer;
        std::string name;
    };

    class MutexManagerParameterizedTest :
        public MutexManagerTest,
        public ::testing::WithParamInterface<MutexTestParam>
    {
    };

    TEST_F(MutexManagerTest, Should_LockMutexSuccessfully_When_UsingUniqueLock)
    {
        QLogicaeCppCore::Result<bool> result;
        int dummy_object = 0;
        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(
            result, &dummy_object
        );
        EXPECT_TRUE(result.get_value());
        EXPECT_EQ(result.get_status(), QLogicaeCppCore::ResultStatus::GOOD);
    }

    TEST_F(MutexManagerTest, Should_LockMutexSuccessfully_When_UsingSharedLock)
    {
        QLogicaeCppCore::Result<bool> result;
        int dummy_object = 0;
        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::shared_lock<std::shared_mutex>, std::shared_mutex>(
            result, &dummy_object
        );
        EXPECT_TRUE(result.get_value());
        EXPECT_EQ(result.get_status(), QLogicaeCppCore::ResultStatus::GOOD);
    }

    TEST_F(MutexManagerTest, Should_HandleMultipleThreads_When_LockingUniqueMutex)
    {
        QLogicaeCppCore::Result<bool> result_main;
        int shared_counter = 0;
        constexpr int thread_count = 10;
        std::vector<std::thread> threads;

        for (int i = 0; i < thread_count; i++)
        {
            threads.emplace_back([&shared_counter, &result_main]()
                {
                    QLogicaeCppCore::Result<bool> result;
                    int dummy_object = 0;
                    QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(
                        result, &dummy_object
                    );
                    if (result.get_value())
                    {
                        shared_counter++;
                    }
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(shared_counter, thread_count);
    }

    TEST_F(MutexManagerTest, Should_HandleMultipleThreads_When_LockingSharedMutex)
    {
        QLogicaeCppCore::Result<bool> result_main;
        int shared_counter = 0;
        constexpr int thread_count = 10;
        std::vector<std::thread> threads;

        for (int i = 0; i < thread_count; i++)
        {
            threads.emplace_back([&shared_counter]()
                {
                    QLogicaeCppCore::Result<bool> result;
                    int dummy_object = 0;
                    QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::shared_lock<std::shared_mutex>, std::shared_mutex>(
                        result, &dummy_object
                    );
                    if (result.get_value())
                    {
                        shared_counter++;
                    }
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(shared_counter, thread_count);
    }

    TEST_F(MutexManagerTest, Should_PerformLocking_Asynchronously)
    {
        int dummy_object = 0;
        auto future1 = std::async(std::launch::async, [&dummy_object]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(
                    result, &dummy_object
                );
                return result.get_value();
            });

        auto future2 = std::async(std::launch::async, [&dummy_object]()
            {
                QLogicaeCppCore::Result<bool> result;
                QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::shared_lock<std::shared_mutex>, std::shared_mutex>(
                    result, &dummy_object
                );
                return result.get_value();
            });

        EXPECT_TRUE(future1.get());
        EXPECT_TRUE(future2.get());
    }

    TEST_F(MutexManagerTest, Should_HandleEdgeCases_When_PointerIsNull)
    {
        QLogicaeCppCore::Result<bool> result;
        int* null_pointer = nullptr;
        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(
            result, null_pointer
        );
        EXPECT_TRUE(result.get_value());
        EXPECT_EQ(result.get_status(), QLogicaeCppCore::ResultStatus::GOOD);
    }

    TEST_F(MutexManagerTest, Should_HandleEdgeCases_When_NameIsEmpty)
    {
        QLogicaeCppCore::Result<bool> result;
        int dummy_object = 0;
        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(
            result, &dummy_object, ""
        );
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(MutexManagerTest, Should_HandleStressTest_WithHighConcurrency)
    {
        constexpr int iterations = 1000;
        std::atomic<int> counter = 0;
        int dummy_object = 0;
        std::vector<std::thread> threads;

        for (int i = 0; i < iterations; i++)
        {
            threads.emplace_back([&counter, &dummy_object]()
                {
                    QLogicaeCppCore::Result<bool> result;
                    QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(
                        result, &dummy_object
                    );
                    if (result.get_value())
                    {
                        counter++;
                    }
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(counter.load(), iterations);
    }

    INSTANTIATE_TEST_CASE_P(
        MutexManagerParameterized,
        MutexManagerParameterizedTest,
        ::testing::Values(
            MutexTestParam{ reinterpret_cast<void*>(0x1), "first" },
            MutexTestParam{ reinterpret_cast<void*>(0x2), "second" },
            MutexTestParam{ nullptr, "" }
        )
    );

    TEST_P(MutexManagerParameterizedTest, Should_LockMutexSuccessfully_ForVariousParameters)
    {
        QLogicaeCppCore::Result<bool> result;
        auto param = GetParam();
        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(
            result, param.pointer, param.name
        );
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(MutexManagerTest, Should_HandleMultipleLocksOnSamePointerAndName)
    {
        QLogicaeCppCore::Result<bool> result;
        int test_object;
        void* ptr = &test_object;

        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(result, ptr, "key1");
        EXPECT_TRUE(result.get_value());

        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(result, ptr, "key1");
        EXPECT_TRUE(result.get_value());

        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::shared_lock<std::shared_mutex>, std::shared_mutex>(result, ptr, "key2");
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(MutexManagerTest, Should_HandleNullPointer)
    {
        QLogicaeCppCore::Result<bool> result;
        void* ptr = nullptr;

        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(result, ptr, "null_test");
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(MutexManagerTest, Should_HandleEmptyStringName)
    {
        QLogicaeCppCore::Result<bool> result;
        int test_object;
        void* ptr = &test_object;

        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(result, ptr, "");
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(MutexManagerTest, Should_HandleLongStringName)
    {
        QLogicaeCppCore::Result<bool> result;
        int test_object;
        void* ptr = &test_object;
        std::string long_name(1000, 'x');

        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(result, ptr, long_name);
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(MutexManagerTest, Should_HandleAsynchronousLocking)
    {
        QLogicaeCppCore::Result<bool> result;
        int test_object;
        void* ptr = &test_object;

        auto future = std::async(std::launch::async, [&]()
            {
                QLogicaeCppCore::Result<bool> async_result;
                QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(async_result, ptr, "async");
                return async_result.get_value();
            });

        EXPECT_TRUE(future.get());
    }

    TEST_F(MutexManagerTest, Should_HandleMultithreadedLocking)
    {
        QLogicaeCppCore::Result<bool> result;
        int test_object;
        void* ptr = &test_object;
        const int thread_count = 10;

        std::vector<std::thread> threads;
        for (int i = 0; i < thread_count; ++i)
        {
            threads.emplace_back([&, i]()
                {
                    QLogicaeCppCore::Result<bool> thread_result;
                    QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(thread_result, ptr,
                        "multi_thread_" + std::to_string(i));
                    EXPECT_TRUE(thread_result.get_value());
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }
    }

    TEST_F(MutexManagerTest, Should_StressTestHighIterationLocks)
    {
        QLogicaeCppCore::Result<bool> result;
        int test_object;
        void* ptr = &test_object;
        const int iteration_count = 1000;

        for (int i = 0; i < iteration_count; ++i)
        {
            QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(result, ptr,
                "stress_" + std::to_string(i));
            EXPECT_TRUE(result.get_value());
        }
    }

    TEST_F(MutexManagerTest, Should_HandleMultipleMutexTypesConcurrently)
    {
        QLogicaeCppCore::Result<bool> result;
        int test_object;
        void* ptr = &test_object;

        std::thread thread1([&]()
            {
                QLogicaeCppCore::Result<bool> r;
                QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(r, ptr, "type1");
                EXPECT_TRUE(r.get_value());
            });

        std::thread thread2([&]()
            {
                QLogicaeCppCore::Result<bool> r;
                QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::shared_lock<std::shared_mutex>, std::shared_mutex>(r, ptr, "type2");
                EXPECT_TRUE(r.get_value());
            });

        thread1.join();
        thread2.join();
    }
    TEST_F(MutexManagerTest, Should_HandleRecursiveLocking)
    {
        QLogicaeCppCore::Result<bool> result;
        std::recursive_mutex rec_mutex;
        void* ptr = &rec_mutex;
        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::recursive_mutex>, std::recursive_mutex>(result, ptr);
        EXPECT_TRUE(result.get_value());
        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::recursive_mutex>, std::recursive_mutex>(result, ptr);
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(MutexManagerTest, Should_HandleRecursiveTimedLocking)
    {
        QLogicaeCppCore::Result<bool> result;
        std::recursive_timed_mutex rec_timed_mutex;
        void* ptr = &rec_timed_mutex;
        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(result, ptr);
        EXPECT_TRUE(result.get_value());
        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(result, ptr);
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(MutexManagerTest, Should_HandleTimedMutexLock)
    {
        QLogicaeCppCore::Result<bool> result;
        std::timed_mutex timed_mutex;
        void* ptr = &timed_mutex;
        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::timed_mutex>, std::timed_mutex>(result, ptr);
        EXPECT_TRUE(result.get_value());
    }

    TEST_F(MutexManagerTest, Should_HandleMultipleSharedLocksConcurrently)
    {
        QLogicaeCppCore::Result<bool> result;
        std::shared_mutex shared_mutex;
        void* ptr = &shared_mutex;
        std::atomic<int> counter = 0;
        constexpr int thread_count = 10;
        std::vector<std::thread> threads;

        for (int i = 0; i < thread_count; ++i)
        {
            threads.emplace_back([&counter, &ptr]()
                {
                    QLogicaeCppCore::Result<bool> r;
                    QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::shared_lock<std::shared_mutex>, std::shared_mutex>(r, ptr);
                    if (r.get_value()) counter++;
                });
        }

        for (auto& t : threads) t.join();
        EXPECT_EQ(counter.load(), thread_count);
    }

    TEST_F(MutexManagerTest, Should_HandleLockingDifferentMutexTypesSimultaneously)
    {
        std::mutex m1;
        std::shared_mutex m2;
        QLogicaeCppCore::Result<bool> r1, r2;
        void* ptr1 = &m1;
        void* ptr2 = &m2;

        std::thread t1([&]() { QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::mutex>, std::mutex>(r1, ptr1); });
        std::thread t2([&]() { QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::shared_lock<std::shared_mutex>, std::shared_mutex>(r2, ptr2); });

        t1.join();
        t2.join();
        EXPECT_TRUE(r1.get_value());
        EXPECT_TRUE(r2.get_value());
    }

    TEST_F(MutexManagerTest, Should_HandleConcurrentLocksOnSameRecursiveMutex)
    {
        std::recursive_mutex rec_mutex;
        void* ptr = &rec_mutex;
        std::atomic<int> counter = 0;
        constexpr int thread_count = 5;
        std::vector<std::thread> threads;

        for (int i = 0; i < thread_count; ++i)
        {
            threads.emplace_back([&]()
                {
                    QLogicaeCppCore::Result<bool> r;
                    QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::recursive_mutex>, std::recursive_mutex>(r, ptr);
                    if (r.get_value()) counter++;
                });
        }

        for (auto& t : threads) t.join();
        EXPECT_EQ(counter.load(), thread_count);
    }

    TEST_F(MutexManagerTest, Should_HandleConcurrentLocksOnSameTimedMutex)
    {
        std::timed_mutex timed_mutex;
        void* ptr = &timed_mutex;
        std::atomic<int> counter = 0;
        constexpr int thread_count = 5;
        std::vector<std::thread> threads;

        for (int i = 0; i < thread_count; ++i)
        {
            threads.emplace_back([&]()
                {
                    QLogicaeCppCore::Result<bool> r;
                    QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::timed_mutex>, std::timed_mutex>(r, ptr);
                    if (r.get_value()) counter++;
                });
        }

        for (auto& t : threads) t.join();
        EXPECT_EQ(counter.load(), thread_count);
    }

    TEST_F(MutexManagerTest, Should_HandleSharedLockAfterUniqueLockOnSameSharedMutex)
    {
        std::shared_mutex shared_mutex;
        void* ptr = &shared_mutex;
        QLogicaeCppCore::Result<bool> r1, r2;

        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::shared_mutex>, std::shared_mutex>(r1, ptr);
        EXPECT_TRUE(r1.get_value());

        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::shared_lock<std::shared_mutex>, std::shared_mutex>(r2, ptr);
        EXPECT_TRUE(r2.get_value());
    }

    TEST_F(MutexManagerTest, Should_FailToLockTimedMutex_When_AlreadyLocked)
    {
        QLogicaeCppCore::Result<bool> result1, result2;
        std::timed_mutex timed_mutex;
        void* ptr = &timed_mutex;

        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::timed_mutex>, std::timed_mutex>(result1, ptr);

        std::thread t([&]()
            {
                QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::timed_mutex>, std::timed_mutex>(result2, ptr);
            });
        t.join();

        EXPECT_TRUE(result1.get_value());
        EXPECT_TRUE(result2.get_value());
    }

    TEST_F(MutexManagerTest, Should_FailToLockRecursiveTimedMutex_When_AlreadyLocked)
    {
        QLogicaeCppCore::Result<bool> result1, result2;
        std::recursive_timed_mutex rec_timed_mutex;
        void* ptr = &rec_timed_mutex;

        QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(result1, ptr);

        std::thread t([&]()
            {
                QLogicaeCppCore::MUTEX_MANAGER.lock_mutex<std::unique_lock<std::recursive_timed_mutex>, std::recursive_timed_mutex>(result2, ptr);
            });
        t.join();

        EXPECT_TRUE(result1.get_value());
        EXPECT_TRUE(result2.get_value());
    }
}
