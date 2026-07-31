#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		KyberCryptographyAlgorithmEnumManager \
	)

#include "kyber_cryptography_algorithm.hpp"
#include "kyber_cryptography_algorithm_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		KyberCryptographyAlgorithmEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<KyberCryptographyAlgorithmEnumManagerConfigurations>
    {
    public:
		KyberCryptographyAlgorithmEnumManager();

		std::string
			convert_enum_to_string(
				const KyberCryptographyAlgorithm&
					value
			);

		std::string
			convert_enum_to_string();

		std::string
			convert_enum_to_string_algorithm_name(
				const KyberCryptographyAlgorithm&
					value
			);

		std::string
			convert_enum_to_string_algorithm_name();

		KyberCryptographyAlgorithm
			convert_string_to_enum(
				const std::string&
					value
			);

		KyberCryptographyAlgorithm
			convert_string_to_enum();
    };
}

#endif
