#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteRow \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class SQLiteRowTest : public ::testing::Test
    {
    public:
        sqlite3* database_handle;
        sqlite3_stmt* statement_handle;

        void SetUp()
        {
            sqlite3_open(":memory:", &database_handle);

            sqlite3_exec(
                database_handle,
                "CREATE TABLE test_table("
                "id INTEGER, value TEXT, flag INTEGER);",
                nullptr,
                nullptr,
                nullptr
            );

            sqlite3_exec(
                database_handle,
                "INSERT INTO test_table VALUES(1,'abc',1);",
                nullptr,
                nullptr,
                nullptr
            );

            sqlite3_prepare_v2(
                database_handle,
                "SELECT * FROM test_table;",
                -1,
                &statement_handle,
                nullptr
            );

            sqlite3_step(statement_handle);
        }

        void TearDown()
        {
            sqlite3_finalize(statement_handle);
            sqlite3_close(database_handle);
        }
    };
    
    struct SQLiteRowParameter
    {
        std::string column_name;
        int expected_index;
    };

    class SQLiteRowParameterizedTest :
        public ::testing::TestWithParam<SQLiteRowParameter>
    {
    public:
        sqlite3* database_handle;
        sqlite3_stmt* statement_handle;

        void SetUp()
        {
            sqlite3_open(":memory:", &database_handle);

            sqlite3_exec(
                database_handle,
                "CREATE TABLE test_table(id INTEGER, name TEXT);",
                nullptr,
                nullptr,
                nullptr
            );

            sqlite3_exec(
                database_handle,
                "INSERT INTO test_table VALUES(1,'x');",
                nullptr,
                nullptr,
                nullptr
            );

            sqlite3_prepare_v2(
                database_handle,
                "SELECT * FROM test_table;",
                -1,
                &statement_handle,
                nullptr
            );

            sqlite3_step(statement_handle);
        }

        void TearDown()
        {
            sqlite3_finalize(statement_handle);
            sqlite3_close(database_handle);
        }
    };

    class SQLiteRowInvalidParameterizedTest :
        public ::testing::TestWithParam<SQLiteRowParameter>
    {
    public:
        sqlite3* database_handle;
        sqlite3_stmt* statement_handle;

        void SetUp()
        {
            sqlite3_open(":memory:", &database_handle);

            sqlite3_exec(
                database_handle,
                "CREATE TABLE test_table(id INTEGER, name TEXT);",
                nullptr,
                nullptr,
                nullptr
            );

            sqlite3_exec(
                database_handle,
                "INSERT INTO test_table VALUES(1,'x');",
                nullptr,
                nullptr,
                nullptr
            );

            sqlite3_prepare_v2(
                database_handle,
                "SELECT * FROM test_table;",
                -1,
                &statement_handle,
                nullptr
            );

            sqlite3_step(statement_handle);
        }

        void TearDown()
        {
            sqlite3_finalize(statement_handle);
            sqlite3_close(database_handle);
        }
    };
}

#endif