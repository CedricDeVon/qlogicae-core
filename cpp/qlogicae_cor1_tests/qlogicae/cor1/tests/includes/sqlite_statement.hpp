#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteStatement \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class SQLiteStatementTest : public ::testing::Test
    {
    protected:
        std::shared_ptr<SQLiteBackend>
            create_backend()
        {
            sqlite3* database_handle = nullptr;

            int open_result = sqlite3_open(":memory:",
                &database_handle);

            EXPECT_EQ(open_result, SQLITE_OK);

            return std::make_shared<
                SQLiteBackend>(
                    database_handle);
        }

        void setup_table(
            SQLiteStatement&
                statement
        )
        {
            statement.bind(1, 1);
        }
    };
    
    class SQLiteStatementParameterTest :
        public ::testing::TestWithParam<int>
    {
    protected:
        std::shared_ptr<SQLiteBackend>
        create_backend()
        {
            sqlite3* database_handle = nullptr;

            int open_result = sqlite3_open(":memory:",
                &database_handle);

            EXPECT_EQ(open_result, SQLITE_OK);

            return std::make_shared<SQLiteBackend>(
                database_handle);
        }
    };
    
    class SQLiteStatementPerformanceTest :
        public ::testing::Test
    {
    protected:
        std::shared_ptr<SQLiteBackend>
            create_backend()
        {
            sqlite3* database_handle = nullptr;

            int open_result = sqlite3_open(":memory:",
                &database_handle);

            EXPECT_EQ(open_result,SQLITE_OK);

            return std::make_shared<SQLiteBackend>(
                database_handle);
        }
    };
}

#endif