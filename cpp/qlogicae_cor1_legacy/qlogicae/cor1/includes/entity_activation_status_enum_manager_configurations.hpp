#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EntityActivationStatusEnumManagerConfigurations \
	)

#include "entity_activation_status.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		EntityActivationStatusEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<EntityActivationStatusEnumManagerConfigurations>
	{
	public:	
		EntityActivationStatus
			type =
				EntityActivationStatus
					::ACTIVE;

		EntityActivationStatusEnumManagerConfigurations();
	};
}

#endif
