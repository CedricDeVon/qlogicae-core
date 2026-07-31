#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		QLogicaeFileSystemManager \
	)

#include "qlogicae_file_system_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		QLogicaeFileSystemManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<QLogicaeFileSystemManagerConfigurations>
    {
    public:
		QLogicaeFileSystemManager();

		~QLogicaeFileSystemManager();
		
        bool
            construct();

		bool
            destruct();
    };
}

#endif

