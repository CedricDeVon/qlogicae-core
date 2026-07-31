#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		QLogicaeCacheManager \
	)

#include "qlogicae_cryptography_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		QLogicaeCacheManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<QLogicaeCacheManagerConfigurations>
    {
    public:		
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		QLogicaeCacheManager();
		
		~QLogicaeCacheManager();

		bool
			construct();

		bool
			destruct();

		bool
			setup(
				const QLogicaeCacheManagerConfigurations&
					new_configurations
			);

		bool
            reset();
    };
}

#endif
