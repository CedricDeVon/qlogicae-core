#pragma once

#include <sqlite3.h>

namespace QLogicaeCore
{
    struct SQLiteBackend
    {
    public:
        explicit SQLiteBackend(sqlite3* raw_database);
        ~SQLiteBackend();

        sqlite3* database_handle;
    };
}
