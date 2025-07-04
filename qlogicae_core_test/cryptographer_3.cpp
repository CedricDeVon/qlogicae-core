#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{

    class Cryptographer3Test : public ::testing::TestWithParam<std::string> {
    protected:
        QLogicaeCore::Cryptographer3 crypto;
    };

    TEST_F(Cryptographer3Test, Should_Expect_TransformResult_When_ValidInput) {
        std::string input = "secure_password";
        std::string hash = crypto.transform(input);
        EXPECT_FALSE(hash.empty());
    }

    TEST_F(Cryptographer3Test, Should_Expect_Empty_When_TransformFailsInternally) {
        std::string long_input(1000000, 'x');
        QLogicaeCore::CryptographerProperties weak_props = QLogicaeCore::default_cryptographer_3_properties;
        weak_props.size_t_1 = 1;
        weak_props.size_t_2 = 1;
        QLogicaeCore::Cryptographer3 weak_crypto(weak_props);
        std::string result = weak_crypto.transform(long_input);
        EXPECT_TRUE(result.empty());
    }

    TEST_F(Cryptographer3Test, Should_Expect_True_When_ReverseMatchesOriginal) {
        std::string input = "password123";
        std::string hash = crypto.transform(input);
        bool result = crypto.reverse(hash, input);
        EXPECT_TRUE(result);
    }

    TEST_F(Cryptographer3Test, Should_Expect_False_When_ReverseFails) {
        std::string input = "password123";
        std::string hash = crypto.transform(input);
        bool result = crypto.reverse(hash, "wrongpassword");
        EXPECT_FALSE(result);
    }

    TEST_F(Cryptographer3Test, Should_Expect_AsyncMatch_When_ComparedWithSync) {
        std::string input = "parallel_test";
        std::future<std::string> f = crypto.transform_async(input);
        std::string sync = crypto.transform(input);
        EXPECT_NE(sync, "");
        EXPECT_EQ(f.get().substr(0, 10), sync.substr(0, 10));
    }

    TEST_F(Cryptographer3Test, Should_Expect_CorrectReverseAsync) {
        std::string input = "async_password";
        std::string hash = crypto.transform(input);
        std::future<bool> result = crypto.reverse_async(hash, input);
        EXPECT_TRUE(result.get());
    }

    TEST_F(Cryptographer3Test, Should_Expect_CorrectResult_When_ConcurrentCallsMade) {
        std::string input = "multithread";
        std::vector<std::future<std::string>> futures;
        for (int i = 0; i < 10; ++i) {
            futures.emplace_back(std::async(std::launch::async, [&]() {
                return crypto.transform(input);
                }));
        }
        for (auto& f : futures) {
            EXPECT_FALSE(f.get().empty());
        }
    }

    TEST_F(Cryptographer3Test, Should_Expect_ReverseTrue_When_ConcurrentReverseCalls) {
        std::string input = "multireverse";
        std::string hash = crypto.transform(input);
        std::vector<std::future<bool>> futures;
        for (int i = 0; i < 10; ++i) {
            futures.emplace_back(std::async(std::launch::async, [&]() {
                return crypto.reverse(hash, input);
                }));
        }
        for (auto& f : futures) {
            EXPECT_TRUE(f.get());
        }
    }

    TEST_F(Cryptographer3Test, Should_Expect_PerformanceUnder20Seconds_When_RepeatedTransform) {
        std::string input = "benchmark";
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < 100; ++i) {
            crypto.transform(input);
        }
        auto end = std::chrono::steady_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::seconds>(end - start).count(), 20);
    }

    TEST_F(Cryptographer3Test, Should_Expect_TransformUnder2Seconds_When_ShortInput) {
        std::string input = "short";
        auto start = std::chrono::high_resolution_clock::now();
        crypto.transform(input);
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::seconds>(end - start).count(), 2);
    }

    TEST_P(Cryptographer3Test, Should_Expect_ValidHash_When_ParameterizedInputsUsed) {
        std::string input = GetParam();
        std::string hash = crypto.transform(input);
        EXPECT_FALSE(hash.empty());
    }

    INSTANTIATE_TEST_CASE_P(
        Cryptographer3TestSet,
        Cryptographer3Test,
        ::testing::Values(
            "", "a", "123456", "complex_string$#@!", std::string(500, 'y')
        )
    );

    TEST_F(Cryptographer3Test, Should_Expect_Death_When_NullptrAccessed) {
        QLogicaeCore::Cryptographer3* ptr = nullptr;
        ASSERT_DEATH({ ptr->transform("crash"); }, "");
    }
}
