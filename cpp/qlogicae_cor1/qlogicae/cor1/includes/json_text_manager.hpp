#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonTextManager \
	)

#include "abstract_batch_operation_configurations.hpp"
#include "json_text_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	enum class
		JsonTextBatchOperation :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_ENUM_INHERITED_TYPE
    {		
		IS_FILE_VALID,
		
		IS_KEY_PATH_VALID,
		
		GET_MANY_VALUES,
		
		SET_MANY_VALUES,
		
		APPEND_MANY_VALUES,
		
		REMOVE_MANY_VALUES,

        QLOGICAE_COR1__BASE__HPP_CPP__ENUM_CONSTANTS
    };

	struct
		JsonTextBatchOperationConfigurations :
			public AbstractBatchOperationConfigurations<JsonTextBatchOperation>
	{
	public:		
		
	};

    class
		JsonTextManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<JsonTextManagerConfigurations>
    {
    public:		
		JsonTextManager();

		std::unordered_map<std::string, std::any>
			execute_batch_operations(
				const std::unordered_map<std::string, JsonTextBatchOperationConfigurations>&
					batch_operations
			);

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
