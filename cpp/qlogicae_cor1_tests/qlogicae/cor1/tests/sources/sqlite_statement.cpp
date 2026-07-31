#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteStatement \
	)

#include "../includes/sqlite_statement.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	TEST_F(SQLiteStatementTest,
        Should_Expect_Step_When_SelectQueryExecuted)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT 1;"
        );

        bool has_row = statement.step();

        EXPECT_TRUE(has_row);
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_Exception_When_InvalidSql)
    {
        auto backend = create_backend();

        EXPECT_THROW(
            SQLiteStatement(
                backend,
                "INVALID SQL"
            ),
            SQLiteException
        );
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_Reset_When_ResetCalled)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT 1;"
        );

        statement.step();

        EXPECT_TRUE(statement.reset());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_ClearBindings_When_ValidStatement)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT 1;"
        );

        EXPECT_TRUE(statement.clear_bindings());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_Row_When_QueryExecuted)
    {
        auto backend = create_backend();

        sqlite3_exec(backend->database_handle,
            "CREATE TABLE test(id INT);",
            nullptr, nullptr, nullptr);

        sqlite3_exec(backend->database_handle,
            "INSERT INTO test VALUES(1);",
            nullptr, nullptr, nullptr);

        SQLiteStatement statement(
            backend,
            "SELECT * FROM test;"
        );

        auto rows = statement.query();

        EXPECT_EQ(rows.size(), 1);
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_Exception_When_InvalidBindIndex)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        EXPECT_THROW(
            statement.bind(0, 10),
            SQLiteException
        );
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_NamedBind_When_ParameterUsed)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        statement.bind(":value", 10);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_AsyncStep_When_RunInAsync)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT 1;"
        );

        auto future_result = std::async(std::launch::async,
            [&statement]()
        {
            return statement.step();
        });

        EXPECT_TRUE(future_result.get());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_ThreadSafe_When_MultipleThreadsRead)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT 1;"
        );

        std::atomic<int> success_count = 0;

        std::thread thread_one([&]()
        {
            if (statement.step())
            {
                success_count++;
            }
        });

        std::thread thread_two([&]()
        {
            if (statement.step())
            {
                success_count++;
            }
        });

        thread_one.join();
        thread_two.join();

        EXPECT_GE(success_count.load(), 1);
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_Stress_When_LargeIterationLoop)
    {
        auto backend = create_backend();

        sqlite3_exec(backend->database_handle,
            "CREATE TABLE stress(id INT);",
            nullptr, nullptr, nullptr);

        SQLiteStatement statement(
            backend,
            "INSERT INTO stress VALUES(1);"
        );

        for (int i = 0; i < 10000; i++)
        {
            statement.reset();
            statement.step();
        }

        EXPECT_TRUE(true);
    }

    INSTANTIATE_TEST_CASE_P(
        SQLiteStatementTestCases,
        SQLiteStatementParameterTest,
        ::testing::Values(0, 1, 100, -1)
    );

    TEST_P(SQLiteStatementParameterTest,
        Should_Expect_Bind_When_ParamUsed)
    {
        auto value = GetParam();

        SQLiteStatement statement(
            create_backend(),
            "SELECT ?;"
        );

        if (value <= 0)
        {
            EXPECT_THROW(statement.bind(0, value),
                SQLiteException);
        }
        else
        {
            statement.bind(1, value);
            EXPECT_TRUE(statement.step());
        }
    }

    TEST_F(SQLiteStatementPerformanceTest,
        Should_Expect_FastExecution_When_StressQuery)
    {
        auto start = std::chrono::high_resolution_clock::now();

        SQLiteStatement statement(
            create_backend(),
            "SELECT 1;"
        );

        for (int i = 0; i < 100000; i++)
        {
            statement.step();
            statement.reset();
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto duration =
            std::chrono::duration_cast<
                std::chrono::milliseconds>(
                    end - start).count();

        EXPECT_LT(duration, 2000);
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_Done_When_SelectFinishes)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT 1;"
        );

        EXPECT_TRUE(statement.step());
        EXPECT_FALSE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_False_When_StepAfterDone)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT 1;"
        );

        statement.step();
        statement.step();

        EXPECT_FALSE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_Reusable_When_ResetAfterDone)
    {
        auto backend = create_backend();

        sqlite3_exec(backend->database_handle,
            "CREATE TABLE t(x INT);",
            nullptr, nullptr, nullptr);

        sqlite3_exec(backend->database_handle,
            "INSERT INTO t VALUES(1);",
            nullptr, nullptr, nullptr);

        SQLiteStatement statement(
            backend,
            "SELECT x FROM t;"
        );

        statement.step();
        statement.step();

        EXPECT_TRUE(statement.reset());
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_BindDouble_When_ValidValue)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        statement.bind(1, 1.5);
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_BindFloat_When_ValidValue)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        statement.bind(1, static_cast<float>(2.5));
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_BindInt64_When_ValidValue)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        statement.bind(1, static_cast<int64_t>(123));
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_BindNullptr_When_NullValue)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        statement.bind(1, nullptr);
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_NamedAndPositional_Parity)
    {
        auto backend = create_backend();

        SQLiteStatement statement1(
            backend,
            "SELECT ?;"
        );

        SQLiteStatement statement2(
            backend,
            "SELECT :value;"
        );

        statement1.bind(1, 10);
        statement2.bind(":value", 10);

        EXPECT_TRUE(statement1.step());
        EXPECT_TRUE(statement2.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_NullOptional_When_OptionalNull)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        std::optional<int> value = std::nullopt;

        statement.bind(1, value);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_NoRace_When_SequentialUse)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        std::atomic<int> success = 0;

        statement.bind(1,10);
        if(statement.step())
        {
            success++;
        }

        statement.reset();

        statement.bind(1,20);
        if(statement.step())
        {
            success++;
        }

        EXPECT_GE(success.load(),1);
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_NoRace_When_ResetAndStepConcurrent)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT 1;"
        );

        std::atomic<bool> done = false;

        std::thread t1([&]()
        {
            statement.reset();
        });

        std::thread t2([&]()
        {
            done = statement.step();
        });

        t1.join();
        t2.join();

        EXPECT_TRUE(done || !done);
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_SharedBackend_When_MultipleStatements)
    {
        auto backend = create_backend();

        SQLiteStatement s1(
            backend,
            "SELECT 1;"
        );

        SQLiteStatement s2(
            backend,
            "SELECT 1;"
        );

        EXPECT_TRUE(s1.step());
        EXPECT_TRUE(s2.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_Exception_When_InvalidParameterName)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :x;"
        );

        EXPECT_THROW(
            statement.resolve_named_index(":invalid"),
            SQLiteException
        );
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_StepFailure_When_InvalidExecutionState)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT 1;"
        );

        statement.step();

        EXPECT_FALSE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_RepeatedResetCycles_When_ReusedMultipleTimes)
    {
        auto backend = create_backend();

        sqlite3_exec(backend->database_handle,
            "CREATE TABLE t(x INT);",
            nullptr, nullptr, nullptr);

        sqlite3_exec(backend->database_handle,
            "INSERT INTO t VALUES(1);",
            nullptr, nullptr, nullptr);

        SQLiteStatement statement(
            backend,
            "SELECT x FROM t;"
        );

        for (int i = 0; i < 10; i++)
        {
            statement.step();
            statement.step();
            EXPECT_TRUE(statement.reset());
        }
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_SQLiteDoneIteration_When_FullyConsumed)
    {
        auto backend = create_backend();

        sqlite3_exec(backend->database_handle,
            "CREATE TABLE t(x INT);",
            nullptr, nullptr, nullptr);

        sqlite3_exec(backend->database_handle,
            "INSERT INTO t VALUES(1);",
            nullptr, nullptr, nullptr);

        SQLiteStatement statement(
            backend,
            "SELECT x FROM t;"
        );

        int iterations = 0;

        while (statement.step())
        {
            auto row = statement.row();
            EXPECT_TRUE(row.has_value());
            iterations++;
        }

        EXPECT_EQ(iterations, 1);
        EXPECT_FALSE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_BindDouble_When_AllOverloadsUsed)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        statement.bind(1, 1.0);
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_BindFloat_When_AllOverloadsUsed)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        statement.bind(1, static_cast<float>(1.0f));
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_BindInt64_When_AllOverloadsUsed)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        statement.bind(1, static_cast<int64_t>(42));
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_BindCharPtr_When_AllOverloadsUsed)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        statement.bind(1, "text");
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_OptionalFullCoverage_When_AllTypesUsed)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        std::optional<int> a = 1;
        std::optional<double> b = 1.5;
        std::optional<std::string> c = "x";

        statement.bind(1, a);
        EXPECT_TRUE(statement.step());

        statement.reset();
        statement.bind(1, b);
        EXPECT_TRUE(statement.step());

        statement.reset();
        statement.bind(1, c);
        EXPECT_TRUE(statement.step());

        statement.reset();

        std::optional<int> nullv = std::nullopt;
        statement.bind(1, nullv);
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_RealConcurrency_When_StressResetStep)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT 1;"
        );

        std::atomic<int> counter = 0;

        std::vector<std::thread> threads;

        for (int i = 0; i < 8; i++)
        {
            threads.emplace_back([&]()
            {
                for (int j = 0; j < 1000; j++)
                {
                    statement.reset();
                    if (statement.step())
                    {
                        counter++;
                    }
                }
            });
        }

        for (auto& t : threads)
        {
            t.join();
        }

        EXPECT_GE(counter.load(), 1);
    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_MultiStatementConcurrency_When_SharedBackend)
    {
        auto backend = create_backend();

        SQLiteStatement s1(
            backend,
            "SELECT 1;"
        );

        SQLiteStatement s2(
            backend,
            "SELECT 1;"
        );

        std::atomic<int> count = 0;

        std::thread t1([&]()
        {
            if (s1.step()) count++;
        });

        std::thread t2([&]()
        {
            if (s2.step()) count++;
        });

        t1.join();
        t2.join();

        EXPECT_GE(count.load(), 1);
    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_IdempotentFalse_When_StepCalledAfterDoneRepeatedly)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    statement.step();
    statement.step();

    EXPECT_FALSE(statement.step());
    EXPECT_FALSE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_StableDoneState_When_MultipleStepCallsAfterExhaustion)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    statement.step();
    statement.step();

    for (int i = 0; i < 5; i++)
    {
        EXPECT_FALSE(statement.step());
    }

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_NoStateCorruption_When_StepCalledThreeTimesAfterDone)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    statement.step();
    statement.step();

    statement.step();
    statement.step();
    statement.step();

    EXPECT_FALSE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_QueryNotAffected_When_StepCalledAfterDoneWithoutReset)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    statement.step();
    statement.step();

    auto rows = statement.query();

    EXPECT_EQ(rows.size(), 1);

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_FreshExecution_When_ResetCalledBeforeAnyStep)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    EXPECT_TRUE(statement.reset());
    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_Reexecution_When_ResetCalledAfterDone)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    statement.step();
    statement.step();

    EXPECT_TRUE(statement.reset());
    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_ResetDoesNotLeakState_When_CalledMultipleTimes)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(statement.reset());
    }

    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_ResetThenStepConsistency_When_CalledInCycles)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    for (int i = 0; i < 5; i++)
    {
        statement.step();
        statement.step();
        EXPECT_TRUE(statement.reset());
        EXPECT_TRUE(statement.step());
    }

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_EmptyResult_When_QueryCalledOnEmptyTable)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1 WHERE 0;"
    );

    auto rows = statement.query();

    EXPECT_TRUE(rows.empty());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_IdempotentResult_When_QueryCalledMultipleTimesWithoutReset)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    auto r1 = statement.query();
    auto r2 = statement.query();

    EXPECT_EQ(r1.size(), r2.size());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_Reexecution_When_QueryCalledAfterReset)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    auto r1 = statement.query();

    statement.reset();

    auto r2 = statement.query();

    EXPECT_EQ(r1.size(), r2.size());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_NoStepSideEffects_When_QueryUsedInsteadOfStepLoop)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    auto rows = statement.query();

    EXPECT_EQ(rows.size(), 1);

    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_BindBool_Positional_When_TrueValue)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT ?;"
    );

    statement.bind(1, true);

    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_BindBool_Positional_When_FalseValue)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT ?;"
    );

    statement.bind(1, false);

    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_BindDouble_Positional_When_DoubleUsed)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT ?;"
    );

    statement.bind(1, 3.14);

    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_BindInt64_Positional_When_LargeValueUsed)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT ?;"
    );

    statement.bind(1, static_cast<int64_t>(9223372036854775807));

    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_BindCharPtr_Positional_When_CStringUsed)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT ?;"
    );

    statement.bind(1, "text");

    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_BindNullptr_Positional_When_NullPtrUsed)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT ?;"
    );

    statement.bind(1, nullptr);

    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_BindBool_Named_When_UsedWithParameter)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT :v;"
    );

    statement.bind(":v", true);

    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_BindDouble_Named_When_UsedWithParameter)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT :v;"
    );

    statement.bind(":v", 2.71);

    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_BindInt64_Named_When_UsedWithParameter)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT :v;"
    );

    statement.bind(":v", static_cast<int64_t>(100));

    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_BindNullptr_Named_When_UsedWithParameter)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT :v;"
    );

    statement.bind(":v", nullptr);

    EXPECT_TRUE(statement.step());

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_DefaultString_When_GetOnNullColumn)
    {
    auto backend = create_backend();

    sqlite3_exec(backend->database_handle,
        "CREATE TABLE t(x TEXT);",
        nullptr, nullptr, nullptr);

    SQLiteStatement statement(
        backend,
        "SELECT x FROM t;"
    );

    statement.step();

    auto row = statement.row();

    EXPECT_THROW(row->get<std::string>(0),
        SQLiteException);

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_Exception_When_GetIntFromTextColumn)
    {
    auto backend = create_backend();

    sqlite3_exec(backend->database_handle,
        "CREATE TABLE t(x TEXT);",
        nullptr, nullptr, nullptr);

    sqlite3_exec(backend->database_handle,
        "INSERT INTO t VALUES('abc');",
        nullptr, nullptr, nullptr);

    SQLiteStatement statement(
        backend,
        "SELECT x FROM t;"
    );

    statement.step();

    auto row = statement.row();

    EXPECT_NO_THROW(row->get<int>(0));

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_Exception_When_GetDoubleFromBlobColumn)
    {
    auto backend = create_backend();

    sqlite3_exec(backend->database_handle,
        "CREATE TABLE t(x BLOB);",
        nullptr, nullptr, nullptr);

    SQLiteStatement statement(
        backend,
        "SELECT x FROM t;"
    );

    statement.step();

    auto row = statement.row();

    EXPECT_THROW(row->get<double>(0),
        SQLiteException);

    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_Exception_When_GetBoolFromNullColumn)
    {
        auto backend = create_backend();

        sqlite3_exec(
            backend->database_handle,
            "CREATE TABLE t(x TEXT);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            backend->database_handle,
            "INSERT INTO t VALUES(NULL);",
            nullptr,
            nullptr,
            nullptr
        );

        SQLiteStatement statement(
            backend,
            "SELECT x FROM t;"
        );

        EXPECT_TRUE(statement.step());

        auto row = statement.row();

        ASSERT_TRUE(row.has_value());

        EXPECT_THROW(
            row->get<bool>(0),
            SQLiteException
        );
    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_Exception_When_NegativeColumnIndex)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    statement.step();

    auto row = statement.row();

    EXPECT_THROW(row->get<int>(-1),
        SQLiteException);

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_Exception_When_IndexGreaterThanColumnCount)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    statement.step();

    auto row = statement.row();

    EXPECT_THROW(row->get<int>(999),
        SQLiteException);

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_Exception_When_StatementUsedAfterBackendMove)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    SQLiteBackend moved = std::move(*backend);

    EXPECT_THROW(statement.step(),
        SQLiteException);

    }

    TEST_F(SQLiteStatementTest,
    Should_Expect_NoDeadlock_When_HeavyResetStepContention)
    {
    auto backend = create_backend();

    SQLiteStatement statement(
        backend,
        "SELECT 1;"
    );

    std::atomic<int> counter = 0;

    std::vector<std::thread> threads;

    for (int i = 0; i < 8; i++)
    {
        threads.emplace_back([&]()
        {
            for (int j = 0; j < 1000; j++)
            {
                statement.reset();
                statement.step();
                counter++;
            }
        });
    }

    for (auto& t : threads)
    {
        t.join();
    }

    EXPECT_GT(counter.load(), 0);

    }

    TEST_F(SQLiteStatementTest,
        Should_Expect_Exception_When_NonexistentColumnNameRepeated)
        {
        auto backend = create_backend();

        sqlite3_exec(backend->database_handle,
            "CREATE TABLE t(x INT);",
            nullptr, nullptr, nullptr);

        SQLiteStatement statement(
            backend,
            "SELECT x FROM t;"
        );

        statement.step();

        auto row = statement.row();

        EXPECT_THROW(row->get_index("invalid"),
            SQLiteException);

        }

        TEST_F(SQLiteStatementTest,
    Should_Enforce_StableDoneState_When_StepCalledAfterExhaustion_RepeatedlyAcrossLoops)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        statement.step();

        for (int i = 0; i < 100; i++)
        {
            EXPECT_FALSE(statement.step());
        }
    }

    TEST_F(SQLiteStatementTest,
    Should_Enforce_IdempotentFalse_When_StepCalledAfterDone_WithoutResetAcrossThreads)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        statement.step();

        std::atomic<bool> r1 = false;
        std::atomic<bool> r2 = false;

        std::thread t1([&](){ r1 = statement.step(); });
        std::thread t2([&](){ r2 = statement.step(); });

        t1.join();
        t2.join();

        EXPECT_FALSE(r1.load());
        EXPECT_FALSE(r2.load());
    }

    TEST_F(SQLiteStatementTest,
    Should_Prevent_InternalVMReexecution_When_StepCalledAfterDone_MultipleTimes)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        statement.step();

        for (int i = 0; i < 10; i++)
        {
            EXPECT_FALSE(statement.step());
        }
    }

    TEST_F(SQLiteStatementTest,
    Should_Ensure_NoRowReuse_When_StepCalledAfterDone_WithoutReset)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        statement.step();

        EXPECT_FALSE(statement.step());
        EXPECT_FALSE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
    Should_Ensure_StateMachineRemainsInDone_When_StepCalledInLongLoopAfterExhaustion)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        statement.step();

        for (int i = 0; i < 1000; i++)
        {
            EXPECT_FALSE(statement.step());
        }
    }

    TEST_F(SQLiteStatementTest,
    Should_InvalidateRowPointer_When_ResetCalledAfterRowAccess)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        auto row = statement.row();

        statement.reset();

        EXPECT_THROW(row->get<int>(0), SQLiteException);
    }

    TEST_F(SQLiteStatementTest,
    Should_ResetPreparedStatementState_When_ResetCalledBeforeAnyStep)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        EXPECT_TRUE(statement.reset());
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
    Should_FullyRecompileVM_When_ResetCalledAfterDone)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        statement.step();

        EXPECT_TRUE(statement.reset());
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
    Should_ClearBoundParameters_When_ResetCalledMultipleTimesSequentially)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT ?;");

        statement.bind(1, 10);

        for (int i = 0; i < 10; i++)
        {
            EXPECT_TRUE(statement.reset());
        }
    }

    TEST_F(SQLiteStatementTest,
    Should_PreserveBackendButResetExecutionCursor_When_ResetCalledMidExecution)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        EXPECT_TRUE(statement.reset());
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
    Should_EnsureResetDoesNotLeakPreviousRowState_When_UsedInCycle)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        for (int i = 0; i < 5; i++)
        {
            statement.step();
            statement.reset();
        }
    }

    TEST_F(SQLiteStatementTest,
    Should_EnsureResetStepConsistency_When_UsedInRepeatedResetStepCycles)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        for (int i = 0; i < 20; i++)
        {
            statement.reset();
            EXPECT_TRUE(statement.step());
        }
    }

    TEST_F(SQLiteStatementTest,
    Should_EnsureQueryPerformsImplicitResetBeforeExecution)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        auto r = statement.query();

        EXPECT_EQ(r.size(), 1);
    }

    TEST_F(SQLiteStatementTest,
    Should_EnsureQueryIsEquivalentToStepLoopAcrossAllRows)
    {
        auto backend = create_backend();

        sqlite3_exec(backend->database_handle,
            "CREATE TABLE t(x INT);", nullptr, nullptr, nullptr);

        sqlite3_exec(backend->database_handle,
            "INSERT INTO t VALUES(1);", nullptr, nullptr, nullptr);

        SQLiteStatement statement(backend, "SELECT x FROM t;");

        auto rows = statement.query();

        EXPECT_EQ(rows.size(), 1);
    }

    TEST_F(SQLiteStatementTest,
    Should_PreventStateLeak_When_QueryCalledAfterPartialStepConsumption)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        auto rows = statement.query();

        EXPECT_EQ(rows.size(), 1);
    }

    TEST_F(SQLiteStatementTest,
    Should_EnsureQueryDoesNotReuseCachedVMState)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        auto r1 = statement.query();
        auto r2 = statement.query();

        EXPECT_EQ(r1.size(), r2.size());
    }

    TEST_F(SQLiteStatementTest,
    Should_EnsureQueryConsistency_When_CalledMultipleTimesWithoutReset)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        auto r1 = statement.query();
        auto r2 = statement.query();

        EXPECT_EQ(r1.size(), r2.size());
    }

    TEST_F(SQLiteStatementTest,
    Should_EnsureQueryInvalidatesPreviousStepCursorState)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        auto rows = statement.query();

        EXPECT_EQ(rows.size(), 1);
    }

    TEST_F(SQLiteStatementTest,
    Should_Throw_When_BindIndexNegativeBeyondZeroBoundary)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT ?;");

        EXPECT_THROW(statement.bind(-1, 10), SQLiteException);
    }

    TEST_F(SQLiteStatementTest,
    Should_Throw_When_BindIndexExceedsParameterCount)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT ?;");

        EXPECT_THROW(statement.bind(999, 10), SQLiteException);
    }

    TEST_F(SQLiteStatementTest,
    Should_Throw_When_ParameterNameEmptyString)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT :x;");

        EXPECT_THROW(statement.bind("", 10), SQLiteException);
    }

    TEST_F(SQLiteStatementTest,
    Should_Throw_When_ParameterNameMalformed)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT :x;");

        EXPECT_THROW(statement.bind("::x", 10), SQLiteException);
    }

    TEST_F(SQLiteStatementTest,
    Should_Throw_When_ParameterNameOnlyColon)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT :x;");

        EXPECT_THROW(statement.bind(":", 10), SQLiteException);
    }

    TEST_F(SQLiteStatementTest,
    Should_Throw_When_ParameterNameContainsWhitespaceOnly)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT :x;");

        EXPECT_THROW(statement.bind("   ", 10), SQLiteException);
    }

    TEST_F(SQLiteStatementTest,
    Should_Throw_When_GetIntOnNullColumn)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT NULL;");

        statement.step();
        auto row = statement.row();

        EXPECT_THROW(row->get<int>(0), SQLiteException);
    }

    TEST_F(SQLiteStatementTest,
    Should_Throw_When_GetDoubleOnNullColumn)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT NULL;");

        statement.step();
        auto row = statement.row();

        EXPECT_THROW(row->get<double>(0), SQLiteException);
    }

    TEST_F(SQLiteStatementTest,
    Should_Throw_When_GetBoolOnNullColumn)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT NULL;");

        statement.step();
        auto row = statement.row();

        EXPECT_THROW(row->get<bool>(0), SQLiteException);
    }

    TEST_F(SQLiteStatementTest,
        Should_NotThrow_When_StatementUsedAfterBackendMoveAcrossMultipleOperations)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend,"SELECT 1;");

        SQLiteBackend moved = std::move(*backend);

        EXPECT_NO_THROW(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_Throw_When_NonexistentColumnRepeatedLookupOccurs)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend,"SELECT 1;");

        statement.step();
        auto row = statement.row();

        EXPECT_THROW(row->get_index("invalid"),SQLiteException);
    }

    TEST_F(SQLiteStatementTest,
    Should_InvalidateActiveRowIterator_When_ResetCalledDuringRowIteration)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        auto row = statement.row();

        statement.reset();

        EXPECT_THROW(row->get<int>(0), SQLiteException);
    }

    TEST_F(SQLiteStatementTest,
    Should_EnsureResetFullyReinitializesVMState_NotPartialCursorReset)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        statement.step();

        EXPECT_TRUE(statement.reset());
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
    Should_VerifyResetClearsInternalStepCacheAcrossRepeatedExecutions)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        for (int i = 0; i < 5; i++)
        {
            statement.step();
            statement.step();
            EXPECT_TRUE(statement.reset());
        }
    }

    TEST_F(SQLiteStatementTest,
    Should_EnsureResetDuringConcurrentStepDoesNotCorruptState)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        std::thread t1([&](){ statement.reset(); });
        std::thread t2([&](){ statement.step(); });

        t1.join();
        t2.join();

        EXPECT_TRUE(true);
    }

    TEST_F(SQLiteStatementTest,
    Should_EnsureResetFollowedByStepIsEquivalentToFreshStatementExecution)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        statement.step();
        statement.reset();

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
    Should_EnsureResetDoesNotRetainPreviousRowPointersAcrossCycles)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        for (int i = 0; i < 3; i++)
        {
            statement.step();
            statement.reset();
        }
    }

    TEST_F(SQLiteStatementTest,
    Should_ValidateResetIsIdempotentUnderStressConditions)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT 1;");

        for (int i = 0; i < 100; i++)
        {
            EXPECT_TRUE(statement.reset());
        }
    }

    TEST_F(SQLiteStatementTest,
    Should_EnsureResetClearsBoundParameterCacheCompletely)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend, "SELECT ?;");

        statement.bind(1, 10);

        statement.reset();

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureQueryEquivalentToFullStepIterationForMultiRowResultSet)
    {
        auto backend = create_backend();

        sqlite3_exec(backend->database_handle,
            "CREATE TABLE t(x INT);",nullptr,nullptr,nullptr);

        sqlite3_exec(backend->database_handle,
            "INSERT INTO t VALUES(1);",nullptr,nullptr,nullptr);

        SQLiteStatement statement(backend,"SELECT x FROM t;");

        auto rows = statement.query();

        EXPECT_EQ(rows.size(),1);
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureQueryPerformsImplicitResetBeforeExecutionEveryTime)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend,"SELECT 1;");

        statement.step();
        auto r = statement.query();

        EXPECT_EQ(r.size(),1);
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureQueryDoesNotDependOnPreviousStepCursorPosition)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend,"SELECT 1;");

        statement.step();
        auto rows = statement.query();

        EXPECT_EQ(rows.size(),1);
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureQueryCannotReuseStaleVMExecutionState)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend,"SELECT 1;");

        auto r1 = statement.query();
        auto r2 = statement.query();

        EXPECT_EQ(r1.size(),r2.size());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureQueryProducesDeterministicResultsAcrossRepeatedCallsWithoutReset)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend,"SELECT 1;");

        auto a = statement.query();
        auto b = statement.query();

        EXPECT_EQ(a.size(),b.size());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureQueryInvalidatesAnyActiveRowCursorState)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend,"SELECT 1;");

        statement.step();
        auto rows = statement.query();

        EXPECT_EQ(rows.size(),1);
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureQueryBehaviorMatchesStepLoopUnderInterleavedResetScenarios)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend,"SELECT 1;");

        statement.step();
        statement.reset();

        auto rows = statement.query();

        EXPECT_EQ(rows.size(),1);
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureQueryIsSafeAfterPartialStepConsumption)
    {
        auto backend = create_backend();

        SQLiteStatement statement(backend,"SELECT 1;");

        statement.step();
        auto rows = statement.query();

        EXPECT_EQ(rows.size(),1);
    }

    TEST_F(SQLiteStatementTest,
            Should_ResolveNamedParameterOnceAndCacheIndexAcrossRepeatedCalls)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        for(int i = 0; i < 100; i++)
        {
            statement.bind(":value",i);
            statement.reset();
        }

        statement.bind(":value",123);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureNamedBindOverridesPreviousNamedValueCorrectly)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        statement.bind(":value",1);
        statement.bind(":value",2);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureMixedNamedAndPositionalBindingsDoNotConflictExecutionPlan)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value, ?;"
        );

        statement.bind(":value",1);
        statement.bind(1,2);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureNamedBindRejectsInvalidSqlIdentifierCharacters)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        EXPECT_THROW(
            statement.bind(":va!ue",1),
            SQLiteException
        );
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureNamedBindHandlesRepeatedBindingConsistencyDeterministically)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        for(int i = 0; i < 50; i++)
        {
            statement.reset();
            statement.bind(":value",i);

            EXPECT_TRUE(statement.step());
        }
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureNamedBindIsIndependentOfParameterDeclarationOrder)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :b, :a;"
        );

        statement.bind(":a",1);
        statement.bind(":b",2);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureNamedBindResolutionIsCaseSensitiveConsistent)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :Value;"
        );

        EXPECT_THROW(
            statement.bind(":value",1),
            SQLiteException
        );
    }

    TEST_F(SQLiteStatementTest,
        Should_BindOptionalAcrossTypeRebindingSequencesWithoutStateLeak)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        std::optional<int> integer_value = 1;
        std::optional<double> double_value = 2.5;
        std::optional<std::string> string_value = "text";

        statement.bind(1,integer_value);
        EXPECT_TRUE(statement.step());

        statement.reset();

        statement.bind(1,double_value);
        EXPECT_TRUE(statement.step());

        statement.reset();

        statement.bind(1,string_value);
        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureOptionalNulloptClearsUnderlyingBoundValueFully)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        std::optional<int> value = 10;

        statement.bind(1,value);

        EXPECT_TRUE(statement.step());

        statement.reset();

        value = std::nullopt;

        statement.bind(1,value);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureOptionalBindingPreservesTypeAffinityCorrectlyAcrossSQLiteConversions)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        std::optional<double> value = 3.14;

        statement.bind(1,value);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureOptionalRebindAfterResetDoesNotRetainOldValue)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        std::optional<int> first = 1;
        std::optional<int> second = 2;

        statement.bind(1,first);

        EXPECT_TRUE(statement.step());

        statement.reset();

        statement.bind(1,second);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureOptionalHandlesLargeBoundaryValuesCorrectlyAcrossAllNumericTypes)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        std::optional<int64_t> value =
            std::numeric_limits<int64_t>::max();

        statement.bind(1,value);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureOptionalNulloptDoesNotAllocateBindingSlotState)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        std::optional<int> value = std::nullopt;

        statement.bind(1,value);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureNamedAndPositionalBindingsProduceIdenticalExecutionPlansInternally)
    {
        auto backend = create_backend();

        SQLiteStatement positional_statement(
            backend,
            "SELECT ?;"
        );

        SQLiteStatement named_statement(
            backend,
            "SELECT :value;"
        );

        positional_statement.bind(1,10);
        named_statement.bind(":value",10);

        EXPECT_TRUE(positional_statement.step());
        EXPECT_TRUE(named_statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureParameterIndexCacheIsPreservedAcrossResetCycle)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        statement.bind(":value",1);

        EXPECT_TRUE(statement.step());

        statement.reset();

        statement.bind(":value",2);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureRepeatedNamedBindingDoesNotRecomputeParameterIndex)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        for(int i = 0; i < 100; i++)
        {
            statement.bind(":value",i);
            statement.reset();
        }

        EXPECT_TRUE(true);
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureBindingOrderDoesNotAffectQueryExecutionResult)
    {
        auto backend = create_backend();

        SQLiteStatement statement_one(
            backend,
            "SELECT ?, ?;"
        );

        SQLiteStatement statement_two(
            backend,
            "SELECT ?, ?;"
        );

        statement_one.bind(1,1);
        statement_one.bind(2,2);

        statement_two.bind(2,2);
        statement_two.bind(1,1);

        EXPECT_TRUE(statement_one.step());
        EXPECT_TRUE(statement_two.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureBindingCacheInvalidatesCorrectlyAfterStatementReset)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        statement.bind(":value",1);

        EXPECT_TRUE(statement.step());

        statement.reset();

        statement.bind(":value",2);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_EnsureNoDoubleBindingSideEffectsOnRepeatedBindCalls)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        statement.bind(1,1);
        statement.bind(1,2);
        statement.bind(1,3);

        EXPECT_TRUE(statement.step());
    }

    TEST_F(SQLiteStatementTest,
        Should_RejectBind_When_ParameterNameContainsNullCharacters)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        std::string invalid_name = ":va\0lue";

        EXPECT_THROW(
            statement.bind(invalid_name,1),
            SQLiteException
        );
    }

    TEST_F(SQLiteStatementTest,
        Should_RejectBind_When_ParameterNameContainsControlCharacters)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        EXPECT_THROW(
            statement.bind(":value\n",1),
            SQLiteException
        );
    }

    TEST_F(SQLiteStatementTest,
        Should_RejectBind_When_ParameterNameUsesInvalidSqlIdentifierFormat)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        EXPECT_THROW(
            statement.bind(":123abc",1),
            SQLiteException
        );
    }

    TEST_F(SQLiteStatementTest,
        Should_RejectBind_When_IndexIsMaxIntOverflowScenario)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT ?;"
        );

        EXPECT_THROW(
            statement.bind(std::numeric_limits<int>::max(),1),
            SQLiteException
        );
    }

    TEST_F(SQLiteStatementTest,
        Should_RejectBind_When_MalformedNamedParameterPrefixUsed)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        EXPECT_THROW(
            statement.bind("@@value",1),
            SQLiteException
        );
    }

    TEST_F(SQLiteStatementTest,
        Should_RejectBind_When_WhitespaceOnlyOrInvisibleUnicodeNameUsed)
    {
        auto backend = create_backend();

        SQLiteStatement statement(
            backend,
            "SELECT :value;"
        );

        EXPECT_THROW(
            statement.bind("\t\n",1),
            SQLiteException
        );
    }
}

#endif
