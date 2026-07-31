#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonFileIoManager \
	)

#include "abstract_batch_operation_configurations.hpp"
#include "json_file_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	enum class
		JsonFileIoBatchOperation :
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
		JsonFileIoBatchOperationConfigurations :
			public AbstractBatchOperationConfigurations<JsonFileIoBatchOperation>
	{
	public:		
		
	};

    class
		JsonFileIoManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<JsonFileIoManagerConfigurations>
    {
    public:		
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_3
		);

		JsonFileIoManager();

		std::unordered_map<std::string, std::any>
			execute_batch_operations(
				const std::unordered_map<std::string, JsonFileIoBatchOperationConfigurations>&
					batch_operations
			);

		bool
			is_valid(
				const std::string&
					file_path
			);

		bool
			is_key_path_valid(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		std::string
			get_raw_json(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		std::string
			get_string(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		double
			get_double(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		bool
			get_boolean(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		std::nullptr_t
			get_null(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		bool
			set_raw_json(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				const std::string&
					value
			);

		bool
			set_string(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				const std::string&
					value
			);

		bool
			append_raw_json(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				const std::string&
					value
			);

		bool
			append_string(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				const std::string&
					value
			);

		bool
			remove_value(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);




		bool
			is_valid();

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

		bool
			set_raw_json(
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				const std::string&
					value
			);

		bool
			set_string(
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				const std::string&
					value
			);

		bool
			append_raw_json(
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				const std::string&
					value
			);

		bool
			append_string(
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				const std::string&
					value
			);

		bool
			remove_value(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		rapidjson::Value*
			traverse(
				rapidjson::Document&
					document,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);
    };
}

#endif
