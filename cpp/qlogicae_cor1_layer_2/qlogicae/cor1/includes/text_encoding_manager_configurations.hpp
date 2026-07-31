#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextEncodingManagerConfigurations \
	)

#include "text_case.hpp"
#include "text_encoding.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		TextEncodingManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<TextEncodingManagerConfigurations>
	{
	public:
		TextEncoding
			original_type =
				TextEncoding::NONE;

		TextEncoding
			target_type =
				TextEncoding::NONE;

		TextEncodingManagerConfigurations();
	};
}

#endif
