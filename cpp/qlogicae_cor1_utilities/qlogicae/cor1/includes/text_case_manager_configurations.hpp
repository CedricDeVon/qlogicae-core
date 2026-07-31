#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextCaseManagerConfigurations \
	)

#include "text_case.hpp"
#include "abstract_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		TextCaseManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<TextCaseManagerConfigurations>
	{
	public:
		bool
			is_specified_length_enabled =
				false;			

		size_t
			specified_length =
				128;

		TextCase
			target_type =
				TextCase::NONE;

		TextCaseManagerConfigurations();
	};
}

#endif
