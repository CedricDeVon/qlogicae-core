#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonWebTokenCryptographyManager \
	)

#include "../includes/jsonwebtoken_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{    
    TEST_F(JsonWebTokenCryptographyManagerTest, Should_ReturnNonEmptySignature_When_ValidKeysAndText)
    {
        std::string signature = manager.sign_text("test_text",
                                                  test_public_key,
                                                  test_private_key);
        EXPECT_FALSE(signature.empty());
    }

    TEST_F(JsonWebTokenCryptographyManagerTest, Should_ReturnEmptyString_When_InvalidPrivateKey)
    {
        std::string signature = manager.sign_text("test_text",
                                                  test_public_key,
                                                  "");
        EXPECT_TRUE(signature.empty());
    }

    TEST_F(JsonWebTokenCryptographyManagerTest, Should_ReturnPayload_When_VerifyValidSignature)
    {
        std::string signed_text = manager.sign_text("test_subject",
                                                    test_public_key,
                                                    test_private_key);
        std::string payload = manager.verify_text(signed_text,
                                                  test_public_key);
        EXPECT_FALSE(payload.empty());
    }

    TEST_F(JsonWebTokenCryptographyManagerTest, Should_ReturnEmptyString_When_VerifyInvalidSignature)
    {
        std::string payload = manager.verify_text("invalid_token",
                                                  test_public_key);
        EXPECT_TRUE(payload.empty());
    }

    TEST_F(JsonWebTokenCryptographyManagerTest, Should_HandleAsyncSigningAndVerification)
    {
        auto future_signature = std::async(std::launch::async, [&]
        {
            return manager.sign_text("async_test",
                                     test_public_key,
                                     test_private_key);
        });

        std::string signature = future_signature.get();
        EXPECT_FALSE(signature.empty());

        auto future_verify = std::async(std::launch::async, [&]
        {
            return manager.verify_text(signature,
                                       test_public_key);
        });

        std::string payload = future_verify.get();
        EXPECT_FALSE(payload.empty());
    }

    TEST_F(JsonWebTokenCryptographyManagerTest, Should_HandleMultithreadedSigning)
    {
        std::vector<std::thread> threads;
        std::atomic<size_t> success_count{0};

        for (size_t index = 0; index < 8; ++index)
        {
            threads.emplace_back([&]
            {
                std::string result = manager.sign_text("thread_text",
                                                       test_public_key,
                                                       test_private_key);
                if (!result.empty())
                {
                    ++success_count;
                }
            });
        }

        for (auto& thread_instance : threads)
        {
            thread_instance.join();
        }

        EXPECT_EQ(success_count.load(), 8);
    }

    TEST_F(JsonWebTokenCryptographyManagerTest, Should_HandleStressSigning)
    {
        for (size_t iteration = 0; iteration < 500; ++iteration)
        {
            std::string signature = manager.sign_text("stress_text",
                                                      test_public_key,
                                                      test_private_key);
            EXPECT_FALSE(signature.empty());
        }
    }

    TEST_P(JsonWebTokenParameterizedTest, Should_SignAndVerifyAccordingToParameters)
    {
        const JsonWebTokenParameter& parameter = GetParam();
        std::string signature = manager.sign_text(parameter.text,
                                                  parameter.public_key,
                                                  parameter.private_key);
        if (parameter.expected_success)
        {
            EXPECT_FALSE(signature.empty());
            std::string payload = manager.verify_text(signature,
                                                      parameter.public_key);
            EXPECT_FALSE(payload.empty());
        }
        else
        {
            EXPECT_TRUE(signature.empty());
        }
    }

    INSTANTIATE_TEST_CASE_P(
		JsonWebTokenTests,
		JsonWebTokenParameterizedTest,
		::testing::Values(
			JsonWebTokenParameter{
				"text1",
"-----BEGIN PUBLIC KEY-----\n"
"MFYwEAYHKoZIzj0CAQYFK4EEAAoDQgAEfy03KCKUpIPMIJBtIG4xOwGm0Np/yHKa\n"
"K9EDZi0mZ7VUeeNKq476CU5X940yusahgneePQrDMF2nWFEtBCOiXQ==\n"
"-----END PUBLIC KEY-----",
"-----BEGIN EC PRIVATE KEY-----\n"
"MHQCAQEEIArnQWnspKtjiVuZuzuZ/l1Uqqq8gb2unLJ/6U/Saf4ioAcGBSuBBAAK\n"
"oUQDQgAEfy03KCKUpIPMIJBtIG4xOwGm0Np/yHKaK9EDZi0mZ7VUeeNKq476CU5X\n"
"940yusahgneePQrDMF2nWFEtBCOiXQ==\n"
"-----END EC PRIVATE KEY-----",
				true
			},
			JsonWebTokenParameter{
				"text2",
"-----BEGIN PUBLIC KEY-----\n"
"MFYwEAYHKoZIzj0CAQYFK4EEAAoDQgAEfy03KCKUpIPMIJBtIG4xOwGm0Np/yHKa\n"
"K9EDZi0mZ7VUeeNKq476CU5X940yusahgneePQrDMF2nWFEtBCOiXQ==\n"
"-----END PUBLIC KEY-----",
				"",
				false
			},
			JsonWebTokenParameter{
				"",
"-----BEGIN PUBLIC KEY-----\n"
"MFYwEAYHKoZIzj0CAQYFK4EEAAoDQgAEfy03KCKUpIPMIJBtIG4xOwGm0Np/yHKa\n"
"K9EDZi0mZ7VUeeNKq476CU5X940yusahgneePQrDMF2nWFEtBCOiXQ==\n"
"-----END PUBLIC KEY-----",
"-----BEGIN EC PRIVATE KEY-----\n"
"MHQCAQEEIArnQWnspKtjiVuZuzuZ/l1Uqqq8gb2unLJ/6U/Saf4ioAcGBSuBBAAK\n"
"940yusahgneePQrDMF2nWFEtBCOiXQ==\n"
"-----END EC PRIVATE KEY-----",
				false
			},
			JsonWebTokenParameter{
				"text3",
				"",
"-----BEGIN EC PRIVATE KEY-----\n"
"MHQCAQEEIArnQWnspKtjiVuZuzuZ/l1Uqqq8gb2unLJ/6U/Saf4ioAcGBSuBBAAK\n"
"oUQDQgAEfy03KCKUpIPMIJBtIG4xOwGm0Np/yHKaK9EDZi0mZ7VUeeNKq476CU5X\n"
"940yusahgneePQrDMF2nWFEtBCOiXQ==\n"
"-----END EC PRIVATE KEY-----",
				false
			}
		)
	);

	TEST_F(JsonWebTokenCryptographyManagerTest, Should_HandleExceptionsDuringSigning)
	{
		std::string signature = manager.sign_text("text", "invalid_public_key", "invalid_private_key");
		EXPECT_TRUE(signature.empty());
	}

	TEST_F(JsonWebTokenCryptographyManagerTest, Should_CompleteSigningUnder2Seconds)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		std::string signature = manager.sign_text("perf_text", test_public_key, test_private_key);
		auto duration = std::chrono::high_resolution_clock::now() - start_time;
		EXPECT_FALSE(signature.empty());
		EXPECT_LT(std::chrono::duration_cast<std::chrono::seconds>(duration).count(), 2);
	}

	TEST_F(JsonWebTokenCryptographyManagerTest, Should_HandleLongText)
	{
		std::string long_text(10000, 'x');
		std::string token = manager.sign_text(long_text, test_public_key, test_private_key);
		EXPECT_FALSE(token.empty());
		std::string payload = manager.verify_text(token, test_public_key);
		EXPECT_FALSE(payload.empty());
	}

	TEST_F(JsonWebTokenCryptographyManagerTest, Should_HandleAsyncMultithreadedSigningStress)
	{
		std::vector<std::future<std::string>> futures;
		for (size_t i = 0; i < 16; ++i)
		{
			futures.push_back(std::async(std::launch::async, [&]{
				return manager.sign_text("stress_async_text", test_public_key, test_private_key);
			}));
		}
		for (auto& future_token : futures)
		{
			EXPECT_FALSE(future_token.get().empty());
		}
	}

	TEST_F(JsonWebTokenCryptographyManagerTest, Should_FailVerificationWithInvalidPublicKey)
	{
		std::string token = manager.sign_text("text", test_public_key, test_private_key);
		std::string payload = manager.verify_text(token, "-----BEGIN PUBLIC KEY-----\nINVALID\n-----END PUBLIC KEY-----");
		EXPECT_TRUE(payload.empty());
	}

	TEST_F(JsonWebTokenCryptographyManagerTest, Should_EmbedAndRetrieveClaims)
	{
		manager.configurations.claims = { {"claimA", "valueA"}, {"claimB", "valueB"} };
		std::string token = manager.sign_text("subject", test_public_key, test_private_key);
		std::string payload = manager.verify_text(token, test_public_key);
		EXPECT_FALSE(payload.empty());
		EXPECT_NE(payload.find("claimA"), std::string::npos);
		EXPECT_NE(payload.find("claimB"), std::string::npos);
	}

	TEST_F(JsonWebTokenCryptographyManagerTest, Should_HandleImmediateExpiration)
	{
		manager.configurations.lifetime = std::chrono::seconds{0};
		std::string token = manager.sign_text("text", test_public_key, test_private_key);
		std::this_thread::sleep_for(std::chrono::seconds{1});
		std::string payload = manager.verify_text(token, test_public_key);
		EXPECT_FALSE(payload.empty());
	}

	TEST_F(JsonWebTokenCryptographyManagerTest, Should_HandleLongLifetime)
	{
		manager.configurations.lifetime = std::chrono::hours{24};
		std::string token = manager.sign_text("text", test_public_key, test_private_key);
		std::string payload = manager.verify_text(token, test_public_key);
		EXPECT_FALSE(payload.empty());
	}

	TEST_F(JsonWebTokenCryptographyManagerTest, Should_HandleThreadSafetyOnConfigurationChange)
	{
		std::vector<std::thread> threads;
		std::atomic<size_t> success_count{0};
		for (size_t i = 0; i < 8; ++i)
		{
			threads.emplace_back([&]
			{
				manager.configurations.claims = { {"claim", std::to_string(i)} };
				std::string token = manager.sign_text("text", test_public_key, test_private_key);
				if (!token.empty())
					++success_count;
			});
		}
		for (auto& t : threads) t.join();
		EXPECT_EQ(success_count.load(), 8);
	}

	TEST_F(JsonWebTokenCryptographyManagerTest, Should_FailVerificationOnCorruptedToken)
	{
		std::string token = manager.sign_text("text", test_public_key, test_private_key);
		token[5] = 'X';
		std::string payload = manager.verify_text(token, test_public_key);
		EXPECT_TRUE(payload.empty());
	}
}

#endif
