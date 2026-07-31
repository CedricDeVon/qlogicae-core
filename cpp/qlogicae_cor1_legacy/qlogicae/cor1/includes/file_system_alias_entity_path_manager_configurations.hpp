#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemAliasEntityPathManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		FileSystemAliasEntityPathManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<FileSystemAliasEntityPathManagerConfigurations>
	{
	public:			
		bool
			is_recursive_search_enabled =
				true;

		FileSystemAliasEntityPathManagerConfigurations();
	};
}

#endif
