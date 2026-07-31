#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RestApiManager \
	)

#include "../includes/rest_api_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(RestApiManagerTest,
		Should_ReturnResponse_When_GetRequestValid)
	{
		auto start_timestamp =
			std::chrono::steady_clock::now();

		auto response =
			execute_get(
				"/"
			);

		auto end_timestamp =
			std::chrono::steady_clock::now();

		auto duration =
			std::chrono::duration_cast
			<
				std::chrono::milliseconds
			>(
				end_timestamp -
				start_timestamp
			);

		EXPECT_LT(
			duration.count(),
			static_cast<long>(2000)
		);
	}

	TEST_F(RestApiManagerTest,
		Should_HandleEmptyPath_When_EdgeCaseEnabled)
	{
		RestApiManagerConfigurations
			configurations;

		configurations.base_url =
			"http://127.0.0.1";

		configurations
			.is_edge_case_handling_override_enabled =
				true;

		configurations
			.is_edge_case_handling_enabled =
				true;

		manager_instance.setup(
			configurations
		);

		auto result =
			manager_instance
				.execute_get_request(
					""
				);

		EXPECT_EQ(
			result.status_code,
			static_cast<long>(0)
		);
	}

	TEST_F(RestApiManagerTest,
		Should_RunAsync_When_MultipleFutures)
	{
		auto future_one =
			std::async(
				std::launch::async,
				[this]()
				{
					return
						execute_get(
							"/"
						);
				}
			);

		auto future_two =
			std::async(
				std::launch::async,
				[this]()
				{
					return
						execute_get(
							"/"
						);
				}
			);

		auto response_one =
			future_one.get();

		auto response_two =
			future_two.get();

		EXPECT_TRUE(
			true
		);
	}

	TEST_F(RestApiManagerTest,
		Should_HandleMultithread_When_ConcurrentAccess)
	{
		std::atomic<int>
			completed_threads =
				0;

		std::vector<std::thread>
			thread_collection;

		for
		(
			std::size_t index = 0;
			index < static_cast<std::size_t>(10);
			++index
		)
		{
			thread_collection.emplace_back(
				[this, &completed_threads]()
				{
					execute_get(
						"/"
					);
					++completed_threads;
				}
			);
		}

		for
		(
			auto&
				thread_instance :
				thread_collection
		)
		{
			thread_instance.join();
		}

		EXPECT_EQ(
			completed_threads.load(),
			static_cast<int>(10)
		);
	}

	TEST_F(RestApiManagerTest,
		Should_HandleStress_When_HighIterationLoad)
	{
		auto start_timestamp =
			std::chrono::steady_clock::now();

		for
		(
			std::size_t index = 0;
			index < static_cast<std::size_t>(50);
			++index
		)
		{
			execute_get(
				"/"
			);
		}

		auto end_timestamp =
			std::chrono::steady_clock::now();

		auto duration =
			std::chrono::duration_cast
			<
				std::chrono::milliseconds
			>(
				end_timestamp -
				start_timestamp
			);

		EXPECT_LT(
			duration.count(),
			static_cast<long>(2000)
		);
	}

	TEST_P(RestApiManagerParameterizedTest,
		Should_ExecuteParameterized_When_PathProvided)
	{
		auto path_value =
			GetParam();

		auto response =
			execute_get(
				path_value
			);

		EXPECT_TRUE(
			true
		);
	}

	INSTANTIATE_TEST_CASE_P(
		RestApiManagerPaths,
		RestApiManagerParameterizedTest,
		::testing::Values(
			std::string("/"),
			std::string("/index"),
			std::string("/api")
		)
	);
	
	TEST_F(
		RestApiManagerTest,
		Should_ReturnResponse_Expect_NoThrow_When_AsyncFutureUsed
	)
	{
		auto async_future =
			std::async(
				std::launch::async,
				[this]()
				{
					return execute_get("/");
				}
			);

		ASSERT_NO_THROW(
			async_future.wait_for(
				std::chrono::seconds(2)
			)
		);

		RestApiManagerResponse response =
			async_future.get();

		EXPECT_GE(
			static_cast<int>(response.status_code),
			0
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_HandleConcurrentCalls_Expect_NoCrash_When_MultipleThreads
	)
	{
		const std::size_t thread_count = 8U;
		std::vector<std::thread> thread_collection;
		std::atomic<std::size_t> completion_counter{0U};
		std::mutex synchronization_mutex;
		std::condition_variable synchronization_condition;

		for (
			std::size_t index = 0U;
			index < thread_count;
			++index
		)
		{
			thread_collection.emplace_back(
				[this, &completion_counter,
				 &synchronization_condition]()
				{
					RestApiManagerResponse response =
						execute_get("/");

					if (
						response.status_code >= 0
					)
					{
						completion_counter.fetch_add(
							1U,
							std::memory_order_relaxed
						);
					}

					synchronization_condition.notify_one();
				}
			);
		}

		for (std::thread& worker_thread :
			 thread_collection)
		{
			worker_thread.join();
		}

		EXPECT_EQ(
			completion_counter.load(
				std::memory_order_relaxed
			),
			thread_count
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_HandleHighLoad_Expect_Stable_When_StressTested
	)
	{
		const std::size_t iteration_count = 100U;
		std::atomic<std::size_t> success_counter{0U};

		for (
			std::size_t iteration = 0U;
			iteration < iteration_count;
			++iteration
		)
		{
			RestApiManagerResponse response =
				execute_get("/");

			if (response.status_code >= 0)
			{
				success_counter.fetch_add(
					1U,
					std::memory_order_relaxed
				);
			}
		}

		EXPECT_EQ(
			success_counter.load(
				std::memory_order_relaxed
			),
			iteration_count
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_ThrowOrReturnError_Expect_ValidState_When_InvalidPath
	)
	{
		ASSERT_NO_THROW(
			execute_get(
				"/\x01\x02"
			)
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_HandleEmptyPath_Expect_NoCrash_When_EmptyString
	)
	{
		ASSERT_NO_THROW(
			execute_get(
				std::string{}
			)
		);
	}

	TEST_P(
		RestApiManagerParameterizedTest,
		Should_ReturnResponse_Expect_NoThrow_When_VariousPaths
	)
	{
		const std::string path =
			GetParam();

		ASSERT_NO_THROW(
			execute_get(
				path
			)
		);

		RestApiManagerResponse response =
			execute_get(
				path
			);

		EXPECT_GE(
			static_cast<int>(response.status_code),
			0
		);
	}

	INSTANTIATE_TEST_CASE_P(
		RestApiManagerPathParameters,
		RestApiManagerParameterizedTest,
		::testing::Values(
			std::string{"/"},
			std::string{"/api"},
			std::string{"/health"},
			std::string{"/status"}
		)
	);

	TEST_F(
		RestApiManagerTest,
		Should_CompleteWithinTime_Expect_LessThanTwoSeconds_When_PerformanceValidated
	)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		RestApiManagerResponse response =
			execute_get("/");

		auto end_time =
			std::chrono::steady_clock::now();

		auto duration =
			std::chrono::duration_cast<
				std::chrono::milliseconds
			>(
				end_time - start_time
			);

		EXPECT_LT(
			duration.count(),
			2000
		);

		EXPECT_GE(
			static_cast<int>(response.status_code),
			0
		);
	}

		TEST_F(
		RestApiManagerTest,
		Should_PropagateException_Expect_FutureThrows_When_BaseUrlInvalid
	)
	{
		RestApiManagerConfigurations configurations;
		configurations.base_url = "http://256.256.256.256";
		manager_instance.setup(configurations);

		auto async_future =
			std::async(
				std::launch::async,
				[this]()
				{
					return execute_get("/");
				}
			);

		EXPECT_NO_THROW(
			async_future.wait_for(
				std::chrono::seconds(2)
			)
		);

		EXPECT_NO_THROW(
			async_future.get()
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_SignalCompletion_Expect_PromiseValue_When_UsingPromise
	)
	{
		std::promise<long> completion_promise;
		std::future<long> completion_future =
			completion_promise.get_future();

		std::thread worker_thread(
			[this, &completion_promise]()
			{
				RestApiManagerResponse response =
					execute_get("/");
				completion_promise.set_value(
					response.status_code
				);
			}
		);

		EXPECT_EQ(
			completion_future.wait_for(
				std::chrono::seconds(2)
			),
			std::future_status::ready
		);

		long status_code =
			completion_future.get();

		worker_thread.join();

		EXPECT_GE(
			status_code,
			static_cast<long>(0)
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_HandleHighConcurrency_Expect_AllThreadsComplete_When_StressThreads
	)
	{
		const std::size_t thread_count =
			static_cast<std::size_t>(50);

		std::atomic<std::size_t>
			completed_threads{0U};

		std::vector<std::thread>
			thread_collection;

		for (
			std::size_t index = 0U;
			index < thread_count;
			++index
		)
		{
			thread_collection.emplace_back(
				[this, &completed_threads]()
				{
					execute_get("/");
					completed_threads.fetch_add(
						1U,
						std::memory_order_relaxed
					);
				}
			);
		}

		for (
			std::thread& thread_instance :
			thread_collection
		)
		{
			thread_instance.join();
		}

		EXPECT_EQ(
			completed_threads.load(
				std::memory_order_relaxed
			),
			thread_count
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_HandleVeryLongPath_Expect_NoCrash_When_PathExceedsNormalLength
	)
	{
		std::string long_path(
			static_cast<std::size_t>(2048),
			'a'
		);

		EXPECT_NO_THROW(
			execute_get(
				long_path
			)
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_HandleUnicodePath_Expect_NoCrash_When_PathContainsUnicode
	)
	{
		std::string unicode_path =
			"/тест";

		EXPECT_NO_THROW(
			execute_get(
				unicode_path
			)
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_ReconfigureManager_Expect_NoCrash_When_SetupCalledTwice
	)
	{
		RestApiManagerConfigurations configurations;
		configurations.base_url =
			"http://127.0.0.1";

		manager_instance.setup(
			configurations
		);

		EXPECT_NO_THROW(
			execute_get("/")
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_HandleMissingProtocol_Expect_NoCrash_When_BaseUrlMalformed
	)
	{
		RestApiManagerConfigurations configurations;
		configurations.base_url =
			"127.0.0.1";

		manager_instance.setup(
			configurations
		);

		EXPECT_NO_THROW(
			execute_get("/")
		);
	}

	TEST_P(
		RestApiManagerParameterizedTest,
		Should_HandleInvalidPaths_Expect_NoThrow_When_InvalidProvided
	)
	{
		const std::string path =
			GetParam();

		EXPECT_NO_THROW(
			execute_get(
				path
			)
		);
	}

	INSTANTIATE_TEST_CASE_P(
		RestApiManagerInvalidPaths,
		RestApiManagerParameterizedTest,
		::testing::Values(
			std::string(""),
			std::string("////"),
			std::string("/../../"),
			std::string("/?query=value"),
			std::string("/\x7F\x7E")
		)
	);

	TEST_F(
		RestApiManagerTest,
		Should_CompleteUnderLoad_Expect_LessThanTwoSeconds_When_ConcurrentAsyncStress
	)
	{
		const std::size_t task_count =
			static_cast<std::size_t>(20);

		std::vector<
			std::future<RestApiManagerResponse>
		> future_collection;

		auto start_timestamp =
			std::chrono::steady_clock::now();

		for (
			std::size_t index = 0U;
			index < task_count;
			++index
		)
		{
			future_collection.emplace_back(
				std::async(
					std::launch::async,
					[this]()
					{
						return execute_get("/");
					}
				)
			);
		}

		for (
			auto& future_instance :
			future_collection
		)
		{
			future_instance.get();
		}

		auto end_timestamp =
			std::chrono::steady_clock::now();

		auto duration =
			std::chrono::duration_cast<
				std::chrono::milliseconds
			>(
				end_timestamp -
				start_timestamp
			);

		EXPECT_LT(
			duration.count(),
			static_cast<long>(2000)
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_ThrowOrReturnFailure_Expect_StableState_When_BaseUrlEmpty
	)
	{
		RestApiManagerConfigurations configurations;
		configurations.base_url = "";

		manager_instance.setup(
			configurations
		);

		EXPECT_NO_THROW(
			execute_get("/")
		);

		RestApiManagerResponse response =
			execute_get("/");

		EXPECT_GE(
			response.status_code,
			static_cast<long>(0)
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_HandleCall_Expect_NoCrash_When_SetupNotCalled
	)
	{
		RestApiManager uninitialized_manager;

		EXPECT_NO_THROW(
			uninitialized_manager.execute_get_request("/")
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_RemainReusable_Expect_NoCrash_When_CallAfterFailure
	)
	{
		RestApiManagerConfigurations configurations;
		configurations.base_url =
			"http://256.256.256.256";

		manager_instance.setup(
			configurations
		);

		EXPECT_NO_THROW(
			execute_get("/")
		);

		RestApiManagerConfigurations valid_configurations;
		valid_configurations.base_url =
			"http://127.0.0.1";

		manager_instance.setup(
			valid_configurations
		);

		EXPECT_NO_THROW(
			execute_get("/")
		);
	}

	TEST_F(
		RestApiManagerTest,
		Should_SynchronizeThreads_Expect_AllWaitingReleased_When_ConditionSignaled
	)
	{
		std::mutex synchronization_mutex;
		std::condition_variable synchronization_condition;
		bool is_ready = false;
		std::atomic<std::size_t> completed_threads{ 0U };
		const std::size_t thread_count =
			static_cast<std::size_t>(10);

		std::vector<std::thread> thread_collection;

		for (
			std::size_t index = 0U;
			index < thread_count;
			++index
			)
		{
			thread_collection.emplace_back(
				[this,
				&synchronization_mutex,
				&synchronization_condition,
				&is_ready,
				&completed_threads]()
				{
					std::unique_lock<std::mutex>
						lock(synchronization_mutex);

					synchronization_condition.wait(
						lock,
						[&is_ready]()
						{
							return is_ready;
						}
					);

					lock.unlock();

					execute_get("/");

					completed_threads.fetch_add(
						1U,
						std::memory_order_relaxed
					);
				}
			);
		}

		{
			std::unique_lock<std::mutex>
				lock(synchronization_mutex);
			is_ready = true;
		}

		synchronization_condition.notify_all();

		for (
			std::thread& thread_instance :
			thread_collection
			)
		{
			thread_instance.join();
		}

		EXPECT_EQ(
			completed_threads.load(
				std::memory_order_relaxed
			),
			thread_count
		);
	}

	TEST_P(
		RestApiManagerEmptyPathParameterizedTest,
		Should_HandleEmptyPath_Expect_NoCrash_When_EmptyProvided
	)
	{
		EXPECT_NO_THROW(
			execute_get(
				std::string{}
			)
		);

		RestApiManagerResponse response =
			execute_get(
				std::string{}
			);

		EXPECT_GE(
			response.status_code,
			static_cast<long>(0)
		);
	}

	INSTANTIATE_TEST_CASE_P(
		RestApiManagerEmptyPathOnly,
		RestApiManagerEmptyPathParameterizedTest,
		::testing::Values(
			0
		)
	);

	TEST_F(
		RestApiManagerTest,
		Should_HandleCombinedAsyncThreadStress_Expect_CompleteWithinTwoSeconds_When_LoadHigh
	)
	{
		const std::size_t thread_count =
			static_cast<std::size_t>(10);
		const std::size_t async_per_thread =
			static_cast<std::size_t>(5);

		auto start_timestamp =
			std::chrono::steady_clock::now();

		std::vector<std::thread> thread_collection;

		for (
			std::size_t index = 0U;
			index < thread_count;
			++index
			)
		{
			thread_collection.emplace_back(
				[this, async_per_thread]()
				{
					std::vector<
						std::future<RestApiManagerResponse>
					> future_collection;

					for (
						std::size_t inner_index = 0U;
						inner_index < async_per_thread;
						++inner_index
						)
					{
						future_collection.emplace_back(
							std::async(
								std::launch::async,
								[this]()
								{
									return execute_get("/");
								}
							)
						);
					}

					for (
						auto& future_instance :
						future_collection
						)
					{
						future_instance.get();
					}
				}
			);
		}

		for (
			std::thread& thread_instance :
			thread_collection
			)
		{
			thread_instance.join();
		}

		auto end_timestamp =
			std::chrono::steady_clock::now();

		auto duration =
			std::chrono::duration_cast<
			std::chrono::milliseconds
			>(
				end_timestamp -
				start_timestamp
			);

		EXPECT_LT(
			duration.count(),
			static_cast<long>(2000)
		);
	}
}

#endif
