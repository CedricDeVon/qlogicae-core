#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EntityActivationManager \
	)

#include "entity_activation_status.hpp"
#include "entity_activation_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		EntityActivationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<EntityActivationManagerConfigurations>
    {
    public:
		std::unordered_map<void*, EntityActivationStatus>
			entity_collection;

		EntityActivationManager();

		EntityActivationStatus
			get_entity_status(
				void*
					value
			);

		bool        
			set_entity_status(
				void*
					value,
				const EntityActivationStatus&
					status
			);

		bool        
			is_entity_status_equal(
				void*
					value,
				const EntityActivationStatus&
					status
			);

		bool        
			remove_entity(
				void*
					value
			);
        
		bool        
			clear_entities();		
	};
}

#endif
