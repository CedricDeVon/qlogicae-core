#pragma once

#include "pch.h"

#include "sqlite.hpp"

namespace QLogicaeCoreTest
{

    class SQLiteTest : public testing::TestWithParam<std::string>
    {
    protected:
        std::unique_ptr<QLogicaeCore::Database> database;

        void SetUp() override
        {
            database = std::make_unique<QLogicaeCore::Database>(":memory:");
        }

        void TearDown() override
        {
            database.reset();
        }
    };

    TEST_P(SQLiteTest, Should_Prepare_ValidStatement_When_GivenValidSql)
    {
        QLogicaeCore::Statement statement =
            database->prepare(GetParam());
        EXPECT_TRUE(statement.is_valid());
    }

    TEST_P(SQLiteTest, Should_Fail_ToPrepare_When_GivenInvalidSql)
    {
        EXPECT_THROW({
            database->prepare("INVALID SQL;");
            }, QLogicaeCore::SQLiteException);
    }

    TEST(SQLiteDatabaseEdgeTest, Should_Fail_When_PreparingEmptySql)
    {
        QLogicaeCore::Database database(":memory:");
        EXPECT_THROW({
            database.prepare("");
            }, QLogicaeCore::SQLiteException);
    }

    /*
    TEST(SQLiteDatabaseThreadingTest, Should_Execute_SetPragma_InParallel)
    {
        QLogicaeCore::Database database(":memory:");
        std::thread thread_one([&]()
            {
                database.set_pragma("foreign_keys", "ON");
            });
        std::thread thread_two([&]()
            {
                database.set_pragma("journal_mode", "WAL");
            });
        thread_one.join();
        thread_two.join();
        SUCCEED();
    }
    */

    TEST(SQLiteDatabaseStressTest, Should_Handle_ThousandInserts_When_UsingPrepare)
    {
        QLogicaeCore::Database database(":memory:");
        database.prepare("CREATE TABLE numbers(id INT);").step();
        QLogicaeCore::Statement insert =
            database.prepare("INSERT INTO numbers(id) VALUES(?);");
        for (int index = 0; index < 10000; ++index)
        {
            insert.reset();
            insert.bind(1, index).step();
        }
        EXPECT_GT(database.total_changes(), 9999);
    }

    TEST(SQLiteDatabaseEdgeTest, Should_Throw_When_BindingWrongType)
    {
        QLogicaeCore::Database database(":memory:");
        database.prepare("CREATE TABLE test(val INTEGER);").step();
        QLogicaeCore::Statement insert =
            database.prepare("INSERT INTO test(val) VALUES(?);");
        EXPECT_THROW({
            insert.bind(1, "text").step();
            }, QLogicaeCore::SQLiteException);
    }

    /*
    
    TEST(SQLiteDatabaseAsyncTest, Should_ReturnAsyncStatement_When_Called)
    {
        QLogicaeCore::Database database(":memory:");
        std::future<std::shared_ptr<QLogicaeCore::Statement>> future =
            database.prepare_async("CREATE TABLE test(id INT);");
        EXPECT_EQ(future.wait_for(std::chrono::seconds(2)),
            std::future_status::ready);
    }

    TEST(SQLiteDatabaseAsyncTest, Should_GetPragma_When_UsingAsync)
    {
        QLogicaeCore::Database database(":memory:");
        database.set_pragma("foreign_keys", "ON");

        std::future<std::string> result =
            database.get_pragma_async("foreign_keys");

        ASSERT_EQ(result.wait_for(std::chrono::seconds(2)),
            std::future_status::ready);

        EXPECT_EQ(result.get(), "1");
    }

    TEST(SQLiteDatabaseAsyncTest, Should_SetPragma_When_UsingAsync)
    {
        QLogicaeCore::Database database(":memory:");
        std::future<void> result =
            database.set_pragma_async("foreign_keys", "ON");
        EXPECT_EQ(result.wait_for(std::chrono::seconds(2)),
            std::future_status::ready);
    }


    TEST(SQLiteDatabaseAsyncTest, Should_GetIndexListAsync_When_Valid)
    {
        QLogicaeCore::Database database(":memory:");
        std::future<std::vector<std::string>> future =
            database.index_list_async("nonexistent");
        EXPECT_EQ(future.wait_for(std::chrono::seconds(2)),
            std::future_status::ready);
    }

    TEST(SQLiteDatabaseAsyncTest, Should_GetTableInfoAsync_When_Valid)
    {
        QLogicaeCore::Database database(":memory:");
        std::future<std::vector<std::string>> future =
            database.table_info_async("nonexistent");
        EXPECT_EQ(future.wait_for(std::chrono::seconds(2)),
            std::future_status::ready);
    }


    */


