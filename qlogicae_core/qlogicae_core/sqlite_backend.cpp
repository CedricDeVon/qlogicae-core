#include "pch.hpp"

#include "sqlite_backend.hpp"

namespace QLogicaeCore
{
    SQLiteBackend::SQLiteBackend(sqlite3* raw_database)
        : database_handle(raw_database)
    {

    }

    SQLiteBackend::~SQLiteBackend()
    {
        sqlite3_close(database_handle);
    }

    void SQLiteBackend::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }
}
