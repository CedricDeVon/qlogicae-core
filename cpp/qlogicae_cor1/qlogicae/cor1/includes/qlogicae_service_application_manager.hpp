#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		QLogicaeServiceApplicationManager \
	)

#include "qlogicae_service_application_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		QLogicaeServiceApplicationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<QLogicaeServiceApplicationManagerConfigurations>
    {
    public:				
		QLogicaeServiceApplicationManager();
		
		~QLogicaeServiceApplicationManager();

		bool
			construct();

		bool
			destruct();
    };
}

#endif