    TEST(SQLiteDatabaseMigrationTest, Should_Migrate_When_Called)
    {
        QLogicaeCore::Database database(":memory:");
        database.set_pragma("user_version", "1");

        database.migrate_to(2, [](int from, int to)
            {
                EXPECT_EQ(from, 1);
                EXPECT_EQ(to, 2);
            });
        std::string version = database.get_pragma("user_version");
        EXPECT_EQ(version, "2");
    }

    TEST(SQLiteDatabaseMigrationTest, Should_MigrateAsync_When_Called)
    {
        QLogicaeCore::Database database(":memory:");
        database.set_pragma("user_version", "1");

        std::future<void> future = database.migrate_to_async(2, [](int from, int to)
            {
                EXPECT_EQ(from, 1);
                EXPECT_EQ(to, 2);
            });

        EXPECT_EQ(future.wait_for(std::chrono::seconds(2)),
            std::future_status::ready);
    }

    TEST(SQLiteDatabaseIntrospectTest, Should_ReturnEmptyIndexList_When_TableMissing)
    {
        QLogicaeCore::Database database(":memory:");
        std::vector<std::string> result =
            database.index_list("nonexistent");
        EXPECT_TRUE(result.empty());
    }

    TEST(SQLiteDatabaseIntrospectTest, Should_ReturnEmptyTableInfo_When_TableMissing)
    {
        QLogicaeCore::Database database(":memory:");
        std::vector<std::string> result =
            database.table_info("nonexistent");
        EXPECT_TRUE(result.empty());
    }

    INSTANTIATE_TEST_CASE_P(
        DatabaseValidSql,
        SQLiteTest,
        testing::Values(
            "CREATE TABLE test(id INT);",
            "CREATE TABLE foo(name TEXT);"
        )
    );



    class SQLiteStatementPoolTest : public testing::Test
    {
    protected:
        std::unique_ptr<QLogicaeCore::Database> database_instance;
        QLogicaeCore::StatementPool* statement_pool_pointer;

        void SetUp() override
        {
            database_instance = std::make_unique<QLogicaeCore::Database>(":memory:");
            statement_pool_pointer = &database_instance->pool();
            database_instance->prepare("CREATE TABLE t(id INT);").step();
        }
    };

    TEST_F(SQLiteStatementPoolTest,
        Should_Reuse_Statement_When_ReleasedToPool)
    {
        auto statement_one = statement_pool_pointer->get(
            "INSERT INTO t(id) VALUES (?);");
        statement_one.bind(1, 1).step();
        statement_pool_pointer->release(
            "INSERT INTO t(id) VALUES (?);", std::move(statement_one));

        auto statement_two = statement_pool_pointer->get(
            "INSERT INTO t(id) VALUES (?);");

        EXPECT_NO_THROW(statement_two.bind(1, 2).step());
    }

    TEST_F(SQLiteStatementPoolTest,
        Should_Separate_Statements_When_SQL_IsDifferent)
    {
        auto insert_statement = statement_pool_pointer->get(
            "INSERT INTO t(id) VALUES (?);");
        auto select_statement = statement_pool_pointer->get(
            "SELECT * FROM t;");
        insert_statement.bind(1, 7).step();

        statement_pool_pointer->release(
            "INSERT INTO t(id) VALUES (?);",
            std::move(insert_statement));
        statement_pool_pointer->release(
            "SELECT * FROM t;",
            std::move(select_statement));

        auto new_insert = statement_pool_pointer->get(
            "INSERT INTO t(id) VALUES (?);");
        auto new_select = statement_pool_pointer->get(
            "SELECT * FROM t;");

        EXPECT_NO_THROW(new_insert.bind(1, 8).step());
        EXPECT_NO_THROW(new_select.step());
    }

