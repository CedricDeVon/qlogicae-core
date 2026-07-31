#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteStatementData \
	)

#include "../includes/sqlite_statement_data.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    SQLiteStatementData
		::SQLiteStatementData(
			sqlite3_stmt*
				raw_statement
		)
    {
		statement_handle =
			raw_statement;
    }

	SQLiteStatementData
		::SQLiteStatementData()
    {
		statement_handle =
			nullptr;
    }

    SQLiteStatementData
		::~SQLiteStatementData()
    {
        if (statement_handle != nullptr)
		{
			sqlite3_finalize(statement_handle);
			statement_handle = nullptr;
		}
    }
	
    SQLiteStatementData
        ::SQLiteStatementData(
            SQLiteStatementData&&
                instance
        ) noexcept
    {
        statement_handle =
            instance.statement_handle;

        instance.statement_handle =
            nullptr;
    }

    SQLiteStatementData&
        SQLiteStatementData
            ::operator=(
                SQLiteStatementData&&
                    instance
            ) noexcept
    {
        if (this != &instance)
        {
            if (statement_handle != nullptr)
            {
                sqlite3_finalize(
                    statement_handle
                );
            }

            statement_handle =
                instance.statement_handle;

            instance.statement_handle =
                nullptr;
        }

        return
            *this;
    }
}

#endif
