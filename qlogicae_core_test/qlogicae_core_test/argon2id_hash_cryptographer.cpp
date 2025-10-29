#include "pch.hpp"

#include "qlogicae_core/argon2id_hash_cryptographer.hpp"

namespace QLogicaeCoreTest
{
    class Argon2idHashCryptographerTest :
        public ::testing::TestWithParam<std::string>
    {
    protected:
        QLogicaeCore::Argon2idHashCryptographer crypto;
    };

    TEST_F(Argon2idHashCryptographerTest,
        Should_Expect_TransformResult_When_ValidInput)
    {
        std::string input = "secure_password";
        std::string hash = crypto.transform(input);
        EXPECT_FALSE(hash.empty());
    }

    TEST_F(Argon2idHashCryptographerTest,
        Should_Expect_Empty_When_TransformFailsInternally)
    {
        std::string long_input(1000000, 'x');
        QLogicaeCore::CryptographerProperties weak_properties =
            QLogicaeCore::DEFAULT_CRYPTOGRAPHER_3_PROPERTIES;
        weak_properties.size_t_1 = 1;
        weak_properties.size_t_2 = 1;
        QLogicaeCore::Argon2idHashCryptographer weak_crypto(
            weak_properties);
        std::string result = weak_crypto.transform(long_input);
        EXPECT_TRUE(result.empty());
    }

    TEST_F(Argon2idHashCryptographerTest,
        Should_Expect_True_When_ReverseMatchesOriginal)
    {
        std::string input = "password123";
        std::string hash = crypto.transform(input);
        bool result = crypto.reverse(hash, input);
        EXPECT_TRUE(result);
    }

    TEST_F(Argon2idHashCryptographerTest,
        Should_Expect_False_When_ReverseFails)
    {
        std::string input = "password123";
        std::string hash = crypto.transform(input);
        bool result = crypto.reverse(hash, "wrongpassword");
        EXPECT_FALSE(result);
    }

    TEST_F(Argon2idHashCryptographerTest,
        Should_Expect_AsyncMatch_When_ComparedWithSync)
    {
        std::string input = "parallel_test";
        std::future<std::string> future_value =
            crypto.transform_async(input);
        std::string sync_value = crypto.transform(input);
        EXPECT_NE(sync_value, "");
        EXPECT_EQ(future_value.get().substr(0, 10),
            sync_value.substr(0, 10));
    }

    TEST_F(Argon2idHashCryptographerTest,
        Should_Expect_CorrectReverseAsync)
    {
        std::string input = "async_password";
        std::string hash = crypto.transform(input);
        std::future<bool> result =
            crypto.reverse_async(hash, input);
        EXPECT_TRUE(result.get());
    }

    TEST_F(Argon2idHashCryptographerTest,
        Should_Expect_CorrectResult_When_ConcurrentCallsMade)
    {
        std::string input = "multithread";
        std::vector<std::future<std::string>> futures;
        for (int index = 0; index < 10; ++index)
        {
            futures.emplace_back(std::async(std::launch::async, [&]()
                {
                    return crypto.transform(input);
                }));
        }
        for (auto& future_value : futures)
        {
            EXPECT_FALSE(future_value.get().empty());
        }
    }

    TEST_F(Argon2idHashCryptographerTest,
        Should_Expect_ReverseTrue_When_ConcurrentReverseCalls)
    {
        std::string input = "multireverse";
        std::string hash = crypto.transform(input);
        std::vector<std::future<bool>> futures;
        for (int index = 0; index < 10; ++index)
        {
            futures.emplace_back(std::async(std::launch::async, [&]()
                {
                    return crypto.reverse(hash, input);
                }));
        }
        for (auto& future_value : futures)
        {
            EXPECT_TRUE(future_value.get());
        }
    }

    TEST_F(Argon2idHashCryptographerTest,
        Should_Expect_PerformanceUnder20Seconds_When_RepeatedTransform)
    {
        std::string input = "benchmark";
        auto start = std::chrono::steady_clock::now();
        for (int index = 0; index < 100; ++index)
        {
            crypto.transform(input);
        }
        auto end = std::chrono::steady_clock::now();
        EXPECT_LE(
            std::chrono::duration_cast<std::chrono::seconds>(
                end - start).count(),
            20
        );
    }

    TEST_F(Argon2idHashCryptographerTest,
        Should_Expect_TransformUnder2Seconds_When_ShortInput)
    {
        std::string input = "short";
        auto start = std::chrono::high_resolution_clock::now();
        crypto.transform(input);
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_LE(
            std::chrono::duration_cast<std::chrono::seconds>(
                end - start).count(),
            2
        );
    }

    TEST_P(Argon2idHashCryptographerTest,
        Should_Expect_ValidHash_When_ParameterizedInputsUsed)
    {
        std::string input = GetParam();
        std::string hash = crypto.transform(input);
        EXPECT_FALSE(hash.empty());
    }

    INSTANTIATE_TEST_CASE_P(
        Argon2idHashCryptographerTestSet,
        Argon2idHashCryptographerTest,
        ::testing::Values(
            "", "a", "123456", "complex_string$#@!",
            std::string(500, 'y')
        )
    );

    TEST_F(Argon2idHashCryptographerTest,
        Should_Expect_Death_When_NullptrAccessed)
    {
        QLogicaeCore::Argon2idHashCryptographer* pointer = nullptr;
        ASSERT_DEATH(
            {
                pointer->transform("crash");
            }, "");
    }
}
