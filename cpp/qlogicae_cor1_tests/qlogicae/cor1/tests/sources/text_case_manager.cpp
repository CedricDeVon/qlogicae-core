#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextCaseManager \
	)

#include "../includes/text_case_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_P(
		TextCaseManagerParameterizedTest,
		Should_ConvertText_When_ValidTargetTypeProvided
	)
	{
		const std::string
			input =
				GetParam().first;

		const TextCase
			target_type =
				GetParam().second;

		const std::string
			result =
				manager.convert_text(
					input,
					target_type
				);

		ASSERT_FALSE(
			result.empty()
		);
	}

	INSTANTIATE_TEST_CASE_P(
		ValidCases,
		TextCaseManagerParameterizedTest,
		::testing::Values(
			std::make_pair(
				"example text",
				TextCase::LOWERCASE
			),
			std::make_pair(
				"example text",
				TextCase::UPPERCASE
			),
			std::make_pair(
				"example text",
				TextCase::CAPITALIZE
			),
			std::make_pair(
				"example text",
				TextCase::TITLE
			),
			std::make_pair(
				"example text",
				TextCase::SENTENCE
			)
		)
	);

	TEST_F(
		TextCaseManagerTest,
		Should_ReturnEmpty_When_EmptyInputProvided
	)
	{
		const std::string
			result =
				manager.convert_text(
					"",
					TextCase::LOWERCASE
				);

		ASSERT_TRUE(
			result.empty()
		);
	}

	TEST_F(
		TextCaseManagerTest,
		Should_RespectSpecifiedLength_When_Enabled
	)
	{
		manager.configurations.is_specified_length_enabled =
			true;

		manager.configurations.specified_length =
			static_cast<std::size_t>(8);

		const std::string
			result =
				manager.convert_text(
					"VeryLongInputText",
					TextCase::UPPERCASE
				);

		ASSERT_LE(
			result.size(),
			static_cast<std::size_t>(8)
		);
	}

	TEST_F(
		TextCaseManagerTest,
		Should_HandleConcurrentAccess_When_ThreadSafetyEnabled
	)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled =
			true;

		std::atomic<bool>
			failure_detected =
				false;

		std::vector<std::thread>
			worker_threads;

		for (std::size_t index = 0; index < 32; ++index)
		{
			worker_threads.emplace_back(
				[&]()
				{
					const std::string
						result =
							manager.convert_text(
								"threaded input",
								TextCase::TITLE
							);

					if (result.empty())
					{
						failure_detected.store(
							true
						);
					}
				}
			);
		}

		for (std::thread&
			worker_thread :
			worker_threads)
		{
			worker_thread.join();
		}

		ASSERT_FALSE(
			failure_detected.load()
		);
	}

	TEST_F(
		TextCaseManagerTest,
		Should_ExecuteAsync_When_UsingStdAsync
	)
	{
		std::future<std::string>
			future_result =
				std::async(
					std::launch::async,
					[&]()
					{
						return
							manager.convert_text(
								"async text",
								TextCase::UPPERCASE
							);
					}
				);

		ASSERT_EQ(
			future_result.wait_for(
				std::chrono::seconds(2)
			),
			std::future_status::ready
		);

		ASSERT_EQ(
			future_result.get(),
			"ASYNC TEXT"
		);
	}

	TEST_F(
		TextCaseManagerTest,
		Should_NotThrow_When_ExceptionOccurs
	)
	{
		ASSERT_NO_THROW(
			{
				manager.convert_text(
					"exception safe",
					TextCase::LOWERCASE
				);
			}
		);
	}

	TEST_F(
		TextCaseManagerTest,
		Should_HandleStressLoad_When_RepeatedlyInvoked
	)
	{
		for (std::size_t iteration = 0;
			iteration < 100000;
			++iteration)
		{
			const std::string
				result =
					manager.convert_text(
						"stress test",
						TextCase::SENTENCE
					);

			ASSERT_FALSE(
				result.empty()
			);
		}
	}

	TEST_F(
		TextCaseManagerTest,
		Should_UseDefaultTargetType_When_NotProvided
	)
	{
		manager.configurations.target_type =
			TextCase::UPPERCASE;

		const std::string
			result =
				manager.convert_text(
					"default behavior"
				);

		ASSERT_EQ(
			result,
			"DEFAULT BEHAVIOR"
		);
	}

	TEST_P(TextCaseManagerEmptyParameterizedTest,
		Should_ReturnEmpty_When_EmptyInputForAllTargetTypes)
	{
		const TextCase target_type = GetParam();
		const std::string result = manager.convert_text("", target_type);
		ASSERT_TRUE(result.empty());
	}

	INSTANTIATE_TEST_CASE_P(EmptyInputCases,
		TextCaseManagerEmptyParameterizedTest,
		::testing::Values(
			TextCase::LOWERCASE,
			TextCase::UPPERCASE,
			TextCase::CAPITALIZE,
			TextCase::TITLE,
			TextCase::SENTENCE,
			TextCase::NONE
		)
	);

	TEST_F(TextCaseManagerTest,
		Should_ReturnOriginalText_When_TargetTypeIsNone)
	{
		const std::string input = "NoTransformText";
		const std::string result = manager.convert_text(input, TextCase::NONE);
		ASSERT_EQ(result, input);
	}

	TEST_F(TextCaseManagerTest,
		Should_HandleNoneTargetTypeInAsyncExecution)
	{
		const std::string input = "AsyncNoneTest";
		std::future<std::string> future_result = std::async(
			std::launch::async,
			[&]()
			{
				return manager.convert_text(input, TextCase::NONE);
			}
		);

		ASSERT_EQ(future_result.wait_for(std::chrono::seconds(2)),
			std::future_status::ready);
		ASSERT_EQ(future_result.get(), input);
	}

	TEST_F(TextCaseManagerTest,
		Should_HandleNoneTargetTypeWithMultithreading)
	{
		const std::string input = "ThreadNoneTest";
		std::atomic<bool> failure_detected = false;
		std::vector<std::thread> worker_threads;

		for (std::size_t index = 0; index < 32; ++index)
		{
			worker_threads.emplace_back([&]()
			{
				const std::string result =
					manager.convert_text(input, TextCase::NONE);
				if (result != input)
				{
					failure_detected.store(true);
				}
			});
		}

		for (std::thread& worker_thread : worker_threads)
		{
			worker_thread.join();
		}

		ASSERT_FALSE(failure_detected.load());
	}

	TEST_F(TextCaseManagerTest,
		Should_UseDefaultTargetTypeCorrectly_When_NotProvided)
	{
		manager.configurations.target_type = TextCase::UPPERCASE;
		manager.configurations.is_specified_length_enabled = false;
		const std::string result = manager.convert_text("default behavior");
		ASSERT_EQ(result, "DEFAULT BEHAVIOR");
	}

	TEST_F(TextCaseManagerTest,
		Should_ExecuteAsyncCorrectly_When_UsingStdAsync)
	{
		manager.configurations.is_specified_length_enabled = false;
		std::future<std::string> future_result = std::async(
			std::launch::async,
			[&]()
			{
				return manager.convert_text("async text", TextCase::UPPERCASE);
			}
		);

		ASSERT_EQ(future_result.wait_for(std::chrono::seconds(2)),
			std::future_status::ready);
		ASSERT_EQ(future_result.get(), "ASYNC TEXT");
	}

	
	TEST_F(TextCaseManagerTest,
		Should_TruncateCorrectly_InAsyncExecutionWhenSpecifiedLengthEnabled)
	{
		manager.configurations.is_specified_length_enabled = true;
		manager.configurations.specified_length = 5;

		std::future<std::string> future_result = std::async(
			std::launch::async,
			[&]()
			{
				return manager.convert_text("truncate async", TextCase::UPPERCASE);
			}
		);

		ASSERT_EQ(future_result.wait_for(std::chrono::seconds(2)),
			std::future_status::ready);

		ASSERT_LE(static_cast<size_t>(future_result.get().size()), static_cast<size_t>(5));
	}

	TEST_F(TextCaseManagerTest,
		Should_TruncateCorrectly_WithMultithreadingWhenSpecifiedLengthEnabled)
	{
		manager.configurations.is_specified_length_enabled = true;
		manager.configurations.specified_length = 4;

		std::atomic<bool> failure_detected = false;
		std::vector<std::thread> worker_threads;

		for (std::size_t index = 0; index < 16; ++index)
		{
			worker_threads.emplace_back([&]()
			{
				const std::string result =
					manager.convert_text("truncate thread", TextCase::LOWERCASE);
				if (result.size() > 4)
				{
					failure_detected.store(true);
				}
			});
		}

		for (auto& worker_thread : worker_threads)
		{
			worker_thread.join();
		}

		ASSERT_FALSE(failure_detected.load());
	}

	TEST_F(TextCaseManagerTest,
		Should_HandleExceptionsInMultithreadedExecution)
	{
		manager.configurations.is_specified_length_enabled = true;
		manager.configurations.specified_length = 0;

		std::atomic<bool> exception_caught = false;
		std::vector<std::thread> worker_threads;

		for (std::size_t index = 0; index < 8; ++index)
		{
			worker_threads.emplace_back([&]()
			{
				try
				{
					manager.convert_text("exception test", TextCase::UPPERCASE);
				}
				catch (...)
				{
					exception_caught.store(true);
				}
			});
		}

		for (auto& worker_thread : worker_threads)
		{
			worker_thread.join();
		}

		ASSERT_FALSE(exception_caught.load());
	}

	TEST_F(TextCaseManagerTest,
		Should_HandleNonAsciiAndControlCharacters)
	{
		const std::string input = "ÁßçΔ\t\n";
		const std::string result_lower =
			manager.convert_text(input, TextCase::LOWERCASE);
		const std::string result_upper =
			manager.convert_text(input, TextCase::UPPERCASE);

		ASSERT_FALSE(result_lower.empty());
		ASSERT_FALSE(result_upper.empty());
	}

	TEST_F(TextCaseManagerTest,
		Should_HandleVeryShortStringsForCapitalizeTitleSentence)
	{
		const std::string one_char = "a";
		const std::string space_char = " ";
		const std::string punctuation_char = "!";

		ASSERT_EQ(manager.convert_text(one_char, TextCase::CAPITALIZE), "A");
		ASSERT_EQ(manager.convert_text(one_char, TextCase::TITLE), "A");
		ASSERT_EQ(manager.convert_text(one_char, TextCase::SENTENCE), "A");

		ASSERT_EQ(manager.convert_text(space_char, TextCase::CAPITALIZE), " ");
		ASSERT_EQ(manager.convert_text(space_char, TextCase::TITLE), " ");
		ASSERT_EQ(manager.convert_text(space_char, TextCase::SENTENCE), " ");

		ASSERT_EQ(manager.convert_text(punctuation_char, TextCase::CAPITALIZE), "!");
		ASSERT_EQ(manager.convert_text(punctuation_char, TextCase::TITLE), "!");
		ASSERT_EQ(manager.convert_text(punctuation_char, TextCase::SENTENCE), "!");
	}

	TEST_F(TextCaseManagerTest,
		Should_CorrectlyCapitalizeSentencesWithMixedPunctuation)
	{
		const std::string input = "hello! this is a test. is it working? yes!";
		const std::string expected = "Hello! This is a test. Is it working? Yes!";
		const std::string result = manager.convert_text(input, TextCase::SENTENCE);

		ASSERT_EQ(result, expected);
	}
}

#endif
