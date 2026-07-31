#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		DilithiumCryptographyAlgorithmEnumManagerConfigurations \
	)

#include "dilithium_cryptography_algorithm.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		DilithiumCryptographyAlgorithmEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DilithiumCryptographyAlgorithmEnumManagerConfigurations>
    {
	public:	
		DilithiumCryptographyAlgorithm
			type =
				DilithiumCryptographyAlgorithm
					::DILITHIUM_3;

		DilithiumCryptographyAlgorithmEnumManagerConfigurations();
    };    
}

#endif
