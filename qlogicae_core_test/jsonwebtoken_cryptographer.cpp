#include "pch.h"

#include "qlogicae_core/jsonwebtoken_cryptographer.hpp"

namespace QLogicaeCoreTest
{
    class JsonWebTokenCryptographerNegativeTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::JsonWebTokenCryptographer cryptographer;
    };

    class JsonWebTokenCryptographerTest : public ::testing::TestWithParam<
        std::tuple<std::string, std::string>>
    {
    protected:
        QLogicaeCore::JsonWebTokenCryptographer cryptographer;

        std::string private_key =
            "-----BEGIN EC PRIVATE KEY-----\n"
            "MHQCAQEEIArnQWnspKtjiVuZuzuZ/l1Uqqq8gb2unLJ/6U/Saf4ioAcGBSuBBAAK\n"
            "oUQDQgAEfy03KCKUpIPMIJBtIG4xOwGm0Np/yHKaK9EDZi0mZ7VUeeNKq476CU5X\n"
            "940yusahgneePQrDMF2nWFEtBCOiXQ==\n"
            "-----END EC PRIVATE KEY-----";

        std::string public_key =
            "-----BEGIN PUBLIC KEY-----\n"
            "MFYwEAYHKoZIzj0CAQYFK4EEAAoDQgAEfy03KCKUpIPMIJBtIG4xOwGm0Np/yHKa\n"
            "K9EDZi0mZ7VUeeNKq476CU5X940yusahgneePQrDMF2nWFEtBCOiXQ==\n"
            "-----END PUBLIC KEY-----";

        std::string issuer = "auth0";
        std::chrono::seconds lifetime = std::chrono::hours(1);
    };

    TEST_P(JsonWebTokenCryptographerTest,
        Should_Transform_And_Reverse_When_Valid)
    {
        const std::string subject = std::get<0>(GetParam());

        QLogicaeCore::JsonWebTokenTransformInput input;
        input.issuer = issuer;
        input.data = subject;
        input.public_key = public_key;
        input.private_key = private_key;
        input.lifetime = lifetime;
        input.claims = { {"role", "admin"} };

        std::string token = cryptographer.transform(input);
        ASSERT_FALSE(token.empty());

        QLogicaeCore::JsonWebTokenReverseInput verify;
        verify.token = token;
        verify.issuer = issuer;
        verify.public_key = public_key;

        auto result = cryptographer.reverse(verify);
        ASSERT_TRUE(result.is_successful);
        ASSERT_EQ(result.subject, subject);
    }

    TEST_P(JsonWebTokenCryptographerTest,
        Should_ReverseAsync_Succeed_When_Valid)
    {
        const std::string subject = std::get<0>(GetParam());

        QLogicaeCore::JsonWebTokenTransformInput input;
        input.issuer = issuer;
        input.data = subject;
        input.public_key = public_key;
        input.private_key = private_key;
        input.lifetime = lifetime;

        std::string token = cryptographer.transform(input);

        QLogicaeCore::JsonWebTokenReverseInput verify;
        verify.token = token;
        verify.issuer = issuer;
        verify.public_key = public_key;

        auto future = cryptographer.reverse_async(verify);
        ASSERT_TRUE(future.wait_for(std::chrono::seconds(2)) ==
            std::future_status::ready);
        ASSERT_TRUE(future.get().is_successful);
    }

    TEST_P(JsonWebTokenCryptographerTest,
        Should_Handle_Concurrent_Reverses_Correctly)
    {
        const std::string subject = std::get<0>(GetParam());

        QLogicaeCore::JsonWebTokenTransformInput input;
        input.issuer = issuer;
        input.data = subject;
        input.public_key = public_key;
        input.private_key = private_key;
        input.lifetime = lifetime;

        std::string token = cryptographer.transform(input);

        QLogicaeCore::JsonWebTokenReverseInput verify;
        verify.token = token;
        verify.issuer = issuer;
        verify.public_key = public_key;

        std::atomic<int> success_count = 0;
        std::vector<std::thread> threads;

        for (int i = 0; i < 10; ++i)
        {
            threads.emplace_back([&, verify]()
                {
                    if (cryptographer.reverse(verify).is_successful)
                    {
                        success_count.fetch_add(1);
                    }
                });
        }

        for (auto& t : threads)
        {
            t.join();
        }

        ASSERT_EQ(success_count.load(), 10);
    }

    INSTANTIATE_TEST_CASE_P(
        ValidJwtSubjects,
        JsonWebTokenCryptographerTest,
        ::testing::Values(
            std::make_tuple("user1", "wrong1"),
            std::make_tuple("admin@example", "wrongadmin"),
            std::make_tuple("A", "Z"),
            std::make_tuple(std::string(1024, 'X'), "y")
        ));

    TEST_F(JsonWebTokenCryptographerNegativeTest,
        Should_ReturnEmpty_When_MissingKeys)
    {
        QLogicaeCore::JsonWebTokenTransformInput input;
        input.issuer = "auth0";
        input.data = "_subject";
        input.public_key = "";
        input.private_key = "";
        input.lifetime = std::chrono::minutes(10);

        std::string token = cryptographer.transform(input);
        ASSERT_TRUE(token.empty());
    }

    TEST_F(JsonWebTokenCryptographerNegativeTest,
        Should_ReturnEmpty_When_InvalidLifetime)
    {
        QLogicaeCore::JsonWebTokenTransformInput input;
        input.issuer = "auth0";
        input.data = "_subject";
        input.public_key = "key";
        input.private_key = "key";
        input.lifetime = std::chrono::seconds(0);

        std::string token = cryptographer.transform(input);
        ASSERT_TRUE(token.empty());
    }
}
