#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RegularExpressionManager \
	)

#include "regular_expression_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		RegularExpressionManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RegularExpressionManagerConfigurations>
    {
    public:
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		RegularExpressionManager();

		bool
			is_direct_pattern_matched(
				const std::string&
					value,
				const std::string&
					pattern
			);

		bool
			is_direct_pattern_matched(
				const std::string&
					value
			);

		bool
			is_pattern_matched(
				const std::string&
					value,
				pcre2_code*
					error_code
			);
	};
}

#endif
