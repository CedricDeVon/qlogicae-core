#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		KyberCryptographyAlgorithmEnumManagerConfigurations \
	)

#include "../includes/kyber_cryptography_algorithm_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	KyberCryptographyAlgorithmEnumManagerConfigurations
		::KyberCryptographyAlgorithmEnumManagerConfigurations() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<KyberCryptographyAlgorithmEnumManagerConfigurations>()
	{
		type =
			KyberCryptographyAlgorithm
				::KYBER_768;
	}
}

#endif
