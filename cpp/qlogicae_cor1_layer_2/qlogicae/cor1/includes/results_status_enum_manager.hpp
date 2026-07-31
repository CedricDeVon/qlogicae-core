#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ResultsStatusEnumManager \
	)

#include "results_status.hpp"
#include "results_status_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		ResultsStatusEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ResultsStatusEnumManagerConfigurations>
    {
    public:
		ResultsStatusEnumManager();

		std::string
			convert_enum_to_string(
				const ResultsStatus&
					value
			);

		std::string
			convert_enum_to_string();

		ResultsStatus
			convert_string_to_enum(
				const std::string&
					value
			);

		ResultsStatus
			convert_string_to_enum();
    };
}

#endif
