#include "pch.h"

#include "qlogicae_core/time.hpp"

namespace QLogicaeCoreTest
{
    class TimeTest : public ::testing::Test {};

    class TimeFormatTest : public ::testing::TestWithParam<QLogicaeCore::TimeFormat> {};

    TEST_F(TimeTest, Should_Expect_ValidComponents_When_LocalTimeZone)
    {
        auto& time = QLogicaeCore::Time::get_instance();

        EXPECT_GE(time.year(QLogicaeCore::TimeZone::LOCAL), 1970);
        EXPECT_GE(time.month(QLogicaeCore::TimeZone::LOCAL), 1);
        EXPECT_GE(time.day(QLogicaeCore::TimeZone::LOCAL), 1);
        EXPECT_GE(time.hour(QLogicaeCore::TimeZone::LOCAL), 0);
        EXPECT_GE(time.minute(QLogicaeCore::TimeZone::LOCAL), 0);
        EXPECT_GE(time.second(QLogicaeCore::TimeZone::LOCAL), 0);
    }

    TEST_F(TimeTest, Should_Expect_ValidComponents_When_UTCTimeZone)
    {
        auto& time = QLogicaeCore::Time::get_instance();

        EXPECT_GE(time.year(QLogicaeCore::TimeZone::UTC), 1970);
        EXPECT_GE(time.month(QLogicaeCore::TimeZone::UTC), 1);
        EXPECT_GE(time.day(QLogicaeCore::TimeZone::UTC), 1);
        EXPECT_GE(time.hour(QLogicaeCore::TimeZone::UTC), 0);
        EXPECT_GE(time.minute(QLogicaeCore::TimeZone::UTC), 0);
        EXPECT_GE(time.second(QLogicaeCore::TimeZone::UTC), 0);
    }

    TEST_F(TimeTest, Should_Expect_ValidSubSecondValues_When_Called)
    {
        auto& time = QLogicaeCore::Time::get_instance();

        EXPECT_GE(time.millisecond(), 0);
        EXPECT_GE(time.microsecond(), 0);
        EXPECT_GE(time.nanosecond(), 0);
    }

    TEST_F(TimeTest, Should_Expect_NotEmpty_When_RequestingFormattedNow)
    {
        auto& time = QLogicaeCore::Time::get_instance();
        auto output = time.now(QLogicaeCore::TimeFormat::ISO8601,
            QLogicaeCore::TimeZone::LOCAL);

        EXPECT_FALSE(output.empty());
    }

    TEST_F(TimeTest, Should_Expect_EpochTime_When_UsingUnixFormat)
    {
        auto& time = QLogicaeCore::Time::get_instance();
        auto output = time.now(QLogicaeCore::TimeFormat::UNIX,
            QLogicaeCore::TimeZone::LOCAL);

        auto value = std::stoll(output);
        EXPECT_GT(value, 1000000000);
    }

    TEST_F(TimeTest, Should_Expect_DifferentZones_When_ComparingUTCAndLocal)
    {
        auto& time = QLogicaeCore::Time::get_instance();
        auto utc = time.now(QLogicaeCore::TimeFormat::HOUR_24,
            QLogicaeCore::TimeZone::UTC);
        auto local = time.now(QLogicaeCore::TimeFormat::HOUR_24,
            QLogicaeCore::TimeZone::LOCAL);

        EXPECT_STRNE(utc.c_str(), local.c_str());
    }

    TEST_F(TimeTest, Should_Expect_ValidFormat_When_MILLIS_MICROS_NANOS)
    {
        auto& time = QLogicaeCore::Time::get_instance();
        auto result = time.now(QLogicaeCore::TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND);

        EXPECT_NE(result.find("ms:"), std::string::npos);
        EXPECT_NE(result.find("us:"), std::string::npos);
        EXPECT_NE(result.find("ns:"), std::string::npos);
    }

    TEST_F(TimeTest, Should_Expect_Success_When_AsynchronousAccess)
    {
        auto result = std::async(std::launch::async, []()
            {
                return QLogicaeCore::Time::get_instance()
                    .now(QLogicaeCore::TimeFormat::ISO8601);
            });

        EXPECT_FALSE(result.get().empty());
    }

