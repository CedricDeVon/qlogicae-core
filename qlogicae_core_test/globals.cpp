#include "pch.h"

#include "globals.hpp"

namespace QLogicaeCoreTest
{
    class ConstantsTest : public ::testing::TestWithParam<int>
    {
    };

    TEST_F(ConstantsTest, Should_Expect_CorrectTimeFormat_When_FormatConstantUsed)
    {
        EXPECT_STREQ(QLogicaeCore::Constants::TIME_FORMAT_ISO_8601,
            "%Y-%m-%dT%H:%M:%S");

        EXPECT_STREQ(QLogicaeCore::Constants::TIME_FORMAT_HOUR_24,
            "%H:%M:%S");

        EXPECT_STREQ(QLogicaeCore::Constants::TIME_FORMAT_DATE_DMY_SLASHED,
            "%d/%m/%Y");
    }

    TEST_F(ConstantsTest, Should_Expect_ValidAccessFlags_When_RegistryUsed)
    {
        EXPECT_TRUE(QLogicaeCore::Constants::REGULAR_ACCESS_FLAGS &
            KEY_READ);
    }

    TEST_F(ConstantsTest, Should_Expect_ValidRandomConstants_When_ValuesWithinBounds)
    {
        EXPECT_GE(QLogicaeCore::Constants::RANDOM_DOUBLE_MINIMUM, 0.0);
        EXPECT_LE(QLogicaeCore::Constants::RANDOM_DOUBLE_MAXIMUM, 1.0);
    }

    TEST_F(ConstantsTest, Should_Expect_CorrectAsciiSetLength_When_FullAsciiChecked)
    {
        std::string_view ascii = QLogicaeCore::Constants::
            FULL_VISIBLE_ASCII_CHARACTERSET;
        EXPECT_GT(ascii.length(), 80);
    }

    TEST_F(ConstantsTest, Should_Expect_EmptyStrings_When_DefaultEmptyConstantsUsed)
    {
        EXPECT_TRUE(QLogicaeCore::Constants::STRING_EMPTY.empty());
        EXPECT_FALSE(QLogicaeCore::Constants::STRING_NONE_1.empty());
    }

    TEST_P(ConstantsTest, Should_Expect_StablePerformance_When_StressConstantsLooped)
    {
        std::chrono::steady_clock::time_point start_time =
            std::chrono::steady_clock::now();

        for (int iteration = 0; iteration < 1000000; iteration++)
        {
            volatile int value = QLogicaeCore::Constants::NUMBER_THOUSAND;
            value += QLogicaeCore::Constants::NUMBER_HUNDRED;
            value += QLogicaeCore::Constants::NUMBER_MILLION;
        }

        std::chrono::duration<double> elapsed =
            std::chrono::steady_clock::now() - start_time;

        EXPECT_LE(elapsed.count(), 2.0);
    }

    TEST_F(ConstantsTest, Should_Expect_UniqueLogLevels_When_DistinctLogEnumsUsed)
    {
        std::set<std::string_view> level_names;

        level_names.insert(QLogicaeCore::get_log_level_string(
            QLogicaeCore::LogLevel::INFO));

        level_names.insert(QLogicaeCore::get_log_level_string(
            QLogicaeCore::LogLevel::DEBUG));

        level_names.insert(QLogicaeCore::get_log_level_string(
            QLogicaeCore::LogLevel::CRITICAL));

        level_names.insert(QLogicaeCore::get_log_level_string(
            QLogicaeCore::LogLevel::EXCEPTION));

        EXPECT_GE(level_names.size(), 4);
    }

    TEST_F(ConstantsTest, Should_Expect_CorrectDefaults_When_NetworkDefaultsUsed)
    {
        QLogicaeCore::NetworkPingSettings settings;
        EXPECT_EQ(settings.host_address,
            QLogicaeCore::Constants::DEFAULT_HOST_ADDRESS);
        EXPECT_TRUE(settings.is_listening);
        EXPECT_EQ(settings.milliseconds_per_callback.count(),
            QLogicaeCore::Constants::DEFAULT_MILLISECONDS_PER_CALLBACK);
    }

    INSTANTIATE_TEST_CASE_P(ConstantsTestCases,
        ConstantsTest,
        ::testing::Values(1, 10, 100));
}

