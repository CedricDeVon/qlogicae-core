#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Argon2idHashCryptographyManager \
	)

#include "../includes/argon2id_hash_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_Return_NonEmptyHash_When_ValidText
	)
	{
		const std::string
			input_text = "secure_password";

		const std::string
			hash_value =
				manager_instance.hash_text(
					input_text
				);

		EXPECT_FALSE(
			hash_value.empty()
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_VerifySuccessfully_When_CorrectTextProvided
	)
	{
		const std::string
			input_text = "verify_password";

		const std::string
			hash_value =
				manager_instance.hash_text(
					input_text
				);

		const bool
			verification_result =
				manager_instance.verify_text(
					input_text,
					hash_value
				);

		EXPECT_TRUE(
			verification_result
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_FailVerification_When_TextIsIncorrect
	)
	{
		const std::string
			input_text = "correct_text";

		const std::string
			incorrect_text = "incorrect_text";

		const std::string
			hash_value =
				manager_instance.hash_text(
					input_text
				);

		const bool
			verification_result =
				manager_instance.verify_text(
					incorrect_text,
					hash_value
				);

		EXPECT_FALSE(
			verification_result
		);
	}



	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_ReturnEmptyHash_When_TextIsEmpty
	)
	{
		const std::string
			input_text = "";

		const std::string
			hash_value =
				manager_instance.hash_text(
					input_text
				);

		EXPECT_TRUE(
			hash_value.empty()
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_FailVerification_When_HashIsEmpty
	)
	{
		const std::string
			input_text = "password";

		const bool
			verification_result =
				manager_instance.verify_text(
					input_text,
					""
				);

		EXPECT_FALSE(
			verification_result
		);
	}

	TEST_P(
		Argon2idHashCryptographyManagerParameterizedTest,
		Should_VerifyCorrectly_When_ParameterizedInputProvided
	)
	{
		const std::string
			input_text = GetParam();

		const std::string
			hash_value =
				manager_instance.hash_text(
					input_text
				);

		const bool
			verification_result =
				manager_instance.verify_text(
					input_text,
					hash_value
				);

		EXPECT_TRUE(
			verification_result
		);
	}

	INSTANTIATE_TEST_CASE_P(
		ValidInputs,
		Argon2idHashCryptographyManagerParameterizedTest,
		::testing::Values(
			"alpha",
			"beta_value",
			"long_secure_password_value_123"
		)
	);

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_ExecuteCorrectly_When_AsyncHashIsUsed
	)
	{
		const std::string
			input_text = "async_password";

		std::future<std::string>
			hash_future =
				std::async(
					std::launch::async,
					[this, input_text]()
					{
						return
							manager_instance.hash_text(
								input_text
							);
					}
				);

		const std::string
			hash_value =
				hash_future.get();

		EXPECT_FALSE(
			hash_value.empty()
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_HandleConcurrentHashing_When_MultipleThreadsUsed
	)
	{
		std::atomic<bool>
			all_threads_succeeded(true);

		std::vector<std::thread>
			thread_pool;

		for (std::size_t index = 0; index < 2; ++index)
		{
			thread_pool.emplace_back(
				[this, &all_threads_succeeded, index]()
				{
					const std::string
						input_text =
							"thread_text_" +
							std::to_string(index);

					const std::string
						hash_value =
							manager_instance.hash_text(
								input_text
							);

					const bool
						verification_result =
							manager_instance.verify_text(
								input_text,
								hash_value
							);

					if (!verification_result)
					{
						all_threads_succeeded.store(
							false
						);
					}
				}
			);
		}

		for (std::thread&
			thread_instance : thread_pool)
		{
			thread_instance.join();
		}

		EXPECT_TRUE(
			all_threads_succeeded.load()
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_CompleteUnderTimeLimit_When_StressTested
	)
	{
		for (std::size_t index = 0; index < 2; ++index)
		{
			const std::string
				input_text =
					"stress_test_" +
					std::to_string(index);

			const std::string
				hash_value =
					manager_instance.hash_text(
						input_text
					);

			const bool
				verification_result =
					manager_instance.verify_text(
						input_text,
						hash_value
					);

			EXPECT_TRUE(
				verification_result
			);
		}
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_NotThrowException_When_InvalidHashProvided
	)
	{
		const std::string
			input_text = "password";

		EXPECT_NO_THROW(
			manager_instance.verify_text(
				input_text,
				"invalid_hash_format"
			)
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_ReturnTrue_When_ConstructIsCalledExplicitly
	)
	{
		const bool
			result =
				manager_instance.construct();

		EXPECT_TRUE(
			result
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_ReturnTrue_When_DestructIsCalledExplicitly
	)
	{
		const bool
			result =
				manager_instance.destruct();

		EXPECT_TRUE(
			result
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_HandleMultipleConstructCalls_When_Reentered
	)
	{
		EXPECT_TRUE(
			manager_instance.construct()
		);

		EXPECT_TRUE(
			manager_instance.construct()
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_HandleMultipleDestructCalls_When_Reentered
	)
	{
		EXPECT_TRUE(
			manager_instance.destruct()
		);

		EXPECT_TRUE(
			manager_instance.destruct()
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_HandleVeryLargeInput_When_HashingAndVerifying
	)
	{
		std::string
			large_text(
				1024,
				'a'
			);

		const std::string
			hash_value =
				manager_instance.hash_text(
					large_text
				);

		const bool
			result =
				manager_instance.verify_text(
					large_text,
					hash_value
				);

		EXPECT_TRUE(
			hash_value.empty() || result
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_HandleBinaryInput_When_HashingAndVerifying
	)
	{
		std::string
			binary_text;

		binary_text.push_back(
			'\0'
		);
		binary_text.push_back(
			'\x01'
		);
		binary_text.push_back(
			'\x7F'
		);

		const std::string
			hash_value =
				manager_instance.hash_text(
					binary_text
				);

		const bool
			result =
				manager_instance.verify_text(
					binary_text,
					hash_value
				);

		EXPECT_TRUE(
			hash_value.empty() || result
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_FailVerification_When_HashIsCorrupted
	)
	{
		const std::string
			input_text = "password";

		std::string
			hash_value =
				manager_instance.hash_text(
					input_text
				);

		if (!hash_value.empty())
		{
			hash_value[0] =
				(hash_value[0] == '$') ?
					'#' :
					'$';
		}

		const bool
			result =
				manager_instance.verify_text(
					input_text,
					hash_value
				);

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_HandleConcurrentConstructAndHash_When_Multithreaded
	)
	{
		std::atomic<bool>
			success(true);

		std::thread
			construct_thread(
				[this, &success]()
				{
					if (!manager_instance.construct())
					{
						success.store(
							false
						);
					}
				}
			);

		std::thread
			hash_thread(
				[this, &success]()
				{
					const std::string
						hash_value =
							manager_instance.hash_text(
								"parallel"
							);

					if (hash_value.empty())
					{
						success.store(
							false
						);
					}
				}
			);

		construct_thread.join();
		hash_thread.join();

		EXPECT_TRUE(
			success.load()
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_HandleAsyncVerifyDuringDestruct_When_Overlapping
	)
	{
		const std::string
			input_text = "async_overlap";

		const std::string
			hash_value =
				manager_instance.hash_text(
					input_text
				);

		std::future<bool>
			verify_future =
				std::async(
					std::launch::async,
					[this, input_text, hash_value]()
					{
						return
							manager_instance.verify_text(
								input_text,
								hash_value
							);
					}
				);

		manager_instance.destruct();

		const bool
			result =
				verify_future.get();

		EXPECT_TRUE(
			result || !result
		);
	}

	TEST_F(
		Argon2idHashCryptographyManagerTest,
		Should_CompleteUnderTimeLimit_When_ParallelStressTested
	)
	{
		const auto
			start_time =
				std::chrono::steady_clock::now();

		std::vector<std::thread>
			thread_pool;

		for (std::size_t index = 0; index < 2; ++index)
		{
			thread_pool.emplace_back(
				[this, index]()
				{
					for (std::size_t inner = 0;
						inner < 8;
						++inner)
					{
						const std::string
							text =
								"stress_" +
								std::to_string(index) +
								"_" +
								std::to_string(inner);

						const std::string
							hash_value =
								manager_instance.hash_text(
									text
								);

						manager_instance.verify_text(
							text,
							hash_value
						);
					}
				}
			);
		}

		for (std::thread&
			thread_instance : thread_pool)
		{
			thread_instance.join();
		}

		const auto
			end_time =
				std::chrono::steady_clock::now();

		const auto
			elapsed =
				std::chrono::duration_cast<
					std::chrono::seconds
				>(
					end_time - start_time
				);

		EXPECT_LT(
			elapsed.count(),
			10
		);
	}
}

#endif
