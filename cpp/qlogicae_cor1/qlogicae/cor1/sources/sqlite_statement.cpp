#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteStatement \
	)

#include "../includes/sqlite_statement.hpp"

namespace
    QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    SQLiteStatement
		::SQLiteStatement(
			std::shared_ptr<SQLiteBackend>
				backend_instance,
			const std::string&
				sql_text
		)
    {
        finished =
            false;

        has_row_state =
            false;

		backend =
			backend_instance;

        sqlite3_stmt*
            raw_statement =
                nullptr;

        int
            result =
                sqlite3_prepare_v2(
                    backend->database_handle,
                    sql_text.data(),
                    static_cast<int>(sql_text.size()),
                    &raw_statement,
                    nullptr
                );

        if (result != SQLITE_OK)
        {
            throw
                SQLiteException(
                    "Failed To Prepare Statement",
                    result,
                    sqlite3_extended_errcode(
                        backend->database_handle
                    )
                );
        }

        statement =
            std::make_unique<SQLiteStatementData>(
                raw_statement
            );
    }

	SQLiteStatement
		::SQLiteStatement(
			const std::string&
				file_path,
			const std::string&
				sql_text
		)
    {
        finished =
            false;

        has_row_state =
            false;

		sqlite3*
			raw_handle =
				nullptr;

		int
			result =
				sqlite3_open(
					file_path.c_str(),
					&raw_handle
				);

		if (result != SQLITE_OK)
		{
			throw
				SQLiteException(
					"Failed To Open Database",
					result,
					result
				);
		}

		backend =
			std::make_shared<SQLiteBackend>(
				raw_handle
			);

        sqlite3_stmt*
            raw_statement =
                nullptr;

        result =
            sqlite3_prepare_v2(
                backend->database_handle,
                sql_text.data(),
                static_cast<int>(sql_text.size()),
                &raw_statement,
                nullptr
            );

        if (result != SQLITE_OK)
        {
            throw
                SQLiteException(
                    "Failed To Prepare Statement",
                    result,
                    sqlite3_extended_errcode(
                        backend->database_handle
                    )
                );
        }

        statement =
            std::make_unique<SQLiteStatementData>(
                raw_statement
            );
    }

    SQLiteStatement
		::SQLiteStatement()
    {
        finished =
            false;

        has_row_state =
            false;

        sqlite3*
			raw_handle =
				nullptr;
    }

    bool
        SQLiteStatement
            ::step()
    {
        if (finished)
        {
            return
                false;
        }

        int
            result =
                sqlite3_step(
                    statement->statement_handle
                );

        if (result == SQLITE_ROW)
        {
            has_row_state = true;
            
            return
                true;
        }

        if (result == SQLITE_DONE)
        {
            finished = true;
            has_row_state = false;
            
            return
                false;
        }

        throw
            SQLiteException(
                "step() failed",
                result,
                sqlite3_extended_errcode(
                    backend->database_handle
                )
            );
    }

    bool
        SQLiteStatement
            ::reset()
    {
        int
            result =
                sqlite3_reset(
                    statement->statement_handle
                );

        if (result != SQLITE_OK)
        {
            throw
                SQLiteException(
                    "reset() failed",
                    result,
                    sqlite3_extended_errcode(
                        backend->database_handle
                    )
                );
        }

        finished =
            false;

        has_row_state =
            false;
        
        sqlite3_reset(
            statement->statement_handle
        );
        
        sqlite3_clear_bindings(
            statement->statement_handle
        );

		return
			true;
    }

    bool
        SQLiteStatement
            ::clear_bindings()
    {
        int
            result =
                sqlite3_clear_bindings(
                    statement->statement_handle
                );

        if (result != SQLITE_OK)
        {
            throw
                SQLiteException(
                    "clear_bindings() failed",
                    result,
                    sqlite3_extended_errcode(
                        backend->database_handle
                    )
                );
        }

		return
			true;
    }

    bool
        SQLiteStatement
            ::is_valid()
    {
        return
            statement != nullptr;
    }

    int
        SQLiteStatement
            ::resolve_named_index(
                const std::string&
                    name
            )
    {
        std::string key(name);
        auto it = parameter_name_to_index.find(key);
        if (it != parameter_name_to_index.end())
        {
            return
                it->second;
        }
        int index = sqlite3_bind_parameter_index(
            statement->statement_handle, name.data()
        );
        if (index == 0)
        {
            throw SQLiteException("invalid parameter name", -1, -1);
        }

        parameter_name_to_index[key] = index;

        return
            index;
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                int
                    index,
                bool
                    value
            )
    {
        return
            bind(
                index,
                static_cast<int>(
                    value
                )
            );
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                int
                    index,
                const std::string&
                    value
            )
    {
        int
            result =
                sqlite3_bind_text(
                    statement->statement_handle,
                    index,
                    value.c_str(),
                    static_cast<int>(value.size()),
                    SQLITE_TRANSIENT
                );

        if (result != SQLITE_OK)
        {
            throw
                SQLiteException(
                    "bind(string) failed",
                    result,
                    sqlite3_extended_errcode(
                        backend->database_handle)
                );
        }

        return
            *this;
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                int
                    index,
                const char*
                    value
            )
    {
        int
            result =
                sqlite3_bind_text(
                    statement->statement_handle,
                    index,
                    value,
                    -1,
                    SQLITE_TRANSIENT
                );

        if (result != SQLITE_OK)
        {
            throw
                SQLiteException(
                    "bind(char*) failed",
                    result,
                    sqlite3_extended_errcode(
                        backend->database_handle
                    )
                );
        }

        return
            *this;
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                int
                    index,
                std::
                    nullptr_t
            )
    {
        int
            result =
                sqlite3_bind_null(
                    statement->statement_handle,
                    index
                );

        if (result != SQLITE_OK)
        {
            throw
                SQLiteException(
                    "bind(null) failed",
                    result,
                    sqlite3_extended_errcode(
                        backend->database_handle
                    )
                );
        }

        return
            *this;
    }

	std::optional<SQLiteRow>
        SQLiteStatement
            ::row()
	{
		if (!statement)
        {
            return
                std::nullopt;
        }

        if (!statement->statement_handle)
        {
            return
                std::nullopt;
        }

        if (finished)
        {
            return
                std::nullopt;
        }

        if (!has_row_state)
        {
            return
                std::nullopt;
        }

        if (sqlite3_data_count(
            statement->statement_handle) <= 0)
        {
            return
                std::nullopt;
        }

		return
            SQLiteRow(
                statement->statement_handle
            );
	}

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                int
                    index,
                int
                    value
            )
    {
        int result = sqlite3_bind_int(
            statement->statement_handle,
            index,
            value
        );
        if (result != SQLITE_OK)
        {
            throw SQLiteException(
                "bind(int) failed",
                result, 
                sqlite3_extended_errcode(
                    backend->database_handle
                )
            );
        }
        return
            *this;
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                int
                    index,
                int64_t
                    value
            )
    {
        int result = sqlite3_bind_int64(
            statement->statement_handle,
            index,
            value
        );
        if (result != SQLITE_OK)
        {
            throw SQLiteException(
                "bind(int64_t) failed",
                result,
                sqlite3_extended_errcode(
                    backend->database_handle
                )
            );
        }
        return
            *this;
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                int
                    index,
                double
                    value
            )
    {
        int result = sqlite3_bind_double(
            statement->statement_handle,
            index,
            value
        );
        if (result != SQLITE_OK)
        {
            throw SQLiteException(
                "bind(double) failed",
                result,
                sqlite3_extended_errcode(
                    backend->database_handle
                )
            );
        }
        return
            *this;
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                int
                    index,
                float
                    value
            )
    {
        return bind(
            index,
            static_cast<double>(value)
        );
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                const std::string&
                    name,
                int
                    value
            )
    {
        return bind(
            resolve_named_index(name),
            value
        );
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                const std::string&
                    name,
                int64_t
                    value
            )
    {
        return bind(
            resolve_named_index(name),
            value
        );
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                const std::string&
                    name,
                double value
            )
    {
        return bind(resolve_named_index(name),
            value
        );
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                const std::string&
                    name,
                float
                    value
            )
    {
        return bind(
            resolve_named_index(name),
            static_cast<double>(value)
        );
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                const std::string&
                    name,
                bool
                    value
            )
    {
        return
            bind(
                resolve_named_index(name),
                static_cast<int>(value)
            );
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                const std::string&
                    name,
                const std::string&
                    value
            )
    {
        int result = sqlite3_bind_text(
            statement->statement_handle,
            resolve_named_index(name),
            value.c_str(),
            static_cast<int>(value.size()),
            SQLITE_TRANSIENT
        );
        if (result != SQLITE_OK)
        {
            throw
                SQLiteException(
                    "bind(std::string) failed",
                    result,
                    sqlite3_extended_errcode(
                        backend->database_handle
                    )
                );
        }

        return
            *this;
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                const std::string&
                    name,
                const char*
                    value
            )
    {
        int result = sqlite3_bind_text(
            statement->statement_handle,
            resolve_named_index(name),
            value,
            -1,
            SQLITE_TRANSIENT
        );
        if (result != SQLITE_OK)
        {
            throw
                SQLiteException(
                    "bind(const char*) failed",
                    result,
                    sqlite3_extended_errcode(
                        backend->database_handle
                    )
                );
        }

        return
            *this;
    }

    SQLiteStatement&
        SQLiteStatement
            ::bind(
                const std::string&
                    name,
                std::nullptr_t
            )
    {
        int result = sqlite3_bind_null(
            statement->statement_handle,
            resolve_named_index(name)
        );
        if (result != SQLITE_OK)
        {
            throw
                SQLiteException(
                    "bind(null) failed",
                    result,
                    sqlite3_extended_errcode(
                        backend->database_handle
                    )
                );
        }

        return
            *this;
    }

    std::vector<SQLiteRow>
        SQLiteStatement
            ::query()
    {
        reset();

        std::vector<SQLiteRow> results;
        while (step())
        {
            if (auto r = row())
            {
                results.push_back(*r);
            }
        }
        reset();

        return
            results;
    }

    template<>
        SQLiteStatement&
            SQLiteStatement
                ::bind<int>(
                    int
                        index,
                    const std::optional<int>&
                        value
                )
    {
        if (value.has_value())
        {
            return
                bind(index, *value);
        }

        return
            bind(index, nullptr);
    }

    template<>
        SQLiteStatement&
            SQLiteStatement
                ::bind<int>(
                    const std::string&
                        name,
                    const std::optional<int>&
                        value
                )
    {
        if (value.has_value())
        {
            return
                bind(name, *value);
        }

        return
            bind(name, nullptr);
    }

    template<>
        SQLiteStatement&
            SQLiteStatement
                ::bind<bool>(
                    int
                        index,
                    const std::optional<bool>&
                        value
                )
    {
        if (value.has_value())
        {
            return
                bind(index, *value);
        }

        return
            bind(index, nullptr);
    }

    template<>
        SQLiteStatement&
            SQLiteStatement
                ::bind<float>(
                    int
                        index,
                    const std::optional<float>&
                        value
                )
    {
        if (value.has_value())
        {
            return
                bind(index, *value);
        }

        return
            bind(index, nullptr);
    }
    
    template<>
        SQLiteStatement&
            SQLiteStatement::bind<double>(
                int
                    index,
                const std::optional<double>&
                    value
    )
    {
        if (value.has_value())
        {
            return
                bind(index, *value);
        }

        return
            bind(index, nullptr);
    }

    template<>
        SQLiteStatement&
            SQLiteStatement
                ::bind<double>(
                    const std::string&
                        name,
                    const std::optional<double>&
                        value
                )
    {
        if (value.has_value())
        {
            return
                bind(name,*value);
        }

        return
            bind(name,nullptr);
    }

    template<>
        SQLiteStatement&
            SQLiteStatement
                ::bind<std::string>(
                    int
                        index,
                    const std::optional<std::string>&
                        value
                )
    {
        if (value.has_value())
        {
            return
                bind(index, *value);
        }

        return
            bind(index, nullptr);
    }

    template<>
        SQLiteStatement&
            SQLiteStatement
                ::bind<std::string>(
                    const std::string&
                        name,
                    const std::optional<std::string>&
                        value
                )
    {
        if (value.has_value())
        {
            return
                bind(name, *value);
        }

        return
            bind(name, nullptr);
    }

    template<>
        SQLiteStatement&
            SQLiteStatement::bind<int64_t>(
                int
                    index,
                const std::optional<int64_t>&
                    value
        )
    {
        if (value.has_value())
        {
            return
                bind(index,value.value());
        }

        return
            bind(index,nullptr);
    }

    template<typename Type>
        SQLiteStatement&
            SQLiteStatement::bind(
                int
                    index,
                const std::optional<Type>&
                    value
            )
    {
        if (value.has_value())
        {
            return
                bind(index,value.value());
        }

        return
            bind(index,nullptr);
    }
}

#endif
