#pragma once

#include "result.hpp"

#include <sqlite3.h>

namespace QLogicaeCore
{
    struct SQLiteBackend
    {
    public:
        explicit SQLiteBackend(
            sqlite3* raw_database
        );

        ~SQLiteBackend();

        void setup(
            Result<void>& result
        );

        sqlite3* database_handle;
    };
}