    TEST_F(SQLiteStatementPoolTest,
        Should_Handle_Parallel_Access_When_UsedFromMultipleThreads)
    {
        std::vector<std::thread> thread_group;

        for (int thread_index = 0; thread_index < 10; ++thread_index)
        {
            thread_group.emplace_back([this]()
                {
                    auto statement = statement_pool_pointer->get(
                        "INSERT INTO t(id) VALUES (?);");
                    statement.bind(1, 99).step();
                    statement_pool_pointer->release(
                        "INSERT INTO t(id) VALUES (?);",
                        std::move(statement));
                });
        }

        for (std::thread& thread_reference : thread_group)
        {
            thread_reference.join();
        }

        SUCCEED();
    }


    class SQLiteTransactionTest : public testing::Test
    {
    protected:
        std::unique_ptr<QLogicaeCore::Database> database_instance;

        void SetUp() override
        {
            database_instance = std::make_unique<QLogicaeCore::Database>(":memory:");
            database_instance->prepare("CREATE TABLE t(id INT);").step();
        }
    };

    TEST_F(SQLiteTransactionTest,
        Should_Rollback_When_TransactionNotCommitted)
    {
        {
            QLogicaeCore::Transaction transaction(*database_instance);
            database_instance->prepare("INSERT INTO t(id) VALUES(1);").step();
        }

        QLogicaeCore::Statement query =
            database_instance->prepare("SELECT COUNT(*) FROM t;");
        query.step();

        int count = query.row()->get<int>(0);
        EXPECT_EQ(count, 0);
    }

    TEST_F(SQLiteTransactionTest,
        Should_Commit_When_ExecuteCalled)
    {
        {
            QLogicaeCore::Transaction transaction(*database_instance);
            database_instance->prepare("INSERT INTO t(id) VALUES(1);").step();
            transaction.execute();
        }

        QLogicaeCore::Statement query =
            database_instance->prepare("SELECT COUNT(*) FROM t;");
        query.step();

        int count = query.row()->get<int>(0);
        EXPECT_EQ(count, 1);
    }


    class SQLiteRowEdgeTest : public testing::Test
    {
    protected:
        std::unique_ptr<QLogicaeCore::Database> database_instance;

        void SetUp() override
        {
            database_instance = std::make_unique<QLogicaeCore::Database>(":memory:");
            database_instance->prepare("CREATE TABLE x(val INT);").step();
            QLogicaeCore::Statement insert =
                database_instance->prepare("INSERT INTO x(val) VALUES(5);");
            insert.step();
        }
    };

    TEST_F(SQLiteRowEdgeTest,
        Should_Throw_When_AccessingInvalidColumnIndex)
    {
        QLogicaeCore::Statement stmt =
            database_instance->prepare("SELECT * FROM x;");
        stmt.step();

        auto row = stmt.row();
        EXPECT_THROW({
            row->get<int>(99);
            }, std::exception);
    }

    TEST_F(SQLiteRowEdgeTest,
        Should_Throw_When_AccessingInvalidColumnName)
    {
        QLogicaeCore::Statement stmt =
            database_instance->prepare("SELECT * FROM x;");
        stmt.step();

        auto row = stmt.row();
        EXPECT_THROW({
            row->get<int>("does_not_exist");
            }, std::exception);
    }


    class SQLiteStatementErrorTest : public testing::Test
    {
    protected:
        std::unique_ptr<QLogicaeCore::Database> database_instance;

        void SetUp() override
        {
            database_instance = std::make_unique<QLogicaeCore::Database>(":memory:");
        }
    };

    TEST_F(SQLiteStatementErrorTest,
        Should_FailReset_When_InvalidStatement)
    {
        QLogicaeCore::Statement statement =
            database_instance->prepare("CREATE TABLE z(id INT);");

        auto released = statement.release_internal_statement();

        EXPECT_THROW({
            statement.reset();
            }, QLogicaeCore::SQLiteException);
    }

    class SQLiteRowOptionalTest : public testing::Test
    {
    protected:
        std::unique_ptr<QLogicaeCore::Database> database_instance;

        void SetUp() override
        {
            database_instance = std::make_unique<QLogicaeCore::Database>(":memory:");
            database_instance->prepare("CREATE TABLE nulls(v INT);").step();
            database_instance->prepare("INSERT INTO nulls(v) VALUES(NULL);").step();
        }
    };

