#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteDatabaseManager \
	)

#include "../includes/sqlite_database_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{	
    

}

#endif

/*

	SQLiteDatabaseManager
		::SQLiteDatabaseManager()
	{
		construct();
	}

	SQLiteDatabaseManager
		::~SQLiteDatabaseManager()
	{
		destruct();
	}

	bool
		SQLiteDatabaseManager
			::construct()
	{
		try
		{
			return
				true;
		}
		catch
		(
			QLOGICAE_COR_V1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR_V1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	bool
		SQLiteDatabaseManager
			::destruct()
	{
		try
		{
			return
				true;
		}
		catch
		(
			QLOGICAE_COR_V1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR_V1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	SQLiteStatement
		SQLiteDatabaseManager
			::setup_statement(
				const std::string&
					file_path,
				const std::string&
					sql_text
			)
	{
		try
		{
			return
				SQLiteStatement(
					file_path,
					sql_text
				);
		}
		catch
		(
			QLOGICAE_COR_V1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR_V1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				SQLiteStatement(
					configurations
						.file_path,
					""
				)
			);
		}
	}

	SQLiteStatement
		SQLiteDatabaseManager
			::setup_statement(
				const std::string&
					sql_text
			)
	{
		try
		{
			return
				SQLiteStatement(
					configurations
						.file_path,
					sql_text
				);
		}
		catch
		(
			QLOGICAE_COR_V1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR_V1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				SQLiteStatement(
					configurations
						.file_path,
					""
				)
			);
		}
	}

	int64_t
		SQLiteDatabaseManager
			::last_insert_rowid()
	{
		try
		{
			if
			(
				configurations
					.is_runtime_execution_disabled_for_feature_handling()
			)
			{
				return
					0;
			}

			boost::unique_lock<boost::mutex>
				mutex_lock;
			if (configurations.is_thread_safety_enabled_for_feature_handling())
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						feature_handling_mutex_1
					);
			}

			return
				sqlite3_last_insert_rowid(
					backend
						->database_handle
				);
		}
		catch
		(
			QLOGICAE_COR_V1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR_V1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

*/
