#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		QLogicaeConsoleApplicationManager \
	)

#include "abstract_class.hpp"
#include "qlogicae_console_application_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    int main(int, char**);

    class
		QLogicaeConsoleApplicationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<QLogicaeConsoleApplicationManagerConfigurations>
    {
    public:				
		QLogicaeConsoleApplicationManager();
		
		~QLogicaeConsoleApplicationManager();

        bool
            construct();

		bool
            destruct();
    };
}

#endif

