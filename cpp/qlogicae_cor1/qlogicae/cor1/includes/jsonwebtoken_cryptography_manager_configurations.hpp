#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonWebTokenCryptographyManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		JsonWebTokenCryptographyManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<JsonWebTokenCryptographyManagerConfigurations>
    {
	public:
		std::string
			issuer =
				"issuer";

		std::chrono::seconds
			lifetime =
				std::chrono::seconds { 86'400'000 };

		std::map<std::string, std::string>
			claims = 
				{};

		JsonWebTokenCryptographyManagerConfigurations();
    };    
}

#endif
