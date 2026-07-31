#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ErrorManager \
	)

#include "../includes/error_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{    
	TEST_F(ErrorManagerTest,
		Should_ConstructSuccessfully_When_Created)
	{
		bool result =
			manager.construct();

		EXPECT_TRUE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleSynchronously_When_AsynchronousDisabled)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			false;

		configurations.is_runtime_throw_output_enabled =
			false;

		configurations.is_asynchronous_output_enabled =
			false;

		manager.setup(
			configurations
		);

		bool result =
			manager.handle_error_outputs(
				"title",
				"message"
			);

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleAsynchronously_When_AsynchronousEnabled)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			true;

		configurations.is_asynchronous_output_enabled =
			true;

		manager.setup(
			configurations
		);

		bool result =
			manager.handle_error_outputs(
				"message"
			);

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_NotHandle_When_Disabled)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			false;

		configurations.is_runtime_throw_output_enabled =
			false;

		manager.setup(
			configurations
		);

		bool result =
			manager.handle_error_outputs(
				"message"
			);

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_ThrowRuntimeError_When_RuntimeThrowEnabled)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			true;

		configurations.is_asynchronous_output_enabled =
			false;

		configurations.is_runtime_throw_output_enabled =
			true;

		manager.setup(
			configurations
		);

		EXPECT_THROW(
			manager.handle_error_outputs(
				"message"
			),
			std::runtime_error
		);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleExceptionInput_When_ExceptionPassed)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			false;

		configurations.is_runtime_throw_output_enabled =
			false;

		manager.setup(
			configurations
		);

		try
		{
			throw std::logic_error(
				"failure"
			);
		}
		catch (
			const std::exception&
			exception
			)
		{
			bool result =
				manager.handle_error_outputs(
					exception
				);

			EXPECT_FALSE(result);
		}
	}

	TEST_F(ErrorManagerTest,
		Should_BeThreadSafe_When_MultipleThreadsInvokeHandle)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			true;

		configurations.is_asynchronous_output_enabled =
			true;

		manager.setup(
			configurations
		);

		std::atomic<bool>
			completed =
			false;

		std::thread worker_thread(
			[&]()
			{
				for (
					std::size_t iteration_index = 0;
					iteration_index < 1000;
					iteration_index++
					)
				{
					manager.handle_error_outputs(
						"message"
					);
				}

				completed.store(
					true
				);
			}
		);

		worker_thread.join();

		EXPECT_TRUE(
			completed.load()
		);
	}

	TEST_P(ErrorManagerParameterizedTest,
		Should_HandleCorrectly_When_AsynchronousFlagVaries)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			false;

		configurations.is_runtime_throw_output_enabled =
			false;

		configurations.is_asynchronous_output_enabled =
			GetParam();

		manager.setup(
			configurations
		);

		bool result =
			manager.handle_error_outputs(
				"message"
			);

		EXPECT_FALSE(result);
	}

	INSTANTIATE_TEST_CASE_P(
		ErrorManagerAsyncVariants,
		ErrorManagerParameterizedTest,
		::testing::Values(
			true,
			false
		)
	);

	TEST_F(ErrorManagerTest,
		Should_HandleConcurrentContention_When_FourThreadsInvoke)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			true;

		configurations.is_thread_safety_handling_override_enabled =
			true;

		configurations.is_asynchronous_output_enabled =
			true;

		manager.setup(
			configurations
		);

		std::atomic<std::size_t>
			completed_count =
			0;

		auto worker =
			[&]()
			{
				for (
					std::size_t iteration_index = 0;
					iteration_index < 500;
					iteration_index++
					)
				{
					manager.handle_error_outputs(
						"message"
					);
				}

				completed_count.fetch_add(
					static_cast<std::size_t>(1)
				);
			};

		std::thread first_thread(worker);
		std::thread second_thread(worker);
		std::thread third_thread(worker);
		std::thread fourth_thread(worker);

		first_thread.join();
		second_thread.join();
		third_thread.join();
		fourth_thread.join();

		EXPECT_EQ(
			completed_count.load(),
			static_cast<std::size_t>(4)
		);
	}

	TEST_F(ErrorManagerTest,
		Should_CaptureAsyncException_When_RuntimeThrowEnabledAsync)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			true;

		configurations.is_asynchronous_output_enabled =
			true;

		configurations.is_asynchronous_runtime_throw_output_enabled =
			true;

		configurations.is_runtime_throw_output_enabled =
			true;

		manager.setup(
			configurations
		);

		EXPECT_THROW(
			manager.handle_error_outputs(
				"async_exception"
			),
			std::runtime_error
		);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleInvalidFilePath_When_FileOutputEnabled)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			false;

		configurations.is_file_output_enabled =
			true;

		configurations.is_runtime_throw_output_enabled =
			false;

		configurations.full_file_output_paths =
		{
			std::string(4096, '\0')
		};

		manager.setup(
			configurations
		);

		bool result =
			manager.handle_error_outputs(
				"invalid_path"
			);

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleEmptyMessage_When_MessageIsEmpty)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			false;

		configurations.is_runtime_throw_output_enabled =
			false;

		manager.setup(
			configurations
		);

		bool result =
			manager.handle_error_outputs(
				""
			);

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleVeryLargeMessage_When_MessageIsLarge)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			false;

		configurations.is_runtime_throw_output_enabled =
			false;

		manager.setup(
			configurations
		);

		std::string
			large_message(
				static_cast<std::size_t>(1000),
				'A'
			);

		bool result =
			manager.handle_error_outputs(
				large_message
			);

		EXPECT_FALSE(result);
	}

	TEST_P(ErrorManagerConfigurationMatrixTest,
		Should_HandleConfigurationMatrix_When_ParametersVary)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			std::get<0>(GetParam());

		configurations.is_runtime_throw_output_enabled =
			std::get<1>(GetParam());

		manager.setup(
			configurations
		);

		if (configurations.is_enable_output_override_enabled ||
			configurations.is_runtime_throw_output_enabled)
		{
			EXPECT_THROW(
				manager.handle_error_outputs(
					"matrix"
				),
				std::runtime_error
			);
		}
		else
		{
			bool result =
				manager.handle_error_outputs(
					"matrix"
				);

			EXPECT_FALSE(result);
		}
	}

	INSTANTIATE_TEST_CASE_P(
		ErrorManagerConfigurationMatrix,
		ErrorManagerConfigurationMatrixTest,
		::testing::Values(
			std::make_tuple(false, false),
			std::make_tuple(true, false),
			std::make_tuple(false, true),
			std::make_tuple(true, true)
		)
	);

	TEST_F(ErrorManagerTest,
		Should_ReturnSameInstance_When_GettingSingletonMultipleTimes)
	{
		ErrorManager&
			first_reference =
			manager;

		ErrorManager&
			second_reference =
			manager;

		EXPECT_EQ(
			&first_reference,
			&second_reference
		);
	}

	TEST_F(ErrorManagerTest,
		Should_NotCrash_When_ResetAndSetupRaceOccurs)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			true;

		std::atomic<bool>
			completed =
			false;

		std::thread setup_thread(
			[&]()
			{
				for (
					std::size_t iteration_index = 0;
					iteration_index < 500;
					iteration_index++
					)
				{
					manager.setup(
						configurations
					);
				}
			}
		);

		std::thread reset_thread(
			[&]()
			{
				for (
					std::size_t iteration_index = 0;
					iteration_index < 500;
					iteration_index++
					)
				{
					manager.reset();
				}

				completed.store(
					true
				);
			}
		);

		setup_thread.join();
		reset_thread.join();

		EXPECT_TRUE(
			completed.load()
		);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleReentrantCalls_When_HandleIsCalledRecursively)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			true;

		manager.setup(
			configurations
		);

		std::function<void(std::size_t)>
			recursive_handle;

		recursive_handle =
			[&](std::size_t depth)
			{
				if (depth == 0)
				{
					return;
				}

				manager.handle_error_outputs(
					"reentrant"
				);

				recursive_handle(
					depth - 1
				);
			};

		bool result =
			false;

		try
		{
			recursive_handle(
				static_cast<std::size_t>(10)
			);
		}
		catch (...)
		{
			result =
				false;
		}

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_ThrowAsyncRuntimeError_When_AsyncAndRuntimeThrowEnabled)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled =
			true;

		configurations.is_asynchronous_output_enabled =
			true;

		configurations.is_asynchronous_runtime_throw_output_enabled =
			true;

		configurations.is_runtime_throw_output_enabled =
			true;

		manager.setup(
			configurations
		);

		EXPECT_THROW(
			manager.handle_error_outputs(
				"async_runtime_throw"
			),
			std::runtime_error
		);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleGuiOutput_When_GuiEnabled)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled = false;
		configurations.is_gui_output_enabled = true;
		configurations.is_asynchronous_gui_output_enabled = false;
		configurations.is_runtime_throw_output_enabled = false;

		manager.setup(configurations);

		bool result = manager.handle_error_outputs("gui_message");

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleAsyncGuiOutput_When_AsynchronousGuiEnabled)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled = false;
		configurations.is_gui_output_enabled = true;
		configurations.is_asynchronous_gui_output_enabled = false;
		configurations.is_asynchronous_output_enabled = true;
		configurations.is_runtime_throw_output_enabled = false;

		manager.setup(configurations);

		bool result = manager.handle_error_outputs("async_gui_message");

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleMultipleFilePaths_When_FileOutputEnabled)
	{
		std::vector<std::string> temp_paths;
		for (int i = 0; i < 2; ++i)
		{
			std::string file_path = "temp_error_" + std::to_string(i) + ".log";
			std::ofstream(file_path).close();
			temp_paths.push_back(file_path);
		}

		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled = false;
		configurations.is_file_output_enabled = true;
		configurations.full_file_output_paths = temp_paths;
		configurations.is_runtime_throw_output_enabled = false;

		manager.setup(configurations);

		bool result = manager.handle_error_outputs("file_message");

		EXPECT_FALSE(result);

		for (const std::string& path : temp_paths)
		{
			std::filesystem::remove(path);
		}
	}

	TEST_F(ErrorManagerTest,
		Should_HandleInternalExceptionsDuringConstruct)
	{
		struct FaultyConfigurations : ErrorManagerConfigurations
		{
			FaultyConfigurations()
			{
				is_enable_output_override_enabled = true;
			}
		};

		bool result = manager.construct();

		EXPECT_TRUE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleInternalExceptionsDuringSetup)
	{
		struct FaultyConfigurations : ErrorManagerConfigurations
		{
			FaultyConfigurations()
			{
				is_enable_output_override_enabled = true;
			}
		};

		ErrorManagerConfigurations configurations = FaultyConfigurations();

		bool result = manager.setup(configurations);

		EXPECT_TRUE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleInternalExceptionsDuringDestruct)
	{
		struct FaultyConfigurations : ErrorManagerConfigurations
		{
			FaultyConfigurations()
			{
				is_enable_output_override_enabled = true;
			}
		};

		ErrorManagerConfigurations configurations = FaultyConfigurations();

		bool result = manager.destruct();

		EXPECT_TRUE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleInternalExceptionsDuringReset)
	{
		struct FaultyConfigurations : ErrorManagerConfigurations
		{
			FaultyConfigurations()
			{
				is_enable_output_override_enabled = true;
			}
		};

		ErrorManagerConfigurations configurations = FaultyConfigurations();

		bool result = manager.reset();

		EXPECT_TRUE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_UpdateCacheVariablesCorrectly_AfterHandle)
	{
		ErrorManagerConfigurations configurations;

		configurations.is_enable_output_override_enabled = false;
		configurations.is_runtime_throw_output_enabled = false;
		configurations.is_asynchronous_output_enabled = false;

		manager.setup(configurations);

		EXPECT_FALSE(manager.handle_error_outputs("cache_test"));
	}

	TEST_F(ErrorManagerTest,
		Should_HandleTitleAndMessageCorrectly)
	{
		ErrorManagerConfigurations configurations;
		configurations.is_enable_output_override_enabled = false;
		configurations.is_runtime_throw_output_enabled = false;
		configurations.is_asynchronous_output_enabled = false;
		manager.setup(configurations);

		bool result =
			manager.handle_error_outputs(
				"ErrorTitle",
				"ErrorMessage"
			);

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleGUIOutputWhenEnabled)
	{
		ErrorManagerConfigurations configurations;
		configurations.is_enable_output_override_enabled = false;
		configurations.is_gui_output_enabled = true;
		configurations.is_asynchronous_gui_output_enabled = false;
		configurations.is_runtime_throw_output_enabled = false;
		manager.setup(configurations);

		bool result =
			manager.handle_error_outputs(
				"GUI message"
			);

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleGUIOutputAsyncWhenEnabled)
	{
		ErrorManagerConfigurations configurations;
		configurations.is_enable_output_override_enabled = true;
		configurations.is_gui_output_enabled = true;
		configurations.is_asynchronous_gui_output_enabled = true;
		configurations.is_runtime_throw_output_enabled = false;
		configurations.is_asynchronous_output_enabled = true;
		manager.setup(configurations);

		bool result =
			manager.handle_error_outputs(
				"GUI async message"
			);

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_CreateFile_When_FileDoesNotExist)
	{
		std::string file_path = "temp_missing_file.log";
		std::filesystem::remove(file_path);

		ErrorManagerConfigurations configurations;
		configurations.is_enable_output_override_enabled = false;
		configurations.is_file_output_enabled = true;
		configurations.full_file_output_paths = { file_path };
		configurations.is_runtime_throw_output_enabled = false;

		manager.setup(configurations);

		bool result = manager.handle_error_outputs("missing_file_test");

		EXPECT_FALSE(result);
		std::filesystem::remove(file_path);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleMessageWithSpecialCharacters)
	{
		ErrorManagerConfigurations configurations;
		configurations.is_enable_output_override_enabled = false;
		configurations.is_runtime_throw_output_enabled = false;
		configurations.is_asynchronous_output_enabled = false;

		manager.setup(configurations);

		std::string special_message = "Line1\nLine2\tUnicode: \u03A9";
		bool result = manager.handle_error_outputs(special_message);

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleExtremelyLargeMessage)
	{
		ErrorManagerConfigurations configurations;
		configurations.is_enable_output_override_enabled = false;
		configurations.is_runtime_throw_output_enabled = false;
		configurations.is_asynchronous_output_enabled = false;

		manager.setup(configurations);

		std::string very_large_message(static_cast<std::size_t>(10000), 'X');
		bool result = manager.handle_error_outputs(very_large_message);

		EXPECT_FALSE(result);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleRecursiveAsyncCallsUnderConcurrency)
	{
		ErrorManagerConfigurations configurations;
		configurations.is_enable_output_override_enabled = true;
		configurations.is_asynchronous_output_enabled = true;
		configurations.is_asynchronous_runtime_throw_output_enabled = false;
		configurations.is_runtime_throw_output_enabled = false;

		manager.setup(configurations);

		auto recursive_async_handle = [&](std::size_t depth, auto& self)
			{
				if (depth == 0) return;
				manager.handle_error_outputs("recursive_async");
				self(depth - 1, self);
			};

		std::thread thread1([&]() { recursive_async_handle(50, recursive_async_handle); });
		std::thread thread2([&]() { recursive_async_handle(50, recursive_async_handle); });

		thread1.join();
		thread2.join();

		EXPECT_TRUE(true);
	}

	TEST_F(ErrorManagerTest,
		Should_HandleAsyncFileExceptionPropagation)
	{
		std::string invalid_file_path = "\0_invalid_path.log";
		ErrorManagerConfigurations configurations;
		configurations.is_enable_output_override_enabled = true;
		configurations.is_file_output_enabled = true;
		configurations.is_asynchronous_output_enabled = true;
		configurations.full_file_output_paths = { invalid_file_path };
		configurations.is_runtime_throw_output_enabled = false;

		manager.setup(configurations);

		bool result = manager.handle_error_outputs("async_file_exception");
		EXPECT_FALSE(result);
	}

	TEST_F(
		ErrorManagerTest,
		Should_ReturnFalse_When_UtilityRuntimeExecutionDisabled_OnConstruct
	)
	{
		ErrorManagerConfigurations configurations;

		configurations
			.is_feature_runtime_execution_handling_enabled =
				false;

		manager.setup(
			configurations
		);

		bool result =
			manager.construct();

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		ErrorManagerTest,
		Should_ReturnFalse_When_UtilityRuntimeExecutionDisabled_OnDestruct
	)
	{
		ErrorManagerConfigurations configurations;

		configurations
			.is_feature_runtime_execution_handling_enabled =
				false;

		manager.setup(
			configurations
		);

		bool result =
			manager.destruct();

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		ErrorManagerTest,
		Should_ReturnFalse_When_UtilityRuntimeExecutionDisabled_OnReset
	)
	{
		ErrorManagerConfigurations configurations;

		configurations
			.is_feature_runtime_execution_handling_enabled =
				false;

		manager.setup(
			configurations
		);

		bool result =
			manager.reset();

		EXPECT_FALSE(
			result
		);
	}

	TEST_F(
		ErrorManagerTest,
		Should_ReturnFalse_When_UtilityRuntimeExecutionDisabled_OnSetup
	)
	{
		ErrorManagerConfigurations configurations;

		configurations
			.is_utility_runtime_execution_handling_enabled =
				false;

		bool result =
			manager.setup(
				configurations
			);

		EXPECT_TRUE(
			result
		);
	}

	TEST_F(
		ErrorManagerTest,
		Should_ReturnEmptyString_When_FeatureRuntimeExecutionDisabled_WithTitleAndMessage
	)
	{
		ErrorManagerConfigurations configurations;

		configurations
			.is_feature_runtime_execution_handling_enabled =
			false;

		manager.setup(
			configurations
		);

		std::string result =
			manager.transform_to_error_log(
				"title",
				"message"
			);

		EXPECT_TRUE(
			result.empty()
		);
	}

	TEST_F(
		ErrorManagerTest,
		Should_ReturnEmptyString_When_FeatureRuntimeExecutionDisabled_WithMessageOnly
	)
	{
		ErrorManagerConfigurations configurations;

		configurations
			.is_feature_runtime_execution_handling_enabled =
			false;

		manager.setup(
			configurations
		);

		std::string result =
			manager.transform_to_error_log(
				"message"
			);

		EXPECT_TRUE(
			result.empty()
		);
	}

	TEST_F(
		ErrorManagerTest,
		Should_ReturnEmptyString_When_FeatureRuntimeExecutionDisabled_WithException
	)
	{
		ErrorManagerConfigurations configurations;

		configurations
			.is_feature_runtime_execution_handling_enabled =
			false;

		manager.setup(
			configurations
		);

		try
		{
			throw std::runtime_error(
				"error"
			);
		}
		catch (
			const std::exception&
				exception
		)
		{
			std::string result =
				manager.transform_to_error_log(
					exception
				);

			EXPECT_TRUE(
				result.empty()
			);
		}
	}

	TEST_F(
		ErrorManagerTest,
		Should_HandleConcurrency_When_ThreadSafetyDisabled
	)
	{
		ErrorManagerConfigurations configurations;

		configurations
			.is_feature_thread_safety_handling_enabled =
			false;

		configurations
			.is_asynchronous_output_enabled =
			true;

		manager.setup(
			configurations
		);

		std::atomic<bool>
			completed =
			false;

		std::thread worker(
			[&]()
			{
				for (
					std::size_t iteration_index = 0;
					iteration_index < 1000;
					iteration_index++
				)
				{
					manager.handle_error_outputs(
						"message"
					);
				}

				completed.store(
					true
				);
			}
		);

		worker.join();

		EXPECT_TRUE(
			completed.load()
		);
	}

	TEST_F(
		ErrorManagerTest,
		Should_HandleAsyncWithoutFutures_When_NoAsyncOutputsEnabled
	)
	{
		ErrorManagerConfigurations configurations;

		configurations
			.is_asynchronous_output_enabled =
			true;

		configurations
			.is_asynchronous_console_output_enabled =
			false;

		configurations
			.is_asynchronous_file_output_enabled =
			false;

		configurations
			.is_asynchronous_runtime_throw_output_enabled =
			false;

		configurations
			.is_enable_output_override_enabled =
			false;

		manager.setup(
			configurations
		);

		bool result =
			manager.handle_error_outputs(
				"no_futures"
			);

		EXPECT_FALSE(
			result
		);
	}
}

#endif
