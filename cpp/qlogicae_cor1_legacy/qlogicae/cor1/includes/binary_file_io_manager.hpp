#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		BinaryFileIoManager \
	)

#include "binary_file_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		BinaryFileIoManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<BinaryFileIoManagerConfigurations>
    {
    public:		
		BinaryFileIoManager();

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
