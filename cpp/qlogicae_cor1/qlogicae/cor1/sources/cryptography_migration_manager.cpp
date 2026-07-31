#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CryptographyMigrationManager \
	)

#include "../includes/cryptography_migration_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    CryptographyMigrationManager
		::CryptographyMigrationManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<CryptographyMigrationManagerConfigurations>()
	{
		
	}

	bool
		CryptographyMigrationManager
			::migrate(
				const std::function<bool()>&
					callback
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!callback
			);

			return
				callback();
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	bool
		CryptographyMigrationManager
			::migrate()
	{
		return
			migrate(
				configurations
					.callback
			);
	}
}

#endif
