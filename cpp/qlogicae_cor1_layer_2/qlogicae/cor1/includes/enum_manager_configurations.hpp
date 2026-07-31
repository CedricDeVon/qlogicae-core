#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EnumManagerConfigurations \
	)

#include "text_case.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		EnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<EnumManagerConfigurations>
	{
	public:	
		bool
			is_text_case_conversion_enabled =
				true;

		TextCase
			text_case =
				TextCase
					::UPPERCASE;

		EnumManagerConfigurations();
	};
}

#endif
