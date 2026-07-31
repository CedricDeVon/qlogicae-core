#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomNumberGenerationManager \
	)

#include "../includes/random_number_generation_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(RandomNumberGenerationManagerTest,
		Should_GenerateIntegerWithinRange_When_MinMaxProvided)
	{
		const int minimum = 1;
		const int maximum = 10;

		const int generated_number =
			manager_instance.generate_number<int>(minimum, maximum);

		EXPECT_GE(generated_number, minimum);
		EXPECT_LE(generated_number, maximum);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_GenerateFloatWithinRange_When_MinMaxProvided)
	{
		const double minimum = 1.5;
		const double maximum = 10.5;

		const double generated_number =
			manager_instance.generate_number<double>(minimum, maximum);

		EXPECT_GE(generated_number, minimum);
		EXPECT_LE(generated_number, maximum);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_GenerateIntegerExcludingValues_When_ExcludedProvided)
	{
		const int minimum = 1;
		const int maximum = 5;
		std::unordered_set<int> excluded{2, 4};

		const int generated_number =
			manager_instance.generate_number<int>(
				minimum, maximum, excluded);

		EXPECT_GE(generated_number, minimum);
		EXPECT_LE(generated_number, maximum);
		EXPECT_TRUE(excluded.find(generated_number) == excluded.end());
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_GenerateIntegerFromIncluded_When_IncludedProvided)
	{
		std::unordered_set<int> included{3, 5, 7};

		const int generated_number =
			manager_instance.generate_number<int>(included);

		EXPECT_TRUE(included.find(generated_number) != included.end());
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_ReturnMinimum_When_MinGreaterThanMax)
	{
		const int minimum = 10;
		const int maximum = 1;

		const int generated_number =
			manager_instance.generate_number<int>(minimum, maximum);

		EXPECT_EQ(generated_number, minimum);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleEmptyIncludedSet_When_GenerateNumberCalled)
	{
		std::unordered_set<int> included;

		const int generated_number =
			manager_instance.generate_number<int>(included);

		EXPECT_EQ(generated_number, int{});
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleExceptionsAndReturnDefault_When_ErrorThrown)
	{
		struct ExceptionConfigurations :
			RandomNumberGenerationManagerConfigurations
		{
			ExceptionConfigurations()
			{
				is_runtime_execution_handling_enabled = false;
			}
		};

		RandomNumberGenerationManager local_manager;

		const int generated_number =
			local_manager.generate_number<int>(1, 10);

		EXPECT_NE(generated_number, int{});
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleMultithreadedGeneration_When_CalledConcurrently)
	{
		const int iterations = 1000;
		std::vector<int> results;
		std::mutex results_mutex;

		auto thread_function = [&]()
		{
			for (int i = 0; i < 100; ++i)
			{
				const int value =
					manager_instance.generate_number<int>(1, 10);
				std::lock_guard<std::mutex> lock(results_mutex);
				results.push_back(value);
			}
		};

		std::thread t1(thread_function);
		std::thread t2(thread_function);
		t1.join();
		t2.join();

		EXPECT_EQ(results.size(), 200);
		for (const auto& number : results)
		{
			EXPECT_GE(number, 1);
			EXPECT_LE(number, 10);
		}
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleAsynchronousGeneration_When_CalledWithFuture)
	{
		auto async_task = std::async(std::launch::async, [&]()
		{
			return manager_instance.generate_number<int>(1, 5);
		});

		const int result = async_task.get();

		EXPECT_GE(result, 1);
		EXPECT_LE(result, 5);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_CompleteStressTestWithinTime_When_LargeIterations)
	{
		const int iterations = 100000;
		std::vector<int> results;
		results.reserve(iterations);

		auto start_time = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < iterations; ++i)
		{
			results.push_back(manager_instance.generate_number<int>(1, 100));
		}

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration =
			std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
				start_time)
				.count();

		EXPECT_LE(duration, 2000);
	}

	TEST_P(RandomNumberGenerationManagerParameterizedTest,
		Should_GenerateNumberWithinRange_When_Parameterized)
	{
		const RandomNumberGenerationManagerParam param = GetParam();

		const int generated_number =
			manager_instance.generate_number<int>(param.minimum,
				param.maximum);

		EXPECT_GE(generated_number, param.minimum);
		EXPECT_LE(generated_number, param.maximum);
	}

	INSTANTIATE_TEST_CASE_P(
		ParameterizedRangeTests,
		RandomNumberGenerationManagerParameterizedTest,
		::testing::Values(
			RandomNumberGenerationManagerParam{0, 0},
			RandomNumberGenerationManagerParam{0, 1},
			RandomNumberGenerationManagerParam{-5, 5},
			RandomNumberGenerationManagerParam{10, 20}));

	TEST_F(RandomNumberGenerationManagerTest,
		Should_GenerateFloatExcludingValues_When_ExcludedProvided)
	{
		const double minimum = 0.0;
		const double maximum = 5.0;
		std::unordered_set<double> excluded{1.0, 2.5, 4.0};

		const double generated_number =
			manager_instance.generate_number<double>(
				minimum, maximum, excluded);

		EXPECT_GE(generated_number, minimum);
		EXPECT_LE(generated_number, maximum);
		for (const auto& value : excluded)
			EXPECT_TRUE(std::fabs(generated_number - value) > std::numeric_limits<double>::epsilon());
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleMaxOnlyWithZeroAndNegative_When_GenerateNumberCalled)
	{
		const int generated_zero =
			manager_instance.generate_number<int>(0);

		EXPECT_GE(generated_zero, 0);
		EXPECT_LE(generated_zero, 0);

		const int generated_negative =
			manager_instance.generate_number<int>(-5, 0);

		EXPECT_LE(generated_negative, 0);
		EXPECT_GE(generated_negative, -5);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleIncludedWithSingleElement_When_GenerateNumberCalled)
	{
		std::unordered_set<int> included{42};

		const int generated_number =
			manager_instance.generate_number<int>(included);

		EXPECT_EQ(generated_number, 42);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleExcludedAllValues_When_RangeFullyExcluded)
	{
		const int minimum = 1;
		const int maximum = 3;
		std::unordered_set<int> excluded{1, 2, 3};

		const int generated_number =
			manager_instance.generate_number<int>(minimum, maximum, excluded);

		EXPECT_GE(generated_number, minimum);
		EXPECT_LE(generated_number, maximum);
		EXPECT_FALSE(excluded.find(generated_number) == excluded.end());
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleExtremeIntegerRange_When_GenerateNumberCalled)
	{
		const int minimum = INT_MAX - 1;
		const int maximum = INT_MAX;

		const int generated_number =
			manager_instance.generate_number<int>(minimum, maximum);

		EXPECT_GE(generated_number, minimum);
		EXPECT_LE(generated_number, maximum);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleExtremeDoubleRange_When_GenerateNumberCalled)
	{
		const double minimum = std::numeric_limits<double>::max() / 2;
		const double maximum = std::numeric_limits<double>::max();

		const double generated_number =
			manager_instance.generate_number<double>(minimum, maximum);

		EXPECT_GE(generated_number, minimum);
		EXPECT_LE(generated_number, maximum);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleMultipleAsyncTasks_When_CalledConcurrently)
	{
		const int tasks = 8;
		std::vector<std::future<int>> futures;

		for (int i = 0; i < tasks; ++i)
		{
			futures.push_back(std::async(std::launch::async, [&]()
			{
				return manager_instance.generate_number<int>(1, 10);
			}));
		}

		for (auto& fut : futures)
		{
			const int result = fut.get();
			EXPECT_GE(result, 1);
			EXPECT_LE(result, 10);
		}
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleHighConcurrencyStress_When_MultithreadedGeneration)
	{
		const int threads_count = 8;
		const int iterations_per_thread = 5000;
		std::vector<int> results;
		results.reserve(threads_count * iterations_per_thread);
		std::mutex results_mutex;

		auto thread_function = [&]()
		{
			for (int i = 0; i < iterations_per_thread; ++i)
			{
				const int value =
					manager_instance.generate_number<int>(1, 50);
				std::lock_guard<std::mutex> lock(results_mutex);
				results.push_back(value);
			}
		};

		std::vector<std::thread> threads;
		for (int i = 0; i < threads_count; ++i)
			threads.emplace_back(thread_function);
		for (auto& thread : threads)
			thread.join();

		EXPECT_EQ(results.size(), threads_count * iterations_per_thread);
		for (const auto& number : results)
		{
			EXPECT_GE(number, 1);
			EXPECT_LE(number, 50);
		}
	}

	TEST_P(RandomNumberGenerationManagerEdgeParameterizedTest,
		Should_GenerateNumberWithinRange_When_MaxAndExcludedProvided)
	{
		const RandomNumberGenerationManagerEdgeParam param = GetParam();

		const int generated_number =
			manager_instance.generate_number<int>(param.maximum, param.excluded);

		EXPECT_GE(generated_number, 0);
		EXPECT_LE(generated_number, param.maximum);
		for (const auto& excluded_value : param.excluded)
			EXPECT_TRUE(generated_number != excluded_value);
	}

	INSTANTIATE_TEST_CASE_P(
		ParameterizedMaxExcludedTests,
		RandomNumberGenerationManagerEdgeParameterizedTest,
		::testing::Values(
			RandomNumberGenerationManagerEdgeParam{5, {2, 3}},
			RandomNumberGenerationManagerEdgeParam{0, {}},
			RandomNumberGenerationManagerEdgeParam{10, {0, 5, 10}}));

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleFloatMinGreaterThanMax_When_GenerateNumberCalled)
	{
		const double minimum = 10.5;
		const double maximum = 1.5;

		const double generated_number =
			manager_instance.generate_number<double>(minimum, maximum);

		EXPECT_EQ(generated_number, minimum);
	}
	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleEmptyExcludedSet_When_FloatGenerationCalled)
	{
		const double minimum = 0.0;
		const double maximum = 5.0;
		std::unordered_set<double> excluded;

		const double generated_number =
			manager_instance.generate_number<double>(minimum, maximum, excluded);

		EXPECT_GE(generated_number, minimum);
		EXPECT_LE(generated_number, maximum);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleExcludedLeavingSingleValue_When_GenerateNumberCalled)
	{
		const int minimum = 1;
		const int maximum = 3;
		std::unordered_set<int> excluded{1, 2};

		const int generated_number =
			manager_instance.generate_number<int>(minimum, maximum, excluded);

		EXPECT_EQ(generated_number, 3);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleAsyncException_When_TaskThrows)
	{
		auto async_task = std::async(std::launch::async, [&]()
		{
			throw std::runtime_error("Simulated exception");
			return manager_instance.generate_number<int>(1, 5);
		});

		EXPECT_THROW(async_task.get(), std::runtime_error);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleMultithreadedException_When_TaskThrows)
	{
		const int threads_count = 2;
		std::vector<std::thread> threads;
		std::vector<int> results;
		std::mutex results_mutex;

		auto thread_function = [&]()
		{
			try
			{
				throw std::runtime_error("Simulated exception");
			}
			catch (...)
			{
				std::lock_guard<std::mutex> lock(results_mutex);
				results.push_back(42);
			}
		};

		for (int i = 0; i < threads_count; ++i)
			threads.emplace_back(thread_function);
		for (auto& thread : threads)
			thread.join();

		EXPECT_EQ(results.size(), threads_count);
		for (const auto& value : results)
			EXPECT_EQ(value, 42);
	}

	TEST_P(RandomNumberGenerationManagerFloatParameterizedTest,
		Should_GenerateFloatWithinRange_When_Parameterized)
	{
		const auto param = GetParam();
		const double generated_number =
			manager_instance.generate_number<double>(param.first, param.second);

		EXPECT_GE(generated_number, param.first);
		EXPECT_LE(generated_number, param.second);
	}

	INSTANTIATE_TEST_CASE_P(
		ParameterizedFloatRangeTests,
		RandomNumberGenerationManagerFloatParameterizedTest,
		::testing::Values(
			std::make_pair(0.0, 0.0),
			std::make_pair(0.0, 1.0),
			std::make_pair(-5.5, 5.5),
			std::make_pair(10.1, 20.2)));

	TEST_F(RandomNumberGenerationManagerTest,
		Should_GenerateFloatFromIncluded_When_SingleElement)
	{
		std::unordered_set<double> included{3.14};

		const double generated_number =
			manager_instance.generate_number<double>(included);

		EXPECT_EQ(generated_number, 3.14);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_GenerateFloatFromIncluded_When_MultipleElements)
	{
		std::unordered_set<double> included{1.1, 2.2, 3.3};

		const double generated_number =
			manager_instance.generate_number<double>(included);

		EXPECT_TRUE(included.find(generated_number) != included.end());
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleExcludedAllValues_When_FloatRangeFullyExcluded)
	{
		const double minimum = 1.0;
		const double maximum = 3.0;
		std::unordered_set<double> excluded{1.0, 2.0, 3.0};

		const double generated_number =
			manager_instance.generate_number<double>(minimum, maximum, excluded);

		EXPECT_GE(generated_number, minimum);
		EXPECT_LE(generated_number, maximum);
		EXPECT_TRUE(excluded.find(generated_number) == excluded.end());
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_CompleteStressTestWithinTime_When_FloatLargeIterations)
	{
		const int iterations = 100000;
		std::vector<double> results;
		results.reserve(iterations);

		auto start_time = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < iterations; ++i)
		{
			results.push_back(manager_instance.generate_number<double>(1.0, 100.0));
		}

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration =
			std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
				start_time)
				.count();

		EXPECT_LE(duration, 2000);
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleMultipleAsyncFloatTasks_When_CalledConcurrently)
	{
		const int tasks = 8;
		std::vector<std::future<double>> futures;

		for (int i = 0; i < tasks; ++i)
		{
			futures.push_back(std::async(std::launch::async, [&]()
			{
				return manager_instance.generate_number<double>(1.0, 10.0);
			}));
		}

		for (auto& fut : futures)
		{
			const double result = fut.get();
			EXPECT_GE(result, 1.0);
			EXPECT_LE(result, 10.0);
		}
	}

	TEST_F(RandomNumberGenerationManagerTest,
		Should_HandleHighConcurrencyStressFloat_When_MultithreadedGeneration)
	{
		const int threads_count = 8;
		const int iterations_per_thread = 5000;
		std::vector<double> results;
		results.reserve(threads_count * iterations_per_thread);
		std::mutex results_mutex;

		auto thread_function = [&]()
		{
			for (int i = 0; i < iterations_per_thread; ++i)
			{
				const double value =
					manager_instance.generate_number<double>(1.0, 50.0);
				std::lock_guard<std::mutex> lock(results_mutex);
				results.push_back(value);
			}
		};

		std::vector<std::thread> threads;
		for (int i = 0; i < threads_count; ++i)
			threads.emplace_back(thread_function);
		for (auto& thread : threads)
			thread.join();

		EXPECT_EQ(results.size(), threads_count * iterations_per_thread);
		for (const auto& number : results)
		{
			EXPECT_GE(number, 1.0);
			EXPECT_LE(number, 50.0);
		}
	}

	TEST_P(RandomNumberGenerationManagerFloatParameterizedTest,
		Should_GenerateFloatFromIncluded_When_Parameterized)
	{
		const auto param = GetParam();
		std::unordered_set<double> included{param.first, param.second};

		const double generated_number =
			manager_instance.generate_number<double>(included);

		EXPECT_TRUE(included.find(generated_number) != included.end());
	}

	TEST_P(RandomNumberGenerationManagerFloatParameterizedTest,
		Should_GenerateFloatExcludingValues_When_Parameterized)
	{
		const auto param = GetParam();
		std::unordered_set<double> excluded{param.first};

		const double generated_number =
			manager_instance.generate_number<double>(param.first, param.second, excluded);

		if (param.first == 0 && param.second == 0)
		{
			EXPECT_EQ(generated_number, param.first);
			EXPECT_EQ(generated_number, param.second);
			EXPECT_TRUE(generated_number == param.first);
		}
		else
		{
			EXPECT_GE(generated_number, param.first);
			EXPECT_LE(generated_number, param.second);
			EXPECT_TRUE(generated_number != param.first);
		}
	}
}

#endif
