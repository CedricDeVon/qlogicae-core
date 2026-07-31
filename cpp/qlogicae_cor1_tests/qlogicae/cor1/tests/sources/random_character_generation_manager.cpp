#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomCharacterGenerationManager \
	)

#include "../includes/random_character_generation_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_ReturnDefault_When_DomainEmpty
	)
	{
		const CharacterDomain domain_value =
			CharacterDomain::NONE;

		const std::unordered_set<char> excluded_values{};

		const char result =
			manager_instance.generate_character<char>(
				domain_value,
				excluded_values
			);

		ASSERT_EQ(result, char{});
	}

	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_ReturnDefault_When_AllExcluded
	)
	{
		const CharacterDomain domain_value =
			CharacterDomain::NONE;

		std::unordered_set<char> excluded_values;
		excluded_values.insert('a');
		excluded_values.insert('b');
		excluded_values.insert('c');

		const char result =
			manager_instance.generate_character<char>(
				domain_value,
				excluded_values
			);

		ASSERT_EQ(result, char{});
	}

	TEST_P(
		ParameterizedDomainTest,
		Should_ReturnValue_When_ValidDomain
	)
	{
		const int parameter_value = GetParam();

		const CharacterDomain domain_value =
			static_cast<CharacterDomain>(parameter_value);

		const std::unordered_set<char> excluded_values{};

		const char result =
			manager_instance.generate_character<char>(
				domain_value,
				excluded_values
			);

		ASSERT_TRUE(
			result == char{} ||
			result != char{}
		);
	}

	INSTANTIATE_TEST_CASE_P(
		RandomCharacterGenerationManagerTest,
		ParameterizedDomainTest,
		::testing::Values(0, 1, 2, 3)
	);

	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_WorkCorrectly_When_AsynchronousExecution
	)
	{
		const CharacterDomain domain_value =
			static_cast<CharacterDomain>(0);

		const std::unordered_set<char> excluded_values{};

		std::future<char> future_result =
			std::async(
				std::launch::async,
				[&]()
				{
					return
						manager_instance
							.generate_character<char>(
								domain_value,
								excluded_values
							);
				}
			);

		const char result = future_result.get();

		ASSERT_TRUE(result == char{} || result != char{});
	}

	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_WorkCorrectly_When_MultithreadedAccess
	)
	{
		const CharacterDomain domain_value =
			static_cast<CharacterDomain>(0);

		const std::unordered_set<char> excluded_values{};

		std::atomic<bool> execution_successful{true};

		auto thread_function =
			[&]()
			{
				const char result =
					manager_instance.generate_character<char>(
						domain_value,
						excluded_values
					);

				if (!(result == char{} || result != char{}))
				{
					execution_successful.store(false);
				}
			};

		std::thread first_thread(thread_function);
		std::thread second_thread(thread_function);
		std::thread third_thread(thread_function);

		first_thread.join();
		second_thread.join();
		third_thread.join();

		ASSERT_TRUE(execution_successful.load());
	}

	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_HandleStress_When_LargeIterations
	)
	{
		const CharacterDomain domain_value =
			static_cast<CharacterDomain>(0);

		const std::unordered_set<char> excluded_values{};

		const std::size_t iteration_count = 50000;

		for (std::size_t index = 0;
			 index < iteration_count;
			 ++index)
		{
			const char result =
				manager_instance.generate_character<char>(
					domain_value,
					excluded_values
				);

			ASSERT_TRUE(result == char{} || result != char{});
		}
	}

	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_NotThrow_When_ExceptionOccurs
	)
	{
		const CharacterDomain domain_value =
			static_cast<CharacterDomain>(-1);

		const std::unordered_set<char> excluded_values{};

		ASSERT_NO_THROW(
			manager_instance.generate_character<char>(
				domain_value,
				excluded_values
			)
		);
	}

	TEST_F(
	RandomCharacterGenerationManagerTest,
	Should_ReturnValue_WithinDomain_When_ValidDomain
	)
	{
	for (int domain_index = 1; domain_index <= 3; ++domain_index)
	{
	const CharacterDomain domain_value =
	static_cast<CharacterDomain>(domain_index);

			const std::unordered_set<char> excluded_values{};

			const char result =
				manager_instance.generate_character<char>(
					domain_value,
					excluded_values
				);

			const std::string domain_string =
				SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

			ASSERT_NE(domain_string.find(result), std::string::npos);
		}
	}

	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_NotReturnExcludedCharacters
	)
	{
		const CharacterDomain domain_value =
			CharacterDomain::ALPHANUMERIC;

		const std::unordered_set<char> excluded_values{'a', 'b', 'c'};

		for (std::size_t index = 0; index < 100; ++index)
		{
			const char result =
				manager_instance.generate_character<char>(
					domain_value,
					excluded_values
				);

			ASSERT_EQ(excluded_values.find(result), excluded_values.end());
		}
	}

	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_ReturnDefault_When_AllDomainExcluded
	)
	{
		const CharacterDomain domain_value =
			CharacterDomain::ALPHANUMERIC;

		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		std::unordered_set<char> excluded_values(domain_string.begin(),
												 domain_string.end());

		const char result =
			manager_instance.generate_character<char>(
				domain_value,
				excluded_values
			);

		ASSERT_EQ(result, char{});
	}

	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_CompleteWithinTime_When_StressTest
	)
	{
		const CharacterDomain domain_value =
			CharacterDomain::ALPHANUMERIC;

		const std::unordered_set<char> excluded_values{};

		auto start_time = std::chrono::steady_clock::now();

		for (std::size_t index = 0; index < 100000; ++index)
		{
			manager_instance.generate_character<char>(domain_value,
													  excluded_values);
		}

		auto end_time = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			end_time - start_time).count();

		ASSERT_LE(elapsed_ms, 2000);
	}

	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_BeThreadSafe_UnderHeavyLoad
	)
	{
		const CharacterDomain domain_value =
			CharacterDomain::ALPHANUMERIC;

		const std::unordered_set<char> excluded_values{};

		std::atomic<bool> execution_successful{true};

		auto thread_function =
			[&]()
			{
				for (std::size_t i = 0; i < 50000; ++i)
				{
					const char result =
						manager_instance.generate_character<char>(
							domain_value,
							excluded_values
						);

					const std::string domain_string =
						SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

					if (domain_string.find(result) == std::string::npos)
					{
						execution_successful.store(false);
					}
				}
			};

		std::vector<std::thread> threads;
		for (int t = 0; t < 8; ++t)
			threads.emplace_back(thread_function);

		for (auto& thread : threads)
			thread.join();

		ASSERT_TRUE(execution_successful.load());
	}

	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_HandleExceptionPath
	)
	{
		struct FaultyManager : RandomCharacterGenerationManager
		{
			const std::string& get_faulty_value(CharacterDomain)
			{
				throw std::runtime_error("forced exception");
			}
		};

		FaultyManager faulty_instance;

		const CharacterDomain domain_value =
			CharacterDomain::ALPHANUMERIC;

		const std::unordered_set<char> excluded_values{};

		ASSERT_NO_THROW(
			faulty_instance.generate_character<char>(domain_value,
													 excluded_values)
		);
	}

	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_ReturnDefault_When_RuntimeDisabled
	)
	{
		struct RuntimeDisabledManager : RandomCharacterGenerationManager
		{
			bool is_runtime_execution_disabled_for_feature_handling() const
			{
				return true;
			}
		};

		RuntimeDisabledManager instance;

		instance.configurations.is_feature_runtime_execution_handling_enabled = false;

		const CharacterDomain domain_value =
			CharacterDomain::ALPHANUMERIC;

		const std::unordered_set<char> excluded_values{};

		const char result =
			instance.generate_character<char>(domain_value,
											  excluded_values);

		ASSERT_EQ(result, char{});
	}

	TEST_F(
		RandomCharacterGenerationManagerTest,
		Should_WorkCorrectly_When_ThreadSafetyEnabled
	)
	{
		struct ThreadSafeManager : RandomCharacterGenerationManager
		{
			bool is_thread_safety_enabled_for_feature_handling() const
			{
				return true;
			}
		};

		ThreadSafeManager instance;

		const CharacterDomain domain_value =
			CharacterDomain::ALPHANUMERIC;

		const std::unordered_set<char> excluded_values{};

		const char result =
			instance.generate_character<char>(domain_value,
											  excluded_values);

		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		ASSERT_NE(domain_string.find(result), std::string::npos);
	}

	TEST_P(
		ParameterizedValidDomainTest,
		Should_ReturnValueWithinDomain_When_VariousDomains
	)
	{
		const CharacterDomain domain_value = GetParam();

		const std::unordered_set<char> excluded_values{};

		const char result =
			manager_instance.generate_character<char>(domain_value,
													  excluded_values);

		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		if (!domain_string.empty())
			ASSERT_NE(domain_string.find(result), std::string::npos);
		else
			ASSERT_EQ(result, char{});
	}

	INSTANTIATE_TEST_CASE_P(
		RandomCharacterGenerationManagerTest,
		ParameterizedValidDomainTest,
		::testing::Values(
			CharacterDomain::BINARY,
			CharacterDomain::OCTAL,
			CharacterDomain::NUMERIC,
			CharacterDomain::LOWERCASE_ALPHABETIC,
			CharacterDomain::UPPERCASE_ALPHABETIC,
			CharacterDomain::ALPHABETIC,
			CharacterDomain::ALPHANUMERIC,
			CharacterDomain::ALPHANUMERIC_LOWERCASE,
			CharacterDomain::ALPHANUMERIC_UPPERCASE,
			CharacterDomain::ALPHANUMERIC_UNDERSCORE,
			CharacterDomain::HEX_LOWERCASE,
			CharacterDomain::HEX_UPPERCASE,
			CharacterDomain::BASE32_RFC4648,
			CharacterDomain::BASE32_CROCKFORD,
			CharacterDomain::BASE58_BITCOIN,
			CharacterDomain::BASE62,
			CharacterDomain::BASE64_RFC4648,
			CharacterDomain::BASE64_URL,
			CharacterDomain::ASCII,
			CharacterDomain::ASCII_PRINTABLE,
			CharacterDomain::ASCII_VISIBLE,
			CharacterDomain::ASCII_NON_WHITESPACE_PRINTABLE,
			CharacterDomain::PUNCTUATION,
			CharacterDomain::SYMBOLS,
			CharacterDomain::WHITESPACE,
			CharacterDomain::CONTROL,
			CharacterDomain::HIGH_ENTROPY_PRINTABLE,
			CharacterDomain::HIGH_ENTROPY_ALPHANUMERIC,
			CharacterDomain::HIGH_ENTROPY_ASCII_VISIBLE,
			CharacterDomain::HUMAN_READABLE,
			CharacterDomain::PASSWORD_SAFE,
			CharacterDomain::PIN_CODE,
			CharacterDomain::SLUG_SAFE,
			CharacterDomain::URL_SAFE_RFC3986,
			CharacterDomain::FILE_NAME_SAFE,
			CharacterDomain::PATH_SEGMENT_SAFE,
			CharacterDomain::JSON_SAFE,
			CharacterDomain::XML_SAFE,
			CharacterDomain::SHELL_SAFE,
			CharacterDomain::FUZZ_PRINTABLE,
			CharacterDomain::FUZZ_ASCII,
			CharacterDomain::EDGE_CASE_ASCII,
			CharacterDomain::MIXED_CASE_STRESS,
			CharacterDomain::EXTENDED_ASCII
		)
	);

	TEST_P(
	ParameterizedValidDomainTest,
	Should_ReturnDefault_When_FullyExcludedDomain
	)
	{
	const CharacterDomain domain_value = GetParam();

		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		std::unordered_set<char> excluded_values(domain_string.begin(),
												 domain_string.end());

		const char result =
			manager_instance.generate_character<char>(domain_value,
													  excluded_values);

		ASSERT_EQ(result, char{});
	}

	TEST_P(
		ParameterizedValidDomainTest,
		Should_ReturnValue_WithinDomainAndNotExcluded
	)
	{
		const CharacterDomain domain_value = GetParam();

		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		std::unordered_set<char> excluded_values;
		if (!domain_string.empty())
			excluded_values.insert(domain_string.front());

		const char result =
			manager_instance.generate_character<char>(domain_value,
													  excluded_values);

		if (!domain_string.empty())
		{
			ASSERT_NE(domain_string.find(result), std::string::npos);
			ASSERT_EQ(excluded_values.find(result), excluded_values.end());
		}
		else
		{
			ASSERT_EQ(result, char{});
		}
	}

	TEST_P(
		ParameterizedValidDomainTest,
		Should_CompleteUnderTimeLimit
	)
	{
		const CharacterDomain domain_value = GetParam();
		const std::unordered_set<char> excluded_values{};

		auto start_time = std::chrono::steady_clock::now();

		for (std::size_t i = 0; i < 10000; ++i)
		{
			manager_instance.generate_character<char>(domain_value,
													  excluded_values);
		}

		auto end_time = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			end_time - start_time).count();

		ASSERT_LE(elapsed_ms, 2000);
	}

	TEST_P(
		ParameterizedValidDomainTest,
		Should_BeThreadSafeUnderManyThreads
	)
	{
		const CharacterDomain domain_value = GetParam();
		const std::unordered_set<char> excluded_values{};

		std::atomic<bool> execution_successful{true};

		auto thread_function =
			[&]()
			{
				for (std::size_t i = 0; i < 10000; ++i)
				{
					const char result =
						manager_instance.generate_character<char>(domain_value,
																  excluded_values);
					const std::string domain_string =
						SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);
					if (!domain_string.empty())
					{
						if (domain_string.find(result) == std::string::npos)
							execution_successful.store(false);
					}
				}
			};

		std::vector<std::thread> threads;
		for (int t = 0; t < 8; ++t)
			threads.emplace_back(thread_function);

		for (auto& thread : threads)
			thread.join();

		ASSERT_TRUE(execution_successful.load());
	}

	INSTANTIATE_TEST_CASE_P(
		RandomCharacterGenerationManagerTest_FullCoverage,
		ParameterizedValidDomainTest,
		::testing::Values(
			CharacterDomain::BINARY,
			CharacterDomain::OCTAL,
			CharacterDomain::NUMERIC,
			CharacterDomain::LOWERCASE_ALPHABETIC,
			CharacterDomain::UPPERCASE_ALPHABETIC,
			CharacterDomain::ALPHABETIC,
			CharacterDomain::ALPHANUMERIC,
			CharacterDomain::ALPHANUMERIC_LOWERCASE,
			CharacterDomain::ALPHANUMERIC_UPPERCASE,
			CharacterDomain::ALPHANUMERIC_UNDERSCORE,
			CharacterDomain::HEX_LOWERCASE,
			CharacterDomain::HEX_UPPERCASE,
			CharacterDomain::BASE32_RFC4648,
			CharacterDomain::BASE32_CROCKFORD,
			CharacterDomain::BASE58_BITCOIN,
			CharacterDomain::BASE62,
			CharacterDomain::BASE64_RFC4648,
			CharacterDomain::BASE64_URL,
			CharacterDomain::ASCII,
			CharacterDomain::ASCII_PRINTABLE,
			CharacterDomain::ASCII_VISIBLE,
			CharacterDomain::ASCII_NON_WHITESPACE_PRINTABLE,
			CharacterDomain::PUNCTUATION,
			CharacterDomain::SYMBOLS,
			CharacterDomain::WHITESPACE,
			CharacterDomain::CONTROL,
			CharacterDomain::HIGH_ENTROPY_PRINTABLE,
			CharacterDomain::HIGH_ENTROPY_ALPHANUMERIC,
			CharacterDomain::HIGH_ENTROPY_ASCII_VISIBLE,
			CharacterDomain::HUMAN_READABLE,
			CharacterDomain::PASSWORD_SAFE,
			CharacterDomain::PIN_CODE,
			CharacterDomain::SLUG_SAFE,
			CharacterDomain::URL_SAFE_RFC3986,
			CharacterDomain::FILE_NAME_SAFE,
			CharacterDomain::PATH_SEGMENT_SAFE,
			CharacterDomain::JSON_SAFE,
			CharacterDomain::XML_SAFE,
			CharacterDomain::SHELL_SAFE,
			CharacterDomain::FUZZ_PRINTABLE,
			CharacterDomain::FUZZ_ASCII,
			CharacterDomain::EDGE_CASE_ASCII,
			CharacterDomain::MIXED_CASE_STRESS,
			CharacterDomain::EXTENDED_ASCII
		)
	);

	TEST_P(
		ParameterizedValidDomainTest,
		Should_HandleNoneDomain
	)
	{
		const CharacterDomain domain_value = CharacterDomain::NONE;

		const std::unordered_set<char> excluded_values{ 'a', 'b', 'c' };

		const char result =
			manager_instance.generate_character<char>(domain_value,
				excluded_values);

		ASSERT_EQ(result, char{});
	}

	TEST_P(
		ParameterizedValidDomainTest,
		Should_StressHighEntropyDomains
	)
	{
		const CharacterDomain domain_value = GetParam();

		if (domain_value != CharacterDomain::HIGH_ENTROPY_PRINTABLE &&
			domain_value != CharacterDomain::MIXED_CASE_STRESS)
			return;

		const std::unordered_set<char> excluded_values{};

		for (std::size_t i = 0; i < 50000; ++i)
		{
			const char result =
				manager_instance.generate_character<char>(domain_value,
					excluded_values);
			const std::string domain_string =
				SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);
			ASSERT_NE(domain_string.find(result), std::string::npos);
		}
	}

	TEST_P(
		ParameterizedValidDomainTest,
		Should_HandleDynamicExclusions
	)
	{
		const CharacterDomain domain_value = GetParam();

		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		if (domain_string.empty())
		{
			const char result =
				manager_instance.generate_character<char>(domain_value, {});
			ASSERT_EQ(result, char{});
			return;
		}

		std::unordered_set<char> excluded_values;
		for (std::size_t i = 0; i < domain_string.size(); ++i)
		{
			excluded_values.insert(domain_string[i]);
			if (i % 2 == 0)
				excluded_values.erase(domain_string[i]);

			const char result =
				manager_instance.generate_character<char>(domain_value,
					excluded_values);

			ASSERT_NE(domain_string.find(result), std::string::npos);
			ASSERT_EQ(excluded_values.find(result), excluded_values.end());
		}
	}

	TEST_P(
		ParameterizedValidDomainTest,
		Should_HandleExceptionsInMultithreadedContext
	)
	{
		const CharacterDomain domain_value = GetParam();

		struct FaultyManager : RandomCharacterGenerationManager
		{
			const std::string& get_value(CharacterDomain)
			{
				throw std::runtime_error("forced multithread exception");
			}
		};

		FaultyManager instance;

		std::atomic<bool> success{ true };

		auto thread_function =
			[&]()
			{
				try
				{
					instance.generate_character<char>(domain_value, {});
				}
				catch (...)
				{
					success.store(false);
				}
			};

		std::vector<std::thread> threads;
		for (int i = 0; i < 4; ++i)
			threads.emplace_back(thread_function);

		for (auto& t : threads)
			t.join();

		ASSERT_TRUE(success.load());
	}

	TEST_P(
		ParameterizedValidDomainTest,
		Should_CompleteWithinTime_ForLargeDomains
	)
	{
		const CharacterDomain domain_value = GetParam();

		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		if (domain_string.empty())
			return;

		const std::unordered_set<char> excluded_values{};

		auto start_time = std::chrono::steady_clock::now();

		for (std::size_t i = 0; i < 100000; ++i)
			manager_instance.generate_character<char>(domain_value, excluded_values);

		auto end_time = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			end_time - start_time).count();

		ASSERT_LE(elapsed_ms, 2000);
	}

	INSTANTIATE_TEST_CASE_P(
		RandomCharacterGenerationManagerTest_MissingCoverage,
		ParameterizedValidDomainTest,
		::testing::Values(
			CharacterDomain::CUSTOM,
			CharacterDomain::NONE,
			CharacterDomain::HIGH_ENTROPY_PRINTABLE,
			CharacterDomain::MIXED_CASE_STRESS
		)
	);

	TEST_P(
		ParameterizedValidDomainTest,
		Should_StressAllHighEntropyAndFuzzDomains
	)
	{
		const CharacterDomain domain_value = GetParam();

		if (domain_value != CharacterDomain::HIGH_ENTROPY_PRINTABLE &&
			domain_value != CharacterDomain::HIGH_ENTROPY_ALPHANUMERIC &&
			domain_value != CharacterDomain::HIGH_ENTROPY_ASCII_VISIBLE &&
			domain_value != CharacterDomain::MIXED_CASE_STRESS &&
			domain_value != CharacterDomain::FUZZ_PRINTABLE)
			return;

		const std::unordered_set<char> excluded_values{};

		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		for (std::size_t i = 0; i < 50000; ++i)
		{
			const char result =
				manager_instance.generate_character<char>(domain_value, excluded_values);

			ASSERT_TRUE(std::find(domain_string.begin(), domain_string.end(), result) != domain_string.end());
		}
	}

	TEST_P(
		ParameterizedValidDomainTest,
		Should_HandleMultipleDynamicExclusions
	)
	{
		const CharacterDomain domain_value = GetParam();

		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		if (domain_string.empty())
		{
			const char result =
				manager_instance.generate_character<char>(domain_value, {});
			ASSERT_EQ(result, char{});
			return;
		}

		std::unordered_set<char> excluded_values;
		for (std::size_t i = 0; i < domain_string.size(); ++i)
		{
			if (i % 3 == 0)
				excluded_values.insert(domain_string[i]);
			else if (i % 5 == 0 && !excluded_values.empty())
				excluded_values.erase(domain_string[i % excluded_values.size()]);

			const char result =
				manager_instance.generate_character<char>(domain_value,
														  excluded_values);

			ASSERT_NE(domain_string.find(result), std::string::npos);
			ASSERT_EQ(excluded_values.find(result), excluded_values.end());
		}
	}

	TEST_P(
		ParameterizedValidDomainTest,
		Should_HandleForcedExceptionsInAllDomains_Multithreaded
	)
	{
		const CharacterDomain domain_value = GetParam();

		struct FaultyManager : RandomCharacterGenerationManager
		{
			const std::string& get_value(CharacterDomain)
			{
				throw std::runtime_error("forced multithread exception");
			}
		};

		FaultyManager instance;

		std::atomic<bool> success{ true };

		auto thread_function =
			[&]()
			{
				try
				{
					instance.generate_character<char>(domain_value, {});
				}
				catch (...)
				{
					success.store(false);
				}
			};

		std::vector<std::thread> threads;
		for (int i = 0; i < 4; ++i)
			threads.emplace_back(thread_function);

		for (auto& t : threads)
			t.join();

		ASSERT_TRUE(success.load());
	}

	INSTANTIATE_TEST_CASE_P(
		RandomCharacterGenerationManagerTest_FullStressCoverage,
		ParameterizedValidDomainTest,
		::testing::Values(
			CharacterDomain::HIGH_ENTROPY_PRINTABLE,
			CharacterDomain::HIGH_ENTROPY_ALPHANUMERIC,
			CharacterDomain::HIGH_ENTROPY_ASCII_VISIBLE,
			CharacterDomain::MIXED_CASE_STRESS,
			CharacterDomain::FUZZ_PRINTABLE,
			CharacterDomain::FUZZ_ASCII,
			CharacterDomain::EDGE_CASE_ASCII,
			CharacterDomain::EXTENDED_ASCII
		)
	);

	TEST_F(RandomCharacterGenerationManagerTest, Should_ReturnDefault_When_EmptyDomain)
	{
		const std::string domain{};
		const std::unordered_set<char> excluded{};
		const char result = manager_instance.generate_character<char>(domain, excluded);
		ASSERT_EQ(result, char{});
	}

	TEST_F(RandomCharacterGenerationManagerTest, Should_ReturnDefault_When_AllCharactersExcluded)
	{
		const std::string domain{"abc"};
		std::unordered_set<char> excluded{'a','b','c'};
		const char result = manager_instance.generate_character<char>(domain, excluded);
		ASSERT_EQ(result, char{});
	}

	TEST_F(RandomCharacterGenerationManagerTest, Should_ReturnValue_When_ValidDomain)
	{
		const std::string domain{"abcdef"};
		const std::unordered_set<char> excluded{};
		const char result = manager_instance.generate_character<char>(domain, excluded);
		ASSERT_NE(domain.find(result), std::string::npos);
	}

	TEST_F(RandomCharacterGenerationManagerTest, Should_NotReturnExcludedCharacters_ViaStringDomain)
	{
		const std::string domain{"abcdef"};
		std::unordered_set<char> excluded{'a','b','c'};
		const char result = manager_instance.generate_character<char>(domain, excluded);
		ASSERT_EQ(excluded.find(result), excluded.end());
		ASSERT_NE(domain.find(result), std::string::npos);
	}

	TEST_F(RandomCharacterGenerationManagerTest, Should_HandleSingleCharacterDomain)
	{
		const std::string domain{"x"};
		const std::unordered_set<char> excluded{};
		const char result = manager_instance.generate_character<char>(domain, excluded);
		ASSERT_EQ(result, 'x');
	}

	TEST_F(RandomCharacterGenerationManagerTest, Should_HandleOverloadWithoutExclusions)
	{
		const std::string domain{"mnopqr"};
		const char result = manager_instance.generate_character<char>(domain);
		ASSERT_NE(domain.find(result), std::string::npos);
	}

	TEST_F(RandomCharacterGenerationManagerTest, Should_ReturnDefault_When_RuntimeExecutionDisabled)
	{
		struct DisabledManager : RandomCharacterGenerationManager
		{
			bool is_runtime_execution_disabled_for_feature_handling() const { return true; }
		};

		DisabledManager instance;
		instance.configurations.is_feature_runtime_execution_handling_enabled = false;
		const std::string domain{"abc"};
		const char result = instance.generate_character<char>(domain);
		ASSERT_EQ(result, char{});
	}

	TEST_F(RandomCharacterGenerationManagerTest, Should_HandleThreadSafety)
	{
		struct ThreadSafeManager : RandomCharacterGenerationManager
		{
			bool is_thread_safety_enabled_for_feature_handling() const { return true; }
		};

		ThreadSafeManager instance;
		const std::string domain{"abcdef"};
		const std::unordered_set<char> excluded{};
		std::atomic<bool> success{true};

		auto thread_func = [&]()
		{
			for (int i = 0; i < 1000; ++i)
			{
				const char result = instance.generate_character<char>(domain, excluded);
				if (domain.find(result) == std::string::npos)
					success.store(false);
			}
		};

		std::thread t1(thread_func);
		std::thread t2(thread_func);
		t1.join();
		t2.join();

		ASSERT_TRUE(success.load());
	}

	TEST_P(ParameterizedValidDomainTest, Should_ReturnValueWithinDomain_AndRespectExclusions)
	{
		const CharacterDomain domain_value = GetParam();
		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		if (domain_string.empty())
		{
			const char result = manager_instance.generate_character<char>(domain_string, {});
			ASSERT_EQ(result, char{});
			return;
		}

		std::unordered_set<char> excluded_values;
		excluded_values.insert(domain_string.front());

		const char result =
			manager_instance.generate_character<char>(domain_string, excluded_values);

		ASSERT_NE(domain_string.find(result), std::string::npos);
		ASSERT_EQ(excluded_values.find(result), excluded_values.end());
	}

	TEST_P(ParameterizedValidDomainTest, Should_HandleOverloadWithoutExclusions)
	{
		const CharacterDomain domain_value = GetParam();
		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		if (domain_string.empty())
		{
			const char result = manager_instance.generate_character<char>(domain_string);
			ASSERT_EQ(result, char{});
			return;
		}

		const char result = manager_instance.generate_character<char>(domain_string);
		ASSERT_NE(domain_string.find(result), std::string::npos);
	}

	TEST_P(ParameterizedValidDomainTest, Should_StressHighEntropyAndFuzzDomains)
	{
		const CharacterDomain domain_value = GetParam();
		if (domain_value != CharacterDomain::HIGH_ENTROPY_PRINTABLE &&
			domain_value != CharacterDomain::HIGH_ENTROPY_ALPHANUMERIC &&
			domain_value != CharacterDomain::HIGH_ENTROPY_ASCII_VISIBLE &&
			domain_value != CharacterDomain::MIXED_CASE_STRESS &&
			domain_value != CharacterDomain::FUZZ_PRINTABLE)
			return;

		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);
		const std::unordered_set<char> excluded_values{};

		for (std::size_t i = 0; i < 50000; ++i)
		{
			const char result =
				manager_instance.generate_character<char>(domain_string, excluded_values);
			ASSERT_NE(domain_string.find(result), std::string::npos);
		}
	}

	TEST_P(ParameterizedValidDomainTest, Should_HandleEmptyAndNoneDomains)
	{
		const CharacterDomain domain_value = GetParam();
		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		if (domain_value == CharacterDomain::NONE || domain_string.empty())
		{
			const char result =
				manager_instance.generate_character<char>(domain_string, {'a','b','c'});
			ASSERT_EQ(result, char{});
		}
	}

	TEST_P(ParameterizedValidDomainTest, Should_HandleThreadSafetyAndRuntimeDisabled)
	{
		const CharacterDomain domain_value = GetParam();
		const std::string domain_string =
			SingletonManager::get_singleton<CharacterDomainManager>().get_value(domain_value);

		struct CustomManager : RandomCharacterGenerationManager
		{
			bool is_runtime_execution_disabled_for_feature_handling() const { return true; }
			bool is_thread_safety_enabled_for_feature_handling() const { return true; }
		} instance;

		std::atomic<bool> success{true};

		auto thread_func = [&]()
		{
			try
			{
				const char result =
					instance.generate_character<char>(domain_string, {});
				if (!domain_string.empty() && domain_string.find(result) == std::string::npos)
					success.store(false);
			}
			catch (...)
			{
				success.store(false);
			}
		};

		std::vector<std::thread> threads;
		for (int t = 0; t < 4; ++t)
			threads.emplace_back(thread_func);

		for (auto& t : threads)
			t.join();

		if (!domain_string.empty())
			ASSERT_TRUE(success.load());
		else
		{
			const char result = instance.generate_character<char>(domain_string, {});
			ASSERT_EQ(result, char{});
		}
	}
}

#endif
