#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		CharacterDomainManager \
	)

#include "character_domain.hpp"
#include "character_domain_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		CharacterDomainManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<CharacterDomainManagerConfigurations>
    {
    public:		
		CharacterDomainManager();

		~CharacterDomainManager();

		bool
			construct();

		bool
			destruct();

		std::string
			get_value(
				const CharacterDomain&
					character_domain
			);

		std::string
			get_value();
    };
}

#endif
