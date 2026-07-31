#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEntityEnumManagerConfigurations \
	)

#include "file_system_entity.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		FileSystemEntityEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<FileSystemEntityEnumManagerConfigurations>
	{
	public:	
		FileSystemEntity
			type =
				FileSystemEntity
					::ALL;

		FileSystemEntityEnumManagerConfigurations();
	};
}

#endif
