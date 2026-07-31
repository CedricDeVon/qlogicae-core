#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextManager \
	)

#include "../includes/text_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(TextManagerTest, Should_ReturnSameSingletonInstance_When_CalledMultipleTimes)
	{
		auto& instance1 = SingletonManager::get_singleton<TextManager>();
		auto& instance2 = SingletonManager::get_singleton<TextManager>();
		ASSERT_EQ(&instance1, &instance2);
	}

	TEST_F(TextManagerTest, Should_ConstructAndDestructSuccessfully)
	{
		ASSERT_TRUE(manager.construct());
		ASSERT_TRUE(manager.destruct());
	}

	TEST_F(TextManagerTest, Should_HandleConstructFailure_When_SodiumInitFails)
	{
		struct TextManagerMock : TextManager
		{
			bool construct_override()
			{
				return false;
			}
		};

		TextManagerMock mock_manager;
		ASSERT_FALSE(mock_manager.construct_override());
	}

	TEST_P(TextManagerConvertTextParameterizedTest,
		Should_ConvertTextBetweenStringAndWStringCorrectly)
	{
		const auto& [input_text, expected_output, use_empty] = GetParam();

		std::string input_str = use_empty ? "" : input_text;
		std::wstring input_wstr = std::wstring(input_str.begin(), input_str.end());

		std::string output_str = manager.convert_text<std::wstring, std::string>(input_wstr);
		std::wstring output_wstr = manager.convert_text<std::string, std::wstring>(input_str);

		ASSERT_EQ(output_str, input_str);
		ASSERT_EQ(output_wstr, input_wstr);
	}

	INSTANTIATE_TEST_CASE_P(
		TextManagerConversions,
		TextManagerConvertTextParameterizedTest,
		::testing::Values(
			std::make_tuple("Hello", "Hello", false),
			std::make_tuple("", "", true),
			std::make_tuple(std::string(1000000, 'A'), std::string(1000000, 'A'), false)
		)
	);

	TEST_F(TextManagerTest, Should_ReturnEmpty_When_InvalidConvertTextType)
	{
		struct Dummy {};
		auto result = manager.convert_text<Dummy, std::string>(Dummy{});
		ASSERT_TRUE(result.empty());
	}

	TEST_F(TextManagerTest, Should_HandleReplaceTextTokens_NormalAndEmptyDictionary)
	{
		std::unordered_map<std::string, std::string> dictionary{
			{"A", "X"}, {"B", "Y"} };

		std::string result = manager.replace_text_tokens("ABCD", dictionary);
		ASSERT_EQ(result, "XYCD");

		std::unordered_map<std::string, std::string> empty_dict;
		result = manager.replace_text_tokens("ABCD", empty_dict);
		ASSERT_EQ(result, "ABCD");
	}

	TEST_F(TextManagerTest, Should_HandleReplaceTextTokens_MultipleReplacements)
	{
		std::unordered_map<std::string, std::string> dictionary{
			{"A", "1"}, {"B", "2"}, {"C", "3"} };

		std::string result = manager.replace_text_tokens("ABCABC", dictionary);
		ASSERT_EQ(result, "123123");
	}

	TEST_F(TextManagerTest, Should_HandleReplaceTextTokens_NoMatch)
	{
		std::unordered_map<std::string, std::string> dictionary{
			{"X", "1"} };

		std::string result = manager.replace_text_tokens("ABC", dictionary);
		ASSERT_EQ(result, "ABC");
	}

	TEST_F(TextManagerTest, Should_HandleAsyncReplaceTextTokens)
	{
		std::unordered_map<std::string, std::string> dictionary{
			{"A", "X"} };

		auto future = std::async(std::launch::async, [&]()
			{
				return manager.replace_text_tokens("A", dictionary);
			});

		ASSERT_EQ(future.get(), "X");
	}

	TEST_F(TextManagerTest, Should_HandleMultithreadedReplaceTextTokens)
	{
		std::unordered_map<std::string, std::string> dictionary{
			{"A", "X"} };

		std::vector<std::thread> threads;
		std::atomic<int> success_count{ 0 };
		for (int i = 0; i < 10; i++)
		{
			threads.emplace_back([&]()
				{
					std::string result = manager.replace_text_tokens("A", dictionary);
					if (result == "X") success_count++;
				});
		}
		for (auto& t : threads) t.join();
		ASSERT_EQ(success_count.load(), 10);
	}

	TEST_F(TextManagerTest, Should_HandleStressReplaceTextTokens)
	{
		std::unordered_map<std::string, std::string> dictionary{
			{"A", "B"} };

		std::string large_text(1000000, 'A');

		for (int i = 0; i < 10; i++)
		{
			std::string result = manager.replace_text_tokens(large_text, dictionary);
			ASSERT_EQ(result, std::string(1000000, 'B'));
		}
	}

	TEST_F(TextManagerTest, Should_HandleSplitText_NormalEmptyAndConsecutiveDelimiters)
	{
		std::vector<std::string> result =
			manager.split_text("A,B,C", ",");
		ASSERT_EQ(result.size(), 3);
		ASSERT_EQ(result[0], "A");
		ASSERT_EQ(result[1], "B");
		ASSERT_EQ(result[2], "C");

		result = manager.split_text("", ",");
		ASSERT_TRUE(result.empty());

		result = manager.split_text("A,,B", ",");
		ASSERT_EQ(result.size(), 3);
		ASSERT_EQ(result[0], "A");
		ASSERT_EQ(result[1], "");
		ASSERT_EQ(result[2], "B");
	}

	TEST_F(TextManagerTest, Should_HandleSplitText_EmptyDelimiter)
	{
		std::vector<std::string> result =
			manager.split_text("ABC", "");
		ASSERT_EQ(result.size(), 3);
		ASSERT_EQ(result[0], "A");
		ASSERT_EQ(result[1], "B");
		ASSERT_EQ(result[2], "C");
	}

	TEST_F(TextManagerTest, Should_HandleAsyncSplitText)
	{
		auto future = std::async(std::launch::async, [&]()
			{
				return manager.split_text("A,B,C", ",");
			});

		std::vector<std::string> result = future.get();
		ASSERT_EQ(result.size(), 3);
		ASSERT_EQ(result[0], "A");
		ASSERT_EQ(result[1], "B");
		ASSERT_EQ(result[2], "C");
	}

	TEST_F(TextManagerTest, Should_HandleMultithreadedSplitText)
	{
		std::atomic<int> success_count{ 0 };
		std::vector<std::thread> threads;
		for (int i = 0; i < 10; i++)
		{
			threads.emplace_back([&]()
				{
					std::vector<std::string> result =
						manager.split_text("A,B", ",");
					if (result.size() == 2 &&
						result[0] == "A" &&
						result[1] == "B")
					{
						success_count++;
					}
				});
		}
		for (auto& t : threads) t.join();
		ASSERT_EQ(success_count.load(), 10);
	}

	TEST_F(TextManagerTest, Should_HandleStressSplitText)
	{
		std::string large_text(1000000, 'A');
		for (size_t i = 0; i < large_text.size(); i += 100) large_text[i] = ',';

		for (int i = 0; i < 5; i++)
		{
			std::vector<std::string> result =
				manager.split_text(large_text, ",");
			ASSERT_FALSE(result.empty());
		}
	}

	TEST_P(
		TextManagerReplaceParameterizedTest,
		Should_ReturnExpectedText_When_ReplaceTextTokensParameterized)
	{
		const auto& [input_text, dictionary, expected] = GetParam();

		std::string result =
			manager.replace_text_tokens(
				input_text,
				dictionary);

		ASSERT_EQ(result, expected);
	}

	TEST_P(
		TextManagerSplitParameterizedTest,
		Should_SplitTextCorrectly_When_Parameterized)
	{
		const auto& [input_text, delimiter, expected_size] = GetParam();

		std::vector<std::string> result =
			manager.split_text(
				input_text,
				delimiter);

		ASSERT_EQ(result.size(), expected_size);
	}
	INSTANTIATE_TEST_CASE_P(
		TextManagerReplaceTextTokens,
		TextManagerReplaceParameterizedTest,
		::testing::Values(
			std::make_tuple(
				"",
				std::unordered_map<std::string, std::string>{},
				""),
			std::make_tuple(
				"",
				std::unordered_map<std::string, std::string>{
					{"A", "1"}},
				""),
			std::make_tuple(
				"A",
				std::unordered_map<std::string, std::string>{},
				"A"),
			std::make_tuple(
				"A",
				std::unordered_map<std::string, std::string>{
					{"A", "1"}},
				"1"),
			std::make_tuple(
				"ABC",
				std::unordered_map<std::string, std::string>{
					{"A", "1"}},
				"1BC"),
			std::make_tuple(
				"ABC",
				std::unordered_map<std::string, std::string>{
					{"A", "1"}, { "B", "2" }},
				"12C"),
			std::make_tuple(
				"ABC",
				std::unordered_map<std::string, std::string>{
					{"A", "1"}, { "B", "2" }, { "C", "3" }},
				"123"),
			std::make_tuple(
				"AAAA",
				std::unordered_map<std::string, std::string>{
					{"A", "B"}},
				"BBBB"),
			std::make_tuple(
				"ABABAB",
				std::unordered_map<std::string, std::string>{
					{"A", "X"}, { "B", "Y" }},
				"XYXYXY"),
			std::make_tuple(
				"ABCDEF",
				std::unordered_map<std::string, std::string>{
					{"X", "1"}},
				"ABCDEF"),
			std::make_tuple(
				std::string(100000, 'A'),
				std::unordered_map<std::string, std::string>{
					{"A", "B"}},
				std::string(100000, 'B'))
		)
	);

	INSTANTIATE_TEST_CASE_P(
		TextManagerSplitText,
		TextManagerSplitParameterizedTest,
		::testing::Values(
			std::make_tuple(
				"",
				",",
				static_cast<size_t>(0)),
			std::make_tuple(
				",",
				",",
				static_cast<size_t>(2)),
			std::make_tuple(
				",,",
				",",
				static_cast<size_t>(3)),
			std::make_tuple(
				"A",
				",",
				static_cast<size_t>(1)),
			std::make_tuple(
				"A,B",
				",",
				static_cast<size_t>(2)),
			std::make_tuple(
				"A,,B",
				",",
				static_cast<size_t>(3)),
			std::make_tuple(
				",A,B,",
				",",
				static_cast<size_t>(4)),
			std::make_tuple(
				"ABC",
				"",
				static_cast<size_t>(3)),
			std::make_tuple(
				"AAAA",
				"A",
				static_cast<size_t>(5)),
			std::make_tuple(
				"A|B|C|D",
				"|",
				static_cast<size_t>(4)),
			std::make_tuple(
				std::string(100000, 'A'),
				"A",
				static_cast<size_t>(100001))
		)
	);

	TEST_F(
		TextManagerTest,
		Should_HandleConcurrentStressReplaceTextTokens)
	{
		std::unordered_map<std::string, std::string> dictionary{
			{"A", "B"} };

		std::string input_text(
			500000,
			'A');

		std::atomic<int> success_count{ 0 };
		std::vector<std::thread> threads;

		for (int i = 0; i < 8; i++)
		{
			threads.emplace_back(
				[&]()
				{
					std::string result =
						manager.replace_text_tokens(
							input_text,
							dictionary);

					if (result ==
						std::string(500000, 'B'))
					{
						success_count.fetch_add(1);
					}
				});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		ASSERT_EQ(success_count.load(), 8);
	}

	TEST_F(
		TextManagerTest,
		Should_HandleAsyncFailurePaths_When_InvalidConvertTextAsync)
	{
		auto future =
			std::async(
				std::launch::async,
				[&]()
				{
					struct InvalidType {};
					return manager.convert_text<
						InvalidType,
						std::string>(InvalidType{});
				});

		std::string result = future.get();
		ASSERT_TRUE(result.empty());
	}

	TEST_F(
		TextManagerTest,
		Should_NotThrow_When_SplitTextUnderConcurrentStress)
	{
		std::string large_text(
			500000,
			'A');

		for (size_t i = 0; i < large_text.size(); i += 50)
		{
			large_text[i] = ',';
		}

		std::atomic<int> completion_count{ 0 };
		std::vector<std::thread> threads;

		for (int i = 0; i < 6; i++)
		{
			threads.emplace_back(
				[&]()
				{
					EXPECT_NO_THROW(
						manager.split_text(
							large_text,
							","));
					completion_count.fetch_add(1);
				});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		ASSERT_EQ(completion_count.load(), 6);
	}

	TEST_F(
		TextManagerTest,
		Should_ConvertUnicodeTextCorrectly_When_ValidUtf8)
	{
		std::string utf8_text =
			"\xE3\x81\x93\xE3\x82\x93\xE3\x81\xAB"
			"\xE3\x81\xA1\xE3\x81\xAF\xE4\xB8\x96"
			"\xE7\x95\x8C";

		std::wstring wide_text =
			manager.convert_text<
			std::string,
			std::wstring>(utf8_text);

		std::string roundtrip_text =
			manager.convert_text<
			std::wstring,
			std::string>(wide_text);

		ASSERT_EQ(roundtrip_text, utf8_text);
	}

	TEST_F(
		TextManagerTest,
		Should_ReturnEmpty_When_InvalidUtf8Sequence)
	{
		std::string invalid_utf8;
		invalid_utf8.push_back(
			static_cast<char>(0xFF));

		std::wstring result =
			manager.convert_text<
			std::string,
			std::wstring>(invalid_utf8);

		ASSERT_FALSE(result.empty());
	}

	TEST_F(
		TextManagerTest,
		Should_ReturnSameString_When_ConvertStringToString)
	{
		std::string input_text = "Passthrough";
		std::string result =
			manager.convert_text<
			std::string,
			std::string>(input_text);
		ASSERT_EQ(result, input_text);
	}

	TEST_F(
		TextManagerTest,
		Should_ReturnSameWString_When_ConvertWStringToWString)
	{
		std::wstring input_text = L"WidePassthrough";
		std::wstring result =
			manager.convert_text<
			std::wstring,
			std::wstring>(input_text);
		ASSERT_EQ(result, input_text);
	}

	TEST_F(
		TextManagerTest,
		Should_SplitTextWithMultiCharacterDelimiter_When_Present)
	{
		std::vector<std::string> result =
			manager.split_text(
				"A--B--C",
				"--");

		ASSERT_EQ(result.size(), 3);
		ASSERT_EQ(result[0], "A");
		ASSERT_EQ(result[1], "B");
		ASSERT_EQ(result[2], "C");
	}

	TEST_F(
		TextManagerTest,
		Should_ReturnSingleElement_When_DelimiterNotFound)
	{
		std::vector<std::string> result =
			manager.split_text(
				"ABC",
				",");

		ASSERT_EQ(result.size(), 1);
		ASSERT_EQ(result[0], "ABC");
	}

	TEST_F(
		TextManagerTest,
		Should_HandleDelimiterLongerThanText)
	{
		std::vector<std::string> result =
			manager.split_text(
				"A",
				"LONG");

		ASSERT_EQ(result.size(), 1);
		ASSERT_EQ(result[0], "A");
	}

	TEST_F(
		TextManagerTest,
		Should_ReplaceOverlappingKeysDeterministically)
	{
		std::unordered_map<
			std::string,
			std::string> dictionary{
			{"AA", "X"},
			{"A", "Y"} };

		std::string result =
			manager.replace_text_tokens(
				"AAAA",
				dictionary);

		ASSERT_FALSE(result.empty());
	}

	TEST_F(
		TextManagerTest,
		Should_HandleEmptyReplacementValue)
	{
		std::unordered_map<
			std::string,
			std::string> dictionary{
			{"A", ""} };

		std::string result =
			manager.replace_text_tokens(
				"ABA",
				dictionary);

		ASSERT_EQ(result, "B");
	}

	TEST_F(
		TextManagerTest,
		Should_HandleLargeReplacementDictionary)
	{
		std::unordered_map<
			std::string,
			std::string> dictionary;

		for (int index = 0; index < 1000; index++)
		{
			dictionary.emplace(
				std::to_string(index),
				"X");
		}

		std::string input_text = "999";
		std::string result =
			manager.replace_text_tokens(
				input_text,
				dictionary);

		ASSERT_EQ(result, "X");
	}

	TEST_F(
		TextManagerTest,
		Should_RemainFunctional_After_ExceptionLikeFailure)
	{
		struct InvalidType {};
		std::string invalid_result =
			manager.convert_text<
			InvalidType,
			std::string>(InvalidType{});

		ASSERT_TRUE(invalid_result.empty());

		std::string valid_result =
			manager.convert_text<
			std::string,
			std::string>("OK");

		ASSERT_EQ(valid_result, "OK");
	}

	TEST_F(
		TextManagerTest,
		Should_HandleReplaceTextTokens_WithEmptyInputAndNonEmptyDictionary)
	{
		std::unordered_map<std::string, std::string> dictionary{
			{"A", "B"} };

		std::string result =
			manager.replace_text_tokens(
				"",
				dictionary);

		ASSERT_TRUE(result.empty());
	}

	TEST_F(
		TextManagerTest,
		Should_HandleReplaceTextTokens_WithEmptyKeys)
	{
		std::unordered_map<std::string, std::string> dictionary{
			{"", "X"} };

		std::string result =
			manager.replace_text_tokens(
				"ABC",
				dictionary);

		ASSERT_EQ(result, "ABC");
	}

	TEST_F(
		TextManagerTest,
		Should_HandleSplitText_WithWhitespaceDelimiter)
	{
		std::vector<std::string> result =
			manager.split_text(
				"A B  C",
				" ");

		ASSERT_EQ(result.size(), 4);
		ASSERT_EQ(result[0], "A");
		ASSERT_EQ(result[1], "B");
		ASSERT_EQ(result[2], "");
		ASSERT_EQ(result[3], "C");
	}

	TEST_F(
		TextManagerTest,
		Should_HandleSplitText_WithRepeatedMultiCharacterDelimiter)
	{
		std::vector<std::string> result =
			manager.split_text(
				"A----B",
				"--");

		ASSERT_EQ(result.size(), 3);
		ASSERT_EQ(result[0], "A");
		ASSERT_EQ(result[1], "");
		ASSERT_EQ(result[2], "B");
	}

	TEST_F(
		TextManagerTest,
		Should_HandleConvertText_WithEmptyWideString)
	{
		std::wstring input_text;
		std::string result =
			manager.convert_text<
			std::wstring,
			std::string>(input_text);

		ASSERT_TRUE(result.empty());
	}

	TEST_F(
		TextManagerTest,
		Should_HandleConvertText_WithEmptyString)
	{
		std::string input_text;
		std::wstring result =
			manager.convert_text<
			std::string,
			std::wstring>(input_text);

		ASSERT_TRUE(result.empty());
	}

	TEST_F(
		TextManagerTest,
		Should_HandleConcurrentConvertTextStress)
	{
		std::atomic<int> success_count{ 0 };
		std::vector<std::thread> threads;

		for (int index = 0; index < 8; index++)
		{
			threads.emplace_back(
				[&]()
				{
					std::string input =
						"ConcurrentText";

					std::wstring wide =
						manager.convert_text<
						std::string,
						std::wstring>(input);

					std::string roundtrip =
						manager.convert_text<
						std::wstring,
						std::string>(wide);

					if (roundtrip == input)
					{
						success_count.fetch_add(1);
					}
				});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		ASSERT_EQ(success_count.load(), 8);
	}

	TEST_F(
		TextManagerTest,
		Should_HandleSplitText_When_AllCharactersAreDelimiters)
	{
		std::vector<std::string> result =
			manager.split_text(
				",,,",
				",");

		ASSERT_EQ(result.size(), 4);
	}

	TEST_F(
		TextManagerTest,
		Should_HandleReplaceTextTokens_WithNumericKeys)
	{
		std::unordered_map<std::string, std::string> dictionary{
			{"1", "A"},
			{"2", "B"} };

		std::string result =
			manager.replace_text_tokens(
				"1212",
				dictionary);

		ASSERT_EQ(result, "ABAB");
	}

	TEST_F(
		TextManagerTest,
		Should_HandleReplaceTextTokens_WithUnicodeText)
	{
		std::unordered_map<std::string, std::string> dictionary{
			{"世", "X"},
			{"界", "Y"} };

		std::string input_text =
			"\xE4\xB8\x96\xE7\x95\x8C";

		std::string result =
			manager.replace_text_tokens(
				input_text,
				dictionary);

		ASSERT_FALSE(result.empty());
	}
}

#endif
