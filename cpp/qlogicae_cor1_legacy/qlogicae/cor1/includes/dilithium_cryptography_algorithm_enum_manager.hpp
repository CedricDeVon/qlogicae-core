#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		DilithiumCryptographyAlgorithmEnumManager \
	)

#include "dilithium_cryptography_algorithm.hpp"
#include "dilithium_cryptography_algorithm_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		DilithiumCryptographyAlgorithmEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<DilithiumCryptographyAlgorithmEnumManagerConfigurations>
    {
    public:
		DilithiumCryptographyAlgorithmEnumManager();

		std::string
			convert_enum_to_string(
				const DilithiumCryptographyAlgorithm&
					value
			);

		std::string
			convert_enum_to_string();

		std::string
			convert_enum_to_string_algorithm_name(
				const DilithiumCryptographyAlgorithm&
					value
			);

		std::string
			convert_enum_to_string_algorithm_name();

		DilithiumCryptographyAlgorithm
			convert_string_to_enum(
				const std::string&
					value
			);

		DilithiumCryptographyAlgorithm
			convert_string_to_enum();
    };
}

#endif
