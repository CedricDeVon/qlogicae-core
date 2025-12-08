#include "pch.hpp"

#include "qlogicae_cpp_core/includes/instance_manager.hpp"

namespace QLogicaeCppCoreTest
{
    static bool wait_for_condition_ms(
        const std::function<bool()>& condition,
        const std::uint64_t timeout_ms
    )
    {
        const std::chrono::milliseconds poll_interval(5);
        const auto start_time = std::chrono::steady_clock::now();
        while (true)
        {
            if (condition())
            {
                return true;
            }
            const auto elapsed =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - start_time
                )
                .count();
            if (static_cast<std::uint64_t>(elapsed) >= timeout_ms)
            {
                return false;
            }
            std::this_thread::sleep_for(poll_interval);
        }
    }

    class InstanceManagerTest :
        public ::testing::Test
    {
    public:
        InstanceManagerTest()
        {
        }

        ~InstanceManagerTest()
        {
        }
    };

    struct DummyStruct
    {
        int value;
    };

    class InstanceManagerParamTest :
        public ::testing::TestWithParam<int>
    {
    public:
        InstanceManagerParamTest()
        {
        }

        ~InstanceManagerParamTest()
        {
        }
    };

    TEST(
        InstanceManagerTest,
        Should_ReturnSamePointer_When_CalledMultipleTimes
    )
    {
        QLogicaeCppCore::InstanceManager& instance_one =
            QLogicaeCppCore::InstanceManager::get_instance<
            QLogicaeCppCore::InstanceManager
            >();
        QLogicaeCppCore::InstanceManager& instance_two =
            QLogicaeCppCore::InstanceManager::get_instance<
            QLogicaeCppCore::InstanceManager
            >();
        ASSERT_EQ(&instance_one, &instance_two);
    }

    TEST(
        InstanceManagerTest,
        Should_ReturnSamePointer_When_CalledFromMultipleThreads
    )
    {
        const int thread_count = 16;
        std::atomic<int> ready_count(0);
        std::atomic<const void*> pointer_value(nullptr);
        std::vector<std::thread> threads;
        for (int t = 0; t < thread_count; ++t)
        {
            threads.emplace_back(
                [&ready_count, &pointer_value]()
                {
                    QLogicaeCppCore::InstanceManager& instance =
                        QLogicaeCppCore::InstanceManager::get_instance<
                        QLogicaeCppCore::InstanceManager
                        >();
                    const void* address = &instance;
                    if (pointer_value.load() == nullptr)
                    {
                        pointer_value.store(address);
                    }
                    else
                    {
                        ASSERT_EQ(pointer_value.load(), address);
                    }
                    ready_count.fetch_add(1);
                }
            );
        }
        for (auto& th : threads)
        {
            th.join();
        }
        ASSERT_EQ(ready_count.load(), thread_count);
    }

    TEST(
        InstanceManagerTest,
        Should_ReturnSamePointer_When_CalledFromAsyncTasks
    )
    {
        const int task_count = 8;
        std::vector<std::future<const void*>> futures;
        for (int i = 0; i < task_count; ++i)
        {
            futures.emplace_back(
                std::async(
                    std::launch::async,
                    []()
                    {
                        QLogicaeCppCore::InstanceManager& instance =
                            QLogicaeCppCore::InstanceManager::get_instance<
                            QLogicaeCppCore::InstanceManager
                            >();
                        return static_cast<const void*>(&instance);
                    }
                )
            );
        }
        const void* first_ptr = futures[0].get();
        for (int i = 1; i < task_count; ++i)
        {
            const void* ptr = futures[i].get();
            ASSERT_EQ(ptr, first_ptr);
        }
    }

    TEST(
        InstanceManagerTest,
        Should_SetResultGoodStatus_When_WrapperCalled
    )
    {
        QLogicaeCppCore::Result<
            QLogicaeCppCore::InstanceManager*
        > result;
        QLogicaeCppCore::InstanceManager::get_instance(result);
        QLogicaeCppCore::InstanceManager* value;
        result.get_value(value);
        ASSERT_NE(value, nullptr);
    }

    TEST(
        InstanceManagerTest,
        Should_ReturnSamePointer_When_WrapperAndDirectUsed
    )
    {
        QLogicaeCppCore::Result<
            QLogicaeCppCore::InstanceManager*
        > wrapper_result;
        QLogicaeCppCore::InstanceManager::get_instance(
            wrapper_result
        );
        QLogicaeCppCore::InstanceManager* wrapper_ptr;
        wrapper_result.get_value(wrapper_ptr);
        QLogicaeCppCore::InstanceManager& direct =
            QLogicaeCppCore::InstanceManager::get_instance<
            QLogicaeCppCore::InstanceManager
            >();
        ASSERT_EQ(wrapper_ptr, &direct);
    }

    TEST(
        InstanceManagerTest,
        Should_HandleStress_When_HighVolume
    )
    {
        const int iterations = 50000;
        std::atomic<int> counter(0);
        for (int i = 0; i < iterations; ++i)
        {
            QLogicaeCppCore::InstanceManager&
                instance =
                QLogicaeCppCore::InstanceManager::get_instance<
                QLogicaeCppCore::InstanceManager
                >();
            const void* ptr = &instance;
            if (ptr != nullptr)
            {
                counter.fetch_add(1);
            }
        }
        ASSERT_EQ(counter.load(), iterations);
    }

    TEST(
        InstanceManagerTest,
        Should_NotThrow_When_CalledInsideTryCatch
    )
    {
        try
        {
            QLogicaeCppCore::InstanceManager&
                instance =
                QLogicaeCppCore::InstanceManager::get_instance<
                QLogicaeCppCore::InstanceManager
                >();
            ASSERT_NE(&instance, nullptr);
        }
        catch (...)
        {
            FAIL();
        }
    }

    TEST(
        InstanceManagerTest,
        Should_ReturnDifferentPointers_When_DifferentTypes
    )
    {
        QLogicaeCppCore::InstanceManager& a =
            QLogicaeCppCore::InstanceManager::get_instance<
            QLogicaeCppCore::InstanceManager
            >();
        DummyStruct& b =
            QLogicaeCppCore::InstanceManager::get_instance<
            DummyStruct
            >();
        const void* pa = static_cast<const void*>(&a);
        const void* pb = static_cast<const void*>(&b);
        ASSERT_NE(pa, pb);
    }

    TEST_P(
        InstanceManagerParamTest,
        Should_ReturnSamePointer_When_Repeated
    )
    {
        QLogicaeCppCore::InstanceManager& instance_one =
            QLogicaeCppCore::InstanceManager::get_instance<
            QLogicaeCppCore::InstanceManager
            >();
        QLogicaeCppCore::InstanceManager& instance_two =
            QLogicaeCppCore::InstanceManager::get_instance<
            QLogicaeCppCore::InstanceManager
            >();
        ASSERT_EQ(&instance_one, &instance_two);
    }

    INSTANTIATE_TEST_CASE_P(
        EmptyArguments,
        InstanceManagerParamTest,
        ::testing::Values(0, 1, 2)
    );
}
/*
"??"
*/