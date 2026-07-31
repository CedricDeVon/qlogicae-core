#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CryptographyMigrationManagerConfigurations \
	)

#include "../includes/cryptography_migration_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	CryptographyMigrationManagerConfigurations
		::CryptographyMigrationManagerConfigurations() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<CryptographyMigrationManagerConfigurations>()
	{
		callback =
			[]() -> bool { return true; };
	}
}

#endif
