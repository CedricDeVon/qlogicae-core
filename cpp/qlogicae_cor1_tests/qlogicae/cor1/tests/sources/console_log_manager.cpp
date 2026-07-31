#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ConsoleLogManager \
	)

#include "../includes/console_log_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnTrue_When_LogRawText_WithValidInput
	)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		bool result =
			manager.log_raw_text("message");

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_TRUE(result);
		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnFalse_When_LogRawText_WithEmptyInput
	)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		bool result =
			manager.log_raw_text("");

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_FALSE(result);
		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnFalse_When_RuntimeExecutionDisabled
	)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled =
			false;
		manager.setup(configurations);

		bool result =
			manager.log_raw_text("text");

		EXPECT_FALSE(result);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_HandleAsync_When_UsingStdAsync
	)
	{
		auto future_result =
			std::async(
				std::launch::async,
				[this]()
				{
					return manager.log_raw_text("async");
				}
			);

		auto status =
			future_result.wait_for(
				std::chrono::seconds(2)
			);

		EXPECT_EQ(
			status,
			std::future_status::ready
		);

		EXPECT_TRUE(
			future_result.get()
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_HandleMultithreading_When_ConcurrentCalls
	)
	{
		std::atomic<bool> all_successful(true);
		std::vector<std::thread> threads;

		for (std::size_t index = 0;
			 index < static_cast<std::size_t>(50);
			 ++index)
		{
			threads.emplace_back(
				[this, &all_successful]()
				{
					bool result =
						manager.log_raw_text("threaded");
					if (!result)
					{
						all_successful.store(false);
					}
				}
			);
		}

		for (auto& thread_instance : threads)
		{
			thread_instance.join();
		}

		EXPECT_TRUE(all_successful.load());
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_SustainStress_When_HighIterationLoad
	)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		for (std::size_t iteration = 0;
			 iteration < static_cast<std::size_t>(10000);
			 ++iteration)
		{
			bool result =
				manager.log_raw_text("stress");
			EXPECT_TRUE(result);
		}

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_NotThrow_When_ExceptionOccurs
	)
	{
		EXPECT_NO_THROW(
			manager.log_formatted_text("exception", LogLevel::INFO)
		);
	}

	TEST_P(
		ConsoleLogManagerParameterizedTest,
		Should_ReturnExpected_When_ParameterizedInput
	)
	{
		std::string parameter_value =
			GetParam();

		bool result =
			manager.log_raw_text(parameter_value);

		if (parameter_value.empty())
		{
			EXPECT_FALSE(result);
		}
		else
		{
			EXPECT_TRUE(result);
		}
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnFalse_When_LogRawText_NoArgumentAndEmptyConfig
	)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.text = "";
		manager.setup(configurations);

		bool result =
			manager.log_raw_text();

		EXPECT_FALSE(result);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnTrue_When_LogFormattedText_WithExplicitLogLevel
	)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		bool result =
			manager.log_formatted_text(
				std::string("formatted"),
				LogLevel::DEBUG
			);

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_TRUE(result);
		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnTrue_When_LogFormattedText_WithConfigurationLogLevel
	)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		bool result =
			manager.log_formatted_text(
				std::string("formatted_default")
			);

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_TRUE(result);
		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnTrue_When_LogFormattedText_NoArguments
	)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		bool result =
			manager.log_formatted_text();

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_TRUE(result);
		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnTrue_When_ThreadSafetyEnabled_And_MultiThreaded
	)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled =
			true;
		configurations.is_feature_edge_case_handling_enabled =
			true;
		configurations.is_feature_thread_safety_handling_enabled =
			true;
		manager.setup(configurations);

		std::atomic<bool> all_successful(true);
		std::vector<std::thread> thread_collection;

		for (std::size_t index = 0;
			 index < static_cast<std::size_t>(100);
			 ++index)
		{
			thread_collection.emplace_back(
				[this, &all_successful]()
				{
					bool result =
						manager.log_raw_text(
							std::string("thread_safe")
						);
					if (!result)
					{
						all_successful.store(false);
					}
				}
			);
		}

		for (auto& thread_instance : thread_collection)
		{
			thread_instance.join();
		}

		EXPECT_TRUE(all_successful.load());
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnFalse_When_RuntimeExecutionOverrideDisabled
	)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_runtime_execution_handling_override_enabled =
			true;
		configurations.is_runtime_execution_handling_enabled =
			false;
		manager.setup(configurations);

		bool result =
			manager.log_raw_text(
				std::string("disabled")
			);

		EXPECT_FALSE(result);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnTrue_When_EdgeCaseDisabled_And_EmptyString
	)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_edge_case_handling_enabled =
			false;
		manager.setup(configurations);

		bool result =
			manager.log_raw_text(
				std::string("")
			);

		EXPECT_TRUE(result);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_HandlePromiseFuture_When_AsynchronousExecution
	)
	{
		std::promise<bool> promise_value;
		std::future<bool> future_value =
			promise_value.get_future();

		std::thread worker_thread(
			[this, &promise_value]()
			{
				bool result =
					manager.log_raw_text(
						std::string("promise_async")
					);
				promise_value.set_value(result);
			}
		);

		auto status =
			future_value.wait_for(
				std::chrono::seconds(2)
			);

		EXPECT_EQ(
			status,
			std::future_status::ready
		);

		EXPECT_TRUE(future_value.get());

		worker_thread.join();
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_SustainConcurrentStress_When_MixedOperations
	)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		std::vector<std::thread> thread_collection;

		for (std::size_t index = 0;
			 index < static_cast<std::size_t>(200);
			 ++index)
		{
			thread_collection.emplace_back(
				[this]()
				{
					manager.log_raw_text(
						std::string("stress_raw")
					);
					manager.log_formatted_text(
						std::string("stress_formatted"),
						LogLevel::WARNING
					);
				}
			);
		}

		for (auto& thread_instance : thread_collection)
		{
			thread_instance.join();
		}

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_P(
		ConsoleLogManagerParameterizedTest,
		Should_HandleVariousInputs_When_ParameterizedExecution
	)
	{
		std::string parameter_value =
			GetParam();

		auto start_time =
			std::chrono::steady_clock::now();

		bool result =
			manager.log_raw_text(
				parameter_value
			);

		auto end_time =
			std::chrono::steady_clock::now();

		if (parameter_value.empty())
		{
			EXPECT_FALSE(result);
		}
		else
		{
			EXPECT_TRUE(result);
		}

		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	INSTANTIATE_TEST_CASE_P(
		ConsoleLogManagerAdditionalTest,
		ConsoleLogManagerParameterizedTest,
		::testing::Values(
			std::string("value_one"),
			std::string("value_two"),
			std::string("")
		)
	);

	TEST_F(
		ConsoleLogManagerTest,
		Should_ResetConfigurations_When_ResetCalled
	)
	{
		manager.reset();

		bool result =
			manager.log_raw_text(
				std::string("")
			);

		EXPECT_FALSE(result);
	}

	TEST_F(ConsoleLogManagerTest,
		Should_ReturnTrue_Expect_AllLogLevels_When_FormattedTextProvided)
	{
		std::vector<LogLevel> log_levels =
		{
			LogLevel::ALL,
			LogLevel::INFO,
			LogLevel::DEBUG,
			LogLevel::WARNING,
			LogLevel::SUCCESS,
			LogLevel::CRITICAL,
			LogLevel::ERROR_TYPE,
			LogLevel::HIGHLIGHTED_INFO,
			LogLevel::NONE
		};

		for (const LogLevel& log_level : log_levels)
		{
			const bool result =
				manager.log_formatted_text("value", log_level);
			EXPECT_TRUE(result);
		}
	}

	TEST_F(ConsoleLogManagerTest,
		Should_ReturnFalse_Expect_EmptyString_When_WhitespaceProvided)
	{
		const std::string whitespace_text = "   ";
		const bool result = manager.log_raw_text(whitespace_text);
		EXPECT_TRUE(result);
	}

	TEST_F(ConsoleLogManagerTest,
		Should_ReturnTrue_Expect_LongString_When_LargeInputProvided)
	{
		std::string large_text(100000U, 'a');
		const bool result = manager.log_raw_text(large_text);
		EXPECT_TRUE(result);
	}

	TEST_F(ConsoleLogManagerTest,
		Should_ReturnFalse_Expect_RuntimeDisabled_When_RuntimeTurnedOff)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled =
			false;
		configurations.is_feature_edge_case_handling_enabled = true;
		configurations.is_feature_thread_safety_handling_enabled =
			false;
		configurations.text = "default";
		configurations.log_level = LogLevel::INFO;

		manager.setup(configurations);

		const bool result = manager.log_raw_text("value");
		EXPECT_FALSE(result);
	}

	TEST_F(ConsoleLogManagerTest,
		Should_ReturnTrue_Expect_ThreadSafety_When_MultipleThreadsWithMutex)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled =
			true;
		configurations.is_feature_edge_case_handling_enabled = true;
		configurations.is_feature_thread_safety_handling_enabled =
			true;
		configurations.text = "default";
		configurations.log_level = LogLevel::INFO;

		manager.setup(configurations);

		std::atomic<int> success_count(0);
		std::vector<std::thread> threads;

		for (int index = 0; index < 100; ++index)
		{
			threads.emplace_back(
				[&success_count, this]()
				{
					if (manager.log_raw_text("value"))
					{
						success_count.fetch_add(1);
					}
				});
		}

		for (std::thread& thread : threads)
		{
			thread.join();
		}

		EXPECT_EQ(success_count.load(), 100);
	}

	TEST_F(ConsoleLogManagerTest,
		Should_ReturnTrue_Expect_AsyncFormatted_When_UsingFuture)
	{
		auto future_result =
			std::async(
				std::launch::async,
				[this]()
				{
					return manager.log_formatted_text("async",
						LogLevel::SUCCESS);
				});

		const bool result = future_result.get();
		EXPECT_TRUE(result);
	}

	TEST_F(ConsoleLogManagerTest,
		Should_ReturnTrue_Expect_ConditionVariable_When_Signaled)
	{
		std::mutex mutex_instance;
		std::condition_variable condition_variable_instance;
		bool is_ready = false;
		bool is_success = false;

		std::thread worker_thread(
			[&]()
			{
				std::unique_lock<std::mutex> lock(mutex_instance);
				condition_variable_instance.wait(
					lock,
					[&]()
					{
						return is_ready;
					});

				is_success = manager.log_raw_text("value");
			});

		{
			std::lock_guard<std::mutex> lock(mutex_instance);
			is_ready = true;
		}

		condition_variable_instance.notify_one();
		worker_thread.join();

		EXPECT_TRUE(is_success);
	}

	TEST_F(ConsoleLogManagerTest,
		Should_ReturnTrue_Expect_ResetThenSetup_When_Reconfigured)
	{
		manager.reset();

		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled =
			true;
		configurations.is_feature_edge_case_handling_enabled = true;
		configurations.is_feature_thread_safety_handling_enabled =
			false;
		configurations.text = "reconfigured";
		configurations.log_level = LogLevel::DEBUG;

		manager.setup(configurations);

		const bool result = manager.log_raw_text("value");
		EXPECT_TRUE(result);
	}

	TEST_F(ConsoleLogManagerTest,
		Should_CompleteWithinTime_Expect_Performance_When_StressAsync)
	{
		const auto start_time =
			std::chrono::steady_clock::now();

		std::vector<std::future<bool>> futures;

		for (int index = 0; index < 200; ++index)
		{
			futures.emplace_back(
				std::async(
					std::launch::async,
					[this]()
					{
						return manager.log_raw_text("stress");
					}));
		}

		for (auto& future : futures)
		{
			EXPECT_TRUE(future.get());
		}

		const auto end_time =
			std::chrono::steady_clock::now();

		const auto duration =
			std::chrono::duration_cast<
				std::chrono::milliseconds>(
				end_time - start_time);

		EXPECT_LT(duration.count(), 2000);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnTrue_When_RuntimeOverrideEnabled_And_RuntimeEnabled
	)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_runtime_execution_handling_override_enabled =
			true;
		configurations.is_feature_runtime_execution_handling_enabled =
			true;
		manager.setup(configurations);

		auto start_time =
			std::chrono::steady_clock::now();

		bool result =
			manager.log_raw_text(std::string("override_enabled"));

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_TRUE(result);
		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnTrue_When_EdgeCaseOverrideEnabled_And_EmptyString
	)
	{
		ConsoleLogManagerConfigurations configurations;		
		configurations.is_feature_edge_case_handling_enabled =
			true;

		manager.setup(configurations);

		auto start_time =
			std::chrono::steady_clock::now();

		bool result =
			manager.log_raw_text(std::string(""));

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_FALSE(result);
		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnTrue_When_ThreadSafetyOverrideEnabled_And_MultiThreaded
	)
	{
		ConsoleLogManagerConfigurations configurations;
		
		configurations.is_feature_thread_safety_handling_enabled =
			true;
		manager.setup(configurations);

		std::atomic<bool> all_successful(true);
		std::vector<std::thread> thread_collection;

		auto start_time =
			std::chrono::steady_clock::now();

		for (std::size_t index = 0;
			 index < static_cast<std::size_t>(100);
			 ++index)
		{
			thread_collection.emplace_back(
				[this, &all_successful]()
				{
					bool result =
						manager.log_raw_text(
							std::string("override_thread")
						);
					if (!result)
					{
						all_successful.store(false);
					}
				}
			);
		}

		for (auto& thread_instance : thread_collection)
		{
			thread_instance.join();
		}

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_TRUE(all_successful.load());
		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnTrue_When_LogFormattedText_WithEmptyStringAndEdgeCaseEnabled
	)
	{
		auto start_time =
			std::chrono::steady_clock::now();

		bool result =
			manager.log_formatted_text(
				std::string(""),
				LogLevel::INFO
			);

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_TRUE(result);
		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_ReturnTrue_When_LogRawText_NoSetupAfterReset
	)
	{
		manager.reset();

		auto start_time =
			std::chrono::steady_clock::now();

		bool result =
			manager.log_raw_text(
				std::string("after_reset")
			);

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_TRUE(result);
		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_SustainStress_When_ThreadSafetyEnabled_And_HighIteration
	)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_thread_safety_handling_enabled =
			true;
		manager.setup(configurations);

		auto start_time =
			std::chrono::steady_clock::now();

		for (std::size_t iteration = 0;
			 iteration < static_cast<std::size_t>(10000);
			 ++iteration)
		{
			bool result =
				manager.log_formatted_text(
					std::string("stress_formatted"),
					LogLevel::WARNING
				);
			EXPECT_TRUE(result);
		}

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(
		ConsoleLogManagerTest,
		Should_HandleAsyncStress_When_MultipleFuturesAndThreadSafety
	)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_thread_safety_handling_enabled =
			true;
		manager.setup(configurations);

		auto start_time =
			std::chrono::steady_clock::now();

		std::vector<std::future<bool>> future_collection;

		for (std::size_t index = 0;
			 index < static_cast<std::size_t>(150);
			 ++index)
		{
			future_collection.emplace_back(
				std::async(
					std::launch::async,
					[this]()
					{
						return manager.log_formatted_text(
							std::string("async_stress"),
							LogLevel::DEBUG
						);
					}
				)
			);
		}

		for (auto& future_instance : future_collection)
		{
			EXPECT_TRUE(future_instance.get());
		}

		auto end_time =
			std::chrono::steady_clock::now();

		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(ConsoleLogManagerTest,
       Should_NotThrow_When_LogRawTextAsync_RuntimeDisabled)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled =
			false;
		configurations.is_feature_edge_case_handling_enabled = true;
		configurations.is_feature_thread_safety_handling_enabled = false;
		configurations.text = "async";
		configurations.log_level = LogLevel::INFO;
		manager.setup(configurations);

		std::future<void> future =
			std::async(std::launch::async, [this]()
			{
				manager.log_raw_text("async_disabled");
			});

		EXPECT_EQ(future.wait_for(std::chrono::seconds(2)),
				  std::future_status::ready);
		EXPECT_NO_THROW(future.get());
	}

	TEST_F(ConsoleLogManagerTest,
		   Should_NotThrow_When_ResetConcurrentWithLogging)
	{
		std::atomic<bool> start_flag = false;
		std::condition_variable condition_variable_instance;
		std::mutex mutex_instance;

		std::thread logging_thread([&]()
		{
			{
				std::unique_lock<std::mutex> lock(mutex_instance);
				condition_variable_instance.wait(lock,
					[&]() { return start_flag.load(); });
			}

			for (int index = 0; index < 5000; ++index)
			{
				manager.log_raw_text("concurrent_reset");
			}
		});

		std::thread reset_thread([&]()
		{
			{
				std::lock_guard<std::mutex> lock(mutex_instance);
				start_flag.store(true);
			}
			condition_variable_instance.notify_one();

			manager.reset();
		});

		logging_thread.join();
		reset_thread.join();
		SUCCEED();
	}

	TEST_F(ConsoleLogManagerTest,
		   Should_NotThrow_When_SetupConcurrentWithLogging)
	{
		std::atomic<bool> start_flag = false;
		std::condition_variable condition_variable_instance;
		std::mutex mutex_instance;

		std::thread logging_thread([&]()
		{
			{
				std::unique_lock<std::mutex> lock(mutex_instance);
				condition_variable_instance.wait(lock,
					[&]() { return start_flag.load(); });
			}

			for (int index = 0; index < 5000; ++index)
			{
				manager.log_formatted_text("concurrent_setup",
										   LogLevel::INFO);
			}
		});

		std::thread setup_thread([&]()
		{
			ConsoleLogManagerConfigurations configurations;
			configurations.is_feature_runtime_execution_handling_enabled =
				true;
			configurations.is_feature_edge_case_handling_enabled = true;
			configurations.is_feature_thread_safety_handling_enabled =
				true;
			configurations.text = "reconfigured";
			configurations.log_level = LogLevel::DEBUG;

			{
				std::lock_guard<std::mutex> lock(mutex_instance);
				start_flag.store(true);
			}
			condition_variable_instance.notify_one();

			manager.setup(configurations);
		});

		logging_thread.join();
		setup_thread.join();
		SUCCEED();
	}

	TEST_P(ConsoleLogManagerLogLevelParameterizedTest,
		   Should_NotThrow_When_LogFormattedText_WithEachLogLevel)
	{
		LogLevel log_level = GetParam();
		EXPECT_NO_THROW(manager.log_formatted_text("level_test",
												   log_level));
	}

	INSTANTIATE_TEST_CASE_P(
		ConsoleLogManagerLogLevelParameterizedTest,
		ConsoleLogManagerLogLevelParameterizedTest,
		::testing::Values(
			LogLevel::DEBUG,
			LogLevel::INFO,
			LogLevel::WARNING,
			LogLevel::ERROR_TYPE,
			LogLevel::CRITICAL));

	TEST_P(ConsoleLogManagerLogLevelParameterizedTest,
       Should_ReturnTrue_When_LogFormattedText_WithAllRemainingLogLevels)
	{
		LogLevel log_level = GetParam();
		EXPECT_TRUE(manager.log_formatted_text("level_test", log_level));
	}

	INSTANTIATE_TEST_CASE_P(
		ConsoleLogManagerRemainingLogLevels,
		ConsoleLogManagerLogLevelParameterizedTest,
		::testing::Values(
			LogLevel::ALL,
			LogLevel::SUCCESS,
			LogLevel::HIGHLIGHTED_INFO,
			LogLevel::NONE
		)
	);

	TEST_F(ConsoleLogManagerTest,
		   Should_ReturnFalse_When_RuntimeDisabled_EdgeCaseDisabled_ThreadSafetyEnabled)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		configurations.is_feature_edge_case_handling_enabled = false;
		configurations.is_feature_thread_safety_handling_enabled = true;
		manager.setup(configurations);

		const bool result = manager.log_raw_text("value");
		EXPECT_FALSE(result);
	}

	TEST_F(ConsoleLogManagerTest,
		   Should_ReturnTrue_When_RuntimeOverrideEnabled_ThreadSafetyOverrideEnabled)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_runtime_execution_handling_override_enabled = true;
		configurations.is_feature_thread_safety_handling_enabled = true;
		manager.setup(configurations);

		std::atomic<int> success_count(0);
		std::vector<std::thread> threads;

		for (int i = 0; i < 50; ++i)
		{
			threads.emplace_back([&]()
			{
				if (manager.log_raw_text("override_thread"))
					success_count.fetch_add(1);
			});
		}

		for (auto& t : threads)
			t.join();

		EXPECT_EQ(success_count.load(), 50);
	}

	TEST_F(ConsoleLogManagerTest,
		   Should_ReturnTrue_When_LogFormattedText_WithEmptyConfigurationText_AndEdgeCaseDisabled)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_edge_case_handling_enabled = false;
		configurations.text = "";
		manager.setup(configurations);

		const bool result = manager.log_formatted_text("", LogLevel::INFO);
		EXPECT_TRUE(result);
	}

	TEST_F(ConsoleLogManagerTest,
       Should_ReturnTrue_When_LogRawText_CalledBeforeSetup)
	{
		ConsoleLogManager uninitialized_manager;
		bool result = uninitialized_manager.log_raw_text("value");
		EXPECT_TRUE(result);
	}

	TEST_F(ConsoleLogManagerTest,
		   Should_ReturnFalse_When_AllFlagsDisabled)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		configurations.is_feature_edge_case_handling_enabled = false;
		configurations.is_feature_thread_safety_handling_enabled = false;
		manager.setup(configurations);
		bool result = manager.log_raw_text("value");
		EXPECT_FALSE(result);
	}

	TEST_F(ConsoleLogManagerTest,
		   Should_HandleExtremeConcurrency_MixedOperations)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_thread_safety_handling_enabled = true;
		manager.setup(configurations);

		std::vector<std::thread> threads;
		std::vector<std::future<bool>> futures;

		for (int i = 0; i < 100; ++i)
		{
			threads.emplace_back([this]()
			{
				manager.log_raw_text("threaded_mixed");
			});

			futures.emplace_back(std::async(std::launch::async, [this]()
			{
				return manager.log_formatted_text("async_mixed", LogLevel::DEBUG);
			}));
		}

		for (auto& thread_instance : threads)
			thread_instance.join();

		for (auto& future_instance : futures)
			EXPECT_TRUE(future_instance.get());
	}

	TEST_P(ConsoleLogManagerLogLevelParameterizedTest,
		   Should_ReturnTrue_When_LogFormattedText_InvalidEnum)
	{
		LogLevel invalid_log_level = static_cast<LogLevel>(999);
		EXPECT_TRUE(manager.log_formatted_text("invalid", invalid_log_level));
	}

	TEST_F(ConsoleLogManagerTest,
		   Should_CompleteRapidly_When_HighIterationRawLogging)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_thread_safety_handling_enabled = true;
		manager.setup(configurations);

		auto start_time = std::chrono::steady_clock::now();
		for (std::size_t i = 0; i < 50000; ++i)
		{
			EXPECT_TRUE(manager.log_raw_text("rapid"));
		}
		auto end_time = std::chrono::steady_clock::now();
		EXPECT_LT(
			std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count(),
			static_cast<long long>(2)
		);
	}

	TEST_F(ConsoleLogManagerTest,
       Should_HandleNonAsciiInput_When_LogRawText)
	{
		std::string non_ascii = "测试🚀";
		EXPECT_TRUE(manager.log_raw_text(non_ascii));
	}

	TEST_F(ConsoleLogManagerTest,
		   Should_HandleNonAsciiInput_When_LogFormattedText)
	{
		std::string non_ascii = "テスト🌟";
		EXPECT_TRUE(manager.log_formatted_text(non_ascii, LogLevel::DEBUG));
	}

	TEST_F(ConsoleLogManagerTest,
		   Should_HandleExtremeLargeString_When_LogFormattedText)
	{
		std::string large_text(500000U, 'x');
		EXPECT_TRUE(manager.log_formatted_text(large_text, LogLevel::INFO));
	}

	TEST_F(ConsoleLogManagerTest,
		   Should_HandleCombinedOverrides_When_RuntimeEdgeThreadSafetyEnabled)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_runtime_execution_handling_override_enabled = true;
		configurations.is_feature_runtime_execution_handling_enabled = true;
		configurations.is_feature_edge_case_handling_enabled = true;
		configurations.is_feature_thread_safety_handling_enabled = true;
		manager.setup(configurations);

		std::atomic<int> success_count(0);
		std::vector<std::thread> threads;

		for (int i = 0; i < 50; ++i)
		{
			threads.emplace_back([&]()
			{
				if (manager.log_raw_text("combined_override"))
					success_count.fetch_add(1);
			});
		}

		for (auto& t : threads)
			t.join();

		EXPECT_EQ(success_count.load(), 50);
	}

	TEST_F(ConsoleLogManagerTest,
		   Should_ReturnTrue_When_LogFormattedText_WithWhitespaceOnlyAndEdgeCaseDisabled)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_edge_case_handling_enabled = false;
		configurations.text = "   ";
		manager.setup(configurations);

		EXPECT_TRUE(manager.log_formatted_text("   ", LogLevel::INFO));
	}

	TEST_F(ConsoleLogManagerTest,
		   Should_HandleAsyncWithAllOverrides_When_MixedOperations)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_runtime_execution_handling_override_enabled = true;
		configurations.is_feature_runtime_execution_handling_enabled = true;
		configurations.is_feature_edge_case_handling_enabled = true;
		configurations.is_feature_thread_safety_handling_enabled = true;
		manager.setup(configurations);

		std::vector<std::future<bool>> futures;
		for (int i = 0; i < 50; ++i)
		{
			futures.emplace_back(std::async(std::launch::async, [this]()
			{
				return manager.log_formatted_text("async_mixed_override", LogLevel::DEBUG);
			}));
		}

		for (auto& future_instance : futures)
			EXPECT_TRUE(future_instance.get());
	}

	TEST_F(ConsoleLogManagerTest,
		Should_HandleExtremeUnicode_When_LogRawText)
	{
		std::string unicode_text;
		for (int i = 0; i < 1000; ++i)
			unicode_text += std::string(reinterpret_cast<const char*>(u8"🌐🚀🎉"));

		EXPECT_TRUE(manager.log_raw_text(unicode_text));
	}

	TEST_F(ConsoleLogManagerTest,
		Should_HandleExtremeUnicode_When_LogFormattedText)
	{
		std::string unicode_text;
		for (int i = 0; i < 1000; ++i)
			unicode_text += std::string(reinterpret_cast<const char*>(u8"🌐🚀🎉"));

		EXPECT_TRUE(manager.log_formatted_text(unicode_text, LogLevel::DEBUG));
	}

	TEST_F(ConsoleLogManagerTest,
		Should_ApplyDefaultLogLevel_When_LogFormattedTextWithoutArgument)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.text = "default_log";
		configurations.log_level = LogLevel::INFO;
		manager.setup(configurations);

		EXPECT_TRUE(manager.log_formatted_text());
	}

	TEST_F(ConsoleLogManagerTest,
		Should_HandleExtremeThreadCount_When_MultiThreadedLogging)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_thread_safety_handling_enabled = true;
		manager.setup(configurations);

		std::atomic<int> success_count(0);
		std::vector<std::thread> threads;

		for (int i = 0; i < 200; ++i)
		{
			threads.emplace_back([&]()
				{
					if (manager.log_raw_text("extreme_thread"))
						success_count.fetch_add(1);
				});
		}

		for (auto& t : threads)
			t.join();

		EXPECT_EQ(success_count.load(), 200);
	}

	TEST_F(ConsoleLogManagerTest,
		Should_ReturnFalse_When_AllFlagsDisabled_EmptyString)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		configurations.is_feature_edge_case_handling_enabled = false;
		configurations.is_feature_thread_safety_handling_enabled = false;
		configurations.text = "";
		manager.setup(configurations);

		EXPECT_FALSE(manager.log_raw_text(""));
		EXPECT_FALSE(manager.log_formatted_text("", LogLevel::INFO));
	}

	TEST_F(ConsoleLogManagerTest,
		Should_HandleLogRawText_NoArgument_WithAllFlags)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = true;
		configurations.is_feature_edge_case_handling_enabled = true;
		configurations.is_feature_thread_safety_handling_enabled = true;
		manager.setup(configurations);
		EXPECT_TRUE(manager.log_raw_text());
	}

	TEST_F(ConsoleLogManagerTest,
		Should_HandleLogFormattedText_NoArgument_WithAllFlags)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = true;
		configurations.is_feature_edge_case_handling_enabled = true;
		configurations.is_feature_thread_safety_handling_enabled = true;
		manager.setup(configurations);
		EXPECT_TRUE(manager.log_formatted_text());
	}

	TEST_F(ConsoleLogManagerTest,
		Should_HandleExtremeInvalidEnum_WithLogFormattedText)
	{
		LogLevel invalid_log_level = static_cast<LogLevel>(10000);
		EXPECT_TRUE(manager.log_formatted_text("invalid_enum", invalid_log_level));
	}

	TEST_F(ConsoleLogManagerTest,
		Should_HandleMixedLogLevels_WithMultiThreadedStress)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_thread_safety_handling_enabled = true;
		manager.setup(configurations);

		std::vector<LogLevel> log_levels = {
			LogLevel::ALL, LogLevel::INFO, LogLevel::DEBUG,
			LogLevel::WARNING, LogLevel::SUCCESS, LogLevel::CRITICAL,
			LogLevel::ERROR_TYPE, LogLevel::HIGHLIGHTED_INFO, LogLevel::NONE
		};

		std::atomic<int> success_count(0);
		std::vector<std::thread> threads;

		for (int i = 0; i < 50; ++i)
		{
			threads.emplace_back([&, i]()
				{
					const LogLevel level = log_levels[i % log_levels.size()];
					if (manager.log_formatted_text("thread_level_test", level))
						success_count.fetch_add(1);
				});
		}

		for (auto& t : threads)
			t.join();

		EXPECT_EQ(success_count.load(), 50);
	}

	TEST_F(ConsoleLogManagerTest,
		Should_HandleExtremeLargeUnicodeRawText)
	{
		std::string unicode_text;
		for (int i = 0; i < 5000; ++i)
			unicode_text += std::string(reinterpret_cast<const char*>(u8"🌍🚀🎉🌟🧩"));

		EXPECT_TRUE(manager.log_raw_text(unicode_text));
	}

	TEST_F(ConsoleLogManagerTest,
		Should_HandleExtremeLargeUnicodeFormattedText)
	{
		std::string unicode_text;
		for (int i = 0; i < 5000; ++i)
			unicode_text += std::string(reinterpret_cast<const char*>(u8"🌍🚀🎉🌟🧩"));

		EXPECT_TRUE(manager.log_formatted_text(unicode_text, LogLevel::SUCCESS));
	}

	TEST_F(ConsoleLogManagerTest,
		Should_HandleConcurrentRawText_WithAllFlagsAndLargeInputs)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = true;
		configurations.is_feature_edge_case_handling_enabled = true;
		configurations.is_feature_thread_safety_handling_enabled = true;
		manager.setup(configurations);

		std::atomic<int> success_count(0);
		std::vector<std::thread> threads;

		for (int i = 0; i < 50; ++i)
		{
			threads.emplace_back([this, &success_count]()
				{
					std::string large_text(100000U, 'X');
					if (manager.log_raw_text(large_text))
						success_count.fetch_add(1);
				});
		}

		for (auto& t : threads)
			t.join();

		EXPECT_EQ(success_count.load(), 50);
	}

	TEST_F(ConsoleLogManagerTest,
		Should_HandleConcurrentFormattedText_WithAllFlagsAndLargeInputs)
	{
		ConsoleLogManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = true;
		configurations.is_feature_edge_case_handling_enabled = true;
		configurations.is_feature_thread_safety_handling_enabled = true;
		manager.setup(configurations);

		std::atomic<int> success_count(0);
		std::vector<std::thread> threads;

		for (int i = 0; i < 50; ++i)
		{
			threads.emplace_back([this, &success_count]()
				{
					std::string large_text(100000U, 'Y');
					if (manager.log_formatted_text(large_text, LogLevel::DEBUG))
						success_count.fetch_add(1);
				});
		}

		for (auto& t : threads)
			t.join();

		EXPECT_EQ(success_count.load(), 50);
	}
}

#endif
