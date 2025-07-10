#pragma once

#include "pch.h"

#include "cryptographer_4.hpp"

namespace QLogicaeCoreTest
{

    class Cryptographer4Test : public ::testing::TestWithParam<std::string> {
    protected:
        QLogicaeCore::Cryptographer4 crypto;
        std::array<unsigned char, crypto_sign_PUBLICKEYBYTES> public_key{};
        std::array<unsigned char, crypto_sign_SECRETKEYBYTES> secret_key{};

        void SetUp() override {
            crypto_sign_keypair(public_key.data(), secret_key.data());
        }
    };

    TEST_F(Cryptographer4Test, Should_Expect_Encoded_When_TransformValidInput) {
        std::string_view input = "message";
        std::string result = crypto.transform(input, public_key.data(), secret_key.data());
        EXPECT_FALSE(result.empty());
    }

    TEST_F(Cryptographer4Test, Should_Expect_Empty_When_NullKeysUsed) {
        std::string_view input = "msg";
        std::string result = crypto.transform(input, nullptr, nullptr);
        EXPECT_TRUE(result.empty());
    }

    TEST_F(Cryptographer4Test, Should_Expect_Original_When_ReverseValidSignature) {
        std::string_view input = "signed";
        std::string signed_data = crypto.transform(input, public_key.data(), secret_key.data());
        std::string output = crypto.reverse(signed_data, public_key.data());
        EXPECT_EQ(output, input);
    }

    TEST_F(Cryptographer4Test, Should_Expect_Empty_When_ReverseFailsDueToBadKey) {
        std::string_view input = "signed";
        std::string signed_data = crypto.transform(input, public_key.data(), secret_key.data());

        std::array<unsigned char, crypto_sign_PUBLICKEYBYTES> wrong_key{};
        std::string output = crypto.reverse(signed_data, wrong_key.data());
        EXPECT_TRUE(output.empty());
    }

    TEST_F(Cryptographer4Test, Should_Expect_Empty_When_ReverseGivenNullKey) {
        std::string_view signed_input = crypto.transform("invalid", public_key.data(), secret_key.data());
        std::string output = crypto.reverse(signed_input, nullptr);
        EXPECT_TRUE(output.empty());
    }

    TEST_F(Cryptographer4Test, Should_Expect_ValidSignature_When_TransformAsync) {
        std::string_view input = "hello";
        std::future<std::string> result = crypto.transform_async(input, public_key.data(), secret_key.data());
        EXPECT_FALSE(result.get().empty());
    }

    TEST_F(Cryptographer4Test, Should_Expect_Original_When_ReverseAsyncMatches) {
        std::string_view input = "verify";
        std::string signature = crypto.transform(input, public_key.data(), secret_key.data());
        std::future<std::string> result = crypto.reverse_async(signature, public_key.data());
        EXPECT_EQ(result.get(), input);
    }

    TEST_F(Cryptographer4Test, Should_Expect_Correct_When_MultipleConcurrentTransformCallsMade) {
        std::string_view input = "concurrent";
        std::vector<std::future<std::string>> futures;
        for (int i = 0; i < 10; ++i) {
            futures.emplace_back(std::async(std::launch::async, [&]() {
                return crypto.transform(input, public_key.data(), secret_key.data());
                }));
        }
        for (auto& future : futures) {
            EXPECT_FALSE(future.get().empty());
        }
    }

    TEST_F(Cryptographer4Test, Should_Expect_Correct_When_MultipleConcurrentReverseCallsMade) {
        std::string_view input = "verifyconcurrent";
        std::string signed_data = crypto.transform(input, public_key.data(), secret_key.data());

        std::vector<std::future<std::string>> futures;
        for (int i = 0; i < 10; ++i) {
            futures.emplace_back(std::async(std::launch::async, [&]() {
                return crypto.reverse(signed_data, public_key.data());
                }));
        }
        for (auto& future : futures) {
            EXPECT_EQ(future.get(), input);
        }
    }

    TEST_F(Cryptographer4Test, Should_Expect_CompleteUnder2Seconds_When_StressTestTransform) {
        std::string_view input = "benchmark";
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < 100; ++i) {
            crypto.transform(input, public_key.data(), secret_key.data());
        }
        auto end = std::chrono::steady_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::seconds>(end - start).count(), 2);
    }

    TEST_F(Cryptographer4Test, Should_Expect_CompleteUnder1Millisecond_When_ShortMessage) {
        std::string_view input = "x";
        auto start = std::chrono::high_resolution_clock::now();
        crypto.transform(input, public_key.data(), secret_key.data());
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), 1000);
    }

    TEST_P(Cryptographer4Test, Should_Expect_ValidTransform_When_VariousInputsUsed) {
        std::string_view input = GetParam();
        std::string result = crypto.transform(input, public_key.data(), secret_key.data());
        EXPECT_FALSE(result.empty());
    }

    INSTANTIATE_TEST_CASE_P(
        Cryptographer4TestSet,
        Cryptographer4Test,
        ::testing::Values(
            "", "a", "1234567890", "!@#$%^&*()_+", std::string(100, 'z')
        )
    );

    TEST_F(Cryptographer4Test, Should_Expect_Death_When_NullPointerUsed) {
        QLogicaeCore::Cryptographer4* ptr = nullptr;
        ASSERT_DEATH({ ptr->reverse("fail", public_key.data()); }, "");
    }
}