    TEST_F(SQLiteRowOptionalTest,
        Should_OptionalReturnNull_When_NullField)
    {
        QLogicaeCore::Statement stmt =
            database_instance->prepare("SELECT * FROM nulls;");
        stmt.step();

        auto row = stmt.row();
        std::optional<int> value = row->get_optional<int>(0);

        EXPECT_FALSE(value.has_value());
    }


    class SQLiteStatementClearTest : public testing::Test
    {
    protected:
        std::unique_ptr<QLogicaeCore::Database> database_instance;

        void SetUp() override
        {
            database_instance = std::make_unique<QLogicaeCore::Database>(":memory:");
            database_instance->prepare("CREATE TABLE a(id INT, name TEXT);").step();
        }
    };

    TEST_F(SQLiteStatementClearTest,
        Should_ClearBindings_When_Called)
    {
        QLogicaeCore::Statement stmt =
            database_instance->prepare("INSERT INTO a(id, name) VALUES(?, ?);");

        stmt.bind(1, 42);
        stmt.bind(2, "before");
        stmt.clear_bindings();

        EXPECT_NO_THROW(stmt.bind(1, 7).bind(2, "after").step());

        QLogicaeCore::Statement select =
            database_instance->prepare("SELECT id, name FROM a;");
        select.step();

        auto row = select.row();
        EXPECT_EQ(row->get<int>(0), 7);
        EXPECT_EQ(row->get<std::string>(1), "after");
    }


    class SQLiteRowMultiTypeTest : public testing::Test
    {
    protected:
        std::unique_ptr<QLogicaeCore::Database> database_instance;

        void SetUp() override
        {
            database_instance = std::make_unique<QLogicaeCore::Database>(":memory:");
            database_instance->prepare(
                "CREATE TABLE types(i INT, d REAL, b INT, t TEXT);").step();

            QLogicaeCore::Statement insert =
                database_instance->prepare("INSERT INTO types VALUES(1, 3.14, 1, 'abc');");
            insert.step();
        }
    };

    TEST_F(SQLiteRowMultiTypeTest,
        Should_ReturnCorrectValue_ForMultipleTypes)
    {
        QLogicaeCore::Statement stmt =
            database_instance->prepare("SELECT * FROM types;");
        stmt.step();

        auto row = stmt.row();
        EXPECT_EQ(row->get<int>(0), 1);
        EXPECT_DOUBLE_EQ(row->get<double>(1), 3.14);
        EXPECT_EQ(row->get<bool>(2), true);
        EXPECT_EQ(row->get<std::string>(3), "abc");
    }


    class SQLiteRowIteratorTest : public testing::Test
    {
    protected:
        std::unique_ptr<QLogicaeCore::Database> database_instance;

        void SetUp() override
        {
            database_instance = std::make_unique<QLogicaeCore::Database>(":memory:");
            database_instance->prepare("CREATE TABLE r(id INT);").step();
            for (int index = 0; index < 3; ++index)
            {
                auto insert = database_instance->prepare(
                    "INSERT INTO r(id) VALUES(?);");
                insert.bind(1, index).step();
            }
        }
    };

    TEST_F(SQLiteRowIteratorTest,
        Should_IterateAllRows_When_UsingRangeLoop)
    {
        auto query = database_instance->prepare("SELECT id FROM r;");
        int count = 0;

        for (const auto& row : query)
        {
            EXPECT_EQ(row.get<int>(0), count);
            count++;
        }

        EXPECT_EQ(count, 3);
    }


    class SQLiteStatementNamedBindTest : public testing::Test
    {
    protected:
        std::unique_ptr<QLogicaeCore::Database> database_instance;

        void SetUp() override
        {
            database_instance = std::make_unique<QLogicaeCore::Database>(":memory:");
            database_instance->prepare("CREATE TABLE n(val TEXT);").step();
        }
    };

    TEST_F(SQLiteStatementNamedBindTest,
        Should_BindNamedParameter_When_ValidName)
    {
        auto stmt = database_instance->prepare(
            "INSERT INTO n(val) VALUES(:val);");

        stmt.bind(":val", "xvalue").step();

        auto select = database_instance->prepare("SELECT val FROM n;");
        select.step();

        auto row = select.row();
        EXPECT_EQ(row->get<std::string>(0), "xvalue");
    }


