#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{

    class Cryptographer2Test : public ::testing::TestWithParam<std::string> {
    protected:
        QLogicaeCore::Cryptographer2 crypto;
        unsigned char key[crypto_aead_aes256gcm_KEYBYTES]{};
        unsigned char nonce[crypto_aead_aes256gcm_NPUBBYTES]{};

        void SetUp() override {
            randombytes_buf(key, sizeof(key));
            randombytes_buf(nonce, sizeof(nonce));
        }
    };

    TEST_F(Cryptographer2Test, Should_Expect_CorrectTransformAndReverse_When_ValidInput) {
        std::string input = "TestString123!";
        std::string encrypted = crypto.transform(input, key, nonce);
        std::string decrypted = crypto.reverse(encrypted, key, nonce);
        EXPECT_EQ(decrypted, input);
    }

    TEST_F(Cryptographer2Test, Should_Expect_Empty_When_KeyOrNonceNull) {
        std::string input = "data";
        EXPECT_EQ(crypto.transform(input, nullptr, nonce), "");
        EXPECT_EQ(crypto.transform(input, key, nullptr), "");
        EXPECT_EQ(crypto.reverse("...", nullptr, nonce), "");
        EXPECT_EQ(crypto.reverse("...", key, nullptr), "");
    }

    TEST_F(Cryptographer2Test, Should_Expect_Empty_When_DecryptionFails) {
        std::string input = "data";
        std::string encrypted = crypto.transform(input, key, nonce);
        unsigned char wrong_key[crypto_aead_aes256gcm_KEYBYTES]{};
        std::string result = crypto.reverse(encrypted, wrong_key, nonce);
        EXPECT_EQ(result, "");
    }

    TEST_F(Cryptographer2Test, Should_Expect_AsyncMatch_When_ComparedWithSync) {
        std::string input = "parallel";
        auto future = crypto.transform_async(input, key, nonce);
        std::string sync_result = crypto.transform(input, key, nonce);
        EXPECT_EQ(future.get(), sync_result);
    }

    TEST_F(Cryptographer2Test, Should_Expect_CorrectReverseAsync) {
        std::string input = "example";
        std::string encrypted = crypto.transform(input, key, nonce);
        auto future = crypto.reverse_async(encrypted, key, nonce);
        EXPECT_EQ(future.get(), input);
    }

    TEST_F(Cryptographer2Test, Should_Expect_MultipleTransformations_When_ConcurrentCallsMade) {
        std::string input = "secure";
        std::vector<std::future<std::string>> futures;
        for (int i = 0; i < 10; ++i) {
            futures.emplace_back(std::async(std::launch::async, [&]() {
                return crypto.transform(input, key, nonce);
                }));
        }
        for (auto& f : futures) {
            EXPECT_FALSE(f.get().empty());
        }
    }

    TEST_F(Cryptographer2Test, Should_Expect_CorrectDecryption_When_ConcurrentCallsMade) {
        std::string input = "secure";
        std::string encrypted = crypto.transform(input, key, nonce);
        std::vector<std::future<std::string>> futures;
        for (int i = 0; i < 10; ++i) {
            futures.emplace_back(std::async(std::launch::async, [&]() {
                return crypto.reverse(encrypted, key, nonce);
                }));
        }
        for (auto& f : futures) {
            EXPECT_EQ(f.get(), input);
        }
    }

    TEST_F(Cryptographer2Test, Should_Expect_PerformanceUnder2Seconds_When_TransformRepeatedly) {
        std::string input = "repeat";
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < 100000; ++i) {
            std::string out = crypto.transform(input, key, nonce);
        }
        auto end = std::chrono::steady_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::seconds>(end - start).count(), 2);
    }

    TEST_F(Cryptographer2Test, Should_Expect_TransformUnder1Millisecond_When_Encrypted) {
        std::string input = "fast";
        auto start = std::chrono::high_resolution_clock::now();
        crypto.transform(input, key, nonce);
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), 1000);
    }

    TEST_P(Cryptographer2Test, Should_Expect_CorrectReverse_When_ParameterizedInput) {
        std::string input = GetParam();
        std::string encrypted = crypto.transform(input, key, nonce);
        std::string decrypted = crypto.reverse(encrypted, key, nonce);
        EXPECT_EQ(decrypted, input);
    }

    INSTANTIATE_TEST_CASE_P(
        Cryptographer2TestSet,
        Cryptographer2Test,
        ::testing::Values(
            "", "abc", "1234567890", "special$#@!", std::string(1000, 'x')
        )
    );

    TEST_F(Cryptographer2Test, Should_Expect_Death_When_DereferencingNullInstance) {
        QLogicaeCore::Cryptographer2* ptr = nullptr;
        ASSERT_DEATH({ ptr->transform("A", key, nonce); }, "");
    }
}
