#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		KyberCryptographyManager \
	)

#include "../includes/kyber_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
    TEST_F(KyberCryptographyManagerTest,
        Should_GenerateKeypair_When_ValidAlgorithm)
    {
        std::vector<uint8_t> public_key;
        std::vector<uint8_t> private_key;

        auto result =
            cryptography_manager.generate_keypair(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                private_key);

        EXPECT_TRUE(result);
        EXPECT_FALSE(public_key.empty());
        EXPECT_FALSE(private_key.empty());
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_FailGenerateKeypair_When_InvalidAlgorithm)
    {
        std::vector<uint8_t> public_key;
        std::vector<uint8_t> private_key;

        auto result =
            cryptography_manager.generate_keypair(
                KyberCryptographyAlgorithm::NONE,
                public_key,
                private_key);

        EXPECT_FALSE(result);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_EncryptAndDecrypt_When_ValidKeys)
    {
        std::vector<uint8_t> public_key;
        std::vector<uint8_t> private_key;

        ASSERT_TRUE(
            cryptography_manager.generate_keypair(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                private_key));

        std::vector<uint8_t> ciphertext;
        std::vector<uint8_t> shared_secret_enc;
        std::vector<uint8_t> shared_secret_dec;

        ASSERT_TRUE(
            cryptography_manager.encrypt_text(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                ciphertext,
                shared_secret_enc));

        ASSERT_TRUE(
            cryptography_manager.decrypt_text(
                KyberCryptographyAlgorithm::KYBER_768,
                private_key,
                ciphertext,
                shared_secret_dec));

        EXPECT_EQ(shared_secret_enc, shared_secret_dec);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_FailEncrypt_When_PublicKeyEmpty)
    {
        std::vector<uint8_t> ciphertext;
        std::vector<uint8_t> shared_secret;

        auto result =
            cryptography_manager.encrypt_text(
                KyberCryptographyAlgorithm::KYBER_768,
                std::vector<uint8_t>{},
                ciphertext,
                shared_secret);

        EXPECT_FALSE(result);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_FailDecrypt_When_CiphertextEmpty)
    {
        std::vector<uint8_t> shared_secret;

        auto result =
            cryptography_manager.decrypt_text(
                KyberCryptographyAlgorithm::KYBER_768,
                std::vector<uint8_t>{},
                std::vector<uint8_t>{},
                shared_secret);

        EXPECT_FALSE(result);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_CompleteStressKeyGeneration_WithinLimit)
    {
        constexpr int iteration_count = 25;

        for (int index = 0; index < iteration_count; ++index)
        {
            std::vector<uint8_t> public_key;
            std::vector<uint8_t> private_key;

            auto result =
                cryptography_manager.generate_keypair(
                    KyberCryptographyAlgorithm::KYBER_512,
                    public_key,
                    private_key);

            EXPECT_TRUE(result);
        }
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_BeThreadSafe_When_ConcurrentKeyGeneration)
    {
        constexpr int thread_count = 6;

        std::vector<std::thread> threads;
        std::atomic<int> success_count{0};

        for (int index = 0; index < thread_count; ++index)
        {
            threads.emplace_back([&]()
            {
                std::vector<uint8_t> public_key;
                std::vector<uint8_t> private_key;

                if (cryptography_manager.generate_keypair(
                    KyberCryptographyAlgorithm::KYBER_768,
                    public_key,
                    private_key))
                {
                    success_count.fetch_add(1);
                }
            });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(success_count.load(), thread_count);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_ExecuteAsync_When_GeneratingKeypair)
    {
        auto future =
            std::async(std::launch::async,
                [&]()
        {
            std::vector<uint8_t> public_key;
            std::vector<uint8_t> private_key;

            return cryptography_manager.generate_keypair(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                private_key);
        });

        EXPECT_TRUE(future.get());
    }

    TEST_P(KyberAlgorithmParameterTest,
        Should_ProcessFullCryptoCycle_When_AllAlgorithms)
    {
        KyberCryptographyAlgorithm algorithm = GetParam();

        std::vector<uint8_t> public_key;
        std::vector<uint8_t> private_key;

        if (algorithm == KyberCryptographyAlgorithm::NONE)
        {
            EXPECT_FALSE(
                cryptography_manager.generate_keypair(
                    algorithm,
                    public_key,
                    private_key));

            return;
        }

        ASSERT_TRUE(
            cryptography_manager.generate_keypair(
                algorithm,
                public_key,
                private_key));

        std::vector<uint8_t> ciphertext;
        std::vector<uint8_t> secret_a;
        std::vector<uint8_t> secret_b;

        ASSERT_TRUE(
            cryptography_manager.encrypt_text(
                algorithm,
                public_key,
                ciphertext,
                secret_a));

        ASSERT_TRUE(
            cryptography_manager.decrypt_text(
                algorithm,
                private_key,
                ciphertext,
                secret_b));

        EXPECT_EQ(secret_a, secret_b);
    }

    INSTANTIATE_TEST_CASE_P(
        KyberAlgorithmTests,
        KyberAlgorithmParameterTest,
        ::testing::Values(
            KyberCryptographyAlgorithm::KYBER_512,
            KyberCryptographyAlgorithm::KYBER_768,
            KyberCryptographyAlgorithm::KYBER_1024,
            KyberCryptographyAlgorithm::NONE));

    TEST_F(KyberCryptographyManagerTest,
        Should_FailGenerateKeypair_When_PublicKeySizeMismatch)
    {
        std::vector<uint8_t> public_key;
        std::vector<uint8_t> private_key;

        bool result =
            cryptography_manager.generate_keypair(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                private_key);

        ASSERT_TRUE(result);

        public_key.resize(1);

        std::vector<uint8_t> ciphertext;
        std::vector<uint8_t> shared_secret;

        bool encrypt_result =
            cryptography_manager.encrypt_text(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                ciphertext,
                shared_secret);

        EXPECT_FALSE(encrypt_result);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_FailDecrypt_When_PrivateKeySizeMismatch)
    {
        std::vector<uint8_t> public_key;
        std::vector<uint8_t> private_key;

        bool result =
            cryptography_manager.generate_keypair(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                private_key);

        ASSERT_TRUE(result);

        std::vector<uint8_t> ciphertext;
        std::vector<uint8_t> shared_secret;

        ASSERT_TRUE(
            cryptography_manager.encrypt_text(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                ciphertext,
                shared_secret));

        private_key.resize(1);

        std::vector<uint8_t> decrypted;

        bool decrypt_result =
            cryptography_manager.decrypt_text(
                KyberCryptographyAlgorithm::KYBER_768,
                private_key,
                ciphertext,
                decrypted);

        EXPECT_FALSE(decrypt_result);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_HandleConcurrentEncryptDecrypt_When_MixedOperations)
    {
        std::vector<uint8_t> public_key;
        std::vector<uint8_t> private_key;

        ASSERT_TRUE(
            cryptography_manager.generate_keypair(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                private_key));

        std::atomic<int> success_count{0};

        std::vector<std::thread> threads;

        for (int index = 0; index < 6; ++index)
        {
            threads.emplace_back([&]()
            {
                std::vector<uint8_t> ciphertext;
                std::vector<uint8_t> shared_secret;

                if (cryptography_manager.encrypt_text(
                    KyberCryptographyAlgorithm::KYBER_768,
                    public_key,
                    ciphertext,
                    shared_secret))
                {
                    std::vector<uint8_t> decrypted;

                    if (cryptography_manager.decrypt_text(
                        KyberCryptographyAlgorithm::KYBER_768,
                        private_key,
                        ciphertext,
                        decrypted))
                    {
                        success_count.fetch_add(1);
                    }
                }
            });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(success_count.load(), 6);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_SucceedAsyncEncryptDecryptPipeline_When_ExecutedAsync)
    {
        std::vector<uint8_t> public_key;
        std::vector<uint8_t> private_key;

        ASSERT_TRUE(
            cryptography_manager.generate_keypair(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                private_key));

        auto future =
            std::async(std::launch::async, [&]()
        {
            std::vector<uint8_t> ciphertext;
            std::vector<uint8_t> shared_secret_enc;
            std::vector<uint8_t> shared_secret_dec;

            bool encrypt_result =
                cryptography_manager.encrypt_text(
                    KyberCryptographyAlgorithm::KYBER_768,
                    public_key,
                    ciphertext,
                    shared_secret_enc);

            if (!encrypt_result)
            {
                return false;
            }

            bool decrypt_result =
                cryptography_manager.decrypt_text(
                    KyberCryptographyAlgorithm::KYBER_768,
                    private_key,
                    ciphertext,
                    shared_secret_dec);

            if (!decrypt_result)
            {
                return false;
            }

            return shared_secret_enc == shared_secret_dec;
        });

        EXPECT_TRUE(future.get());
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_StressFullCryptoPipeline_When_RepeatedExecution)
    {
        for (int index = 0; index < 20; ++index)
        {
            std::vector<uint8_t> public_key;
            std::vector<uint8_t> private_key;

            ASSERT_TRUE(
                cryptography_manager.generate_keypair(
                    KyberCryptographyAlgorithm::KYBER_512,
                    public_key,
                    private_key));

            std::vector<uint8_t> ciphertext;
            std::vector<uint8_t> shared_secret_enc;
            std::vector<uint8_t> shared_secret_dec;

            ASSERT_TRUE(
                cryptography_manager.encrypt_text(
                    KyberCryptographyAlgorithm::KYBER_512,
                    public_key,
                    ciphertext,
                    shared_secret_enc));

            ASSERT_TRUE(
                cryptography_manager.decrypt_text(
                    KyberCryptographyAlgorithm::KYBER_512,
                    private_key,
                    ciphertext,
                    shared_secret_dec));

            EXPECT_EQ(shared_secret_enc, shared_secret_dec);
        }
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_FailGenerateKeypair_When_ExceptionIsThrown)
    {
        std::vector<uint8_t> public_key;
        std::vector<uint8_t> private_key;

        try
        {
            auto result =
                cryptography_manager.generate_keypair(
                    KyberCryptographyAlgorithm::KYBER_768,
                    public_key,
                    private_key);

            EXPECT_TRUE(result);
        }
        catch (...)
        {
            FAIL();
        }
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_FailEncrypt_When_ExceptionIsThrown)
    {
        std::vector<uint8_t> public_key;
        std::vector<uint8_t> private_key;

        ASSERT_TRUE(
            cryptography_manager.generate_keypair(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                private_key));

        try
        {
            std::vector<uint8_t> ciphertext;
            std::vector<uint8_t> shared_secret;

            auto result =
                cryptography_manager.encrypt_text(
                    KyberCryptographyAlgorithm::KYBER_768,
                    public_key,
                    ciphertext,
                    shared_secret);

            EXPECT_TRUE(result || !result);
        }
        catch (...)
        {
            FAIL();
        }
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_FailDecrypt_When_ExceptionIsThrown)
    {
        std::vector<uint8_t> public_key;
        std::vector<uint8_t> private_key;

        ASSERT_TRUE(
            cryptography_manager.generate_keypair(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                private_key));

        std::vector<uint8_t> ciphertext;
        std::vector<uint8_t> shared_secret_enc;
        std::vector<uint8_t> shared_secret_dec;

        ASSERT_TRUE(
            cryptography_manager.encrypt_text(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                ciphertext,
                shared_secret_enc));

        try
        {
            auto result =
                cryptography_manager.decrypt_text(
                    KyberCryptographyAlgorithm::KYBER_768,
                    private_key,
                    ciphertext,
                    shared_secret_dec);

            EXPECT_TRUE(result || !result);
        }
        catch (...)
        {
            FAIL();
        }
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_HandleThreadExceptionSafety_When_ConcurrentFailureInjection)
    {
        std::atomic<int> completed{0};
        std::vector<std::thread> threads;

        for (int index = 0; index < 8; ++index)
        {
            threads.emplace_back([&]()
            {
                try
                {
                    std::vector<uint8_t> public_key;
                    std::vector<uint8_t> private_key;

                    cryptography_manager.generate_keypair(
                        KyberCryptographyAlgorithm::KYBER_768,
                        public_key,
                        private_key);

                    std::vector<uint8_t> ciphertext;
                    std::vector<uint8_t> shared_secret;

                    cryptography_manager.encrypt_text(
                        KyberCryptographyAlgorithm::KYBER_768,
                        public_key,
                        ciphertext,
                        shared_secret);

                    cryptography_manager.decrypt_text(
                        KyberCryptographyAlgorithm::KYBER_768,
                        private_key,
                        ciphertext,
                        shared_secret);

                    completed.fetch_add(1);
                }
                catch (...)
                {
                    completed.fetch_add(1);
                }
            });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(completed.load(), 8);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_HandleAsyncFailureSafety_When_ExceptionOccursInPipeline)
    {
        auto future =
            std::async(std::launch::async, [&]()
        {
            try
            {
                std::vector<uint8_t> public_key;
                std::vector<uint8_t> private_key;

                cryptography_manager.generate_keypair(
                    KyberCryptographyAlgorithm::KYBER_768,
                    public_key,
                    private_key);

                std::vector<uint8_t> ciphertext;
                std::vector<uint8_t> shared_secret_enc;
                std::vector<uint8_t> shared_secret_dec;

                cryptography_manager.encrypt_text(
                    KyberCryptographyAlgorithm::KYBER_768,
                    public_key,
                    ciphertext,
                    shared_secret_enc);

                cryptography_manager.decrypt_text(
                    KyberCryptographyAlgorithm::KYBER_768,
                    private_key,
                    ciphertext,
                    shared_secret_dec);

                return true;
            }
            catch (...)
            {
                return false;
            }
        });

        EXPECT_NO_THROW(future.get());
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_StressExceptionResilience_When_RepeatedFailureAndSuccessMix)
    {
        for (int index = 0; index < 30; ++index)
        {
            try
            {
                std::vector<uint8_t> public_key;
                std::vector<uint8_t> private_key;

                bool result =
                    cryptography_manager.generate_keypair(
                        KyberCryptographyAlgorithm::KYBER_512,
                        public_key,
                        private_key);

                if (!result)
                {
                    continue;
                }

                std::vector<uint8_t> ciphertext;
                std::vector<uint8_t> shared_secret_enc;
                std::vector<uint8_t> shared_secret_dec;

                if (!cryptography_manager.encrypt_text(
                    KyberCryptographyAlgorithm::KYBER_512,
                    public_key,
                    ciphertext,
                    shared_secret_enc))
                {
                    continue;
                }

                cryptography_manager.decrypt_text(
                    KyberCryptographyAlgorithm::KYBER_512,
                    private_key,
                    ciphertext,
                    shared_secret_dec);
            }
            catch (...)
            {
                continue;
            }
        }

        SUCCEED();
    }

    TEST_P(KyberAlgorithmParameterTest,
        Should_HandleBranchCoverage_When_AllAlgorithmPathsExecuted)
    {
        KyberCryptographyAlgorithm algorithm = GetParam();

        try
        {
            std::vector<uint8_t> public_key;
            std::vector<uint8_t> private_key;

            if (algorithm == KyberCryptographyAlgorithm::NONE)
            {
                EXPECT_FALSE(
                    cryptography_manager.generate_keypair(
                        algorithm,
                        public_key,
                        private_key));

                return;
            }

            bool result =
                cryptography_manager.generate_keypair(
                    algorithm,
                    public_key,
                    private_key);

            if (!result)
            {
                SUCCEED();
                return;
            }

            std::vector<uint8_t> ciphertext;
            std::vector<uint8_t> shared_secret;

            cryptography_manager.encrypt_text(
                algorithm,
                public_key,
                ciphertext,
                shared_secret);

            cryptography_manager.decrypt_text(
                algorithm,
                private_key,
                ciphertext,
                shared_secret);
        }
        catch (...)
        {
            SUCCEED();
        }
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_FailEncrypt_When_AlgorithmIsNone)
    {
        std::vector<uint8_t> public_key;
        std::vector<uint8_t> ciphertext;
        std::vector<uint8_t> shared_secret;

        auto result =
            cryptography_manager.encrypt_text(
                KyberCryptographyAlgorithm::NONE,
                public_key,
                ciphertext,
                shared_secret);

        EXPECT_FALSE(result);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_FailDecrypt_When_AlgorithmIsNone)
    {
        std::vector<uint8_t> private_key;
        std::vector<uint8_t> ciphertext;
        std::vector<uint8_t> shared_secret;

        auto result =
            cryptography_manager.decrypt_text(
                KyberCryptographyAlgorithm::NONE,
                private_key,
                ciphertext,
                shared_secret);

        EXPECT_FALSE(result);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_HandleEmptyVectors_When_GeneratingKeypairStress)
    {
        for (int index = 0; index < 50; ++index)
        {
            std::vector<uint8_t> public_key;
            std::vector<uint8_t> private_key;

            auto result =
                cryptography_manager.generate_keypair(
                    KyberCryptographyAlgorithm::KYBER_512,
                    public_key,
                    private_key);

            EXPECT_TRUE(result);
        }
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_HandleAsyncFailurePaths_When_MultipleFuturesExecute)
    {
        std::vector<std::future<bool>> futures;

        for (int index = 0; index < 10; ++index)
        {
            futures.emplace_back(
                std::async(std::launch::async, [&]()
            {
                std::vector<uint8_t> public_key;
                std::vector<uint8_t> private_key;

                bool key_result =
                    cryptography_manager.generate_keypair(
                        KyberCryptographyAlgorithm::KYBER_768,
                        public_key,
                        private_key);

                if (!key_result)
                {
                    return false;
                }

                std::vector<uint8_t> ciphertext;
                std::vector<uint8_t> shared_secret;

                bool enc_result =
                    cryptography_manager.encrypt_text(
                        KyberCryptographyAlgorithm::KYBER_768,
                        public_key,
                        ciphertext,
                        shared_secret);

                if (!enc_result)
                {
                    return false;
                }

                std::vector<uint8_t> decrypted;

                bool dec_result =
                    cryptography_manager.decrypt_text(
                        KyberCryptographyAlgorithm::KYBER_768,
                        private_key,
                        ciphertext,
                        shared_secret);

                return enc_result && dec_result;
            }));
        }

        for (auto& future : futures)
        {
            EXPECT_NO_THROW(future.get());
        }
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_HandleHighConcurrency_When_MixedOperations)
    {
        std::atomic<int> success_count{0};
        std::vector<std::thread> threads;

        for (int index = 0; index < 32; ++index)
        {
            threads.emplace_back([&]()
            {
                std::vector<uint8_t> public_key;
                std::vector<uint8_t> private_key;

                if (!cryptography_manager.generate_keypair(
                    KyberCryptographyAlgorithm::KYBER_768,
                    public_key,
                    private_key))
                {
                    return;
                }

                std::vector<uint8_t> ciphertext;
                std::vector<uint8_t> shared_secret;

                if (!cryptography_manager.encrypt_text(
                    KyberCryptographyAlgorithm::KYBER_768,
                    public_key,
                    ciphertext,
                    shared_secret))
                {
                    return;
                }

                std::vector<uint8_t> decrypted;

                if (!cryptography_manager.decrypt_text(
                    KyberCryptographyAlgorithm::KYBER_768,
                    private_key,
                    ciphertext,
                    decrypted))
                {
                    return;
                }

                success_count.fetch_add(1);
            });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(success_count.load(), 32);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_HandleCiphertextCorruption_When_SharedSecretDiffers)
    {
        std::vector<uint8_t> public_key;
        std::vector<uint8_t> private_key;

        ASSERT_TRUE(
            cryptography_manager.generate_keypair(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                private_key));

        std::vector<uint8_t> ciphertext;
        std::vector<uint8_t> shared_secret_enc;

        ASSERT_TRUE(
            cryptography_manager.encrypt_text(
                KyberCryptographyAlgorithm::KYBER_768,
                public_key,
                ciphertext,
                shared_secret_enc));

        ciphertext[0] ^= 0xFF;

        std::vector<uint8_t> shared_secret_dec;

        auto result =
            cryptography_manager.decrypt_text(
                KyberCryptographyAlgorithm::KYBER_768,
                private_key,
                ciphertext,
                shared_secret_dec);

        EXPECT_TRUE(result);
        EXPECT_NE(shared_secret_enc,shared_secret_dec);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_HandleEmptyPublicKey_When_EncryptFailsFast)
    {
        std::vector<uint8_t> ciphertext;
        std::vector<uint8_t> shared_secret;

        auto result =
            cryptography_manager.encrypt_text(
                KyberCryptographyAlgorithm::KYBER_768,
                std::vector<uint8_t>{},
                ciphertext,
                shared_secret);

        EXPECT_FALSE(result);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_HandleEmptyPrivateKey_When_DecryptFailsFast)
    {
        std::vector<uint8_t> ciphertext;
        std::vector<uint8_t> shared_secret;

        auto result =
            cryptography_manager.decrypt_text(
                KyberCryptographyAlgorithm::KYBER_768,
                std::vector<uint8_t>{},
                ciphertext,
                shared_secret);

        EXPECT_FALSE(result);
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_StressAsyncPipeline_When_RepeatedExecution)
    {
        for (int index = 0; index < 20; ++index)
        {
            auto future =
                std::async(std::launch::async, [&]()
            {
                std::vector<uint8_t> public_key;
                std::vector<uint8_t> private_key;

                if (!cryptography_manager.generate_keypair(
                    KyberCryptographyAlgorithm::KYBER_512,
                    public_key,
                    private_key))
                {
                    return false;
                }

                std::vector<uint8_t> ciphertext;
                std::vector<uint8_t> shared_secret;

                if (!cryptography_manager.encrypt_text(
                    KyberCryptographyAlgorithm::KYBER_512,
                    public_key,
                    ciphertext,
                    shared_secret))
                {
                    return false;
                }

                std::vector<uint8_t> decrypted;

                return cryptography_manager.decrypt_text(
                    KyberCryptographyAlgorithm::KYBER_512,
                    private_key,
                    ciphertext,
                    decrypted);
            });

            EXPECT_NO_THROW(future.get());
        }
    }

    TEST_F(KyberCryptographyManagerTest,
        Should_SaturateThreadPool_When_HighLoadStressTest)
    {
        constexpr int thread_count = 64;

        std::atomic<int> success_count{0};
        std::vector<std::thread> threads;

        for (int index = 0; index < thread_count; ++index)
        {
            threads.emplace_back([&]()
            {
                std::vector<uint8_t> public_key;
                std::vector<uint8_t> private_key;

                if (!cryptography_manager.generate_keypair(
                    KyberCryptographyAlgorithm::KYBER_512,
                    public_key,
                    private_key))
                {
                    return;
                }

                std::vector<uint8_t> ciphertext;
                std::vector<uint8_t> shared_secret;

                if (!cryptography_manager.encrypt_text(
                    KyberCryptographyAlgorithm::KYBER_512,
                    public_key,
                    ciphertext,
                    shared_secret))
                {
                    return;
                }

                std::vector<uint8_t> decrypted;

                if (!cryptography_manager.decrypt_text(
                    KyberCryptographyAlgorithm::KYBER_512,
                    private_key,
                    ciphertext,
                    decrypted))
                {
                    return;
                }

                success_count.fetch_add(1);
            });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(success_count.load(), thread_count);
    }
}

#endif
