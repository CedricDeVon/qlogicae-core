#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteStatementData \
	)

namespace
    QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		SQLiteStatementData
    {
    public:
        sqlite3_stmt*
			statement_handle;

        SQLiteStatementData(
            sqlite3_stmt*
				raw_statement
        );

		SQLiteStatementData();
        
        ~SQLiteStatementData();
        
        SQLiteStatementData(
                SQLiteStatementData&&
                    instance
            ) noexcept;

        SQLiteStatementData&
            operator=(
                SQLiteStatementData&&
                    instance
            ) noexcept;

        SQLiteStatementData(
                const SQLiteStatementData&
                    instance
            ) = delete;

        SQLiteStatementData&
            operator = (
                const SQLiteStatementData&
                    instance
            ) = delete;
    };
}

#endif
