#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CsvFileIoManager \
	)

#include "csv_file_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		CsvFileIoManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<CsvFileIoManagerConfigurations>
    {
    public:		
		CsvFileIoManager();

		std::unordered_map<std::string, std::vector<std::string>>
			read(
				const std::string&
					file_path
			);

		bool
			write(
				const std::string&
					file_path,
				const std::unordered_map<std::string, std::vector<std::string>>&
					values
			);

		bool
			write(
				const std::string&
					file_path,
				const std::vector<std::string>&
					column_names
			);

		bool
			is_valid(
				const std::string&
					file_path

			);

		bool
			is_column_name_found(
				const std::string&
					file_path,
				const std::string&
					value
			);

		bool
			is_row_index_found(
				const std::string&
					file_path,
				const size_t&
					value
		);

		bool
			is_cell_coordinate_valid(
				const std::string&
					file_path,
				const std::string&
					column_name,
				const size_t&
					row_index
			);

		size_t
			get_column_size(
				const std::string&
					file_path
			);

		size_t
			get_row_size(
				const std::string&
					file_path
			);

		size_t
			get_empty_cell_count(
				const std::string&
					file_path
			);

		size_t
			get_non_empty_cell_count(
				const std::string&
					file_path
			);

		std::vector<std::string>
			get_column_names(
				const std::string&
					file_path
			);

		std::string
			get_cell(
				const std::string&
					file_path,
				const std::string&
					column_name,
				const size_t&
					row_index
			);

		std::unordered_map<std::string, std::string>
			get_column(
				const std::string&
					file_path,
				const std::string&
					column_name
			);

		std::unordered_map<std::string, std::string>
			get_row(
				const std::string&
					file_path,
				const size_t&
					row_index
			);

		std::unordered_map<std::string, std::vector<std::string>>
			get_table(
				const std::string&
					file_path
			);

		bool
			set_cell(
				const std::string&
					file_path,
				const std::string&
					column_name,
				const size_t&
					row_index,
				const std::string&
					value
			);

		bool
			set_column(
				const std::string&
					file_path,
				const std::string&
					column,
				const std::unordered_map<size_t, std::string>&
					values
			);

		bool
			set_column(
				const std::string&
					file_path,
				const std::string&
					column,
				const std::vector<std::string>&
					values
			);

		bool
			set_row(
				const std::string&
					file_path,				
				const size_t&
					row_index,
				const std::unordered_map<std::string, std::string>&
					values
			);

		bool
			set_row(
				const std::string&
					file_path,				
				const size_t&
					row_index,
				const std::vector<std::string>&
					values
			);

		bool
			set_table(
				const std::string&
					file_path,				
				const std::unordered_map<std::string, std::vector<std::string>>&
					values
			);

		bool
			append_column(
				const std::string&
					file_path,				
				const std::string&
					column_name,
				const std::unordered_map<size_t, std::string>&
					values
			);

		bool
			append_column(
				const std::string&
					file_path,				
				const std::string&
					column_name,
				const std::vector<std::string>&
					values
			);

		bool
			append_row(
				const std::string&
					file_path,				
				const std::unordered_map<std::string, std::string>&
					values
			);

		bool
			append_row(
				const std::string&
					file_path,				
				const std::vector<std::string>&
					values
			);

		bool
			insert_column(
				const std::string&
					file_path,
				const std::string&
					column_name,
				const std::unordered_map<size_t, std::string>&
					values
			);

		bool
			insert_column(
				const std::string&
					file_path,
				const std::string&
					column_name,
				const std::vector<std::string>&
					values
			);

		bool
			insert_row(
				const std::string&
					file_path,
				const size_t&
					row_index,
				const std::unordered_map<std::string, std::string>&
					values
			);

		bool
			insert_row(
				const std::string&
					file_path,
				const size_t&
					row_index,
				const std::vector<std::string>&
					values
			);

		bool
			remove_column(
				const std::string&
					file_path,				
				const std::string&
					column_name
			);

		bool
			remove_row(
				const std::string&
					file_path,				
				const size_t&
					row_index
			);



		std::unordered_map<std::string, std::vector<std::string>>
			read();

		bool
			write(				
				const std::unordered_map<std::string, std::vector<std::string>>&
					values
			);

		bool
			write(				
				const std::vector<std::string>&
					column_names
			);

		bool
			is_valid();

		bool
			is_column_name_found(
				const std::string&
					value
			);

		bool
			is_row_index_found(
				const size_t&
					value
		);

		bool
			is_cell_coordinate_valid(
				const std::string&
					column_name,
				const size_t&
					row_index
			);

		size_t
			get_column_size();

		size_t
			get_row_size();

		size_t
			get_empty_cell_count();

		size_t
			get_non_empty_cell_count();

		std::vector<std::string>
			get_column_names();

		std::string
			get_cell(
				const std::string&
					column_name,
				const size_t&
					row_index
			);

		std::unordered_map<std::string, std::string>
			get_column(
				const std::string&
					column_name
			);

		std::unordered_map<std::string, std::string>
			get_row(
				const size_t&
					row_index
			);

		std::unordered_map<std::string, std::vector<std::string>>
			get_table();

		bool
			set_cell(
				const std::string&
					column_name,
				const size_t&
					row_index,
				const std::string&
					value
			);

		bool
			set_column(
				const std::string&
					column,
				const std::unordered_map<size_t, std::string>&
					values
			);

		bool
			set_column(
				const std::string&
					column,
				const std::vector<std::string>&
					values
			);

		bool
			set_row(				
				const size_t&
					row_index,
				const std::unordered_map<std::string, std::string>&
					values
			);

		bool
			set_row(				
				const size_t&
					row_index,
				const std::vector<std::string>&
					values
			);

		bool
			set_table(				
				const std::unordered_map<std::string, std::vector<std::string>>&
					values
			);

		bool
			append_column(				
				const std::string&
					column_name,
				const std::unordered_map<size_t, std::string>&
					values
			);

		bool
			append_column(				
				const std::string&
					column_name,
				const std::vector<std::string>&
					values
			);

		bool
			append_row(				
				const std::unordered_map<std::string, std::string>&
					values
			);

		bool
			append_row(				
				const std::vector<std::string>&
					values
			);

		bool
			insert_column(
				const std::string&
					column_name,
				const std::unordered_map<size_t, std::string>&
					values
			);

		bool
			insert_column(
				const std::string&
					column_name,
				const std::vector<std::string>&
					values
			);

		bool
			insert_row(
				const size_t&
					row_index,
				const std::unordered_map<std::string, std::string>&
					values
			);

		bool
			insert_row(
				const size_t&
					row_index,
				const std::vector<std::string>&
					values
			);

		bool
			remove_column(				
				const std::string&
					column_name
			);

		bool
			remove_row(				
				const size_t&
					row_index
			);
    };
}

#endif
