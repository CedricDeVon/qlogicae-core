#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextFileIoManager \
	)

#include "text_file_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TextFileIoManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextFileIoManagerConfigurations>
    {
    public:		
		TextFileIoManager();

		std::string
			read_text(
				const std::string
					file_path
			);

		bool
			write_text(
				const std::string
					file_path,
				const std::string&
					text
			);

		bool
			append_text(
				const std::string
					file_path,
				const std::string&
					text
			);

		std::string
			get_text(
				const std::string
					file_path,
				const size_t&
					line_number
			);

		bool
			set_text(
				const std::string
					file_path,
				const size_t&
					line_number,
				const std::string&
					text
			);

		bool
			insert_text(
				const std::string
					file_path,
				const size_t&
					line_number,
				const std::string&
					text
			);

		bool
			remove_text(
				const std::string
					file_path,
				const size_t&
					line_number
			);



		std::string
			read_text();

		bool
			write_text(
				const std::string&
					text
			);

		bool
			append_text(
				const std::string&
					text
			);

		std::string
			get_text(
				const size_t&
					line_number
			);

		bool
			set_text(
				const size_t&
					line_number,
				const std::string&
					text
			);

		bool
			insert_text(
				const size_t&
					line_number,
				const std::string&
					text
			);

		bool
			remove_text(
				const size_t&
					line_number
			);
		
		bool
			append_text(
				const std::string
					file_path,
				const std::vector<std::string>&
					texts
			);

		std::unordered_map<size_t, std::string>
			get_text(
				const std::string
					file_path,
				const std::vector<size_t>&
					line_numbers
			);

		std::unordered_map<size_t, std::string>
			get_text(
				const std::string
					file_path,
				const size_t&
					starting_line_number,
				const size_t&
					ending_line_number
			);

		bool
			set_text(
				const std::string
					file_path,
				const std::unordered_map<size_t, std::string>&
					line_number_and_text
			);

		bool
			insert_text(
				const std::string
					file_path,
				const std::unordered_map<size_t, std::string>&
					line_number_and_text
			);

		bool
			remove_text(
				const std::string
					file_path,
				const std::vector<size_t>&
					line_numbers
			);

		bool
			append_text(
				const std::vector<std::string>&
					texts
			);

		std::unordered_map<size_t, std::string>
			get_text(
				const std::vector<size_t>&
					line_numbers
			);

		std::unordered_map<size_t, std::string>
			get_text(
				const size_t&
					starting_line_number,
				const size_t&
					ending_line_number
			);

		bool
			set_text(
				const std::unordered_map<size_t, std::string>&
					line_number_and_text
			);

		bool
			insert_text(
				const std::unordered_map<size_t, std::string>&
					line_number_and_text
			);

		bool
			remove_text(
				const std::vector<size_t>&
					line_numbers
			);
    };
}

#endif
