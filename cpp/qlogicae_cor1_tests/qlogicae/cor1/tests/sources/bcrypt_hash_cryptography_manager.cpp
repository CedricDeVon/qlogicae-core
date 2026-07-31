#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		BcryptHashCryptographyManager \
	)

#include "../includes/bcrypt_hash_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_DestructSuccessfully_When_Called
	)
	{
		bool result =
			manager.destruct();

		EXPECT_TRUE(result);
	}

	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_ReturnValidHash_When_TextIsValid
	)
	{
		std::string text =
			"valid_password";

		std::string hash =
			manager.hash_text(text);

		EXPECT_FALSE(hash.empty());
	}

	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_ReturnEmptyHash_When_TextIsEmpty
	)
	{
		std::string text =
			"";

		std::string hash =
			manager.hash_text(text);

		EXPECT_TRUE(hash.empty());
	}

	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_VerifySuccessfully_When_HashMatchesText
	)
	{
		std::string text =
			"verification_password";

		std::string hash =
			manager.hash_text(text);

		bool result =
			manager.verify_text(text, hash);

		EXPECT_TRUE(result);
	}

	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_FailVerification_When_TextDoesNotMatchHash
	)
	{
		std::string text =
			"original_text";

		std::string hash =
			manager.hash_text(text);

		bool result =
			manager.verify_text(
				"different_text",
				hash
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_HandleConcurrentHashing_When_MultipleThreadsUsed
	)
	{
		std::atomic<bool>
			all_successful =
				true;

		std::vector<std::thread>
			threads;

		for (std::size_t iteration = 0;
			 iteration < 2;
			 ++iteration)
		{
			threads.emplace_back(
				[this, &all_successful]()
				{
					std::string hash =
						manager.hash_text(
							"concurrent_text");

					if (hash.empty())
					{
						all_successful =
							false;
					}
				}
			);
		}

		for (std::thread&
				thread_instance :
				threads)
		{
			thread_instance.join();
		}

		EXPECT_TRUE(all_successful.load());
	}

	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_HandleAsyncHashing_When_UsingStdAsync
	)
	{
		auto future_hash =
			std::async(
				std::launch::async,
				[this]()
				{
					return
						manager.hash_text(
							"async_text");
				}
			);

		std::string hash =
			future_hash.get();

		EXPECT_FALSE(hash.empty());
	}

	TEST_P(
		BcryptHashCryptographyManagerParameterizedTest,
		Should_GenerateHash_When_TextIsParameterized
	)
	{
		std::string text =
			GetParam();

		std::string hash =
			manager.hash_text(text);

		EXPECT_FALSE(hash.empty());
	}

	INSTANTIATE_TEST_CASE_P(
		ValidInputs,
		BcryptHashCryptographyManagerParameterizedTest,
		::testing::Values(
			std::string("a"),
			std::string("longer_password_text"),
			std::string("1234567890"),
			std::string("!@#$%^&*()")
		)
	);

	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_HandleExceptionSafety_When_InternalErrorOccurs
	)
	{
		try
		{
			std::string hash =
				manager.hash_text(
					std::string(8, 'x'));

			EXPECT_FALSE(hash.empty());
		}
		catch (...)
		{
			FAIL();
		}
	}

	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_SetupSuccessfully_When_NewConfigurationsProvided
	)
	{
		BcryptHashCryptographyManagerConfigurations
			new_configurations;

		bool result =
			manager.setup(
				new_configurations
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_ResetSuccessfully_When_Called
	)
	{
		bool result =
			manager.reset();

		EXPECT_TRUE(result);
	}

	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_HandleThreadSafetyDisabled_When_UtilityHandling
	)
	{
		BcryptHashCryptographyManagerConfigurations
			new_configurations;

		new_configurations
			.is_utility_thread_safety_handling_enabled =
				false;

		manager.setup(
			new_configurations
		);

		bool result =
			manager.construct();

		EXPECT_TRUE(result);
	}

	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_HandleThreadSafetyOverride_When_Enabled
	)
	{
		BcryptHashCryptographyManagerConfigurations
			new_configurations;

		new_configurations
			.is_thread_safety_handling_override_enabled =
				true;

		manager.setup(
			new_configurations
		);

		bool result =
			manager.destruct();

		EXPECT_TRUE(result);
	}

	TEST_F(
		BcryptHashCryptographyManagerTest,
		Should_HandleAsyncVerification_When_UsingStdAsync
	)
	{
		std::string text =
			"async_verify_text";

		std::string hash =
			manager.hash_text(
				text
			);

		auto future_result =
			std::async(
				std::launch::async,
				[this,
				 text,
				 hash]()
				{
					return
						manager.verify_text(
							text,
							hash
						);
				}
			);

		bool result =
			future_result.get();

		EXPECT_TRUE(result);
	}
}

#endif
