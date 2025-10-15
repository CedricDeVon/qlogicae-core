#include "pch.hpp"

#include "sqlite_statement.hpp"

namespace QLogicaeCore
{
    SQLiteStatement::SQLiteStatement(std::shared_ptr<SQLiteBackend> backend_instance,
        const std::string_view& sql_text)
        : backend(backend_instance)
    {
        sqlite3_stmt* raw_statement = nullptr;
        int result = sqlite3_prepare_v2(backend->database_handle,
            sql_text.data(),
            static_cast<int>(sql_text.size()),
            &raw_statement, nullptr);
        if (result != SQLITE_OK)
        {
            throw SQLiteException("failed to prepare statement",
                result, sqlite3_extended_errcode(backend->database_handle));
        }
        statement = std::make_unique<SQLiteStatementData>(raw_statement);
    }

    SQLiteStatement::~SQLiteStatement() = default;

    SQLiteStatement::SQLiteStatement(SQLiteStatement&& other) noexcept = default;
    SQLiteStatement& SQLiteStatement::operator=(SQLiteStatement&& other) noexcept = default;

    bool SQLiteStatement::step()
    {
        int result = sqlite3_step(statement->get());
        if (result == SQLITE_ROW)
        {
            return true;
        }
        if (result == SQLITE_DONE)
        {
            return false;
        }
        throw SQLiteException("step() failed",
            result, sqlite3_extended_errcode(backend->database_handle));
    }

    void SQLiteStatement::reset()
    {
        int result = sqlite3_reset(statement->get());
        if (result != SQLITE_OK)
        {
            throw SQLiteException("reset() failed",
                result, sqlite3_extended_errcode(backend->database_handle));
        }
    }

    void SQLiteStatement::clear_bindings()
    {
        int result = sqlite3_clear_bindings(statement->get());
        if (result != SQLITE_OK)
        {
            throw SQLiteException("clear_bindings() failed",
                result, sqlite3_extended_errcode(backend->database_handle));
        }
    }

    bool SQLiteStatement::is_valid() const
    {
        return statement != nullptr;
    }

    int SQLiteStatement::resolve_named_index(const std::string_view& name)
    {
        std::string key(name);
        auto it = parameter_name_to_index.find(key);
        if (it != parameter_name_to_index.end())
        {
            return it->second;
        }
        int index = sqlite3_bind_parameter_index(statement->get(), name.data());
        if (index == 0)
        {
            throw SQLiteException("invalid parameter name", -1, -1);
        }
        parameter_name_to_index[key] = index;
        return index;
    }

    SQLiteStatement& SQLiteStatement::bind(int index, bool value)
    {
        return bind(index, static_cast<int>(value));
    }

