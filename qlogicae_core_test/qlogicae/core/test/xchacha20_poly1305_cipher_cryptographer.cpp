#include "pch.hpp"

#include "qlogicae/core/generator.hpp"
#include "qlogicae/core/xchacha20_poly1305_cipher_cryptographer.hpp"

namespace QLogicaeCoreTest
{
    class XChaCha20Poly1305CipherCryptographerTest : public ::testing::TestWithParam<std::string>
    {
    protected:
        QLogicaeCore::XChaCha20Poly1305CipherCryptographer crypto;
        unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES]{};
        unsigned char nonce[crypto_aead_xchacha20poly1305_ietf_NPUBBYTES]{};

        void SetUp() override
        {
            QLogicaeCore::Generator::get_instance().random_bytes(key, sizeof(key));
            QLogicaeCore::Generator::get_instance().random_bytes(nonce, sizeof(nonce));
        }
    };

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_ValidTransformAndReverse_When_GivenCorrectInput)
    {
        std::string input = "Hello, world!";
        std::string encrypted = crypto.transform(input, key, nonce);
        std::string decrypted = crypto.reverse(encrypted, key, nonce);
        EXPECT_EQ(decrypted, input);
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_Empty_When_KeyOrNonceNull)
    {
        std::string input = "data";
        EXPECT_EQ(crypto.transform(input, nullptr, nonce), "");
        EXPECT_EQ(crypto.transform(input, key, nullptr), "");
        EXPECT_EQ(crypto.reverse("...", nullptr, nonce), "");
        EXPECT_EQ(crypto.reverse("...", key, nullptr), "");
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_Empty_When_InvalidBase64Input)
    {
        std::string input = "####";
        EXPECT_EQ(crypto.reverse(input, key, nonce), "");
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_Empty_When_DecryptFails)
    {
        std::string input = crypto.transform("secure text", key, nonce);
        unsigned char wrong_key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES]{};
        std::string result = crypto.reverse(input, wrong_key, nonce);
        EXPECT_EQ(result, "");
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_Empty_When_EncryptFailsGracefully)
    {
        EXPECT_EQ(crypto.transform("fail", key, nullptr), "");
        EXPECT_EQ(crypto.transform("fail", nullptr, nonce), "");
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_AsyncMatch_When_ComparedWithSync)
    {
        std::string input = "parallel";
        auto async_future = crypto.transform_async(input, key, nonce);
        std::string sync = crypto.transform(input, key, nonce);
        EXPECT_EQ(async_future.get(), sync);
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_CorrectReverseAsync)
    {
        std::string input = "value";
        std::string encrypted = crypto.transform(input, key, nonce);
        auto async_future = crypto.reverse_async(encrypted, key, nonce);
        EXPECT_EQ(async_future.get(), input);
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_CorrectMultithreadedTransformation)
    {
        std::string input = "thread-safe";
        std::vector<std::future<std::string>> results;
        for (int i = 0; i < 10; ++i)
        {
            results.emplace_back(std::async(std::launch::async, [&] {
                return crypto.transform(input, key, nonce);
                }));
        }
        for (auto& result : results)
        {
            EXPECT_FALSE(result.get().empty());
        }
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_CorrectMultithreadedReverse)
    {
        std::string input = "data";
        std::string encoded = crypto.transform(input, key, nonce);
        std::vector<std::future<std::string>> results;
        for (int i = 0; i < 10; ++i)
        {
            results.emplace_back(std::async(std::launch::async, [&] {
                return crypto.reverse(encoded, key, nonce);
                }));
        }
        for (auto& result : results)
        {
            EXPECT_EQ(result.get(), input);
        }
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_PerformanceUnder2Seconds_When_StressEncrypted100000)
    {
        std::string input = "timing";
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < 100000; ++i)
        {
            crypto.transform(input, key, nonce);
        }
        auto end = std::chrono::steady_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::seconds>(
            end - start).count(),
            2);
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_TransformUnder1Millisecond)
    {
        std::string input = "a";
        auto start = std::chrono::high_resolution_clock::now();
        crypto.transform(input, key, nonce);
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::microseconds>(
            end - start).count(),
            1000);
    }

    TEST_P(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_ValidTransformAndReverse_When_Parameterized)
    {
        std::string input = GetParam();
        std::string encrypted = crypto.transform(input, key, nonce);
        std::string decrypted = crypto.reverse(encrypted, key, nonce);
        EXPECT_EQ(decrypted, input);
    }

    INSTANTIATE_TEST_CASE_P(
        XChaCha20Poly1305CipherCryptographerTestSet,
        XChaCha20Poly1305CipherCryptographerTest,
        ::testing::Values(
            "", "short", "loooooooooooooooooooongstring",
            "1234567890", "!@#$%^&*()"
        )
    );

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_Death_When_DereferencingNullCrypto)
    {
        QLogicaeCore::XChaCha20Poly1305CipherCryptographer* pointer = nullptr;
        ASSERT_DEATH(
            {
                pointer->transform("A", key, nonce);
            },
            ""
        );
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_Empty_When_EncryptedDataTooShort)
    {
        std::string input = "a";
        std::string short_input = QLogicaeCore::Encoder::get_instance()
            .from_bytes_to_base64(reinterpret_cast<const unsigned char*>(
                input.data()), input.size());
        EXPECT_EQ(crypto.reverse(short_input, key, nonce), "");
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_Success_When_InputContainsNullBytes)
    {
        std::string input = std::string("a\0b\0c", 5);
        std::string encrypted = crypto.transform(input, key, nonce);
        std::string decrypted = crypto.reverse(encrypted, key, nonce);
        EXPECT_EQ(decrypted, input);
    }

    TEST_F(XChaCha20Poly1305CipherCryptographerTest,
        Should_Expect_Success_When_TransformWithStringViewKeyNonce)
    {
        std::string input = "string-view";
        std::string k(reinterpret_cast<const char*>(key),
            crypto_aead_xchacha20poly1305_ietf_KEYBYTES);
        std::string n(reinterpret_cast<const char*>(nonce),
            crypto_aead_xchacha20poly1305_ietf_NPUBBYTES);
        std::string encrypted = crypto.transform(input, k, n);
        std::string decrypted = crypto.reverse(encrypted, k, n);
        EXPECT_EQ(decrypted, input);
    }

}
