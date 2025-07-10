#pragma once

#include "pch.h"

#include "dot_env_value_extractor.hpp"

namespace QLogicaeCoreTest
{
    class DotEnvValueExtractorTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            SetEnvironmentVariableW(L"DOTENV_STRING", L"utf8-string");
        }

        void TearDown() override
        {
            SetEnvironmentVariableW(L"DOTENV_STRING", nullptr);
        }
    };

    TEST_F(DotEnvValueExtractorTest, Should_Expect_Value_When_ValidUtf8Key)
    {
        QLogicaeCore::DotEnvValueExtractor extractor("DOTENV_STRING");
        auto value = extractor.get_value();
        EXPECT_TRUE(value.has_value());
        EXPECT_EQ(value.value(), "utf8-string");
    }

    TEST_F(DotEnvValueExtractorTest, Should_Expect_Value_When_ValidUtf16Key)
    {
        QLogicaeCore::DotEnvValueExtractor extractor(L"DOTENV_STRING");
        auto value = extractor.get_value();
        EXPECT_TRUE(value.has_value());
        EXPECT_EQ(value.value(), "utf8-string");
    }

    TEST_F(DotEnvValueExtractorTest, Should_Expect_Empty_When_KeyDoesNotExist)
    {
        QLogicaeCore::DotEnvValueExtractor extractor("DOES_NOT_EXIST");
        auto value = extractor.get_value();
        EXPECT_TRUE(value.has_value());
        EXPECT_EQ(value.value(), "");
    }

    TEST_F(DotEnvValueExtractorTest, Should_Expect_NoThrow_When_CalledAsync)
    {
        QLogicaeCore::DotEnvValueExtractor extractor("DOTENV_STRING");
        auto future = std::async(std::launch::async, [&]() { return extractor.get_value(); });
        EXPECT_NO_THROW(future.get());
    }

    TEST_F(DotEnvValueExtractorTest, Should_Expect_Correct_When_UsedMultithreaded)
    {
        QLogicaeCore::DotEnvValueExtractor extractor("DOTENV_STRING");
        std::vector<std::thread> threads;
        std::atomic<int> success = 0;
        for (int i = 0; i < 32; ++i)
        {
            threads.emplace_back([&]()
                {
                    if (extractor.get_value().value() == "utf8-string") ++success;
                });
        }
        for (auto& t : threads) t.join();
        EXPECT_EQ(success.load(), 32);
    }

    TEST_F(DotEnvValueExtractorTest, Should_Expect_ThousandCalls_When_Stressed)
    {
        QLogicaeCore::DotEnvValueExtractor extractor("DOTENV_STRING");
        auto start = std::chrono::steady_clock::now();
        size_t count = 0;
        while (std::chrono::steady_clock::now() - start < std::chrono::seconds(2))
        {
            extractor.get_value();
            ++count;
        }
        EXPECT_GT(count, 1000);
    }

    class DotEnvValueExtractorParameterizedTest : public ::testing::TestWithParam<std::string> {};

    TEST_P(DotEnvValueExtractorParameterizedTest, Should_Expect_Empty_When_UnknownKeys)
    {
        QLogicaeCore::DotEnvValueExtractor extractor(GetParam());
        auto result = extractor.get_value();
        EXPECT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), "");
    }

    INSTANTIATE_TEST_CASE_P(
        DotEnvKeys,
        DotEnvValueExtractorParameterizedTest,
        ::testing::Values("UNSET_1", "UNSET_2", "UNSET_3", "UNSET_4", "UNSET_5")
    );

    TEST_F(DotEnvValueExtractorTest, Should_Expect_Millisecond_Execution_When_CalledOnce)
    {
        QLogicaeCore::DotEnvValueExtractor extractor("DOTENV_STRING");
        auto start = std::chrono::steady_clock::now();
        extractor.get_value();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start).count();
        EXPECT_LT(duration, 1000);
    }
}