    SQLiteStatement& SQLiteStatement::bind(int index, const std::string& value)
    {
        int result = sqlite3_bind_text(statement->get(), index,
            value.c_str(), static_cast<int>(value.size()),
            SQLITE_TRANSIENT);
        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(string) failed",
                result, sqlite3_extended_errcode(backend->database_handle));
        }
        return *this;
    }

    SQLiteStatement& SQLiteStatement::bind(int index, const char* value)
    {
        int result = sqlite3_bind_text(statement->get(), index,
            value, -1, SQLITE_TRANSIENT);
        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(char*) failed",
                result, sqlite3_extended_errcode(backend->database_handle));
        }
        return *this;
    }

    SQLiteStatement& SQLiteStatement::bind(int index, std::nullptr_t)
    {
        int result = sqlite3_bind_null(statement->get(), index);
        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(null) failed",
                result, sqlite3_extended_errcode(backend->database_handle));
        }
        return *this;
    }

    int SQLiteRow::get_column_count() const
    {
        return sqlite3_column_count(statement);
    }

    std::string_view SQLiteRow::get_column_name(int column_index) const
    {
        const char* name = sqlite3_column_name(statement, column_index);
        return name ? std::string_view(name) : std::string_view();
    }

    int SQLiteRow::get_index(const std::string_view& column_name) const
    {
        auto it = column_name_to_index.find(std::string(column_name));
        if (it != column_name_to_index.end())
        {
            return it->second;
        }
        int count = get_column_count();
        for (int i = 0; i < count; ++i)
        {
            if (get_column_name(i) == column_name)
            {
                column_name_to_index[std::string(column_name)] = i;
                return i;
            }
        }
        throw SQLiteException("column name not found", -1, -1);
    }

    SQLiteStatement& SQLiteStatement::bind(int index, int value)
    {
        int result = sqlite3_bind_int(statement->get(), index, value);
        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(int) failed", result, sqlite3_extended_errcode(backend->database_handle));
        }
        return *this;
    }

    SQLiteStatement& SQLiteStatement::bind(int index, int64_t value)
    {
        int result = sqlite3_bind_int64(statement->get(), index, value);
        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(int64_t) failed", result, sqlite3_extended_errcode(backend->database_handle));
        }
        return *this;
    }

    SQLiteStatement& SQLiteStatement::bind(int index, double value)
    {
        int result = sqlite3_bind_double(statement->get(), index, value);
        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(double) failed", result, sqlite3_extended_errcode(backend->database_handle));
        }
        return *this;
    }

    SQLiteStatement& SQLiteStatement::bind(int index, float value)
    {
        return bind(index, static_cast<double>(value));
    }

    SQLiteStatement& SQLiteStatement::bind(const std::string_view& name, int value)
    {
        return bind(resolve_named_index(name), value);
    }

    SQLiteStatement& SQLiteStatement::bind(const std::string_view& name, int64_t value)
    {
        return bind(resolve_named_index(name), value);
    }

    SQLiteStatement& SQLiteStatement::bind(const std::string_view& name, double value)
    {
        return bind(resolve_named_index(name), value);
    }

    SQLiteStatement& SQLiteStatement::bind(const std::string_view& name, float value)
    {
        return bind(resolve_named_index(name), static_cast<double>(value));
    }

    SQLiteStatement& SQLiteStatement::bind(const std::string_view& name, bool value)
    {
        return bind(resolve_named_index(name), static_cast<int>(value));
    }

    SQLiteStatement& SQLiteStatement::bind(const std::string_view& name, const std::string& value)
    {
        int result = sqlite3_bind_text(statement->get(), resolve_named_index(name), value.c_str(), static_cast<int>(value.size()), SQLITE_TRANSIENT);
        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(std::string) failed", result, sqlite3_extended_errcode(backend->database_handle));
        }
        return *this;
    }

    SQLiteStatement& SQLiteStatement::bind(const std::string_view& name, const char* value)
    {
        int result = sqlite3_bind_text(statement->get(), resolve_named_index(name), value, -1, SQLITE_TRANSIENT);
        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(const char*) failed", result, sqlite3_extended_errcode(backend->database_handle));
        }
        return *this;
    }

    SQLiteStatement& SQLiteStatement::bind(const std::string_view& name, std::nullptr_t)
    {
        int result = sqlite3_bind_null(statement->get(), resolve_named_index(name));
        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(null) failed", result, sqlite3_extended_errcode(backend->database_handle));
        }
        return *this;
    }

    std::vector<SQLiteRow> SQLiteStatement::query()
    {
        std::vector<SQLiteRow> results;
        while (step())
        {
            if (auto r = row())
            {
                results.push_back(*r);
            }
        }
        reset();
        return results;
    }

    std::future<void> SQLiteStatement::step_async()
    {
        return std::async(std::launch::async, [this]() {
            step();
            });
    }

    std::future<void> SQLiteStatement::reset_async()
    {
        return std::async(std::launch::async, [this]() {
            reset();
            });
    }

    std::future<void> SQLiteStatement::clear_bindings_async()
    {
        return std::async(std::launch::async, [this]() {
            clear_bindings();
            });
    }

    std::future<std::vector<SQLiteRow>> SQLiteStatement::query_async()
    {
        return std::async(std::launch::async, [this]() {
            return query();
            });
    }

    SQLiteRow::SQLiteRow(sqlite3_stmt* raw_statement)
        : statement(raw_statement)
    {
    }

    std::optional<SQLiteRow> SQLiteStatement::row()
    {
        if (!statement || sqlite3_data_count(statement->get()) == 0)
        {
            return std::nullopt;
        }
        return SQLiteRow(statement->get());
    }

    template<>
    SQLiteStatement& SQLiteStatement::bind<int>(
        int index, const std::optional<int>& value)
    {
        if (value.has_value())
        {
            return bind(index, *value);
        }
        return bind(index, nullptr);
    }

    template<>
    SQLiteStatement& SQLiteStatement::bind<int>(
        const std::string_view& name, const std::optional<int>& value)
    {
        if (value.has_value())
        {
            return bind(name, *value);
        }
        return bind(name, nullptr);
    }

    template<>
    SQLiteStatement& SQLiteStatement::bind<bool>(
        int index, const std::optional<bool>& value) {
        if (value.has_value()) return bind(index, *value);
        return bind(index, nullptr);
    }

    template<>
    std::optional<bool> SQLiteRow::get_optional<bool>(
        int column_index) const {
        if (sqlite3_column_type(statement, column_index) == SQLITE_NULL)
            return std::nullopt;
        return get<bool>(column_index);
    }

    template<>
    SQLiteStatement& SQLiteStatement::bind<float>(
        int index, const std::optional<float>& value) {
        if (value.has_value()) return bind(index, *value);
        return bind(index, nullptr);
    }

    template<>
    SQLiteStatement& SQLiteStatement::bind<std::string>(
        int index, const std::optional<std::string>& value)
    {
        if (value.has_value())
        {
            return bind(index, *value);
        }
        return bind(index, nullptr);
    }

    template<>
    SQLiteStatement& SQLiteStatement::bind<std::string>(
        const std::string_view& name, const std::optional<std::string>& value)
    {
        if (value.has_value())
        {
            return bind(name, *value);
        }
        return bind(name, nullptr);
    }

    void SQLiteStatement::setup(
        Result<void>& result
    )
    {
        result.set_to_success();
    }
}
