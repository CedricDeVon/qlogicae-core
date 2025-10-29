#include "pch.hpp"

#include "sqlite.hpp"

namespace QLogicaeCoreTest
{
    class SQLiteStatementTest : public testing::TestWithParam<std::string>
    {
    protected:
        void SetUp() override
        {
            database = std::make_unique<QLogicaeCore::SQLiteDatabase>(":memory:");
            QLogicaeCore::SQLiteStatement create = database->prepare("CREATE TABLE items (id INT, name TEXT);");
            create.step();
        }

        void TearDown() override
        {
            database.reset();
        }

        std::unique_ptr<QLogicaeCore::SQLiteDatabase> database;
    };

    class SQLiteStatementCoverageTest : public testing::Test
    {
    protected:
        void SetUp() override
        {
            database = std::make_unique<QLogicaeCore::SQLiteDatabase>(":memory:");
            database->prepare("CREATE TABLE items(id INT, name TEXT);").step();
        }

        std::unique_ptr<QLogicaeCore::SQLiteDatabase> database;
    };

    class SQLiteParameterizedSQLTest : public testing::TestWithParam<std::string>
    {
    protected:
        void SetUp() override
        {
            database = std::make_unique<QLogicaeCore::SQLiteDatabase>(":memory:");
            database->prepare("CREATE TABLE t(id INT);").step();
        }

        std::unique_ptr<QLogicaeCore::SQLiteDatabase> database;
    };

    TEST_F(SQLiteStatementTest, Should_Throw_When_BindingInvalidName)
    {
        QLogicaeCore::SQLiteStatement statement = database->prepare("SELECT 1;");
        EXPECT_THROW(statement.bind("?nonexistent", 5), QLogicaeCore::SQLiteException);
    }

    TEST_F(SQLiteStatementTest, Should_Throw_When_BindingAfterInvalidation)
    {
        QLogicaeCore::SQLiteStatement statement = database->prepare("INSERT INTO items(id) VALUES(?);");
        statement.step();
        statement.reset();
        statement.clear_bindings();
        EXPECT_NO_THROW(statement.bind(1, 5));
    }

    TEST_F(SQLiteStatementTest, Should_Throw_When_NameBindFails)
    {
        QLogicaeCore::SQLiteStatement statement = database->prepare("SELECT :value;");
        EXPECT_THROW(statement.bind(":missing", 1), QLogicaeCore::SQLiteException);
    }

    TEST_F(SQLiteStatementTest, Should_Bind_Nullptr_To_Statement)
    {
        QLogicaeCore::SQLiteStatement statement = database->prepare("INSERT INTO items(id, name) VALUES (?, ?);");
        EXPECT_NO_THROW(statement.bind(1, 10).bind(2, nullptr).step());
    }

    TEST_F(SQLiteStatementTest, Should_Return_Nullopt_When_StatementInvalid)
    {
        QLogicaeCore::SQLiteStatement statement = database->prepare("SELECT id FROM items;");
        EXPECT_FALSE(statement.step());
        EXPECT_FALSE(statement.row().has_value());
    }

    TEST_F(SQLiteStatementTest, Should_Handle_Optional_Bind_And_Get)
    {
        QLogicaeCore::SQLiteStatement insert = database->prepare("INSERT INTO items(id, name) VALUES (?, ?);");
        std::optional<std::string> empty_name = std::nullopt;
        insert.bind(1, 5).bind(2, empty_name).step();

        QLogicaeCore::SQLiteStatement select = database->prepare("SELECT name FROM items WHERE id = 5;");
        select.step();
        std::optional<QLogicaeCore::SQLiteRow> row = select.row();
        ASSERT_TRUE(row.has_value());
        std::optional<std::string> result = row->get_optional<std::string>(0);
        ASSERT_FALSE(result.has_value());
    }

