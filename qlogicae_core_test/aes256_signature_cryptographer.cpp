#include "pch.h"

#include "aes256_signature_cryptographer.hpp"

namespace QLogicaeCoreTest
{
    class AES256SignatureCryptographerTest :
        public ::testing::TestWithParam<std::string>
    {
    protected:
        QLogicaeCore::AES256SignatureCryptographer cryptographer;
        std::array<unsigned char, crypto_sign_PUBLICKEYBYTES> public_key{};
        std::array<unsigned char, crypto_sign_SECRETKEYBYTES> secret_key{};

        void SetUp() override
        {
            crypto_sign_keypair(public_key.data(), secret_key.data());
        }
    };

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Encoded_When_TransformValidInput)
    {
        std::string_view input = "message";
        std::string result = cryptographer.transform(
            input, public_key.data(), secret_key.data());
        EXPECT_FALSE(result.empty());
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Empty_When_NullKeysUsed)
    {
        std::string_view input = "nullkeys";
        std::string result = cryptographer.transform(input, nullptr, nullptr);
        EXPECT_TRUE(result.empty());
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Original_When_ReverseValidSignature)
    {
        std::string_view input = "signed";
        std::string signed_data = cryptographer.transform(
            input, public_key.data(), secret_key.data());
        std::string result = cryptographer.reverse(
            signed_data, public_key.data());
        EXPECT_EQ(result, input);
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Empty_When_ReverseFailsDueToBadKey)
    {
        std::string_view input = "invalid";
        std::string signed_data = cryptographer.transform(
            input, public_key.data(), secret_key.data());

        std::array<unsigned char, crypto_sign_PUBLICKEYBYTES> wrong_key{};
        crypto_sign_keypair(wrong_key.data(), secret_key.data());

        std::string result = cryptographer.reverse(signed_data, wrong_key.data());
        EXPECT_TRUE(result.empty());
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Empty_When_ReverseGivenNullKey)
    {
        std::string signed_data = cryptographer.transform(
            "check", public_key.data(), secret_key.data());
        std::string result = cryptographer.reverse(signed_data, nullptr);
        EXPECT_TRUE(result.empty());
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_ValidSignature_When_TransformAsync)
    {
        std::string_view input = "async";
        std::future<std::string> future_result =
            cryptographer.transform_async(input,
                public_key.data(), secret_key.data());
        EXPECT_FALSE(future_result.get().empty());
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Original_When_ReverseAsyncMatches)
    {
        std::string_view input = "parallel";
        std::string signed_data = cryptographer.transform(
            input, public_key.data(), secret_key.data());
        std::future<std::string> future_result =
            cryptographer.reverse_async(signed_data, public_key.data());
        EXPECT_EQ(future_result.get(), input);
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Correct_When_MultipleConcurrentTransformCallsMade)
    {
        std::string_view input = "multisign";
        std::vector<std::future<std::string>> futures;

        for (int index = 0; index < 10; ++index)
        {
            futures.emplace_back(std::async(std::launch::async, [&]()
                {
                    return cryptographer.transform(input,
                        public_key.data(), secret_key.data());
                }));
        }

        for (auto& future : futures)
        {
            EXPECT_FALSE(future.get().empty());
        }
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Correct_When_MultipleConcurrentReverseCallsMade)
    {
        std::string_view input = "verifymany";
        std::string signed_data = cryptographer.transform(
            input, public_key.data(), secret_key.data());
        std::vector<std::future<std::string>> futures;

        for (int index = 0; index < 10; ++index)
        {
            futures.emplace_back(std::async(std::launch::async, [&]()
                {
                    return cryptographer.reverse(signed_data, public_key.data());
                }));
        }

        for (auto& future : futures)
        {
            EXPECT_EQ(future.get(), input);
        }
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_CompleteUnder2Seconds_When_StressTestTransform)
    {
        std::string_view input = "load";
        auto start = std::chrono::steady_clock::now();

        for (int index = 0; index < 100; ++index)
        {
            cryptographer.transform(input,
                public_key.data(), secret_key.data());
        }

        auto end = std::chrono::steady_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::seconds>(
            end - start).count(), 2);
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_CompleteUnder1Millisecond_When_ShortMessage)
    {
        std::string_view input = "x";
        auto start = std::chrono::high_resolution_clock::now();
        cryptographer.transform(input,
            public_key.data(), secret_key.data());
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::microseconds>(
            end - start).count(), 1000);
    }

    TEST_P(AES256SignatureCryptographerTest,
        Should_Expect_ValidTransform_When_VariousInputsUsed)
    {
        std::string_view input = GetParam();
        std::string signed_data = cryptographer.transform(
            input, public_key.data(), secret_key.data());
        std::string result = cryptographer.reverse(
            signed_data, public_key.data());
        EXPECT_EQ(result, input);
    }

    INSTANTIATE_TEST_CASE_P(
        AES256SignatureCryptographerTestSet,
        AES256SignatureCryptographerTest,
        ::testing::Values(
            "", "a", "sample", "1234567890",
            "!@#$%^&*()", std::string(100, 'Z')
        )
    );

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Death_When_NullPointerUsed)
    {
        QLogicaeCore::AES256SignatureCryptographer* ptr = nullptr;
        ASSERT_DEATH(
            {
                ptr->transform("fail", public_key.data(), secret_key.data());
            }, "");
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Empty_When_SignatureTampered)
    {
        std::string_view input = "payload";
        std::string signed_data = cryptographer.transform(
            input, public_key.data(), secret_key.data());
        signed_data[10] ^= 0xFF;
        std::string result = cryptographer.reverse(
            signed_data, public_key.data());
        EXPECT_TRUE(result.empty());
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Correct_When_InputHasNullBytes)
    {
        std::string input = std::string("a\0b", 3);
        std::string signed_data = cryptographer.transform(
            input, public_key.data(), secret_key.data());
        std::string result = cryptographer.reverse(
            signed_data, public_key.data());
        EXPECT_EQ(result, input);
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Correct_When_UsingStringViewKeyOverloads)
    {
        std::string_view input = "abc123";
        std::string pub_key(reinterpret_cast<char*>(public_key.data()),
            public_key.size());
        std::string sec_key(reinterpret_cast<char*>(secret_key.data()),
            secret_key.size());

        std::string signed_data = cryptographer.transform(
            input, pub_key, sec_key);
        std::string result = cryptographer.reverse(signed_data, pub_key);
        EXPECT_EQ(result, input);
    }

    TEST_F(AES256SignatureCryptographerTest,
        Should_Expect_Correct_When_ReverseAsyncWithStringViewKey)
    {
        std::string_view input = "verifyview";
        std::string public_key_string(
            reinterpret_cast<char*>(public_key.data()),
            public_key.size());
        std::string secret_key_string(
            reinterpret_cast<char*>(secret_key.data()),
            secret_key.size());

        std::string signed_data = cryptographer.transform(
            input, public_key_string, secret_key_string);

        std::future<std::string> future_result = cryptographer.reverse_async(
            signed_data, public_key_string);

        EXPECT_EQ(future_result.get(), input);
    }
}
