#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{
    class StringMemoryPoolTest : public ::testing::TestWithParam<std::string>
    {
    protected:
        QLogicaeCore::StringMemoryPool<> pool;
    };

    class StringMemoryPoolAsyncTest : public ::testing::TestWithParam<std::string>
    {
    protected:
        QLogicaeCore::StringMemoryPool<> pool;
    };

    TEST_P(StringMemoryPoolTest, Should_Expect_PointerEquality_When_SameStringInternedTwice)
    {
        const std::string input = GetParam();
        const std::string* first_result = pool.get_internal(input);
        const std::string* second_result = pool.get_internal(input);

        ASSERT_EQ(first_result, second_result);
        ASSERT_EQ(*first_result, input);
    }

    TEST_P(StringMemoryPoolTest, Should_Expect_PointerEquality_When_SameStringInternedAsyncTwice)
    {
        const std::string input = GetParam();
        std::future<const std::string*> first_future = pool.get_internal_async(input);
        std::future<const std::string*> second_future = pool.get_internal_async(input);
        const std::string* first_result = first_future.get();
        const std::string* second_result = second_future.get();

        ASSERT_EQ(first_result, second_result);
        ASSERT_EQ(*first_result, input);
    }

    TEST_P(StringMemoryPoolTest, Should_Expect_True_When_StringFoundAfterInterning)
    {
        const std::string input = GetParam();
        pool.get_internal(input);

        ASSERT_TRUE(pool.is_found(input));
        ASSERT_TRUE(pool.is_found_async(input).get());
    }

    TEST_P(StringMemoryPoolTest, Should_Expect_Empty_When_ClearedPoolQueried)
    {
        const std::string input = GetParam();
        pool.get_internal(input);
        pool.clear();

        ASSERT_FALSE(pool.is_found(input));
        ASSERT_EQ(pool.get_size(), 0);
    }

    TEST_P(StringMemoryPoolTest, Should_Expect_ZeroSize_When_Initialized)
    {
        ASSERT_EQ(pool.get_size(), 0);
        ASSERT_EQ(pool.get_size_async().get(), 0);
    }

    TEST_P(StringMemoryPoolTest, Should_Expect_MultithreadedInterning_When_ConcurrentCallsMade)
    {
        const std::string input = GetParam();
        std::vector<std::thread> threads;
        std::vector<const std::string*> results(16);

        for (int index = 0; index < 16; ++index)
        {
            threads.emplace_back([&pool = this->pool, &input, &results, index]()
                {
                    results[index] = pool.get_internal(input);
                });
        }

        for (std::thread& thread_reference : threads)
        {
            thread_reference.join();
        }

        for (int index = 1; index < 16; ++index)
        {
            ASSERT_EQ(results[0], results[index]);
        }
    }

    TEST_P(StringMemoryPoolTest, Should_Expect_PerformanceWithinLimit_When_StressTested)
    {
        const std::string input_base = GetParam();
        std::vector<std::string> inputs;
        for (int index = 0; index < 1000; ++index)
        {
            inputs.push_back(input_base + std::to_string(index));
        }

        auto time_start = std::chrono::steady_clock::now();
        for (const std::string& input_string : inputs)
        {
            pool.get_internal(input_string);
        }
        auto time_stop = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(time_stop - time_start);

        ASSERT_LE(duration.count(), 2000);
    }

    TEST_P(StringMemoryPoolTest, Should_Expect_DiagnosticsUpdated_When_StringsInterned)
    {
        const std::string input = GetParam();
        pool.get_internal(input);
        pool.get_internal(input);

        QLogicaeCore::StringMemoryPoolSnapshot snapshot = pool.get_diagnostics_snapshot();

        ASSERT_GE(snapshot.pool_hits, 1);
        ASSERT_EQ(snapshot.pool_misses, 1);
        ASSERT_EQ(snapshot.interned_count, 1);
        ASSERT_GE(snapshot.bytes_used, input.size());
    }

    TEST_P(StringMemoryPoolAsyncTest, Should_Expect_ZeroSize_When_ClearedAsync)
    {
        const std::string input = GetParam();
        pool.get_internal(input);
        pool.clear_async().get();

        ASSERT_EQ(pool.get_size(), 0);
        ASSERT_EQ(pool.get_size_async().get(), 0);
    }

    TEST_P(StringMemoryPoolAsyncTest, Should_Expect_CorrectDiagnostics_When_AsyncQueried)
    {
        const std::string input = GetParam();
        pool.get_internal(input);
        pool.get_internal(input);

        QLogicaeCore::StringMemoryPoolSnapshot snapshot = pool.get_diagnostics_async().get();

        ASSERT_GE(snapshot.pool_hits, 1);
        ASSERT_EQ(snapshot.pool_misses, 1);
        ASSERT_EQ(snapshot.interned_count, 1);
        ASSERT_GE(snapshot.bytes_used, input.size());
    }

    TEST_P(StringMemoryPoolAsyncTest, Should_Expect_PointerEquality_When_InternedFromStringView)
    {
        const std::string input = GetParam();
        const std::string_view view = static_cast<std::string_view>(input);

        const std::string* result_a = pool.get_internal(view);
        const std::string* result_b = pool.get_internal(input);

        ASSERT_EQ(result_a, result_b);
        ASSERT_EQ(*result_a, input);
    }

    TEST_P(StringMemoryPoolAsyncTest, Should_Expect_Found_When_StringViewInterned)
    {
        const std::string input = GetParam();
        const std::string_view view = static_cast<std::string_view>(input);

        pool.get_internal(view);

        ASSERT_TRUE(pool.is_found(view));
        ASSERT_TRUE(pool.is_found_async(view).get());
    }

    TEST_P(StringMemoryPoolAsyncTest, Should_Expect_MultithreadedEquality_When_AsyncInterned)
    {
        const std::string input = GetParam();
        std::vector<const std::string*> results(16);
        std::vector<std::future<void>> futures;

        for (int index = 0; index < 16; ++index)
        {
            futures.emplace_back(std::async(std::launch::async, [&pool = this->pool, &input, &results, index]()
                {
                    results[index] = pool.get_internal_async(input).get();
                }));
        }

        for (std::future<void>& future_reference : futures)
        {
            future_reference.get();
        }

        for (int index = 1; index < 16; ++index)
        {
            ASSERT_EQ(results[0], results[index]);
        }
    }

    TEST_P(StringMemoryPoolAsyncTest, Should_Expect_StableState_When_ConcurrentStressAndClear)
    {
        std::atomic<bool> stop_flag = false;
        std::string input = GetParam();
        std::vector<std::thread> threads;

        threads.emplace_back([&]()
            {
                while (!stop_flag.load())
                {
                    pool.get_internal(input);
                }
            });

        threads.emplace_back([&]()
            {
                while (!stop_flag.load())
                {
                    pool.is_found(input);
                }
            });

        threads.emplace_back([&]()
            {
                for (int count = 0; count < 5; ++count)
                {
                    pool.clear();
                    std::this_thread::sleep_for(std::chrono::milliseconds(20));
                }
            });

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        stop_flag = true;

        for (std::thread& thread_reference : threads)
        {
            thread_reference.join();
        }

        ASSERT_TRUE(true);
    }

    TEST_P(StringMemoryPoolAsyncTest, Should_Expect_NoThrow_When_AsyncOperationsRunInParallel)
    {
        const std::string input = GetParam();
        std::vector<std::future<void>> futures;

        for (int index = 0; index < 64; ++index)
        {
            futures.emplace_back(std::async(std::launch::async, [&pool = this->pool, input]()
                {
                    pool.get_internal_async(input).get();
                }));
        }

        for (std::future<void>& future_reference : futures)
        {
            ASSERT_NO_THROW(future_reference.get());
        }
    }

    TEST_P(StringMemoryPoolAsyncTest, Should_Expect_EdgeCaseHandled_When_EmptyStringViewUsed)
    {
        const std::string_view empty_view = std::string_view();
        const std::string* result = pool.get_internal(empty_view);

        ASSERT_NE(result, nullptr);
        ASSERT_EQ(*result, "");
    }

    TEST_P(StringMemoryPoolAsyncTest, Should_Expect_PerformanceWithinLimit_When_AsyncInterningHighVolume)
    {
        const std::string input_base = GetParam();
        std::vector<std::string> inputs;

        for (int index = 0; index < 1000; ++index)
        {
            inputs.push_back(input_base + std::to_string(index));
        }

        auto time_start = std::chrono::steady_clock::now();

        std::vector<std::future<const std::string*>> futures;
        for (const std::string& value : inputs)
        {
            futures.push_back(pool.get_internal_async(value));
        }

        for (std::future<const std::string*>& future_reference : futures)
        {
            future_reference.get();
        }

        auto time_stop = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(time_stop - time_start);

        ASSERT_LE(duration.count(), 2000);
    }

    INSTANTIATE_TEST_CASE_P(StringMemoryPoolTestParam,
        StringMemoryPoolTest,
        ::testing::Values(
            "",
            "a",
            "Test",
            "LongString_" + std::string(1000, 'x'),
            "MiXeDcAsE",
            "CASEsensitive",
            std::string(1, '\0'),
            std::string(256, 'z'),
            "1234567890!@#$%^&*()",
            std::to_string(std::numeric_limits<int>::max()),
            std::to_string(std::numeric_limits<int>::min())
        )
    );

    INSTANTIATE_TEST_CASE_P(StringMemoryPoolTestParamAsync,
        StringMemoryPoolAsyncTest,
        ::testing::Values(
            "",
            "a",
            "Test",
            "LongString_" + std::string(1000, 'x'),
            "MiXeDcAsE",
            "CASEsensitive",
            std::string(1, '\0'),
            std::string(256, 'z'),
            "1234567890!@#$%^&*()",
            std::to_string(std::numeric_limits<int>::max()),
            std::to_string(std::numeric_limits<int>::min())
        )
    );

}
