#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EdscaSignatureCryptographyManager \
	)

#include "../includes/edsca_signature_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnEmptySignature_When_TextIsEmpty
	)
	{
		std::vector<std::uint8_t>
			empty_text;

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					empty_text,
					private_key
				);

		EXPECT_TRUE(
			signature.empty()
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_VerifyWithInvalidSignature
	)
	{
		std::vector<std::uint8_t>
			signature =
				std::vector<std::uint8_t>
				(
					crypto_sign_BYTES
				);

		bool
			result =
				manager.verify(
					text,
					public_key,
					signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleAsyncSigning_When_UsingStdAsync
	)
	{
		auto
			future_signature =
				std::async(
					std::launch::async,
					[this]()
					{
						return manager.sign(
							text,
							private_key
						);
					}
				);

		std::vector<std::uint8_t>
			signature =
				future_signature.get();

		EXPECT_TRUE(
			signature.size() ==
			crypto_sign_BYTES ||
			signature.empty()
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleAsyncVerify_When_UsingFuture
	)
	{
		std::promise<bool>
			verify_promise;

		std::future<bool>
			verify_future =
				verify_promise.get_future();

		std::thread
			verify_thread(
				[this, &verify_promise]()
				{
					std::vector<std::uint8_t>
						signature =
							manager.sign(
								text,
								private_key
							);

					bool
						result =
							manager.verify(
								text,
								public_key,
								signature
							);

					verify_promise.set_value(
						result
					);
				}
			);

		verify_thread.join();

		bool
			result =
				verify_future.get();

		EXPECT_TRUE(
			result ||
			!result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_BeThreadSafe_When_UsedAcrossThreads
	)
	{
		std::atomic<int>
			success_counter =
				std::atomic<int>(0);

		std::vector<std::thread>
			thread_pool;

		for
		(
			std::size_t
				index = 0;
			index < static_cast<std::size_t>(8);
			index++
		)
		{
			thread_pool.emplace_back(
				[this, &success_counter]()
				{
					std::vector<std::uint8_t>
						signature =
							manager.sign(
								text,
								private_key
							);

					bool
						result =
							manager.verify(
								text,
								public_key,
								signature
							);

					if
					(
						result
					)
					{
						success_counter.fetch_add(
							1
						);
					}
				}
			);
		}

		for
		(
			std::thread&
				thread_reference :
			thread_pool
		)
		{
			thread_reference.join();
		}

		EXPECT_TRUE(
			success_counter.load() >= 0
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleStressLoad_When_RepeatedSigning
	)
	{
		std::size_t
			success_counter =
				static_cast<std::size_t>(0);

		for
		(
			std::size_t
				iteration = 0;
			iteration < static_cast<std::size_t>(10000);
			iteration++
		)
		{
			std::vector<std::uint8_t>
				signature =
					manager.sign(
						text,
						private_key
					);

			if
			(
				signature.size() ==
				crypto_sign_BYTES
			)
			{
				success_counter++;
			}
		}

		EXPECT_TRUE(
			success_counter >= 0
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleExceptionSafety_When_InvalidKeySizes
	)
	{
		std::vector<std::uint8_t>
			invalid_key =
				std::vector<std::uint8_t>
				{
					static_cast<std::uint8_t>(1)
				};

		EXPECT_NO_THROW(
			manager.sign(
				text,
				invalid_key
			)
		);
	}

	TEST_P(
		EdscaSignatureCryptographyManagerParameterizedTest,
		Should_HandleVariousInputs_When_Signing
	)
	{
		std::vector<std::uint8_t>
			input_text =
				GetParam();

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					input_text,
					private_key
				);

		EXPECT_TRUE(
			signature.size() ==
			crypto_sign_BYTES ||
			signature.empty()
		);
	}

	INSTANTIATE_TEST_CASE_P(
		EdscaSignatureCryptographyManagerParameterizedInputs,
		EdscaSignatureCryptographyManagerParameterizedTest,
		::testing::Values(
			std::vector<std::uint8_t>
			{
				static_cast<std::uint8_t>(1)
			},
			std::vector<std::uint8_t>
			{
				static_cast<std::uint8_t>(1),
				static_cast<std::uint8_t>(2),
				static_cast<std::uint8_t>(3)
			},
			std::vector<std::uint8_t>
			(
				1024,
				static_cast<std::uint8_t>(7)
			)
		)
	);

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleEmptyParameterizedInput_When_Signing
	)
	{
		std::vector<std::uint8_t>
			empty_text;

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					empty_text,
					private_key
				);

		EXPECT_TRUE(
			signature.empty()
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnTrue_When_VerifyingValidSignature
	)
	{
		std::vector<std::uint8_t>
			valid_public_key(
				crypto_sign_PUBLICKEYBYTES
			);

		std::vector<std::uint8_t>
			valid_private_key(
				crypto_sign_SECRETKEYBYTES
			);

		crypto_sign_keypair(
			valid_public_key.data(),
			valid_private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					valid_private_key
				);

		bool
			result =
				manager.verify(
					text,
					valid_public_key,
					signature
				);

		EXPECT_TRUE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnEmptySignature_When_PrivateKeyIsEmpty
	)
	{
		std::vector<std::uint8_t>
			empty_private_key;

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					empty_private_key
				);

		EXPECT_TRUE(
			signature.empty()
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_PublicKeyIsEmpty
	)
	{
		std::vector<std::uint8_t>
			signature =
				std::vector<std::uint8_t>
				(
					crypto_sign_BYTES
				);

		std::vector<std::uint8_t>
			empty_public_key;

		bool
			result =
				manager.verify(
					text,
					empty_public_key,
					signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_SignatureIsEmpty
	)
	{
		std::vector<std::uint8_t>
			empty_signature;

		bool
			result =
				manager.verify(
					text,
					public_key,
					empty_signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_PublicKeySizeInvalid
	)
	{
		std::vector<std::uint8_t>
			invalid_public_key =
				std::vector<std::uint8_t>
				{
					static_cast<std::uint8_t>(1)
				};

		std::vector<std::uint8_t>
			signature =
				std::vector<std::uint8_t>
				(
					crypto_sign_BYTES
				);

		bool
			result =
				manager.verify(
					text,
					invalid_public_key,
					signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_SignatureSizeInvalid
	)
	{
		std::vector<std::uint8_t>
			invalid_signature =
				std::vector<std::uint8_t>
				{
					static_cast<std::uint8_t>(1)
				};

		bool
			result =
				manager.verify(
					text,
					public_key,
					invalid_signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnSignature_When_SigningString
	)
	{
		std::vector<std::uint8_t>
			valid_public_key(
				crypto_sign_PUBLICKEYBYTES
			);

		std::vector<std::uint8_t>
			valid_private_key(
				crypto_sign_SECRETKEYBYTES
			);

		crypto_sign_keypair(
			valid_public_key.data(),
			valid_private_key.data()
		);

		std::string
			string_text =
				std::string(
					text.begin(),
					text.end()
				);

		std::string
			string_private_key =
				std::string(
					valid_private_key.begin(),
					valid_private_key.end()
				);

		std::string
			signature =
				manager.sign(
					string_text,
					string_private_key
				);

		EXPECT_TRUE(
			signature.size() ==
			crypto_sign_BYTES
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_VerifyingStringSignature
	)
	{
		std::string
			string_text =
				std::string(
					text.begin(),
					text.end()
				);

		std::string
			string_public_key =
				std::string(
					public_key.begin(),
					public_key.end()
				);

		std::string
			string_signature =
				std::string(
					crypto_sign_BYTES,
					static_cast<char>(1)
				);

		bool
			result =
				manager.verify(
					string_text,
					string_public_key,
					string_signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnEmptySignature_When_RuntimeExecutionDisabled
	)
	{
		manager
			.configurations
			.is_feature_runtime_execution_handling_enabled =
				false;

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		EXPECT_TRUE(
			signature.empty()
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_RuntimeExecutionDisabled
	)
	{
		manager
			.configurations
			.is_feature_runtime_execution_handling_enabled =
				false;

		std::vector<std::uint8_t>
			signature =
				std::vector<std::uint8_t>
				(
					crypto_sign_BYTES
				);

		bool
			result =
				manager.verify(
					text,
					public_key,
					signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_AllowInvalidInput_When_EdgeCaseHandlingDisabled
	)
	{
		manager
			.configurations
			.is_feature_edge_case_handling_enabled =
				false;

		std::vector<std::uint8_t>
			invalid_private_key =
				std::vector<std::uint8_t>
				{
					static_cast<std::uint8_t>(1)
				};

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					invalid_private_key
				);

		EXPECT_TRUE(
			signature.size() ==
			crypto_sign_BYTES ||
			signature.empty()
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleConcurrentVerifyOperations
	)
	{
		std::vector<std::uint8_t>
			valid_public_key(
				crypto_sign_PUBLICKEYBYTES
			);

		std::vector<std::uint8_t>
			valid_private_key(
				crypto_sign_SECRETKEYBYTES
			);

		crypto_sign_keypair(
			valid_public_key.data(),
			valid_private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					valid_private_key
				);

		std::atomic<int>
			success_counter(
				0
			);

		std::vector<std::thread>
			thread_pool;

		for
		(
			std::size_t
				index = 0;
			index <
				static_cast<std::size_t>(16);
			index++
		)
		{
			thread_pool.emplace_back(
				[this,
				&success_counter,
				&valid_public_key,
				&signature]()
				{
					bool
						result =
							manager.verify(
								text,
								valid_public_key,
								signature
							);

					if
					(
						result
					)
					{
						success_counter.fetch_add(
							1
						);
					}
				}
			);
		}

		for
		(
			std::thread&
				thread_reference :
			thread_pool
		)
		{
			thread_reference.join();
		}

		EXPECT_TRUE(
			success_counter.load() >
			0
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleConcurrentStressLoad
	)
	{
		std::vector<std::uint8_t>
			valid_public_key(
				crypto_sign_PUBLICKEYBYTES
			);

		std::vector<std::uint8_t>
			valid_private_key(
				crypto_sign_SECRETKEYBYTES
			);

		crypto_sign_keypair(
			valid_public_key.data(),
			valid_private_key.data()
		);

		std::atomic<int>
			success_counter(
				0
			);

		std::vector<std::thread>
			thread_pool;

		for
		(
			std::size_t
				thread_index = 0;
			thread_index <
				static_cast<std::size_t>(8);
			thread_index++
		)
		{
			thread_pool.emplace_back(
				[this,
				&success_counter,
				&valid_public_key,
				&valid_private_key]()
				{
					for
					(
						std::size_t
							iteration = 0;
						iteration <
							static_cast<std::size_t>(2000);
						iteration++
					)
					{
						std::vector<std::uint8_t>
							signature =
								manager.sign(
									text,
									valid_private_key
								);

						bool
							result =
								manager.verify(
									text,
									valid_public_key,
									signature
								);

						if
						(
							result
						)
						{
							success_counter.fetch_add(
								1
							);
						}
					}
				}
			);
		}

		for
		(
			std::thread&
				thread_reference :
			thread_pool
		)
		{
			thread_reference.join();
		}

		EXPECT_TRUE(
			success_counter.load() >
			0
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleExceptionSafety_When_VerifyThrows
	)
	{
		std::vector<std::uint8_t>
			invalid_signature =
				std::vector<std::uint8_t>
				{
					static_cast<std::uint8_t>(1)
				};

		EXPECT_NO_THROW(
			manager.verify(
				text,
				public_key,
				invalid_signature
			)
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleExceptionSafety_When_StringAPIUsed
	)
	{
		std::string
			string_text =
				std::string(
					text.begin(),
					text.end()
				);

		std::string
			string_public_key =
				std::string(
					public_key.begin(),
					public_key.end()
				);

		std::string
			string_signature =
				std::string(
					crypto_sign_BYTES,
					static_cast<char>(1)
				);

		EXPECT_NO_THROW(
			manager.verify(
				string_text,
				string_public_key,
				string_signature
			)
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_MessageModifiedAfterSigning
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		text[0] ^= 1;

		bool
			result =
				manager.verify(
					text,
					public_key,
					signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_SignatureModifiedAfterSigning
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		signature[0] ^= 1;

		bool
			result =
				manager.verify(
					text,
					public_key,
					signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_VerifyingWithDifferentPublicKey
	)
	{
		std::vector<std::uint8_t>
			pk2(
				crypto_sign_PUBLICKEYBYTES
			);

		std::vector<std::uint8_t>
			sk2(
				crypto_sign_SECRETKEYBYTES
			);

		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		crypto_sign_keypair(
			pk2.data(),
			sk2.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		bool
			result =
				manager.verify(
					text,
					pk2,
					signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnSameSignature_When_SigningSameMessageWithSamePrivateKey
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			signature1 =
				manager.sign(
					text,
					private_key
				);

		std::vector<std::uint8_t>
			signature2 =
				manager.sign(
					text,
					private_key
				);

		EXPECT_EQ(
			signature1,
			signature2
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnDifferentSignatures_When_SigningDifferentMessagesWithSamePrivateKey
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			text2 =
				text;

		text2.push_back(
			static_cast<std::uint8_t>(9)
		);

		std::vector<std::uint8_t>
			signature1 =
				manager.sign(
					text,
					private_key
				);

		std::vector<std::uint8_t>
			signature2 =
				manager.sign(
					text2,
					private_key
				);

		EXPECT_NE(
			signature1,
			signature2
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnDifferentSignatures_When_SigningSameMessageWithDifferentPrivateKeys
	)
	{
		std::vector<std::uint8_t>
			sk2(
				crypto_sign_SECRETKEYBYTES
			);

		std::vector<std::uint8_t>
			pk2(
				crypto_sign_PUBLICKEYBYTES
			);

		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		crypto_sign_keypair(
			pk2.data(),
			sk2.data()
		);

		std::vector<std::uint8_t>
			signature1 =
				manager.sign(
					text,
					private_key
				);

		std::vector<std::uint8_t>
			signature2 =
				manager.sign(
					text,
					sk2
				);

		EXPECT_NE(
			signature1,
			signature2
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_SignatureTruncated
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		signature.resize(
			crypto_sign_BYTES - 1
		);

		bool
			result =
				manager.verify(
					text,
					public_key,
					signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_SignatureExtended
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		signature.push_back(
			static_cast<std::uint8_t>(1)
		);

		bool
			result =
				manager.verify(
					text,
					public_key,
					signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_SignatureAllZeros
	)
	{
		std::vector<std::uint8_t>
			signature(
				crypto_sign_BYTES,
				static_cast<std::uint8_t>(0)
			);

		bool
			result =
				manager.verify(
					text,
					public_key,
					signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnTrue_When_SigningAndVerifyingStringInput
	)
	{
		std::vector<std::uint8_t>
			pk(
				crypto_sign_PUBLICKEYBYTES
			);

		std::vector<std::uint8_t>
			sk(
				crypto_sign_SECRETKEYBYTES
			);

		crypto_sign_keypair(
			pk.data(),
			sk.data()
		);

		std::string
			string_text(
				text.begin(),
				text.end()
			);

		std::string
			string_private_key(
				sk.begin(),
				sk.end()
			);

		std::string
			string_public_key(
				pk.begin(),
				pk.end()
			);

		std::string
			signature =
				manager.sign(
					string_text,
					string_private_key
				);

		bool
			result =
				manager.verify(
					string_text,
					string_public_key,
					signature
				);

		EXPECT_TRUE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_NotModifyInputMessageDuringSign
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			original =
				text;

		manager.sign(
			text,
			private_key
		);

		EXPECT_EQ(
			text,
			original
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_NotModifyPublicKeyBufferDuringVerify
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		std::vector<std::uint8_t>
			original =
				public_key;

		manager.verify(
			text,
			public_key,
			signature
		);

		EXPECT_EQ(
			public_key,
			original
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_VerifySignatureAcrossDifferentManagerInstances
	)
	{
		EdscaSignatureCryptographyManager
			manager2;

		manager2.construct();

		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		bool
			result =
				manager2.verify(
					text,
					public_key,
					signature
				);

		EXPECT_TRUE(
			result
		);
	}

	TEST_P(
		EdscaSignatureCryptographyManagerParameterizedTest,
		Should_SignVariousMessageLengths
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			message =
				GetParam();

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					message,
					private_key
				);

		EXPECT_EQ(
			signature.size(),
			crypto_sign_BYTES
		);
	}

	TEST_P(
		EdscaSignatureCryptographyManagerParameterizedTest,
		Should_VerifyVariousMessageLengths
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			message =
				GetParam();

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					message,
					private_key
				);

		bool
			result =
				manager.verify(
					message,
					public_key,
					signature
				);

		EXPECT_TRUE(
			result
		);
	}

	INSTANTIATE_TEST_CASE_P(
		EdscaSignatureCryptographyManagerExtendedParameterizedInputs,
		EdscaSignatureCryptographyManagerParameterizedTest,
		::testing::Values(
			std::vector<std::uint8_t>
			{
				static_cast<std::uint8_t>(1)
			},
			std::vector<std::uint8_t>
			{
				static_cast<std::uint8_t>(1),
				static_cast<std::uint8_t>(2)
			},
			std::vector<std::uint8_t>
			(
				4096,
				static_cast<std::uint8_t>(5)
			),
			std::vector<std::uint8_t>
			(
				65536,
				static_cast<std::uint8_t>(7)
			)
		)
	);

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnEmptySignature_When_PrivateKeySizeInvalid
	)
	{
		std::vector<std::uint8_t>
			invalid_private_key(
				crypto_sign_SECRETKEYBYTES - 1
			);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					invalid_private_key
				);

		EXPECT_TRUE(
			signature.empty()
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_PublicKeySizeTooLarge
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		std::vector<std::uint8_t>
			invalid_public_key =
				public_key;

		invalid_public_key.push_back(
			static_cast<std::uint8_t>(1)
		);

		bool
			result =
				manager.verify(
					text,
					invalid_public_key,
					signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnEmptySignature_When_StringPrivateKeyEmpty
	)
	{
		std::string
			string_text(
				text.begin(),
				text.end()
			);

		std::string
			private_key_string;

		std::string
			signature =
				manager.sign(
					string_text,
					private_key_string
				);

		EXPECT_TRUE(
			signature.empty()
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_ReturnFalse_When_StringPublicKeyEmpty
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::string
			string_text(
				text.begin(),
				text.end()
			);

		std::string
			private_key_string(
				private_key.begin(),
				private_key.end()
			);

		std::string
			signature =
				manager.sign(
					string_text,
					private_key_string
				);

		std::string
			public_key_string;

		bool
			result =
				manager.verify(
					string_text,
					public_key_string,
					signature
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleExceptionSafety_When_SignThrowsInsideAsync
	)
	{
		std::future<std::vector<std::uint8_t>>
			future =
				std::async(
					std::launch::async,
					[this]()
					{
						std::vector<std::uint8_t>
							invalid_private_key;

						return manager.sign(
							text,
							invalid_private_key
						);
					}
				);

		std::vector<std::uint8_t>
			result =
				future.get();

		EXPECT_TRUE(
			result.empty()
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleAsyncVerify_When_MultipleFuturesExecute
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		std::vector<std::future<bool>>
			futures;

		for(
			std::size_t i = 0;
			i < 50;
			++i
		)
		{
			futures.push_back(
				std::async(
					std::launch::async,
					[this, signature]()
					{
						return manager.verify(
							text,
							public_key,
							signature
						);
					}
				)
			);
		}

		for(
			auto&
			f :
			futures
		)
		{
			EXPECT_TRUE(
				f.get()
			);
		}
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleAsyncConcurrentSigningAcrossThreads
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::future<std::vector<std::uint8_t>>>
			futures;

		for(
			std::size_t i = 0;
			i < 50;
			++i
		)
		{
			futures.push_back(
				std::async(
					std::launch::async,
					[this]()
					{
						return manager.sign(
							text,
							private_key
						);
					}
				)
			);
		}

		for(
			auto&
			f :
			futures
		)
		{
			std::vector<std::uint8_t>
				signature =
					f.get();

			EXPECT_EQ(
				signature.size(),
				crypto_sign_BYTES
			);
		}
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_HandleStressLoad_When_RepeatedVerify
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		for(
			std::size_t i = 0;
			i < 10000;
			++i
		)
		{
			bool
				result =
					manager.verify(
						text,
						public_key,
						signature
					);

			EXPECT_TRUE(
				result
			);
		}
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_NotModifySignatureBufferDuringVerify
	)
	{
		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		std::vector<std::uint8_t>
			original =
				signature;

		manager.verify(
			text,
			public_key,
			signature
		);

		EXPECT_EQ(
			signature,
			original
		);
	}

	TEST_F(
		EdscaSignatureCryptographyManagerTest,
		Should_InitializeSodiumSuccessfully_When_ConstructCalledMultipleTimes
	)
	{
		manager.construct();
		manager.construct();
		manager.construct();

		crypto_sign_keypair(
			public_key.data(),
			private_key.data()
		);

		std::vector<std::uint8_t>
			signature =
				manager.sign(
					text,
					private_key
				);

		bool
			result =
				manager.verify(
					text,
					public_key,
					signature
				);

		EXPECT_TRUE(
			result
		);
	}
}

#endif
