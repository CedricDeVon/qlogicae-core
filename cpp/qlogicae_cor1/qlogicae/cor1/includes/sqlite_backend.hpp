#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteBackend \
	)

namespace
    QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		SQLiteBackend
    {
    public:
        sqlite3*
			database_handle;

        SQLiteBackend(
            sqlite3*
				raw_database
        );

		SQLiteBackend();

        ~SQLiteBackend();

        SQLiteBackend(
            const SQLiteBackend&
                instance
        ) = delete;
        
        SQLiteBackend& operator = (
            const SQLiteBackend&
                instance
        ) = delete;

        SQLiteBackend(
            SQLiteBackend&&
                instance
        ) noexcept;
        
        SQLiteBackend& operator = (
            SQLiteBackend&&
                instance
        ) noexcept;
    };
}

#endif
