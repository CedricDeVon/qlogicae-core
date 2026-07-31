#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		DilithiumCryptographyManagerConfigurations \
	)

#include "../includes/dilithium_cryptography_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	DilithiumCryptographyManagerConfigurations
		::DilithiumCryptographyManagerConfigurations() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DilithiumCryptographyManagerConfigurations>()
	{
		algorithm =
			DilithiumCryptographyAlgorithm
				::DILITHIUM_3;
	}
}

#endif
