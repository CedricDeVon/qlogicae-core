#include "pch.hpp"

#include "../includes/sqlite_statement_data.hpp"

namespace QLogicaeCore
{
    SQLiteStatementData::SQLiteStatementData(
        sqlite3_stmt* raw_statement
    )
        : statement_handle(raw_statement)
    {
    }

    SQLiteStatementData::~SQLiteStatementData()
    {
        sqlite3_finalize(statement_handle);
    }

    sqlite3_stmt* SQLiteStatementData::get() noexcept
    {
        return statement_handle;
    }
}
