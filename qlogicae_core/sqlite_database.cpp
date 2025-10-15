#include "pch.hpp"

#include "sqlite_database.hpp"

namespace QLogicaeCore
{
    SQLiteDatabase::SQLiteDatabase(const std::string& file_path)
    {
        sqlite3* raw_handle = nullptr;
        int result = sqlite3_open(file_path.c_str(), &raw_handle);
        if (result != SQLITE_OK)
        {
            throw SQLiteException("failed to open database", result, result);
        }
        backend = std::make_shared<SQLiteBackend>(raw_handle);
    }

    SQLiteDatabase::~SQLiteDatabase() = default;

    SQLiteStatement SQLiteDatabase::prepare(const std::string_view& sql_text)
    {
        return SQLiteStatement(backend, sql_text);
    }

    std::future<std::shared_ptr<SQLiteStatement>> SQLiteDatabase::prepare_async(
        const std::string_view& sql_text)
    {
        return std::async(std::launch::async, [this, sql_text]() {
            return std::make_shared<SQLiteStatement>(backend, sql_text);
            });
    }

    int64_t SQLiteDatabase::last_insert_rowid() const
    {
        return sqlite3_last_insert_rowid(backend->database_handle);
    }

    void SQLiteDatabase::enable_foreign_keys()
    {
        SQLiteStatement pragma_statement = prepare("PRAGMA foreign_keys = ON;");
        pragma_statement.step();
    }

    void SQLiteDatabase::setup(
        Result<void>& result
    )
    {
        result.set_to_success();
    }
}
