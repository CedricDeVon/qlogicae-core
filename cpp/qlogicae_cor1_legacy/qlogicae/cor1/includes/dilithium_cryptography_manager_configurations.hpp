#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		DilithiumCryptographyManagerConfigurations \
	)

#include "dilithium_cryptography_algorithm.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		DilithiumCryptographyManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DilithiumCryptographyManagerConfigurations>
    {
	public:	
		DilithiumCryptographyAlgorithm
			algorithm =
				DilithiumCryptographyAlgorithm
					::DILITHIUM_3;

		DilithiumCryptographyManagerConfigurations();
    };    
}

#endif
