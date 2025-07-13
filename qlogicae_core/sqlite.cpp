#pragma once

#include "pch.h"

#include "sqlite.hpp"

namespace QLogicaeCore
{
    SQLiteException::SQLiteException(
        const std::string& message,
        int errcode,
        int extended
    ) : std::runtime_error(message),
        _error_code(errcode),
        _extended_code(extended)
    {
    }

    int SQLiteException::get_error_code() const noexcept
    {
        return _error_code;
    }

    int SQLiteException::get_extended_code() const noexcept
    {
        return _extended_code;
    }

    
    StatementPool::StatementPool(std::shared_ptr<SQLiteBackend> db)
        : _database(db)
    {
    }

    Statement StatementPool::get(const std::string_view& sql)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto it = _cache.find(std::string(sql));
        if (it != _cache.end() && !it->second.empty())
        {
            auto stmt = std::move(it->second.front());
            it->second.pop();
            return Statement(_database, sql);
        }
        return Statement(_database, sql);
    }

    std::unique_ptr<SQLiteStatement> Statement::release_internal_statement()
    {
        _is_valid = false;
        return std::move(_statement);
    }

    void StatementPool::release(
        const std::string& sql,
        Statement stmt
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _cache[sql].push(stmt.release_internal_statement());
    }

    RowIterator::RowIterator(Statement* statement, bool is_end)
        : _statement(statement), _is_end(is_end || !statement || !statement->is_valid())
    {
        if (!_is_end && !_statement->step())
        {
            _is_end = true;
        }
    }

    RowIterator& RowIterator::operator++()
    {
        if (!_statement || !_statement->step())
        {
            _is_end = true;
        }
        return *this;
    }

    Row RowIterator::operator*() const
    {
        return *(_statement->row());
    }

    bool RowIterator::operator!=(const RowIterator& other) const
    {
        return _is_end != other._is_end || _statement != other._statement;
    }

    std::future<void> Statement::step_async()
    {
        return std::async(std::launch::async, [this]() -> void
            {
                step();
            });
    }
    
    bool Statement::is_valid() const
    {
        return _is_valid;
    }

    std::future<void> Statement::reset_async()
    {
        return std::async(std::launch::async, [this]() -> void
            {
                reset();
            });
    }

    std::future<void> Statement::clear_bindings_async()
    {
        return std::async(std::launch::async, [this]() -> void
            {
                clear_bindings();
            });
    }

    void Statement::invalidate()
    {
        _is_valid = false;
    }

    bool Statement::step()
    {
        if (!_statement)
        {
            return false;
        }

        int result = sqlite3_step(
            reinterpret_cast<sqlite3_stmt*>(_statement.get())
        );

        if (result == SQLITE_ROW)
        {
            _is_valid = true;
            return true;
        }

        if (result == SQLITE_DONE)
        {
            _is_valid = false;
            return false;
        }

        throw SQLiteException("step() failed", result, result);
    }

    void Statement::reset()
    {
        if (_statement)
        {
            int result = sqlite3_reset(
                reinterpret_cast<sqlite3_stmt*>(_statement.get())
            );

            if (result != SQLITE_OK)
            {
                throw SQLiteException("reset() failed", result, result);
            }

            _is_valid = false;
        }
    }

    void Statement::clear_bindings()
    {
        if (_statement)
        {
            int result = sqlite3_clear_bindings(
                reinterpret_cast<sqlite3_stmt*>(_statement.get())
            );

            if (result != SQLITE_OK)
            {
                throw SQLiteException("clear_bindings() failed", result, result);
            }
        }
    }

    std::optional<Row> Statement::row()
    {
        if (!_is_valid || !_statement)
        {
            return std::nullopt;
        }

        return Row(std::make_unique<SQLiteStatement>(*(_statement.get())));
    }

    std::vector<Row> Statement::query()
    {
        std::vector<Row> result;

        while (step())
        {
            if (auto r = row())
            {
                result.push_back(std::move(*r));
            }
        }

        reset();
        return result;
    }


    Statement& Statement::bind(int index, int value)
    {
        int result = sqlite3_bind_int(
            reinterpret_cast<sqlite3_stmt*>(_statement.get()), index, value
        );

        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(int) failed", result, result);
        }

        return *this;
    }

    Statement& Statement::bind(int index, int64_t value)
    {
        int result = sqlite3_bind_int64(
            reinterpret_cast<sqlite3_stmt*>(_statement.get()), index, value
        );

        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(int64_t) failed", result, result);
        }

        return *this;
    }

    Statement& Statement::bind(int index, double value)
    {
        int result = sqlite3_bind_double(
            reinterpret_cast<sqlite3_stmt*>(_statement.get()), index, value
        );

        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(double) failed", result, result);
        }

        return *this;
    }

    Statement& Statement::bind(int index, float value)
    {
        return bind(index, static_cast<double>(value));
    }

    Statement& Statement::bind(int index, bool value)
    {
        return bind(index, static_cast<int>(value));
    }

    Statement& Statement::bind(int index, const std::string& value)
    {
        int result = sqlite3_bind_text(
            reinterpret_cast<sqlite3_stmt*>(_statement.get()), index,
            value.c_str(), static_cast<int>(value.size()), SQLITE_TRANSIENT
        );

        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(string) failed", result, result);
        }

        return *this;
    }

    Statement& Statement::bind(int index, const char* value)
    {
        int result = sqlite3_bind_text(
            reinterpret_cast<sqlite3_stmt*>(_statement.get()), index,
            value, -1, SQLITE_TRANSIENT
        );

        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(char*) failed", result, result);
        }

        return *this;
    }

    RowIterator Statement::begin()
    {
        return RowIterator(this);
    }

    RowIterator Statement::end()
    {
        return RowIterator(this, true);
    }

    Statement& Statement::bind(int index, std::nullptr_t)
    {
        int result = sqlite3_bind_null(
            reinterpret_cast<sqlite3_stmt*>(_statement.get()), index
        );

        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind(null) failed", result, result);
        }

        return *this;
    }

    Statement& Statement::bind_blob(int index, const void* data, int size)
    {
        int result = sqlite3_bind_blob(
            reinterpret_cast<sqlite3_stmt*>(_statement.get()), index,
            data, size, SQLITE_TRANSIENT
        );

        if (result != SQLITE_OK)
        {
            throw SQLiteException("bind_blob failed", result, result);
        }

        return *this;
    }

    int Statement::resolve_named_index(const std::string_view& name)
    {
        auto it = _parameter_name_cache.find(std::string(name));
        if (it != _parameter_name_cache.end())
        {
            return it->second;
        }

        int index = sqlite3_bind_parameter_index(
            reinterpret_cast<sqlite3_stmt*>(_statement.get()), name.data()
        );

        if (index == 0)
        {
            throw SQLiteException("Invalid bind parameter name: " + std::string(name), -1, -1);
        }

        _parameter_name_cache[std::string(name)] = index;
        return index;
    }

    Statement& Statement::bind(const std::string_view& name, int value)
    {
        return bind(resolve_named_index(name), value);
    }

    Statement& Statement::bind(const std::string_view& name, int64_t value)
    {
        return bind(resolve_named_index(name), value);
    }

    Statement& Statement::bind(const std::string_view& name, double value)
    {
        return bind(resolve_named_index(name), value);
    }

    Statement& Statement::bind(const std::string_view& name, float value)
    {
        return bind(resolve_named_index(name), value);
    }

    Statement& Statement::bind(const std::string_view& name, bool value)
    {
        return bind(resolve_named_index(name), value);
    }

    Statement& Statement::bind(
        const std::string_view& name,
        const std::string& value
    )
    {
        return bind(resolve_named_index(name), value);
    }

    Statement& Statement::bind(const std::string_view& name, const char* value)
    {
        return bind(resolve_named_index(name), value);
    }

    Statement& Statement::bind(const std::string_view& name, std::nullptr_t)
    {
        return bind(resolve_named_index(name), nullptr);
    }

    Statement& Statement::bind_blob(
        const std::string_view& name,
        const void* data,
        int size
    )
    {
        return bind_blob(resolve_named_index(name), data, size);
    }

    std::future<std::vector<Row>> Statement::query_async()
    {
        return std::async(std::launch::async, [this]()
            {
                std::vector<Row> result;

                while (step())
                {
                    if (auto r = row())
                    {
                        result.push_back(std::move(*r));
                    }
                }

                reset();
                return result;
            });
    }

    Statement::Statement(
        std::shared_ptr<SQLiteBackend> db,
        const std::string_view& sql
    ) : _statement(nullptr), _is_valid(false)
    {
        sqlite3_stmt* raw_stmt = nullptr;

        int result = sqlite3_prepare_v2(
            db->handler,
            sql.data(),
            static_cast<int>(sql.size()),
            &raw_stmt,
            nullptr
        );

        if (result != SQLITE_OK)
        {
            throw SQLiteException("Failed to prepare statement", result, result);
        }

        _statement = std::make_unique<SQLiteStatement>(raw_stmt);
    }

    int Row::get_index(const std::string_view& name) const
    {
        auto it = name_to_index_cache_.find(std::string(name));
        if (it != name_to_index_cache_.end())
        {
            return it->second;
        }

        int column_count = get_column_count();
        for (int i = 0; i < column_count; ++i)
        {
            std::string_view column_name = get_column_name(i);
            if (column_name == name)
            {
                name_to_index_cache_[std::string(name)] = i;
                return i;
            }
        }

        throw std::out_of_range("Column name not found: " + std::string(name));
    }

    Row::Row(std::unique_ptr<SQLiteStatement> stmt)
        : _statement(std::move(stmt))
    {
    }

    int Row::get_column_count() const
    {
        return sqlite3_column_count(
            reinterpret_cast<sqlite3_stmt*>(_statement.get())
        );
    }

    std::string_view Row::get_column_name(int index) const
    {
        const char* name = sqlite3_column_name(
            reinterpret_cast<sqlite3_stmt*>(_statement.get()), index
        );
        return name ? std::string_view(name) : std::string_view();
    }

    bool Row::is_valid() const
    {
        return _statement != nullptr;
    }

    std::vector<std::string> Row::get_column_types() const
    {
        std::vector<std::string> types;
        int count = get_column_count();

        for (int i = 0; i < count; ++i)
        {
            int type = sqlite3_column_type(
                reinterpret_cast<sqlite3_stmt*>(_statement.get()), i
            );

            switch (type)
            {
            case SQLITE_INTEGER:
                types.emplace_back("INTEGER");
                break;
            case SQLITE_FLOAT:
                types.emplace_back("FLOAT");
                break;
            case SQLITE_TEXT:
                types.emplace_back("TEXT");
                break;
            case SQLITE_BLOB:
                types.emplace_back("BLOB");
                break;
            case SQLITE_NULL:
                types.emplace_back("NULL");
                break;
            default:
                types.emplace_back("UNKNOWN");
                break;
            }
        }

        return types;
    }

    Database::Database(const std::string& filename)
    {
        sqlite3* handle = nullptr;
        int result = sqlite3_open(filename.c_str(), &handle);
        if (result != SQLITE_OK)
        {
            throw SQLiteException("Failed to open database", result, result);
        }
        _database = std::make_shared<SQLiteBackend>(handle);

    }

    Database::~Database()
    {
        sqlite3_close(reinterpret_cast<sqlite3*>(_database.get()));
    }

    void Database::configure_threading()
    {
        sqlite3_config(SQLITE_CONFIG_SERIALIZED);
    }

    Statement Database::prepare(const std::string_view& sql)
    {
        return Statement(_database, sql);
    }

    std::future<std::shared_ptr<Statement>> Database::prepare_async(
        const std::string_view& sql
    )
    {
        return std::async(std::launch::async, [this, sql]()
            {
                return std::make_shared<Statement>(_database, sql);
            });
    }

    void Database::enable_foreign_keys()
    {
        prepare("PRAGMA foreign_keys = ON;").step();
    }

    int64_t Database::last_insert_rowid() const
    {
        return sqlite3_last_insert_rowid(reinterpret_cast<sqlite3*>(_database.get()));
    }

    int Database::changes() const
    {
        return sqlite3_changes(reinterpret_cast<sqlite3*>(_database.get()));
    }

    int Database::total_changes() const
    {
        return sqlite3_total_changes(reinterpret_cast<sqlite3*>(_database.get()));
    }

    std::string Database::get_pragma(const std::string_view& name) const
    {
        sqlite3_stmt* stmt;
        std::string query = "PRAGMA " + std::string(name);
        sqlite3_prepare_v2(reinterpret_cast<sqlite3*>(_database.get()), query.c_str(), -1, &stmt, nullptr);
        if (sqlite3_step(stmt) != SQLITE_ROW)
        {
            sqlite3_finalize(stmt);
            throw SQLiteException("PRAGMA failed", -1, -1);
        }
        const char* result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string value = result ? result : "";
        sqlite3_finalize(stmt);
        return value;
    }

    void Database::set_pragma(
        const std::string_view& name,
        const std::string_view& value
    )
    {
        std::string query = "PRAGMA " + std::string(name) + " = " + std::string(value);
        prepare(query).step();
    }

    std::future<std::string> Database::get_pragma_async(const std::string_view& name) const
    {
        return std::async(std::launch::async, [this, name]() -> std::string
            {
                return get_pragma(name);
            });
    }

    std::future<void> Database::set_pragma_async(
        const std::string_view& name,
        const std::string_view& value
    )
    {
        return std::async(std::launch::async, [this, name, value]() -> void
            {
                set_pragma(name, value);
            });
    }

    StatementPool& Database::pool()
    {
        return *_statement_pool;
    }

    std::vector<std::string> Database::table_info(
        const std::string& table_name
    ) const
    {
        std::string query = "PRAGMA table_info(" + table_name + ");";
        Statement stmt = Statement(_database, query);

        std::vector<std::string> columns;

        while (stmt.step())
        {
            if (auto row = stmt.row())
            {
                columns.push_back(row->get<std::string>(1)); // name column
            }
        }

        stmt.reset();
        return columns;
    }

    std::future<std::vector<std::string>> Database::table_info_async(
        const std::string& table_name
    ) const
    {
        return std::async(std::launch::async, [this, table_name]()
            {
                return table_info(table_name);
            });
    }

    std::vector<std::string> Database::index_list(
        const std::string& table_name
    ) const
    {
        std::string query = "PRAGMA index_list(" + table_name + ");";
        Statement stmt = Statement(_database, query);

        std::vector<std::string> indexes;

        while (stmt.step())
        {
            if (auto row = stmt.row())
            {
                indexes.push_back(row->get<std::string>(1)); // name column
            }
        }

        stmt.reset();
        return indexes;
    }

    std::future<std::vector<std::string>> Database::index_list_async(
        const std::string& table_name
    ) const
    {
        return std::async(std::launch::async, [this, table_name]()
            {
                return index_list(table_name);
            });
    }

    void Database::migrate_to(
        int target_version,
        const std::function<void(int from, int to)>& upgrader
    )
    {
        Statement version_stmt = prepare(
            "PRAGMA user_version;"
        );

        int current_version = 0;
        if (version_stmt.step())
        {
            current_version = version_stmt.row()->get<int>(0);
        }

        if (current_version >= target_version)
        {
            return;
        }

        Transaction tx(*this);
        upgrader(current_version, target_version);
        prepare(
            "PRAGMA user_version = " + std::to_string(target_version)
        ).step();
        tx.execute();
    }

    std::future<void> Database::migrate_to_async(
        int target_version,
        const std::function<void(int from, int to)>& upgrader
    )
    {
        return std::async(std::launch::async, [this, target_version, upgrader]()
            {
                migrate_to(target_version, upgrader);
            });
    }

    Transaction::Transaction(Database& database)
        : _database(database), _is_committed(false)
    {
        _database.prepare("BEGIN IMMEDIATE;").step();
    }

    Transaction::~Transaction()
    {
        if (!_is_committed)
        {
            try
            {
                _database.prepare("ROLLBACK;").step();
            }
            catch (...)
            {
            }
        }
    }

    void Transaction::execute()
    {
        if (!_is_committed)
        {
            _database.prepare("COMMIT;").step();
            _is_committed = true;
        }
    }
}
