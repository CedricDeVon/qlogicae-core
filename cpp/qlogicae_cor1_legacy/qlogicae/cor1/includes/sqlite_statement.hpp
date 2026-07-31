#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SQLiteStatement \
	)

#include "sqlite_row.hpp"
#include "sqlite_backend.hpp"
#include "sqlite_exception.hpp"
#include "sqlite_statement_data.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class SQLiteStatement
    {
    public:
		bool
			finished;

		bool
			has_row_state;

		std::shared_ptr<SQLiteBackend>
			backend;

		std::unique_ptr<SQLiteStatementData>
			statement;

		mutable std::unordered_map<std::string, int>
			parameter_name_to_index;

        SQLiteStatement(
            std::shared_ptr<SQLiteBackend>
				backend_instance,
            const std::string&
				sql_text
        );

        SQLiteStatement(
			const std::string&
				file_path,
            const std::string&
				sql_text
        );

		SQLiteStatement();

		int
			resolve_named_index(
				const std::string& name
			);

        bool
			step();

        bool
			reset();

        bool
			clear_bindings();

        bool
			is_valid();

        std::optional<SQLiteRow>
			row();

        std::vector<SQLiteRow>
			query();

        SQLiteStatement&
			bind(
				int
					index,
				int
					value
			);

        SQLiteStatement&
			bind(
				int
					index,
				bool
					value
			);

        SQLiteStatement&
			bind(
				int
					index,
				float
					value
			);

        SQLiteStatement&
			bind(
				int
					index,
				double
					value
			);

        SQLiteStatement&
			bind(
				int
					index,
				int64_t
					value
			);

        SQLiteStatement&
			bind(
				int
					index,
				std::nullptr_t
			);

        SQLiteStatement&
			bind(
				int
					index,
				const char*
					value
			);

        SQLiteStatement&
			bind(
				int
					index,
				const std::string&
					value
			);

        SQLiteStatement&
			bind(
				const std::string&
					name,
				int
					value
			);

        SQLiteStatement&
			bind(
				const std::string&
					name,
				bool
					value
			);

        SQLiteStatement&
			bind(
				const std::string&
					name,
				float
					value
			);

        SQLiteStatement&
			bind(
				const std::string&
					name,
				double
					value
			);

        SQLiteStatement&
			bind(
				const std::string&
					name,
				int64_t
					value
			);

        SQLiteStatement&
			bind(
				const std::string&
					name,
				std::nullptr_t
			);

        SQLiteStatement&
			bind(
				const std::string&
					name,
				const std::string&
					value
			);

        SQLiteStatement&
			bind(
				const std::string&
					name,
				const char*
					value
			);

        template<typename Type> SQLiteStatement&
			bind(
				int
					index,
				const std::optional<Type>&
					value        
			);

        template<typename Type> SQLiteStatement&
			bind(
				const std::string&
					name,
				const std::optional<Type>&
					value
			);
    };	
}

#endif

