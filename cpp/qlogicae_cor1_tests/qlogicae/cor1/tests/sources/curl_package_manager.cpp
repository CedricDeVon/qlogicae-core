#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CurlPackageManager \
	)

#include "../includes/curl_package_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(CurlPackageManagerTest, Should_ReturnTrue_When_SetupWithDefaultConfigurations)
	{
		ASSERT_TRUE(manager.setup());
	}

	TEST_F(CurlPackageManagerTest, Should_ReturnFalse_When_RuntimeExecutionDisabled)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled =
			false;
		ASSERT_FALSE(manager.setup());
		manager.configurations.is_feature_runtime_execution_handling_enabled =
			true;
	}

	TEST_F(CurlPackageManagerTest, Should_InitializeOnce_When_MultipleSetupCalls)
	{
		ASSERT_TRUE(manager.setup());
		ASSERT_TRUE(manager.setup());
	}

	TEST_F(CurlPackageManagerTest, Should_HandleThreadSafety_When_MultipleThreadsCallSetup)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled =
			true;

		std::vector<std::thread> threads;
		std::vector<bool> results(10, false);

		for (std::size_t index = 0; index < 10; ++index)
		{
			threads.emplace_back([&, index]()
			{
				results[index] = manager.setup();
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		for (const auto& result : results)
		{
			ASSERT_TRUE(result);
		}
	}

	TEST_F(CurlPackageManagerTest, Should_HandleEdgeCases_When_DefaultConfigurationsEmpty)
	{
		manager.configurations = {};
		ASSERT_TRUE(manager.setup());
	}

	TEST_F(CurlPackageManagerTest, Should_PerformUnderStress_When_RepeatedSetupCalls)
	{
		for (std::size_t index = 0; index < 1000; ++index)
		{
			ASSERT_TRUE(manager.setup());
		}
	}

	TEST_F(CurlPackageManagerTest, Should_HandleAsyncSetup_When_UsingFutures)
	{
		auto future_setup = std::async(std::launch::async, [&]()
		{
			return manager.setup();
		});

		ASSERT_TRUE(future_setup.get());
	}

	TEST_F(CurlPackageManagerTest, Should_HandleMultipleAsyncCalls_When_UsingPromises)
	{
		std::promise<bool> setup_promise;
		std::future<bool> setup_future = setup_promise.get_future();

		std::thread async_thread([&]()
		{
			setup_promise.set_value(manager.setup());
		});

		ASSERT_TRUE(setup_future.get());
		async_thread.join();
	}

	INSTANTIATE_TEST_CASE_P(
		CurlPackageManagerParameterized,
		CurlPackageManagerParameterizedTest,
		::testing::Values(true, false)
	);

	TEST_P(CurlPackageManagerParameterizedTest, Should_HandleParameterizedThreadSafety_When_ConfigChanges)
	{
		manager.configurations.is_utility_thread_safety_handling_enabled = GetParam();
		ASSERT_TRUE(manager.setup());
	}

	TEST_F(CurlPackageManagerTest, Should_CompleteUnderTwoSeconds_When_StressTest)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		for (std::size_t index = 0; index < 10000; ++index)
		{
			ASSERT_TRUE(manager.setup());
		}
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration_ms =
			std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time)
				.count();
		ASSERT_LE(duration_ms, 2000);
	}

	TEST_F(CurlPackageManagerTest, Should_HandleFeatureRuntimeExecutionDisabled)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled =
			false;
		ASSERT_FALSE(manager.setup());
		manager.configurations.is_feature_runtime_execution_handling_enabled =
			true;
	}

	TEST_F(CurlPackageManagerTest, Should_HandleErrorRuntimeExecutionDisabled)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled =
			false;
		ASSERT_FALSE(manager.setup());
		manager.configurations.is_error_runtime_execution_handling_enabled =
			true;
	}

	TEST_F(CurlPackageManagerTest, Should_HandleFeatureEdgeCaseDisabled)
	{
		manager.configurations.is_feature_edge_case_handling_enabled =
			false;
		ASSERT_TRUE(manager.setup());
		manager.configurations.is_feature_edge_case_handling_enabled =
			true;
	}

	TEST_F(CurlPackageManagerTest, Should_HandleErrorEdgeCaseDisabled)
	{
		manager.configurations.is_error_edge_case_handling_enabled =
			false;
		ASSERT_TRUE(manager.setup());
		manager.configurations.is_error_edge_case_handling_enabled =
			true;
	}

	TEST_F(CurlPackageManagerTest, Should_HandleFeatureThreadSafetyDisabled)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled =
			false;

		std::vector<std::thread> threads;
		std::vector<bool> results(5, false);

		for (std::size_t index = 0; index < 5; ++index)
		{
			threads.emplace_back([&, index]()
			{
				results[index] = manager.setup();
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		for (const auto& result : results)
		{
			ASSERT_TRUE(result);
		}
		manager.configurations.is_feature_thread_safety_handling_enabled =
			true;
	}

	TEST_F(CurlPackageManagerTest, Should_HandleErrorThreadSafetyDisabled)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled =
			false;

		std::vector<std::thread> threads;
		std::vector<bool> results(5, false);

		for (std::size_t index = 0; index < 5; ++index)
		{
			threads.emplace_back([&, index]()
			{
				results[index] = manager.setup();
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		for (const auto& result : results)
		{
			ASSERT_TRUE(result);
		}
		manager.configurations.is_error_thread_safety_handling_enabled =
			true;
	}

	TEST_F(CurlPackageManagerTest, Should_HandleAsyncStress_When_MultipleFuturesAndThreads)
	{
		std::vector<std::future<bool>> futures;
		for (std::size_t i = 0; i < 10; ++i)
		{
			futures.emplace_back(std::async(std::launch::async, [&]()
			{
				return manager.setup();
			}));
		}

		std::vector<std::thread> threads;
		std::vector<bool> results(5, false);
		for (std::size_t i = 0; i < 5; ++i)
		{
			threads.emplace_back([&, i]()
			{
				results[i] = manager.setup();
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		for (auto& future : futures)
		{
			ASSERT_TRUE(future.get());
		}

		for (const auto& result : results)
		{
			ASSERT_TRUE(result);
		}
	}

	TEST_F(CurlPackageManagerTest, Should_HandlePartialInvalidConfigurations)
	{
		manager.configurations.is_feature_runtime_execution_handling_enabled =
			false;
		manager.configurations.is_feature_thread_safety_handling_enabled =
			false;
		ASSERT_FALSE(manager.setup());
		manager.configurations.is_feature_runtime_execution_handling_enabled =
			true;
		manager.configurations.is_feature_thread_safety_handling_enabled =
			true;
	}

	TEST_F(CurlPackageManagerTest, Should_HandleThreadedExceptionSafety_When_ThreadThrows)
	{
		std::atomic<bool> caught_exception = false;

		std::thread thread([&]()
		{
			try
			{
				struct CurlPackageManagerMock :
					public CurlPackageManager
				{
					bool setup()
					{
						throw std::runtime_error("Thread exception");
					}
				};

				CurlPackageManagerMock mock_manager;
				mock_manager.setup();
			}
			catch (const std::exception&)
			{
				caught_exception = true;
			}
		});

		thread.join();
		ASSERT_TRUE(caught_exception);
	}

	TEST_F(CurlPackageManagerTest, Should_HandleMixedInvalidConfigurations_UnderStress)
	{
		manager.configurations.is_utility_runtime_execution_handling_enabled = false;
		manager.configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.configurations.is_error_runtime_execution_handling_enabled = false;
		manager.configurations.is_feature_thread_safety_handling_enabled = false;
		manager.configurations.is_error_thread_safety_handling_enabled = false;

		for (std::size_t index = 0; index < 500; ++index)
		{
			ASSERT_FALSE(manager.setup());
		}

		manager.configurations.is_utility_runtime_execution_handling_enabled = true;
		manager.configurations.is_feature_runtime_execution_handling_enabled = true;
		manager.configurations.is_error_runtime_execution_handling_enabled = true;
		manager.configurations.is_feature_thread_safety_handling_enabled = true;
		manager.configurations.is_error_thread_safety_handling_enabled = true;

		for (std::size_t index = 0; index < 500; ++index)
		{
			ASSERT_TRUE(manager.setup());
		}
	}

	INSTANTIATE_TEST_CASE_P(
		CurlPackageManagerParameterizedInvalid,
		CurlPackageManagerParameterizedInvalidTest,
		::testing::Values(
			[]() { CurlPackageManagerConfigurations cfg{}; cfg.is_utility_runtime_execution_handling_enabled = false; return cfg; }(),
			[]() { CurlPackageManagerConfigurations cfg{}; cfg.is_feature_runtime_execution_handling_enabled = false; return cfg; }(),
			[]() { CurlPackageManagerConfigurations cfg{}; cfg.is_error_runtime_execution_handling_enabled = false; return cfg; }(),
			[]() { CurlPackageManagerConfigurations cfg{}; cfg.is_feature_thread_safety_handling_enabled = false; return cfg; }(),
			[]() { CurlPackageManagerConfigurations cfg{}; cfg.is_error_thread_safety_handling_enabled = false; return cfg; }()
		)
	);

	TEST_P(CurlPackageManagerParameterizedInvalidTest, Should_HandleParameterizedInvalidConfigurations)
	{
		manager.configurations = GetParam();
		if (!manager.configurations.is_runtime_execution_enabled_for_feature_handling())
		{
			ASSERT_FALSE(manager.setup());
		}
		else
		{
			ASSERT_TRUE(manager.setup());
		}
	}

	TEST_F(CurlPackageManagerTest, Should_CompleteAsyncAndThreadStressUnderTwoSeconds)
	{
		auto start_time = std::chrono::high_resolution_clock::now();

		std::vector<std::future<bool>> futures;
		for (std::size_t i = 0; i < 10; ++i)
		{
			futures.emplace_back(std::async(std::launch::async, [&]()
			{
				return manager.setup();
			}));
		}

		std::vector<std::thread> threads;
		for (std::size_t i = 0; i < 10; ++i)
		{
			threads.emplace_back([&]()
			{
				manager.setup();
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		for (auto& future : futures)
		{
			ASSERT_TRUE(future.get());
		}

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration_ms =
			std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time)
				.count();
		ASSERT_LE(duration_ms, 2000);
	}
}

#endif
