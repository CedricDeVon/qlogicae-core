#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		BinaryFileIoManager \
	)

#include "abstract_batch_operation_configurations.hpp"
#include "binary_file_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	enum class
		BinaryFileIoBatchOperation :
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
		BinaryFileIoBatchOperationConfigurations :
			public AbstractBatchOperationConfigurations<BinaryFileIoBatchOperation>
	{
	public:		
		
	};

    class
		BinaryFileIoManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<BinaryFileIoManagerConfigurations>
    {
    public:		
		BinaryFileIoManager();

		std::unordered_map<std::string, std::any>
			execute_batch_operations(
				const std::unordered_map<std::string, BinaryFileIoBatchOperationConfigurations>&
					batch_operations
			);

		std::vector<std::byte>
			read_raw_bytes(
				const std::string&
					file_path
			);

		bool
			write_raw_bytes(
				const std::string&
					file_path,
				const std::vector<std::byte>&
					text
			);

		bool
			append_raw_bytes(
				const std::string&
					file_path,
				const std::vector<std::byte>&
					text
			);

		std::string
			read_raw_text(
				const std::string&
					file_path
			);
 
		bool
			write_raw_text(
				const std::string&
					file_path,
				const std::string&
					text
			);

		bool
			append_raw_text(
				const std::string&
					file_path,
				const std::string&
					text
			);

		std::vector<std::byte>
			read_raw_bytes();

		bool
			write_raw_bytes(
				const std::vector<std::byte>&
					text
			);

		bool
			append_raw_bytes(
				const std::vector<std::byte>&
					text
			);

		std::string
			read_raw_text();

		bool
			write_raw_text(
				const std::string&
					text
			);

		bool
			append_raw_text(
				const std::string&
					text
			);
    };
}

#endif
