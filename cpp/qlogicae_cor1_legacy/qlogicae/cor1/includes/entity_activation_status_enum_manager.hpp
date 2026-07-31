#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EntityActivationStatusEnumManager \
	)

#include "entity_activation_status.hpp"
#include "entity_activation_status_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		EntityActivationStatusEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<EntityActivationStatusEnumManagerConfigurations>
    {
    public:
		EntityActivationStatusEnumManager();

		std::string
			convert_enum_to_string(
				const EntityActivationStatus&
					value
			);

		std::string
			convert_enum_to_string();

		EntityActivationStatus
			convert_string_to_enum(
				const std::string&
					value
			);

		EntityActivationStatus
			convert_string_to_enum();
    };
}

#endif
