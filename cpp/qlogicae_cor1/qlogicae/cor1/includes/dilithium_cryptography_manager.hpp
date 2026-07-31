#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		DilithiumCryptographyManager \
	)

#include "dilithium_cryptography_algorithm_enum_manager.hpp"
#include "dilithium_cryptography_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		DilithiumCryptographyManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<DilithiumCryptographyManagerConfigurations>
    {
    public:
		DilithiumCryptographyManager();

		bool
			generate_keypair(
				const DilithiumCryptographyAlgorithm&
					algorithm,
				std::vector<uint8_t>&
					public_key,
				std::vector<uint8_t>&
					private_key
			);

		bool
			sign_text(
				const DilithiumCryptographyAlgorithm&
					algorithm,
				const std::vector<uint8_t>&
					private_key,
				const std::vector<uint8_t>&
					message,
				std::vector<uint8_t>&
					signature
			);

		bool
			verify_text(
				const DilithiumCryptographyAlgorithm&
					algorithm,
				const std::vector<uint8_t>&
					public_key,
				const std::vector<uint8_t>&
					message,
				const std::vector<uint8_t>&
					signature
			);

		bool
			generate_keypair(
				std::vector<uint8_t>&
					public_key,
				std::vector<uint8_t>&
					private_key
			);

		bool
			sign_text(
				const std::vector<uint8_t>&
					private_key,
				const std::vector<uint8_t>&
					message,
				std::vector<uint8_t>&
					signature
			);

		bool
			verify_text(
				const std::vector<uint8_t>&
					public_key,
				const std::vector<uint8_t>&
					message,
				const std::vector<uint8_t>&
					signature
			);
	};
}

#endif
