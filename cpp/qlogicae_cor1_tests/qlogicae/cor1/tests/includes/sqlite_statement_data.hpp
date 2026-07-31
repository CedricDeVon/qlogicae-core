#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteStatementData \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class SQLiteStatementDataTest : public ::testing::Test
    {
    protected:
        sqlite3* database_handle;

        void SetUp()
        {
            sqlite3_open(":memory:", &database_handle);
        }

        void TearDown()
        {
            sqlite3_close(database_handle);
        }

        sqlite3_stmt* prepare_statement(
            const std::string& sql)
        {
            sqlite3_stmt* statement = nullptr;

            sqlite3_prepare_v2(
                database_handle,
                sql.c_str(),
                -1,
                &statement,
                nullptr
            );

            return statement;
        }
    };

    class SQLiteStatementDataParamTest:
        public SQLiteStatementDataTest,
        public ::testing::WithParamInterface<std::string>
    {
    };

    class SQLiteStatementDataThreadTest:
        public SQLiteStatementDataTest
    {
    protected:
        std::mutex mutex;
        std::condition_variable condition_variable;
        bool ready = false;
    };
}

#endif