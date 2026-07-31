#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteRow \
	)

#include "../includes/sqlite_row.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	TEST_F(SQLiteRowTest,
    Should_ReturnCount_Expect_Valid_When_QueryExecuted)
    {
        SQLiteRow row(statement_handle);
        EXPECT_EQ(row.get_column_count(), 3);
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnValue_Expect_Int_When_GetInt)
    {
        SQLiteRow row(statement_handle);
        EXPECT_EQ(row.get<int>(0), 1);
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnValue_Expect_String_When_GetString)
    {
        SQLiteRow row(statement_handle);
        EXPECT_EQ(row.get<std::string>(1), "abc");
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnValue_Expect_Bool_When_GetBool)
    {
        SQLiteRow row(statement_handle);
        EXPECT_TRUE(row.get<bool>(2));
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_NullColumnAccessed)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE null_table(id INTEGER);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO null_table VALUES(NULL);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* null_stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT * FROM null_table;",
            -1,
            &null_stmt,
            nullptr
        );

        sqlite3_step(null_stmt);

        SQLiteRow row(null_stmt);

        EXPECT_THROW(row.get<int>(0), SQLiteException);

        sqlite3_finalize(null_stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_MapColumn_Expect_Index_When_GetIndexCalled)
    {
        SQLiteRow row(statement_handle);
        EXPECT_EQ(row.get_index("value"), 1);
    }

    TEST_F(SQLiteRowTest,
    Should_RunAsync_Expect_Valid_When_MultipleThreadsAccess)
    {
        SQLiteRow row(statement_handle);

        auto worker = [&row]()
        {
            for (int index = 0; index < 1000; ++index)
            {
                volatile int value = row.get<int>(0);
                (void)value;
            }
        };

        std::thread thread_a(worker);
        std::thread thread_b(worker);

        thread_a.join();
        thread_b.join();

        SUCCEED();
    }

    TEST_F(SQLiteRowTest,
    Should_RunAsyncFuture_Expect_Valid_When_UsingStdAsync)
    {
        SQLiteRow row(statement_handle);

        auto future_task =
            std::async(std::launch::async,
            [&row]()
            {
                return row.get<int>(0);
            });

        EXPECT_EQ(future_task.get(), 1);
    }

    TEST_F(SQLiteRowTest,
    Should_Stress_Expect_Stable_When_RepeatedAccess)
    {
        SQLiteRow row(statement_handle);

        for (int index = 0; index < 5000; ++index)
        {
            EXPECT_EQ(row.get<int>(0), 1);
        }
    }

    TEST_F(SQLiteRowTest,
    Should_Perform_Expect_UnderLimit_When_HeavyRead)
    {
        SQLiteRow row(statement_handle);

        auto start = std::chrono::high_resolution_clock::now();

        for (int index = 0; index < 10000; ++index)
        {
            row.get<std::string>(1);
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start
            ).count();

        EXPECT_LT(duration, 2000);
    }
    
    TEST_P(SQLiteRowInvalidParameterizedTest,
        Should_Throw_Expect_Exception_When_InvalidColumnLookup)
    {
        SQLiteRowParameter parameter = GetParam();

        SQLiteRow row(statement_handle);

        EXPECT_THROW(
            row.get_index(parameter.column_name),
            SQLiteException
        );
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnValue_Expect_Double_When_GetDouble)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE double_table(value REAL);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO double_table VALUES(123.456);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* double_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM double_table;",
            -1,
            &double_statement,
            nullptr
        );

        sqlite3_step(double_statement);

        SQLiteRow row(double_statement);

        EXPECT_DOUBLE_EQ(
            row.get<double>(0),
            123.456
        );

        sqlite3_finalize(double_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnValue_Expect_Float_When_GetFloat)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE float_table(value REAL);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO float_table VALUES(55.25);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* float_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM float_table;",
            -1,
            &float_statement,
            nullptr
        );

        sqlite3_step(float_statement);

        SQLiteRow row(float_statement);

        EXPECT_FLOAT_EQ(
            row.get<float>(0),
            55.25f
        );

        sqlite3_finalize(float_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnValue_Expect_Int_When_GetIntByColumnName)
    {
        SQLiteRow row(statement_handle);

        EXPECT_EQ(
            row.get<int>("id"),
            1
        );
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnValue_Expect_String_When_GetStringByColumnName)
    {
        SQLiteRow row(statement_handle);

        EXPECT_EQ(
            row.get<std::string>("value"),
            "abc"
        );
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnCount_Expect_Cached_When_GetIndexRepeated)
    {
        SQLiteRow row(statement_handle);

        EXPECT_EQ(
            row.get_index("value"),
            1
        );

        EXPECT_EQ(
            row.column_name_to_index.size(),
            static_cast<std::size_t>(1)
        );

        EXPECT_EQ(
            row.get_index("value"),
            1
        );

        EXPECT_EQ(
            row.column_name_to_index.size(),
            static_cast<std::size_t>(1)
        );
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_ColumnNameMissing)
    {
        SQLiteRow row(statement_handle);

        EXPECT_THROW(
            row.get_index("missing"),
            SQLiteException
        );
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_EmptyColumnName)
    {
        SQLiteRow row(statement_handle);

        EXPECT_THROW(
            row.get_index(""),
            SQLiteException
        );
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_CaseMismatch)
    {
        SQLiteRow row(statement_handle);

        EXPECT_THROW(
            row.get_index("VALUE"),
            SQLiteException
        );
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnValue_Expect_ColumnName_When_GetColumnName)
    {
        SQLiteRow row(statement_handle);

        EXPECT_EQ(
            row.get_column_name(0),
            "id"
        );

        EXPECT_EQ(
            row.get_column_name(1),
            "value"
        );

        EXPECT_EQ(
            row.get_column_name(2),
            "flag"
        );
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnEmpty_Expect_String_When_NullString)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE null_string_table(value TEXT);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO null_string_table VALUES(NULL);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* null_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM null_string_table;",
            -1,
            &null_statement,
            nullptr
        );

        sqlite3_step(null_statement);

        SQLiteRow row(null_statement);

        EXPECT_EQ(
            row.get<std::string>(0),
            ""
        );

        sqlite3_finalize(null_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_NullBool)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE null_bool_table(value INTEGER);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO null_bool_table VALUES(NULL);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* null_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM null_bool_table;",
            -1,
            &null_statement,
            nullptr
        );

        sqlite3_step(null_statement);

        SQLiteRow row(null_statement);

        EXPECT_THROW(
            row.get<bool>(0),
            SQLiteException
        );

        sqlite3_finalize(null_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_RunAsync_Expect_Valid_When_UsingPromise)
    {
        SQLiteRow row(statement_handle);

        std::promise<int> promise;
        std::future<int> future =
            promise.get_future();

        std::thread worker(
            [&row, &promise]()
            {
                promise.set_value(
                    row.get<int>(0)
                );
            }
        );

        EXPECT_EQ(
            future.get(),
            1
        );

        worker.join();
    }

    TEST_F(SQLiteRowTest,
    Should_RunConcurrent_Expect_Stable_When_UsingAtomicCounter)
    {
        SQLiteRow row(statement_handle);

        std::atomic<int> success_count(0);

        auto worker =
            [&row, &success_count]()
            {
                for (int index = 0; index < 1000; ++index)
                {
                    if (row.get<int>(0) == 1)
                    {
                        ++success_count;
                    }
                }
            };

        std::thread thread_a(worker);
        std::thread thread_b(worker);

        thread_a.join();
        thread_b.join();

        EXPECT_EQ(
            success_count.load(),
            2000
        );
    }

    TEST_F(SQLiteRowTest,
    Should_RunConcurrent_Expect_Stable_When_UsingConditionVariable)
    {
        SQLiteRow row(statement_handle);

        std::mutex mutex;
        std::condition_variable condition_variable;
        bool is_ready = false;
        int result = 0;

        std::thread worker(
            [&]()
            {
                {
                    std::lock_guard<std::mutex> lock(mutex);

                    result =
                        row.get<int>(0);

                    is_ready = true;
                }

                condition_variable.notify_one();
            }
        );

        {
            std::unique_lock<std::mutex> lock(mutex);

            condition_variable.wait(
                lock,
                [&is_ready]()
                {
                    return is_ready;
                }
            );
        }

        EXPECT_EQ(result, 1);

        worker.join();
    }

    TEST_F(SQLiteRowTest,
    Should_Stress_Expect_Stable_When_RepeatedCacheLookup)
    {
        SQLiteRow row(statement_handle);

        for (int index = 0; index < 10000; ++index)
        {
            EXPECT_EQ(
                row.get_index("value"),
                1
            );
        }
    }

    TEST_P(SQLiteRowParameterizedTest,
    Should_Throw_Expect_Exception_When_InvalidColumnLookup)
    {
        SQLiteRowParameter parameter =
            GetParam();

        SQLiteRow row(statement_handle);

        EXPECT_NO_THROW(
            row.get_index(parameter.column_name)
        );
    }
    
    INSTANTIATE_TEST_CASE_P(
        SQLiteRowColumnCases,
        SQLiteRowParameterizedTest,
        ::testing::Values(
            SQLiteRowParameter{"id", 0},
            SQLiteRowParameter{"name", 1}
        )
    );

    INSTANTIATE_TEST_CASE_P(
        SQLiteRowInvalidColumnCases,
        SQLiteRowInvalidParameterizedTest,
        ::testing::Values(
            SQLiteRowParameter{"",-1},
            SQLiteRowParameter{"missing",-1},
            SQLiteRowParameter{"NAME",-1}
        )
    );

    TEST_F(SQLiteRowTest,
    Should_ReturnFalse_Expect_Bool_When_ValueZero)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE bool_false_table(value INTEGER);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO bool_false_table VALUES(0);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* bool_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM bool_false_table;",
            -1,
            &bool_statement,
            nullptr
        );

        sqlite3_step(bool_statement);

        SQLiteRow row(bool_statement);

        EXPECT_FALSE(
            row.get<bool>(0)
        );

        sqlite3_finalize(bool_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_EmptyString_When_StringEmpty)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE empty_string_table(value TEXT);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO empty_string_table VALUES('');",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* empty_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM empty_string_table;",
            -1,
            &empty_statement,
            nullptr
        );

        sqlite3_step(empty_statement);

        SQLiteRow row(empty_statement);

        EXPECT_EQ(
            row.get<std::string>(0),
            ""
        );

        sqlite3_finalize(empty_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_IndexNegative)
    {
        SQLiteRow row(statement_handle);

        EXPECT_THROW(
            row.get<int>(-1),
            SQLiteException
        );
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_IndexOutOfRange)
    {
        SQLiteRow row(statement_handle);

        EXPECT_THROW(
            row.get<int>(999),
            SQLiteException
        );
    }

    TEST_F(SQLiteRowTest,
    Should_RunConcurrent_Expect_Stable_When_CacheMutates)
    {
        SQLiteRow row(statement_handle);

        std::mutex mutex;
        std::vector<std::thread> thread_list;

        auto worker =
            [&row, &mutex]()
            {
                for (int index = 0; index < 1000; ++index)
                {
                    std::lock_guard<std::mutex> lock(mutex);

                    EXPECT_EQ(
                        row.get_index("value"),
                        1
                    );
                }
            };

        for (int index = 0; index < 4; ++index)
        {
            thread_list.emplace_back(worker);
        }

        for (std::thread& thread : thread_list)
        {
            thread.join();
        }

        EXPECT_EQ(
            row.column_name_to_index.size(),
            static_cast<std::size_t>(1)
        );
    }

    TEST_F(SQLiteRowTest,
    Should_Propagate_Expect_Exception_When_AsyncThrows)
    {
        SQLiteRow row(statement_handle);

        auto future =
            std::async(
                std::launch::async,
                [&row]()
                {
                    return row.get<int>(999);
                }
            );

        EXPECT_THROW(
            future.get(),
            SQLiteException
        );
    }

    TEST_F(SQLiteRowTest,
    Should_Stress_Expect_Stable_When_RepeatedFailures)
    {
        SQLiteRow row(statement_handle);

        for (int index = 0; index < 1000; ++index)
        {
            EXPECT_THROW(
                row.get_index("missing"),
                SQLiteException
            );
        }
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnValue_Expect_CachedIndex_When_CacheInserted)
    {
        SQLiteRow row(statement_handle);

        EXPECT_EQ(
            row.get_index("value"),
            1
        );

        EXPECT_EQ(
            row.column_name_to_index["value"],
            1
        );
    }

    TEST_F(SQLiteRowTest,
    Should_Perform_Expect_UnderLimit_When_RepeatedCacheLookup)
    {
        SQLiteRow row(statement_handle);

        row.get_index("value");

        auto start =
            std::chrono::high_resolution_clock::now();

        for (int index = 0; index < 10000; ++index)
        {
            row.get_index("value");
        }

        auto end =
            std::chrono::high_resolution_clock::now();

        auto duration =
            std::chrono::duration_cast<
                std::chrono::milliseconds>(
                    end - start
                ).count();

        EXPECT_LT(duration, 2000);
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnIndex_Expect_NoThrow_When_ColumnExists)
    {
        SQLiteRow row(statement_handle);

        EXPECT_NO_THROW(
            row.get_index("value")
        );

        EXPECT_EQ(
            row.get_index("value"),
            1
        );
    }

    TEST_P(SQLiteRowParameterizedTest,
    Should_ReturnIndex_Expect_Valid_When_ColumnLookup)
    {
        SQLiteRowParameter parameter =
            GetParam();

        SQLiteRow row(statement_handle);

        EXPECT_EQ(
            row.get_index(parameter.column_name),
            parameter.expected_index
        );
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnEmpty_Expect_String_When_ColumnNameInvalid)
    {
        SQLiteRow row(statement_handle);

        EXPECT_EQ(
            row.get_column_name(-1),
            ""
        );

        EXPECT_EQ(
            row.get_column_name(999),
            ""
        );
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_GetIntByMissingColumnName)
    {
        SQLiteRow row(statement_handle);

        EXPECT_THROW(
            row.get<int>("missing"),
            SQLiteException
        );
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_GetStringByMissingColumnName)
    {
        SQLiteRow row(statement_handle);

        EXPECT_THROW(
            row.get<std::string>("missing"),
            SQLiteException
        );
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnEmpty_Expect_String_When_GetStringByColumnNameNull)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE nullable_text_table(value TEXT);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO nullable_text_table VALUES(NULL);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* nullable_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM nullable_text_table;",
            -1,
            &nullable_statement,
            nullptr
        );

        sqlite3_step(nullable_statement);

        SQLiteRow row(nullable_statement);

        EXPECT_EQ(
            row.get<std::string>(0),
            ""
        );

        sqlite3_finalize(nullable_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_GetIntBeforeStep)
    {
        sqlite3_stmt* pending_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT * FROM test_table;",
            -1,
            &pending_statement,
            nullptr
        );

        SQLiteRow row(pending_statement);

        EXPECT_THROW(
            row.get<int>(0),
            SQLiteException
        );

        sqlite3_finalize(pending_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_GetIntAfterDone)
    {
        sqlite3_stmt* done_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT * FROM test_table;",
            -1,
            &done_statement,
            nullptr
        );

        sqlite3_step(done_statement);
        sqlite3_step(done_statement);

        SQLiteRow row(done_statement);

        EXPECT_THROW(
            row.get<int>(0),
            SQLiteException
        );

        sqlite3_finalize(done_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_EmptyResultSet)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE empty_table(id INTEGER);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* empty_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT * FROM empty_table;",
            -1,
            &empty_statement,
            nullptr
        );

        sqlite3_step(empty_statement);

        SQLiteRow row(empty_statement);

        EXPECT_THROW(
            row.get<int>(0),
            SQLiteException
        );

        sqlite3_finalize(empty_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_NotModifyCache_Expect_Stable_When_LookupFails)
    {
        SQLiteRow row(statement_handle);

        EXPECT_EQ(
            row.column_name_to_index.size(),
            static_cast<std::size_t>(0)
        );

        EXPECT_THROW(
            row.get_index("missing"),
            SQLiteException
        );

        EXPECT_EQ(
            row.column_name_to_index.size(),
            static_cast<std::size_t>(0)
        );
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnUnicode_Expect_String_When_ValueUnicode)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE unicode_table(value TEXT);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO unicode_table VALUES('こんにちは');",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* unicode_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM unicode_table;",
            -1,
            &unicode_statement,
            nullptr
        );

        sqlite3_step(unicode_statement);

        SQLiteRow row(unicode_statement);

        EXPECT_EQ(
            row.get<std::string>(0),
            "こんにちは"
        );

        sqlite3_finalize(unicode_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnValue_Expect_MaxInt_When_LargeInteger)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE integer_limit_table(value INTEGER);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO integer_limit_table VALUES(2147483647);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* integer_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM integer_limit_table;",
            -1,
            &integer_statement,
            nullptr
        );

        sqlite3_step(integer_statement);

        SQLiteRow row(integer_statement);

        EXPECT_EQ(
            row.get<int>(0),
            std::numeric_limits<int>::max()
        );

        sqlite3_finalize(integer_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnTrue_Expect_Bool_When_NegativeInteger)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE negative_bool_table(value INTEGER);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO negative_bool_table VALUES(-1);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* negative_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM negative_bool_table;",
            -1,
            &negative_statement,
            nullptr
        );

        sqlite3_step(negative_statement);

        SQLiteRow row(negative_statement);

        EXPECT_TRUE(
            row.get<bool>(0)
        );

        sqlite3_finalize(negative_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_RunConcurrent_Expect_Stable_When_DifferentColumnsAccessed)
    {
        SQLiteRow row(statement_handle);

        std::thread id_thread(
            [&row]()
            {
                for (int index = 0; index < 1000; ++index)
                {
                    EXPECT_EQ(
                        row.get_index("id"),
                        0
                    );
                }
            }
        );

        std::thread value_thread(
            [&row]()
            {
                for (int index = 0; index < 1000; ++index)
                {
                    EXPECT_EQ(
                        row.get_index("value"),
                        1
                    );
                }
            }
        );

        id_thread.join();
        value_thread.join();

        EXPECT_EQ(
            row.column_name_to_index.size(),
            static_cast<std::size_t>(2)
        );
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnValue_Expect_MinInt_When_SmallInteger)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE minimum_integer_table(value INTEGER);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO minimum_integer_table VALUES(-2147483648);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* minimum_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM minimum_integer_table;",
            -1,
            &minimum_statement,
            nullptr
        );

        sqlite3_step(minimum_statement);

        SQLiteRow row(minimum_statement);

        EXPECT_EQ(
            row.get<int>(0),
            std::numeric_limits<int>::min()
        );

        sqlite3_finalize(minimum_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_ReturnValue_Expect_LargeDouble_When_MaxDouble)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE maximum_double_table(value REAL);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO maximum_double_table "
            "VALUES(1.7976931348623157E+308);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* maximum_statement = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM maximum_double_table;",
            -1,
            &maximum_statement,
            nullptr
        );

        sqlite3_step(maximum_statement);

        SQLiteRow row(maximum_statement);

        EXPECT_DOUBLE_EQ(
            row.get<double>(0),
            std::numeric_limits<double>::max()
        );

        sqlite3_finalize(maximum_statement);
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_NullInt_When_ValueIsNull)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE null_int_table(value INTEGER);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO null_int_table VALUES(NULL);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM null_int_table;",
            -1,
            &stmt,
            nullptr
        );

        sqlite3_step(stmt);

        SQLiteRow row(stmt);

        EXPECT_THROW(row.get<int>(0), SQLiteException);

        sqlite3_finalize(stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_NullDouble_When_ValueIsNull)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE null_double_table(value REAL);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO null_double_table VALUES(NULL);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM null_double_table;",
            -1,
            &stmt,
            nullptr
        );

        sqlite3_step(stmt);

        SQLiteRow row(stmt);

        EXPECT_THROW(row.get<double>(0), SQLiteException);

        sqlite3_finalize(stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_NullBool_When_ValueIsNull)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE null_bool_table(value INTEGER);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO null_bool_table VALUES(NULL);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM null_bool_table;",
            -1,
            &stmt,
            nullptr
        );

        sqlite3_step(stmt);

        SQLiteRow row(stmt);

        EXPECT_THROW(row.get<bool>(0), SQLiteException);

        sqlite3_finalize(stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_ResetBehavior_When_StatementReset)
    {
        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT * FROM test_table;",
            -1,
            &stmt,
            nullptr
        );

        sqlite3_step(stmt);

        sqlite3_reset(stmt);
        sqlite3_step(stmt);

        SQLiteRow row(stmt);

        EXPECT_EQ(row.get<int>(0), 1);

        sqlite3_finalize(stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_ReuseAfterReset_When_MultipleSteps)
    {
        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT * FROM test_table;",
            -1,
            &stmt,
            nullptr
        );

        sqlite3_step(stmt);

        SQLiteRow row(stmt);

        EXPECT_EQ(row.get<int>(0), 1);

        sqlite3_reset(stmt);
        sqlite3_step(stmt);

        EXPECT_EQ(row.get<int>(0), 1);

        sqlite3_finalize(stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_EmptyResultSet_When_NoRowsReturned)
    {
        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT * FROM test_table WHERE id = 999;",
            -1,
            &stmt,
            nullptr
        );

        int step_result = sqlite3_step(stmt);

        EXPECT_NE(step_result, SQLITE_ROW);

        SQLiteRow row(stmt);

        EXPECT_THROW(row.get<int>(0), SQLiteException);

        sqlite3_finalize(stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_CacheStability_When_FailureThenSuccess)
    {
        SQLiteRow row(statement_handle);

        EXPECT_THROW(row.get_index("missing"), SQLiteException);

        EXPECT_EQ(row.column_name_to_index.size(), static_cast<std::size_t>(0));

        EXPECT_EQ(row.get_index("value"), 1);

        EXPECT_EQ(row.column_name_to_index.size(), static_cast<std::size_t>(1));
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_CorrectBoolConversion_When_VariousIntegers)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE bool_test(value INTEGER);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO bool_test VALUES(2);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM bool_test;",
            -1,
            &stmt,
            nullptr
        );

        sqlite3_step(stmt);

        SQLiteRow row(stmt);

        EXPECT_TRUE(row.get<bool>(0));

        sqlite3_finalize(stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_StringUnicodeAndEmptyMix)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE unicode_mix_table(value TEXT);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO unicode_mix_table VALUES('');",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM unicode_mix_table;",
            -1,
            &stmt,
            nullptr
        );

        sqlite3_step(stmt);

        SQLiteRow row(stmt);

        EXPECT_EQ(row.get<std::string>(0), "");

        sqlite3_finalize(stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_DoubleIntegerBoundary_When_LargePrecisionLoss)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE precision_table(value REAL);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO precision_table VALUES(1.0);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT value FROM precision_table;",
            -1,
            &stmt,
            nullptr
        );

        sqlite3_step(stmt);

        SQLiteRow row(stmt);

        EXPECT_DOUBLE_EQ(row.get<double>(0), 1.0);

        sqlite3_finalize(stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_NotBeTested_Expect_UndefinedBehavior_When_AccessAfterFinalize)
    {
        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT * FROM test_table;",
            -1,
            &stmt,
            nullptr
        );

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        EXPECT_TRUE(true);
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_NullStatementPassed)
    {
        SQLiteRow row(nullptr);

        EXPECT_THROW(
            row.get<int>(0),
            SQLiteException
        );
    }

    TEST_F(SQLiteRowTest,
    Should_Throw_Expect_Exception_When_InvalidSqlExecutionState)
    {
        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT * FROM test_table;",
            -1,
            &stmt,
            nullptr
        );

        SQLiteRow row(stmt);

        EXPECT_THROW(
            row.get<int>(0),
            SQLiteException
        );

        sqlite3_finalize(stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_Stress_Expect_Stable_When_ConcurrentCacheInsertion)
    {
        SQLiteRow row(statement_handle);

        auto worker = [&row]()
        {
            for (int index = 0; index < 2000; ++index)
            {
                try
                {
                    row.get_index("value");
                }
                catch (...) {}
            }
        };

        std::thread thread_a(worker);
        std::thread thread_b(worker);
        std::thread thread_c(worker);
        std::thread thread_d(worker);

        thread_a.join();
        thread_b.join();
        thread_c.join();
        thread_d.join();

        EXPECT_GE(
            row.column_name_to_index.size(),
            static_cast<std::size_t>(1)
        );
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_CorrectBehavior_When_MultipleRowIteration)
    {
        sqlite3_exec(
            database_handle,
            "CREATE TABLE multi_table(id INTEGER);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO multi_table VALUES(1);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_exec(
            database_handle,
            "INSERT INTO multi_table VALUES(2);",
            nullptr,
            nullptr,
            nullptr
        );

        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT * FROM multi_table ORDER BY id;",
            -1,
            &stmt,
            nullptr
        );

        EXPECT_EQ(sqlite3_step(stmt), SQLITE_ROW);

        SQLiteRow row_a(stmt);
        EXPECT_EQ(row_a.get<int>(0), 1);

        EXPECT_EQ(sqlite3_step(stmt), SQLITE_ROW);

        SQLiteRow row_b(stmt);
        EXPECT_EQ(row_b.get<int>(0), 2);

        sqlite3_finalize(stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_CorrectBehavior_When_ResetReuseCycle)
    {
        sqlite3_stmt* stmt = nullptr;

        sqlite3_prepare_v2(
            database_handle,
            "SELECT * FROM test_table;",
            -1,
            &stmt,
            nullptr
        );

        sqlite3_step(stmt);

        SQLiteRow row(stmt);
        EXPECT_EQ(row.get<int>(0), 1);

        sqlite3_reset(stmt);
        sqlite3_step(stmt);

        SQLiteRow row2(stmt);
        EXPECT_EQ(row2.get<int>(0), 1);

        sqlite3_finalize(stmt);
    }

    TEST_F(SQLiteRowTest,
    Should_Handle_Expect_CorrectBehavior_When_CachePersistsAcrossReset)
    {
        SQLiteRow row(statement_handle);

        row.get_index("value");

        sqlite3_reset(statement_handle);
        sqlite3_step(statement_handle);

        EXPECT_EQ(
            row.get_index("value"),
            1
        );

        EXPECT_EQ(
            row.column_name_to_index.size(),
            static_cast<std::size_t>(1)
        );
    }
}

#endif