    class SQLiteRowCacheTest : public testing::Test
    {
    protected:
        std::unique_ptr<QLogicaeCore::Database> database_instance;

        void SetUp() override
        {
            database_instance = std::make_unique<QLogicaeCore::Database>(":memory:");
            database_instance->prepare("CREATE TABLE test(id INT, name TEXT);").step();
            auto stmt = database_instance->prepare("INSERT INTO test VALUES(1, 'bob');");
            stmt.step();
        }
    };

    TEST_F(SQLiteRowCacheTest,
        Should_UseNameCache_When_GettingByNameTwice)
    {
        auto stmt = database_instance->prepare("SELECT id, name FROM test;");
        stmt.step();
        auto row = stmt.row();

        int first = row->get<int>("id");
        int second = row->get<int>("id");

        EXPECT_EQ(first, second);
    }


    class SQLiteOptionalBindTest : public testing::Test
    {
    protected:
        std::unique_ptr<QLogicaeCore::Database> database_instance;

        void SetUp() override
        {
            database_instance = std::make_unique<QLogicaeCore::Database>(":memory:");
            database_instance->prepare("CREATE TABLE optionals(x TEXT);").step();
        }
    };

    TEST_F(SQLiteOptionalBindTest,
        Should_BindOptionalNull_When_ValueMissing)
    {
        std::optional<std::string> none = std::nullopt;
        auto insert = database_instance->prepare(
            "INSERT INTO optionals(x) VALUES(?);");

        insert.bind<std::string>(1, none).step();

        auto query = database_instance->prepare("SELECT x FROM optionals;");
        query.step();
        auto row = query.row();

        EXPECT_FALSE(row->get_optional<std::string>(0).has_value());
    }

    TEST_F(SQLiteTransactionTest,
        Should_Rollback_When_NotCommitted)
    {
        {
            QLogicaeCore::Transaction transaction(*database_instance);
            auto insert = database_instance->prepare(
                "INSERT INTO tx(val) VALUES(123);");
            insert.step();
        }

        auto query = database_instance->prepare("SELECT COUNT(*) FROM tx;");
        query.step();
        int count = query.row()->get<int>(0);

        EXPECT_EQ(count, 0);
    }

    TEST(SQLiteRowInternalTest, Should_GetValidIndex_When_ColumnExists)
    {
        QLogicaeCore::Database db(":memory:");
        db.prepare("CREATE TABLE t(a INT, b TEXT);").step();
        db.prepare("INSERT INTO t(a, b) VALUES(42, 'x');").step();

        QLogicaeCore::Statement stmt = db.prepare("SELECT * FROM t;");
        stmt.step();
        auto row = stmt.row();
        EXPECT_NO_THROW({
            int idx = row->get<int>("a");
            EXPECT_EQ(idx, 42);
            });
    }

    TEST(SQLiteRowInternalTest, Should_Throw_When_ColumnDoesNotExist)
    {
        QLogicaeCore::Database db(":memory:");
        db.prepare("CREATE TABLE t(a INT);").step();
        db.prepare("INSERT INTO t(a) VALUES(1);").step();

        QLogicaeCore::Statement stmt = db.prepare("SELECT * FROM t;");
        stmt.step();
        auto row = stmt.row();

        EXPECT_THROW({
            row->get<int>("nonexistent");
            }, std::exception);
    }

    TEST(SQLiteTemplateTest, Should_CompileAndBindAllSupportedTypes)
    {
        QLogicaeCore::Database db(":memory:");
        db.prepare("CREATE TABLE t(i INT, d REAL, b INT, s TEXT);").step();

        auto stmt = db.prepare("INSERT INTO t VALUES(?, ?, ?, ?);");
        stmt.bind(1, 123);
        stmt.bind(2, 3.14f);
        stmt.bind(3, true);
        stmt.bind(4, std::string("abc"));
        stmt.step();

        auto select = db.prepare("SELECT * FROM t;");
        select.step();
        auto row = select.row();

        EXPECT_EQ(row->get<int>(0), 123);
        EXPECT_FLOAT_EQ(row->get<float>(1), 3.14f);
        EXPECT_EQ(row->get<bool>(2), true);
        EXPECT_EQ(row->get<std::string>(3), "abc");
    }

