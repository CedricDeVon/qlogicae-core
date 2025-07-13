#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    class Statement;
    class StatementPool;
    class RowIterator;

    struct SQLiteBackend
    {
        sqlite3* handler;

        explicit SQLiteBackend(sqlite3* h)
            : handler(h)
        {
        }

        ~SQLiteBackend()
        {
            sqlite3_close(handler);
        }
    };

    struct SQLiteStatement
    {
        sqlite3_stmt* handler;

        explicit SQLiteStatement(sqlite3_stmt* raw) : handler(raw) {}
        ~SQLiteStatement()
        {
            sqlite3_finalize(handler);
        }
    };

    class SQLiteException : public std::runtime_error
    {
    public:
        SQLiteException(
            const std::string& message,
            int error_code,
            int get_extended_code
        );

        int get_error_code() const noexcept;
        int get_extended_code() const noexcept;

    private:
        int _error_code;
        int _extended_code;
    };

    class Database
    {
    public:
        ~Database();
        explicit Database(const std::string& filename);

        Statement prepare(const std::string_view& sql_string);
        std::future<std::shared_ptr<Statement>> prepare_async(
            const std::string_view& sql_string
        );
        static void configure_threading();
        void enable_foreign_keys();
        int64_t last_insert_rowid() const;
        int changes() const;
        int total_changes() const;

        std::vector<std::string> table_info(
            const std::string& table_name
        ) const;
        std::future<std::vector<std::string>> table_info_async(
            const std::string& table_name
        ) const;

        std::vector<std::string> index_list(
            const std::string& table_name
        ) const;
        std::future<std::vector<std::string>> index_list_async(
            const std::string& table_name
        ) const;

        void migrate_to(
            int target_version,
            const std::function<void(int from, int to)>& upgrader
        );
        std::future<void> migrate_to_async(
            int target_version,
            const std::function<void(int from, int to)>& upgrader
        );

        std::string get_pragma(const std::string_view& name) const;
        void set_pragma(
            const std::string_view& name,
            const std::string_view& value
        );
        std::future<std::string> get_pragma_async(
            const std::string_view& name
        ) const;
        std::future<void> set_pragma_async(
            const std::string_view& name,
            const std::string_view& value
        );

        StatementPool& pool();

    private:
        std::shared_ptr<SQLiteBackend> _database;
        std::unique_ptr<StatementPool> _statement_pool;
    };

    class Row
    {
    public:
        explicit Row(std::unique_ptr<SQLiteStatement> statement);

        bool is_valid() const;
        int get_column_count() const;
        std::vector<std::string> get_column_types() const;
        std::string_view get_column_name(int index) const;
        template<typename Type>
        Type get(int column) const;
        template<typename Type>
        Type get(const std::string_view& name) const;
        template<typename Type>
        std::optional<Type> get_optional(int column) const;
        template<typename Type>
        std::optional<Type> get_optional(const std::string_view& name) const;

    private:
        std::unique_ptr<SQLiteStatement> _statement;
        mutable std::unordered_map<std::string, int> name_to_index_cache_;

        int get_index(const std::string_view& name) const;
    };

    class Statement
    {
    public:
        ~Statement() = default;
        Statement(
            std::shared_ptr<SQLiteBackend> database,
            const std::string_view& sql_statement
        );
        Statement(const Statement&) = delete;
        Statement(Statement&&) noexcept = default;
        Statement& operator=(const Statement&) = delete;
        Statement& operator=(Statement&&) noexcept = default;

        bool step();
        void reset();
        void invalidate();
        RowIterator end();
        RowIterator begin();
        void clear_bindings();
        bool is_valid() const;
        std::optional<Row> row();
        std::vector<Row> query();
        Statement& bind(int index, int value);
        Statement& bind(int index, bool value);
        Statement& bind(int index, float value);
        Statement& bind(int index, double value);
        Statement& bind(int index, int64_t value);
        Statement& bind(int index, std::nullptr_t);
        Statement& bind(int index, const char* value);
        Statement& bind(int index, const std::string& value);
        int resolve_named_index(const std::string_view& name);
        Statement& bind(const std::string_view& name, int value);
        Statement& bind(const std::string_view& name, bool value);
        Statement& bind(const std::string_view& name, float value);
        Statement& bind(const std::string_view& name, double value);
        Statement& bind(const std::string_view& name, int64_t value);
        Statement& bind(const std::string_view& name, std::nullptr_t);
        std::unique_ptr<SQLiteStatement> release_internal_statement();
        Statement& bind(const std::string_view& name, const char* value);
        Statement& bind(
            const std::string_view& name,
            const std::string& value
        );
        Statement& bind_blob(int index, const void* data, int size);
        Statement& bind_blob(const std::string_view& name,
            const void* data, int size);
        template<typename T>
        Statement& bind(int index, const std::optional<T>& value);
        template<typename T>
        Statement& bind(
            const std::string_view& name,
            const std::optional<T>& value
        );
        template<typename... Args>
        void execute_many(
            const std::vector<std::tuple<Args...>>& rows
        );

        std::future<void> step_async();
        std::future<void> reset_async();
        std::future<void> clear_bindings_async();
        std::future<std::vector<Row>> query_async();

    private:
        bool _is_valid = false;
        std::unique_ptr<SQLiteStatement> _statement;
        mutable std::unordered_map<std::string, int> _parameter_name_cache;
    };

    class RowIterator
    {
    public:
        Row operator*() const;
        RowIterator& operator++();
        bool operator!=(const RowIterator& other) const;
        explicit RowIterator(Statement* statement, bool is_end = false);

    private:
        Statement* _statement;
        bool _is_end = false;
    };

    class StatementPool
    {
    public:
        explicit StatementPool(std::shared_ptr<SQLiteBackend> database);

        Statement get(const std::string_view& sql_string);
        void release(const std::string& sql_string,Statement statement);

    private:
        std::mutex _mutex;
        std::shared_ptr<SQLiteBackend> _database;
        std::unordered_map<
            std::string,
            std::queue<std::unique_ptr<SQLiteStatement>>
        > _cache;
    };

    class Transaction
    {
    public:
        ~Transaction();
        explicit Transaction(Database& database);

        void execute();

    protected:
        bool _is_committed;
        Database& _database;
    };

    template<typename T>
    Statement& Statement::bind(int index, const std::optional<T>& value)
    {
        if (value.has_value())
        {
            return bind(index, *value);
        }
        else
        {
            return bind(index, nullptr);
        }
    }

    template<typename T>
    Statement& Statement::bind(
        const std::string_view& name,
        const std::optional<T>& value
    )
    {
        if (value.has_value())
        {
            return bind(name, *value);
        }
        else
        {
            return bind(name, nullptr);
        }
    }

    template<typename... Args>
    void Statement::execute_many(const std::vector<std::tuple<Args...>>& rows)
    {
        for (const auto& tuple_row : rows)
        {
            reset();
            clear_bindings();

            std::apply(
                [this, index = 1](const Args&... args) mutable
                {
                    (bind(index++, args), ...);
                },
                tuple_row
            );

            step();
        }

        reset();
    }

    template<typename T>
    T Row::get(int col) const
    {
        sqlite3_stmt* raw_stmt = reinterpret_cast<sqlite3_stmt*>(
            _statement.get());

        if constexpr (std::is_same_v<T, int>)
        {
            return sqlite3_column_int(raw_stmt, col);
        }
        else if constexpr (std::is_same_v<T, int64_t>)
        {
            return sqlite3_column_int64(raw_stmt, col);
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return sqlite3_column_double(raw_stmt, col);
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            return static_cast<float>(sqlite3_column_double(raw_stmt, col));
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
            return sqlite3_column_int(raw_stmt, col) != 0;
        }
        else if constexpr (std::is_same_v<T, std::string>)
        {
            const char* text = reinterpret_cast<const char*>(
                sqlite3_column_text(raw_stmt, col)
                );
            return text ? std::string(text) : std::string();
        }
        else if constexpr (std::is_same_v<T, std::vector<std::byte>>)
        {
            const void* blob = sqlite3_column_blob(raw_stmt, col);
            int size = sqlite3_column_bytes(raw_stmt, col);
            const std::byte* ptr = reinterpret_cast<const std::byte*>(blob);
            return std::vector<std::byte>(ptr, ptr + size);
        }
    }

    template<typename T>
    std::optional<T> Row::get_optional(int col) const
    {
        if (sqlite3_column_type(reinterpret_cast<sqlite3_stmt*>(
            _statement.get()), col)
            == SQLITE_NULL)
        {
            return std::nullopt;
        }

        return get<T>(col);
    }

    template<typename T>
    T Row::get(const std::string_view& name) const
    {
        int col = get_index(name);
        return get<T>(col);
    }

    template<typename T>
    std::optional<T> Row::get_optional(const std::string_view& name) const
    {
        int col = get_index(name);
        return get_optional<T>(col);
    }
}
