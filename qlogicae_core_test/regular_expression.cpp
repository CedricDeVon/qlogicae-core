#pragma once

#include "pch.h"

#include "regular_expression.hpp"

namespace QLogicaeCoreTest
{

    class RegularExpressionTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string>>
    {
    protected:
        void SetUp() override
        {
            QLogicaeCore::RegularExpression::instance().clear_all_patterns();
        }

        void TearDown() override
        {
            QLogicaeCore::RegularExpression::instance().clear_all_patterns();
        }
    };

    TEST_F(RegularExpressionTest, Should_AddPattern_When_GivenValidPattern)
    {
        ASSERT_TRUE(QLogicaeCore::RegularExpression::instance().add_pattern("digit", R"(\d+)"));
        ASSERT_TRUE(QLogicaeCore::RegularExpression::instance().has_pattern("digit"));
        ASSERT_EQ(QLogicaeCore::RegularExpression::instance().get_patterrn("digit"), R"(\d+)");
    }

    TEST_F(RegularExpressionTest, Should_ReturnFalse_When_AddingInvalidPattern)
    {
        ASSERT_FALSE(QLogicaeCore::RegularExpression::instance().add_pattern("invalid", R"([)"));
        ASSERT_FALSE(QLogicaeCore::RegularExpression::instance().has_pattern("invalid"));
    }

    TEST_F(RegularExpressionTest, Should_MatchNamed_When_ValidSubjectAndPattern)
    {
        QLogicaeCore::RegularExpression::instance().add_pattern("word", R"(\w+)");
        ASSERT_TRUE(QLogicaeCore::RegularExpression::instance().match_named("test", "word"));
    }

    TEST_F(RegularExpressionTest, Should_NotMatchNamed_When_PatternNotExist)
    {
        ASSERT_FALSE(QLogicaeCore::RegularExpression::instance().match_named("test", "none"));
    }

    TEST_F(RegularExpressionTest, Should_MatchDirect_When_GivenValidPattern)
    {
        ASSERT_TRUE(QLogicaeCore::RegularExpression::instance().match_direct("2025", R"(\d+)"));
    }

    TEST_F(RegularExpressionTest, Should_NotMatchDirect_When_InvalidPattern)
    {
        ASSERT_FALSE(QLogicaeCore::RegularExpression::instance().match_direct("abc", R"([)"));
    }

    TEST_F(RegularExpressionTest, Should_ClearAllPatterns_When_Called)
    {
        QLogicaeCore::RegularExpression::instance().add_pattern("a", R"(a)");
        QLogicaeCore::RegularExpression::instance().clear_all_patterns();
        ASSERT_FALSE(QLogicaeCore::RegularExpression::instance().has_pattern("a"));
    }

    TEST_F(RegularExpressionTest, Should_ReplaceOldPattern_When_SameNameUsed)
    {
        QLogicaeCore::RegularExpression::instance().add_pattern("val", R"(a)");
        ASSERT_TRUE(QLogicaeCore::RegularExpression::instance().add_pattern("val", R"(b)"));
        ASSERT_EQ(QLogicaeCore::RegularExpression::instance().get_patterrn("val"), R"(b)");
    }

    TEST_F(RegularExpressionTest, Should_MatchNamedAsync_When_Valid)
    {
        QLogicaeCore::RegularExpression::instance().add_pattern("alnum", R"(\w+)");
        auto fut = QLogicaeCore::RegularExpression::instance().match_named_async("abc123", "alnum");
        ASSERT_TRUE(fut.get());
    }

    TEST_F(RegularExpressionTest, Should_MatchDirectAsync_When_Valid)
    {
        auto fut = QLogicaeCore::RegularExpression::instance().match_direct_async("123", R"(\d+)");
        ASSERT_TRUE(fut.get());
    }

    TEST_F(RegularExpressionTest, Should_NotThrow_When_InvalidAsyncPattern)
    {
        auto fut = QLogicaeCore::RegularExpression::instance().match_direct_async("x", R"([)");
        ASSERT_FALSE(fut.get());
    }

    TEST_F(RegularExpressionTest, Should_MatchDirect_When_EmptySubject)
    {
        ASSERT_FALSE(QLogicaeCore::RegularExpression::instance().match_direct("", R"(\d+)"));
    }

    TEST_P(RegularExpressionTest, Should_MatchNamed_When_ParameterizedInputs)
    {
        auto [name, pattern, input] = GetParam();
        QLogicaeCore::RegularExpression::instance().add_pattern(name, pattern);
        ASSERT_TRUE(QLogicaeCore::RegularExpression::instance().match_named(input, name));
    }

    INSTANTIATE_TEST_CASE_P(RegularExpressionTestData, RegularExpressionTest, ::testing::Values(
        std::make_tuple("num", R"(\d+)", "2025"),
        std::make_tuple("word", R"(\w+)", "chatgpt"),
        std::make_tuple("alphanum", R"([a-zA-Z0-9]+)", "a1b2c3")
    ));

    TEST_F(RegularExpressionTest, Should_HandleMultithreadedAccess_When_ConcurrentAdd)
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i)
        {
            threads.emplace_back([i]()
                {
                    std::string name = "p" + std::to_string(i);
                    std::string pattern = R"(\w+)";
                    QLogicaeCore::RegularExpression::instance().add_pattern(name, pattern);
                });
        }

        for (auto& t : threads)
        {
            t.join();
        }

        for (int i = 0; i < 10; ++i)
        {
            ASSERT_TRUE(QLogicaeCore::RegularExpression::instance().has_pattern("p" + std::to_string(i)));
        }
    }

    TEST_F(RegularExpressionTest, Should_HandleStress_When_ThousandsOfDirectMatches)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 10000; ++i)
        {
            ASSERT_TRUE(QLogicaeCore::RegularExpression::instance().match_direct("match123", R"(\w+)"));
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        ASSERT_LT(duration.count(), 2000);
    }

    TEST_F(RegularExpressionTest, Should_BeFast_When_SingleMatch)
    {
        auto start = std::chrono::high_resolution_clock::now();

        ASSERT_TRUE(QLogicaeCore::RegularExpression::instance().match_direct("fastmatch", R"(\w+)"));

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        ASSERT_LT(duration.count(), 1);
    }
}
