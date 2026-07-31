#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TimeManagerConfigurations \
	)

#include "time_zone.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		TimeManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<TimeManagerConfigurations>
	{
	public:
		TimeZone
			time_zone =
				TimeZone::UTC;

		TimeManagerConfigurations();
	};
}

#endif
