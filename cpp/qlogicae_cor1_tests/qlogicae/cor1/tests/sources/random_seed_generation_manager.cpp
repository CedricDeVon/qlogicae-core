#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomSeedGenerationManager \
	)

#include "../includes/random_seed_generation_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(RandomSeedGenerationManagerTest,
		Should_ConstructSuccessfully_When_Default)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		bool result =
			manager_instance.construct();

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_TRUE(result);

		EXPECT_LT(
			std::chrono::duration_cast
			<std::chrono::milliseconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2000LL)
		);
	}

	TEST_F(RandomSeedGenerationManagerTest,
		Should_GenerateDeterministicSequence_When_SameSeed)
	{
		const std::uint64_t seed_value =
			static_cast<std::uint64_t>(123456789ULL);

		std::vector<std::uint64_t> values_one;
		std::vector<std::uint64_t> values_two;

		for (std::size_t index = 0U;
			index < static_cast<std::size_t>(100U);
			++index)
		{
			values_one.push_back(manager_instance.generate_deterministic_seed(seed_value));
		}

		for (std::size_t index = 0U;
			index < static_cast<std::size_t>(100U);
			++index)
		{
			values_two.push_back(manager_instance.generate_deterministic_seed(seed_value));
		}

		EXPECT_EQ(values_one, values_two);
	}

	TEST_F(RandomSeedGenerationManagerTest,
		Should_GenerateDifferentSequences_When_DifferentSeed)
	{
		std::mt19937& engine_one =
			manager_instance.random_deterministic_seed_engine;

		std::mt19937& engine_two =
			manager_instance.random_deterministic_seed_engine;

		EXPECT_NE(engine_one(), engine_two());
	}

	TEST_F(RandomSeedGenerationManagerTest,
		Should_GenerateIndeterministicSequence_When_Called)
	{
		std::mt19937& engine =
			manager_instance.random_indeterministic_seed_engine;

		std::uint32_t value_one = engine();
		std::uint32_t value_two = engine();

		EXPECT_NE(value_one, value_two);
	}

	TEST_F(RandomSeedGenerationManagerTest,
		Should_MixSplit64Correctly_When_MaximumValue)
	{
		const std::uint64_t maximum_value =
			std::numeric_limits<std::uint64_t>::max();

		std::uint64_t result =
			manager_instance.mix_split_64(
				maximum_value
			);

		EXPECT_NE(result, maximum_value);
	}

	TEST_F(RandomSeedGenerationManagerTest,
		Should_MixEntropy_When_CalledMultipleTimes)
	{
		std::uint64_t first =
			manager_instance.mix_entropy();

		std::uint64_t second =
			manager_instance.mix_entropy();

		EXPECT_NE(first, second);
	}

	TEST_F(RandomSeedGenerationManagerTest,
		Should_HandleZeroSeed_When_Deterministic)
	{
		std::mt19937& engine =
			manager_instance.random_deterministic_seed_engine;

		std::uint32_t value = engine();

		EXPECT_NE(value, static_cast<std::uint32_t>(0U));
	}

	TEST_F(RandomSeedGenerationManagerTest,
		Should_HandleHighLoad_When_StressTested)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		std::atomic<std::uint64_t> aggregate_sum =
			static_cast<std::uint64_t>(0ULL);

		std::vector<std::thread> worker_threads;

		for (std::size_t index = 0U;
			index < THREAD_COUNT;
			++index)
		{
			worker_threads.emplace_back(
				[this, &aggregate_sum]()
				{
					std::mt19937& engine =
						manager_instance
						.random_indeterministic_seed_engine;

					for (std::size_t iteration = 0U;
						iteration < ITERATION_COUNT;
						++iteration)
					{
						aggregate_sum.fetch_add(
							static_cast
							<std::uint64_t>(
								engine()
							),
							std::memory_order_relaxed
						);
					}
				}
			);
		}

		for (std::thread& thread_instance :
			worker_threads)
		{
			thread_instance.join();
		}

		EXPECT_GT(aggregate_sum.load(),
			static_cast<std::uint64_t>(0ULL));

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast
			<std::chrono::milliseconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2000LL)
		);
	}

	TEST_F(RandomSeedGenerationManagerTest,
		Should_SynchronizeThreads_When_UsingConditionVariable)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		std::mutex condition_mutex;
		std::condition_variable condition_variable_instance;
		bool ready_flag = false;
		std::uint32_t generated_value =
			static_cast<std::uint32_t>(0U);

		std::thread worker_thread(
			[this,
			 &condition_mutex,
			 &condition_variable_instance,
			 &ready_flag,
			 &generated_value]()
			{
				std::unique_lock<std::mutex>
					lock(condition_mutex);

				condition_variable_instance.wait(
					lock,
					[&ready_flag]()
					{
						return ready_flag;
					}
				);

				std::mt19937& engine =
					manager_instance
					.random_indeterministic_seed_engine;

				generated_value = engine();
			}
		);

		{
			std::lock_guard<std::mutex>
				lock(condition_mutex);

			ready_flag = true;
		}

		condition_variable_instance.notify_one();

		worker_thread.join();

		EXPECT_NE(generated_value,
			static_cast<std::uint32_t>(0U));

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast
			<std::chrono::milliseconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2000LL)
		);
	}

	TEST_F(RandomSeedGenerationManagerTest,
		Should_GenerateValue_When_AsyncLaunch)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		std::future<std::uint32_t> future_value =
			std::async(
				std::launch::async,
				[this]()
				{
					std::mt19937& engine =
						manager_instance
						.random_indeterministic_seed_engine;
					return engine();
				}
			);

		std::uint32_t result =
			future_value.get();

		EXPECT_NE(result,
			static_cast<std::uint32_t>(0U));

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast
			<std::chrono::milliseconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2000LL)
		);
	}

	TEST_F(RandomSeedGenerationManagerTest,
		Should_SynchronizeWithPromise_When_Async)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		std::promise<std::uint32_t> promise_value;
		std::future<std::uint32_t> future_value =
			promise_value.get_future();

		std::thread worker_thread(
			[this, &promise_value]()
			{
				std::mt19937& engine =
					manager_instance
					.random_indeterministic_seed_engine;

				promise_value.set_value(
					engine()
				);
			}
		);

		std::uint32_t result =
			future_value.get();

		worker_thread.join();

		EXPECT_NE(result,
			static_cast<std::uint32_t>(0U));

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast
			<std::chrono::milliseconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2000LL)
		);
	}

	TEST_P(RandomSeedGenerationManagerParameterizedTest,
		Should_GenerateStableSequence_When_ParameterizedSeed)
	{
		const std::uint64_t seed_value =
			GetParam();

		std::mt19937& engine =
			manager_instance.random_deterministic_seed_engine;

		std::uint32_t first_value = engine();
		std::uint32_t second_value = engine();

		EXPECT_NE(first_value,
			second_value);
	}

	INSTANTIATE_TEST_CASE_P(
		DeterministicSeeds,
		RandomSeedGenerationManagerParameterizedTest,
		::testing::Values(
			static_cast<std::uint64_t>(1ULL),
			static_cast<std::uint64_t>(2ULL),
			static_cast<std::uint64_t>(42ULL),
			static_cast<std::uint64_t>(
				std::numeric_limits
				<std::uint64_t>::max()
			)
		)
	);

	TEST_P(RandomSeedGenerationManagerEmptySeedTest,
		Should_HandleZeroSeed_When_EmptyEquivalent)
	{
		std::mt19937& engine =
			manager_instance.random_deterministic_seed_engine;

		EXPECT_NE(engine(),
			static_cast<std::uint32_t>(0U));
	}

	INSTANTIATE_TEST_CASE_P(
		ZeroSeedCase,
		RandomSeedGenerationManagerEmptySeedTest,
		::testing::Values(
			static_cast<int>(0)
		)
	);

	TEST_F(RandomSeedGenerationManagerTest,
		Should_NotThrow_When_StressAsync)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		std::vector<std::future<void>> futures;

		for (std::size_t index = 0U;
			index < THREAD_COUNT;
			++index)
		{
			futures.emplace_back(
				std::async(
					std::launch::async,
					[this]()
					{
						for (std::uint64_t iteration =
							static_cast
							<std::uint64_t>(0ULL);
							iteration <
							MAX_ITERATIONS;
							++iteration)
						{
							std::mt19937& engine =
								manager_instance
								.random_indeterministic_seed_engine;

							volatile std::uint32_t value =
								engine();
							static_cast<void>(value);
						}
					}
				)
			);
		}

		for (auto& future_instance :
			futures)
		{
			future_instance.get();
		}

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast
			<std::chrono::milliseconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2000LL)
		);
	}

	TEST_F(RandomSeedGenerationManagerTest,
		Should_HandleExceptionSafety_When_NoThrowPaths)
	{
		EXPECT_NO_THROW(
			{
				std::mt19937 & engine =
					manager_instance
					.random_indeterministic_seed_engine;

			std::uint32_t value =
				engine();

			static_cast<void>(value);
		});
	}
	
	TEST_F(RandomSeedGenerationManagerTest,
	Should_ReturnTrue_When_ConstructCalledMultipleTimes)
	{
		bool first_result = this->manager_instance.construct();
		bool second_result = this->manager_instance.construct();

		EXPECT_TRUE(first_result);
		EXPECT_TRUE(second_result);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_ReturnTrue_When_DestructCalledWithoutConstruct)
	{
		bool destruct_result = this->manager_instance.destruct();
		EXPECT_TRUE(destruct_result);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_ReturnTrue_When_ConstructAndDestructRepeated)
	{
		for (std::size_t iteration_index = 0U;
			 iteration_index < THREAD_COUNT;
			 ++iteration_index)
		{
			bool construct_result = this->manager_instance.construct();
			bool destruct_result = this->manager_instance.destruct();
			EXPECT_TRUE(construct_result);
			EXPECT_TRUE(destruct_result);
		}
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_GenerateNonZero_When_CryptographySeedRequested)
	{
		std::uint64_t seed_value =
			this->manager_instance.generate_cryptography_seed();
		EXPECT_NE(seed_value, static_cast<std::uint64_t>(0ULL));
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_CompleteUnderTwoSeconds_When_CryptographyStressTested)
	{
		auto start_time = std::chrono::steady_clock::now();

		for (std::uint64_t iteration_index = 0ULL;
			 iteration_index < MAX_ITERATIONS;
			 ++iteration_index)
		{
			std::uint64_t value =
				this->manager_instance.generate_cryptography_seed();
			EXPECT_NE(value, static_cast<std::uint64_t>(0ULL));
		}

		auto end_time = std::chrono::steady_clock::now();
		auto duration =
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time);

		EXPECT_LT(duration.count(), static_cast<long>(2));
	}

	TEST_P(SplitMix64ParameterizedTest,
	Should_ReturnDeterministicValue_When_SameInputProvided)
	{
		std::uint64_t input_value = GetParam();

		std::uint64_t first_result =
			this->manager_instance.mix_split_64(input_value);

		std::uint64_t second_result =
			this->manager_instance.mix_split_64(input_value);

		EXPECT_EQ(first_result, second_result);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_ReturnNonZero_When_SplitMix64StressTested)
	{
		auto start_time = std::chrono::steady_clock::now();

		for (std::uint64_t iteration_index = 0ULL;
			 iteration_index < MAX_ITERATIONS;
			 ++iteration_index)
		{
			std::uint64_t result =
				this->manager_instance.mix_split_64(iteration_index);
			EXPECT_NE(result, static_cast<std::uint64_t>(0ULL));
		}

		auto end_time = std::chrono::steady_clock::now();
		auto duration =
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time);

		EXPECT_LT(duration.count(), static_cast<long>(2));
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_GenerateDifferentEntropy_When_Multithreaded)
	{
		std::vector<std::uint64_t> entropy_values(THREAD_COUNT);
		std::vector<std::thread> thread_pool;

		for (std::size_t thread_index = 0U;
			 thread_index < THREAD_COUNT;
			 ++thread_index)
		{
			thread_pool.emplace_back(
				[this, thread_index, &entropy_values]()
				{
					entropy_values[thread_index] =
						this->manager_instance.mix_entropy();
				});
		}

		for (std::thread& worker_thread : thread_pool)
		{
			worker_thread.join();
		}

		for (std::size_t index = 1U;
			 index < THREAD_COUNT;
			 ++index)
		{
			EXPECT_NE(entropy_values[0U], entropy_values[index]);
		}
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_CompleteUnderTwoSeconds_When_EntropyStressTested)
	{
		auto start_time = std::chrono::steady_clock::now();

		for (std::uint64_t iteration_index = 0ULL;
			 iteration_index < MAX_ITERATIONS;
			 ++iteration_index)
		{
			std::uint64_t value =
				this->manager_instance.mix_entropy();
			EXPECT_NE(value, static_cast<std::uint64_t>(0ULL));
		}

		auto end_time = std::chrono::steady_clock::now();
		auto duration =
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time);

		EXPECT_LT(duration.count(), static_cast<long>(2));
	}

	TEST_P(DeterministicSeedParameterizedTest,
	Should_GenerateIdenticalSequence_When_SameSeedProvided)
	{
		std::uint64_t seed_value = GetParam();

		this->manager_instance.generate_deterministic_seed(seed_value);

		std::uint64_t first_value =
			this->manager_instance.generate_deterministic_seed(seed_value);

		this->manager_instance.generate_deterministic_seed(seed_value);

		std::uint64_t second_value =
			this->manager_instance.generate_deterministic_seed(seed_value);

		EXPECT_EQ(first_value, second_value);
	}

	INSTANTIATE_TEST_CASE_P(
		SplitMix64Inputs,
		SplitMix64ParameterizedTest,
		::testing::Values(
			static_cast<std::uint64_t>(0ULL),
			static_cast<std::uint64_t>(1ULL),
			std::numeric_limits<std::uint64_t>::max()
		)
	);

	INSTANTIATE_TEST_CASE_P(
		DeterministicSeedInputs,
		DeterministicSeedParameterizedTest,
		::testing::Values(
			static_cast<std::uint64_t>(0ULL),
			static_cast<std::uint64_t>(1ULL),
			static_cast<std::uint64_t>(123456789ULL),
			std::numeric_limits<std::uint64_t>::max()
		)
	);

	TEST_F(RandomSeedGenerationManagerTest,
	Should_ReconstructSuccessfully_When_ConstructAfterDestruct)
	{
		bool first_construct =
			manager_instance.construct();
		bool first_destruct =
			manager_instance.destruct();
		bool second_construct =
			manager_instance.construct();

		EXPECT_TRUE(first_construct);
		EXPECT_TRUE(first_destruct);
		EXPECT_TRUE(second_construct);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_GenerateAfterDestruct_When_Reconstructed)
	{
		manager_instance.construct();
		manager_instance.destruct();
		manager_instance.construct();

		std::mt19937& engine =
			manager_instance.random_indeterministic_seed_engine;

		std::uint32_t value = engine();

		EXPECT_NE(value,
			static_cast<std::uint32_t>(0U));
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_IsolateAcrossInstances_When_MultiInstance)
	{
		RandomSeedGenerationManager second_instance;

		std::mt19937& engine_one =
			manager_instance.random_indeterministic_seed_engine;

		std::mt19937& engine_two =
			second_instance.random_indeterministic_seed_engine;

		EXPECT_NE(engine_one(), engine_two());
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_HandleDeterministicStress_When_HighIteration)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		manager_instance.generate_deterministic_seed(
			static_cast<std::uint64_t>(99ULL));

		for (std::uint64_t iteration = 0ULL;
			iteration < MAX_ITERATIONS;
			++iteration)
		{
			std::uint64_t value =
				manager_instance
				.generate_deterministic_seed(10U);

			EXPECT_NE(value,
				static_cast<std::uint64_t>(0ULL));
		}

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast
			<std::chrono::milliseconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2000LL)
		);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_StressConstructDestruct_When_Repeated)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		for (std::size_t index = 0U;
			index < THREAD_COUNT * 10U;
			++index)
		{
			bool construct_result =
				manager_instance.construct();
			bool destruct_result =
				manager_instance.destruct();

			EXPECT_TRUE(construct_result);
			EXPECT_TRUE(destruct_result);
		}

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast
			<std::chrono::milliseconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2000LL)
		);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_GenerateEntropyAsync_When_ConcurrentFutures)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		std::vector<std::future<std::uint64_t>> futures;

		for (std::size_t index = 0U;
			index < THREAD_COUNT;
			++index)
		{
			futures.emplace_back(
				std::async(
					std::launch::async,
					[this]()
					{
						return manager_instance
							.mix_entropy();
					}
				)
			);
		}

		for (auto& future_instance :
			futures)
		{
			std::uint64_t value =
				future_instance.get();

			EXPECT_NE(value,
				static_cast<std::uint64_t>(0ULL));
		}

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast
			<std::chrono::milliseconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2000LL)
		);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_GenerateSplitMixAsync_When_Concurrent)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		std::vector<std::future<std::uint64_t>> futures;

		for (std::size_t index = 0U;
			index < THREAD_COUNT;
			++index)
		{
			futures.emplace_back(
				std::async(
					std::launch::async,
					[this, index]()
					{
						return manager_instance
							.mix_split_64(
								static_cast
								<std::uint64_t>(index)
							);
					}
				)
			);
		}

		for (auto& future_instance :
			futures)
		{
			std::uint64_t value =
				future_instance.get();

			EXPECT_NE(value,
				static_cast<std::uint64_t>(0ULL));
		}

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast
			<std::chrono::milliseconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2000LL)
		);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_HandleGenerateBeforeConstruct_When_DefaultState)
	{
		std::mt19937& engine =
			manager_instance.random_indeterministic_seed_engine;

		std::uint32_t value =
			engine();

		EXPECT_NE(value,
			static_cast<std::uint32_t>(0U));
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_NotThrow_When_ConstructDestructAsync)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		std::future<void> future_instance =
			std::async(
				std::launch::async,
				[this]()
				{
					for (std::size_t index = 0U;
						index < THREAD_COUNT;
						++index)
					{
						manager_instance.construct();
						manager_instance.destruct();
					}
				}
			);

		EXPECT_NO_THROW(
			future_instance.get();
		);

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast
			<std::chrono::milliseconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2000LL)
		);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_HandleMultipleDestructCalls_When_CalledRepeatedly)
	{
		manager_instance.construct();
		EXPECT_TRUE(manager_instance.destruct());
		EXPECT_TRUE(manager_instance.destruct());
		EXPECT_TRUE(manager_instance.destruct());
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_GenerateDistinctDeterministicEngines_When_DifferentSeeds)
	{
		std::mt19937& engine_one =
			manager_instance.random_deterministic_seed_engine;
		std::mt19937& engine_two =
			manager_instance.random_deterministic_seed_engine;
		EXPECT_NE(engine_one(), engine_two());
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_ProduceConsistentDeterministicSequence_When_ReSeeded)
	{
		manager_instance.generate_deterministic_seed(789ULL);
		std::vector<std::uint64_t> first_seq;
		for (std::size_t i = 0; i < 50; ++i)
			first_seq.push_back(manager_instance.generate_deterministic_seed(789ULL));
		manager_instance.generate_deterministic_seed(789ULL);
		std::vector<std::uint64_t> second_seq;
		for (std::size_t i = 0; i < 50; ++i)
			second_seq.push_back(manager_instance.generate_deterministic_seed(789ULL));
		EXPECT_EQ(first_seq, second_seq);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_NotReturnZero_When_MixSplit64CalledRepeatedly)
	{
		for (std::uint64_t i = 0; i < 10000; ++i)
			EXPECT_NE(manager_instance.mix_split_64(i), 0ULL);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_GenerateNonZeroCryptographySeed_When_CalledRepeatedly)
	{
		for (std::size_t i = 0; i < 1000; ++i)
			EXPECT_NE(manager_instance.generate_cryptography_seed(), 0ULL);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_GenerateUniqueCryptographySeeds_When_MultiThreaded)
	{
		std::vector<std::uint64_t> seeds(THREAD_COUNT);
		std::vector<std::thread> threads;
		for (std::size_t i = 0; i < THREAD_COUNT; ++i)
		{
			threads.emplace_back([this, i, &seeds]()
			{
				seeds[i] = manager_instance.generate_cryptography_seed();
			});
		}
		for (auto& t : threads) t.join();
		for (std::size_t i = 1; i < THREAD_COUNT; ++i)
			EXPECT_NE(seeds[0], seeds[i]);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_CompleteUnderTwoSeconds_When_CryptographyHighLoad)
	{
		auto start_time = std::chrono::steady_clock::now();
		for (std::uint64_t i = 0; i < 100000; ++i)
			EXPECT_NE(manager_instance.generate_cryptography_seed(), 0ULL);
		auto end_time = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
		EXPECT_LT(duration.count(), 2);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_GenerateDifferentEntropyValues_When_Concurrent)
	{
		std::vector<std::uint64_t> entropy_values(THREAD_COUNT);
		std::vector<std::thread> threads;
		for (std::size_t i = 0; i < THREAD_COUNT; ++i)
		{
			threads.emplace_back([this, i, &entropy_values]()
			{
				entropy_values[i] = manager_instance.mix_entropy();
			});
		}
		for (auto& t : threads) t.join();
		for (std::size_t i = 1; i < THREAD_COUNT; ++i)
			EXPECT_NE(entropy_values[0], entropy_values[i]);
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_NotThrow_When_ConstructDestructConcurrent)
	{
		std::vector<std::future<void>> futures;
		for (std::size_t i = 0; i < THREAD_COUNT; ++i)
		{
			futures.push_back(std::async(std::launch::async, [this]()
			{
				manager_instance.construct();
				manager_instance.destruct();
			}));
		}
		for (auto& f : futures)
			EXPECT_NO_THROW(f.get());
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_GenerateDistinctSplitMixValues_When_DifferentInputs)
	{
		std::uint64_t prev = 0;
		for (std::uint64_t i = 0; i < 1000; ++i)
		{
			std::uint64_t value = manager_instance.mix_split_64(i);
			if (i > 0) EXPECT_NE(value, prev);
			prev = value;
		}
	}

	TEST_F(RandomSeedGenerationManagerTest,
	Should_HandleReconstructAfterStressDestruct)
	{
		for (std::size_t i = 0; i < THREAD_COUNT * 5; ++i)
		{
			EXPECT_TRUE(manager_instance.construct());
			EXPECT_TRUE(manager_instance.destruct());
		}
		EXPECT_TRUE(manager_instance.construct());
		std::mt19937& engine = manager_instance.random_indeterministic_seed_engine;
		EXPECT_NE(engine(), 0U);
	}

	TEST_F(RandomSeedGenerationManagerTest, Should_SetupIndeterministicSeed)
	{
		EXPECT_TRUE(manager_instance.setup_indeterministic_seed());
		std::uint64_t first_value = manager_instance.generate_indeterministic_seed();
		std::uint64_t second_value = manager_instance.generate_indeterministic_seed();
		EXPECT_NE(first_value, second_value);
	}

	TEST_F(RandomSeedGenerationManagerTest, Should_SetupDeterministicSeed_WithGivenValue)
	{
		std::uint64_t seed = 123456789ULL;
		EXPECT_TRUE(manager_instance.setup_deterministic_seed(seed));
		std::mt19937 engine_copy;
		engine_copy.seed(static_cast<unsigned int>(manager_instance.mix_split_64(seed)));
		EXPECT_EQ(manager_instance.generate_deterministic_seed(seed), engine_copy());
	}

	TEST_F(RandomSeedGenerationManagerTest, Should_SetupCryptographySeed)
	{
		EXPECT_TRUE(manager_instance.setup_cryptography_seed());
		std::uint64_t value1 = manager_instance.generate_cryptography_seed();
		std::uint64_t value2 = manager_instance.generate_cryptography_seed();
		EXPECT_NE(value1, value2);
	}

	TEST_F(RandomSeedGenerationManagerTest, DeterministicSeed_ShouldProduceSameValueOnReset)
	{
		std::uint64_t seed = 987654321ULL;
		manager_instance.setup_deterministic_seed(seed);
		std::uint64_t first = manager_instance.generate_deterministic_seed(seed);
		manager_instance.setup_deterministic_seed(seed);
		std::uint64_t second = manager_instance.generate_deterministic_seed(seed);
		EXPECT_EQ(first, second);
	}

	TEST_F(RandomSeedGenerationManagerTest, IndeterministicSeed_ShouldProduceDifferentValues)
	{
		manager_instance.setup_indeterministic_seed();
		std::uint64_t first = manager_instance.generate_indeterministic_seed();
		std::uint64_t second = manager_instance.generate_indeterministic_seed();
		EXPECT_NE(first, second);
	}

	TEST_F(RandomSeedGenerationManagerTest, CryptographySeed_ShouldProduceDifferentValues)
	{
		manager_instance.setup_cryptography_seed();
		std::uint64_t first = manager_instance.generate_cryptography_seed();
		std::uint64_t second = manager_instance.generate_cryptography_seed();
		EXPECT_NE(first, second);
	}
}

#endif
