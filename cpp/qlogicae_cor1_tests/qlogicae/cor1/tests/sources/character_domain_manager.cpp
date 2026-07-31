#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CharacterDomainManager \
	)

#include "../includes/character_domain_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(CharacterDomainManagerTest, Should_ConstructSuccessfully_When_RuntimeEnabled)
	{
		ASSERT_TRUE(manager.construct());
	}

	TEST_F(CharacterDomainManagerTest, Should_DestructSuccessfully_When_RuntimeEnabled)
	{
		ASSERT_TRUE(manager.destruct());
	}

	TEST_F(CharacterDomainManagerTest, Should_ReturnDefaultTypeValue_When_NoArgument)
	{
		manager.configurations.type = CharacterDomain::NUMERIC;
		ASSERT_EQ(manager.get_value(), "0123456789");
	}

	TEST_P(CharacterDomainManagerParameterizedTest,
		Should_ReturnCorrectValue_When_CharacterDomainSpecified)
	{
		const CharacterDomainParam& param = GetParam();
		ASSERT_EQ(manager.get_value(param.domain), param.expected_string);
	}

	TEST_F(CharacterDomainManagerTest,
		Should_HandleCustomDomainAndNone_When_CharacterDomainIsCustomOrNone)
	{
		ASSERT_EQ(manager.get_value(CharacterDomain::CUSTOM), "");
		ASSERT_EQ(manager.get_value(CharacterDomain::NONE), "");
	}

	TEST_F(CharacterDomainManagerTest,
		Should_HandleMultithreadedAccess_When_ConcurrentThreadsCallGetValue)
	{
		std::vector<std::thread> threads;
		std::vector<std::string> results(10);
		for (size_t i = 0; i < 10; ++i)
		{
			threads.emplace_back([&, i]()
				{
					results[i] = manager.get_value(CharacterDomain::ALPHANUMERIC);
				});
		}
		for (auto& thread : threads) thread.join();
		for (auto& result : results)
		{
			ASSERT_EQ(result, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
		}
	}

	TEST_F(CharacterDomainManagerTest,
		Should_HandleAsyncAccess_When_UsingFutures)
	{
		std::vector<std::future<std::string>> futures;
		for (size_t i = 0; i < 10; ++i)
		{
			futures.emplace_back(std::async(std::launch::async,
				[this]()
				{
					return manager.get_value(CharacterDomain::HEX_UPPERCASE);
				}));
		}
		for (auto& future : futures)
		{
			ASSERT_EQ(future.get(), "0123456789ABCDEF");
		}
	}

	TEST_F(CharacterDomainManagerTest,
		Should_HandleStress_When_CallingGetValueManyTimes)
	{
		auto start_time = std::chrono::steady_clock::now();
		for (size_t i = 0; i < 100000; ++i)
		{
			ASSERT_EQ(manager.get_value(CharacterDomain::NUMERIC), "0123456789");
		}
		auto end_time = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
		ASSERT_LT(duration.count(), 2);
	}

	TEST_F(CharacterDomainManagerTest,
		Should_CatchExceptions_When_HandleErrorOutputsThrows)
	{
		ASSERT_NO_THROW(manager.get_value(CharacterDomain::NUMERIC));
	}
	
	INSTANTIATE_TEST_CASE_P(
		CharacterDomainTests,
		CharacterDomainManagerParameterizedTest,
		::testing::ValuesIn(character_domain_params));
}

#endif
