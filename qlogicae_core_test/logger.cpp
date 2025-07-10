#pragma once

#include "pch.h"

#include "logger.hpp"

namespace QLogicaeCoreTest
{
    class LoggerTest : public ::testing::Test {};

    TEST_F(LoggerTest, Should_Expect_DefaultValues_When_DefaultConstructed)
    {
        QLogicaeCore::Logger logger;
        EXPECT_EQ(logger.get_name(), "");
        EXPECT_EQ(logger.get_medium(), QLogicaeCore::LogMedium::CONSOLE);
        EXPECT_FALSE(logger.get_is_simplified());
        EXPECT_TRUE(logger.get_output_paths().empty());
    }

    TEST_F(LoggerTest, Should_Expect_ProperInitialization_When_ConstructedWithParams)
    {
        std::vector<std::string> paths = { "log1.txt", "log2.txt" };
        QLogicaeCore::Logger logger("MyLogger",
            QLogicaeCore::LogMedium::CONSOLE, paths, true);

        EXPECT_EQ(logger.get_name(), "MyLogger");
        EXPECT_EQ(logger.get_medium(), QLogicaeCore::LogMedium::CONSOLE);
        EXPECT_TRUE(logger.get_is_simplified());
        EXPECT_EQ(logger.get_output_paths(), paths);
    }

    TEST_F(LoggerTest, Should_Expect_FlagUpdated_When_SetIsSimplified)
    {
        QLogicaeCore::Logger logger;
        EXPECT_FALSE(logger.get_is_simplified());
        logger.set_is_simplified(true);
        EXPECT_TRUE(logger.get_is_simplified());
    }

    TEST_F(LoggerTest, Should_Expect_AsyncLogToComplete_When_LogAsync)
    {
        QLogicaeCore::Logger logger;
        std::future<void> future = logger.log_async("message");
        future.get();
        SUCCEED();
    }

    TEST_F(LoggerTest, Should_Expect_ParallelLogging_When_Multithreaded)
    {
        QLogicaeCore::Logger logger;
        std::vector<std::thread> thread_list;

        for (int index = 0; index < 8; ++index)
        {
            thread_list.emplace_back([&logger]() {
                logger.log("threaded message");
                });
        }

        for (auto& thread : thread_list)
        {
            thread.join();
        }

        SUCCEED();
    }

    TEST_F(LoggerTest, Should_Expect_HighVolumeLogToSucceed_When_StressTested)
    {
        QLogicaeCore::Logger logger;
        std::atomic<int> log_count = 0;
        auto start = std::chrono::steady_clock::now();

        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(2))
        {
            logger.log("stress log");
            ++log_count;
        }

        EXPECT_GT(log_count.load(), 1000);
    }

    TEST_F(LoggerTest, Should_Expect_NoThrow_When_LoggingEmptyString)
    {
        QLogicaeCore::Logger logger;
        EXPECT_NO_THROW(logger.log(""));
    }

    TEST_F(LoggerTest, Should_Expect_CompleteQuickly_When_LoggingUnder2Seconds)
    {
        QLogicaeCore::Logger logger;
        auto start = std::chrono::steady_clock::now();
        logger.log("timed message");
        auto end = std::chrono::steady_clock::now();

        EXPECT_LT(std::chrono::duration_cast<std::chrono::seconds>(end - start).count(), 2);
    }

    class SimplifiedLogFlagTest : public ::testing::TestWithParam<bool> {};

    TEST_P(SimplifiedLogFlagTest, Should_Expect_LogBehavesCorrectly_When_Parameterized)
    {
        QLogicaeCore::Logger logger;
        logger.set_is_simplified(GetParam());
        EXPECT_EQ(logger.get_is_simplified(), GetParam());
        EXPECT_NO_THROW(logger.log("param log", QLogicaeCore::LogLevel::INFO, GetParam()));
    }

    INSTANTIATE_TEST_CASE_P(LogSimplifiedStates, SimplifiedLogFlagTest,
        ::testing::Values(true, false));

}
