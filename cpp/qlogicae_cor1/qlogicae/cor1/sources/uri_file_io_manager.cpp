#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		UriFileIoManager \
	)

#include "../includes/uri_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	UriFileIoManager
		::UriFileIoManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<UriFileIoManagerConfigurations>()
    {
        
    }
	
	std::unordered_map<std::string, std::any>
		UriFileIoManager
			::execute_batch_operations(
				const std::unordered_map<std::string, UriFileIoBatchOperationConfigurations>&
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

			std::unordered_map<std::string, std::any>
				batch_operation_outpus;

			std::string
				file_path;						

			std::ifstream
				input_file;
                        
			for (const auto& [batch_operation_key, batch_operation_value] : batch_operations)
			{
				file_path =
					std::any_cast<std::string>(
						batch_operation_value.inputs.at("file_path")
					);

				switch (batch_operation_value.type)
				{
					case (UriFileIoBatchOperation::IS_FILE_VALID):
					{
						batch_operation_outpus[batch_operation_key] =
							bool(
								!file_path.empty() &&
								std::filesystem::exists(file_path) &
								!std::filesystem::is_directory(file_path)
							);

						break;
					}
					case (UriFileIoBatchOperation::GET_URI):
					{
						input_file = std::ifstream(
							file_path,
							std::ios::binary
						);

						if (!input_file)
						{
							batch_operation_outpus[batch_operation_key] =
								bool(false);

							continue;
						}

						std::ostringstream
							input_file_stream;

						input_file_stream << input_file.rdbuf();

						batch_operation_outpus[batch_operation_key] =
							std::string(
								"data:" +
								std::any_cast<std::string>(
									batch_operation_value.inputs.at("mime_type")
								) +
								";base64," +
								"AKLOMP_ENCODED(" +
								input_file_stream.str() +
								")"
							);

						break;
					}
					default:
					{
						batch_operation_outpus[batch_operation_key] =
							bool(false);

						break;
					}
				}				
			}

            return
				batch_operation_outpus;
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
		UriFileIoManager
			::get_uri(
				const std::string&
					file_path,
				const std::string&
					mime_type
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

            std::ifstream
				input_file(
					file_path,
					std::ios::binary
				);

            if (!input_file)
            {
                return "";
            }

            std::ostringstream
				output_buffer;

            output_buffer << input_file.rdbuf();

            std::string
				raw_data =
					output_buffer
						.str();

            return
				std::string("data:") +
				mime_type +
                ";base64," +
                "AKLOMP_ENCODED(" +
                raw_data +
                ")";
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
		UriFileIoManager
			::get_uri()
	{
		return
			get_uri(
				configurations
					.file_path,
				configurations
					.mime_type
			);
	}
}

#endif
