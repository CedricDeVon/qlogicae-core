#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteException \
	)

#include "../includes/sqlite_exception.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    SQLiteException
		::SQLiteException(
				const std::string&
				message_value,
            const int
				error_code_value,
            const int
				extended_code_value
		) : std::runtime_error(
				message_value
			)
    {
		error_code =
			error_code_value;

		extended_code =
			extended_code_value;
    }

	SQLiteException
		::SQLiteException() :
			std::runtime_error(
				"SQLiteException"
			)
    {
		error_code =
			0;

		extended_code =
			0;
    }
}

#endif

