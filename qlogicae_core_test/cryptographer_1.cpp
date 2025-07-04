#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{

    class Cryptographer1Test : public ::testing::TestWithParam<std::string> {
    protected:
        QLogicaeCore::Cryptographer1 crypto;
        unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES]{};
        unsigned char nonce[crypto_aead_xchacha20poly1305_ietf_NPUBBYTES]{};

        void SetUp() override {
            QLogicaeCore::Generator::instance().random_bytes(key, sizeof(key));
            QLogicaeCore::Generator::instance().random_bytes(nonce, sizeof(nonce));
        }
    };

    TEST_F(Cryptographer1Test, Should_Expect_ValidTransformAndReverse_When_GivenCorrectInput) {
        std::string input = "Hello, world!";
        std::string encoded = crypto.transform(input, key, nonce);
        std::string decoded = crypto.reverse(encoded, key, nonce);
        EXPECT_EQ(decoded, input);
    }

    TEST_F(Cryptographer1Test, Should_Expect_Empty_When_KeyOrNonceNull) {
        std::string input = "data";
        EXPECT_EQ(crypto.transform(input, nullptr, nonce), "");
        EXPECT_EQ(crypto.transform(input, key, nullptr), "");
        EXPECT_EQ(crypto.reverse("...", nullptr, nonce), "");
        EXPECT_EQ(crypto.reverse("...", key, nullptr), "");
    }

    TEST_F(Cryptographer1Test, Should_Expect_Empty_When_InvalidBase64Input) {
        std::string input = "$$$$"; // invalid base64
        EXPECT_EQ(crypto.reverse(input, key, nonce), "");
    }

    TEST_F(Cryptographer1Test, Should_Expect_Empty_When_DecryptFails) {
        std::string input = crypto.transform("secure text", key, nonce);
        unsigned char wrong_key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES]{};
        std::string result = crypto.reverse(input, wrong_key, nonce);
        EXPECT_EQ(result, "");
    }

    TEST_F(Cryptographer1Test, Should_Expect_Empty_When_EncryptFailsGracefully) {
        EXPECT_EQ(crypto.transform("fail", key, nullptr), "");
        EXPECT_EQ(crypto.transform("fail", nullptr, nonce), "");
    }

    TEST_F(Cryptographer1Test, Should_Expect_AsyncMatch_When_ComparedWithSync) {
        std::string input = "parallel";
        auto f = crypto.transform_async(input, key, nonce);
        std::string sync = crypto.transform(input, key, nonce);
        EXPECT_EQ(f.get(), sync);
    }

    TEST_F(Cryptographer1Test, Should_Expect_CorrectReverseAsync) {
        std::string input = "value";
        std::string encrypted = crypto.transform(input, key, nonce);
        auto f = crypto.reverse_async(encrypted, key, nonce);
        EXPECT_EQ(f.get(), input);
    }

    TEST_F(Cryptographer1Test, Should_Expect_CorrectMultithreadedTransformation) {
        std::string input = "thread-safe";
        std::vector<std::future<std::string>> futures;
        for (int i = 0; i < 10; ++i) {
            futures.emplace_back(std::async(std::launch::async, [&] {
                return crypto.transform(input, key, nonce);
                }));
        }
        for (auto& f : futures) {
            EXPECT_FALSE(f.get().empty());
        }
    }

    TEST_F(Cryptographer1Test, Should_Expect_CorrectMultithreadedReverse) {
        std::string input = "data";
        std::string encoded = crypto.transform(input, key, nonce);
        std::vector<std::future<std::string>> futures;
        for (int i = 0; i < 10; ++i) {
            futures.emplace_back(std::async(std::launch::async, [&] {
                return crypto.reverse(encoded, key, nonce);
                }));
        }
        for (auto& f : futures) {
            EXPECT_EQ(f.get(), input);
        }
    }

    TEST_F(Cryptographer1Test, Should_Expect_PerformanceUnder2Seconds_When_StressEncrypted100000) {
        std::string input = "timing";
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < 100000; ++i) {
            std::string out = crypto.transform(input, key, nonce);
        }
        auto end = std::chrono::steady_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::seconds>(end - start).count(), 2);
    }

    TEST_F(Cryptographer1Test, Should_Expect_TransformUnder1Millisecond) {
        std::string input = "a";
        auto start = std::chrono::high_resolution_clock::now();
        crypto.transform(input, key, nonce);
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), 1000);
    }

    TEST_P(Cryptographer1Test, Should_Expect_ValidTransformAndReverse_When_Parameterized) {
        std::string input = GetParam();
        std::string out = crypto.transform(input, key, nonce);
        std::string back = crypto.reverse(out, key, nonce);
        EXPECT_EQ(back, input);
    }

    INSTANTIATE_TEST_CASE_P(
        Cryptographer1TestSet,
        Cryptographer1Test,
        ::testing::Values(
            "", "short", "loooooooooooooooooooongstring", "1234567890", "!@#$%^&*()"
        )
    );

    TEST_F(Cryptographer1Test, Should_Expect_Death_When_DereferencingNullCrypto) {
        QLogicaeCore::Cryptographer1* ptr = nullptr;
        ASSERT_DEATH({ ptr->transform("A", key, nonce); }, "");
    }
}
