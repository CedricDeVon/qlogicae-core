#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		QLogicaeLoggingManager \
	)

#include "abstract_class.hpp"
#include "qlogicae_logging_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		QLogicaeLoggingManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<QLogicaeLoggingManagerConfigurations>
    {
    public:				
		QLogicaeLoggingManager();
		
		~QLogicaeLoggingManager();

		bool
			construct();

		bool
			destruct();
    };
}

#endif