    TEST_F(SQLiteStatementTest, Should_Work_Async_For_Query_And_Step)
    {
        QLogicaeCore::SQLiteStatement create_statement =
            database->prepare("CREATE TABLE data(id INT, name TEXT);");
        EXPECT_FALSE(create_statement.step());

        QLogicaeCore::SQLiteStatement insert_statement =
            database->prepare("INSERT INTO data VALUES(?, ?);");
        insert_statement.bind(1, 1);
        insert_statement.bind(2, "alpha");
        EXPECT_FALSE(insert_statement.step());

        QLogicaeCore::SQLiteStatement query_statement =
            database->prepare("SELECT id, name FROM data;");

        std::future<void> step_future = query_statement.step_async();
        EXPECT_EQ(step_future.wait_for(std::chrono::seconds(2)),
            std::future_status::ready);

        std::optional<QLogicaeCore::SQLiteRow> row = query_statement.row();
        ASSERT_TRUE(row.has_value());

        std::optional<int> id = row->get_optional<int>(0);
        std::optional<std::string> name = row->get_optional<std::string>(1);

        ASSERT_TRUE(id.has_value());
        ASSERT_TRUE(name.has_value());
        EXPECT_EQ(id.value(), 1);
        EXPECT_EQ(name.value(), "alpha");
    }

