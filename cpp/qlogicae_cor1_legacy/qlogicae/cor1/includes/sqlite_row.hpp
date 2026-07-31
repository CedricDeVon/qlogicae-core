#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteRow \
	)

#include "sqlite_exception.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	using SQLiteValue =
		std::variant<
			std::nullptr_t,
			int64_t,
			double,
			std::string
		>;

	class SQLiteRow;

    class SQLiteRow
    {
    public:
        sqlite3_stmt*
			statement;
        
		std::vector<SQLiteValue>
			values;

        mutable std::unordered_map<std::string, int>
			column_name_to_index;

        SQLiteRow(
            sqlite3_stmt*
				raw_statement
        );

		SQLiteRow
			materialize();

        template<typename Type> Type
			get(
				int
					column_index
			);

        template<typename Type> Type
			get(
				const std::string&
					column_name
			);

        int
			get_column_count();

        std::string
			get_column_name(
				int
					column_index
			);

        int
			get_index(
				const std::string&
					column_name
			);
    };
}

#endif

