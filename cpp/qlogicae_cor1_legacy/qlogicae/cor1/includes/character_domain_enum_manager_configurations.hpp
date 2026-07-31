#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CharacterDomainEnumManagerConfigurations \
	)

#include "character_domain.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		CharacterDomainEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<CharacterDomainEnumManagerConfigurations>
    {
	public:
		CharacterDomain
			type =
				CharacterDomain
					::ALPHABETIC;

		CharacterDomainEnumManagerConfigurations();
    };    
}

#endif
