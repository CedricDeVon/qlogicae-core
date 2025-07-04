#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{
    class ValidatorsTest : public ::testing::TestWithParam<int> {};

    TEST_F(ValidatorsTest, Should_Expect_SingletonInstance_When_AccessedMultipleTimes) {
        auto& instance1 = QLogicaeCore::Validators::instance();
        auto& instance2 = QLogicaeCore::Validators::instance();
        EXPECT_EQ(&instance1, &instance2);
    }

    TEST_F(ValidatorsTest, Should_Expect_SingletonInstance_When_AccessedConcurrently) {
        std::vector<const QLogicaeCore::Validators*> instances(10);
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back([&instances, i] {
                instances[i] = &QLogicaeCore::Validators::instance();
                });
        }
        for (auto& t : threads) {
            t.join();
        }
        for (int i = 1; i < 10; ++i) {
            EXPECT_EQ(instances[0], instances[i]);
        }
    }

    TEST_F(ValidatorsTest, Should_Expect_ThreadSafety_When_StressAccessedInParallel) {
        std::vector<std::thread> threads;
        for (int i = 0; i < 100; ++i) {
            threads.emplace_back([] {
                auto& instance = QLogicaeCore::Validators::instance();
                (void)instance;
                });
        }
        for (auto& thread : threads) {
            thread.join();
        }
        SUCCEED();
    }

    TEST_F(ValidatorsTest, Should_Expect_PerformanceUnderTwoSeconds_When_AccessedRepeatedly) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 100000; ++i) {
            auto& instance = QLogicaeCore::Validators::instance();
            (void)instance;
        }
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = stop - start;
        EXPECT_LT(duration.count(), 2.0);
    }

    TEST_F(ValidatorsTest, Should_Expect_PerformanceUnderOneMillisecond_When_SingleAccess) {
        auto start = std::chrono::high_resolution_clock::now();
        auto& instance = QLogicaeCore::Validators::instance();
        (void)instance;
        auto stop = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        EXPECT_LT(elapsed.count(), 1000);
    }

    TEST(ValidatorsTestDeathTest, Should_Expect_Death_When_ForcedExitDuringAccess) {
        EXPECT_DEATH({
            auto& instance = QLogicaeCore::Validators::instance();
            std::exit(1);
            }, "");
    }

    TEST_P(ValidatorsTest, Should_Expect_InstanceAccess_When_ParameterizedValuesAreUsed) {
        int loop_count = GetParam();
        for (int i = 0; i < loop_count; ++i) {
            auto& instance = QLogicaeCore::Validators::instance();
            (void)instance;
        }
        SUCCEED();
    }

    INSTANTIATE_TEST_CASE_P(
        ValidatorsParameterized,
        ValidatorsTest,
        ::testing::Values(1, 10, 100, 1000, 10000)
    );
}
