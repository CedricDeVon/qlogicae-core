#include "pch.hpp"

#include "sha256_hash_cryptographer.hpp"

namespace QLogicaeCoreTest
{
    class SHA256HashCryptographerTest : public ::testing::TestWithParam<std::string>
    {
    protected:
        QLogicaeCore::SHA256HashCryptographer cryptographer;
    };

    TEST_P(SHA256HashCryptographerTest, Should_Produce_CorrectHash_When_InputIsValid)
    {
        std::string input = GetParam();
        std::string hash = cryptographer.transform(input);
        ASSERT_FALSE(hash.empty());
        ASSERT_TRUE(cryptographer.reverse(input, hash));
    }

    TEST_P(SHA256HashCryptographerTest, Should_ReturnFalse_When_HashIsIncorrect)
    {
        std::string input = GetParam();
        std::string incorrect_hash(input);
        std::reverse(incorrect_hash.begin(), incorrect_hash.end());
        ASSERT_FALSE(cryptographer.reverse(input, incorrect_hash));
    }

    TEST_P(SHA256HashCryptographerTest, Should_Produce_AsyncHash_When_InputIsValid)
    {
        std::string input = GetParam();
        std::future<std::string> future_result =
            cryptographer.transform_async(input);
        std::string result = future_result.get();
        ASSERT_FALSE(result.empty());
        ASSERT_TRUE(cryptographer.reverse(input, result));
    }

    TEST_P(SHA256HashCryptographerTest, Should_Reverse_AsyncCorrectly)
    {
        std::string input = GetParam();
        std::string hash = cryptographer.transform(input);
        std::future<bool> future_result =
            cryptographer.reverse_async(input, hash);
        ASSERT_TRUE(future_result.get());
    }

    TEST(SHA256HashCryptographerEmptyTest, Should_ReturnEmpty_When_InputIsEmpty)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        std::string result = cryptographer.transform("");
        ASSERT_TRUE(result.empty());
    }

    TEST(SHA256HashCryptographerEmptyTest, Should_ReturnFalse_When_ReverseEmpty)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        ASSERT_FALSE(cryptographer.reverse("", ""));
    }

    TEST(SHA256HashCryptographerPerformanceTest, Should_CompleteTransformUnder2Seconds)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        std::string input(1000, 'x');
        auto start = std::chrono::steady_clock::now();
        std::string hash = cryptographer.transform(input);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        ASSERT_LT(elapsed.count(), 2.0);
    }

    TEST(SHA256HashCryptographerStressTest, Should_HandleMultipleThreadsSafely)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        std::vector<std::thread> thread_list;
        std::atomic<int> success_count = 0;
        for (int i = 0; i < 100; ++i)
        {
            thread_list.emplace_back([&cryptographer, &success_count]()
                {
                    std::string input = "stress_test_input";
                    std::string hash = cryptographer.transform(input);
                    if (cryptographer.reverse(input, hash))
                    {
                        ++success_count;
                    }
                });
        }
        for (std::thread& thread : thread_list)
        {
            thread.join();
        }
        ASSERT_EQ(success_count.load(), 100);
    }

    TEST(SHA256HashCryptographerEdgeTest, Should_HandleUnicodeInput)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        std::string input(reinterpret_cast<const char*>(u8"😀你好"));
        std::string hash = cryptographer.transform(input);
        ASSERT_FALSE(hash.empty());
        ASSERT_TRUE(cryptographer.reverse(input, hash));
    }

    TEST(SHA256HashCryptographerEdgeTest, Should_HandleLargeInput)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        std::string input(1 << 20, 'A');
        std::string hash = cryptographer.transform(input);
        ASSERT_FALSE(hash.empty());
        ASSERT_TRUE(cryptographer.reverse(input, hash));
    }

    TEST(SHA256HashCryptographerMismatchTest, Should_ReturnFalse_When_FormatMismatch)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        std::string input = "test";
        std::string hash = cryptographer.transform(input);
        std::string hex_like(hash.size() * 2, 'a');
        ASSERT_FALSE(cryptographer.reverse(input, hex_like));
    }

    TEST(SHA256HashCryptographerExceptionTest, Should_HandleExceptionInAsyncTransform)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        std::promise<std::string> promise;
        std::future<std::string> result = std::async(std::launch::async, []()
            {
                throw std::runtime_error("Test Exception");
                return std::string("");
            });
        try
        {
            std::string output = result.get();
            SUCCEED();
        }
        catch (...)
        {
            SUCCEED();
        }
    }

    INSTANTIATE_TEST_CASE_P(
        SHA256HashCryptographerParamTest,
        SHA256HashCryptographerTest,
        ::testing::Values(
            std::string("a"),
            std::string("test"),
            std::string("1234567890"),
            std::string(1000, 'x'),
            std::string("\0", 1),
            std::string(reinterpret_cast<const char*>(u8"😀")),
            std::string("\xff\xff", 2),
            std::string("\0\x01\x02\xff", 4),
            std::string(50, ' ')
        )
    );

    TEST(SHA256HashCryptographerAsyncTest,
        Should_ReturnFalse_When_ReverseAsyncFails)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        std::string input = "async_test";
        std::string fake_hash = "invalid_hash";
        std::future<bool> result =
            cryptographer.reverse_async(input, fake_hash);
        ASSERT_FALSE(result.get());
    }

    TEST(SHA256HashCryptographerAsyncTest,
        Should_HandleExceptionInReverseAsync)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        std::future<bool> result = std::async(std::launch::async, []()
            {
                throw std::runtime_error("reverse_async exception");
                return false;
            });

        try
        {
            result.get();
            FAIL();
        }
        catch (...)
        {
            SUCCEED();
        }
    }

    TEST(SHA256HashCryptographerAsyncTest,
        Should_ReturnEmpty_When_TransformAsyncInputIsEmpty)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        std::future<std::string> result =
            cryptographer.transform_async("");
        ASSERT_TRUE(result.get().empty());
    }

    TEST(SHA256HashCryptographerAsyncTest,
        Should_TransformAsyncLargeInput_Successfully)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        std::string input(1 << 20, 'X');
        std::future<std::string> result =
            cryptographer.transform_async(input);
        ASSERT_FALSE(result.get().empty());
    }

    TEST(SHA256HashCryptographerAsyncTest,
        Should_ReturnFalse_When_ReverseAsyncFormatMismatch)
    {
        QLogicaeCore::SHA256HashCryptographer cryptographer;
        std::string input = "test_async";
        std::string valid_hash = cryptographer.transform(input);
        std::string fake_hex_hash(valid_hash.size() * 2, 'a');

        std::future<bool> result =
            cryptographer.reverse_async(input, fake_hex_hash);
        ASSERT_FALSE(result.get());
    }
}
