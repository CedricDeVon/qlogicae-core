#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		UuidEnumManagerConfigurations \
	)

#include "uuid.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		UuidEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<UuidEnumManagerConfigurations>
	{
	public:	
		Uuid
			type =
				Uuid
					::V4;

		UuidEnumManagerConfigurations();
	};
}

#endif
