#include "pch.hpp"

#include "sqlite_row.hpp"

namespace QLogicaeCore
{
    template<>
    int SQLiteRow::get<int>(int column_index) const
    {
        if (sqlite3_column_type(statement, column_index) == SQLITE_NULL)
        {
            throw SQLiteException("column is null", -1, -1);
        }
        return sqlite3_column_int(statement, column_index);
    }

    template<>
    double SQLiteRow::get<double>(int column_index) const
    {
        if (sqlite3_column_type(statement, column_index) == SQLITE_NULL)
        {
            throw SQLiteException("column is null", -1, -1);
        }
        return sqlite3_column_double(statement, column_index);
    }

    template<>
    float SQLiteRow::get<float>(int column_index) const
    {
        return static_cast<float>(get<double>(column_index));
    }

    template<>
    bool SQLiteRow::get<bool>(int column_index) const
    {
        return get<int>(column_index) != 0;
    }

    template<>
    std::string SQLiteRow::get<std::string>(int column_index) const
    {
        const char* text = reinterpret_cast<const char*>(
            sqlite3_column_text(statement, column_index));
        return text ? std::string(text) : std::string();
    }

    template<>
    std::optional<std::string> SQLiteRow::get_optional<std::string>(
        int column_index) const
    {
        if (sqlite3_column_type(statement, column_index) == SQLITE_NULL)
        {
            return std::nullopt;
        }
        return get<std::string>(column_index);
    }

    template<>
    std::optional<int> SQLiteRow::get_optional<int>(
        int column_index) const
    {
        if (sqlite3_column_type(statement, column_index) == SQLITE_NULL)
        {
            return std::nullopt;
        }
        return get<int>(column_index);
    }

    template<>
    std::optional<float> SQLiteRow::get_optional<float>(
        int column_index) const
    {
        if (sqlite3_column_type(statement, column_index) == SQLITE_NULL)
            return std::nullopt;
        return get<float>(column_index);
    }

    template<>
    int SQLiteRow::get<int>(const std::string_view& column_name) const
    {
        return get<int>(get_index(column_name));
    }

    template<>
    std::string SQLiteRow::get<std::string>(
        const std::string_view& column_name) const
    {
        return get<std::string>(get_index(column_name));
    }

    void SQLiteRow::setup(
        Result<void>& result
    )
    {
        result.set_to_success();
    }
}
