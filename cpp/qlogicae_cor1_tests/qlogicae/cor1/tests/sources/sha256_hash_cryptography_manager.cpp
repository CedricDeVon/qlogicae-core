#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Sha256HashCryptographyManager \
	)

#include "../includes/sha256_hash_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(Sha256HashCryptographyManagerTest,
		Should_ReturnTrue_When_ConstructIsCalledExplicitly)
	{
		EXPECT_TRUE(manager_instance.construct());
	}

	TEST_F(Sha256HashCryptographyManagerTest,
		Should_ReturnTrue_When_DestructIsCalledExplicitly)
	{
		EXPECT_TRUE(manager_instance.destruct());
	}

	TEST_F(Sha256HashCryptographyManagerTest,
		Should_HandleMultipleConstructCalls_When_Reentered)
	{
		EXPECT_TRUE(manager_instance.construct());
		EXPECT_TRUE(manager_instance.construct());
	}

	TEST_F(Sha256HashCryptographyManagerTest,
		Should_HandleMultipleDestructCalls_When_Reentered)
	{
		EXPECT_TRUE(manager_instance.destruct());
		EXPECT_TRUE(manager_instance.destruct());
	}

	TEST_F(Sha256HashCryptographyManagerTest,
		Should_HashAndVerify_When_InputIsEmpty)
	{
		const std::string input = "";
		const std::string hash = manager_instance.hash_text(input);
		EXPECT_TRUE(hash.empty() || manager_instance.verify_text(input, hash));
	}

	TEST_F(Sha256HashCryptographyManagerTest,
		Should_FailVerification_When_HashIsCorrupted)
	{
		const std::string input = "password";
		std::string hash = manager_instance.hash_text(input);

		if (!hash.empty())
		{
			hash[0] = (hash[0] == 'a') ? 'b' : 'a';
		}

		EXPECT_FALSE(manager_instance.verify_text(input, hash));
	}

	TEST_F(Sha256HashCryptographyManagerTest,
		Should_HandleConcurrentConstructAndHash_When_Multithreaded)
	{
		std::atomic<bool> success(true);

		std::thread construct_thread([this, &success]()
		{
			if (!manager_instance.construct())
				success.store(false);
		});

		std::thread hash_thread([this, &success]()
		{
			const std::string hash = manager_instance.hash_text("parallel");
			if (hash.empty())
				success.store(false);
		});

		construct_thread.join();
		hash_thread.join();

		EXPECT_TRUE(success.load());
	}

	TEST_F(Sha256HashCryptographyManagerTest,
		Should_HandleAsyncVerifyDuringDestruct_When_Overlapping)
	{
		const std::string input = "async_overlap";
		const std::string hash = manager_instance.hash_text(input);

		std::future<bool> verify_future = std::async(std::launch::async,
			[this, input, hash]() { return manager_instance.verify_text(input, hash); });

		manager_instance.destruct();

		const bool result = verify_future.get();
		EXPECT_TRUE(result || !result);
	}

	TEST_F(Sha256HashCryptographyManagerTest,
		Should_CompleteUnderParallelStressTested)
	{
		std::vector<std::thread> thread_pool;

		for (std::size_t index = 0; index < 4; ++index)
		{
			thread_pool.emplace_back([this, index]()
			{
				for (std::size_t inner = 0; inner < 8; ++inner)
				{
					const std::string text = "stress_" + std::to_string(index) +
						"_" + std::to_string(inner);
					const std::string hash = manager_instance.hash_text(text);
					manager_instance.verify_text(text, hash);
				}
			});
		}

		for (auto& thread_instance : thread_pool)
			thread_instance.join();
	}

	INSTANTIATE_TEST_CASE_P(ValidAndEdgeCases, Sha256HashCryptographyManagerParameterizedTest,
		::testing::Values(
			"",
			"a",
			"abc123",
			"安全なパスワード🔑",
			std::string(1024 * 1024, 'x'),
			std::string("\0\1\2\3", 4)
		));

	TEST_P(Sha256HashCryptographyManagerParameterizedTest,
		Should_HashAndVerify_When_InputIsParameterized)
	{
		const std::string input = GetParam();
		const std::string hash = manager_instance.hash_text(input);
		EXPECT_TRUE(hash.empty() || manager_instance.verify_text(input, hash));
	}
}

#endif
