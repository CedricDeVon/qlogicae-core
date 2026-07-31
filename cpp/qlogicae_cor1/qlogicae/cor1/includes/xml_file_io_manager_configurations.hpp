#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		XmlFileIoManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		XmlFileIoManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<XmlFileIoManagerConfigurations>
    {
	public:
		std::string
			file_path =
				"";

		size_t
			indentation_count =
				1;

		XmlFileIoManagerConfigurations();
    };    
}

#endif
