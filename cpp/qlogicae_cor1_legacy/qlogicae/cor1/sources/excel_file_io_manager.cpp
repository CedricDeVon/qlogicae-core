#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ExcelFileIoManager \
	)

#include "../includes/excel_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	ExcelFileIoManager
		::ExcelFileIoManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ExcelFileIoManagerConfigurations>()
    {
        
    }

	bool
		is_valid_coordinate(const std::string& coord)
	{
		static const std::regex coord_regex("^[A-Z]+[1-9][0-9]*$");
		return std::regex_match(coord, coord_regex);
	}

	bool
		ExcelFileIoManager
			::is_file_valid(
				const std::string&
					file_path
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			xlnt::workbook wb;
			wb.load(file_path);

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
		ExcelFileIoManager
			::is_worksheet_found(
				const std::string&
					file_path,
				const std::string&
					worksheet_name
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			xlnt::workbook wb;
			wb.load(file_path);

			return
				wb.contains(worksheet_name);			
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
		ExcelFileIoManager
			::create_worksheet(
				const std::string&
					file_path,
				const std::string&
					worksheet_name
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);	

			xlnt::workbook wb;
			wb.load(file_path);
			if (wb.contains(worksheet_name))
			{
				return
					false;
			}

			if (wb.sheet_count() == 1 && wb.sheet_by_index(0).title() == "Sheet1") {
				wb.sheet_by_index(0).title(worksheet_name);
			} else if (!wb.contains(worksheet_name)) {
				wb.create_sheet().title(worksheet_name);
			}
			wb.save(file_path);

			return true;					
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
		ExcelFileIoManager
			::copy_worksheet(
				const std::string&
					file_path,
				const std::string&
					from_worksheet_name,
				const std::string&
					to_worksheet_name
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!from_worksheet_name.size() ||
				!to_worksheet_name.size() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);	

			xlnt::workbook wb;
			wb.load(file_path);
			if (!wb.contains(from_worksheet_name) || wb.contains(to_worksheet_name)) return false;
        
			auto ws = wb.sheet_by_title(from_worksheet_name); 
			auto new_ws = wb.create_sheet();
			new_ws.title(to_worksheet_name);

			for (auto row : ws.rows()) {
				for (auto cell : row) {
					new_ws.cell(cell.reference()).value(cell.value<std::string>());
				}
			}
			wb.save(file_path);
			return true;					
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
		ExcelFileIoManager
			::clear_worksheet(
				const std::string&
					file_path,
				const std::string&
					worksheet_name
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);		

			xlnt::workbook wb;
			wb.load(file_path);

			if (!wb.contains(worksheet_name)) return false;

			auto old_ws = wb.sheet_by_title(worksheet_name);
			auto index = wb.index(old_ws);

			wb.remove_sheet(old_ws);

			auto new_ws = wb.create_sheet(index);
			new_ws.title(worksheet_name);

			wb.save(file_path);

			return true;					
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
		ExcelFileIoManager
			::remove_worksheet(
				const std::string&
					file_path,
				const std::string&
					worksheet_name
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);	

			xlnt::workbook wb;
			wb.load(file_path);
			auto ws = wb.sheet_by_title(worksheet_name);
			wb.remove_sheet(ws);
			wb.save(file_path);

			return true;					
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
		ExcelFileIoManager
			::get_cell_value(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::string&
					coordinate
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				!coordinate.size() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			xlnt::workbook wb;
			wb.load(file_path);

			if (!is_valid_coordinate(coordinate)) return {};
			
			return wb.sheet_by_title(worksheet_name).cell(coordinate).to_string();			
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
		ExcelFileIoManager
			::get_cell_values(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::vector<std::string>&
					coordinates
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				coordinates.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);		

			std::unordered_map<std::string, std::string> results;

			xlnt::workbook wb;
			wb.load(file_path);
			auto ws = wb.sheet_by_title(worksheet_name);
			for (const auto& coord : coordinates) {
				if (!is_valid_coordinate(coord)) return {};

				results[coord] = ws.cell(coord).to_string();
			}

			return results;
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
		ExcelFileIoManager
			::get_cell_values(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::string&
					from_coordinate,
				const std::string&
					to_coordinate
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				!from_coordinate.size() ||
				!to_coordinate.size() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!is_valid_coordinate(from_coordinate) ||
				!is_valid_coordinate(to_coordinate)
			);		

			std::unordered_map<std::string, std::string> results;

			xlnt::workbook wb;
			wb.load(file_path);
			auto ws = wb.sheet_by_title(worksheet_name);
			auto range = ws.range(from_coordinate + ":" + to_coordinate);
			for (auto row : range) {
				for (auto cell : row) {
					results[cell.reference().to_string()] = cell.to_string();
				}
			}

			return results;			
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
		ExcelFileIoManager
			::set_cell_value(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::string&
					coordinate,
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				!coordinate.size() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!is_valid_coordinate(coordinate)
			);

			xlnt::workbook wb;
			wb.load(file_path);
			wb.sheet_by_title(worksheet_name).cell(coordinate).value(value);
			wb.save(file_path);
			return true;					
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
		ExcelFileIoManager
			::set_cell_values(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::unordered_map<std::string, std::string>&
					values
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				values.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			xlnt::workbook wb;
			wb.load(file_path);
			auto ws = wb.sheet_by_title(worksheet_name);
			for (const auto& [coord, val] : values) {
				if (!is_valid_coordinate(coord)) return {};

				ws.cell(coord).value(val);
			}
			wb.save(file_path);
			return true;					
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
		ExcelFileIoManager
			::set_cell_values(
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
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				!from_coordinate.size() ||
				!to_coordinate.size() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!is_valid_coordinate(from_coordinate) ||
				!is_valid_coordinate(to_coordinate)
			);	

			xlnt::workbook wb;
			wb.load(file_path);
			auto ws = wb.sheet_by_title(worksheet_name);
			auto range = ws.range(from_coordinate + ":" + to_coordinate);
			for (auto row : range) {
				for (auto cell : row) {
					cell.value(value);
				}
			}
			wb.save(file_path);
			return true;					
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
		ExcelFileIoManager
			::clear_cell_value(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::string&
					coordinate
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				!coordinate.size() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!is_valid_coordinate(coordinate)
			);

			xlnt::workbook wb;
			wb.load(file_path);
			wb.sheet_by_title(worksheet_name).cell(coordinate).clear_value();
			wb.save(file_path);
			return true;					
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
		ExcelFileIoManager
			::clear_cell_values(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::vector<std::string>&
					coordinates
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				coordinates.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			xlnt::workbook wb;
			wb.load(file_path);
			auto ws = wb.sheet_by_title(worksheet_name);
			for (const auto& coord : coordinates) {
				if (!is_valid_coordinate(coord)) return {};

				ws.cell(coord).clear_value();
			}
			wb.save(file_path);
			return true;					
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
		ExcelFileIoManager
			::clear_cell_values(
				const std::string&
					file_path,
				const std::string&
					worksheet_name,
				const std::string&
					from_coordinate,
				const std::string&
					to_coordinate
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!file_path.size() ||
				!worksheet_name.size() ||
				!from_coordinate.size() ||
				!to_coordinate.size() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!is_valid_coordinate(from_coordinate) ||
				!is_valid_coordinate(to_coordinate)
			);		

			xlnt::workbook wb;
			wb.load(file_path);
			auto ws = wb.sheet_by_title(worksheet_name);
			auto range = ws.range(from_coordinate + ":" + to_coordinate);
			for (auto row : range) {
				for (auto cell : row) {
					cell.clear_value();
				}
			}
			wb.save(file_path);
			return true;				
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
		ExcelFileIoManager
			::is_file_valid()
	{
		return
			is_file_valid(
				configurations
					.file_path
			);	
	}

	bool
		ExcelFileIoManager
			::is_worksheet_found(
				const std::string&
					worksheet_name
			)
	{
		return
			is_worksheet_found(
				configurations
					.file_path,
				worksheet_name
			);	
	}

	bool
		ExcelFileIoManager
			::create_worksheet(
				const std::string&
					worksheet_name
			)
	{
		return
			create_worksheet(
				configurations
					.file_path,
				worksheet_name
			);	
	}

	bool
		ExcelFileIoManager
			::copy_worksheet(
				const std::string&
					from_worksheet_name,
				const std::string&
					to_worksheet_name
			)
	{
		return
			copy_worksheet(
				configurations
					.file_path,
				from_worksheet_name,
				to_worksheet_name
			);	
	}

	bool
		ExcelFileIoManager
			::clear_worksheet(
				const std::string&
					worksheet_name
			)
	{
		return
			clear_worksheet(
				configurations
					.file_path,
				worksheet_name
			);	
	}

	bool
		ExcelFileIoManager
			::remove_worksheet(
				const std::string&
					worksheet_name
			)
	{
		return
			remove_worksheet(
				configurations
					.file_path,
				worksheet_name
			);	
	}

	std::string
		ExcelFileIoManager
			::get_cell_value(
				const std::string&
					coordinate
			)
	{
		return
			get_cell_value(
				configurations
					.file_path,
				configurations
					.worksheet_name,
				coordinate
			);	
	}

	std::unordered_map<std::string, std::string>
		ExcelFileIoManager
			::get_cell_values(
				const std::vector<std::string>&
					coordinates
			)
	{
		return
			get_cell_values(
				configurations
					.file_path,
				configurations
					.worksheet_name,
				coordinates
			);	
	}

	std::unordered_map<std::string, std::string>
		ExcelFileIoManager
			::get_cell_values(
				const std::string&
					from_coordinate,
				const std::string&
					to_coordinate
			)
	{
		return
			get_cell_values(
				configurations
					.file_path,
				configurations
					.worksheet_name,
				from_coordinate,
				to_coordinate
			);	
	}

	bool
		ExcelFileIoManager
			::set_cell_value(
				const std::string&
					coordinate,
				const std::string&
					value
			)
	{
		return
			set_cell_value(
				configurations
					.file_path,
				configurations
					.worksheet_name,
				coordinate,
				value
			);	
	}

	bool
		ExcelFileIoManager
			::set_cell_values(
				const std::unordered_map<std::string, std::string>&
					values
			)
	{
		return
			set_cell_values(
				configurations
					.file_path,
				configurations
					.worksheet_name,
				values
			);	
	}

	bool
		ExcelFileIoManager
			::set_cell_values(
				const std::string&
					from_coordinate,
				const std::string&
					to_coordinate,
				const std::string&
					value
			)
	{
		return
			set_cell_values(
				configurations
					.file_path,
				configurations
					.worksheet_name,
				from_coordinate,
				to_coordinate,
				value
			);	
	}

	bool
		ExcelFileIoManager
			::clear_cell_value(
				const std::string&
					coordinate
			)
	{
		return
			clear_cell_value(
				configurations
					.file_path,
				configurations
					.worksheet_name,
				coordinate
			);	
	}

	bool
		ExcelFileIoManager
			::clear_cell_values(
				const std::vector<std::string>&
					coordinates
			)
	{
		return
			clear_cell_values(
				configurations
					.file_path,
				configurations
					.worksheet_name,
				coordinates
			);	
	}

	bool
		ExcelFileIoManager
			::clear_cell_values(
				const std::string&
					from_coordinate,
				const std::string&
					to_coordinate
			)
	{
		return
			clear_cell_values(
				configurations
					.file_path,
				configurations
					.worksheet_name,
				from_coordinate,
				to_coordinate
			);	
	}
}

#endif
