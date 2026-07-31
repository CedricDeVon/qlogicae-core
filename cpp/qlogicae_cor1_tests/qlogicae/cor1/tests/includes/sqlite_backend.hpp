#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteBackend \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class SQLiteBackendTest
    {
    public:
        SQLiteBackendTest() = default;
        ~SQLiteBackendTest() = default;

        static sqlite3* create_memory_database()
        {
            sqlite3* database_handle = nullptr;
            sqlite3_open(":memory:", &database_handle);
            return database_handle;
        }

        static void safe_close(sqlite3* database_handle)
        {
            if (database_handle)
            {
                sqlite3_close(database_handle);
            }
        }
    };
}

#endif