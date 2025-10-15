#pragma once

#include "sqlite_database.hpp"

namespace QLogicaeCore
{
    class SQLiteTransaction
    {
    public:
        explicit SQLiteTransaction(
            SQLiteDatabase& database_instance
        );
        
        ~SQLiteTransaction();

        void commit();

    protected:
        bool committed;
        
        SQLiteDatabase& database;
    };
}
