#pragma once

#include "pch.h"

#include "globals.hpp"

namespace QLogicaeCore
{
    class SQLiteRow;
    class SQLiteStatement;

    class SQLiteException : public std::runtime_error
    {
    public:
        SQLiteException(const std::string& message,
            const int error_code,
            const int extended_code);

        int get_error_code() const noexcept;
        int get_extended_code() const noexcept;

    protected:
        int error_code;
        int extended_code;
    };

    class SQLiteDatabase
    {
    public:
        explicit SQLiteDatabase(const std::string& file_path);
        ~SQLiteDatabase();

        void enable_foreign_keys();
        int64_t last_insert_rowid() const;
        SQLiteStatement prepare(const std::string_view& sql_text);
        std::future<std::shared_ptr<SQLiteStatement>> prepare_async(
            const std::string_view& sql_text);

    protected:
        std::shared_ptr<SQLiteBackend> backend;
    };

    class SQLiteStatement
    {
    public:
        SQLiteStatement(std::shared_ptr<SQLiteBackend> backend_instance,
            const std::string_view& sql_text);
        ~SQLiteStatement();

        SQLiteStatement(SQLiteStatement&&) noexcept;
        SQLiteStatement& operator=(SQLiteStatement&&) noexcept;

        SQLiteStatement(const SQLiteStatement&) = delete;
        SQLiteStatement& operator=(const SQLiteStatement&) = delete;

        bool step();
        void reset();
        void clear_bindings();
        bool is_valid() const;
        std::optional<SQLiteRow> row();
        std::vector<SQLiteRow> query();
        SQLiteStatement& bind(int index, int value);
        SQLiteStatement& bind(int index, bool value);
        SQLiteStatement& bind(int index, float value);
        SQLiteStatement& bind(int index, double value);
        SQLiteStatement& bind(int index, int64_t value);
        SQLiteStatement& bind(int index, std::nullptr_t);
        SQLiteStatement& bind(int index, const char* value);
        SQLiteStatement& bind(int index, const std::string& value);
        SQLiteStatement& bind(const std::string_view& name, int value);
        SQLiteStatement& bind(const std::string_view& name, bool value);
        SQLiteStatement& bind(const std::string_view& name, float value);
        SQLiteStatement& bind(const std::string_view& name, double value);
        SQLiteStatement& bind(const std::string_view& name, int64_t value);
        SQLiteStatement& bind(const std::string_view& name, std::nullptr_t);
        SQLiteStatement& bind(const std::string_view& name,
            const std::string& value);
        SQLiteStatement& bind(const std::string_view& name, const char* value);
        template<typename T>
        SQLiteStatement& bind(int index, const std::optional<T>& value);
        template<typename T>
        SQLiteStatement& bind(const std::string_view& name,
            const std::optional<T>& value);

        std::future<void> step_async();
        std::future<void> reset_async();
        std::future<void> clear_bindings_async();
        std::future<std::vector<SQLiteRow>> query_async();

    protected:
        std::shared_ptr<SQLiteBackend> backend;
        std::unique_ptr<SQLiteStatementData> statement;
        mutable std::unordered_map<std::string, int> parameter_name_to_index;
        
        int resolve_named_index(const std::string_view& name);
    };

    class SQLiteRow
    {
    public:
        explicit SQLiteRow(sqlite3_stmt* raw_statement);

        template<typename Type>
        Type get(int column_index) const;

        template<typename Type>
        Type get(const std::string_view& column_name) const;

        template<typename Type>
        std::optional<Type> get_optional(int column_index) const;

        template<typename Type>
        std::optional<Type> get_optional(
            const std::string_view& column_name) const;

        int get_column_count() const;
        std::string_view get_column_name(int column_index) const;

    protected:
        int get_index(const std::string_view& column_name) const;

        sqlite3_stmt* statement;
        mutable std::unordered_map<std::string, int> column_name_to_index;
    };

    class SQLiteTransaction
    {
    public:
        explicit SQLiteTransaction(SQLiteDatabase& database_instance);
        ~SQLiteTransaction();

        void commit();

    protected:
        bool committed;
        SQLiteDatabase& database;
    };
}
