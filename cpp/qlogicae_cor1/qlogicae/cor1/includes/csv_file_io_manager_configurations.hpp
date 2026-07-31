#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CsvFileIoManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		CsvFileIoManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<CsvFileIoManagerConfigurations>
    {
	public:
		std::string
			file_path =
				"";	

		std::string				
			delimeter =
				",";
	
		CsvFileIoManagerConfigurations();
    };    
}

#endif
