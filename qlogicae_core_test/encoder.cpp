#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{
    class EncoderTest : public ::testing::TestWithParam<std::any> {
    protected:
        QLogicaeCore::Encoder& encoder = QLogicaeCore::Encoder::instance();
    };

    TEST_F(EncoderTest, Should_Expect_ValidBase64_When_EncodingUTF8) {
        std::string input = "Hello, World!";
        std::string encoded = encoder.from_utf8_to_base64(input);
        EXPECT_FALSE(encoded.empty());
    }

    TEST_F(EncoderTest, Should_Expect_OriginalUTF8_When_EncodingAndDecoding) {
        std::string input = "SampleTest123";
        std::string encoded = encoder.from_utf8_to_base64(input);
        std::string decoded = encoder.from_base64_to_utf8(encoded);
        EXPECT_EQ(decoded, input);
    }

    TEST_F(EncoderTest, Should_Expect_Hex_When_EncodingUTF8) {
        std::string input = "ABC";
        std::string hex = encoder.from_utf8_to_hex(input);
        EXPECT_EQ(hex, "414243");
    }

    TEST_F(EncoderTest, Should_Expect_UTF8_When_DecodingHex) {
        std::string hex = "48656c6c6f";
        std::string utf8 = encoder.from_hex_to_utf8(hex);
        EXPECT_EQ(utf8, "Hello");
    }

    TEST_F(EncoderTest, Should_Expect_Base64Hex_When_ConvertedFromHex) {
        std::string hex = encoder.from_utf8_to_hex("test");
        std::string base64 = encoder.from_hex_to_base64(hex);
        EXPECT_FALSE(base64.empty());
    }

    TEST_F(EncoderTest, Should_Expect_UTF16_When_ConvertingFromUTF8) {
        std::wstring utf16 = encoder.from_utf8_to_utf16("hello");
        EXPECT_FALSE(utf16.empty());
    }

    TEST_F(EncoderTest, Should_Expect_UTF8_When_ConvertingFromUTF16) {
        std::wstring wide = L"data";
        std::string utf8 = encoder.from_utf16_to_utf8(wide);
        EXPECT_EQ(utf8, "data");
    }

    TEST_F(EncoderTest, Should_Expect_CorrectHex_When_ConvertingFromBytes) {
        std::string data = "1234";
        std::string hex = encoder.from_bytes_to_hex(reinterpret_cast<const unsigned char*>(data.data()), data.size());
        EXPECT_EQ(hex, "31323334");
    }

    TEST_F(EncoderTest, Should_Expect_CorrectBytes_When_ConvertingFromHex) {
        std::vector<unsigned char> bytes = encoder.from_hex_to_bytes("31323334");
        EXPECT_EQ(std::string(bytes.begin(), bytes.end()), "1234");
    }

    TEST_F(EncoderTest, Should_Expect_CorrectBase64_When_ConvertingFromBytes) {
        std::string data = "abcd";
        std::string base64 = encoder.from_bytes_to_base64(reinterpret_cast<const unsigned char*>(data.data()), data.size());
        EXPECT_FALSE(base64.empty());
    }

    TEST_F(EncoderTest, Should_Expect_CorrectBytes_When_ConvertingFromBase64) {
        std::string base64 = encoder.from_utf8_to_base64("test");
        auto bytes = encoder.from_base64_to_bytes(base64);
        EXPECT_EQ(std::string(bytes.begin(), bytes.end()), "test");
    }

    TEST_F(EncoderTest, Should_Expect_EmptyString_When_InvalidHex) {
        std::string utf8 = encoder.from_hex_to_utf8("nothex");
        EXPECT_TRUE(utf8.empty());
    }

    TEST_F(EncoderTest, Should_Expect_EmptyString_When_InvalidBase64) {
        std::string utf8 = encoder.from_base64_to_utf8("@@@!!");
        EXPECT_TRUE(utf8.empty());
    }

    TEST_F(EncoderTest, Should_Expect_CorrectOutput_When_ParallelHexConversions) {
        std::vector<std::thread> threads;
        std::vector<std::string> results(8);
        for (int i = 0; i < 8; ++i) {
            threads.emplace_back([&, i]() {
                results[i] = encoder.from_utf8_to_hex("threaded" + std::to_string(i));
                });
        }
        for (auto& t : threads) t.join();
        for (const auto& hex : results) {
            EXPECT_FALSE(hex.empty());
        }
    }

    TEST_F(EncoderTest, Should_Expect_Under2Seconds_When_BulkBase64Conversions) {
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < 1000; ++i) {
            encoder.from_utf8_to_base64("performance-test-string-" + std::to_string(i));
        }
        auto end = std::chrono::steady_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(), 2000);
    }

    TEST_F(EncoderTest, Should_Expect_UnderMicrosecond_When_SingleCallHex) {
        auto start = std::chrono::high_resolution_clock::now();
        encoder.from_utf8_to_hex("fast");
        auto end = std::chrono::high_resolution_clock::now();
        EXPECT_LE(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(), 1000);
    }

    TEST_P(EncoderTest, Should_Expect_NoThrow_When_ConvertingVariousTypes) {
        auto param = GetParam();
        if (param.type() == typeid(std::string)) {
            std::string s = std::any_cast<std::string>(param);
            EXPECT_NO_THROW(encoder.from_utf8_to_base64(s));
            EXPECT_NO_THROW(encoder.from_utf8_to_hex(s));
        }
        else if (param.type() == typeid(std::wstring)) {
            std::wstring ws = std::any_cast<std::wstring>(param);
            EXPECT_NO_THROW(encoder.from_utf16_to_utf8(ws));
        }
    }

    INSTANTIATE_TEST_CASE_P(
        EncoderTest_Parameterized,
        EncoderTest,
        ::testing::Values(
            std::any(std::string("48656c6c6f")),
            std::any(std::string("SGVsbG8=")),
            std::any(std::wstring(L"Text")),
            std::any(std::string("1234")),
            std::any(std::string("test"))
        )
    );

    TEST_F(EncoderTest, Should_Expect_No_Throw_When_CorruptBase64ToUtf8Access) {
        EXPECT_NO_THROW({
            auto s = encoder.from_base64_to_utf8("@@@@");
            static_cast<void>(s);
            });
    }

}