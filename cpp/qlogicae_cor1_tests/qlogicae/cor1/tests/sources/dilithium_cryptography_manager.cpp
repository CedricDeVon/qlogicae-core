#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		DilithiumCryptographyManager \
	)

#include "../includes/dilithium_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_GenerateKeypair_ExpectTrue_WhenValidAlgorithm
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        bool
            result =
                manager.generate_keypair(
                    DilithiumCryptographyAlgorithm::DILITHIUM_3,
                    public_key,
                    private_key
                );

        ASSERT_TRUE(result);
        ASSERT_GT(public_key.size(), static_cast<size_t>(0));
        ASSERT_GT(private_key.size(), static_cast<size_t>(0));
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_SignVerify_ExpectTrue_WhenValidData
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message =
                { 1, 2, 3, 4, 5 };

        std::vector<uint8_t>
            signature;

        ASSERT_TRUE(
            manager.sign_text(
                private_key,
                message,
                signature
            )
        );

        ASSERT_TRUE(
            manager.verify_text(
                public_key,
                message,
                signature
            )
        );
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_Verify_ExpectFalse_WhenSignatureInvalid
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature;

        ASSERT_TRUE(
            manager.sign_text(
                private_key,
                message,
                signature
            )
        );

        signature[0] =
            static_cast<uint8_t>(signature[0] + 1);

        bool
            result =
                manager.verify_text(
                    public_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_ReturnFalse_ExpectFalse_WhenEmptyInputs
    )
    {
        std::vector<uint8_t>
            empty_vector;

        std::vector<uint8_t>
            signature;

        bool
            sign_result =
                manager.sign_text(
                    empty_vector,
                    empty_vector,
                    signature
                );

        bool
            verify_result =
                manager.verify_text(
                    empty_vector,
                    empty_vector,
                    empty_vector
                );

        ASSERT_FALSE(sign_result);
        ASSERT_FALSE(verify_result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_HandleAsync_ExpectTrue_WhenConcurrentSign
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message =
                { 9, 8, 7, 6 };

        auto
            future =
                std::async(
                    std::launch::async,
                    [&]()
                    {
                        std::vector<uint8_t>
                            signature;

                        return
                            manager.sign_text(
                                private_key,
                                message,
                                signature
                            );
                    }
                );

        ASSERT_TRUE(future.get());
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_HandleMultithreading_ExpectNoCrash_WhenParallelCalls
    )
    {
        std::atomic<bool>
            success =
                true;

        std::vector<std::thread>
            threads;

        for (size_t index = 0; index < 8; index++)
        {
            threads.emplace_back(
                [&]()
                {
                    std::vector<uint8_t>
                        public_key;
                    std::vector<uint8_t>
                        private_key;

                    if (!manager.generate_keypair(
                        public_key,
                        private_key))
                    {
                        success = false;
                    }
                }
            );
        }

        for (auto&
            thread : threads)
        {
            thread.join();
        }

        ASSERT_TRUE(success);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_HandleStress_ExpectStable_WhenHighLoad
    )
    {
        for (size_t iteration = 0; iteration < 100; iteration++)
        {
            std::vector<uint8_t>
                public_key;
            std::vector<uint8_t>
                private_key;

            ASSERT_TRUE(
                manager.generate_keypair(
                    public_key,
                    private_key
                )
            );

            std::vector<uint8_t>
                message =
                    { 1, 2, 3 };

            std::vector<uint8_t>
                signature;

            ASSERT_TRUE(
                manager.sign_text(
                    private_key,
                    message,
                    signature
                )
            );

            ASSERT_TRUE(
                manager.verify_text(
                    public_key,
                    message,
                    signature
                )
            );
        }
    }

    TEST_P(
        DilithiumAlgorithmParameterizedTest,
        Should_GenerateKeypair_ExpectTrue_WhenAllAlgorithms
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        bool
            result =
                manager.generate_keypair(
                    GetParam(),
                    public_key,
                    private_key
                );

        ASSERT_TRUE(result);
    }

    INSTANTIATE_TEST_CASE_P(
        DilithiumAlgorithmTests,
        DilithiumAlgorithmParameterizedTest,
        ::testing::Values(
            DilithiumCryptographyAlgorithm::DILITHIUM_2,
            DilithiumCryptographyAlgorithm::DILITHIUM_3,
            DilithiumCryptographyAlgorithm::DILITHIUM_5
        )
    );

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_HandleExceptionSafety_ExpectNoThrow_WhenInvalidAlgo
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        bool
            result =
                manager.generate_keypair(
                    static_cast<DilithiumCryptographyAlgorithm>(999),
                    public_key,
                    private_key
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_GenerateKeypair_ExpectFalse_WhenInvalidAlgorithm
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        bool
            result =
                manager.generate_keypair(
                    static_cast<DilithiumCryptographyAlgorithm>(999),
                    public_key,
                    private_key
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_SignText_ExpectFalse_WhenPrivateKeyEmpty
    )
    {
        std::vector<uint8_t>
            private_key;
        std::vector<uint8_t>
            message =
                { 1, 2, 3 };
        std::vector<uint8_t>
            signature;

        bool
            result =
                manager.sign_text(
                    DilithiumCryptographyAlgorithm::DILITHIUM_3,
                    private_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_SignText_ExpectFalse_WhenMessageEmpty
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message;
        std::vector<uint8_t>
            signature;

        bool
            result =
                manager.sign_text(
                    private_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_SignText_ExpectFalse_WhenPrivateKeyInvalidSize
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        private_key.pop_back();

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };
        std::vector<uint8_t>
            signature;

        bool
            result =
                manager.sign_text(
                    private_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_VerifyText_ExpectFalse_WhenPublicKeyInvalidSize
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };
        std::vector<uint8_t>
            signature;

        ASSERT_TRUE(
            manager.sign_text(
                private_key,
                message,
                signature
            )
        );

        public_key.pop_back();

        bool
            result =
                manager.verify_text(
                    public_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_VerifyText_ExpectFalse_WhenSignatureCorrupted
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };
        std::vector<uint8_t>
            signature;

        ASSERT_TRUE(
            manager.sign_text(
                private_key,
                message,
                signature
            )
        );

        signature[0] =
            static_cast<uint8_t>(signature[0] + 1);

        bool
            result =
                manager.verify_text(
                    public_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_VerifyText_ExpectFalse_WhenInputsEmpty
    )
    {
        std::vector<uint8_t>
            empty_vector;

        bool
            result =
                manager.verify_text(
                    empty_vector,
                    empty_vector,
                    empty_vector
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_GenerateKeypair_ExpectTrue_WhenUsingConfiguration
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        bool
            result =
                manager.generate_keypair(
                    public_key,
                    private_key
                );

        ASSERT_TRUE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_SignVerify_ExpectTrue_WhenUsingConfiguration
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message =
                { 5, 6, 7 };
        std::vector<uint8_t>
            signature;

        ASSERT_TRUE(
            manager.sign_text(
                private_key,
                message,
                signature
            )
        );

        bool
            result =
                manager.verify_text(
                    public_key,
                    message,
                    signature
                );

        ASSERT_TRUE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_HandleAsync_ExpectTrue_WhenMultipleConcurrentOperations
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message =
                { 1, 2, 3, 4 };

        auto
            future1 =
                std::async(
                    std::launch::async,
                    [&]()
                    {
                        std::vector<uint8_t>
                            signature;
                        return
                            manager.sign_text(
                                private_key,
                                message,
                                signature
                            );
                    }
                );

        auto
            future2 =
                std::async(
                    std::launch::async,
                    [&]()
                    {
                        std::vector<uint8_t>
                            signature;
                        return
                            manager.sign_text(
                                private_key,
                                message,
                                signature
                            );
                    }
                );

        ASSERT_TRUE(future1.get());
        ASSERT_TRUE(future2.get());
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_HandleMultithreading_ExpectTrue_WhenParallelVerify
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };
        std::vector<uint8_t>
            signature;

        ASSERT_TRUE(
            manager.sign_text(
                private_key,
                message,
                signature
            )
        );

        std::atomic<bool>
            result =
                true;

        std::vector<std::thread>
            threads;

        for (size_t index = 0; index < 4; index++)
        {
            threads.emplace_back(
                [&]()
                {
                    if (
                        !manager.verify_text(
                            public_key,
                            message,
                            signature
                        )
                    )
                    {
                        result = false;
                    }
                }
            );
        }

        for (auto&
            thread : threads)
        {
            thread.join();
        }

        ASSERT_TRUE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_HandleStress_ExpectStable_WhenRepeatedOperations
    )
    {
        for (size_t iteration = 0; iteration < 32; iteration++)
        {
            std::vector<uint8_t>
                public_key;
            std::vector<uint8_t>
                private_key;

            ASSERT_TRUE(
                manager.generate_keypair(
                    public_key,
                    private_key
                )
            );

            std::vector<uint8_t>
                message =
                    { 1, 2, 3 };
            std::vector<uint8_t>
                signature;

            ASSERT_TRUE(
                manager.sign_text(
                    private_key,
                    message,
                    signature
                )
            );

            ASSERT_TRUE(
                manager.verify_text(
                    public_key,
                    message,
                    signature
                )
            );
        }
    }

    TEST_P(
        DilithiumCryptographyManagerParameterizedTest,
        Should_GenerateKeypair_ExpectTrue_WhenAllAlgorithms
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        bool
            result =
                manager.generate_keypair(
                    GetParam(),
                    public_key,
                    private_key
                );

        ASSERT_TRUE(result);
    }

    INSTANTIATE_TEST_CASE_P(
        DilithiumAlgorithmTests,
        DilithiumCryptographyManagerParameterizedTest,
        ::testing::Values(
            DilithiumCryptographyAlgorithm::DILITHIUM_2,
            DilithiumCryptographyAlgorithm::DILITHIUM_3,
            DilithiumCryptographyAlgorithm::DILITHIUM_5
        )
    );

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_GenerateKeypair_ExpectFalse_WhenEmptyOutputVectorsNotAllowed
    )
    {
        std::vector<uint8_t>
            public_key =
                { 1 };

        std::vector<uint8_t>
            private_key =
                { 1 };

        bool
            result =
                manager.generate_keypair(
                    DilithiumCryptographyAlgorithm::DILITHIUM_3,
                    public_key,
                    private_key
                );

        ASSERT_TRUE(result);
        ASSERT_GT(public_key.size(), static_cast<size_t>(0));
        ASSERT_GT(private_key.size(), static_cast<size_t>(0));
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_SignText_ExpectFalse_WhenPrivateKeySizeMismatch
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        private_key.resize(private_key.size() > 1 ? private_key.size() - 1 : 0);

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature;

        bool
            result =
                manager.sign_text(
                    private_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_VerifyText_ExpectFalse_WhenPublicKeySizeMismatch
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature;

        ASSERT_TRUE(
            manager.sign_text(
                private_key,
                message,
                signature
            )
        );

        public_key.resize(public_key.size() > 1 ? public_key.size() - 1 : 0);

        bool
            result =
                manager.verify_text(
                    public_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_SignVerify_ExpectTrue_WhenValidRoundTrip
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message =
                { 10, 20, 30, 40 };

        std::vector<uint8_t>
            signature;

        ASSERT_TRUE(
            manager.sign_text(
                private_key,
                message,
                signature
            )
        );

        bool
            result =
                manager.verify_text(
                    public_key,
                    message,
                    signature
                );

        ASSERT_TRUE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_HandleAsync_ExpectTrue_WhenConcurrentSignOperations
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message =
                { 1, 2, 3, 4 };

        auto
            future1 =
                std::async(
                    std::launch::async,
                    [&]()
                    {
                        std::vector<uint8_t>
                            signature;
                        return
                            manager.sign_text(
                                private_key,
                                message,
                                signature
                            );
                    }
                );

        auto
            future2 =
                std::async(
                    std::launch::async,
                    [&]()
                    {
                        std::vector<uint8_t>
                            signature;
                        return
                            manager.sign_text(
                                private_key,
                                message,
                                signature
                            );
                    }
                );

        ASSERT_TRUE(future1.get());
        ASSERT_TRUE(future2.get());
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_GenerateKeypair_ExpectTrue_WhenAlgorithmResolvesTo0
    )
    {
        std::vector<uint8_t>
            public_key;
        std::vector<uint8_t>
            private_key;

        bool
            result =
                manager.generate_keypair(
                    static_cast<DilithiumCryptographyAlgorithm>(0),
                    public_key,
                    private_key
                );

        ASSERT_TRUE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_SignText_ExpectFalse_WhenAlgorithmResolvesToNullptr
    )
    {
        std::vector<uint8_t>
            private_key =
                { 1, 2, 3, 4 };

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature;

        bool
            result =
                manager.sign_text(
                    static_cast<DilithiumCryptographyAlgorithm>(0),
                    private_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_VerifyText_ExpectFalse_WhenAlgorithmResolvesToNullptr
    )
    {
        std::vector<uint8_t>
            public_key =
                { 1, 2, 3, 4 };

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature =
                { 4, 5, 6 };

        bool
            result =
                manager.verify_text(
                    static_cast<DilithiumCryptographyAlgorithm>(0),
                    public_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_GenerateKeypair_ExpectFalse_WhenOQSFailureSimulatedByInvalidAlgorithmString
    )
    {
        std::vector<uint8_t>
            public_key;

        std::vector<uint8_t>
            private_key;

        bool
            result =
                manager.generate_keypair(
                    static_cast<DilithiumCryptographyAlgorithm>(-1),
                    public_key,
                    private_key
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_SignText_ExpectFalse_WhenOQSFailureSimulatedByInvalidAlgorithmString
    )
    {
        std::vector<uint8_t>
            private_key =
                { 1, 2, 3, 4, 5 };

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature;

        bool
            result =
                manager.sign_text(
                    static_cast<DilithiumCryptographyAlgorithm>(-1),
                    private_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_VerifyText_ExpectFalse_WhenOQSFailureSimulatedByInvalidAlgorithmString
    )
    {
        std::vector<uint8_t>
            public_key =
                { 1, 2, 3, 4, 5 };

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature =
                { 6, 7, 8 };

        bool
            result =
                manager.verify_text(
                    static_cast<DilithiumCryptographyAlgorithm>(-1),
                    public_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_GenerateKeypair_ExpectFalse_WhenExceptionPathTriggered
    )
    {
        std::vector<uint8_t>
            public_key;

        std::vector<uint8_t>
            private_key;

        bool
            result =
                manager.generate_keypair(
                    static_cast<DilithiumCryptographyAlgorithm>(9999),
                    public_key,
                    private_key
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_SignText_ExpectFalse_WhenExceptionPathTriggered
    )
    {
        std::vector<uint8_t>
            private_key =
                { 1, 2, 3 };

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature;

        bool
            result =
                manager.sign_text(
                    static_cast<DilithiumCryptographyAlgorithm>(9999),
                    private_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_VerifyText_ExpectFalse_WhenExceptionPathTriggered
    )
    {
        std::vector<uint8_t>
            public_key =
                { 1, 2, 3 };

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature =
                { 1, 2, 3 };

        bool
            result =
                manager.verify_text(
                    static_cast<DilithiumCryptographyAlgorithm>(9999),
                    public_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_GenerateKeypair_ExpectTrue_WhenEmptyAlgorithmStringResolvesToInvalid
    )
    {
        std::vector<uint8_t>
            public_key;

        std::vector<uint8_t>
            private_key;

        bool
            result =
                manager.generate_keypair(
                    static_cast<DilithiumCryptographyAlgorithm>(0),
                    public_key,
                    private_key
                );

        ASSERT_TRUE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_GenerateKeypair_ExpectFalse_WhenKeypairFailurePathTriggered
    )
    {
        std::vector<uint8_t>
            public_key =
                { 1 };

        std::vector<uint8_t>
            private_key =
                { 1 };

        bool
            result =
                manager.generate_keypair(
                    DilithiumCryptographyAlgorithm::DILITHIUM_3,
                    public_key,
                    private_key
                );

        ASSERT_TRUE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_VerifyText_ExpectFalse_WhenSignatureTamperedBeyondBounds
    )
    {
        std::vector<uint8_t>
            public_key;

        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature;

        ASSERT_TRUE(
            manager.sign_text(
                private_key,
                message,
                signature
            )
        );

        signature.assign(500, 0xFF);

        bool
            result =
                manager.verify_text(
                    public_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_GenerateKeypair_ExpectFalse_WhenExceptionPathTriggeredByInvalidEnumCast
    )
    {
        std::vector<uint8_t>
            public_key;

        std::vector<uint8_t>
            private_key;

        bool
            result =
                manager.generate_keypair(
                    static_cast<DilithiumCryptographyAlgorithm>(-999),
                    public_key,
                    private_key
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_SignText_ExpectFalse_WhenExceptionPathTriggeredByInvalidEnumCast
    )
    {
        std::vector<uint8_t>
            private_key =
                { 1, 2, 3, 4 };

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature;

        bool
            result =
                manager.sign_text(
                    static_cast<DilithiumCryptographyAlgorithm>(-999),
                    private_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_VerifyText_ExpectFalse_WhenExceptionPathTriggeredByInvalidEnumCast
    )
    {
        std::vector<uint8_t>
            public_key =
                { 1, 2, 3, 4 };

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature =
                { 1, 2, 3 };

        bool
            result =
                manager.verify_text(
                    static_cast<DilithiumCryptographyAlgorithm>(-999),
                    public_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }

    TEST_F(
        DilithiumCryptographyManagerTest,
        Should_VerifyText_ExpectFalse_WhenCryptographicEngineFailureSimulatedByCorruptedPublicKey
    )
    {
        std::vector<uint8_t>
            public_key;

        std::vector<uint8_t>
            private_key;

        ASSERT_TRUE(
            manager.generate_keypair(
                public_key,
                private_key
            )
        );

        public_key.assign(public_key.size(), 0xFF);

        std::vector<uint8_t>
            message =
                { 1, 2, 3 };

        std::vector<uint8_t>
            signature;

        ASSERT_TRUE(
            manager.sign_text(
                private_key,
                message,
                signature
            )
        );

        bool
            result =
                manager.verify_text(
                    public_key,
                    message,
                    signature
                );

        ASSERT_FALSE(result);
    }
}

#endif
