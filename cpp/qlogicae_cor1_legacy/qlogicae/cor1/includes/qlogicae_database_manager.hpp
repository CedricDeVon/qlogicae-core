#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		QLogicaeDatabaseManager \
	)

#include "abstract_class.hpp"
#include "qlogicae_database_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		QLogicaeDatabaseManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<QLogicaeDatabaseManagerConfigurations>
    {
    public:		
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		QLogicaeDatabaseManager();
		
		~QLogicaeDatabaseManager();

		bool
			construct();

		bool
			destruct();

		bool
			setup(
				const QLogicaeDatabaseManagerConfigurations&
					new_configurations
			);

		bool
            reset();
    };
}

#endif