    TEST(SQLiteMemoryCleanupTest, Should_DestructDatabaseWithoutLeak)
    {
        {
            QLogicaeCore::Database db(":memory:");
            db.prepare("CREATE TABLE cleanup_test(val INT);").step();
        }

        SUCCEED();
    }

    TEST(SQLiteDatabaseErrorTest, Should_Throw_When_OpeningInvalidFile)
    {
        EXPECT_THROW({
            QLogicaeCore::Database db("?:\\invalid\\::db"); 
            }, QLogicaeCore::SQLiteException);
    }

    TEST(SQLiteBlobBindTest, Should_BindAndRetrieveBlob_When_UsingVectorByte)
    {
        QLogicaeCore::Database db(":memory:");
        db.prepare("CREATE TABLE blobs(data BLOB);").step();

        std::vector<std::byte> input_blob = {
            std::byte{0x01}, std::byte{0x02}, std::byte{0x03}
        };

        auto insert = db.prepare("INSERT INTO blobs(data) VALUES(?);");
        insert.bind_blob(1, input_blob.data(), static_cast<int>(input_blob.size())).step();

        auto select = db.prepare("SELECT data FROM blobs;");
        select.step();
        auto row = select.row();
        auto result = row->get<std::vector<std::byte>>(0);

        EXPECT_EQ(result, input_blob);
    }

    TEST(SQLiteBulkExecuteTest, Should_InsertMultipleRows_When_UsingExecuteMany)
    {
        QLogicaeCore::Database db(":memory:");
        db.prepare("CREATE TABLE bulk(id INT, val TEXT);").step();

        auto stmt = db.prepare("INSERT INTO bulk VALUES(?, ?);");
        std::vector<std::tuple<int, std::string>> rows = {
            {1, "one"}, {2, "two"}, {3, "three"}
        };

        stmt.execute_many(rows);

        auto query = db.prepare("SELECT COUNT(*) FROM bulk;");
        query.step();
        auto row = query.row();

        EXPECT_EQ(row->get<int>(0), 3);
    }

    TEST(SQLiteAsyncExceptionTest, Should_Throw_When_PreparingInvalidAsync)
    {
        QLogicaeCore::Database db(":memory:");
        std::future<std::shared_ptr<QLogicaeCore::Statement>> future =
            db.prepare_async("THIS IS NOT SQL");

        EXPECT_THROW({
            auto s = future.get();
            }, QLogicaeCore::SQLiteException);
    }

    TEST(SQLitePragmaErrorTest, Should_Throw_When_PragmaFails)
    {
        QLogicaeCore::Database db(":memory:");
        EXPECT_THROW({
            db.set_pragma("invalid_pragma", "123");
            }, QLogicaeCore::SQLiteException);
    }

    TEST(SQLiteAsyncErrorFlowTest, Should_Throw_When_ResetAsyncInvalid)
    {
        QLogicaeCore::Database db(":memory:");
        auto stmt = db.prepare("CREATE TABLE async_err(x INT);");
        auto raw = stmt.release_internal_statement();
        EXPECT_THROW(stmt.reset_async().get(), QLogicaeCore::SQLiteException);
    }

    TEST(SQLiteAsyncErrorFlowTest, Should_Throw_When_ClearBindingsAsyncInvalid)
    {
        QLogicaeCore::Database db(":memory:");
        auto stmt = db.prepare("CREATE TABLE clear_err(x INT);");
        auto raw = stmt.release_internal_statement();
        EXPECT_THROW(stmt.clear_bindings_async().get(), QLogicaeCore::SQLiteException);
    }

    TEST(SQLiteAsyncErrorFlowTest, Should_Throw_When_QueryAsyncInvalid)
    {
        QLogicaeCore::Database db(":memory:");
        auto stmt = db.prepare("CREATE TABLE query_err(x INT);");
        auto raw = stmt.release_internal_statement();
        EXPECT_THROW(stmt.query_async().get(), QLogicaeCore::SQLiteException);
    }

    TEST(SQLiteIteratorTest, Should_NotIterate_When_ResultEmpty)
    {
        QLogicaeCore::Database db(":memory:");
        db.prepare("CREATE TABLE empty(id INT);").step();

        auto stmt = db.prepare("SELECT * FROM empty;");
        int count = 0;

        for (const auto& row : stmt)
        {
            count++;
        }

        EXPECT_EQ(count, 0);
    }
}
