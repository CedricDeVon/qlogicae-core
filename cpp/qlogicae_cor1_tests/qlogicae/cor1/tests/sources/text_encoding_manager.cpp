#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextEncodingManager \
	)

#include "../includes/text_encoding_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(TextEncodingManagerTest, Should_ReturnEmpty_When_DecodeBase16EmptyString)
	{
		std::string result = encoding_manager.decode_base16("");
		ASSERT_TRUE(result.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnEmpty_When_EncodeBase16EmptyString)
	{
		std::string result = encoding_manager.encode_base16("");
		ASSERT_TRUE(result.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnDecoded_When_Base16ValidInput)
	{
		const std::string input = "48656C6C6F";
		const std::string expected = "Hello";
		std::string output = encoding_manager.decode_base16(input);
		ASSERT_EQ(output, expected);
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnEncoded_When_Base16ValidInput)
	{
		const std::string input = "Hello";
		const std::string expected = "48656C6C6F";
		std::string output = encoding_manager.encode_base16(input);
		ASSERT_EQ(output, expected);
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnDecoded_When_Base32ValidInput)
	{
		const std::string input = "JBSWY3DP";
		const std::string expected = "Hello";
		std::string output = encoding_manager.decode_base32(input);
		ASSERT_EQ(output, expected);
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnEncoded_When_Base32ValidInput)
	{
		const std::string input = "Hello";
		const std::string expected = "JBSWY3DP";
		std::string output = encoding_manager.encode_base32(input);
		ASSERT_EQ(output.substr(0, expected.size()), expected);
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnDecoded_When_Base64ValidInput)
	{
		const std::string input = "SGVsbG8=";
		const std::string expected = "Hello";
		std::string output = encoding_manager.decode_base64(input);
		ASSERT_EQ(output, expected);
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnEncoded_When_Base64ValidInput)
	{
		const std::string input = "Hello";
		const std::string expected = "SGVsbG8=";
		std::string output = encoding_manager.encode_base64(input);
		ASSERT_EQ(output, expected);
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnEmpty_When_InvalidBase32Input)
	{
		const std::string input = "!!!";
		std::string output = encoding_manager.decode_base32(input);
		ASSERT_TRUE(output.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_HandleConvertTextBase16ToBase64)
	{
		const std::string original = "48656C6C6F";
		std::string result = encoding_manager.convert_text(original,
			TextEncoding::BASE16, TextEncoding::BASE64);
		ASSERT_EQ(result, "SGVsbG8=");
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnNotEmpty_When_ConvertTextInvalidEncoding)
	{
		std::string result = encoding_manager.convert_text("abc",
			TextEncoding::NONE, TextEncoding::BASE64);
		ASSERT_FALSE(result.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_HandleMultithreadedEncoding)
	{
		const std::string input = "HelloWorld";
		std::vector<std::thread> threads;
		std::atomic<int> success_count{0};

		for (int i = 0; i < 10; i++)
		{
			threads.emplace_back([&]()
			{
				std::string encoded = encoding_manager.encode_base64(input);
				if (!encoded.empty())
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

	TEST_F(TextEncodingManagerTest, Should_HandleAsyncEncoding)
	{
		const std::string input = "HelloWorld";
		auto future = std::async(std::launch::async, [&]()
		{
			return encoding_manager.encode_base64(input);
		});

		std::string result = future.get();
		ASSERT_FALSE(result.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_HandleStressTestLargeInput)
	{
		std::string large_input(1000000, 'A');
		std::string encoded = encoding_manager.encode_base64(large_input);
		ASSERT_FALSE(encoded.empty());
	}

	INSTANTIATE_TEST_CASE_P(
		TextEncodingManagerConversions,
		TextEncodingManagerParameterizedTest,
		::testing::Values(
			std::make_tuple("48656C6C6F", TextEncoding::BASE16, TextEncoding::BASE16, "48656C6C6F"),
			std::make_tuple("48656C6C6F", TextEncoding::BASE16, TextEncoding::BASE32, "JBSWY3DP"),
			std::make_tuple("48656C6C6F", TextEncoding::BASE16, TextEncoding::BASE64, "SGVsbG8="),
			std::make_tuple("JBSWY3DP", TextEncoding::BASE32, TextEncoding::BASE16, "48656C6C6F"),
			std::make_tuple("JBSWY3DP", TextEncoding::BASE32, TextEncoding::BASE32, "JBSWY3DP"),
			std::make_tuple("JBSWY3DP", TextEncoding::BASE32, TextEncoding::BASE64, "SGVsbG8="),
			std::make_tuple("SGVsbG8=", TextEncoding::BASE64, TextEncoding::BASE16, "48656C6C6F"),
			std::make_tuple("SGVsbG8=", TextEncoding::BASE64, TextEncoding::BASE32, "JBSWY3DP"),
			std::make_tuple("SGVsbG8=", TextEncoding::BASE64, TextEncoding::BASE64, "SGVsbG8=")
		)
	);

	TEST_P(TextEncodingManagerParameterizedTest, Should_ConvertTextToExpectedResult_When_ValidInput)
	{
		const auto& [input, original_encoding, target_encoding, expected_output] = GetParam();
		std::string result = encoding_manager.convert_text(input, original_encoding, target_encoding);
		ASSERT_EQ(result, expected_output);
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnEmpty_When_DecodeBase32EmptyString)
	{
		std::string result = encoding_manager.decode_base32("");
		ASSERT_TRUE(result.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnEmpty_When_EncodeBase32EmptyString)
	{
		std::string result = encoding_manager.encode_base32("");
		ASSERT_TRUE(result.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnEmpty_When_DecodeBase16InvalidInput)
	{
		std::string result = encoding_manager.decode_base16("ZZ");
		ASSERT_TRUE(result.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnEmpty_When_DecodeBase16OddLength)
	{
		std::string result = encoding_manager.decode_base16("ABC");
		ASSERT_TRUE(result.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_HandleLowercaseBase16)
	{
		const std::string input = "48656c6c6f";
		const std::string expected = "Hello";
		std::string output = encoding_manager.decode_base16(input);
		ASSERT_EQ(output, expected);
	}

	TEST_F(TextEncodingManagerTest, Should_HandleLowercaseBase32)
	{
		const std::string input = "jbswy3dp";
		const std::string expected = "Hello";
		std::string output = encoding_manager.decode_base32(input);
		ASSERT_EQ(output, expected);
	}

	TEST_F(TextEncodingManagerTest, Should_HandleBase64WithoutPadding)
	{
		const std::string input = "SGVsbG8";
		const std::string expected = "Hello";
		std::string output = encoding_manager.decode_base64(input);
		ASSERT_EQ(output, expected);
	}

	TEST_F(TextEncodingManagerTest, Should_HandleRoundTripBase16)
	{
		const std::string input = "HelloWorld";
		std::string encoded = encoding_manager.encode_base16(input);
		std::string decoded = encoding_manager.decode_base16(encoded);
		ASSERT_EQ(decoded, input);
	}

	TEST_F(TextEncodingManagerTest, Should_HandleRoundTripBase32)
	{
		const std::string input = "HelloWorld";
		std::string encoded = encoding_manager.encode_base32(input);
		std::string decoded = encoding_manager.decode_base32(encoded);
		ASSERT_EQ(decoded, input);
	}

	TEST_F(TextEncodingManagerTest, Should_HandleRoundTripBase64)
	{
		const std::string input = "HelloWorld";
		std::string encoded = encoding_manager.encode_base64(input);
		std::string decoded = encoding_manager.decode_base64(encoded);
		ASSERT_EQ(decoded, input);
	}

	TEST_F(TextEncodingManagerTest, Should_HandleBinaryDataBase16)
	{
		std::string input = "\x00\xFF\x10\x80";
		std::string encoded = encoding_manager.encode_base16(input);
		std::string decoded = encoding_manager.decode_base16(encoded);
		ASSERT_EQ(decoded, input);
	}

	TEST_F(TextEncodingManagerTest, Should_HandleBinaryDataBase32)
	{
		std::string input = "\x00\xFF\x10\x80";
		std::string encoded = encoding_manager.encode_base32(input);
		std::string decoded = encoding_manager.decode_base32(encoded);
		ASSERT_EQ(decoded, input);
	}

	TEST_F(TextEncodingManagerTest, Should_HandleBinaryDataBase64)
	{
		std::string input = "\x00\xFF\x10\x80";
		std::string encoded = encoding_manager.encode_base64(input);
		std::string decoded = encoding_manager.decode_base64(encoded);
		ASSERT_EQ(decoded, input);
	}

	TEST_F(TextEncodingManagerTest, Should_HandleConvertTextBase32ToBase16)
	{
		const std::string original = "JBSWY3DP";
		std::string result = encoding_manager.convert_text(original, TextEncoding::BASE32, TextEncoding::BASE16);
		ASSERT_EQ(result, "48656C6C6F");
	}

	TEST_F(TextEncodingManagerTest, Should_HandleConvertTextBase64ToBase16)
	{
		const std::string original = "SGVsbG8=";
		std::string result = encoding_manager.convert_text(original, TextEncoding::BASE64, TextEncoding::BASE16);
		ASSERT_EQ(result, "48656C6C6F");
	}

	TEST_F(TextEncodingManagerTest, Should_HandleConvertTextIdentity)
	{
		const std::string original = "TestInput";
		std::string result = encoding_manager.convert_text(original, TextEncoding::BASE16, TextEncoding::BASE16);
		ASSERT_EQ(result, original);
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnNotEmpty_When_ConvertTextNoneToValid)
	{
		std::string result = encoding_manager.convert_text("abc", TextEncoding::NONE, TextEncoding::BASE16);
		ASSERT_FALSE(result.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnNotEmpty_When_ConvertTextValidToNone)
	{
		std::string result = encoding_manager.convert_text("48656C6C6F", TextEncoding::BASE16, TextEncoding::NONE);
		ASSERT_FALSE(result.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnEmpty_When_PartialInvalidBase32)
	{
		const std::string input = "JBSW!3DP";
		std::string output = encoding_manager.decode_base32(input);
		ASSERT_TRUE(output.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_ReturnEmpty_When_PartialInvalidBase64)
	{
		const std::string input = "SGVsbG8$";
		std::string output = encoding_manager.decode_base64(input);
		ASSERT_TRUE(output.empty());
	}

	TEST_F(TextEncodingManagerTest, Should_HandleMultithreadedBase16Encoding)
	{
		const std::string input = "HelloWorld";
		std::vector<std::thread> threads;
		std::atomic<int> success_count{ 0 };

		for (int i = 0; i < 10; i++)
		{
			threads.emplace_back([&]()
				{
					std::string encoded = encoding_manager.encode_base16(input);
					if (!encoded.empty())
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

	TEST_F(TextEncodingManagerTest, Should_HandleMultithreadedBase32Encoding)
	{
		const std::string input = "HelloWorld";
		std::vector<std::thread> threads;
		std::atomic<int> success_count{ 0 };

		for (int i = 0; i < 10; i++)
		{
			threads.emplace_back([&]()
				{
					std::string encoded = encoding_manager.encode_base32(input);
					if (!encoded.empty())
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

	TEST_F(TextEncodingManagerTest, Should_HandleConvertTextBinaryData)
	{
		std::string input = "\x00\xFF\x10\x80";
		std::string encoded_base16 = encoding_manager.convert_text(input, TextEncoding::BASE16, TextEncoding::BASE16);
		std::string encoded_base32 = encoding_manager.convert_text(input, TextEncoding::BASE32, TextEncoding::BASE32);
		std::string encoded_base64 = encoding_manager.convert_text(input, TextEncoding::BASE64, TextEncoding::BASE64);

		ASSERT_EQ(encoded_base16, encoding_manager.encode_base16(input));
		ASSERT_EQ(encoded_base32.substr(0, encoding_manager.encode_base32(input).size()), encoding_manager.encode_base32(input));
		ASSERT_EQ(encoded_base64, encoding_manager.encode_base64(input));
	}
}

#endif
