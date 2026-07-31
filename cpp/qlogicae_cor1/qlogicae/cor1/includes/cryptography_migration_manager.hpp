#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CryptographyMigrationManager \
	)

#include "cryptography_migration_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		CryptographyMigrationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<CryptographyMigrationManagerConfigurations>
    {
    public:
		CryptographyMigrationManager();

		bool
			migrate(
				const std::function<bool()>&
					callback
			);

		bool
			migrate();
	};
}

#endif
