#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ResultsStatusEnumManagerConfigurations \
	)

#include "results_status.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		ResultsStatusEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<ResultsStatusEnumManagerConfigurations>
	{
	public:	
		ResultsStatus
			type =
				ResultsStatus
					::GOOD;

		ResultsStatusEnumManagerConfigurations();
	};
}

#endif
