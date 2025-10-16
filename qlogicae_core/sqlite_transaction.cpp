#include "pch.hpp"

#include "sqlite_transaction.hpp"

namespace QLogicaeCore
{
    SQLiteTransaction::SQLiteTransaction(
        SQLiteDatabase& database_instance
    )
        : database(database_instance),
        committed(false)
    {
        SQLiteStatement begin_statement =
            database.prepare("BEGIN;");
        
        begin_statement.step();
    }

    SQLiteTransaction::~SQLiteTransaction()
    {
        if (!committed)
        {
            try
            {
                SQLiteStatement rollback_statement =
                    database.prepare("ROLLBACK;");
                
                rollback_statement.step();
            }
            catch (...)
            {
            
            }
        }
    }

    void SQLiteTransaction::commit()
    {
        if (!committed)
        {
            SQLiteStatement commit_statement =
                database.prepare("COMMIT;");
            
            commit_statement.step();
            committed = true;
        }
    }
}
