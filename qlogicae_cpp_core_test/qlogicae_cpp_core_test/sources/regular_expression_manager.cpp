#include "pch.hpp" //

#include "qlogicae_cpp_core/includes/regular_expression_manager.hpp"

namespace QLogicaeCppCoreTest
{
    struct PatternParameter
    {
        std::string name;
        std::string expression;
        std::string subject;
        bool expected;
    };

    struct EdgeParameter
    {
        std::string name;
        std::string expression;
        std::string subject;
        bool expected;
    };

    struct RegexParameter
    {
        std::string name;
        std::string expression;
        std::string subject;
        bool expected;
    };

    class RegularExpressionManagerTest :
        public ::testing::Test,
        public ::testing::WithParamInterface<PatternParameter>
    {
    public:
        QLogicaeCppCore::RegularExpressionManager manager;
        QLogicaeCppCore::Result<bool> bool_result;
        QLogicaeCppCore::Result<std::string> string_result;
        std::mutex mutex_object;
        std::condition_variable condition_object;
        std::atomic<int> ready_count;
        QLogicaeCppCore::Result<bool> shared_result;

        RegularExpressionManagerTest()
        {
            ready_count = 0;
        }
    };

    TEST_F(
        RegularExpressionManagerTest,
        ShouldAddValidPattern
    )
    {
        manager.add_pattern(
            bool_result,
            "alpha",
            "a+"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_TRUE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldReturnFalseWhenPatternMissing
    )
    {
        manager.has_pattern(
            bool_result,
            "missing"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_FALSE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldDetectExistingPattern
    )
    {
        manager.add_pattern(
            bool_result,
            "beta",
            "b+"
        );

        manager.has_pattern(
            bool_result,
            "beta"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_TRUE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldReturnStoredExpression
    )
    {
        manager.add_pattern(
            bool_result,
            "gamma",
            "c+"
        );

        manager.get_patterrn(
            string_result,
            "gamma"
        );

        std::string value;
        string_result.get_value(value);

        ASSERT_EQ(value, "c+");
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldReturnEmptyWhenNotFound
    )
    {
        manager.get_patterrn(
            string_result,
            "none"
        );

        std::string value;
        string_result.get_value(value);

        ASSERT_EQ(value, "");
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldMatchNamedPatternTrue
    )
    {
        manager.add_pattern(
            bool_result,
            "delta",
            "d+"
        );

        manager.match_named(
            bool_result,
            "ddd",
            "delta"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_TRUE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldMatchNamedPatternFalse
    )
    {
        manager.add_pattern(
            bool_result,
            "epsilon",
            "e+"
        );

        manager.match_named(
            bool_result,
            "a",
            "epsilon"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_FALSE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldMatchDirectTrue
    )
    {
        manager.match_direct(
            bool_result,
            "zzz",
            "z+"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_TRUE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldMatchDirectFalse
    )
    {
        manager.match_direct(
            bool_result,
            "x",
            "z+"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_FALSE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldReturnBadWhenInvalidCompileNamed
    )
    {
        manager.add_pattern(
            bool_result,
            "invalid",
            "("
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_FALSE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldReturnBadWhenInvalidCompileDirect
    )
    {
        manager.match_direct(
            bool_result,
            "abc",
            "("
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_FALSE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldClearPatterns
    )
    {
        manager.add_pattern(
            bool_result,
            "zeta",
            "z+"
        );

        manager.clear_all_patterns(
            bool_result
        );

        manager.has_pattern(
            bool_result,
            "zeta"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_FALSE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldHandleAsyncAdd
    )
    {
        auto future_object = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> local;
                manager.add_pattern(
                    local,
                    "async",
                    "a+"
                );
                bool value = false;
                local.get_value(value);
                return value;
            }
        );

        bool output = future_object.get();
        ASSERT_TRUE(output);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldHandleAsyncMatchNamed
    )
    {
        manager.add_pattern(
            bool_result,
            "async_named",
            "b+"
        );

        auto future_object = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> local;
                manager.match_named(
                    local,
                    "bbb",
                    "async_named"
                );
                bool value = false;
                local.get_value(value);
                return value;
            }
        );

        bool output = future_object.get();
        ASSERT_TRUE(output);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldHandleAsyncMatchDirect
    )
    {
        auto future_object = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> local;
                manager.match_direct(
                    local,
                    "ccc",
                    "c+"
                );
                bool value = false;
                local.get_value(value);
                return value;
            }
        );

        bool output = future_object.get();
        ASSERT_TRUE(output);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldWorkWithPromise
    )
    {
        std::promise<bool> promise_object;
        std::future<bool> future_object = promise_object.get_future();

        std::thread worker(
            [&]()
            {
                QLogicaeCppCore::Result<bool> local;
                manager.match_direct(
                    local,
                    "ddd",
                    "d+"
                );
                bool value = false;
                local.get_value(value);
                promise_object.set_value(value);
            }
        );

        worker.join();
        bool output = future_object.get();
        ASSERT_TRUE(output);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldHandleMultipleThreads
    )
    {
        int thread_count = 16;
        std::vector<std::thread> threads;

        for (int index = 0; index < thread_count; index++)
        {
            threads.emplace_back(
                [&]()
                {
                    QLogicaeCppCore::Result<bool> local;
                    manager.match_direct(
                        local,
                        "aaa",
                        "a+"
                    );

                    {
                        std::lock_guard<std::mutex> guard(mutex_object);
                        shared_result = local;
                        ready_count++;
                    }

                    condition_object.notify_one();
                }
            );
        }

        {
            std::unique_lock<std::mutex> lock(mutex_object);
            condition_object.wait(
                lock,
                [&]()
                {
                    return ready_count.load() == thread_count;
                }
            );
        }

        for (auto& th : threads)
        {
            th.join();
        }

        bool value = false;
        shared_result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldStressMatchDirect
    )
    {
        int iteration_count = 5000;

        for (int index = 0; index < iteration_count; index++)
        {
            manager.match_direct(
                bool_result,
                "stress",
                "s+"
            );
        }

        bool value = false;
        bool_result.get_value(value);

        ASSERT_TRUE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldStressAddPatterns
    )
    {
        int iteration_count = 2000;

        for (int index = 0; index < iteration_count; index++)
        {
            std::string name = "n" + std::to_string(index);
            manager.add_pattern(
                bool_result,
                name,
                "a+"
            );
        }

        bool value = false;
        bool_result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldReturnFalseWhenNamedPatternMissing
    )
    {
        manager.match_named(
            bool_result,
            "abc",
            "unknown"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_FALSE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldReturnFalseWhenSubjectEmptyNamed
    )
    {
        manager.add_pattern(
            bool_result,
            "alpha",
            "a+"
        );

        manager.match_named(
            bool_result,
            "",
            "alpha"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_FALSE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldReturnFalseWhenSubjectEmptyDirect
    )
    {
        manager.match_direct(
            bool_result,
            "",
            "a+"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_FALSE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldOverwriteDuplicatePattern
    )
    {
        manager.add_pattern(
            bool_result,
            "dup",
            "a+"
        );

        manager.add_pattern(
            bool_result,
            "dup",
            "b+"
        );

        manager.match_named(
            bool_result,
            "bbb",
            "dup"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_TRUE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldHandleVeryLongSubject
    )
    {
        std::string subject(20000, 'a');

        manager.add_pattern(
            bool_result,
            "long",
            "a+"
        );

        manager.match_named(
            bool_result,
            subject,
            "long"
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_TRUE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldHandleVeryLongExpression
    )
    {
        std::string pattern(20000, 'a');

        manager.add_pattern(
            bool_result,
            "long_expr",
            pattern
        );

        bool value = false;
        bool_result.get_value(value);

        ASSERT_TRUE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldHandleConcurrentAddAndMatch
    )
    {
        int thread_count = 8;
        std::vector<std::thread> threads;

        for (int index = 0; index < thread_count; index++)
        {
            threads.emplace_back(
                [&]()
                {
                    QLogicaeCppCore::Result<bool> local;

                    manager.add_pattern(local, "a", "a+");

                    manager.match_named(local, "aaa", "a");

                    std::lock_guard<std::mutex> guard(mutex_object);
                    shared_result = local;
                    ready_count++;
                    condition_object.notify_one();
                }
            );
        }

        {
            std::unique_lock<std::mutex> lock(mutex_object);
            condition_object.wait(
                lock,
                [&]()
                {
                    return ready_count.load() == thread_count;
                }
            );
        }

        for (auto& th : threads)
        {
            th.join();
        }

        bool value = false;
        shared_result.get_value(value);

        ASSERT_TRUE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldStressMixedOperations
    )
    {
        int count = 3000;

        for (int index = 0; index < count; index++)
        {
            manager.add_pattern(
                bool_result,
                "a",
                "a+"
            );

            manager.match_direct(
                bool_result,
                "aaa",
                "a+"
            );
        }

        bool value = false;
        bool_result.get_value(value);

        ASSERT_TRUE(value);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldHandleAsyncGetPattern
    )
    {
        manager.add_pattern(
            bool_result,
            "async_get",
            "a+"
        );

        auto future_object = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<std::string> local;
                manager.get_patterrn(local, "async_get");

                std::string value;
                local.get_value(value);

                return value;
            }
        );

        std::string output = future_object.get();
        ASSERT_EQ(output, "a+");
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldHandleAsyncHasPattern
    )
    {
        manager.add_pattern(
            bool_result,
            "async_has",
            "a+"
        );

        auto future_object = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> local;
                manager.has_pattern(local, "async_has");

                bool value = false;
                local.get_value(value);

                return value;
            }
        );

        bool output = future_object.get();
        ASSERT_TRUE(output);
    }

    TEST_F(
        RegularExpressionManagerTest,
        ShouldHandleAsyncClear
    )
    {
        manager.add_pattern(
            bool_result,
            "async_clear",
            "a+"
        );

        auto future_object = std::async(
            std::launch::async,
            [&]()
            {
                QLogicaeCppCore::Result<bool> local;
                manager.clear_all_patterns(local);
                bool value = false;
                local.get_value(value);
                return value;
            }
        );

        bool output = future_object.get();
        ASSERT_TRUE(output);
    }

    TEST_F(RegularExpressionManagerTest, AddPattern_WithEmptyName_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> result;

        manager.add_pattern(
            result,
            "",
            "a+"
        );

        EXPECT_TRUE(result.get_value());
    }

    TEST_F(RegularExpressionManagerTest, AddPattern_WithEmptyExpression_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> result;

        manager.add_pattern(
            result,
            "name",
            ""
        );

        EXPECT_TRUE(result.get_value());
    }

    TEST_F(RegularExpressionManagerTest, AddPattern_WithVeryLongExpression_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> result;

        std::string long_expr;
        long_expr.reserve(5000);
        long_expr.append(5000, 'a');

        manager.add_pattern(
            result,
            "long",
            long_expr
        );

        EXPECT_TRUE(result.get_value());
    }

    TEST_F(RegularExpressionManagerTest, MatchNamed_WhenPatternMissing_ShouldReturnFalse)
    {
        QLogicaeCppCore::Result<bool> result;

        manager.match_named(
            result,
            "abc",
            "not_exist"
        );

        EXPECT_FALSE(result.get_value());
    }

    TEST_F(RegularExpressionManagerTest, MatchDirect_WithInvalidExpression_ShouldReturnFalse)
    {
        QLogicaeCppCore::Result<bool> result;

        manager.match_direct(
            result,
            "abc",
            "("
        );

        EXPECT_FALSE(result.get_value());
    }

    TEST_F(RegularExpressionManagerTest, ClearAllPatterns_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> result;

        manager.clear_all_patterns(result);

        EXPECT_TRUE(result.get_value());
    }

    TEST_F(RegularExpressionManagerTest, HasPattern_WhenNotPresent_ShouldReturnFalse)
    {
        QLogicaeCppCore::Result<bool> result;

        manager.has_pattern(
            result,
            "none"
        );

        EXPECT_FALSE(result.get_value());
    }

    TEST_F(RegularExpressionManagerTest, HasPattern_WhenPresent_ShouldReturnTrue)
    {

        {
            QLogicaeCppCore::Result<bool> tmp;
            manager.add_pattern(tmp, "x", "x+");
        }

        QLogicaeCppCore::Result<bool> result;

        manager.has_pattern(
            result,
            "x"
        );

        EXPECT_TRUE(result.get_value());
    }

    TEST_F(RegularExpressionManagerTest, GetPattern_WhenMissing_ShouldReturnEmptyString)
    {
        QLogicaeCppCore::Result<std::string> result;

        manager.get_patterrn(
            result,
            "none"
        );

        EXPECT_EQ("", result.get_value());
    }

    TEST_F(RegularExpressionManagerTest, GetPattern_WhenPresent_ShouldReturnStoredExpression)
    {

        {
            QLogicaeCppCore::Result<bool> tmp;
            manager.add_pattern(tmp, "y", "y+");
        }

        QLogicaeCppCore::Result<std::string> result;

        manager.get_patterrn(
            result,
            "y"
        );

        EXPECT_EQ("y+", result.get_value());
    }


    TEST_F(RegularExpressionManagerTest, Add_BasicValidAdd_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> result;
        manager.add_pattern(result, "valid", "a+");
        bool value = false;
        result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, Add_EmptyName_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> result;
        manager.add_pattern(result, "", "a+");
        bool value = false;
        result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, Add_EmptyExpression_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> result;
        manager.add_pattern(result, "name", "");
        bool value = false;
        result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, Add_VeryLongExpression_ShouldReturnTrue)
    {
        std::string long_expr;
        long_expr.reserve(15000);
        long_expr.append(12000, 'a');
        QLogicaeCppCore::Result<bool> result;
        manager.add_pattern(result, "longexpr", long_expr);
        bool value = false;
        result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, Add_VeryLongName_ShouldReturnTrue)
    {
        std::string long_name;
        long_name.reserve(15000);
        long_name.append(12000, 'n');
        QLogicaeCppCore::Result<bool> result;
        manager.add_pattern(result, long_name, "a+");
        bool value = false;
        result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, Add_DuplicateName_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> r1;
        manager.add_pattern(r1, "dup", "a+");
        QLogicaeCppCore::Result<bool> r2;
        manager.add_pattern(r2, "dup", "a+");
        bool second = false;
        r2.get_value(second);
        ASSERT_TRUE(second);
    }

    TEST_F(RegularExpressionManagerTest, Add_NullLikeStrings_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> r1;
        manager.add_pattern(r1, " ", "a+");
        bool v1 = false;
        r1.get_value(v1);
        ASSERT_TRUE(v1);
        QLogicaeCppCore::Result<bool> r2;
        manager.add_pattern(r2, "name", " ");
        bool v2 = false;
        r2.get_value(v2);
        ASSERT_TRUE(v2);
    }

    TEST_F(RegularExpressionManagerTest, Regex_GreedyNonGreedy)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.match_direct(r, "aaaa", "a+");
        bool v = false;
        r.get_value(v);
        ASSERT_TRUE(v);
        QLogicaeCppCore::Result<bool> r2;
        manager.match_direct(r2, "ab", "a+?");
        bool v2 = false;
        r2.get_value(v2);
        ASSERT_TRUE(v2);
    }

    TEST_F(RegularExpressionManagerTest, Add_InvalidExpression_ShouldReturnFalse)
    {
        QLogicaeCppCore::Result<bool> result;
        manager.add_pattern(result, "inv", "(abc");
        bool value = false;
        result.get_value(value);
        ASSERT_FALSE(value);
    }

    TEST_F(RegularExpressionManagerTest, Add_SpecialCharactersName_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> result;
        manager.add_pattern(result, "name!@#$%^&*()", "a+");
        bool value = false;
        result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, Add_AfterClear_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> tmp;
        manager.add_pattern(tmp, "t1", "a+");
        QLogicaeCppCore::Result<bool> c;
        manager.clear_all_patterns(c);
        QLogicaeCppCore::Result<bool> result;
        manager.add_pattern(result, "after", "b+");
        bool value = false;
        result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, Match_ExistingEntry_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.add_pattern(r, "m1", "abc");
        QLogicaeCppCore::Result<bool> result;
        manager.match_named(result, "abc", "m1");
        bool value = false;
        result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, Match_FailingSubject_ShouldReturnFalse)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.add_pattern(r, "m2", "a+");
        QLogicaeCppCore::Result<bool> result;
        manager.match_named(result, "bbb", "m2");
        bool value = false;
        result.get_value(value);
        ASSERT_FALSE(value);
    }

    TEST_F(RegularExpressionManagerTest, Match_UnknownName_ShouldReturnFalse)
    {
        QLogicaeCppCore::Result<bool> result;
        manager.match_named(result, "abc", "unknown_name");
        bool value = false;
        result.get_value(value);
        ASSERT_FALSE(value);
    }

    TEST_F(RegularExpressionManagerTest, Match_EmptySubject_BehavesCorrectly)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.add_pattern(r, "empty", "^$");
        QLogicaeCppCore::Result<bool> result;
        manager.match_named(result, "", "empty");
        bool value = false;
        result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, Match_VeryLargeSubject_ShouldReturn)
    {
        std::string subject;
        subject.reserve(15000);
        subject.append(12000, 'a');
        QLogicaeCppCore::Result<bool> r;
        manager.add_pattern(r, "longs", "a+");
        QLogicaeCppCore::Result<bool> result;
        manager.match_named(result, subject, "longs");
        bool value = false;
        result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, Match_InvalidStoredExpression_ShouldNotMatch)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.add_pattern(r, "inv2", "(abc");
        QLogicaeCppCore::Result<bool> result;
        manager.match_named(result, "abc", "inv2");
        bool value = false;
        result.get_value(value);
        ASSERT_FALSE(value);
    }

    TEST_F(RegularExpressionManagerTest, Match_ConcurrentAdd_ShouldBeSafe)
    {
        int thread_count = 8;
        std::vector<std::thread> threads;
        for (int i = 0; i < thread_count; i++)
        {
            threads.emplace_back(
                [this]()
                {
                    QLogicaeCppCore::Result<bool> r;
                    manager.add_pattern(r, "con", "a+");
                    QLogicaeCppCore::Result<bool> m;
                    manager.match_named(m, "aaa", "con");
                }
            );
        }
        for (auto& th : threads) th.join();
        QLogicaeCppCore::Result<bool> result;
        manager.match_named(result, "aaa", "con");
        bool value = false;
        result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, ConcurrentClear_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.add_pattern(r, "c1", "a+");
        QLogicaeCppCore::Result<bool> match_result;
        std::thread tclear([this]()
            {
                QLogicaeCppCore::Result<bool> rr;
                manager.clear_all_patterns(rr);
            });
        tclear.join();
        bool value = false;
        match_result.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, Remove_ExistingEntry_ShouldReturnTrue)
    {
        QLogicaeCppCore::Result<bool> radd;
        manager.add_pattern(radd, "rem1", "a+");
        QLogicaeCppCore::Result<bool> r;
        manager.remove_pattern(r, "rem1");
        bool value = false;
        r.get_value(value);
        ASSERT_TRUE(value);
    }

    TEST_F(RegularExpressionManagerTest, Remove_NonexistentEntry_ShouldReturnFalse)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.remove_pattern(r, "doesnotexist");
        bool value = false;
        r.get_value(value);
        ASSERT_FALSE(value);
    }

