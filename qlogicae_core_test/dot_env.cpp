#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{

    class DotEnvTest : public ::testing::TestWithParam<std::wstring> {};

    TEST_F(DotEnvTest, Should_Expect_SetAndGetValue_When_ValidKeyValueProvided) {
        auto& env = QLogicaeCore::DotEnv::instance();
        const wchar_t* key = L"TEST_ENV_VAR";
        const wchar_t* value = L"TestValue";

        ASSERT_TRUE(env.set(key, value));
        auto result = env.get(key);
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), value);
        ASSERT_TRUE(env.remove(key));
    }

    TEST_F(DotEnvTest, Should_Expect_EmptyOptional_When_KeyDoesNotExist) {
        auto& env = QLogicaeCore::DotEnv::instance();
        const wchar_t* key = L"NON_EXISTENT_ENV_VAR";

        auto result = env.get(key);
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), L"");
    }

    TEST_F(DotEnvTest, Should_Expect_Failure_When_SetWithNullArguments) {
        auto& env = QLogicaeCore::DotEnv::instance();
        EXPECT_FALSE(env.set(nullptr, L"SomeValue"));
        EXPECT_FALSE(env.set(L"KEY", nullptr));
    }

    TEST_F(DotEnvTest, Should_Expect_Failure_When_RemoveWithNullArgument) {
        auto& env = QLogicaeCore::DotEnv::instance();
        EXPECT_FALSE(env.remove(nullptr));
    }

    TEST_F(DotEnvTest, Should_Expect_Success_When_RemoveExistingKey) {
        auto& env = QLogicaeCore::DotEnv::instance();
        const wchar_t* key = L"REMOVE_TEST_KEY";
        const wchar_t* value = L"123";

        ASSERT_TRUE(env.set(key, value));
        ASSERT_TRUE(env.remove(key));
        auto result = env.get(key);
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), L"");
    }

    TEST_F(DotEnvTest, Should_Expect_SingletonBehavior_When_AccessedMultipleTimes) {
        auto& instance1 = QLogicaeCore::DotEnv::instance();
        auto& instance2 = QLogicaeCore::DotEnv::instance();
        EXPECT_EQ(&instance1, &instance2);
    }

    TEST_F(DotEnvTest, Should_Expect_ThreadSafety_When_AccessedConcurrently) {
        auto& env = QLogicaeCore::DotEnv::instance();
        const wchar_t* key = L"CONCURRENT_KEY";
        const wchar_t* value = L"VAL";

        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back([&env, key, value]() {
                env.set(key, value);
                auto val = env.get(key);
                EXPECT_TRUE(val.has_value());
                EXPECT_EQ(val.value(), value);
                });
        }

        for (auto& thread : threads) {
            thread.join();
        }

        env.remove(key);
    }

    TEST_F(DotEnvTest, Should_Expect_StressHandling_When_RepeatedSetAndGet) {
        auto& env = QLogicaeCore::DotEnv::instance();
        const wchar_t* key = L"STRESS_ENV";
        const wchar_t* value = L"STRESS_VAL";

        for (int i = 0; i < 1000; ++i) {
            ASSERT_TRUE(env.set(key, value));
            auto result = env.get(key);
            ASSERT_TRUE(result.has_value());
            EXPECT_EQ(result.value(), value);
        }

        ASSERT_TRUE(env.remove(key));
    }

    TEST_F(DotEnvTest, Should_Expect_PerformanceUnderTwoSeconds_When_RepeatedAccess) {
        auto& env = QLogicaeCore::DotEnv::instance();
        const wchar_t* key = L"PERF_KEY";
        const wchar_t* value = L"VAL";

        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < 10000; ++i) {
            env.set(key, value);
            env.get(key);
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        EXPECT_LT(elapsed.count(), 2.0);
        env.remove(key);
    }

    TEST_F(DotEnvTest, Should_Expect_PerformanceUnderOneMillisecond_When_SingleSetAndGet) {
        auto& env = QLogicaeCore::DotEnv::instance();
        const wchar_t* key = L"PERF_1MS";
        const wchar_t* value = L"123";

        auto start = std::chrono::high_resolution_clock::now();
        env.set(key, value);
        auto result = env.get(key);
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), value);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        EXPECT_LT(duration.count(), 1000);
        env.remove(key);
    }

    TEST(DotEnvTestDeathTest, Should_Expect_Death_When_ForcedExitAfterSet) {
        EXPECT_DEATH({
            auto& env = QLogicaeCore::DotEnv::instance();
            env.set(L"DEATH_VAR", L"DEATH");
            std::exit(1);
            }, "");
    }

    INSTANTIATE_TEST_CASE_P(
        DotEnvParameterized,
        DotEnvTest,
        ::testing::Values(
            L"ENV_1",
            L"ENV_2",
            L"ENV_3",
            L"ENV_4",
            L"ENV_5"
        )
    );
}
