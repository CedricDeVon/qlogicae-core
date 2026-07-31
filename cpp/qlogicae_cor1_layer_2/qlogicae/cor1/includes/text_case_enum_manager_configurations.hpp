#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextCaseEnumManagerConfigurations \
	)

#include "text_case.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		TextCaseEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<TextCaseEnumManagerConfigurations>
	{
	public:
		TextCase
			type =
				TextCase
					::NONE;

		TextCaseEnumManagerConfigurations();
	};
}

#endif
