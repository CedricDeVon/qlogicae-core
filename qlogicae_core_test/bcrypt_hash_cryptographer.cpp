#include "pch.h"

#include "qlogicae_core/bcrypt_hash_cryptographer.hpp"

namespace QLogicaeCoreTest
{
    class BcryptHashCryptographerTest : public ::testing::TestWithParam<
        std::tuple<std::string, std::string>>
    {
    protected:
        QLogicaeCore::BcryptHashCryptographer cryptographer;
    };

    class BcryptHashCryptographerNegativeTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::BcryptHashCryptographer cryptographer;
    };

    TEST_P(BcryptHashCryptographerTest, Should_Hash_Successfully_When_Valid)
    {
        const std::string password = std::get<0>(GetParam());
        ASSERT_NO_THROW({
            std::string result = cryptographer.transform(password);
            ASSERT_FALSE(result.empty());
            });
    }

    TEST_P(BcryptHashCryptographerTest, Should_Verify_True_When_HashMatches)
    {
        const std::string password = std::get<0>(GetParam());
        std::string hash = cryptographer.transform(password);
        ASSERT_TRUE(cryptographer.reverse(password, hash));
    }

    TEST_P(BcryptHashCryptographerTest, Should_Verify_False_When_HashMismatches)
    {
        const std::string wrong_password = std::get<1>(GetParam());
        const std::string actual_password = std::get<0>(GetParam());
        std::string hash = cryptographer.transform(actual_password);
        ASSERT_FALSE(cryptographer.reverse(wrong_password, hash));
    }

    TEST_P(BcryptHashCryptographerTest, Should_AsyncTransform_Quickly_When_Valid)
    {
        const std::string password = std::get<0>(GetParam());
        auto future = cryptographer.transform_async(password);
        ASSERT_TRUE(future.wait_for(std::chrono::seconds(2)) ==
            std::future_status::ready);
        ASSERT_FALSE(future.get().empty());
    }

    TEST_P(BcryptHashCryptographerTest, Should_AsyncReverse_True_When_Correct)
    {
        const std::string password = std::get<0>(GetParam());
        std::string hash = cryptographer.transform(password);
        auto future = cryptographer.reverse_async(password, hash);
        ASSERT_TRUE(future.wait_for(std::chrono::seconds(2)) ==
            std::future_status::ready);
        ASSERT_TRUE(future.get());
    }

    TEST_P(BcryptHashCryptographerTest, Should_AsyncReverse_False_When_Incorrect)
    {
        const std::string password = std::get<0>(GetParam());
        const std::string wrong = std::get<1>(GetParam());
        std::string hash = cryptographer.transform(password);
        auto future = cryptographer.reverse_async(wrong, hash);
        ASSERT_TRUE(future.wait_for(std::chrono::seconds(2)) ==
            std::future_status::ready);
        ASSERT_FALSE(future.get());
    }

    TEST_P(BcryptHashCryptographerTest, Should_Handle_Multithreaded_Access)
    {
        const std::string password = std::get<0>(GetParam());
        std::string hash = cryptographer.transform(password);
        std::atomic<int> success_count = 0;
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i)
        {
            threads.emplace_back([&]
                {
                    if (cryptographer.reverse(password, hash))
                    {
                        success_count.fetch_add(1);
                    }
                });
        }
        for (auto& thread : threads)
        {
            thread.join();
        }
        ASSERT_EQ(success_count.load(), 10);
    }

    INSTANTIATE_TEST_CASE_P(
        BcryptValidInputs,
        BcryptHashCryptographerTest,
        ::testing::Values(
            std::make_tuple("helloWorld1", "badPass1"),
            std::make_tuple("12345678", "87654321"),
            std::make_tuple("correcthorsebatterystaple", "wrongpass"),
            std::make_tuple("admin!@#", "ADMIN!@#"),
            std::make_tuple(std::string(1024, 'x'), std::string(1024, 'y'))
        ));

    TEST_F(BcryptHashCryptographerNegativeTest,
        Should_ReturnFalse_When_Reversing_EmptyInputs)
    {
        ASSERT_FALSE(cryptographer.reverse("", ""));
    }
}

