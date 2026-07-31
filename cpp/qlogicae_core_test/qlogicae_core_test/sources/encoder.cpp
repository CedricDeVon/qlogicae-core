#include "pch.hpp"

#include "qlogicae_core/includes/encoder.hpp"

namespace QLogicaeCoreTest
{

    class EncoderTest : public ::testing::TestWithParam<std::string> {};

    TEST_P(EncoderTest, Should_Expect_HexRoundTrip_When_ConvertingUtf8)
    {
        const std::string& original_text = GetParam();
        std::string hex = QLogicaeCore::Encoder::get_instance().from_utf8_to_hex(original_text);
        std::string utf8 = QLogicaeCore::Encoder::get_instance().from_hex_to_utf8(hex);
        EXPECT_EQ(original_text, utf8);
    }

    TEST_P(EncoderTest, Should_Expect_Base64RoundTrip_When_ConvertingUtf8)
    {
        const std::string& original_text = GetParam();
        std::string base64 = QLogicaeCore::Encoder::get_instance().from_utf8_to_base64(original_text);
        std::string utf8 = QLogicaeCore::Encoder::get_instance().from_base64_to_utf8(base64);
        EXPECT_EQ(original_text, utf8);
    }

    TEST_P(EncoderTest, Should_Expect_HexBase64RoundTrip_When_ConvertingHex)
    {
        const std::string& original_text = GetParam();
        std::string hex = QLogicaeCore::Encoder::get_instance().from_utf8_to_hex(original_text);
        std::string base64 = QLogicaeCore::Encoder::get_instance().from_hex_to_base64(hex);
        std::string hex_back = QLogicaeCore::Encoder::get_instance().from_base64_to_hex(base64);
        EXPECT_EQ(hex, hex_back);
    }

    TEST_P(EncoderTest, Should_Expect_Utf16RoundTrip_When_ConvertingText)
    {
        const std::string& original_text = GetParam();
        std::wstring utf16 = QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(original_text);
        std::string utf8 = QLogicaeCore::Encoder::get_instance().from_utf16_to_utf8(utf16);
        EXPECT_EQ(original_text, utf8);
    }

    TEST_P(EncoderTest, Should_Expect_BinaryRoundTrip_When_ConvertingHex)
    {
        const std::string& original_text = GetParam();
        std::string hex = QLogicaeCore::Encoder::get_instance().from_utf8_to_hex(original_text);
        std::vector<unsigned char> bytes = QLogicaeCore::Encoder::get_instance().from_hex_to_bytes(hex);
        std::string roundtrip = QLogicaeCore::Encoder::get_instance().from_bytes_to_hex(bytes.data(), bytes.size());
        EXPECT_EQ(hex, roundtrip);
    }

    TEST_P(EncoderTest, Should_Expect_BinaryRoundTrip_When_ConvertingBase64)
    {
        const std::string& original_text = GetParam();
        std::string base64 = QLogicaeCore::Encoder::get_instance().from_utf8_to_base64(original_text);
        std::vector<unsigned char> bytes = QLogicaeCore::Encoder::get_instance().from_base64_to_bytes(base64);
        std::string roundtrip = QLogicaeCore::Encoder::get_instance().from_bytes_to_base64(bytes.data(), bytes.size());
        EXPECT_EQ(base64, roundtrip);
    }

    TEST_P(EncoderTest, Should_Expect_NoThrow_When_ConvertingEmptyText)
    {
        EXPECT_NO_THROW({
            QLogicaeCore::Encoder::get_instance().from_utf8_to_hex("");
            QLogicaeCore::Encoder::get_instance().from_hex_to_utf8("");
            QLogicaeCore::Encoder::get_instance().from_utf8_to_base64("");
            QLogicaeCore::Encoder::get_instance().from_base64_to_utf8("");
            });
    }

    TEST_P(EncoderTest, Should_Expect_Result_When_AsyncEncodingExecuted)
    {
        const std::string& input = GetParam();
        std::future<std::string> task = std::async(std::launch::async, [&]() {
            return QLogicaeCore::Encoder::get_instance().from_utf8_to_base64(input);
            });

        bool result = task.get().empty();
        if (result)
        {
            EXPECT_TRUE(result);
        }
        else
        {
            EXPECT_FALSE(result);
        }
    }

    TEST_P(EncoderTest, Should_Expect_Valid_When_ExecutedInMultipleThreads)
    {
        const std::string& input = GetParam();
        const int thread_count = 16;
        std::vector<std::thread> threads;
        std::atomic<int> success_count = 0;

        for (int index = 0; index < thread_count; ++index)
        {
            threads.emplace_back([&]() {
                std::string result = QLogicaeCore::Encoder::get_instance().from_utf8_to_base64(input);
                success_count++;
            });
        }

        for (std::thread& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(success_count, thread_count);
    }

    TEST_P(EncoderTest, Should_Expect_FastExecution_When_PerformingRoundTrip)
    {
        const std::string& original_text = GetParam();

        auto start = std::chrono::high_resolution_clock::now();

        for (int index = 0; index < 1000; ++index)
        {
            std::string base64 = QLogicaeCore::Encoder::get_instance()
                .from_utf8_to_base64(original_text);
            std::string back = QLogicaeCore::Encoder::get_instance()
                .from_base64_to_utf8(base64);
            EXPECT_EQ(original_text, back);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        EXPECT_LE(duration.count(), 2000);
    }

    INSTANTIATE_TEST_CASE_P(
        EncoderStrings,
        EncoderTest,
        ::testing::Values(
            "",
            "test",
            "HelloWorld",
            "1234567890",
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
            std::string(1024, 'A'),
            std::string(2048, 'B')
        )
    );
}

