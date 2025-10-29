#include "pch.hpp"

#include "qlogicae_core/regular_expression.hpp"

namespace QLogicaeCoreTest
{
    class RegularExpressionTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string, bool>>
    {
    protected:
        void SetUp() override
        {
            QLogicaeCore::RegularExpression::get_instance().clear_all_patterns();
        }
    };

    TEST(RegularExpressionTest, Should_ReturnFalse_When_AddingInvalidPattern)
    {
        bool result = QLogicaeCore::RegularExpression::get_instance().add_pattern("invalid", "[");
        ASSERT_FALSE(result);
    }

    TEST(RegularExpressionTest, Should_ReturnTrue_When_AddingValidPattern)
    {
        bool result = QLogicaeCore::RegularExpression::get_instance().add_pattern("valid", "abc");
        ASSERT_TRUE(result);
    }

    TEST(RegularExpressionTest, Should_ReturnEmptyString_When_GettingNonexistentPattern)
    {
        std::string pattern = QLogicaeCore::RegularExpression::get_instance().get_patterrn("none");
        ASSERT_TRUE(pattern.empty());
    }

    TEST(RegularExpressionTest, Should_ReturnPattern_When_GettingExistingPattern)
    {
        QLogicaeCore::RegularExpression::get_instance().add_pattern("named", "abc");
        std::string pattern = QLogicaeCore::RegularExpression::get_instance().get_patterrn("named");
        ASSERT_EQ(pattern, "abc");
    }

    TEST(RegularExpressionTest, Should_ReturnTrue_When_PatternExists)
    {
        QLogicaeCore::RegularExpression::get_instance().add_pattern("exists", "abc");
        ASSERT_TRUE(QLogicaeCore::RegularExpression::get_instance().has_pattern("exists"));
    }

    TEST(RegularExpressionTest, Should_ReturnFalse_When_PatternDoesNotExist)
    {
        ASSERT_FALSE(QLogicaeCore::RegularExpression::get_instance().has_pattern("missing"));
    }

    TEST(RegularExpressionTest, Should_ReturnTrue_When_NamedPatternMatchesSubject)
    {
        QLogicaeCore::RegularExpression::get_instance().add_pattern("match", "abc");
        ASSERT_TRUE(QLogicaeCore::RegularExpression::get_instance().match_named("abc", "match"));
    }

    TEST(RegularExpressionTest, Should_ReturnFalse_When_NamedPatternNotFound)
    {
        ASSERT_FALSE(QLogicaeCore::RegularExpression::get_instance().match_named("abc", "missing"));
    }

    TEST(RegularExpressionTest, Should_ReturnTrue_When_DirectMatch)
    {
        ASSERT_TRUE(QLogicaeCore::RegularExpression::get_instance().match_direct("abc", "abc"));
    }

    TEST(RegularExpressionTest, Should_ReturnFalse_When_DirectMatchFails)
    {
        ASSERT_FALSE(QLogicaeCore::RegularExpression::get_instance().match_direct("xyz", "abc"));
    }

    TEST(RegularExpressionTest, Should_ReturnFalse_When_DirectMatchPatternInvalid)
    {
        ASSERT_FALSE(QLogicaeCore::RegularExpression::get_instance().match_direct("abc", "["));
    }

    TEST(RegularExpressionTest, Should_CompleteUnderTimeLimit_When_AsyncMatchNamed)
    {
        QLogicaeCore::RegularExpression::get_instance().add_pattern("async", "abc");
        auto future = QLogicaeCore::RegularExpression::get_instance().match_named_async("abc", "async");
        ASSERT_TRUE(future.wait_for(std::chrono::seconds(2)) == std::future_status::ready);
        ASSERT_TRUE(future.get());
    }

    TEST(RegularExpressionTest, Should_CompleteUnderTimeLimit_When_AsyncMatchDirect)
    {
        auto future = QLogicaeCore::RegularExpression::get_instance().match_direct_async("abc", "abc");
        ASSERT_TRUE(future.wait_for(std::chrono::seconds(2)) == std::future_status::ready);
        ASSERT_TRUE(future.get());
    }

