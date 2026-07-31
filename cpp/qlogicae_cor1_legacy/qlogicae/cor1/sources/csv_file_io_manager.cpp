#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CsvFileIoManager \
	)

#include "../includes/csv_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	CsvFileIoManager
		::CsvFileIoManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<CsvFileIoManagerConfigurations>()
    {
        
    }
	
	std::unordered_map<std::string, std::vector<std::string>>
		CsvFileIoManager
			::read(
				const std::string&
					file_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			std::unordered_map<std::string, std::vector<std::string>> result;
			auto names = document.GetColumnNames();
			auto rows = document.GetRowCount();
			for (const auto& name : names)
			{
				std::vector<std::string> column;
				column.reserve(rows);
				for (size_t r = 0; r < rows; ++r)
				{
					column.push_back(document.GetCell<std::string>(name, r));
				}
				result[name] = std::move(column);
			}

			return result;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::write(
				const std::string&
					file_path,
				const std::unordered_map<std::string, std::vector<std::string>>&
					values
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!values.size()
			);

			size_t row_count = 0;
			for (const auto& [_, col] : values)
			{
				if (col.size() > row_count)
				{
					row_count = col.size();
				}
			}

			std::vector<std::string> column_names;
			for (const auto& [name, _] : values)
			{
				column_names.push_back(name);
			}

			rapidcsv::Document document(
				file_path,
				rapidcsv::LabelParams(0, -1)
			);

			for (size_t i = 0; i < column_names.size(); ++i)
			{
				const auto& name = column_names[i];
				const auto& col_values = values.at(name);
				std::vector<std::string> column(row_count, "");
				for (size_t r = 0; r < col_values.size(); ++r)
				{
					column[r] = col_values[r];
				}
				document.InsertColumn(i, column, name);
			}

			document.Save(file_path);

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::write(
				const std::string&
					file_path,
				const std::vector<std::string>&
					column_names
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!column_names.size()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			for (size_t i = 0; i < column_names.size(); ++i)
			{
				std::vector<std::string> empty_column;
				document.InsertColumn(i, empty_column, column_names[i]);
			}
			document.Save(file_path);

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::is_valid(
				const std::string&
					file_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			document.GetColumnCount();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::is_column_name_found(
				const std::string&
					file_path,
				const std::string&
					value
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			auto names = document.GetColumnNames();
			for (const auto& name : names)
			{
				if (name == value)
				{
					return true;
				}
			}
			return false;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::is_row_index_found(
				const std::string&
					file_path,
				const size_t&
					value
		)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));

			return value < document.GetRowCount();
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::is_cell_coordinate_valid(
				const std::string&
					file_path,
				const std::string&
					column_name,
				const size_t&
					row_index
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				column_name.empty() ||
				row_index < 0
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			auto names = document.GetColumnNames();
			bool found = false;
			for (const auto& name : names)
			{
				if (name == column_name)
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				return false;
			}
			return row_index < document.GetRowCount();
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	size_t
		CsvFileIoManager
			::get_column_size(
				const std::string&
					file_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));

			return document.GetColumnCount();
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	size_t
		CsvFileIoManager
			::get_row_size(
				const std::string&
					file_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));

			return document.GetRowCount();
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	size_t
		CsvFileIoManager
			::get_empty_cell_count(
				const std::string&
					file_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			size_t count = 0;
			auto rows = document.GetRowCount();
			auto cols = document.GetColumnCount();
			for (size_t r = 0; r < rows; ++r)
			{
				for (size_t c = 0; c < cols; ++c)
				{
					if (document.GetCell<std::string>(c, r).empty())
					{
						++count;
					}
				}
			}

			return count;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	size_t
		CsvFileIoManager
			::get_non_empty_cell_count(
				const std::string&
					file_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			size_t count = 0;
			auto rows = document.GetRowCount();
			auto cols = document.GetColumnCount();
			for (size_t r = 0; r < rows; ++r)
			{
				for (size_t c = 0; c < cols; ++c)
				{
					if (!document.GetCell<std::string>(c, r).empty())
					{
						++count;
					}
				}
			}

			return count;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::vector<std::string>
		CsvFileIoManager
			::get_column_names(
				const std::string&
					file_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));

			return document.GetColumnNames();
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::string
		CsvFileIoManager
			::get_cell(
				const std::string&
					file_path,
				const std::string&
					column_name,
				const size_t&
					row_index
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				column_name.empty() ||
				row_index < 0
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			return document.GetCell<std::string>(column_name, row_index);
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::unordered_map<std::string, std::string>
		CsvFileIoManager
			::get_column(
				const std::string&
					file_path,
				const std::string&
					column_name
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				column_name.empty()
			);

			try
			{
				rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
				std::unordered_map<std::string, std::string> result;
				auto rows = document.GetRowCount();
				for (size_t r = 0; r < rows; ++r)
				{
					result[std::to_string(r)] =
						document.GetCell<std::string>(column_name, r);
				}

				return result;
			}
			catch (...)
			{
				return
					{};
			}			
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::unordered_map<std::string, std::string>
		CsvFileIoManager
			::get_row(
				const std::string&
					file_path,
				const size_t&
					row_index
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				row_index < 0
			);

			try
			{
				rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
				std::unordered_map<std::string, std::string> result;
				auto names = document.GetColumnNames();
				for (const auto& name : names)
				{
					result[name] =
						document.GetCell<std::string>(name, row_index);
				}

				return result;
			}
			catch (...)
			{
				return
					{};
			}
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::unordered_map<std::string, std::vector<std::string>>
		CsvFileIoManager
			::get_table(
				const std::string&
					file_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			std::unordered_map<std::string, std::vector<std::string>> result;
			auto names = document.GetColumnNames();
			auto rows = document.GetRowCount();
			for (const auto& name : names)
			{
				std::vector<std::string> column;
				for (size_t r = 0; r < rows; ++r)
				{
					column.push_back(
						document.GetCell<std::string>(name, r)
					);
				}
				result[name] = column;
			}
			return result;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::set_cell(
				const std::string&
					file_path,
				const std::string&
					column_name,
				const size_t&
					row_index,
				const std::string&
					value
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				column_name.empty() ||
				row_index < 0
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			document.SetCell(column_name, row_index, value);
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::set_column(
				const std::string&
					file_path,
				const std::string&
					column_name,
				const std::unordered_map<size_t, std::string>&
					values
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				column_name.empty() ||
				!values.size()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			for (const auto& [index, value] : values)
			{
				if (index < document.GetRowCount())
				{
					document.SetCell(column_name, index, value);
				}
			}
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::set_column(
				const std::string&
					file_path,
				const std::string&
					column_name,
				const std::vector<std::string>&
					values
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				column_name.empty() ||
				!values.size()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			auto rows = document.GetRowCount();
			for (size_t i = 0; i < values.size() && i < rows; ++i)
			{
				document.SetCell(column_name, i, values[i]);
			}
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::set_row(
				const std::string&
					file_path,				
				const size_t&
					row_index,
				const std::unordered_map<std::string, std::string>&
					values
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				row_index < 0 ||
				!values.size()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			for (const auto& [column, value] : values)
			{
				document.SetCell(column, row_index, value);
			}
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::set_row(
				const std::string&
					file_path,				
				const size_t&
					row_index,
				const std::vector<std::string>&
					values
			)
	{
		try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				row_index < 0 ||
				!values.size()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			auto names = document.GetColumnNames();
			for (size_t i = 0; i < values.size() && i < names.size(); ++i)
			{
				document.SetCell(names[i], row_index, values[i]);
			}
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::set_table(
				const std::string&
					file_path,				
				const std::unordered_map<std::string, std::vector<std::string>>&
					values
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!values.size()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			for (const auto& [column, column_values] : values)
			{
				for (size_t i = 0;
					i < column_values.size() &&
					i < document.GetRowCount();
					++i)
				{
					document.SetCell(column, i, column_values[i]);
				}
			}
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::append_column(
				const std::string&
					file_path,				
				const std::string&
					column_name,
				const std::unordered_map<size_t, std::string>&
					values
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				column_name.empty() ||
				!values.size()
			);
	
			try
			{
				rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
				std::vector<std::string> column(
					document.GetRowCount(), ""
				);
				for (const auto& [index, value] : values)
				{
					if (index < column.size())
					{
						column[index] = value;
					}
				}
				document.InsertColumn(
					document.GetColumnCount(),
					column,
					column_name
				);
				document.Save();

				return
					true;	
			}
			catch (...)
			{
				return
					false;
			}				
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::append_column(
				const std::string&
					file_path,				
				const std::string&
					column_name,
				const std::vector<std::string>&
					values
			)
	{
		try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				column_name.empty() ||
				!values.size()
			);

			try
			{
				rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
				document.InsertColumn(
					document.GetColumnCount(),
					values,
					column_name
				);
				document.Save();

				return
					true;	
			}
			catch (...)
			{
				return
					false;	
			}										
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::append_row(
				const std::string&
					file_path,				
				const std::unordered_map<std::string, std::string>&
					values
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!values.size()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			std::vector<std::string> row(
				document.GetColumnCount(), ""
			);
			auto names = document.GetColumnNames();
			for (size_t i = 0; i < names.size(); ++i)
			{
				if (values.contains(names[i]))
				{
					row[i] = values.at(names[i]);
				}
			}
			document.InsertRow(
				document.GetRowCount(),
				row
			);
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::append_row(
				const std::string&
					file_path,				
				const std::vector<std::string>&
					values
			)
	{
		try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!values.size()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			document.InsertRow(
				document.GetRowCount(),
				values
			);
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::insert_column(
				const std::string&
					file_path,
				const std::string&
					column_name,
				const std::unordered_map<size_t, std::string>&
					values
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				column_name.empty() ||
				!values.size()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			std::vector<std::string> column(
				document.GetRowCount(), ""
			);
			for (const auto& [index, value] : values)
			{
				if (index < column.size())
				{
					column[index] = value;
				}
			}
			document.InsertColumn(0, column, column_name);
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::insert_column(
				const std::string&
					file_path,
				const std::string&
					column_name,
				const std::vector<std::string>&
					values
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				column_name.empty() ||
				!values.size()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			document.InsertColumn(0, values, column_name);
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::insert_row(
				const std::string&
					file_path,
				const size_t&
					row_index,
				const std::unordered_map<std::string, std::string>&
					values
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				row_index < 0 ||
				!values.size()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			std::vector<std::string> row(
				document.GetColumnCount(), ""
			);
			auto names = document.GetColumnNames();
			for (size_t i = 0; i < names.size(); ++i)
			{
				if (values.contains(names[i]))
				{
					row[i] = values.at(names[i]);
				}
			}
			document.InsertRow(row_index, row);
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::insert_row(
				const std::string&
					file_path,
				const size_t&
					row_index,
				const std::vector<std::string>&
					values
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				row_index < 0 ||
				!values.size()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			document.InsertRow(row_index, values);
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::remove_column(
				const std::string&
					file_path,				
				const std::string&
					column_name
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				column_name.empty()
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			auto names = document.GetColumnNames();
			for (size_t i = 0; i < names.size(); ++i)
			{
				if (names[i] == column_name)
				{
					document.RemoveColumn(i);
					document.Save();
					return true;
				}
			}

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		CsvFileIoManager
			::remove_row(
				const std::string&
					file_path,				
				const size_t&
					row_index
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				row_index < 0
			);

			rapidcsv::Document document(file_path, rapidcsv::LabelParams(0, -1));
			document.RemoveRow(row_index);
			document.Save();

            return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::unordered_map<std::string, std::vector<std::string>>
		CsvFileIoManager
			::read()
	{
		return
			read(
				configurations
					.file_path
			);
	}

	bool
		CsvFileIoManager
			::write(				
				const std::unordered_map<std::string, std::vector<std::string>>&
					values
			)
	{
		return
			write(
				configurations
					.file_path,
				values
			);
	}

	bool
		CsvFileIoManager
			::write(				
				const std::vector<std::string>&
					column_names
			)
	{
		return
			write(
				configurations
					.file_path,
				column_names
			);
	}
	
	bool
		CsvFileIoManager
			::is_valid()
	{
		return
			is_valid(
				configurations
					.file_path
			);
	}

	bool
		CsvFileIoManager
			::is_column_name_found(
				const std::string&
					value
			)
	{
		return
			is_column_name_found(
				configurations
					.file_path,
				value
			);
	}

	bool
		CsvFileIoManager
			::is_row_index_found(
				const size_t&
					value
		)
	{
		return
			is_row_index_found(
				configurations
					.file_path,
				value
			);
	}

	bool
		CsvFileIoManager
			::is_cell_coordinate_valid(
				const std::string&
					column_name,
				const size_t&
					row_index
			)
	{
		return
			is_cell_coordinate_valid(
				configurations
					.file_path,
				column_name,
				row_index
			);
	}

	size_t
		CsvFileIoManager
			::get_column_size()
	{
		return
			get_column_size(
				configurations
					.file_path
			);
	}

	size_t
		CsvFileIoManager
			::get_row_size()
	{
		return
			get_row_size(
				configurations
					.file_path
			);
	}

	size_t
		CsvFileIoManager
			::get_empty_cell_count()
	{
		return
			get_empty_cell_count(
				configurations
					.file_path
			);
	}

	size_t
		CsvFileIoManager
			::get_non_empty_cell_count()
	{
		return
			get_non_empty_cell_count(
				configurations
					.file_path
			);
	}

	std::vector<std::string>
		CsvFileIoManager
			::get_column_names()
	{
		return
			get_column_names(
				configurations
					.file_path
			);
	}

	std::string
		CsvFileIoManager
			::get_cell(
				const std::string&
					column_name,
				const size_t&
					row_index
			)
	{
		return
			get_cell(
				configurations
					.file_path,
				column_name,
				row_index
			);
	}

	std::unordered_map<std::string, std::string>
		CsvFileIoManager
			::get_column(
				const std::string&
					column_name
			)
	{
		return
			get_column(
				configurations
					.file_path,
				column_name
			);
	}

	std::unordered_map<std::string, std::string>
		CsvFileIoManager
			::get_row(
				const size_t&
					row_index
			)
	{
		return
			get_row(
				configurations
					.file_path,
				row_index
			);
	}

	std::unordered_map<std::string, std::vector<std::string>>
		CsvFileIoManager
			::get_table()
	{
		return
			get_table(
				configurations
					.file_path
			);
	}

	bool
		CsvFileIoManager
			::set_cell(
				const std::string&
					column_name,
				const size_t&
					row_index,
				const std::string&
					value
			)
	{
		return
			set_cell(
				configurations
					.file_path,
				column_name,
				row_index,
				value
			);
	}

	bool
		CsvFileIoManager
			::set_column(
				const std::string&
					column_name,
				const std::unordered_map<size_t, std::string>&
					values
			)
	{
		return
			set_column(
				configurations
					.file_path,
				column_name,
				values
			);
	}

	bool
		CsvFileIoManager
			::set_column(
				const std::string&
					column_name,
				const std::vector<std::string>&
					values
			)
	{
		return
			set_column(
				configurations
					.file_path,
				column_name,
				values
			);
	}

	bool
		CsvFileIoManager
			::set_row(				
				const size_t&
					row_index,
				const std::unordered_map<std::string, std::string>&
					values
			)
	{
		return
			set_row(
				configurations
					.file_path,
				row_index,
				values
			);
	}

	bool
		CsvFileIoManager
			::set_row(				
				const size_t&
					row_index,
				const std::vector<std::string>&
					values
			)
	{
		return
			set_row(
				configurations
					.file_path,
				row_index,
				values
			);
	}

	bool
		CsvFileIoManager
			::set_table(				
				const std::unordered_map<std::string, std::vector<std::string>>&
					values
			)
	{
		return
			set_table(
				configurations
					.file_path,
				values
			);
	}

	bool
		CsvFileIoManager
			::append_column(				
				const std::string&
					column_name,
				const std::unordered_map<size_t, std::string>&
					values
			)
	{
		return
			append_column(
				configurations
					.file_path,
				column_name,
				values
			);
	}

	bool
		CsvFileIoManager
			::append_column(				
				const std::string&
					column_name,
				const std::vector<std::string>&
					values
			)
	{
		return
			append_column(
				configurations
					.file_path,
				column_name,
				values
			);
	}

	bool
		CsvFileIoManager
			::append_row(				
				const std::unordered_map<std::string, std::string>&
					values
			)
	{
		return
			append_row(
				configurations
					.file_path,
				values
			);
	}

	bool
		CsvFileIoManager
			::append_row(				
				const std::vector<std::string>&
					values
			)
	{
		return
			append_row(
				configurations
					.file_path,
				values
			);
	}

	bool
		CsvFileIoManager
			::insert_column(
				const std::string&
					column_name,
				const std::unordered_map<size_t, std::string>&
					values
			)
	{
		return
			insert_column(
				configurations
					.file_path,
				column_name,
				values
			);
	}

	bool
		CsvFileIoManager
			::insert_column(
				const std::string&
					column_name,
				const std::vector<std::string>&
					values
			)
	{
		return
			insert_column(
				configurations
					.file_path,
				column_name,
				values
			);
	}

	bool
		CsvFileIoManager
			::insert_row(
				const size_t&
					row_index,
				const std::unordered_map<std::string, std::string>&
					values
			)
	{
		return
			insert_row(
				configurations
					.file_path,
				row_index,
				values
			);
	}

	bool
		CsvFileIoManager
			::insert_row(
				const size_t&
					row_index,
				const std::vector<std::string>&
					values
			)
	{
		return
			insert_row(
				configurations
					.file_path,
				row_index,
				values
			);
	}

	bool
		CsvFileIoManager
			::remove_column(				
				const std::string&
					column_name
			)
	{
		return
			remove_column(
				configurations
					.file_path,
				column_name
			);
	}

	bool
		CsvFileIoManager
			::remove_row(				
				const size_t&
					row_index
			)
	{
		return
			remove_row(
				configurations
					.file_path,
				row_index
			);
	}		
}

#endif
