#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		YamlFileIoManager \
	)

#include "abstract_batch_operation_configurations.hpp"
#include "yaml_file_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	enum class
		YamlFileIoBatchOperation :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_ENUM_INHERITED_TYPE
    {
		IS_FILE_VALID,

		GET_URI,

        QLOGICAE_COR1__BASE__HPP_CPP__ENUM_CONSTANTS
    };

	struct
		YamlFileIoBatchOperationConfigurations :
			public AbstractBatchOperationConfigurations<YamlFileIoBatchOperation>
	{
	public:		
		
	};

	class
		YamlFileIoManager:
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<YamlFileIoManagerConfigurations>
	{
	public:
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		YamlFileIoManager();

		std::unordered_map<std::string, std::any>
			execute_batch_operations(
				const std::unordered_map<std::string, YamlFileIoBatchOperationConfigurations>&
					batch_operations
			);

		YAML::Node
			traverse_to_parent_node(
				YAML::Node root,
				const std::vector<std::variant<std::string, size_t>>& key_path
			);

		YAML::Node
			safe_traverse_tree(
				const YAML::Node& node,
				const std::vector<std::variant<std::string, size_t>>& key_path
			);

		YAML::Node
			traverse_tree(
				YAML::Node
					node,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			);

		YAML::Node
			resolve_or_create(
				YAML::Node root,
					const std::vector<std::variant<std::string, size_t>>&
						key_path
			);
		
		YAML::Node
			walk_root_node(
				YAML::Node& root,
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				bool
					create
			);
		
		YAML::Node
			load(
				const std::string&
					file_path
			);

		bool
			save(
				const std::string&
					file_path,
				const YAML::Node&
					node
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
			get_raw_yaml(
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
			set_raw_yaml(
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
			append_raw_yaml(
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
			get_raw_yaml(
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
			set_raw_yaml(
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
			append_raw_yaml(
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
	};
}

#endif

