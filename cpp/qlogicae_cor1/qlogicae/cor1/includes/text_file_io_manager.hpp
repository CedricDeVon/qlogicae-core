#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextFileIoManager \
	)

#include "abstract_batch_operation_configurations.hpp"
#include "text_file_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	enum class
		TextFileIoBatchOperation :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_ENUM_INHERITED_TYPE
    {
		IS_FILE_VALID,

		READ_ALL_LINES,

		WRITE_ALL_LINES,

		CLEAR_ALL_LINES,

		READ_MANY_LINES,

		APPEND_MANY_LINES,

		INSERT_MANY_LINES,

		REMOVE_MANY_LINES,

        QLOGICAE_COR1__BASE__HPP_CPP__ENUM_CONSTANTS
    };

	struct
		TextFileIoBatchOperationConfigurations :
			public AbstractBatchOperationConfigurations<TextFileIoBatchOperation>
	{
	public:		
		
	};

    class
		TextFileIoManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextFileIoManagerConfigurations>
    {
    public:		
		TextFileIoManager();

		std::unordered_map<std::string, std::any>
			execute_batch_operations(
				const std::unordered_map<std::string, TextFileIoBatchOperationConfigurations>&
					batch_operations
			);

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
