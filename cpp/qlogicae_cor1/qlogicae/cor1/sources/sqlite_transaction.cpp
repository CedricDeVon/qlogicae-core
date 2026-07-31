#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteTransaction \
	)

#include "../includes/sqlite_transaction.hpp"

namespace
    QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    
}

#endif

/*

SQLiteTransaction
        ::SQLiteTransaction(
            SQLiteDatabaseManager&
                database_instance
        ) :
            database(
                database_instance
            )
    {
        SQLiteStatement
            begin_statement =
                database
                    .setup_statement("BEGIN;");

        committed =
            false;

        begin_statement
            .step();
    }

    SQLiteTransaction
        ::~SQLiteTransaction()
    {
        if (!committed)
        {
            try
            {
                SQLiteStatement
                    rollback_statement =
                        database
                            .setup_statement("ROLLBACK;");

                rollback_statement
                    .step();
            }
            catch (...)
            {

            }
        }
    }

    bool
        SQLiteTransaction
            ::commit()
    {
        if (!committed)
        {
            SQLiteStatement
                commit_statement =
                    database
                        .setup_statement("COMMIT;");

            commit_statement.step();
            committed = true;
        }

        return
            true;
    }

*/
