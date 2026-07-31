#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextLogManager \
	)

#include "../includes/text_log_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
    TEST_P(TextLogManagerTimeFormatTest, Should_Format_Time_Correctly)
    {
        const TimeFormat format_value = GetParam();
        const std::string message_value = "time_message";

        const std::string result =
            text_log_manager_instance.convert_text(
                message_value,
                LogLevel::INFO,
                format_value,
                LogFormat::STANDARD
            );

        ASSERT_NE(result.find(message_value), std::string::npos);
		ASSERT_FALSE(result.empty());
		if (format_value == TimeFormat::ISO8601)
		{
			ASSERT_NE(result.find("T"), std::string::npos);
			ASSERT_NE(result.find("-"), std::string::npos);
		}
    }

    TEST_P(TextLogManagerTimeFormatTest, Should_Apply_SpecifiedLength_With_TimeFormat)
    {
        text_log_manager_instance.configurations.is_specified_length_enabled = true;
        text_log_manager_instance.configurations.specified_length = 50;

        const TimeFormat format_value = GetParam();
        const std::string message_value = "length_message";

        const std::string result =
            text_log_manager_instance.convert_text(
                message_value,
                LogLevel::INFO,
                format_value,
                LogFormat::STANDARD
            );

        ASSERT_EQ(result.size(), 50);

        text_log_manager_instance.configurations.is_specified_length_enabled = false;
    }

    TEST_P(TextLogManagerTimeFormatTest, Should_Handle_ThreadSafety_With_TimeFormat)
    {
        text_log_manager_instance.configurations.is_feature_thread_safety_handling_enabled = true;

        const TimeFormat format_value = GetParam();
        const std::string message_value = "thread_message";

        std::atomic<bool> success_flag(true);
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i)
        {
            threads.emplace_back([&]()
            {
                const std::string result =
                    text_log_manager_instance.convert_text(
                        message_value,
                        LogLevel::INFO,
                        format_value,
                        LogFormat::STANDARD
                    );
                if (result.empty()) success_flag.store(false);
            });
        }

        for (auto& t : threads) t.join();

        ASSERT_TRUE(success_flag.load());

        text_log_manager_instance.configurations.is_feature_thread_safety_handling_enabled = false;
    }

    TEST_P(TextLogManagerTimeFormatTest, Should_Not_Throw_On_Exception_With_TimeFormat)
    {
        const TimeFormat format_value = GetParam();
        const std::string message_value = std::string("\0", 1);

        ASSERT_NO_THROW(
            text_log_manager_instance.convert_text(
                message_value,
                LogLevel::INFO,
                format_value,
                LogFormat::STANDARD
            )
        );
    }

    INSTANTIATE_TEST_CASE_P(
        TextLogManagerTimeFormatInstantiation,
        TextLogManagerTimeFormatTest,
        ::testing::Values(
            TimeFormat::UNIX,
            TimeFormat::ISO8601,
            TimeFormat::SECOND_LEVEL_TIMESTAMP,
            TimeFormat::MILLISECOND_LEVEL_TIMESTAMP,
            TimeFormat::MICROSECOND_LEVEL_TIMESTAMP,
            TimeFormat::FULL_TIMESTAMP,
            TimeFormat::FULL_DASHED_TIMESTAMP,
            TimeFormat::HOUR_12,
            TimeFormat::HOUR_24,
            TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND,
            TimeFormat::DATE_DASHED,
            TimeFormat::DATE_MDY_SLASHED,
            TimeFormat::DATE_DMY_SLASHED,
            TimeFormat::DATE_DMY_SPACED,
            TimeFormat::DATE_VERBOSE,
            TimeFormat::NONE
        )
    );

	TEST_F(
		TextLogManagerTest,
		Should_Return_Message_When_LogFormatNone
	)
	{
		const std::string message_value = "message";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				"",
				LogFormat::NONE
			);

		ASSERT_EQ(result, message_value);
	}

	TEST_F(
		TextLogManagerTest,
		Should_Return_Message_When_CustomFormat
	)
	{
		const std::string message_value = "message";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				"",
				LogFormat::CUSTOM
			);

		ASSERT_EQ(result, message_value);
	}

	TEST_F(
		TextLogManagerTest,
		Should_Include_Time_And_Level_When_StandardFormat
	)
	{
		const std::string message_value = "message";
		const std::string time_value = "2024";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				time_value,
				LogFormat::STANDARD
			);

		ASSERT_NE(result.find(message_value), std::string::npos);
	}

	TEST_F(
		TextLogManagerTest,
		Should_Handle_Empty_Message_When_EmptyInput
	)
	{
		const std::string message_value = "";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				"",
				LogFormat::STANDARD
			);

		ASSERT_TRUE(result.empty() || result.find("") != std::string::npos);
	}

	TEST_F(
		TextLogManagerTest,
		Should_Not_Throw_When_Invalid_LogFormat
	)
	{
		const std::string message_value = "message";

		ASSERT_NO_THROW(
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				"",
				static_cast<LogFormat>(999)
			)
		);
	}

	TEST_P(
		TextLogManagerParameterizedTest,
		Should_Return_Valid_Output_When_ParameterizedFormats
	)
	{
		const LogFormat format_value = GetParam();
		const std::string message_value = "message";

		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				"",
				format_value
			);

		ASSERT_FALSE(result.empty());
	}

	INSTANTIATE_TEST_CASE_P(
		TextLogManagerParameterizedInstantiation,
		TextLogManagerParameterizedTest,
		::testing::Values(
			LogFormat::STANDARD,
			LogFormat::CUSTOM,
			LogFormat::NONE
		)
	);

	TEST_F(
		TextLogManagerTest,
		Should_Execute_Asynchronously_When_UsingStdAsync
	)
	{
		const std::string message_value = "message";

		std::future<std::string> future_result =
			std::async(
				std::launch::async,
				[&]()
				{
					return text_log_manager_instance.convert_text(
						message_value,
						LogLevel::INFO
					);
				}
			);

		const std::string result = future_result.get();
		ASSERT_FALSE(result.empty());
	}

	TEST_F(
		TextLogManagerTest,
		Should_Handle_Multithreaded_Access_When_ConcurrentCalls
	)
	{
		const std::string message_value = "message";
		std::atomic<bool> success_flag(true);
		std::vector<std::thread> thread_collection;

		for (std::size_t index = 0U; index < 20U; ++index)
		{
			thread_collection.emplace_back(
				[&]()
				{
					const std::string result =
						text_log_manager_instance.convert_text(
							message_value,
							LogLevel::INFO
						);

					if (result.empty())
					{
						success_flag.store(false);
					}
				}
			);
		}

		for (std::thread& thread_instance : thread_collection)
		{
			thread_instance.join();
		}

		ASSERT_TRUE(success_flag.load());
	}

	TEST_F(
		TextLogManagerTest,
		Should_Sustain_HighLoad_When_StressTesting
	)
	{
		const std::string message_value = "message";

		const auto start_time =
			std::chrono::steady_clock::now();

		for (std::size_t index = 0U; index < 50000U; ++index)
		{
			const std::string result =
				text_log_manager_instance.convert_text(
					message_value,
					LogLevel::INFO
				);

			ASSERT_FALSE(result.empty());
		}

		const auto end_time =
			std::chrono::steady_clock::now();

		const auto duration =
			std::chrono::duration_cast<std::chrono::seconds>(
				end_time - start_time
			);

		ASSERT_LT(duration.count(), 2LL);
	}

	TEST_F(
		TextLogManagerTest,
		Should_Not_Throw_When_ExceptionOccursInternally
	)
	{
		const std::string message_value = "message";

		ASSERT_NO_THROW(
			text_log_manager_instance.convert_text(
				message_value
			)
		);
	}

	TEST_F(
		TextLogManagerTest,
		Should_Handle_Default_Overload_When_NoArguments
	)
	{
		const std::string result =
			text_log_manager_instance.convert_text();

		ASSERT_FALSE(result.empty());
	}

	TEST_F(
		TextLogManagerTest,
		Should_Return_Message_When_RuntimeExecutionDisabled
	)
	{
		text_log_manager_instance
			.configurations
			.is_feature_runtime_execution_handling_enabled = false;

		const std::string message_value = "runtime";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				"time",
				LogFormat::STANDARD
			);

		ASSERT_EQ(result, message_value);
	}

	TEST_F(
		TextLogManagerTest,
		Should_Return_Message_When_EdgeCaseEnabledAndNoneFormat
	)
	{
		text_log_manager_instance
			.configurations
			.is_feature_edge_case_handling_enabled = true;

		const std::string message_value = "edge";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				"time",
				LogFormat::NONE
			);

		ASSERT_EQ(result, message_value);

		text_log_manager_instance
			.configurations
			.is_feature_edge_case_handling_enabled = false;
	}

	TEST_F(
		TextLogManagerTest,
		Should_ReserveSpecifiedLength_When_SpecifiedLengthEnabled
	)
	{
		text_log_manager_instance
			.configurations
			.is_specified_length_enabled = true;

		text_log_manager_instance
			.configurations
			.specified_length = 1024U;

		const std::string message_value = "reserve";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				"time",
				LogFormat::STANDARD
			);

		ASSERT_FALSE(result.empty());

		text_log_manager_instance
			.configurations
			.is_specified_length_enabled = false;
	}

	TEST_F(
		TextLogManagerTest,
		Should_ExecuteThreadSafetyPath_When_ThreadSafetyEnabled
	)
	{
		text_log_manager_instance
			.configurations
			.is_feature_thread_safety_handling_enabled = true;

		const std::string message_value = "threadsafe";

		std::thread thread_instance(
			[&]()
			{
				text_log_manager_instance.convert_text(
					message_value,
					LogLevel::INFO
				);
			}
		);

		thread_instance.join();

		ASSERT_TRUE(true);

		text_log_manager_instance
			.configurations
			.is_feature_thread_safety_handling_enabled = false;
	}

	TEST_F(
		TextLogManagerTest,
		Should_Handle_TimeFormatOverload_When_TimeFormatProvided
	)
	{
		const std::string message_value = "timeformat";

		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				TimeFormat::NONE,
				LogFormat::STANDARD
			);

		ASSERT_FALSE(result.empty());
	}

	TEST_F(
		TextLogManagerTest,
		Should_Handle_TimeFormatWithoutLogFormat_When_UsingConfiguration
	)
	{
		const std::string message_value = "timeonly";

		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				TimeFormat::NONE
			);

		ASSERT_FALSE(result.empty());
	}

	TEST_F(
		TextLogManagerTest,
		Should_Handle_StringTimeWithoutLogFormat_When_UsingConfiguration
	)
	{
		const std::string message_value = "stringtime";

		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				std::string("time")
			);

		ASSERT_FALSE(result.empty());
	}

	TEST_F(
		TextLogManagerTest,
		Should_Handle_LogFormatOnlyOverload_When_TimeFromConfiguration
	)
	{
		const std::string message_value = "formatonly";

		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				LogFormat::STANDARD
			);

		ASSERT_FALSE(result.empty());
	}

	TEST_F(
		TextLogManagerTest,
		Should_Handle_LargeMessage_When_MaximumInputSize
	)
	{
		const std::string message_value(10000U, 'A');

		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO
			);

		ASSERT_FALSE(result.empty());
	}

	TEST_F(
		TextLogManagerTest,
		Should_Synchronize_WithConditionVariable_When_MultiThreadCoordinated
	)
	{
		std::mutex mutex_instance;
		std::condition_variable condition_variable_instance;
		bool ready_flag = false;
		bool completed_flag = false;

		std::thread thread_instance(
			[&]()
			{
				std::unique_lock<std::mutex> lock_instance(mutex_instance);
				condition_variable_instance.wait(
					lock_instance,
					[&]() { return ready_flag; }
				);

				text_log_manager_instance.convert_text(
					"condition",
					LogLevel::INFO
				);

				completed_flag = true;
				condition_variable_instance.notify_one();
			}
		);

		{
			std::unique_lock<std::mutex> lock_instance(mutex_instance);
			ready_flag = true;
			condition_variable_instance.notify_one();
		}

		{
			std::unique_lock<std::mutex> lock_instance(mutex_instance);
			condition_variable_instance.wait(
				lock_instance,
				[&]() { return completed_flag; }
			);
		}

		thread_instance.join();

		ASSERT_TRUE(completed_flag);
	}

	TEST_F(
		TextLogManagerTest,
		Should_PropagateFutureException_When_ExceptionThrownAsync
	)
	{
		std::promise<void> promise_instance;
		std::future<void> future_instance =
			promise_instance.get_future();

		std::thread thread_instance(
			[&]()
			{
				try
				{
					text_log_manager_instance.convert_text(
						"exception",
						LogLevel::INFO
					);
					promise_instance.set_value();
				}
				catch (...)
				{
					promise_instance.set_exception(
						std::current_exception()
					);
				}
			}
		);

		thread_instance.join();

		ASSERT_NO_THROW(future_instance.get());
	}

	TEST_F(
		TextLogManagerTest,
		RuntimeExecutionUtilityOverrideTrue_ShouldReturnOverrideValue
	)
	{
		text_log_manager_instance
			.configurations
			.is_runtime_execution_handling_override_enabled = true;

		text_log_manager_instance
			.configurations
			.is_runtime_execution_handling_enabled = false;

		ASSERT_FALSE(
			text_log_manager_instance
				.configurations
				.is_runtime_execution_enabled_for_utility_handling()
		);

		text_log_manager_instance
			.configurations
			.is_runtime_execution_handling_enabled = true;

		ASSERT_TRUE(
			text_log_manager_instance
				.configurations
				.is_runtime_execution_enabled_for_utility_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		RuntimeExecutionFeatureOverrideFalse_ShouldReturnFeatureValue
	)
	{
		text_log_manager_instance
			.configurations
			.is_runtime_execution_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_feature_runtime_execution_handling_enabled = false;

		ASSERT_FALSE(
			text_log_manager_instance
				.configurations
				.is_runtime_execution_enabled_for_feature_handling()
		);

		text_log_manager_instance
			.configurations
			.is_feature_runtime_execution_handling_enabled = true;

		ASSERT_TRUE(
			text_log_manager_instance
				.configurations
				.is_runtime_execution_enabled_for_feature_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		EdgeCaseFeatureOverrideTrue_ShouldReturnOverrideValue
	)
	{
		text_log_manager_instance
			.configurations
			.is_edge_case_handling_override_enabled = true;

		text_log_manager_instance
			.configurations
			.is_edge_case_handling_enabled = false;

		ASSERT_FALSE(
			text_log_manager_instance
				.configurations
				.is_edge_case_enabled_for_feature_handling()
		);

		text_log_manager_instance
			.configurations
			.is_edge_case_handling_enabled = true;

		ASSERT_TRUE(
			text_log_manager_instance
				.configurations
				.is_edge_case_enabled_for_feature_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		ThreadSafetyFeatureOverrideTrue_ShouldReturnOverrideValue
	)
	{
		text_log_manager_instance
			.configurations
			.is_thread_safety_handling_override_enabled = true;

		text_log_manager_instance
			.configurations
			.is_thread_safety_handling_enabled = false;

		ASSERT_FALSE(
			text_log_manager_instance
				.configurations
				.is_thread_safety_enabled_for_feature_handling()
		);

		text_log_manager_instance
			.configurations
			.is_thread_safety_handling_enabled = true;

		ASSERT_TRUE(
			text_log_manager_instance
				.configurations
				.is_thread_safety_enabled_for_feature_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		RuntimeExecutionDisabledForUtility_ShouldNegateEnabled
	)
	{
		text_log_manager_instance
			.configurations
			.is_runtime_execution_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_utility_runtime_execution_handling_enabled = true;

		ASSERT_FALSE(
			text_log_manager_instance
				.configurations
				.is_runtime_execution_disabled_for_utility_handling()
		);

		text_log_manager_instance
			.configurations
			.is_utility_runtime_execution_handling_enabled = false;

		ASSERT_TRUE(
			text_log_manager_instance
				.configurations
				.is_runtime_execution_disabled_for_utility_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		EdgeCaseDisabledForFeature_ShouldNegateEnabled
	)
	{
		text_log_manager_instance
			.configurations
			.is_edge_case_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_feature_edge_case_handling_enabled = true;

		ASSERT_FALSE(
			text_log_manager_instance
				.configurations
				.is_edge_case_disabled_for_feature_handling()
		);

		text_log_manager_instance
			.configurations
			.is_feature_edge_case_handling_enabled = false;

		ASSERT_TRUE(
			text_log_manager_instance
				.configurations
				.is_edge_case_disabled_for_feature_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		ThreadSafetyDisabledForFeature_ShouldNegateEnabled
	)
	{
		text_log_manager_instance
			.configurations
			.is_thread_safety_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_feature_thread_safety_handling_enabled = false;

		ASSERT_TRUE(
			text_log_manager_instance
				.configurations
				.is_thread_safety_disabled_for_feature_handling()
		);

		text_log_manager_instance
			.configurations
			.is_feature_thread_safety_handling_enabled = true;

		ASSERT_FALSE(
			text_log_manager_instance
				.configurations
				.is_thread_safety_disabled_for_feature_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		RuntimeExecutionErrorOverrideFalse_ShouldReturnErrorValue
	)
	{
		text_log_manager_instance
			.configurations
			.is_runtime_execution_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_error_runtime_execution_handling_enabled = false;

		ASSERT_FALSE(
			text_log_manager_instance
			.configurations
			.is_runtime_execution_enabled_for_error_handling()
		);

		text_log_manager_instance
			.configurations
			.is_error_runtime_execution_handling_enabled = true;

		ASSERT_TRUE(
			text_log_manager_instance
			.configurations
			.is_runtime_execution_enabled_for_error_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		EdgeCaseUtilityOverrideFalse_ShouldReturnUtilityValue
	)
	{
		text_log_manager_instance
			.configurations
			.is_edge_case_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_utility_edge_case_handling_enabled = false;

		ASSERT_FALSE(
			text_log_manager_instance
			.configurations
			.is_edge_case_enabled_for_utility_handling()
		);

		text_log_manager_instance
			.configurations
			.is_utility_edge_case_handling_enabled = true;

		ASSERT_TRUE(
			text_log_manager_instance
			.configurations
			.is_edge_case_enabled_for_utility_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		EdgeCaseErrorOverrideFalse_ShouldReturnErrorValue
	)
	{
		text_log_manager_instance
			.configurations
			.is_edge_case_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_error_edge_case_handling_enabled = false;

		ASSERT_FALSE(
			text_log_manager_instance
			.configurations
			.is_edge_case_enabled_for_error_handling()
		);

		text_log_manager_instance
			.configurations
			.is_error_edge_case_handling_enabled = true;

		ASSERT_TRUE(
			text_log_manager_instance
			.configurations
			.is_edge_case_enabled_for_error_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		ThreadSafetyUtilityOverrideFalse_ShouldReturnUtilityValue
	)
	{
		text_log_manager_instance
			.configurations
			.is_thread_safety_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_utility_thread_safety_handling_enabled = false;

		ASSERT_FALSE(
			text_log_manager_instance
			.configurations
			.is_thread_safety_enabled_for_utility_handling()
		);

		text_log_manager_instance
			.configurations
			.is_utility_thread_safety_handling_enabled = true;

		ASSERT_TRUE(
			text_log_manager_instance
			.configurations
			.is_thread_safety_enabled_for_utility_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		ThreadSafetyErrorOverrideFalse_ShouldReturnErrorValue
	)
	{
		text_log_manager_instance
			.configurations
			.is_thread_safety_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_error_thread_safety_handling_enabled = false;

		ASSERT_FALSE(
			text_log_manager_instance
			.configurations
			.is_thread_safety_enabled_for_error_handling()
		);

		text_log_manager_instance
			.configurations
			.is_error_thread_safety_handling_enabled = true;

		ASSERT_TRUE(
			text_log_manager_instance
			.configurations
			.is_thread_safety_enabled_for_error_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		RuntimeExecutionDisabledForFeature_ShouldNegateEnabled
	)
	{
		text_log_manager_instance
			.configurations
			.is_runtime_execution_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_feature_runtime_execution_handling_enabled = true;

		ASSERT_FALSE(
			text_log_manager_instance
			.configurations
			.is_runtime_execution_disabled_for_feature_handling()
		);

		text_log_manager_instance
			.configurations
			.is_feature_runtime_execution_handling_enabled = false;

		ASSERT_TRUE(
			text_log_manager_instance
			.configurations
			.is_runtime_execution_disabled_for_feature_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		RuntimeExecutionDisabledForError_ShouldNegateEnabled
	)
	{
		text_log_manager_instance
			.configurations
			.is_runtime_execution_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_error_runtime_execution_handling_enabled = true;

		ASSERT_FALSE(
			text_log_manager_instance
			.configurations
			.is_runtime_execution_disabled_for_error_handling()
		);

		text_log_manager_instance
			.configurations
			.is_error_runtime_execution_handling_enabled = false;

		ASSERT_TRUE(
			text_log_manager_instance
			.configurations
			.is_runtime_execution_disabled_for_error_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		EdgeCaseDisabledForUtility_ShouldNegateEnabled
	)
	{
		text_log_manager_instance
			.configurations
			.is_edge_case_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_utility_edge_case_handling_enabled = true;

		ASSERT_FALSE(
			text_log_manager_instance
			.configurations
			.is_edge_case_disabled_for_utility_handling()
		);

		text_log_manager_instance
			.configurations
			.is_utility_edge_case_handling_enabled = false;

		ASSERT_TRUE(
			text_log_manager_instance
			.configurations
			.is_edge_case_disabled_for_utility_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		EdgeCaseDisabledForError_ShouldNegateEnabled
	)
	{
		text_log_manager_instance
			.configurations
			.is_edge_case_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_error_edge_case_handling_enabled = true;

		ASSERT_FALSE(
			text_log_manager_instance
			.configurations
			.is_edge_case_disabled_for_error_handling()
		);

		text_log_manager_instance
			.configurations
			.is_error_edge_case_handling_enabled = false;

		ASSERT_TRUE(
			text_log_manager_instance
			.configurations
			.is_edge_case_disabled_for_error_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		ThreadSafetyDisabledForUtility_ShouldNegateEnabled
	)
	{
		text_log_manager_instance
			.configurations
			.is_thread_safety_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_utility_thread_safety_handling_enabled = true;

		ASSERT_FALSE(
			text_log_manager_instance
			.configurations
			.is_thread_safety_disabled_for_utility_handling()
		);

		text_log_manager_instance
			.configurations
			.is_utility_thread_safety_handling_enabled = false;

		ASSERT_TRUE(
			text_log_manager_instance
			.configurations
			.is_thread_safety_disabled_for_utility_handling()
		);
	}

	TEST_F(
		TextLogManagerTest,
		ThreadSafetyDisabledForError_ShouldNegateEnabled
	)
	{
		text_log_manager_instance
			.configurations
			.is_thread_safety_handling_override_enabled = false;

		text_log_manager_instance
			.configurations
			.is_error_thread_safety_handling_enabled = true;

		ASSERT_FALSE(
			text_log_manager_instance
			.configurations
			.is_thread_safety_disabled_for_error_handling()
		);

		text_log_manager_instance
			.configurations
			.is_error_thread_safety_handling_enabled = false;

		ASSERT_TRUE(
			text_log_manager_instance
			.configurations
			.is_thread_safety_disabled_for_error_handling()
		);
	}

	TEST_F(TextLogManagerTest, Should_Apply_CustomFormatStringCorrectly)
	{
		const std::string message_value = "custom";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::WARNING,
				"",
				LogFormat::CUSTOM
			);

		ASSERT_EQ(result.find("WARNING"), std::string::npos);
		ASSERT_NE(result.find(message_value), std::string::npos);
	}

	TEST_F(TextLogManagerTest, Should_Enforce_SpecifiedLengthExactly)
	{
		text_log_manager_instance
			.configurations
			.is_specified_length_enabled = true;
		text_log_manager_instance
			.configurations
			.specified_length = 10;

		const std::string message_value = "123456789012345";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO
			);

		ASSERT_EQ(result.size(), 10);

		text_log_manager_instance
			.configurations
			.is_specified_length_enabled = false;
	}

	TEST_F(TextLogManagerTest, Should_Handle_MultipleConfigurationFlagsCombined)
	{
		text_log_manager_instance.configurations.is_feature_runtime_execution_handling_enabled = true;
		text_log_manager_instance.configurations.is_feature_edge_case_handling_enabled = true;
		text_log_manager_instance.configurations.is_feature_thread_safety_handling_enabled = true;
		text_log_manager_instance.configurations.is_specified_length_enabled = true;
		text_log_manager_instance.configurations.specified_length = 50;

		const std::string message_value = "combined_flags_test";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::ERROR_TYPE,
				TimeFormat::ISO8601,
				LogFormat::STANDARD
			);

		ASSERT_FALSE(result.empty());
		ASSERT_EQ(result.size(), 50);

		text_log_manager_instance.configurations.is_specified_length_enabled = false;
	}

	TEST_F(TextLogManagerTest, Should_FormatTime_When_NonNoneTimeFormat)
	{
		const std::string message_value = "time_test";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				TimeFormat::ISO8601,
				LogFormat::STANDARD
			);

		ASSERT_NE(result.find("T"), std::string::npos); 
		ASSERT_NE(result.find(message_value), std::string::npos);
	}

	TEST_F(TextLogManagerTest, Should_Handle_Unicode_Message)
	{
		const std::string message_value = "こんにちは世界🌏";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO
			);

		ASSERT_NE(result.find("こんにちは世界🌏"), std::string::npos);
	}

	TEST_F(TextLogManagerTest, Should_Propagate_Exception_When_InvalidInput)
	{
		const std::string invalid_message = std::string("\0", 1); 

		ASSERT_NO_THROW(
			text_log_manager_instance.convert_text(
				invalid_message,
				LogLevel::INFO
			)
		);
	}

	TEST_F(TextLogManagerTest, Should_Propagate_Exception_FromConvertText)
	{
		struct ThrowingTextLogManager : public TextLogManager
		{
			std::string convert_text(const std::string&, const LogLevel&, const std::string&, const LogFormat&)
			{
				throw std::runtime_error("forced");
			}
		};

		ThrowingTextLogManager throwing_manager;

		ASSERT_THROW(
			throwing_manager.convert_text("msg", LogLevel::INFO, "", LogFormat::STANDARD),
			std::runtime_error
		);
	}

	TEST_F(TextLogManagerTest, Should_FormatTime_Fully_When_NonNoneTimeFormat)
	{
		const std::string message_value = "time_test";
		const std::string result =
			text_log_manager_instance.convert_text(
				message_value,
				LogLevel::INFO,
				TimeFormat::ISO8601,
				LogFormat::STANDARD
			);

		ASSERT_NE(result.find(message_value), std::string::npos);

		std::regex iso_regex(R"(\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2})");
		ASSERT_TRUE(std::regex_search(result, iso_regex));
	}
}

#endif
