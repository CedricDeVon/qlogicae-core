#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogFormatEnumManagerConfigurations \
	)

#include "log_format.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		LogFormatEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<LogFormatEnumManagerConfigurations>
	{
	public:	
		LogFormat
			type =
				LogFormat
					::STANDARD;

		LogFormatEnumManagerConfigurations();
	};
}

#endif
