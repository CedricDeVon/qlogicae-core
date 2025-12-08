#include "pch.hpp"

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

    TEST_F(RegularExpressionManagerTest, RemovePattern_ShouldAlwaysReturnTrue)
    {
        QLogicaeCppCore::Result<bool> result;

        manager.remove_pattern(
            result,
            "missing"
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

    TEST_F(RegularExpressionManagerTest, ConcurrentClearAndMatch_ShouldReturnTrueForMatch)
    {

        QLogicaeCppCore::Result<bool> match_result;

        {
            QLogicaeCppCore::Result<bool> tmp;
            manager.add_pattern(tmp, "a", "a+");
        }

        std::thread t_clear([&]()
            {
                QLogicaeCppCore::Result<bool> r;
                manager.clear_all_patterns(r);
            });

        std::thread t_match([&]()
            {
                QLogicaeCppCore::Result<bool> r;
                manager.match_named(r, "aaa", "a");

                match_result = r;
            });

        t_clear.join();
        t_match.join();

        EXPECT_TRUE(match_result.get_value());
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
}
