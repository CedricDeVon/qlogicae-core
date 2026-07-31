#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextFileIoManager \
	)

#include "../includes/text_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        
	TextFileIoManager
		::TextFileIoManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextFileIoManagerConfigurations>()
    {
        
    }
	
	std::string
		TextFileIoManager
			::read_text(
				const std::string
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

			fast_io::native_file_loader
				file_loader(
					file_path
				);

            return
				file_loader
					.data();
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
		TextFileIoManager
			::write_text(
				const std::string
					file_path,
				const std::string&
					text
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				text.empty()
			);

			fast_io::obuf_file
				write_file(
					file_path
				);

			fast_io::write(
				write_file,
				text.begin(),
				text.end()
			);

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
		TextFileIoManager
			::append_text(
				const std::string
					file_path,
				const std::string&
					text
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				text.empty()
			);

			fast_io::obuf_file
				append_file(
					file_path,
					fast_io::open_mode::app
				);

			fast_io::write(
				append_file,
				text.begin(),
				text.end()
			);

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

	std::string
		TextFileIoManager
			::get_text(
				const std::string
					file_path,
				const size_t&
					line_number
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
				line_number < 1
			);

			fast_io::native_file_loader f(file_path);
			std::string_view content(f.data(), f.size());
			size_t i = 0;
			size_t pos = 0;
			while (pos < content.size()) {
				size_t end = content.find('\n', pos);
				if (end == std::string_view::npos) end = content.size();
				if (++i == line_number)
					return std::string(content.substr(pos, end - pos));
				pos = end + 1;
			}

            return
				"";
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
		TextFileIoManager
			::set_text(
				const std::string
					file_path,
				const size_t&
					line_number,
				const std::string&
					text
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
				line_number < 1
			);

			std::vector<std::string> lines;
			std::ifstream input(file_path);
			std::string line;
			while (std::getline(input, line))
				lines.push_back(line);
			input.close();

			if (line_number > lines.size()) return false;
			lines[line_number - 1] = text;

			std::ofstream output(file_path, std::ios::binary | std::ios::trunc);
			for (const auto& l : lines)
				output << l << '\n';

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
		TextFileIoManager
			::insert_text(
				const std::string
					file_path,
				const size_t&
					line_number,
				const std::string&
					text
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
				line_number < 1
			);

			std::vector<std::string> lines;
			std::ifstream input(file_path);
			std::string line;
			while (std::getline(input, line))
				lines.push_back(line);
			input.close();

			if (line_number > lines.size() + 1) return false;
			lines.insert(lines.begin() + (line_number - 1), text);

			std::ofstream output(file_path, std::ios::binary | std::ios::trunc);
			for (const auto& l : lines)
				output << l << '\n';

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
		TextFileIoManager
			::remove_text(
				const std::string
					file_path,
				const size_t&
					line_number
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
				line_number < 1
			);

			std::vector<std::string> lines;
			std::ifstream input(file_path);
			std::string line;
			while (std::getline(input, line))
				lines.push_back(line);
			input.close();

			if (line_number > lines.size()) return false;
			lines.erase(lines.begin() + (line_number - 1));

			std::ofstream output(file_path, std::ios::binary | std::ios::trunc);
			for (const auto& l : lines)
				output << l << '\n';

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
		TextFileIoManager
			::append_text(
				const std::string
					file_path,
				const std::vector<std::string>&
					texts
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!texts.size()
			);

			std::string
				output = "";

			fast_io::obuf_file
				file(
					file_path,		
					fast_io::open_mode::app
				);

			for (const std::string& text : texts)
			{
				output += text + "\n";				
			}

			fast_io::io::print(
				file,
				output
			);

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

	std::unordered_map<size_t, std::string>
		TextFileIoManager
			::get_text(
				const std::string
					file_path,
				const std::vector<size_t>&
					line_numbers
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
				!line_numbers.size()
			);

			std::unordered_map<size_t, std::string> result;
			std::unordered_set<size_t> targets(line_numbers.begin(), line_numbers.end());

			std::ifstream file(file_path);
			if (!file.is_open()) return {};

			std::string line;
			size_t index{ 1 };

			while (std::getline(file, line))
			{
				if (targets.contains(index))
				{
					result.emplace(index, line);
				}
				++index;
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

	std::unordered_map<size_t, std::string>
		TextFileIoManager
			::get_text(
				const std::string
					file_path,
				const size_t&
					starting_line_number,
				const size_t&
					ending_line_number
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
				starting_line_number > ending_line_number ||
				ending_line_number < starting_line_number
			);

			std::unordered_map<size_t, std::string> result;
			std::ifstream file(file_path);
			if (!file.is_open()) return {};

			std::string line;
			size_t index{ 1 };

			while (std::getline(file, line))
			{
				if (index >= starting_line_number && index <= ending_line_number)
				{
					result.emplace(index, line);
				}

				if (index > ending_line_number)
				{
					break;
				}

				++index;
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
		TextFileIoManager
			::set_text(
				const std::string
					file_path,
				const std::unordered_map<size_t, std::string>&
					line_number_and_text
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
				!line_number_and_text.size()
			);

			std::vector<std::string> lines;
			std::ifstream input(file_path);
			std::string line;
			while (std::getline(input, line))
				lines.push_back(line);
			input.close();

			for (const auto& [num, text] : line_number_and_text)
			{
				if (num == 0) continue;
				size_t index = num - 1;
				if (index < lines.size())
					lines[index] = text;
			}

			std::ofstream output(file_path, std::ios::binary | std::ios::trunc);
			for (const auto& l : lines)
				output << l << '\n';

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
		TextFileIoManager
			::insert_text(
				const std::string
					file_path,
				const std::unordered_map<size_t, std::string>&
					line_number_and_text
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
				!line_number_and_text.size()
			);

			std::vector<std::string> lines;
			std::ifstream input(file_path);
			std::string line;

			while (std::getline(input, line))
			{
				lines.push_back(line);
			}

			input.close();

			std::vector<std::pair<size_t, std::string>> entries(
				line_number_and_text.begin(),
				line_number_and_text.end()
			);

			std::sort(
				entries.begin(),
				entries.end(),
				[](const auto& a, const auto& b)
				{
					return a.first < b.first;
				}
			);

			std::vector<std::string> result;

			size_t entry_index = 0;

			for (size_t i = 0; i < lines.size(); ++i)
			{
				size_t current_line = i + 1;

				while
					(
						entry_index < entries.size() &&
						entries[entry_index].first == current_line
						)
				{
					result.push_back(entries[entry_index].second);
					entry_index++;
				}

				result.push_back(lines[i]);
			}

			while (entry_index < entries.size())
			{
				result.push_back(entries[entry_index].second);
				entry_index++;
			}

			std::ofstream output(file_path, std::ios::binary | std::ios::trunc);

			for (const auto& l : result)
			{
				output << l << '\n';
			}

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
		TextFileIoManager
			::remove_text(
				const std::string
					file_path,
				const std::vector<size_t>&
					line_numbers
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
				!line_numbers.size()
			);

			std::vector<std::string> lines;
			std::ifstream input(file_path);
			std::string line;
			while (std::getline(input, line))
				lines.push_back(line);
			input.close();

			std::vector<size_t> indices(line_numbers.begin(), line_numbers.end());
			std::sort(indices.begin(), indices.end(), std::greater<size_t>());

			for (size_t num : indices)
			{
				if (num == 0) continue;
				size_t index = num - 1;
				if (index < lines.size())
					lines.erase(lines.begin() + index);
			}

			std::ofstream output(file_path, std::ios::binary | std::ios::trunc);
			for (const auto& l : lines)
				output << l << '\n';

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
		TextFileIoManager
			::read_text()
	{
		return
			read_text(
				configurations
					.file_path
			);
	}

	bool
		TextFileIoManager
			::write_text(
				const std::string&
					text
			)
	{
		return
			write_text(
				configurations
					.file_path,
				text
			);
	}

	bool
		TextFileIoManager
			::append_text(
				const std::string&
					text
			)
	{
		return
			append_text(
				configurations
					.file_path,
				text
			);
	}

	std::string
		TextFileIoManager
			::get_text(
				const size_t&
					line_number
			)
	{
		return
			get_text(
				configurations
					.file_path,
				line_number
			);
	}

	bool
		TextFileIoManager
			::set_text(
				const size_t&
					line_number,
				const std::string&
					text
			)
	{
		return
			set_text(
				configurations
					.file_path,
				line_number,
				text
			);
	}

	bool
		TextFileIoManager
			::insert_text(
				const size_t&
					line_number,
				const std::string&
					text
			)
	{
		return
			insert_text(
				configurations
					.file_path,
				line_number,
				text
			);
	}

	bool
		TextFileIoManager
			::remove_text(
				const size_t&
					line_number
			)
	{
		return
			remove_text(
				configurations
					.file_path,
				line_number
			);
	}

	bool
		TextFileIoManager
			::append_text(
				const std::vector<std::string>&
					texts
			)
	{
		return
			append_text(
				configurations
					.file_path,
				texts
			);
	}

	std::unordered_map<size_t, std::string>
		TextFileIoManager
			::get_text(
				const std::vector<size_t>&
					line_numbers
			)
	{
		return
			get_text(
				configurations
					.file_path,
				line_numbers
			);
	}

	std::unordered_map<size_t, std::string>
		TextFileIoManager
			::get_text(
				const size_t&
					starting_line_number,
				const size_t&
					ending_line_number
			)
	{
		return
			get_text(
				configurations
					.file_path,
				starting_line_number,
				ending_line_number
			);
	}

	bool
		TextFileIoManager
			::set_text(
				const std::unordered_map<size_t, std::string>&
					line_number_and_text
			)
	{
		return
			set_text(
				configurations
					.file_path,
				line_number_and_text
			);
	}

	bool
		TextFileIoManager
			::insert_text(
				const std::unordered_map<size_t, std::string>&
					line_number_and_text
			)
	{
		return
			insert_text(
				configurations
					.file_path,
				line_number_and_text
			);
	}

	bool
		TextFileIoManager
			::remove_text(
				const std::vector<size_t>&
					line_numbers
			)
	{
		return
			remove_text(
				configurations
					.file_path,
				line_numbers
			);
	}
}

#endif
