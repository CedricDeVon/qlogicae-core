#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomEnumGenerationManager \
	)

#include "../includes/random_enum_generation_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	TEST_F(RandomEnumGenerationManagerTest,
		Should_GenerateEnumWithinBounds_When_NoExclusion)
	{
		TestEnum result =
			manager.generate_enum<TestEnum>(
				TestEnum::ALPHA,
				TestEnum::DELTA
			);

		EXPECT_GE(
			static_cast<std::underlying_type_t<TestEnum>>(result),
			static_cast<std::underlying_type_t<TestEnum>>(
				TestEnum::ALPHA
			)
		);

		EXPECT_LE(
			static_cast<std::underlying_type_t<TestEnum>>(result),
			static_cast<std::underlying_type_t<TestEnum>>(
				TestEnum::DELTA
			)
		);

		EXPECT_NE(result, TestEnum::NONE);
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_ReturnNone_When_AllValuesExcluded)
	{
		std::unordered_set<TestEnum> excluded =
		{
			TestEnum::ALPHA,
			TestEnum::BETA,
			TestEnum::GAMMA,
			TestEnum::DELTA
		};

		TestEnum result =
			manager.generate_enum<TestEnum>(
				TestEnum::ALPHA,
				TestEnum::DELTA,
				excluded
			);

		EXPECT_EQ(result, TestEnum::NONE);
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_HandleEmptyExclusionSet_When_Provided)
	{
		std::unordered_set<TestEnum> excluded;

		TestEnum result =
			manager.generate_enum<TestEnum>(
				TestEnum::ALPHA,
				TestEnum::DELTA,
				excluded
			);

		EXPECT_NE(result, TestEnum::NONE);
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_HandleMaximumOnly_When_MinNotSpecified)
	{
		TestEnum result =
			manager.generate_enum<TestEnum>(
				TestEnum::DELTA
			);

		EXPECT_GE(
			static_cast<std::underlying_type_t<TestEnum>>(result),
			static_cast<std::underlying_type_t<TestEnum>>(0)
		);

		EXPECT_LE(
			static_cast<std::underlying_type_t<TestEnum>>(result),
			static_cast<std::underlying_type_t<TestEnum>>(
				TestEnum::DELTA
			)
		);
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_HandleExcludedOnly_When_MinMaxNotSpecified)
	{
		std::unordered_set<TestEnum> excluded =
		{
			TestEnum::ALPHA,
			TestEnum::BETA
		};

		TestEnum result =
			manager.generate_enum<TestEnum>(
				excluded
			);

		EXPECT_NE(result, TestEnum::ALPHA);
		EXPECT_NE(result, TestEnum::BETA);
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_HandleAllValues_When_NoArguments)
	{
		TestEnum result = manager.generate_enum<TestEnum>();
		EXPECT_GE(
			static_cast<std::underlying_type_t<TestEnum>>(result),
			static_cast<std::underlying_type_t<TestEnum>>(0)
		);

		EXPECT_LE(
			static_cast<std::underlying_type_t<TestEnum>>(result),
			static_cast<std::underlying_type_t<TestEnum>>(TestEnum::NONE)
		);
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_BeThreadSafe_When_MultipleThreadsAccess)
	{
		std::vector<std::thread> threads;
		std::atomic<int> counter{ 0 };

		for (int i = 0; i < 16; ++i)
		{
			threads.emplace_back([&]()
				{
					TestEnum result =
						manager.generate_enum<TestEnum>(TestEnum::ALPHA, TestEnum::DELTA);
					if (result != TestEnum::NONE)
					{
						counter.fetch_add(1, std::memory_order_relaxed);
					}
					EXPECT_NE(result, TestEnum::NONE);
				});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		EXPECT_EQ(counter.load(std::memory_order_relaxed), 16);
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_BeExceptionSafe_When_InvalidCastOccurs)
	{
		try
		{
			TestEnum result =
				manager.generate_enum<TestEnum>(
					static_cast<TestEnum>(1000),
					static_cast<TestEnum>(1001)
				);
			(void)result;
		}
		catch (...)
		{
			FAIL();
		}
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_HandleHighLoad_When_StressTested)
	{
		for (int i = 0; i < 10000; ++i)
		{
			TestEnum result = manager.generate_enum<TestEnum>();
			EXPECT_GE(
				static_cast<std::underlying_type_t<TestEnum>>(result),
				0
			);
		}
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_GenerateEnumAsync_When_UsingFuture)
	{
		std::future<TestEnum> future_result =
			std::async(
				std::launch::async,
				[&]()
				{
					return manager.generate_enum<TestEnum>();
				}
			);

		TestEnum result = future_result.get();
		EXPECT_GE(
			static_cast<std::underlying_type_t<TestEnum>>(result),
			0
		);
	}

	INSTANTIATE_TEST_CASE_P(
		RandomEnumGenerationManagerParameterizedTestInstances,
		RandomEnumGenerationManagerParameterizedTest,
		::testing::Values(
			RandomEnumGenerationManagerTestParam
			{
				TestEnum::ALPHA,
				TestEnum::DELTA,
				{},
				TestEnum::ALPHA
			},
			RandomEnumGenerationManagerTestParam
			{
				TestEnum::ALPHA,
				TestEnum::DELTA,
				{TestEnum::BETA, TestEnum::GAMMA},
				TestEnum::ALPHA
			},
			RandomEnumGenerationManagerTestParam
			{
				TestEnum::ALPHA,
				TestEnum::ALPHA,
				{},
				TestEnum::ALPHA
			}
		)
	);

	TEST_P(RandomEnumGenerationManagerParameterizedTest,
		Should_GenerateExpectedEnum_When_UsingParameters)
	{
		RandomEnumGenerationManagerTestParam param =
			GetParam();

		TestEnum result =
			manager.generate_enum<TestEnum>(
				param.minimum,
				param.maximum,
				param.excluded
			);

		EXPECT_NE(result, TestEnum::NONE);
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_HandleFullExclusion_When_NoAvailableValue)
	{
		std::unordered_set<TestEnum> excluded = {
			TestEnum::ALPHA, TestEnum::BETA, TestEnum::GAMMA, TestEnum::DELTA
		};

		TestEnum result =
			manager.generate_enum<TestEnum>(TestEnum::DELTA, excluded);

		EXPECT_EQ(result, TestEnum::NONE);
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_HandleMinEqualsMax_When_SingleValue)
	{
		TestEnum result =
			manager.generate_enum<TestEnum>(TestEnum::BETA, TestEnum::BETA);
		EXPECT_EQ(result, TestEnum::BETA);
	}

	INSTANTIATE_TEST_CASE_P(
		RandomEnumGenerationManagerParameterizedTests,
		RandomEnumGenerationManagerParameterizedTest,
		::testing::Values(
			RandomEnumGenerationManagerTestParam{ TestEnum::ALPHA, TestEnum::DELTA, {}, TestEnum::ALPHA },
			RandomEnumGenerationManagerTestParam{ TestEnum::BETA, TestEnum::GAMMA, {}, TestEnum::BETA }
		)
	);

	TEST_P(RandomEnumGenerationManagerParameterizedTest,
		Should_ReturnExpectedEnum_When_Parameterized)
	{
		RandomEnumGenerationManagerTestParam param = GetParam();
		TestEnum result =
			manager.generate_enum<TestEnum>(
				param.minimum, param.maximum, param.excluded
			);
		EXPECT_EQ(result, param.expected);
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_HandlePromiseAsync_When_FutureUsedWithPromise)
	{
		std::promise<TestEnum> promise;
		std::future<TestEnum> future_result = promise.get_future();

		std::thread worker([&]()
		{
			TestEnum result =
				manager.generate_enum<TestEnum>(TestEnum::ALPHA,
					TestEnum::DELTA);
			promise.set_value(result);
		});

		TestEnum result = future_result.get();
		EXPECT_GE(
			static_cast<std::underlying_type_t<TestEnum>>(result),
			static_cast<std::underlying_type_t<TestEnum>>(TestEnum::ALPHA)
		);
		EXPECT_LE(
			static_cast<std::underlying_type_t<TestEnum>>(result),
			static_cast<std::underlying_type_t<TestEnum>>(TestEnum::DELTA)
		);

		worker.join();
	}

	TEST_F(RandomEnumGenerationManagerTest,
		Should_HandleHighConcurrencyStress_When_MultipleThreadsGenerateEnum)
	{
		constexpr std::size_t thread_count = 10;
		constexpr std::size_t iteration_count = 10000;
		std::atomic<bool> success = true;

		auto thread_worker = [&]()
		{
			for (std::size_t i = 0; i < iteration_count; i++)
			{
				TestEnum result =
					manager.generate_enum<TestEnum>(TestEnum::ALPHA,
						TestEnum::DELTA);
				if (result == TestEnum::NONE)
				{
					success = false;
				}
			}
		};

		std::vector<std::thread> threads;
		for (std::size_t i = 0; i < thread_count; i++)
		{
			threads.emplace_back(thread_worker);
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		EXPECT_TRUE(success);
	}

	TEST_F(RandomEnumGenerationManagerErrorInjectionTest,
		Should_HandleErrorManagerException_When_GenerateEnumFails)
	{
		TestEnum result;
		EXPECT_NO_THROW(
			result = manager_with_mock.generate_enum<TestEnum>(
				static_cast<TestEnum>(100000),
				static_cast<TestEnum>(200000)
			)
		);
		EXPECT_TRUE(
			result == TestEnum::NONE ||
			static_cast<std::underlying_type_t<TestEnum>>(result) >= 100000
		);
	}
}

#endif
