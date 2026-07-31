#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonTextManager \
	)

#include "json_text_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		JsonTextManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<JsonTextManagerConfigurations>
    {
    public:		
		JsonTextManager();

		bool
			is_text_valid(
				const std::string&
					json_text
			);

		bool
			is_key_path_valid(
				const std::string&
					json_text,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		std::string
			get_raw_json(
				const std::string&
					json_text,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		std::string
			get_string(
				const std::string&
					json_text,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		double
			get_double(
				const std::string&
					json_text,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		bool
			get_boolean(
				const std::string&
					json_text,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		std::nullptr_t
			get_null(
				const std::string&
					json_text,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		bool
			is_text_valid();

		bool
			is_key_path_valid(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		std::string
			get_raw_json(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		std::string
			get_string(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		double
			get_double(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		bool
			get_boolean(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		std::nullptr_t
			get_null(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);
    };
}

#endif
