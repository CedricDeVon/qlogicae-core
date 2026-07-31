#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CharacterDomainEnumManager \
	)

#include "character_domain.hpp"
#include "character_domain_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		CharacterDomainEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<CharacterDomainEnumManagerConfigurations>
    {
    public:
		CharacterDomainEnumManager();

		std::string
			convert_enum_to_string(
				const CharacterDomain&
					value
			);

		std::string
			convert_enum_to_string();

		CharacterDomain
			convert_string_to_enum(
				const std::string&
					value
			);

		CharacterDomain
			convert_string_to_enum();
    };
}

#endif
