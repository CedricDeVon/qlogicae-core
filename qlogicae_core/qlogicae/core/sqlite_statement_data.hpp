#pragma once

namespace QLogicaeCore
{
    struct SQLiteStatementData
    {
    public:
        explicit SQLiteStatementData(sqlite3_stmt* raw_statement);
        ~SQLiteStatementData();

        sqlite3_stmt* get() const noexcept;

    protected:
        sqlite3_stmt* statement_handle;
    };
}
