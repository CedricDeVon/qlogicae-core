#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		KyberCryptographyManager \
	)

#include "kyber_cryptography_algorithm_enum_manager.hpp"
#include "kyber_cryptography_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		KyberCryptographyManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<KyberCryptographyManagerConfigurations>
    {
    public:
		KyberCryptographyManager();

		bool
			generate_keypair(
				const KyberCryptographyAlgorithm&
					algorithm,
				std::vector<uint8_t>&
					public_key,
				std::vector<uint8_t>&
					private_key
			);

		bool
			encrypt_text(
				const KyberCryptographyAlgorithm&
					algorithm,
				const std::vector<uint8_t>&
					public_key,
				std::vector<uint8_t>&
					ciphertext,
				std::vector<uint8_t>&
					shared_secret
			);

		bool
			decrypt_text(
				const KyberCryptographyAlgorithm&
					algorithm,
				const std::vector<uint8_t>&
					private_key,
				const std::vector<uint8_t>&
					ciphertext,
				std::vector<uint8_t>&
					shared_secret
			);

		bool
			generate_keypair(
				std::vector<uint8_t>&
					public_key,
				std::vector<uint8_t>&
					private_key
			);

		bool
			encrypt_text(
				const std::vector<uint8_t>&
					public_key,
				std::vector<uint8_t>&
					ciphertext,
				std::vector<uint8_t>&
					shared_secret
			);

		bool
			decrypt_text(
				const std::vector<uint8_t>&
					private_key,
				const std::vector<uint8_t>&
					ciphertext,
				std::vector<uint8_t>&
					shared_secret
			);
	};
}

#endif