    TEST(RegularExpressionTest, Should_ClearAllPatterns_When_Called)
    {
        QLogicaeCore::RegularExpression::get_instance().add_pattern("toClear", "abc");
        QLogicaeCore::RegularExpression::get_instance().clear_all_patterns();
        ASSERT_FALSE(QLogicaeCore::RegularExpression::get_instance().has_pattern("toClear"));
    }

    TEST_P(RegularExpressionTest, Should_MatchCorrectly_When_Parameterized)
    {
        std::string name, pattern, subject;
        bool expected;
        std::tie(name, pattern, subject, expected) = GetParam();
        QLogicaeCore::RegularExpression::get_instance().add_pattern(name, pattern);
        ASSERT_EQ(QLogicaeCore::RegularExpression::get_instance().match_named(subject, name), expected);
    }

    INSTANTIATE_TEST_CASE_P(
        MatchParameterized,
        RegularExpressionTest,
        ::testing::Values(
            std::make_tuple("digits", "\\d+", "12345", true),
            std::make_tuple("alpha", "[a-zA-Z]+", "abcXYZ", true),
            std::make_tuple("empty", "", "", true),
            std::make_tuple("nonmatch", "abc", "def", false),
            std::make_tuple("special", "^\\w+$", "@!#", false)
        )
    );

    TEST(RegularExpressionTest, Should_HandleStress_When_RepeatingAddAndMatch)
    {
        for (int index = 0; index < 10000; ++index)
        {
            std::string name = "name" + std::to_string(index);
            QLogicaeCore::RegularExpression::get_instance().add_pattern(name, "abc");
            ASSERT_TRUE(QLogicaeCore::RegularExpression::get_instance().match_named("abc", name));
        }
    }

    TEST(RegularExpressionTest, Should_HandleConcurrentAccess_When_MultipleThreads)
    {
        std::atomic<bool> success = true;
        QLogicaeCore::RegularExpression::get_instance().add_pattern("threaded", "abc");

        auto task = []()
            {
                for (int index = 0; index < 1000; ++index)
                {
                    if (!QLogicaeCore::RegularExpression::get_instance().match_named("abc", "threaded"))
                    {
                        return false;
                    }
                }
                return true;
            };

        std::thread thread1([&]() { if (!task()) success = false; });
        std::thread thread2([&]() { if (!task()) success = false; });

        thread1.join();
        thread2.join();

        ASSERT_TRUE(success);
    }

    TEST(RegularExpressionTest, Should_HandleConcurrentAddClearMatch_When_MultipleThreads)
    {
        std::atomic<bool> success = true;

        std::thread adder([&]() {
            for (int i = 0; i < 1000; ++i)
            {
                std::string name = "pattern" + std::to_string(i);
                QLogicaeCore::RegularExpression::get_instance().add_pattern(name, "abc");
            }
            });

        std::thread clearer([&]() {
            for (int i = 0; i < 100; ++i)
            {
                QLogicaeCore::RegularExpression::get_instance().clear_all_patterns();
            }
            });

        std::thread matcher([&]() {
            for (int i = 0; i < 1000; ++i)
            {
                QLogicaeCore::RegularExpression::get_instance().match_named("abc", "pattern1");
            }
            });

        adder.join();
        clearer.join();
        matcher.join();

        ASSERT_TRUE(success);
    }

    TEST(RegularExpressionTest, Should_NotLeakMemory_When_ReplacingPatternsRepeatedly)
    {
        for (int i = 0; i < 10000; ++i)
        {
            ASSERT_TRUE(QLogicaeCore::RegularExpression::get_instance().add_pattern("repeat", "abc"));
        }
        ASSERT_TRUE(QLogicaeCore::RegularExpression::get_instance().match_named("abc", "repeat"));
    }

    TEST(RegularExpressionTest, Should_HandleLongAndUTF8Strings_When_Matching)
    {
        std::string long_subject(10000, 'a');
        std::string long_pattern = "a{10000}";
        ASSERT_TRUE(QLogicaeCore::RegularExpression::get_instance().match_direct(long_subject, long_pattern));
    }
}

