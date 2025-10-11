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
}
