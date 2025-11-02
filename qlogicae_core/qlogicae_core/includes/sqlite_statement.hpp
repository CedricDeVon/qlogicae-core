#pragma once

#include "result.hpp"
#include "sqlite_backend.hpp"
#include "sqlite_exception.hpp"
#include "sqlite_statement_data.hpp"
#include "sqlite_row.hpp"

namespace QLogicaeCore
{
    class SQLiteStatement
    {
    public:
        SQLiteStatement(
            std::shared_ptr<SQLiteBackend> backend_instance,
            const std::string_view& sql_text
        );

        ~SQLiteStatement();

        SQLiteStatement(
            SQLiteStatement&&
        ) noexcept;

        SQLiteStatement& operator = (
            SQLiteStatement&&
        ) noexcept;

        SQLiteStatement(
            const SQLiteStatement&
        ) = delete;

        SQLiteStatement& operator = (
            const SQLiteStatement&
        ) = delete;

        bool step();

        void reset();

        void clear_bindings();

        bool is_valid();

        std::optional<SQLiteRow> row();

        std::vector<SQLiteRow> query();

        SQLiteStatement& bind(
            int index,
            int value
        );

        SQLiteStatement& bind(
            int index,
            bool value
        );

        SQLiteStatement& bind(
            int index,
            float value
        );

        SQLiteStatement& bind(
            int index,
            double value
        );

        SQLiteStatement& bind(
            int index,
            int64_t value
        );

        SQLiteStatement& bind(
            int index,
            std::nullptr_t
        );

        SQLiteStatement& bind(
            int index,
            const char* value
        );

        SQLiteStatement& bind(
            int index,
            const std::string& value
        );

        SQLiteStatement& bind(
            const std::string_view& name,
            int value
        );

        SQLiteStatement& bind(
            const std::string_view& name,
            bool value
        );

        SQLiteStatement& bind(
            const std::string_view& name,
            float value
        );

        SQLiteStatement& bind(
            const std::string_view& name,
            double value
        );

        SQLiteStatement& bind(
            const std::string_view& name,
            int64_t value
        );

        SQLiteStatement& bind(
            const std::string_view& name,
            std::nullptr_t
        );

        SQLiteStatement& bind(
            const std::string_view& name,
            const std::string& value
        );

        SQLiteStatement& bind(
            const std::string_view& name,
            const char* value
        );

        template<typename T>
        SQLiteStatement& bind(
            int index,
            const std::optional<T>& value        
        );

        template<typename T>
        SQLiteStatement& bind(
            const std::string_view& name,
            const std::optional<T>& value
        );

        std::future<void> step_async();

        std::future<void> reset_async();

        std::future<void> clear_bindings_async();

        std::future<std::vector<SQLiteRow>> query_async();

        void setup(
            Result<void>& result
        );

    protected:
        std::shared_ptr<SQLiteBackend> backend;

        std::unique_ptr<SQLiteStatementData> statement;

        mutable std::unordered_map<std::string, int> parameter_name_to_index;

        int resolve_named_index(
            const std::string_view& name
        );
    };
}
