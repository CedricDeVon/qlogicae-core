#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		UriFileIoManager \
	)

#include "uri_file_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		UriFileIoManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<UriFileIoManagerConfigurations>
    {
    public:		
		UriFileIoManager();
	
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
