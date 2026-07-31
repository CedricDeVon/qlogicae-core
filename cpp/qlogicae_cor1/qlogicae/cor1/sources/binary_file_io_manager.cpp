#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		BinaryFileIoManager \
	)

#include "../includes/binary_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	BinaryFileIoManager
		::BinaryFileIoManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<BinaryFileIoManagerConfigurations>()
    {
        
    }

	std::unordered_map<std::string, std::any>
		BinaryFileIoManager
			::execute_batch_operations(
				const std::unordered_map<std::string, BinaryFileIoBatchOperationConfigurations>&
					batch_operations
			)	
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				batch_operations.empty()
			);

            return
				{};
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::vector<std::byte>
		BinaryFileIoManager
			::read_raw_bytes(
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

            fast_io::native_file_loader
				file_loader(
					file_path
				);

            auto
				span_bytes =
					std::as_bytes(
						std::span(
							file_loader.data(),
							file_loader.size()
						)
					);

            std::vector<std::byte> content(
                span_bytes.begin(),
                span_bytes.end()
            );

            return content;
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
		BinaryFileIoManager
			::write_raw_bytes(
				const std::string&
					file_path,
				const std::vector<std::byte>&
					text
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!text.size()
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
		BinaryFileIoManager
			::append_raw_bytes(
				const std::string&
					file_path,
				const std::vector<std::byte>&
					text
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!text.size()
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

	std::vector<std::byte>
		BinaryFileIoManager
			::read_raw_bytes()
	{
		return
			read_raw_bytes(
				configurations
					.file_path
			);
	}

	bool
		BinaryFileIoManager
			::write_raw_bytes(
				const std::vector<std::byte>&
					text
			)
	{
		return
			write_raw_bytes(
				configurations
					.file_path,
				text
			);
	}

	bool
		BinaryFileIoManager
			::append_raw_bytes(
				const std::vector<std::byte>&
					text
			)
	{
		return
			append_raw_bytes(
				configurations
					.file_path,
				text
			);
	}

	std::string
		BinaryFileIoManager
			::read_raw_text(
				const std::string&
					file_path
			)
	{
		return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextEncodingManager>()				
				.convert_bytes_to_string(
					read_raw_bytes(
						file_path
					)
				);
	}

	std::string
		BinaryFileIoManager
			::read_raw_text()
	{
		return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextEncodingManager>()				
				.convert_bytes_to_string(
					read_raw_bytes(
						configurations
							.file_path
					)
				);
	}

	bool
		BinaryFileIoManager
			::write_raw_text(
				const std::string&
					file_path,
				const std::string&
					text
			)
	{
		return
			write_raw_bytes(
				file_path,
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextEncodingManager>()					
					.convert_string_to_bytes(
						text
					)
			);
	}

	bool
		BinaryFileIoManager
			::write_raw_text(
				const std::string&
					text
			)
	{
		return
			write_raw_bytes(
				configurations
					.file_path,
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextEncodingManager>()					
					.convert_string_to_bytes(
						text
					)
			);
	}

	bool
		BinaryFileIoManager
			::append_raw_text(
				const std::string&
					file_path,
				const std::string&
					text
			)
	{
		return
			append_raw_bytes(
				file_path,
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextEncodingManager>()					
					.convert_string_to_bytes(
						text
					)
			);
	}

	bool
		BinaryFileIoManager
			::append_raw_text(
				const std::string&
					text
			)
	{
		return
			append_raw_bytes(
				configurations
					.file_path,
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextEncodingManager>()					
					.convert_string_to_bytes(
						text
					)
			);
	}
}

#endif
