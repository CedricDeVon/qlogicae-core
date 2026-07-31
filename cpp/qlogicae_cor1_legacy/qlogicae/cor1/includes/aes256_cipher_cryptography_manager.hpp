#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Aes256CipherCryptographyManager \
	)

#include "aes256_cipher_cryptography_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		Aes256CipherCryptographyManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<Aes256CipherCryptographyManagerConfigurations>
    {
    public:
		Aes256CipherCryptographyManager();

		std::string
			encrypt_text(
				const std::string&
					text,
				const std::string&
					private_key,
				const std::string&
					nonce
			);

		std::string
			decrypt_text(
				const std::string&
					text,
				const std::string&
					private_key,
				const std::string&
					nonce
			);

		bool
			encrypt_text(
				std::vector<uint8_t>&
					text,
				const std::vector<uint8_t>&
					private_key,
				const std::vector<uint8_t>&
					nonce
			);

		bool
			decrypt_text(
				std::vector<uint8_t>&
					text,
				const std::vector<uint8_t>&
					private_key,
				const std::vector<uint8_t>&
					nonce
			);
    };
}

#endif
