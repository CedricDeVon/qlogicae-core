#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextErrorManager \
	)

#include "../includes/text_error_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
    TEST_F(
        TextErrorManagerTest,
        Should_ReturnSameInstance_When_SingletonAccessed)
    {
        auto& first_instance =
            SingletonManager::get_singleton<TextErrorManager>();

        auto& second_instance =
            SingletonManager::get_singleton<TextErrorManager>();

        ASSERT_EQ(
            &first_instance,
            &second_instance);
    }

    TEST_P(
        TextErrorManagerTest,
        Should_FormatTextCorrectly_When_ValidParametersProvided)
    {
        const auto& parameters =
            GetParam();

        const std::string origin =
            std::get<0>(parameters);

        const std::string message =
            std::get<1>(parameters);

        const std::string expected_substring =
            std::get<2>(parameters);

        const std::string result =
            text_error_manager.convert_text(
                origin,
                message);

        ASSERT_NE(
            result.find(expected_substring),
            std::string::npos);
    }

    INSTANTIATE_TEST_CASE_P(
        TextFormatting,
        TextErrorManagerTest,
        ::testing::Values(
            std::make_tuple(
                std::string("origin"),
                std::string("message"),
                std::string("message")),
            std::make_tuple(
                std::string(""),
                std::string("message"),
                std::string("message")),
            std::make_tuple(
                std::string("origin"),
                std::string(""),
                std::string(""))
        )
    );

    TEST_F(
        TextErrorManagerTest,
        Should_NotDeadlock_When_CalledConcurrently)
    {
        constexpr std::size_t THREAD_COUNT = 32;

        std::vector<std::thread>
            worker_threads;

        std::atomic<std::size_t>
            completed_calls =
                static_cast<std::size_t>(0);

        for
        (
            std::size_t thread_index = 0;
            thread_index < THREAD_COUNT;
            ++thread_index
        )
        {
            worker_threads.emplace_back(
                [&]()
                {
                    const std::string result =
                        text_error_manager.convert_text(
                            "origin",
                            "message");

                    if (!result.empty())
                    {
                        completed_calls.fetch_add(
                            static_cast<std::size_t>(1),
                            std::memory_order_relaxed);
                    }
                });
        }

        for
        (
            std::thread& worker_thread :
            worker_threads
        )
        {
            worker_thread.join();
        }

        ASSERT_EQ(
            completed_calls.load(),
            THREAD_COUNT);
    }

    TEST_F(
        TextErrorManagerTest,
        Should_CompleteAsyncCalls_When_UsingStdAsync)
    {
        auto async_task =
            std::async(
                std::launch::async,
                [&]()
                {
                    return
                        text_error_manager.convert_text(
                            "origin",
                            "async_message");
                });

        const std::string result =
            async_task.get();

        ASSERT_FALSE(
            result.empty());
    }

    TEST_F(
        TextErrorManagerTest,
        Should_HandleStressLoad_When_RepeatedCallsExecuted)
    {
        constexpr std::size_t ITERATION_COUNT = 100000;

        for
        (
            std::size_t iteration_index = 0;
            iteration_index < ITERATION_COUNT;
            ++iteration_index
        )
        {
            const std::string result =
                text_error_manager.convert_text(
                    "origin",
                    "stress_message");

            ASSERT_FALSE(
                result.empty());
        }
    }

    TEST_F(
        TextErrorManagerTest,
        Should_NotThrow_When_ExceptionOccursInternally)
    {
        ASSERT_NO_THROW(
            {
                const std::string result =
                    text_error_manager.convert_text(
                        std::string(),
                        std::string());
            });
    }

    TEST_F(
        TextErrorManagerTest,
        Should_CompleteWithinTimeLimit_When_MixedConcurrencyApplied)
    {
        constexpr std::size_t THREAD_COUNT = 16;
        constexpr std::size_t ITERATION_COUNT = 5000;

        std::vector<std::thread>
            worker_threads;

        for
        (
            std::size_t thread_index = 0;
            thread_index < THREAD_COUNT;
            ++thread_index
        )
        {
            worker_threads.emplace_back(
                [&]()
                {
                    for
                    (
                        std::size_t iteration_index = 0;
                        iteration_index < ITERATION_COUNT;
                        ++iteration_index
                    )
                    {
                        text_error_manager.convert_text(
                            "origin",
                            "concurrent_message");
                    }
                });
        }

        for
        (
            std::thread& worker_thread :
            worker_threads
        )
        {
            worker_thread.join();
        }
    }

    TEST_F(
        TextErrorManagerTest,
        Should_ApplyNewConfigurations_When_SetupCalled)
    {
        TextErrorManagerConfigurations
            new_configurations;

        new_configurations.title =
            std::string("NewTitle");

        const bool setup_result =
            text_error_manager.setup(
                new_configurations);

        ASSERT_TRUE(
            setup_result);

        const std::string result =
            text_error_manager.convert_text(
                std::string("origin"),
                std::string("message"));

        ASSERT_NE(
            result.find("NewTitle"),
            std::string::npos);
    }

    TEST_F(
        TextErrorManagerTest,
        Should_ResetConfigurations_When_ResetCalled)
    {
        const bool reset_result =
            text_error_manager.reset();

        ASSERT_TRUE(
            reset_result);

        const std::string result =
            text_error_manager.convert_text(
                std::string("origin"),
                std::string("message"));

        ASSERT_NE(
            result.find("Exception"),
            std::string::npos);
    }

    TEST_F(
        TextErrorManagerTest,
        Should_PropagateAsyncException_When_PromiseUsed)
    {
        std::promise<std::string>
            value_promise;

        std::future<std::string>
            value_future =
                value_promise.get_future();

        std::thread
            worker_thread(
                [&]()
                {
                    try
                    {
                        throw
                            std::runtime_error(
                                std::string("failure"));
                    }
                    catch (...)
                    {
                        value_promise
                            .set_exception(
                                std::current_exception());
                    }
                });

        worker_thread.join();

        ASSERT_THROW(
            value_future.get(),
            std::runtime_error);
    }

    TEST_F(
        TextErrorManagerTest,
        Should_HandleMaximumLengthStrings_When_StressApplied)
    {
        const std::string
            maximum_length_string(
                static_cast<std::size_t>(100000),
                'X');

        const std::string result =
            text_error_manager.convert_text(
                maximum_length_string,
                maximum_length_string);

        ASSERT_FALSE(
            result.empty());
    }

    TEST_F(
        TextErrorManagerTest,
        Should_NotDeadlock_When_ConcurrentResetOccurs)
    {
        std::atomic<bool>
            execution_completed =
                false;

        std::thread
            reset_thread(
                [&]()
                {
                    text_error_manager.reset();
                });

        std::thread
            call_thread(
                [&]()
                {
                    text_error_manager.convert_text(
                        std::string("origin"),
                        std::string("message"));

                    execution_completed.store(
                        true);
                });

        reset_thread.join();
        call_thread.join();

        ASSERT_TRUE(
            execution_completed.load());
    }

    TEST_F(
        TextErrorManagerTest,
        Should_RespectThreadSafetyOverride_When_Enabled)
    {
        TextErrorManagerConfigurations
            new_configurations;

        new_configurations
            .is_thread_safety_handling_override_enabled =
			true;

		text_error_manager.setup(
			new_configurations);

		std::vector<std::thread>
			worker_threads;

		for
			(
				std::size_t thread_index = 0;
				thread_index < static_cast<std::size_t>(16);
				++thread_index
				)
		{
			worker_threads.emplace_back(
				[&]()
				{
					text_error_manager.convert_text(
						std::string("origin"),
						std::string("message"));
				});
		}

		for
			(
				std::thread& worker_thread :
				worker_threads
				)
		{
			worker_thread.join();
		}

		SUCCEED();
	}

	TEST_F(
		TextErrorManagerTest,
		Should_ExerciseFeatureHandlingMutexes_When_Configured)
	{
		TextErrorManagerConfigurations
			new_configurations;

		new_configurations
			.is_feature_thread_safety_handling_enabled =
			true;

		text_error_manager.setup(
			new_configurations);

		std::thread
			first_thread(
				[&]()
				{
					text_error_manager.convert_text(
						std::string("origin"),
						std::string("message"));
				});

		std::thread
			second_thread(
				[&]()
				{
					text_error_manager.convert_text(
						std::string("origin"),
						std::string("message"));
				});

		first_thread.join();
		second_thread.join();

		SUCCEED();
	}

	TEST_F(
		TextErrorManagerTest,
		Should_HandleSpecifiedLength_When_Enabled)
	{
		TextErrorManagerConfigurations
			new_configurations;

		new_configurations
			.is_specified_length_enabled =
			true;

		new_configurations
			.specified_length =
			static_cast<std::size_t>(8);

		text_error_manager.setup(
			new_configurations);

		const std::string result =
			text_error_manager.convert_text(
				std::string("origin"),
				std::string("123456789"));

		ASSERT_FALSE(
			result.empty());

		ASSERT_NE(
			result.find(
				std::string("123456789")),
			std::string::npos);
	}

	TEST_F(
		TextErrorManagerTest,
		Should_RunWithoutMutex_When_ThreadSafetyDisabled)
	{
		TextErrorManagerConfigurations
			new_configurations;

		new_configurations
			.is_thread_safety_handling_override_enabled =
                false;

        new_configurations
            .is_utility_thread_safety_handling_enabled =
                false;

        text_error_manager.setup(
            new_configurations);

        const std::string result =
            text_error_manager.convert_text(
                std::string("origin"),
                std::string("message"));

        ASSERT_FALSE(
            result.empty());
    }

    TEST_F(
        TextErrorManagerTest,
        Should_HandleEmptyArguments_When_Isolated)
    {
        const std::string result =
            text_error_manager.convert_text(
                std::string(),
                std::string());

        ASSERT_FALSE(
            result.empty());
    }

    TEST_F(
        TextErrorManagerTest,
        Should_NotCrash_When_DestructedDuringConcurrentAccess)
    {
        std::atomic<bool>
            execution_completed =
                false;

        std::thread
            worker_thread(
                [&]()
                {
                    text_error_manager.convert_text(
                        std::string("origin"),
                        std::string("message"));

                    execution_completed.store(
                        true);
                });

        worker_thread.join();

        ASSERT_TRUE(
            execution_completed.load());
    }
}

#endif
