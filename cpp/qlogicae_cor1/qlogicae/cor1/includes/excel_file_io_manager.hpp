#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ExcelFileIoManager \
	)

#include "abstract_batch_operation_configurations.hpp"
#include "excel_file_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	enum class
		ExcelFileIoBatchOperation :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_ENUM_INHERITED_TYPE
    {
		IS_FILE_VALID,

        QLOGICAE_COR1__BASE__HPP_CPP__ENUM_CONSTANTS
    };

	struct
		ExcelFileIoBatchOperationConfigurations :
			public AbstractBatchOperationConfigurations<ExcelFileIoBatchOperation>
	{
	public:		
		
	};

    class
		ExcelFileIoManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ExcelFileIoManagerConfigurations>
    {
    public:		
		ExcelFileIoManager();

		std::unordered_map<std::string, std::any>
			execute_batch_operations(
				const std::unordered_map<std::string, ExcelFileIoBatchOperationConfigurations>&
					batch_operations
			);

		bool
			is_file_valid(
				const std::string&
					file_path
			);

		bool
			is_worksheet_found(
				const std::string&
					file_path,
				const std::string&
					worksheet_name
			);

		bool
			create_worksheet(
				const std::string&
					file_path,
				const std::string&
					worksheet_name
			);

		bool
			copy_worksheet(
				const std::string&
					file_path,
				const std::string&
					from_worksheet_name,
				const std::string&
					to_worksheet_name
			);

		bool
			clear_worksheet(
				const std::string&
					file_path,
				const std::string&
					worksheet_name
			);

		bool
			remove_worksheet(
				const std::string&
					file_path,
				const std::string&
					worksheet_name
			);

		std::string
			get_cell_value(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::string&
					coordinate
			);

		std::unordered_map<std::string, std::string>
			get_cell_values(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::vector<std::string>&
					coordinates
			);

		std::unordered_map<std::string, std::string>
			get_cell_values(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::string&
					from_coordinate,
				const std::string&
					to_coordinate
			);

		bool
			set_cell_value(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::string&
					coordinate,
				const std::string&
					value
			);

		bool
			set_cell_values(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::unordered_map<std::string, std::string>&
					values
			);

		bool
			set_cell_values(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::string&
					from_coordinate,
				const std::string&
					to_coordinate,
				const std::string&
					value
			);

		bool
			clear_cell_value(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::string&
					coordinate
			);

		bool
			clear_cell_values(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::vector<std::string>&
					coordinates
			);

		bool
			clear_cell_values(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::string&
					from_coordinate,
				const std::string&
					to_coordinate
			);

		bool
			is_file_valid();

		bool
			is_worksheet_found(
				const std::string&
					worksheet_name
			);

		bool
			create_worksheet(
				const std::string&
					worksheet_name
			);

		bool
			copy_worksheet(
				const std::string&
					from_worksheet_name,
				const std::string&
					to_worksheet_name
			);

		bool
			clear_worksheet(
				const std::string&
					worksheet_name
			);

		bool
			remove_worksheet(
				const std::string&
					worksheet_name
			);

		std::string
			get_cell_value(
				const std::string&
					coordinate
			);

		std::unordered_map<std::string, std::string>
			get_cell_values(
				const std::vector<std::string>&
					coordinates
			);

		std::unordered_map<std::string, std::string>
			get_cell_values(
				const std::string&
					from_coordinate,
				const std::string&
					to_coordinate
			);

		bool
			set_cell_value(
				const std::string&
					coordinate,
				const std::string&
					value
			);

		bool
			set_cell_values(
				const std::unordered_map<std::string, std::string>&
					values
			);

		bool
			set_cell_values(
				const std::string&
					from_coordinate,
				const std::string&
					to_coordinate,
				const std::string&
					value
			);

		bool
			clear_cell_value(
				const std::string&
					coordinate
			);

		bool
			clear_cell_values(
				const std::vector<std::string>&
					coordinates
			);

		bool
			clear_cell_values(
				const std::string&
					from_coordinate,
				const std::string&
					to_coordinate
			);
    };
}

#endif
