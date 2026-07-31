#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ExcelFileIoManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		ExcelFileIoManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<ExcelFileIoManagerConfigurations>
    {
	public:
		std::string
			file_path =
				"";

		std::string
			worksheet_name =
				"";

		ExcelFileIoManagerConfigurations();
    };    
}

#endif
