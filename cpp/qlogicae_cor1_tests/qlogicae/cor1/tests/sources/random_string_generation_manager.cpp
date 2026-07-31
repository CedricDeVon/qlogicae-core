#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomStringGenerationManager \
	)

#include "../includes/random_string_generation_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	TEST_F(RandomStringGenerationManagerTest, Should_ReturnEmptyString_When_LengthZero)
	{
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::ASCII_PRINTABLE, 0);
		ASSERT_TRUE(result.empty());
	}

	TEST_F(RandomStringGenerationManagerTest, Should_ReturnEmptyString_When_DomainNone)
	{
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::NONE, 5);
		ASSERT_TRUE(result.empty());
	}

	TEST_F(RandomStringGenerationManagerTest, Should_RespectExclusionSet)
	{
		const std::unordered_set<char> excluded{ 'a','b','c' };
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::ASCII_PRINTABLE, 1000, excluded);
		for (const char ch : result)
			ASSERT_TRUE(excluded.find(ch) == excluded.end());
	}

	TEST_F(RandomStringGenerationManagerTest, Should_GenerateDefaultLengthString)
	{
		const std::string result = manager_instance.generate_string<std::string>(CharacterDomain::ASCII_PRINTABLE);
		ASSERT_EQ(result.length(), manager_instance.configurations.length);
	}

	TEST_F(RandomStringGenerationManagerTest, Should_GenerateStringFromCustomContainer)
	{
		const std::string custom_domain = "XYZ123";
		const std::string result =
			manager_instance.generate_string<std::string>(custom_domain, 50);
		for (const char ch : result)
			ASSERT_NE(custom_domain.find(ch), std::string::npos);
	}

	TEST_F(RandomStringGenerationManagerTest, Should_GenerateStringUsingDefaultContainer)
	{
		const std::string result = manager_instance.generate_string<std::string>();
		const std::string domain =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(manager_instance.configurations.character_domain);
		for (const char ch : result)
			ASSERT_NE(domain.find(ch), std::string::npos);
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleFullExclusionGracefully)
	{
		const std::string domain = "ABC";
		const std::unordered_set<char> excluded{ 'A','B','C' };
		const std::string result =
			manager_instance.generate_string<std::string>(domain, 10, excluded);
		ASSERT_TRUE(result.empty());
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleEmptyCustomDomainGracefully)
	{
		const std::string result =
			manager_instance.generate_string<std::string>("", 10);
		ASSERT_TRUE(result.empty());
	}

	TEST_F(RandomStringGenerationManagerTest, Should_CompleteStressTestWithinTime)
	{
		const auto start_time = std::chrono::steady_clock::now();
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::ALPHANUMERIC, 10000);
		const auto end_time = std::chrono::steady_clock::now();
		ASSERT_LE(std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count(), 2);

		const std::string domain =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(CharacterDomain::ALPHANUMERIC);
		for (const char ch : result)
			ASSERT_NE(domain.find(ch), std::string::npos);
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleAsyncGeneration)
	{
		auto future = std::async(std::launch::async, [&]()
			{
				return manager_instance.generate_string<std::string>(CharacterDomain::ASCII_PRINTABLE, 1000);
			});
		const std::string result = future.get();
		ASSERT_EQ(result.length(), 1000);

		const std::string domain =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(CharacterDomain::ASCII_PRINTABLE);
		for (const char ch : result)
			ASSERT_NE(domain.find(ch), std::string::npos);
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleMultithreadedGeneration)
	{
		const size_t thread_count = 8;
		std::vector<std::thread> threads(thread_count);
		std::vector<std::string> results(thread_count);

		for (size_t i = 0; i < thread_count; ++i)
		{
			threads[i] = std::thread([&, i]()
				{
					results[i] = manager_instance.generate_string<std::string>(CharacterDomain::ASCII_PRINTABLE, 1000);
				});
		}

		for (auto& th : threads)
			th.join();

		const std::string domain =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(CharacterDomain::ASCII_PRINTABLE);

		for (const auto& str : results)
		{
			ASSERT_EQ(str.length(), 1000);
			for (const char ch : str)
				ASSERT_NE(domain.find(ch), std::string::npos);
		}
	}

	TEST_P(ParameterizedDomainTest, Should_ContainOnlyValidCharacters_When_Generated)
	{
		const CharacterDomain domain_value = GetParam();
		const std::string result =
			manager_instance.generate_string<std::string>(domain_value, 1000);
		const std::string domain_string = SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);
		for (const char ch : result)
			ASSERT_NE(domain_string.find(ch), std::string::npos);
	}

	TEST_P(ParameterizedLengthTest, Should_ProduceStringOfExpectedLength)
	{
		const size_t length_value = GetParam();
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::ALPHANUMERIC, length_value);
		ASSERT_EQ(result.length(), length_value);
	}

	INSTANTIATE_TEST_CASE_P(AllDomains, ParameterizedDomainTest,
		::testing::Values(
			CharacterDomain::ASCII_PRINTABLE,
			CharacterDomain::ALPHANUMERIC,
			CharacterDomain::HIGH_ENTROPY_PRINTABLE,
			CharacterDomain::HIGH_ENTROPY_ALPHANUMERIC,
			CharacterDomain::MIXED_CASE_STRESS,
			CharacterDomain::FUZZ_PRINTABLE
		)
	);

	INSTANTIATE_TEST_CASE_P(AllLengths, ParameterizedLengthTest,
		::testing::Values(0, 1, 10, 100, 1000, 10000)
	);

	TEST_F(RandomStringGenerationManagerTest, Should_HandleExcludedTypeDifferentFromOutputType)
	{
		const std::unordered_set<int> excluded_ints{65,66,67};
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::ASCII_PRINTABLE, 100, excluded_ints);
		for (const char ch : result)
			ASSERT_TRUE(excluded_ints.find(static_cast<int>(ch)) == excluded_ints.end());
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleVectorOutputType)
	{
		const std::vector<char> result =
			manager_instance.generate_string<std::vector<char>>(CharacterDomain::ASCII_PRINTABLE, 50);
		ASSERT_EQ(result.size(), 50);
		const std::string domain = SingletonManager::get_singleton<CharacterDomainManager>().get_value(CharacterDomain::ASCII_PRINTABLE);
		for (const char ch : result)
			ASSERT_NE(domain.find(ch), std::string::npos);
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleDuplicateCharacterDomain)
	{
		const std::string dup_domain = "AAABBBCCCDDDEEE";
		const std::string result =
			manager_instance.generate_string<std::string>(dup_domain, 50);
		ASSERT_EQ(result.length(), 50);
		for (const char ch : result)
			ASSERT_NE(dup_domain.find(ch), std::string::npos);
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleEmptyExcludedSet)
	{
		const std::unordered_set<char> empty_excluded;
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::ASCII_PRINTABLE, 100, empty_excluded);
		ASSERT_EQ(result.length(), 100);
		const std::string domain = SingletonManager::get_singleton<CharacterDomainManager>().get_value(CharacterDomain::ASCII_PRINTABLE);
		for (const char ch : result)
			ASSERT_NE(domain.find(ch), std::string::npos);
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleExtremeConcurrency)
	{
		const size_t thread_count = 32;
		const size_t length = 50000;
		std::vector<std::thread> threads(thread_count);
		std::vector<std::string> results(thread_count);

		for (size_t i = 0; i < thread_count; ++i)
		{
			threads[i] = std::thread([&, i]()
				{
					results[i] = manager_instance.generate_string<std::string>(CharacterDomain::ALPHANUMERIC, length);
				});
		}

		for (auto& th : threads)
			th.join();

		const std::string domain = SingletonManager::get_singleton<CharacterDomainManager>().get_value(CharacterDomain::ALPHANUMERIC);

		for (const auto& str : results)
		{
			ASSERT_EQ(str.length(), length);
			for (const char ch : str)
				ASSERT_NE(domain.find(ch), std::string::npos);
		}
	}

	TEST_P(ParameterizedOutputTypeTest, Should_HandleDifferentOutputTypes)
	{
		const std::string result =
			manager_instance.generate_string<std::string>(GetParam(), 50);
		ASSERT_EQ(result.length(), 50);
		for (const char ch : result)
			ASSERT_NE(GetParam().find(ch), std::string::npos);
	}

	INSTANTIATE_TEST_CASE_P(CustomDomains, ParameterizedOutputTypeTest,
		::testing::Values(
			"ABCDEF123",
			"XYZ!@#",
			"aaabbbccc"
		)
	);

	TEST_P(ParameterizedExcludedSetTest, Should_RespectExcludedSet)
	{
		const std::unordered_set<char> excluded = GetParam();
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::ASCII_PRINTABLE, 100, excluded);
		for (const char ch : result)
			ASSERT_TRUE(excluded.find(ch) == excluded.end());
	}

	INSTANTIATE_TEST_CASE_P(VariousExclusions, ParameterizedExcludedSetTest,
		::testing::Values(
			std::unordered_set<char>{'a','b','c'},
			std::unordered_set<char>{'0','1','2','3'},
			std::unordered_set<char>{'!','@','#','$'}
		)
	);

	TEST_F(RandomStringGenerationManagerTest, Should_HandleSingleCharacterDomain)
	{
		const std::string domain = "X";
		const std::string result =
			manager_instance.generate_string<std::string>(domain, 10);
		ASSERT_EQ(result.length(), 10);
		for (const char ch : result)
			ASSERT_EQ(ch, 'X');
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleSingleCharacterDomainWithExclusion)
	{
		const std::string domain = "X";
		const std::unordered_set<char> excluded{'X'};
		const std::string result =
			manager_instance.generate_string<std::string>(domain, 10, excluded);
		ASSERT_TRUE(result.empty());
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleDomainWithDuplicates)
	{
		const std::string domain = "AABBCC";
		const std::string result =
			manager_instance.generate_string<std::string>(domain, 6);
		ASSERT_EQ(result.length(), 6);
		for (const char ch : result)
			ASSERT_TRUE(domain.find(ch) != std::string::npos);
	}

	TEST_P(ParameterizedExcludedSetTest, Should_ExcludeAllSpecifiedCharacters)
	{
		const std::unordered_set<char> excluded = GetParam();
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::ASCII_PRINTABLE, 1000, excluded);
		for (const char ch : result)
			ASSERT_TRUE(excluded.find(ch) == excluded.end());
	}

	INSTANTIATE_TEST_CASE_P(AllExcludedSets, ParameterizedExcludedSetTest,
		::testing::Values(
			std::unordered_set<char>{'a'},
			std::unordered_set<char>{'a','b','c'},
			std::unordered_set<char>{'0','1','2','3','4','5','6','7','8','9'},
			std::unordered_set<char>{'!','@','#','$','%','^','&','*','('},
			std::unordered_set<char>{}
		)
	);

	TEST_F(RandomStringGenerationManagerTest, Should_HandleMultithreadedMinimalDomain)
	{
		const std::string domain = "Z";
		const size_t thread_count = 8;
		std::vector<std::thread> threads(thread_count);
		std::vector<std::string> results(thread_count);

		for (size_t i = 0; i < thread_count; ++i)
		{
			threads[i] = std::thread([&, i]()
			{
				results[i] = manager_instance.generate_string<std::string>(domain, 5);
			});
		}

		for (auto& th : threads)
			th.join();

		for (const auto& str : results)
		{
			ASSERT_EQ(str.length(), 5);
			for (const char ch : str)
				ASSERT_EQ(ch, 'Z');
		}
	}

	TEST_F(RandomStringGenerationManagerTest, Should_GenerateStringWithMaxLength)
	{
		const size_t max_length = 100000;
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::ASCII_PRINTABLE, max_length);
		ASSERT_EQ(result.length(), max_length);

		const std::string domain =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(CharacterDomain::ASCII_PRINTABLE);
		for (const char ch : result)
			ASSERT_NE(domain.find(ch), std::string::npos);
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleEdgeDomainsWithExclusions)
	{
		const std::unordered_set<char> excluded{'A','B','C','D','E','F'};
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::HIGH_ENTROPY_PRINTABLE, 500, excluded);
		const std::string domain =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(CharacterDomain::HIGH_ENTROPY_PRINTABLE);
		for (const char ch : result)
			ASSERT_TRUE(excluded.find(ch) == excluded.end() && domain.find(ch) != std::string::npos);
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleFuzzDomainsWithExclusions)
	{
		const std::unordered_set<char> excluded{'1','2','3','4','5'};
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::FUZZ_PRINTABLE, 500, excluded);
		const std::string domain =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(CharacterDomain::FUZZ_PRINTABLE);
		for (const char ch : result)
			ASSERT_TRUE(excluded.find(ch) == excluded.end() && domain.find(ch) != std::string::npos);
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleLargeDomain)
	{
		std::string large_domain;
		for (int i = 0; i < 1000000; ++i)
			large_domain += static_cast<char>(i % 256);
		const std::string result =
			manager_instance.generate_string<std::string>(large_domain, 1000);
		ASSERT_EQ(result.length(), 1000);
		for (const char ch : result)
			ASSERT_NE(large_domain.find(ch), std::string::npos);
	}

	TEST_F(RandomStringGenerationManagerTest, Should_HandleExcludedSetWithMultithreading)
	{
		const std::unordered_set<char> excluded{'a','b','c','d'};
		const size_t thread_count = 8;
		const size_t length = 500;
		std::vector<std::thread> threads(thread_count);
		std::vector<std::string> results(thread_count);
		for (size_t i = 0; i < thread_count; ++i)
		{
			threads[i] = std::thread([&, i]()
			{
				results[i] = manager_instance.generate_string<std::string>(
					CharacterDomain::ALPHANUMERIC, length, excluded);
			});
		}
		for (auto& th : threads)
			th.join();
		const std::string domain = SingletonManager::get_singleton<CharacterDomainManager>().get_value(CharacterDomain::ALPHANUMERIC);
		for (const auto& str : results)
		{
			ASSERT_EQ(str.length(), length);
			for (const char ch : str)
				ASSERT_TRUE(excluded.find(ch) == excluded.end() && domain.find(ch) != std::string::npos);
		}
	}

	TEST_P(ParameterizedDomainTest, Should_HandleEdgeDomains)
	{
		const CharacterDomain domain_value = GetParam();
		const std::string result =
			manager_instance.generate_string<std::string>(domain_value, 500);
		const std::string domain_string = SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);
		ASSERT_EQ(result.length(), 500);
		for (const char ch : result)
			ASSERT_NE(domain_string.find(ch), std::string::npos);
	}

	TEST_P(ParameterizedLengthTest, Should_HandleVeryLargeLength)
	{
		const size_t length_value = GetParam();
		const std::string result =
			manager_instance.generate_string<std::string>(CharacterDomain::ALPHANUMERIC, length_value);
		ASSERT_EQ(result.length(), length_value);
		for (const char ch : result)
			ASSERT_NE(SingletonManager::get_singleton<CharacterDomainManager>().get_value(CharacterDomain::ALPHANUMERIC).find(ch), std::string::npos);
	}

	INSTANTIATE_TEST_CASE_P(EdgeDomains, ParameterizedDomainTest,
		::testing::Values(
			CharacterDomain::HIGH_ENTROPY_PRINTABLE,
			CharacterDomain::HIGH_ENTROPY_ALPHANUMERIC
		)
	);

	INSTANTIATE_TEST_CASE_P(VeryLargeLengths, ParameterizedLengthTest,
		::testing::Values(50000, 100000)
	);
}

#endif