    TEST_F(TimeTest, Should_Expect_Success_When_MultithreadedAccess)
    {
        std::vector<std::thread> threads;
        std::atomic<int> count = 0;

        for (int index = 0; index < 16; ++index)
        {
            threads.emplace_back([&]() {
                if (!QLogicaeCore::Time::get_instance()
                    .now(QLogicaeCore::TimeFormat::HOUR_12)
                    .empty())
                {
                    ++count;
                }
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_EQ(count, 16);
    }

    TEST_F(TimeTest, Should_Expect_PerformanceUnder2Seconds_When_StressAccess)
    {
        auto start = std::chrono::steady_clock::now();
        int access_count = 0;

        while (std::chrono::steady_clock::now() - start <
            std::chrono::seconds(2))
        {
            QLogicaeCore::Time::get_instance()
                .now(QLogicaeCore::TimeFormat::DATE_DASHED);
            ++access_count;
        }

        EXPECT_GT(access_count, 1000);
    }

    TEST_F(TimeTest, Should_Expect_NoCrash_When_StressQueryingSubSeconds)
    {
        auto& time = QLogicaeCore::Time::get_instance();

        for (int index = 0; index < 1000000; ++index)
        {
            EXPECT_GE(time.nanosecond(), 0);
            EXPECT_GE(time.microsecond(), 0);
            EXPECT_GE(time.millisecond(), 0);
        }
    }

    TEST_F(TimeTest, Should_Expect_ValidFormat_When_ISO8601Used)
    {
        auto& time = QLogicaeCore::Time::get_instance();
        auto output = time.now(QLogicaeCore::TimeFormat::ISO8601);

        std::regex pattern(
            R"(^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(\.\d+)?(Z|[+-]\d{2}:\d{2})?$)"
        );

        EXPECT_TRUE(std::regex_match(output, pattern));
    }

    TEST_F(TimeTest, Should_Expect_SameReference_When_AccessingSingleton)
    {
        auto& first = QLogicaeCore::Time::get_instance();
        auto& second = QLogicaeCore::Time::get_instance();

        EXPECT_EQ(&first, &second);
    }

    TEST_F(TimeTest, Should_Expect_Under1Millisecond_When_RequestingHour)
    {
        auto start = std::chrono::steady_clock::now();
        QLogicaeCore::Time::get_instance().hour();
        auto duration = std::chrono::steady_clock::now() - start;

        EXPECT_LT(
            std::chrono::duration_cast<std::chrono::milliseconds>(duration)
            .count(),
            1
        );
    }

    TEST_F(TimeTest, Should_Expect_Throw_When_InvalidZoneUsedInPrivateMethod)
    {
        struct TimePublic : QLogicaeCore::Time {
            using QLogicaeCore::Time::_get_time_zone;
        };

        TimePublic accessor;
        auto result = accessor._get_time_zone(
            static_cast<QLogicaeCore::TimeZone>(999));
        EXPECT_GE(result.tm_year, 0);
    }

    class TimeZoneTest : public ::testing::TestWithParam<QLogicaeCore::TimeZone> {};

    TEST_P(TimeZoneTest, Should_Expect_ValidTime_When_UsingAllTimeZones)
    {
        auto& time = QLogicaeCore::Time::get_instance();

        EXPECT_GE(time.year(GetParam()), 1970);
        EXPECT_GE(time.month(GetParam()), 1);
        EXPECT_GE(time.day(GetParam()), 1);
        EXPECT_GE(time.hour(GetParam()), 0);
        EXPECT_GE(time.minute(GetParam()), 0);
        EXPECT_GE(time.second(GetParam()), 0);
    }

    INSTANTIATE_TEST_CASE_P(
        AllZones,
        TimeZoneTest,
        ::testing::Values(
            QLogicaeCore::TimeZone::LOCAL,
            QLogicaeCore::TimeZone::UTC
        )
    );

    TEST_P(TimeFormatTest, Should_Expect_NonEmpty_When_Parameterized)
    {
        auto result = QLogicaeCore::Time::get_instance().now(GetParam());
        EXPECT_FALSE(result.empty());
    }

    INSTANTIATE_TEST_CASE_P(
        ValidFormats,
        TimeFormatTest,
        ::testing::Values(
            QLogicaeCore::TimeFormat::UNIX,
            QLogicaeCore::TimeFormat::ISO8601,
            QLogicaeCore::TimeFormat::FULL_TIMESTAMP,
            QLogicaeCore::TimeFormat::FULL_DASHED_TIMESTAMP,
            QLogicaeCore::TimeFormat::HOUR_12,
            QLogicaeCore::TimeFormat::HOUR_24,
            QLogicaeCore::TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND,
            QLogicaeCore::TimeFormat::DATE_DASHED,
            QLogicaeCore::TimeFormat::DATE_MDY_SLASHED,
            QLogicaeCore::TimeFormat::DATE_DMY_SLASHED,
            QLogicaeCore::TimeFormat::DATE_DMY_SPACED,
            QLogicaeCore::TimeFormat::DATE_VERBOSE
        )
    );
}
