#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		QLogicaeCryptographyManager \
	)

#include "abstract_class.hpp"
#include "qlogicae_cryptography_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	enum class
		QLogicaeCryptography :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_ENUM_INHERITED_TYPE
	{
		METHOD_1,

		METHOD_2,

		QLOGICAE_COR1__BASE__HPP_CPP__ENUM_CONSTANTS
	}

    class
		QLogicaeCryptographyManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<QLogicaeCryptographyManagerConfigurations>
    {
    public:		
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		QLogicaeCryptographyManager();
		
		~QLogicaeCryptographyManager();

		bool
			construct();

		bool
			destruct();

		
    };
}

#endif
