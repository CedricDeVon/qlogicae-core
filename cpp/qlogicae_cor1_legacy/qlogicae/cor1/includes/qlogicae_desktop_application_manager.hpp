#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		QLogicaeDesktopApplicationManager \
	)

#include "abstract_class.hpp"
#include "qlogicae_desktop_application_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		QLogicaeDesktopApplicationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<QLogicaeDesktopApplicationManagerConfigurations>
    {
    public:				
		QLogicaeDesktopApplicationManager();

		~QLogicaeDesktopApplicationManager();

        bool
            construct();

		bool
            destruct();
    };
}

#endif
