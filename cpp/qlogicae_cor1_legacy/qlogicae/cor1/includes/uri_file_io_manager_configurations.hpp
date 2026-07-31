#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		UriFileIoManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		UriFileIoManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<UriFileIoManagerConfigurations>
    {
	public:
		std::string
			file_path =
				"";

		std::string
			mime_type =
				"application/octet-stream";

		UriFileIoManagerConfigurations();
    };    
}

#endif
