#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CryptographyMigrationManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		CryptographyMigrationManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<CryptographyMigrationManagerConfigurations>
    {
	public:	
		std::function<bool()>
			callback =
				[]() -> bool { return true; };

		CryptographyMigrationManagerConfigurations();
    };    
}

#endif
