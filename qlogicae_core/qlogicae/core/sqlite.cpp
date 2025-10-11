#include "pch.hpp"

#include "sqlite.hpp"

namespace QLogicaeCore
{
    SQLiteException::SQLiteException(const std::string& message,
        const int error_code,
        const int extended_code)
        : std::runtime_error(message),
        error_code(error_code),
        extended_code(extended_code)
    {
    }

    int SQLiteException::get_error_code() const noexcept
    {
        return error_code;
    }

    int SQLiteException::get_extended_code() const noexcept
    {
        return extended_code;
    }

    SQLiteBackend::SQLiteBackend(sqlite3* raw_database)
        : database_handle(raw_database)
    {
    }

    SQLiteBackend::~SQLiteBackend()
    {
        sqlite3_close(database_handle);
    }

    SQLiteStatementData::SQLiteStatementData(sqlite3_stmt* raw_statement)
        : statement_handle(raw_statement)
    {
    }

    SQLiteStatementData::~SQLiteStatementData()
    {
        sqlite3_finalize(statement_handle);
    }

    sqlite3_stmt* SQLiteStatementData::get() const noexcept
    {
        return statement_handle;
    }

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

    SQLiteTransaction::SQLiteTransaction(SQLiteDatabase& database_instance)
        : database(database_instance), committed(false)
    {
        SQLiteStatement begin_statement = database.prepare("BEGIN;");
        begin_statement.step();
    }

    SQLiteTransaction::~SQLiteTransaction()
    {
        if (!committed)
        {
            try
            {
                SQLiteStatement rollback_statement = database.prepare("ROLLBACK;");
                rollback_statement.step();
            }
            catch (...) {}
        }
    }

    void SQLiteTransaction::commit()
    {
        if (!committed)
        {
            SQLiteStatement commit_statement = database.prepare("COMMIT;");
            commit_statement.step();
            committed = true;
        }
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
    QLogicaeCore::SQLiteStatement& QLogicaeCore::SQLiteStatement::bind<std::string>(
        int index, const std::optional<std::string>& value)
    {
        if (value.has_value())
        {
            return bind(index, *value);
        }
        return bind(index, nullptr);
    }

    template<>
    QLogicaeCore::SQLiteStatement& QLogicaeCore::SQLiteStatement::bind<std::string>(
        const std::string_view& name, const std::optional<std::string>& value)
    {
        if (value.has_value())
        {
            return bind(name, *value);
        }
        return bind(name, nullptr);
    }

    template<>
    std::optional<std::string> QLogicaeCore::SQLiteRow::get_optional<std::string>(
        int column_index) const
    {
        if (sqlite3_column_type(statement, column_index) == SQLITE_NULL)
        {
            return std::nullopt;
        }
        return get<std::string>(column_index);
    }

    template<>
    std::optional<int> QLogicaeCore::SQLiteRow::get_optional<int>(
        int column_index) const
    {
        if (sqlite3_column_type(statement, column_index) == SQLITE_NULL)
        {
            return std::nullopt;
        }
        return get<int>(column_index);
    }

    template<>
    QLogicaeCore::SQLiteStatement& QLogicaeCore::SQLiteStatement::bind<int>(
        int index, const std::optional<int>& value)
    {
        if (value.has_value())
        {
            return bind(index, *value);
        }
        return bind(index, nullptr);
    }

    template<>
    QLogicaeCore::SQLiteStatement& QLogicaeCore::SQLiteStatement::bind<int>(
        const std::string_view& name, const std::optional<int>& value)
    {
        if (value.has_value())
        {
            return bind(name, *value);
        }
        return bind(name, nullptr);
    }

    template<>
    QLogicaeCore::SQLiteStatement& QLogicaeCore::SQLiteStatement::bind<bool>(
        int index, const std::optional<bool>& value) {
        if (value.has_value()) return bind(index, *value);
        return bind(index, nullptr);
    }

    template<>
    std::optional<bool> QLogicaeCore::SQLiteRow::get_optional<bool>(
        int column_index) const {
        if (sqlite3_column_type(statement, column_index) == SQLITE_NULL)
            return std::nullopt;
        return get<bool>(column_index);
    }

    template<>
    QLogicaeCore::SQLiteStatement& QLogicaeCore::SQLiteStatement::bind<float>(
        int index, const std::optional<float>& value) {
        if (value.has_value()) return bind(index, *value);
        return bind(index, nullptr);
    }

    template<>
    std::optional<float> QLogicaeCore::SQLiteRow::get_optional<float>(
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

}
