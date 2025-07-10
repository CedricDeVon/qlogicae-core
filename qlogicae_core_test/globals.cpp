#pragma once

#include "pch.h"

#include "globals.hpp"

namespace QLogicaeCoreTest
{

    class ConstantsTest : public ::testing::Test {};

    TEST_F(ConstantsTest, Should_Expect_DefaultRegistryValues_When_Accessed)
    {
        EXPECT_EQ(QLogicaeCore::Constants::DEFAULT_HKEY, HKEY_CURRENT_USER);
        EXPECT_EQ(QLogicaeCore::Constants::HKEY_MAXIMUM_VALUE_SIZE, 65536);
        EXPECT_EQ(QLogicaeCore::Constants::DEFAULT_NAME_KEY, L"Data");
        EXPECT_EQ(QLogicaeCore::Constants::DEFAULT_SUB_KEY, L"Software\\App");
        EXPECT_EQ(QLogicaeCore::Constants::REGULAR_ACCESS_FLAGS, KEY_READ | KEY_SET_VALUE);
    }

    TEST_F(ConstantsTest, Should_Expect_NumberConstants_When_Accessed)
    {
        EXPECT_EQ(QLogicaeCore::Constants::NUMBER_ZERO, 0u);
        EXPECT_EQ(QLogicaeCore::Constants::NUMBER_ONE, 1u);
        EXPECT_EQ(QLogicaeCore::Constants::NUMBER_TEN, 10u);
        EXPECT_EQ(QLogicaeCore::Constants::NUMBER_HUNDRED, 100u);
        EXPECT_EQ(QLogicaeCore::Constants::NUMBER_THOUSAND, 1000u);
        EXPECT_EQ(QLogicaeCore::Constants::NUMBER_MILLION, 1000000u);
        EXPECT_EQ(QLogicaeCore::Constants::NUMBER_BILLION, 1000000000u);
    }

    TEST_F(ConstantsTest, Should_Expect_StringViews_When_Accessed)
    {
        EXPECT_EQ(QLogicaeCore::Constants::STRING_EMPTY, "");
        EXPECT_EQ(QLogicaeCore::Constants::STRING_NONE_1, "None");
        EXPECT_EQ(QLogicaeCore::Constants::STRING_NONE_2, "N/A");
        EXPECT_TRUE(QLogicaeCore::Constants::FULL_VISIBLE_ASCII_CHARACTERSET.find("!") != std::string_view::npos);
    }

    TEST_F(ConstantsTest, Should_Expect_LogLevels_When_Called)
    {
        using QLogicaeCore::LogLevel;
        EXPECT_EQ(QLogicaeCore::get_log_level_string(LogLevel::INFO), "INFO");
        EXPECT_EQ(QLogicaeCore::get_log_level_string(LogLevel::DEBUG), "DEBUG");
        EXPECT_EQ(QLogicaeCore::get_log_level_string(LogLevel::SUCCESS), "SUCCESS");
        EXPECT_EQ(QLogicaeCore::get_log_level_string(LogLevel::WARNING), "WARNING");
        EXPECT_EQ(QLogicaeCore::get_log_level_string(LogLevel::CRITICAL), "CRITICAL");
        EXPECT_EQ(QLogicaeCore::get_log_level_string(LogLevel::EXCEPTION), "EXCEPTION");
        EXPECT_EQ(QLogicaeCore::get_log_level_string(LogLevel::HIGHLIGHTED_INFO), "INFO");
    }

    TEST_F(ConstantsTest, Should_Expect_DefaultCryptographer3Properties_When_Accessed)
    {
        auto props = QLogicaeCore::default_cryptographer_3_properties;
        EXPECT_EQ(props.size_t_1, 32u);
        EXPECT_EQ(props.size_t_2, 16u);
        EXPECT_EQ(props.uint32_t_1, 3u);
        EXPECT_EQ(props.uint32_t_2, 65536u);
        EXPECT_EQ(props.uint32_t_3, 2u);
    }

    TEST_F(ConstantsTest, Should_Expect_Success_When_ThreadedAccess)
    {
        std::atomic<int> success = 0;
        std::vector<std::thread> threads;

        for (int i = 0; i < 16; ++i)
        {
            threads.emplace_back([&]()
                {
                    if (QLogicaeCore::Constants::NUMBER_ONE == 1) ++success;
                });
        }

        for (auto& t : threads) t.join();
        EXPECT_EQ(success, 16);
    }

    TEST_F(ConstantsTest, Should_Expect_Completion_When_AsyncAccessed)
    {
        auto future = std::async(std::launch::async, []()
            {
                return QLogicaeCore::Constants::TIME_FORMAT_ISO_8601;
            });
        auto result = future.get();
        EXPECT_STREQ(result, "%Y-%m-%d %H:%M:%S");
    }

    TEST_F(ConstantsTest, Should_Expect_ConsistentUnderStress_When_RepeatedAccess)
    {
        auto start = std::chrono::steady_clock::now();
        int count = 0;

        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(2))
        {
            auto val = QLogicaeCore::Constants::LOG_PART_1;
            if (val == "[") ++count;
        }

        EXPECT_GT(count, 100000);
    }

    class LogLevelToStringTest : public ::testing::TestWithParam<QLogicaeCore::LogLevel> {};

    TEST_P(LogLevelToStringTest, Should_Expect_ValidMapping_When_Parameterized)
    {
        auto result = QLogicaeCore::get_log_level_string(GetParam());
        EXPECT_FALSE(result.empty());
    }

    INSTANTIATE_TEST_CASE_P(
        ValidLogLevels,
        LogLevelToStringTest,
        ::testing::Values(
            QLogicaeCore::LogLevel::ALL,
            QLogicaeCore::LogLevel::INFO,
            QLogicaeCore::LogLevel::DEBUG,
            QLogicaeCore::LogLevel::SUCCESS,
            QLogicaeCore::LogLevel::WARNING,
            QLogicaeCore::LogLevel::CRITICAL,
            QLogicaeCore::LogLevel::EXCEPTION,
            QLogicaeCore::LogLevel::HIGHLIGHTED_INFO
        )
    );

    TEST_F(ConstantsTest, Should_Expect_OneMillisecond_When_MeasuringGetString)
    {
        auto start = std::chrono::steady_clock::now();
        auto result = QLogicaeCore::get_log_level_string(QLogicaeCore::LogLevel::INFO);
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start).count();
        EXPECT_LT(duration, 1000);
    }
}

