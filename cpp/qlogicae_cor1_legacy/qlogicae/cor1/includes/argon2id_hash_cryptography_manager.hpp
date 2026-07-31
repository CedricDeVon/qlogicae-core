#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Argon2idHashCryptographyManager \
	)

#include "random_value_generation_manager.hpp"
#include "argon2id_hash_cryptography_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		Argon2idHashCryptographyManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<Argon2idHashCryptographyManagerConfigurations>
    {
    public:
		Argon2idHashCryptographyManager();

		std::string
			hash_text(
				const std::string&
					text
			);

		bool
			verify_text(
				const std::string&
					text,
				const std::string&
					hash
			);

		bool
			hash_text(
				std::vector<uint8_t>&
					text
			);

		bool
			verify_text(
				const std::vector<uint8_t>&
					text,
				const std::vector<uint8_t>&
					hash
			);
    };
}

#endif
