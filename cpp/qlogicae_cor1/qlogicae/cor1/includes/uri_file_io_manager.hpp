#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		UriFileIoManager \
	)

#include "abstract_batch_operation_configurations.hpp"
#include "uri_file_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	enum class
		UriFileIoBatchOperation :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_ENUM_INHERITED_TYPE
    {
		IS_FILE_VALID,

		GET_URI,

        QLOGICAE_COR1__BASE__HPP_CPP__ENUM_CONSTANTS
    };

	struct
		UriFileIoBatchOperationConfigurations :
			public AbstractBatchOperationConfigurations<UriFileIoBatchOperation>
	{
	public:		
		
	};

    class
		UriFileIoManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<UriFileIoManagerConfigurations>
    {
    public:		
		UriFileIoManager();

		std::unordered_map<std::string, std::any>
			execute_batch_operations(
				const std::unordered_map<std::string, UriFileIoBatchOperationConfigurations>&
					batch_operations
			);
	
		std::string
			get_uri(
				const std::string&
					file_path,
				const std::string&
					mime_type
			);

		std::string
			get_uri();
    };
}

#endif