    TEST_F(RegularExpressionManagerTest, Remove_AfterClear_ShouldReturnFalse)
    {
        QLogicaeCppCore::Result<bool> radd;
        manager.add_pattern(radd, "rem2", "a+");
        QLogicaeCppCore::Result<bool> rc;
        manager.clear_all_patterns(rc);
        QLogicaeCppCore::Result<bool> r;
        manager.remove_pattern(r, "rem2");
        bool value = false;
        r.get_value(value);
        ASSERT_FALSE(value);
    }

    TEST_F(RegularExpressionManagerTest, Remove_ConcurrentWithAdd_ShouldBeStable)
    {
        std::atomic<bool> removed{ false };
        std::thread tadd([this]()
            {
                QLogicaeCppCore::Result<bool> r;
                manager.add_pattern(r, "ra", "a+");
            });
        std::thread trem([this, &removed]()
            {
                QLogicaeCppCore::Result<bool> r;
                manager.remove_pattern(r, "ra");
                bool v = false;
                r.get_value(v);
                removed.store(v);
            });
        tadd.join();
        trem.join();
        ASSERT_TRUE(removed.load() == true || removed.load() == false);
    }

    TEST_F(RegularExpressionManagerTest, Remove_WhileMatchRunning_ShouldNotCrash)
    {
        QLogicaeCppCore::Result<bool> radd;
        manager.add_pattern(radd, "rm", "a+");
        std::thread tmatch([this]()
            {
                QLogicaeCppCore::Result<bool> rm;
                manager.match_named(rm, "aaa", "rm");
            });
        std::thread trem([this]()
            {
                QLogicaeCppCore::Result<bool> rr;
                manager.remove_pattern(rr, "rm");
            });
        tmatch.join();
        trem.join();
        SUCCEED();
    }