    TEST_F(SQLiteStatementTest, Should_Handle_Multithreaded_Execution)
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i)
        {
            threads.emplace_back([this, i]() {
                QLogicaeCore::SQLiteStatement insert = database->prepare("INSERT INTO items(id, name) VALUES (?, ?);");
                insert.bind(1, i).bind(2, std::to_string(i)).step();
                });
        }
        for (auto& thread : threads)
        {
            thread.join();
        }
        QLogicaeCore::SQLiteStatement query = database->prepare("SELECT COUNT(*) FROM items;");
        query.step();
        std::optional<QLogicaeCore::SQLiteRow> result = query.row();
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(result->get<int>(0), 10);
    }

    INSTANTIATE_TEST_CASE_P(
        StatementParameterizedTest,
        SQLiteStatementTest,
        testing::Values("", "SELECT"));

    TEST_F(SQLiteStatementCoverageTest, Should_Insert_ThousandRows_UnderTwoSeconds)
    {
        QLogicaeCore::SQLiteStatement insert =
            database->prepare("INSERT INTO items(id, name) VALUES(?, ?);");

        auto start = std::chrono::high_resolution_clock::now();

        for (int index = 0; index < 10000; ++index)
        {
            insert.reset();
            insert.clear_bindings();
            insert.bind(1, index).bind(2, std::to_string(index)).step();
        }

        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = stop - start;

        EXPECT_LT(elapsed.count(), 2.0);

        QLogicaeCore::SQLiteStatement query = database->prepare("SELECT COUNT(*) FROM items;");
        query.step();
        EXPECT_EQ(query.row()->get<int>(0), 10000);
    }

    TEST_F(SQLiteStatementCoverageTest, Should_FailAsync_When_InvalidQuery)
    {
        std::future<void> step_future = std::async(std::launch::async, [this]() {
            QLogicaeCore::SQLiteStatement bad_statement = database->prepare("INVALID SQL;");
            bad_statement.step();
            });

        EXPECT_THROW(step_future.get(), QLogicaeCore::SQLiteException);
    }

    TEST_F(SQLiteStatementCoverageTest, Should_InsertAndCountRowsSuccessfully)
    {
        QLogicaeCore::SQLiteStatement create =
            database->prepare("CREATE TABLE IF NOT EXISTS items(id INT, name TEXT);");
        ASSERT_NO_THROW(create.step());

        QLogicaeCore::SQLiteStatement insert =
            database->prepare("INSERT INTO items VALUES(?, ?);");

        ASSERT_FALSE(insert.bind(1, 1).bind(2, "a").step());

        QLogicaeCore::SQLiteStatement count =
            database->prepare("SELECT COUNT(*) FROM items;");
        ASSERT_TRUE(count.step());

        auto row = count.row();
        ASSERT_TRUE(row.has_value());

        auto result = row->get_optional<int>(0);
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value(), 1);
    }

    TEST_F(SQLiteStatementCoverageTest, Should_Handle_NullRow_Correctly)
    {
        QLogicaeCore::SQLiteStatement insert =
            database->prepare("INSERT INTO items(id, name) VALUES (?, NULL);");
        insert.bind(1, 42).step();

        QLogicaeCore::SQLiteStatement query = database->prepare("SELECT name FROM items WHERE id = 42;");
        query.step();
        std::optional<std::string> name = query.row()->get_optional<std::string>(0);

        EXPECT_FALSE(name.has_value());
    }

    TEST_P(SQLiteParameterizedSQLTest, Should_Handle_ParameterSyntaxForms)
    {
        std::string parameter = GetParam();
        std::string sql = "SELECT " + parameter + " AS value;";

        QLogicaeCore::SQLiteStatement stmt = database->prepare(sql);
        if (parameter[0] == '?')
            stmt.bind(1, 7);
        else
            stmt.bind(parameter, 7);

        EXPECT_NO_THROW(stmt.step());
        std::optional<QLogicaeCore::SQLiteRow> row = stmt.row();
        ASSERT_TRUE(row.has_value());
        EXPECT_EQ(row->get<int>(0), 7);
    }

    INSTANTIATE_TEST_CASE_P(
        SqliteValidParameterForms,
        SQLiteParameterizedSQLTest,
        testing::Values("?", ":value", "@param", "$key"));

    TEST(SQLiteParameterizedSQLTest, Should_Fail_On_EmptyParameterName)
    {
        std::unique_ptr<QLogicaeCore::SQLiteDatabase> database = std::make_unique<QLogicaeCore::SQLiteDatabase>(":memory:");

        QLogicaeCore::SQLiteStatement create = database->prepare("CREATE TABLE test(id INTEGER);");
        create.step();

        EXPECT_THROW({
            QLogicaeCore::SQLiteStatement stmt = database->prepare("INSERT INTO test(id) VALUES(" + std::string("") + ");");
            stmt.bind("", 42);
            stmt.step();
            }, QLogicaeCore::SQLiteException);
    }

    TEST_F(SQLiteStatementCoverageTest, Should_ResetAsync_And_ClearBindingsAsync)
    {
        QLogicaeCore::SQLiteStatement insert = database->prepare("INSERT INTO items(id, name) VALUES(?, ?);");

        insert.bind(1, 10).bind(2, "first").step();

        insert.reset_async().get();
        insert.clear_bindings_async().get();

        insert.bind(1, 11).bind(2, "second").step();

        QLogicaeCore::SQLiteStatement query = database->prepare("SELECT COUNT(*) FROM items;");
        query.step();

        EXPECT_EQ(query.row()->get<int>(0), 2);
    }

    TEST_F(SQLiteStatementCoverageTest, Should_GetBoolAndFloat_Correctly)
    {
        database->prepare("CREATE TABLE boolfloat(b BOOLEAN, f FLOAT);").step();

        QLogicaeCore::SQLiteStatement insert = database->prepare("INSERT INTO boolfloat VALUES(?, ?);");
        insert.bind(1, true).bind(2, 3.14f).step();

        QLogicaeCore::SQLiteStatement query = database->prepare("SELECT b, f FROM boolfloat;");
        query.step();

        auto row = query.row();
        ASSERT_TRUE(row.has_value());

        EXPECT_EQ(row->get<bool>(0), true);
        EXPECT_FLOAT_EQ(row->get<float>(1), 3.14f);
    }

    TEST_F(SQLiteStatementCoverageTest, Should_PrepareAsync_InMultipleThreads)
    {
        constexpr int kThreads = 5;
        std::vector<std::future<std::shared_ptr<QLogicaeCore::SQLiteStatement>>> futures;

        for (int i = 0; i < kThreads; ++i)
        {
            futures.push_back(database->prepare_async("INSERT INTO items(id, name) VALUES(?, ?);"));
        }

        for (int i = 0; i < kThreads; ++i)
        {
            auto statement = futures[i].get();
            statement->bind(1, i).bind(2, "t" + std::to_string(i)).step();
        }

        QLogicaeCore::SQLiteStatement query = database->prepare("SELECT COUNT(*) FROM items;");
        query.step();

        auto row = query.row();
        ASSERT_TRUE(row.has_value());
        EXPECT_EQ(row->get<int>(0), kThreads);
    }

    TEST_F(SQLiteStatementCoverageTest, Should_HandleOptionalBoolAndFloat)
    {
        database->prepare("CREATE TABLE flags(id INT, ok BOOLEAN, ratio FLOAT);").step();

        QLogicaeCore::SQLiteStatement insert = database->prepare("INSERT INTO flags(id, ok, ratio) VALUES(?, ?, ?);");

        std::optional<bool> is_true = true;
        std::optional<float> pi = 3.14f;
        insert.bind(1, 1).bind(2, is_true).bind(3, pi).step();

        QLogicaeCore::SQLiteStatement query = database->prepare("SELECT ok, ratio FROM flags WHERE id = 1;");
        query.step();

        auto row = query.row();
        ASSERT_TRUE(row.has_value());

        std::optional<bool> ok = row->get_optional<bool>(0);
        std::optional<float> ratio = row->get_optional<float>(1);

        ASSERT_TRUE(ok.has_value());
        ASSERT_TRUE(ratio.has_value());

        EXPECT_TRUE(ok.value());
        EXPECT_FLOAT_EQ(ratio.value(), 3.14f);
    }

    TEST_F(SQLiteStatementCoverageTest, Should_HandleOptionalBoolAndFloatNullopt)
    {
        database->prepare("CREATE TABLE flags(id INT, ok BOOLEAN, ratio FLOAT);").step();

        QLogicaeCore::SQLiteStatement insert = database->prepare("INSERT INTO flags(id, ok, ratio) VALUES(?, ?, ?);");

        std::optional<bool> ok = std::nullopt;
        std::optional<float> ratio = std::nullopt;

        insert.bind(1, 1).bind(2, ok).bind(3, ratio).step();

        QLogicaeCore::SQLiteStatement query = database->prepare("SELECT ok, ratio FROM flags WHERE id = 1;");
        query.step();

        auto row = query.row();
        ASSERT_TRUE(row.has_value());

        std::optional<bool> retrieved_ok = row->get_optional<bool>(0);
        std::optional<float> retrieved_ratio = row->get_optional<float>(1);

        EXPECT_FALSE(retrieved_ok.has_value());
        EXPECT_FALSE(retrieved_ratio.has_value());
    }

    TEST_F(SQLiteStatementCoverageTest, Should_CommitTransaction)
    {
        {
            QLogicaeCore::SQLiteTransaction txn(*database);
            QLogicaeCore::SQLiteStatement insert = database->prepare("INSERT INTO items(id, name) VALUES (?, ?);");
            insert.bind(1, 100).bind(2, "tx_commit").step();
            txn.commit();
        }

        QLogicaeCore::SQLiteStatement query = database->prepare("SELECT name FROM items WHERE id = 100;");
        query.step();
        auto row = query.row();
        ASSERT_TRUE(row.has_value());
        EXPECT_EQ(row->get<std::string>(0), "tx_commit");
    }

    TEST_F(SQLiteStatementCoverageTest, Should_RollbackOnDestruction)
    {
        {
            QLogicaeCore::SQLiteTransaction txn(*database);
            QLogicaeCore::SQLiteStatement insert = database->prepare("INSERT INTO items(id, name) VALUES (?, ?);");
            insert.bind(1, 101).bind(2, "tx_rollback").step();
        }

        QLogicaeCore::SQLiteStatement query = database->prepare("SELECT name FROM items WHERE id = 101;");
        EXPECT_FALSE(query.step());
    }

    TEST_F(SQLiteStatementCoverageTest, Should_GetValue_ByColumnName)
    {
        QLogicaeCore::SQLiteStatement insert = database->prepare("INSERT INTO items(id, name) VALUES (?, ?);");
        insert.bind(1, 200).bind(2, "column_name").step();

        QLogicaeCore::SQLiteStatement query = database->prepare("SELECT id, name FROM items WHERE id = 200;");
        query.step();
        auto row = query.row();
        ASSERT_TRUE(row.has_value());

        int id = row->get<int>("id");
        std::string name = row->get<std::string>("name");

        EXPECT_EQ(id, 200);
        EXPECT_EQ(name, "column_name");
    }

    TEST_F(SQLiteStatementCoverageTest, Should_FailAsync_Prepare_InvalidSQL)
    {
        auto future = database->prepare_async("MALFORMED SQL");
        EXPECT_THROW({
            auto stmt = future.get();
            }, QLogicaeCore::SQLiteException);
    }
}
