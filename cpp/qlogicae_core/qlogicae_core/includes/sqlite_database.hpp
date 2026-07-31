#pragma once

#include "result.hpp"
#include "sqlite_exception.hpp"
#include "sqlite_statement.hpp"

namespace QLogicaeCore
{
    class SQLiteDatabase
    {
    public:
        explicit SQLiteDatabase(
            const std::string& file_path
        );

        ~SQLiteDatabase();

        void enable_foreign_keys();

        int64_t last_insert_rowid();

        SQLiteStatement prepare(
            const std::string_view& sql_text
        );

        std::future<std::shared_ptr<SQLiteStatement>> prepare_async(
            const std::string_view& sql_text
        );

        void setup(
            Result<void>& result
        );

    protected:
        std::shared_ptr<SQLiteBackend> backend;
    };
}
