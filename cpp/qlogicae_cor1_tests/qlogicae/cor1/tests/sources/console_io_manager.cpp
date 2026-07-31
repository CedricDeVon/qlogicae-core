#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ConsoleIoManager \
	)

#include "../includes/console_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(
		ConsoleIoManagerTest,
		Should_ReturnTrue_When_ConstructCalled
	)
	{
		EXPECT_TRUE(
			manager.construct()
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_ReturnTrue_When_DestructCalled
	)
	{
		EXPECT_TRUE(
			manager.destruct()
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_ReturnEmptyString_When_ScanWithNoInput
	)
	{
		std::istringstream
			input_stream("");

		std::cin.rdbuf(
			input_stream.rdbuf()
		);

		std::string
			result =
			manager.scan();

		EXPECT_TRUE(
			result.empty()
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_ReturnValue_When_BuiltinScanReceivesInput
	)
	{
		std::istringstream
			input_stream("value");

		std::cin.rdbuf(
			input_stream.rdbuf()
		);

		std::string
			result =
			manager.builtin_scan();

		EXPECT_EQ(
			result,
			"value"
		);
	}

	TEST_P(
		ConsoleIoManagerPrintParameterizedTest,
		Should_ReturnTrue_When_PrintCalled
	)
	{
		EXPECT_TRUE(
			manager.print(
				GetParam()
			)
		);
	}

	TEST_P(
		ConsoleIoManagerPrintParameterizedTest,
		Should_ReturnTrue_When_PrintWithNewLineCalled
	)
	{
		EXPECT_TRUE(
			manager.print_with_new_line(
				GetParam()
			)
		);
	}

	TEST_P(
		ConsoleIoManagerPrintParameterizedTest,
		Should_ReturnTrue_When_BuiltinPrintCalled
	)
	{
		EXPECT_TRUE(
			manager.builtin_print(
				GetParam()
			)
		);
	}

	TEST_P(
		ConsoleIoManagerPrintParameterizedTest,
		Should_ReturnTrue_When_BuiltinPrintWithNewLineCalled
	)
	{
		EXPECT_TRUE(
			manager.builtin_print_with_new_line(
				GetParam()
			)
		);
	}

	INSTANTIATE_TEST_CASE_P(
		ConsoleIoManagerPrintValues,
		ConsoleIoManagerPrintParameterizedTest,
		::testing::Values(
			std::string(""),
			std::string("a"),
			std::string("test"),
			std::string(1000, 'x')
		)
	);

	TEST_F(
		ConsoleIoManagerTest,
		Should_BeThreadSafe_When_MultipleThreadsPrint
	)
	{
		std::atomic<bool>
			execution_successful(true);

		std::vector<std::thread>
			threads;

		for (std::size_t index = 0;
			index < 32;
			++index)
		{
			threads.emplace_back(
				[&]()
				{
					if (!manager.print("thread"))
					{
						execution_successful =
							false;
					}
				}
			);
		}

		for (std::thread&
			current_thread : threads)
		{
			current_thread.join();
		}

		EXPECT_TRUE(
			execution_successful
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_CompleteAsync_When_UsingStdAsync
	)
	{
		std::future<bool>
			future_result =
			std::async(
				std::launch::async,
				[&]()
				{
					return
						manager.print(
							"async"
						);
				}
			);

		EXPECT_TRUE(
			future_result.get()
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_HandleStressLoad_When_RepeatedCalls
	)
	{
		for (std::size_t index = 0;
			index < 100000;
			++index)
		{
			EXPECT_TRUE(
				manager.print("x")
			);
		}
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_ResetConfigurations_When_ResetCalled
	)
	{
		ConsoleIoManagerConfigurations
			new_configurations;

		new_configurations
			.is_thread_safety_handling_override_enabled =
			true;

		EXPECT_TRUE(
			manager.setup(
				new_configurations
			)
		);

		EXPECT_TRUE(
			manager.reset()
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_HandleConcurrentAsyncCalls_When_MixedOperations
	)
	{
		std::vector<std::future<bool>>
			futures;

		for (std::size_t index = 0;
			index < 16;
			++index)
		{
			futures.emplace_back(
				std::async(
					std::launch::async,
					[&]()
					{
						return
							manager.print_with_new_line(
								"mixed"
							);
					}
				)
			);
		}

		for (std::future<bool>&
			current_future : futures)
		{
			EXPECT_TRUE(
				current_future.get()
			);
		}
	}


	TEST_F(
		ConsoleIoManagerTest,
		Should_RemoveCarriageReturn_When_ScanEndsWithCarriageReturn
	)
	{
		std::istringstream
			input_stream(
				std::string("value\r\n")
			);

		std::cin.rdbuf(
			input_stream.rdbuf()
		);

		std::string
			result =
			manager.scan();

		EXPECT_EQ(
			result,
			"value"
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_ReadSingleToken_When_BuiltinScanHasSpaces
	)
	{
		std::istringstream
			input_stream(
				std::string("first second")
			);

		std::cin.rdbuf(
			input_stream.rdbuf()
		);

		std::string
			result =
			manager.builtin_scan();

		EXPECT_EQ(
			result,
			"first"
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_DisableUtilityMutex_When_ThreadSafetyDisabled
	)
	{
		ConsoleIoManagerConfigurations
			configurations;

		configurations
			.is_utility_thread_safety_handling_enabled =
			false;

		EXPECT_TRUE(
			manager.setup(
				configurations
			)
		);

		EXPECT_TRUE(
			manager.construct()
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_ForceUtilityMutex_When_OverrideEnabled
	)
	{
		ConsoleIoManagerConfigurations
			configurations;

		configurations
			.is_utility_thread_safety_handling_enabled =
			false;

		configurations
			.is_thread_safety_handling_override_enabled =
			true;

		EXPECT_TRUE(
			manager.setup(
				configurations
			)
		);

		EXPECT_TRUE(
			manager.construct()
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_DisableFeatureMutex_When_FeatureThreadSafetyDisabled
	)
	{
		ConsoleIoManagerConfigurations
			configurations;

		configurations
			.is_feature_thread_safety_handling_enabled =
			false;

		EXPECT_TRUE(
			manager.setup(
				configurations
			)
		);

		EXPECT_TRUE(
			manager.print(
				"test"
			)
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_EnableFeatureMutex_When_FeatureThreadSafetyEnabled
	)
	{
		ConsoleIoManagerConfigurations
			configurations;

		configurations
			.is_feature_thread_safety_handling_enabled =
			true;

		EXPECT_TRUE(
			manager.setup(
				configurations
			)
		);

		EXPECT_TRUE(
			manager.print(
				"test"
			)
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_HandleErrorPath_When_OutputStreamFails
	)
	{
		std::ostringstream
			failed_stream;

		failed_stream.setstate(
			std::ios::badbit
		);

		std::cout.rdbuf(
			failed_stream.rdbuf()
		);

		EXPECT_TRUE(
			manager.builtin_print(
				"text"
			)
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_HandleErrorMutex_When_ErrorThreadSafetyEnabled
	)
	{
		ConsoleIoManagerConfigurations
			configurations;

		configurations
			.is_error_thread_safety_handling_enabled =
			true;

		EXPECT_TRUE(
			manager.setup(
				configurations
			)
		);

		ASSERT_THROW(
			manager.handle_error_outputs(
				std::runtime_error(
					"error"
				)
			),
			std::runtime_error
		);
	}

	TEST_F(
		ConsoleIoManagerTest,
		Should_HandleConcurrentMixedOperations_When_ThreadSafetyToggled
	)
	{
		ConsoleIoManagerConfigurations
			configurations;

		configurations
			.is_feature_thread_safety_handling_enabled =
			true;

		EXPECT_TRUE(
			manager.setup(
				configurations
			)
		);

		std::vector<std::thread>
			threads;

		std::atomic<bool>
			success(true);

		for (std::size_t index = 0;
			index < 64;
			++index)
		{
			threads.emplace_back(
				[&]()
				{
					if (!manager.print_with_new_line("x"))
					{
						success =
							false;
					}
				}
			);
		}

		for (std::thread&
			thread : threads)
		{
			thread.join();
		}

		EXPECT_TRUE(
			success
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_ErrorOutputs_String)
	{
		ASSERT_THROW(
			manager.handle_error_outputs(
				std::string("error")
			),
			std::runtime_error
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_ErrorOutputs_TitleAndMessage)
	{
		ASSERT_THROW(
			manager.handle_error_outputs(
				std::string("title"),
				std::string("message")
			),
			std::runtime_error
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_ErrorOutputs_When_ThreadSafetyDisabled)
	{
		manager.configurations.is_error_thread_safety_handling_enabled =
			false;

		ASSERT_THROW(
			manager.handle_error_outputs(
				std::string("error")
			),
			std::runtime_error
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_ErrorOutputs_During_ConstructAndDestruct)
	{
		manager.destruct();
		manager.construct();

		ASSERT_THROW(
			manager.handle_error_outputs(
				std::string("error")
			),
			std::runtime_error
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Scan_When_Eof)
	{
		std::istringstream input;
		std::cin.rdbuf(
			input.rdbuf()
		);

		auto result =
			manager.scan();

		EXPECT_TRUE(
			result.empty()
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Consecutive_Scan_After_Eof)
	{
		std::istringstream input;
		std::cin.rdbuf(
			input.rdbuf()
		);

		manager.scan();

		auto result =
			manager.scan();

		EXPECT_TRUE(
			result.empty()
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Scan_When_FeatureThreadSafetyDisabled)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled =
			false;

		std::istringstream input("value");
		std::cin.rdbuf(
			input.rdbuf()
		);

		auto result =
			manager.scan();

		EXPECT_EQ(
			result,
			"value"
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Print_Failure_Path)
	{
		std::ostringstream output;
		output.setstate(
			std::ios::badbit
		);

		std::cout.rdbuf(
			output.rdbuf()
		);

		manager.print(
			"test"
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_PrintWithNewLine_Failure_Path)
	{
		std::ostringstream output;
		output.setstate(
			std::ios::badbit
		);

		std::cout.rdbuf(
			output.rdbuf()
		);

		manager.print_with_new_line(
			"test"
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Not_Deadlock_With_Mixed_Builtin_And_Print)
	{
		std::thread t1(
			[this]()
			{
				manager.builtin_print(
					"a"
				);
			}
		);

		std::thread t2(
			[this]()
			{
				manager.print(
					"b"
				);
			}
		);

		t1.join();
		t2.join();
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Override_Disabling_ThreadSafety)
	{
		manager.configurations.is_thread_safety_handling_override_enabled =
			false;

		manager.configurations.is_utility_thread_safety_handling_enabled =
			false;

		manager.print(
			"test"
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Evaluate_All_ThreadSafety_Flags)
	{
		EXPECT_NO_THROW(
			manager.configurations.is_thread_safety_enabled_for_utility_handling()
		);

		EXPECT_NO_THROW(
			manager.configurations.is_thread_safety_enabled_for_feature_handling()
		);

		EXPECT_NO_THROW(
			manager.configurations.is_thread_safety_enabled_for_error_handling()
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Async_Builtin_Print)
	{
		auto future =
			std::async(
				std::launch::async,
				[this]()
				{
					manager.builtin_print(
						"async"
					);
				}
			);

		future.get();
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Async_Scan)
	{
		std::istringstream input("value");
		std::cin.rdbuf(
			input.rdbuf()
		);

		auto future =
			std::async(
				std::launch::async,
				[this]()
				{
					return manager.scan();
				}
			);

		EXPECT_EQ(
			future.get(),
			"value"
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Reset_During_Concurrent_Io)
	{
		std::thread t1(
			[this]()
			{
				manager.print(
					"a"
				);
			}
		);

		std::thread t2(
			[this]()
			{
				manager.reset();
			}
		);

		t1.join();
		t2.join();
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Stress_With_Configuration_Toggling)
	{
		for (size_t i = 0; i < 10000; ++i)
		{
			manager.configurations.is_feature_thread_safety_handling_enabled =
				(i % 2) == 0;

			manager.print(
				"x"
			);
		}
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Repeated_Construct_Destruct)
	{
		for (size_t i = 0; i < 1000; ++i)
		{
			manager.destruct();
			manager.construct();
		}
	}

	INSTANTIATE_TEST_CASE_P(
		ConsoleIoManagerParameterizedScan,
		ConsoleIoManagerPrintParameterizedTest,
		::testing::Values(
			"",
			"a",
			"multiple words",
			"123"
		)
	);

	TEST_P(ConsoleIoManagerPrintParameterizedTest, Should_Handle_Scan_Parameterized)
	{
		std::istringstream input(
			GetParam()
		);

		std::cin.rdbuf(
			input.rdbuf()
		);

		EXPECT_EQ(
			manager.scan(),
			GetParam()
		);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_ExtremelyLargeInput_ForScan)
	{
		std::string large_input(1000000, 'x');
		std::istringstream input_stream(large_input);
		std::cin.rdbuf(input_stream.rdbuf());

		auto result = manager.scan();
		EXPECT_EQ(result.size(), large_input.size());
		EXPECT_EQ(result, large_input);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_ExtremelyLargeInput_ForBuiltinScan)
	{
		std::string large_input(1000000, 'y');
		std::istringstream input_stream(large_input);
		std::cin.rdbuf(input_stream.rdbuf());

		auto result = manager.builtin_scan();
		EXPECT_EQ(result.size(), large_input.size());
		EXPECT_EQ(result, large_input);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Concurrent_ScanAndPrint)
	{
		std::string scan_input = "concurrent";
		std::istringstream input_stream(scan_input);
		std::cin.rdbuf(input_stream.rdbuf());

		std::atomic<bool> success(true);
		std::thread t1([&]() { if (manager.scan() != scan_input) success = false; });
		std::thread t2([&]() { if (!manager.print("output")) success = false; });
		std::thread t3([&]() { if (!manager.print_with_new_line("output")) success = false; });

		t1.join();
		t2.join();
		t3.join();

		EXPECT_TRUE(success);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Boundary_NumericConversions)
	{
		std::string numeric_min = std::to_string(std::numeric_limits<int>::min());
		std::string numeric_max = std::to_string(std::numeric_limits<int>::max());

		std::istringstream input_min(numeric_min);
		std::cin.rdbuf(input_min.rdbuf());
		EXPECT_EQ(manager.scan(), numeric_min);

		std::istringstream input_max(numeric_max);
		std::cin.rdbuf(input_max.rdbuf());
		EXPECT_EQ(manager.scan(), numeric_max);
	}

	TEST_F(ConsoleIoManagerTest, Should_Persist_Configuration_AcrossRepeatedResets)
	{
		ConsoleIoManagerConfigurations conf;
		conf.is_feature_thread_safety_handling_enabled = true;
		conf.is_utility_thread_safety_handling_enabled = true;

		for (size_t i = 0; i < 10; ++i)
		{
			EXPECT_TRUE(manager.setup(conf));
			EXPECT_TRUE(manager.reset());
			EXPECT_TRUE(manager.construct());
			EXPECT_TRUE(manager.destruct());
		}
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_ExtremeConcurrency_Stress)
	{
		std::atomic<bool> success(true);
		std::vector<std::thread> threads;

		for (size_t i = 0; i < 1024; ++i)
		{
			threads.emplace_back([&]()
				{
					for (size_t j = 0; j < 1000; ++j)
					{
						if (!manager.print("x"))
							success = false;
					}
				});
		}

		for (auto& t : threads) t.join();
		EXPECT_TRUE(success);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Async_Print_With_BadStream)
	{
		std::ostringstream output;
		output.setstate(std::ios::badbit);
		std::cout.rdbuf(output.rdbuf());

		auto future = std::async(std::launch::async, [&]()
			{
				return manager.print("async bad");
			});

		EXPECT_TRUE(future.get());
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Threaded_Print_With_BadStream)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled =
			true;

		std::ostringstream output;
		output.setstate(std::ios::badbit);
		std::cout.rdbuf(output.rdbuf());

		std::vector<std::thread> threads;
		std::atomic<bool> success(true);

		for (size_t i = 0; i < 16; ++i)
		{
			threads.emplace_back([&]()
				{
					if (!manager.print("x"))
						success = false;
				});
		}

		for (auto& t : threads) t.join();
		EXPECT_TRUE(success);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_MinMax_Numeric_Output)
	{
		int min_value = std::numeric_limits<int>::min();
		int max_value = std::numeric_limits<int>::max();

		EXPECT_TRUE(manager.print(std::to_string(min_value)));
		EXPECT_TRUE(manager.print(std::to_string(max_value)));
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Extremely_Large_Input_Scan)
	{
		std::string large_input(1'000'000, 'x');
		std::istringstream input(large_input);
		std::cin.rdbuf(input.rdbuf());

		auto result = manager.scan();

		EXPECT_EQ(result.size(), large_input.size());
		EXPECT_EQ(result, large_input);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Extremely_Large_Input_BuiltinScan)
	{
		std::string large_input(1'000'000, 'y');
		std::istringstream input(large_input);
		std::cin.rdbuf(input.rdbuf());

		auto result = manager.builtin_scan();

		EXPECT_EQ(result.size(), large_input.size());
		EXPECT_EQ(result, large_input);
	}

	TEST_F(ConsoleIoManagerTest, Should_Handle_Exception_Propagation_From_Scan)
	{
		std::istringstream input;
		std::cin.rdbuf(input.rdbuf());
		EXPECT_NO_THROW(manager.scan());
		EXPECT_NO_THROW(manager.builtin_scan());
	}
}

#endif
