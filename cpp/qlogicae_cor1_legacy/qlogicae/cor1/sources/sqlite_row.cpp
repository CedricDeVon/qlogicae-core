#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteRow \
	)

#include "../includes/sqlite_row.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	SQLiteRow
		::SQLiteRow(
			sqlite3_stmt*
				raw_statement
		) :
			statement(
				raw_statement
			)
	{

	}

	void
        validate_statement(
            sqlite3_stmt*
                statement
        )
    {
        if (statement == nullptr)
        {
            throw SQLiteException(
                "Invalid Statement",
                -1,
                -1
            );
        }
    }

    void
        validate_column_index(
            sqlite3_stmt*
                statement,
            int
                column_index
        )
    {
        validate_statement(statement);

        int column_count =
            sqlite3_column_count(
                statement
            );

        if (
            column_index < 0 ||
            column_index >= column_count
        )
        {
            throw SQLiteException(
                "Invalid Column Index",
                -1,
                -1
            );
        }
    }

    void
        validate_column_type(
            sqlite3_stmt*
                statement,
            int
                column_index,
            int
                expected_type
        )
    {
        validate_column_index(
            statement,
            column_index
        );

        int type =
            sqlite3_column_type(
                statement,
                column_index
            );

        if (type == SQLITE_NULL)
        {
            throw SQLiteException(
                "Column Should Not Be Null",
                -1,
                -1
            );
        }

        if (type != expected_type)
        {
            throw SQLiteException(
                "Column Type Mismatch",
                -1,
                -1
            );
        }
    }

    template<> int
		SQLiteRow::get<int>(
			int
				column_index
		)
    {
		validate_column_type(
			statement,
			column_index,
			SQLITE_INTEGER
		);

		return sqlite3_column_int(
			statement,
			column_index
		);
    }

    template<> double
		SQLiteRow
			::get<double>(
				int
					column_index
			)
    {
		validate_column_type(
			statement,
			column_index,
			SQLITE_FLOAT
		);

		return sqlite3_column_double(
			statement,
			column_index
		);
    }

    template<> float
		SQLiteRow
			::get<float>(
				int
					column_index
			)
    {
        return
			static_cast<float>(
				get<double>(
					column_index
				)
			);
    }

    template<> bool
		SQLiteRow
			::get<bool>(
				int
					column_index
			)
    {
		validate_column_type(
			statement,
			column_index,
			SQLITE_INTEGER
		);

		return sqlite3_column_int(
			statement,
			column_index
		) != 0;
    }

    template<> std::string
		SQLiteRow
			::get<std::string>(
				int
					column_index
			)
    {
		validate_column_index(
            statement,
            column_index
        );

        int type =
            sqlite3_column_type(
                statement,
                column_index
            );

        if (type == SQLITE_NULL)
        {
            return "";
        }

        if (type != SQLITE_TEXT)
        {
            throw SQLiteException(
                "Column Type Mismatch",
                -1,
                -1
            );
        }

        const unsigned char*
            text =
                sqlite3_column_text(
                    statement,
                    column_index
                );

        if (text == nullptr)
        {
            return "";
        }

        return std::string(
            reinterpret_cast<
                const char*
            >(text)
        );
    }

    template<> int
		SQLiteRow
			::get<int>(
				const std::string&
					column_name
			)
    {
		return get<int>(
			get_index(
				column_name
			)
		);
    }

	template<> double
        SQLiteRow::get<double>(
            const std::string&
                column_name
        )
    {
        return get<double>(
            get_index(
                column_name
            )
        );
    }

    template<> float
        SQLiteRow::get<float>(
            const std::string&
                column_name
        )
    {
        return get<float>(
            get_index(
                column_name
            )
        );
    }

    template<> bool
        SQLiteRow::get<bool>(
            const std::string&
                column_name
        )
    {
        return get<bool>(
            get_index(
                column_name
            )
        );
    }

    template<> std::string
		SQLiteRow
			::get<std::string>(
				const std::string&
					column_name
			)
    {
        return
			get<std::string>(
				get_index(
					column_name
				)
			);
    }

	int
		SQLiteRow
			::get_column_count()
	{
		validate_statement(statement);

		return
			sqlite3_column_count(
				statement
			);
	}

	std::string
		SQLiteRow
			::get_column_name(
				int
					column_index
			)
	{
        validate_statement(statement);

        int column_count =
            sqlite3_column_count(
                statement
            );

        if (
            column_index < 0 ||
            column_index >= column_count
            )
        {
            return "";
        }

        const char*
            name =
            sqlite3_column_name(
                statement,
                column_index
            );

        return
            name ?
            std::string(name) :
            "";
	}

	int
		SQLiteRow
			::get_index(
				const std::string&
					column_name
			)
	{
        validate_statement(statement);

        auto iterator =
            column_name_to_index.find(
                column_name
            );

        if (
            iterator !=
            column_name_to_index.end()
            )
        {
            return iterator->second;
        }

        int count =
            get_column_count();

        for(
            int index = 0;
            index < count;
            ++index
            )
        {
            if (
                get_column_name(index) ==
                column_name
                )
            {
                column_name_to_index[
                    column_name
                ] = index;

                return index;
            }
        }

        throw SQLiteException(
            "Column Name Not Found",
            -1,
            -1
        );    
	}
}

#endif