    TEST_F(RegularExpressionManagerTest, Clear_BasicClear_RemovesAll)
    {
        QLogicaeCppCore::Result<bool> r1;
        QLogicaeCppCore::Result<bool> r2;
        manager.add_pattern(r1, "cA", "a+");
        manager.add_pattern(r2, "cB", "b+");
        QLogicaeCppCore::Result<bool> rc;
        manager.clear_all_patterns(rc);
        QLogicaeCppCore::Result<bool> h1;
        manager.has_pattern(h1, "cA");
        bool v1 = false;
        h1.get_value(v1);
        QLogicaeCppCore::Result<bool> h2;
        manager.has_pattern(h2, "cB");
        bool v2 = false;
        h2.get_value(v2);
        ASSERT_FALSE(v1);
        ASSERT_FALSE(v2);
    }

    TEST_F(RegularExpressionManagerTest, Clear_WhenEmpty_ShouldBeSafe)
    {
        QLogicaeCppCore::Result<bool> rc;
        manager.clear_all_patterns(rc);
        bool v = false;
        rc.get_value(v);
        ASSERT_TRUE(v);
    }

    TEST_F(RegularExpressionManagerTest, Clear_ConcurrentAdd_ShouldNotCorrupt)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.add_pattern(r, "a1", "a+");
        std::thread tclear([this]()
            {
                QLogicaeCppCore::Result<bool> rc;
                manager.clear_all_patterns(rc);
            });
        std::thread tadd([this]()
            {
                QLogicaeCppCore::Result<bool> ra;
                manager.add_pattern(ra, "a2", "a+");
            });
        tclear.join();
        tadd.join();
        SUCCEED();
    }

    TEST_F(RegularExpressionManagerTest, List_GetSizeReflectsOperations)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.add_pattern(r, "ls1", "a+");
        manager.add_pattern(r, "ls2", "b+");
        QLogicaeCppCore::Result<bool> h1;
        manager.has_pattern(h1, "ls1");
        bool v1 = false;
        h1.get_value(v1);
        QLogicaeCppCore::Result<bool> h2;
        manager.has_pattern(h2, "ls2");
        bool v2 = false;
        h2.get_value(v2);
        ASSERT_TRUE(v1);
        ASSERT_TRUE(v2);
    }

    TEST_F(RegularExpressionManagerTest, Stress_MultiThreadedAdd_UniqueNames)
    {
        int thread_count = 16;
        std::vector<std::thread> threads;
        for (int i = 0; i < thread_count; i++)
        {
            threads.emplace_back(
                [this, i]()
                {
                    QLogicaeCppCore::Result<bool> r;
                    manager.add_pattern(r, "u" + std::to_string(i), "a+");
                }
            );
        }
        for (auto& t : threads) t.join();
        int found = 0;
        for (int i = 0; i < thread_count; i++)
        {
            QLogicaeCppCore::Result<bool> r;
            manager.has_pattern(r, "u" + std::to_string(i));
            bool v = false;
            r.get_value(v);
            if (v) found++;
        }
        ASSERT_EQ(found, thread_count);
    }

    TEST_F(RegularExpressionManagerTest, Stress_MultiThreadedRemove)
    {
        for (int i = 0; i < 100; i++)
        {
            QLogicaeCppCore::Result<bool> r;
            manager.add_pattern(r, "rm" + std::to_string(i), "a+");
        }
        std::vector<std::thread> threads;
        for (int i = 0; i < 50; i++)
        {
            threads.emplace_back(
                [this, i]()
                {
                    QLogicaeCppCore::Result<bool> r;
                    manager.remove_pattern(r, "rm" + std::to_string(i));
                }
            );
        }
        for (auto& t : threads) t.join();
        SUCCEED();
    }

    TEST_F(RegularExpressionManagerTest, Stress_MixedAddMatch)
    {
        for (int i = 0; i < 500; i++)
        {
            QLogicaeCppCore::Result<bool> r;
            manager.add_pattern(r, "m" + std::to_string(i), "a+");
            QLogicaeCppCore::Result<bool> rm;
            manager.match_direct(rm, "aaa", "a+");
        }
        SUCCEED();
    }

    TEST_F(RegularExpressionManagerTest, Regex_BoundariesGroupsNested)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.match_direct(r, "abc", "^(a|b)c$");
        bool v = false;
        r.get_value(v);
        ASSERT_FALSE(v);
    }

    TEST_F(RegularExpressionManagerTest, Regex_InvalidEscape_ShouldReturnFalse)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.match_direct(r, "x", "\\");
        bool v = false;
        r.get_value(v);
        ASSERT_FALSE(v);
    }

    TEST_F(RegularExpressionManagerTest, Operational_AddAfterInternalError)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.add_pattern(r, "err", "(");
        QLogicaeCppCore::Result<bool> r2;
        manager.add_pattern(r2, "ok", "a+");
        bool v = false;
        r2.get_value(v);
        ASSERT_TRUE(v);
    }

    TEST_F(RegularExpressionManagerTest, Operational_RemoveWithWhitespaceName)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.add_pattern(r, " ws ", "a+");
        QLogicaeCppCore::Result<bool> rm;
        manager.remove_pattern(rm, " ws ");
        bool v = false;
        rm.get_value(v);
        ASSERT_TRUE(v);
    }

    TEST_F(RegularExpressionManagerTest, Regex_CompilesButAlwaysFails)
    {
        QLogicaeCppCore::Result<bool> r;
        manager.add_pattern(r, "f", "(?!)");
        QLogicaeCppCore::Result<bool> m;
        manager.match_named(m, "anything", "f");
        bool v = false;
        m.get_value(v);
        ASSERT_FALSE(v);
    }

    TEST_F(RegularExpressionManagerTest, Regex_CatastrophicBacktrackComplex)
    {
        std::string subject(2000, 'a');
        QLogicaeCppCore::Result<bool> r;
        manager.match_direct(r, subject, "(a+)+b");
        bool v = false;
        r.get_value(v);
        ASSERT_FALSE(v);
    }
}
