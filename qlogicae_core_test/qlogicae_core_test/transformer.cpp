#include "pch.hpp"

#include "qlogicae_core/transformer.hpp"

namespace QLogicaeCoreTest
{
    class TransformerTest : public ::testing::Test {};

    class LogLevelColorParamTest : public ::testing::TestWithParam<QLogicaeCore::LogLevel> {};

    class OutputSizeParamTest : public ::testing::TestWithParam<size_t> {};

    TEST_F(TransformerTest, Should_Expect_ColoredString_When_LogLevelIsSet)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::string result = transformer.color_type(QLogicaeCore::LogLevel::WARNING);
        EXPECT_EQ(result, "\033[93m");
    }

    TEST_F(TransformerTest, Should_Expect_EmptyString_When_UnknownLogLevel)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::string result = transformer.color_type(static_cast<QLogicaeCore::LogLevel>(999));
        EXPECT_EQ(result, "");
    }

    TEST_F(TransformerTest, Should_Expect_DefaultLogFormat_When_GivenText)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::string result = transformer.to_log_format("log entry", QLogicaeCore::LogLevel::INFO, 512);
        EXPECT_TRUE(result.find("log entry") != std::string::npos);
    }

    TEST_F(TransformerTest, DISABLED_Should_Expect_ColorWrappedText_When_ToLogLevelColorFormat)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::string result = transformer.to_log_level_color_format("highlight", QLogicaeCore::LogLevel::SUCCESS, 128);
        EXPECT_TRUE(result.find("") != std::string::npos);
        EXPECT_TRUE(result.find("highlight") != std::string::npos);
        EXPECT_TRUE(result.find("") != std::string::npos);
    }

    TEST_F(TransformerTest, Should_Expect_None_When_ToNoneFormatWithEmpty)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::string result = transformer.to_none_format("");
        EXPECT_EQ(result, "None");
    }

    TEST_F(TransformerTest, Should_Expect_NA_When_ToNAFormatWithEmpty)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::string result = transformer.to_na_format("");
        EXPECT_EQ(result, "N/A");
    }

    TEST_F(TransformerTest, Should_Expect_Text_When_ToNoneFormatWithText)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::string result = transformer.to_none_format("something");
        EXPECT_EQ(result, "something");
    }

    TEST_F(TransformerTest, Should_Expect_Text_When_ToNAFormatWithText)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::string result = transformer.to_na_format("something");
        EXPECT_EQ(result, "something");
    }

    TEST_F(TransformerTest, Should_Expect_MatchingSize_When_ToLogFormat)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::string result = transformer.to_log_format("info", QLogicaeCore::LogLevel::INFO, 256);
        EXPECT_LE(result.size(), 256);
    }

    TEST_F(TransformerTest, Should_Expect_AsyncLogGeneration_When_UsingFutures)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::future<std::string> f = std::async(std::launch::async, [&] {
            return transformer.to_log_format("async", QLogicaeCore::LogLevel::DEBUG, 128);
            });
        std::string result = f.get();
        EXPECT_TRUE(result.find("async") != std::string::npos);
    }

    TEST_F(TransformerTest, Should_Expect_LogFormatUnder1ms_When_PerformingSingleCall)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        auto start = std::chrono::steady_clock::now();
        transformer.to_log_format("performance", QLogicaeCore::LogLevel::DEBUG, 128);
        auto elapsed = std::chrono::steady_clock::now() - start;
        EXPECT_LT(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count(), 1);
    }

    TEST_F(TransformerTest, Should_Expect_MultipleCallsWithin2Seconds_When_StressTested)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        auto start = std::chrono::steady_clock::now();
        int counter = 0;
        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(2))
        {
            transformer.to_log_format("stress", QLogicaeCore::LogLevel::WARNING, 128);
            counter++;
        }
        EXPECT_GT(counter, 1000);
    }

    TEST_F(TransformerTest, Should_Expect_ThreadSafeOutput_When_Multithreaded)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::vector<std::future<std::string>> futures;
        for (int i = 0; i < 8; ++i)
        {
            futures.push_back(std::async(std::launch::async, [&transformer]() {
                return transformer.to_log_level_color_format("threaded", QLogicaeCore::LogLevel::EXCEPTION, 128);
                }));
        }

        for (auto& future : futures)
        {
            std::string result = future.get();
            EXPECT_TRUE(result.find("threaded") != std::string::npos);
        }
    }

    TEST_P(LogLevelColorParamTest, Should_Expect_ValidFormat_When_Parameterized)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::string result = transformer.to_log_level_color_format("param", GetParam(), 64);
        EXPECT_TRUE(result.find("param") != std::string::npos);
    }

    INSTANTIATE_TEST_CASE_P(LogLevels, LogLevelColorParamTest,
        ::testing::Values(
            QLogicaeCore::LogLevel::DEBUG,
            QLogicaeCore::LogLevel::INFO,
            QLogicaeCore::LogLevel::WARNING,
            QLogicaeCore::LogLevel::CRITICAL,
            QLogicaeCore::LogLevel::EXCEPTION,
            QLogicaeCore::LogLevel::SUCCESS
        ));

    TEST_P(OutputSizeParamTest, Should_Expect_ResultUnderSize_When_OutputSizeVaries)
    {
        auto& transformer = QLogicaeCore::Transformer::get_instance();
        std::string result = transformer.to_log_format("testing size", QLogicaeCore::LogLevel::HIGHLIGHTED_INFO, GetParam());
        EXPECT_LE(result.size(), GetParam());
    }

    INSTANTIATE_TEST_CASE_P(OutputSizes, OutputSizeParamTest,
        ::testing::Values(65, 128, 256, 512));
}

