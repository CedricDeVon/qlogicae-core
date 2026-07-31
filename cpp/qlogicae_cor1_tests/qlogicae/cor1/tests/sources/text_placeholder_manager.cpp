#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextPlaceholderManager \
	)

#include "../includes/text_placeholder_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(TextPlaceholderManagerTest, Should_ReturnSameSingletonInstance_When_CalledMultipleTimes)
	{
		auto& instance1 = SingletonManager::get_singleton<TextPlaceholderManager>();
		auto& instance2 = SingletonManager::get_singleton<TextPlaceholderManager>();
		ASSERT_EQ(&instance1, &instance2);
	}

	TEST_F(TextPlaceholderManagerTest, Should_ReturnText_When_ConditionalCallbackReturnsFalse)
	{
		manager.configurations.conditional_callback = [](const std::string&) { return false; };
		manager.configurations.is_conditional_callback_enabled = true;
		std::string result = manager.convert_text("Hello", "Placeholder");
		ASSERT_EQ(result, "Hello");
	}

	TEST_F(TextPlaceholderManagerTest, Should_ReturnPlaceholder_When_ConditionalCallbackReturnsTrue)
	{
		manager.configurations.conditional_callback = [](const std::string&) { return true; };
		manager.configurations.is_conditional_callback_enabled = true;
		std::string result = manager.convert_text("Hello", "Placeholder");
		ASSERT_EQ(result, "Placeholder");
	}

	TEST_F(TextPlaceholderManagerTest, Should_ReturnText_When_ConditionalCallbackDisabled)
	{
		manager.configurations.is_conditional_callback_enabled = false;
		std::string result = manager.convert_text("Hello", "Placeholder");
		ASSERT_EQ(result, "Hello");
	}

	TEST_F(TextPlaceholderManagerTest, Should_ReturnEmpty_When_ConditionalCallbackThrows)
	{
		manager.configurations.conditional_callback = [](const std::string&) { throw std::runtime_error("fail"); return true; };
		manager.configurations.is_conditional_callback_enabled = true;

		ASSERT_THROW(
			manager.convert_text("Hello", "Placeholder"),
			std::runtime_error
		);
	}

	TEST_F(TextPlaceholderManagerTest, Should_UseDefaultPlaceholder_When_ConvertTextOverloadCalled)
	{
		manager.configurations.placeholder = "Default";
		manager.configurations.conditional_callback = [](const std::string& text) { return text.empty(); };
		std::string result1 = manager.convert_text("");
		std::string result2 = manager.convert_text("NonEmpty");
		ASSERT_EQ(result1, "Default");
		ASSERT_EQ(result2, "NonEmpty");
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleEmptyTextAndPlaceholder)
	{
		manager.configurations.placeholder = "";
		manager.configurations.conditional_callback = [](const std::string&) { return true; };
		std::string result = manager.convert_text("", "");
		ASSERT_EQ(result, "");
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleLongTextConversion)
	{
		std::string long_text(1000000, 'A');
		manager.configurations.placeholder = "LongPlaceholder";
		manager.configurations.conditional_callback = [](const std::string& text) { return text.empty(); };
		std::string result = manager.convert_text(long_text);
		ASSERT_EQ(result, long_text);
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleConstructAndDestructThreadSafetyEnabled)
	{
		manager.configurations.is_thread_safety_handling_override_enabled = true;
		manager.configurations.is_utility_thread_safety_handling_enabled = true;
		ASSERT_TRUE(manager.construct());
		ASSERT_TRUE(manager.destruct());
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleConstructAndDestructThreadSafetyDisabled)
	{
		manager.configurations.is_thread_safety_handling_override_enabled = false;
		manager.configurations.is_utility_thread_safety_handling_enabled = false;
		ASSERT_TRUE(manager.construct());
		ASSERT_TRUE(manager.destruct());
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleMultithreadedConvertText)
	{
		manager.configurations.placeholder = "None";
		manager.configurations.conditional_callback = [](const std::string& text) { return text.empty(); };
		manager.configurations.is_feature_thread_safety_handling_enabled = true;

		std::atomic<int> success_count{ 0 };
		std::vector<std::thread> threads;
		for (int i = 0; i < 10; i++)
		{
			threads.emplace_back([&]()
				{
					std::string result = manager.convert_text("");
					if (result == "None") success_count++;
				});
		}
		for (auto& t : threads) t.join();
		ASSERT_EQ(success_count.load(), 10);
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleAsyncConvertText)
	{
		manager.configurations.placeholder = "Async";
		manager.configurations.conditional_callback = [](const std::string& text) { return text.empty(); };

		auto future = std::async(std::launch::async, [&]()
			{
				return manager.convert_text("");
			});

		std::string result = future.get();
		ASSERT_EQ(result, "Async");
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleStressTestConvertText)
	{
		manager.configurations.placeholder = "Stress";
		manager.configurations.conditional_callback = [](const std::string& text) { return text.empty(); };
		std::string large_text(1000000, 'B');

		for (int i = 0; i < 10; i++)
		{
			std::string result = manager.convert_text(large_text);
			ASSERT_EQ(result, large_text);
		}
	}

	INSTANTIATE_TEST_CASE_P(
		TextPlaceholderManagerConversions,
		TextPlaceholderManagerParameterizedTest,
		::testing::Values(
			std::make_tuple("", "EmptyPlaceholder", true, true),
			std::make_tuple("", "EmptyPlaceholder", true, false),
			std::make_tuple("", "EmptyPlaceholder", false, true),
			std::make_tuple("", "EmptyPlaceholder", false, false),
			std::make_tuple("Text", "Placeholder", true, true),
			std::make_tuple("Text", "Placeholder", true, false),
			std::make_tuple("Text", "Placeholder", false, true),
			std::make_tuple("Text", "Placeholder", false, false),
			std::make_tuple("NonEmptyText", "Default", true, true),
			std::make_tuple("NonEmptyText", "Default", true, false),
			std::make_tuple("NonEmptyText", "Default", false, true),
			std::make_tuple("NonEmptyText", "Default", false, false),
			std::make_tuple(std::string(1000000, 'A'), "LongPH", true, true),
			std::make_tuple(std::string(1000000, 'A'), "LongPH", false, true),
			std::make_tuple(std::string(1000000, 'A'), "LongPH", true, false),
			std::make_tuple(std::string(1000000, 'A'), "LongPH", false, false)
		)
	);

	TEST_P(TextPlaceholderManagerParameterizedTest,
		Should_ConvertTextAccordingToCallbackAndPlaceholder)
	{
		const auto& [input_text, placeholder, callback_returns_true, callback_enabled] = GetParam();

		manager.configurations.is_conditional_callback_enabled = callback_enabled;
		manager.configurations.placeholder = placeholder;
		manager.configurations.conditional_callback =
			[callback_returns_true](const std::string&) { return callback_returns_true; };

		std::string expected = (callback_enabled && callback_returns_true) ? placeholder : input_text;
		std::string result = manager.convert_text(input_text);
		ASSERT_EQ(result, expected);
	}

	TEST_F(TextPlaceholderManagerTest, Should_ReturnText_When_ConditionalCallbackIsNull)
	{
		manager.configurations.conditional_callback = nullptr;
		std::string result = manager.convert_text("SampleText", "Placeholder");
		ASSERT_EQ(result, "SampleText");
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleMultithreadedConvertTextWithPlaceholder)
	{
		manager.configurations.conditional_callback =
			[](const std::string& text) { return text.empty(); };

		std::vector<std::thread> threads;
		std::atomic<int> placeholder_count{ 0 };
		for (int i = 0; i < 10; i++)
		{
			threads.emplace_back([&]()
				{
					std::string result = manager.convert_text("", "PH");
					if (result == "PH")
					{
						placeholder_count++;
					}
				});
		}
		for (auto& t : threads)
		{
			t.join();
		}
		ASSERT_EQ(placeholder_count.load(), 10);
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleAsyncConvertTextWithPlaceholder)
	{
		manager.configurations.conditional_callback =
			[](const std::string& text) { return text.empty(); };

		auto future = std::async(std::launch::async, [&]()
			{
				return manager.convert_text("", "PH");
			});

		std::string result = future.get();
		ASSERT_EQ(result, "PH");
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleEmptyTextWithPlaceholder)
	{
		std::string result = manager.convert_text("", "PH");
		ASSERT_EQ(result, "PH");
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleVeryLongTextConversion)
	{
		std::string long_text(1000000, 'A');
		std::string result = manager.convert_text(long_text, "PH");
		ASSERT_EQ(result, long_text);
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleEmptyStringWithNonEmptyPlaceholder)
	{
		std::string input = "";
		std::string placeholder = "NonEmptyPH";
		manager.configurations.placeholder = placeholder;
		manager.configurations.conditional_callback = [](const std::string& text) { return text.empty(); };
		std::string result = manager.convert_text(input);
		ASSERT_EQ(result, placeholder);
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleMultipleAsyncConvertTextSimultaneously)
	{
		manager.configurations.placeholder = "AsyncPH";
		manager.configurations.conditional_callback = [](const std::string& text) { return text.empty(); };

		std::vector<std::future<std::string>> futures;
		for (int i = 0; i < 20; i++)
		{
			futures.push_back(std::async(std::launch::async, [&]() {
				return manager.convert_text("");
				}));
		}

		for (auto& future : futures)
		{
			std::string result = future.get();
			ASSERT_EQ(result, "AsyncPH");
		}
	}

	TEST_F(TextPlaceholderManagerTest, Should_HandleMultithreadedAsyncConvertText)
	{
		manager.configurations.placeholder = "MTAsyncPH";
		manager.configurations.conditional_callback = [](const std::string& text) { return text.empty(); };

		std::vector<std::thread> threads;
		std::atomic<int> success_count{ 0 };

		for (int i = 0; i < 10; i++)
		{
			threads.emplace_back([&]() {
				auto future = std::async(std::launch::async, [&]() {
					return manager.convert_text("");
					});
				if (future.get() == "MTAsyncPH")
				{
					success_count++;
				}
				});
		}

		for (auto& t : threads)
		{
			t.join();
		}

		ASSERT_EQ(success_count.load(), 10);
	}
}

#endif
