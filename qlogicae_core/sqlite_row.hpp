#pragma once

#include "sqlite_exception.hpp"

#include <sqlite3.h>

namespace QLogicaeCore
{
	class SQLiteRow;

    class SQLiteRow
    {
    public:
        explicit SQLiteRow(
            sqlite3_stmt* raw_statement
        );

        template<typename Type>
        Type get(
            int column_index
        ) const;

        template<typename Type>
        Type get(
            const std::string_view& column_name
        ) const;

        template<typename Type>
        std::optional<Type> get_optional(
            int column_index
        ) const;

        template<typename Type>
        std::optional<Type> get_optional(
            const std::string_view& column_name
        ) const;

        int get_column_count() const;
        std::string_view get_column_name(
            int column_index
        ) const;

    protected:
        int get_index(
            const std::string_view& column_name
        ) const;

        sqlite3_stmt* statement;
        
        mutable std::unordered_map<std::string, int> column_name_to_index;
    };
}
