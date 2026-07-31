#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EdscaSignatureCryptographyManager \
	)

#include "edsca_signature_cryptography_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		EdscaSignatureCryptographyManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<EdscaSignatureCryptographyManagerConfigurations>
    {
    public:
		EdscaSignatureCryptographyManager();

		bool
			construct();

		std::vector<std::uint8_t>
			sign(
				const std::vector<std::uint8_t>&
					text,
				const std::vector<std::uint8_t>&
					private_key
			);

		bool
			verify(
				const std::vector<std::uint8_t>&
					text,
				const std::vector<std::uint8_t>&
					public_key,
				const std::vector<std::uint8_t>&
					signature
			);

		std::string
			sign(
				const std::string&
					text,
				const std::string&
					private_key
			);

		bool
			verify(
				const std::string&
					text,
				const std::string&
					public_key,
				const std::string&
					signature
			);
    };
}

#endif
