#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{

    class LoggerTest : public ::testing::TestWithParam<std::tuple<std::string, QLogicaeCore::LogMedium, bool>>
    {
    };

    TEST_P(LoggerTest, Should_Expect_ProperConstruction_When_CreatedWithParameters)
    {
        const std::string name = std::get<0>(GetParam());
        const QLogicaeCore::LogMedium medium = std::get<1>(GetParam());
        const bool simplified = std::get<2>(GetParam());
        QLogicaeCore::Logger logger(name, medium, { "out.txt" }, simplified);
        EXPECT_EQ(logger.get_name(), name);
        EXPECT_EQ(logger.get_medium(), medium);
        EXPECT_EQ(logger.get_is_simplified(), simplified);
        EXPECT_EQ(logger.get_output_paths().size(), 1);
    }

    TEST(LoggerTest, Should_Expect_SimplifiedToggle_When_Set)
    {
        QLogicaeCore::Logger logger;
        EXPECT_FALSE(logger.get_is_simplified());
        logger.set_is_simplified(true);
        EXPECT_TRUE(logger.get_is_simplified());
    }

    TEST(LoggerTest, Should_Expect_AsyncLogCompletion_When_Invoked)
    {
        QLogicaeCore::Logger logger;
        auto future = logger.log_async("async test");
        EXPECT_EQ(future.wait_for(std::chrono::seconds(2)), std::future_status::ready);
    }

    TEST(LoggerTest, Should_Expect_MultipleThreads_When_LoggingConcurrently)
    {
        QLogicaeCore::Logger logger;
        std::vector<std::future<void>> futures;
        for (int i = 0; i < 16; ++i)
        {
            futures.push_back(logger.log_async("concurrent"));
        }
        for (auto& f : futures)
        {
            EXPECT_EQ(f.wait_for(std::chrono::milliseconds(1000)), std::future_status::ready);
        }
    }

    TEST(LoggerTest, Should_Expect_PerformanceUnder1ms_When_LoggingSimple)
    {
        QLogicaeCore::Logger logger(true);
        const auto start = std::chrono::high_resolution_clock::now();
        logger.log("perf");
        const auto end = std::chrono::high_resolution_clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        EXPECT_LE(elapsed.count(), 1);
    }

    TEST(LoggerTest, Should_Expect_ConstructorDefaultValues_When_EmptyConstructed)
    {
        QLogicaeCore::Logger logger;
        EXPECT_EQ(logger.get_name(), "");
        EXPECT_EQ(logger.get_medium(), QLogicaeCore::LogMedium::CONSOLE);
        EXPECT_FALSE(logger.get_is_simplified());
        EXPECT_TRUE(logger.get_output_paths().empty());
    }

    INSTANTIATE_TEST_CASE_P(
        LoggerVariations,
        LoggerTest,
        ::testing::Values(
            std::make_tuple("log1", QLogicaeCore::LogMedium::CONSOLE, false),
            std::make_tuple("log2", QLogicaeCore::LogMedium::FILE, true),
            std::make_tuple("log3", QLogicaeCore::LogMedium::ALL, false)
        )
    );
}
