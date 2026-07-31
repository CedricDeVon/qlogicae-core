#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextEncodingEnumManagerConfigurations \
	)

#include "text_encoding.hpp"
#include "abstract_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		TextEncodingEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<TextEncodingEnumManagerConfigurations>
	{
	public:
		TextEncoding
			type =
				TextEncoding
					::NONE;

		TextEncodingEnumManagerConfigurations();
	};
}

#endif
