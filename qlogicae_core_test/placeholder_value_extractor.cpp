#pragma once

#include "pch.h"

#include "qlogicae_core.hpp"

namespace QLogicaeCoreTest
{
    class PlaceholderValueExtractorTest : public ::testing::TestWithParam<std::any> {};

    TEST_P(PlaceholderValueExtractorTest, Should_Expect_CorrectValue_When_ValidStringGiven)
    {
        std::string value = std::any_cast<std::string>(GetParam());
        QLogicaeCore::PlaceholderValueExtractor extractor(value);
        EXPECT_EQ(extractor.get_value().value(), value);
    }

    TEST_P(PlaceholderValueExtractorTest, Should_Expect_NoThrow_When_AccessedAsynchronously)
    {
        std::string value = std::any_cast<std::string>(GetParam());
        QLogicaeCore::PlaceholderValueExtractor extractor(value);
        auto future = std::async(std::launch::async, [&]() { return extractor.get_value(); });
        EXPECT_NO_THROW(future.get());
    }

    TEST_P(PlaceholderValueExtractorTest, Should_Expect_CorrectResult_When_AccessedByMultipleThreads)
    {
        std::string value = std::any_cast<std::string>(GetParam());
        QLogicaeCore::PlaceholderValueExtractor extractor(value);
        std::vector<std::thread> threads;
        std::atomic<size_t> success = 0;

        for (int i = 0; i < 32; ++i)
        {
            threads.emplace_back([&]() {
                if (extractor.get_value().value() == value) ++success;
                });
        }

        for (auto& t : threads) t.join();
        EXPECT_EQ(success.load(), 32);
    }

    TEST_P(PlaceholderValueExtractorTest, Should_Expect_ResultWithinMicrosecond_When_PerformanceChecked)
    {
        std::string value = std::any_cast<std::string>(GetParam());
        QLogicaeCore::PlaceholderValueExtractor extractor(value);
        auto start = std::chrono::steady_clock::now();
        auto result = extractor.get_value();
        auto end = std::chrono::steady_clock::now();
        auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        EXPECT_LE(duration_us, 1000);
    }

    TEST_P(PlaceholderValueExtractorTest, Should_Expect_ManyCalls_When_StressedForTwoSeconds)
    {
        std::string value = std::any_cast<std::string>(GetParam());
        QLogicaeCore::PlaceholderValueExtractor extractor(value);
        auto start = std::chrono::steady_clock::now();
        size_t call_count = 0;
        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(2))
        {
            extractor.get_value();
            ++call_count;
        }
        EXPECT_GT(call_count, 1000);
    }

    INSTANTIATE_TEST_CASE_P(
        PlaceholderValueExtractorParams,
        PlaceholderValueExtractorTest,
        ::testing::Values(
            std::any(std::string("test")),
            std::any(std::string("value")),
            std::any(std::string("")),
            std::any(std::string("123")),
            std::any(std::string("!@#$%^&*"))
        )
    );

}
