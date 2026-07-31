#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonWebTokenCryptographyManager \
	)

#include "jsonwebtoken_cryptography_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		JsonWebTokenCryptographyManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<JsonWebTokenCryptographyManagerConfigurations>
    {
    public:
		JsonWebTokenCryptographyManager();

		std::string
			sign_text(
				const std::string&
					text,
				const std::string&
					public_key,
				const std::string&
					private_key
			);

		std::string
			verify_text(
				const std::string&
					text,
				const std::string&
					public_key
			);

		bool
			sign_text(
				std::vector<uint8_t>&
					text,
				const std::vector<uint8_t>&
					public_key,
				const std::vector<uint8_t>&
					private_key
			);

		bool
			verify_text(
				std::vector<uint8_t>&
					text,
				const std::vector<uint8_t>&
					public_key
			);
	};
}

#endif
