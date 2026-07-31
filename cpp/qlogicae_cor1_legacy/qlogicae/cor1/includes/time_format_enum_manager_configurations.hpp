#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeFormatEnumManagerConfigurations \
	)

#include "time_format.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		TimeFormatEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<TimeFormatEnumManagerConfigurations>
	{
	public:	
		TimeFormat
			type =
				TimeFormat
					::FULL_TIMESTAMP;

		TimeFormatEnumManagerConfigurations();
	};
}

#endif
