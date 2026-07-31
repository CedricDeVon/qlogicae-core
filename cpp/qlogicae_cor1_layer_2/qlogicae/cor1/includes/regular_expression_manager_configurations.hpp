#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RegularExpressionManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		RegularExpressionManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<RegularExpressionManagerConfigurations>
	{
	public:
		std::string
			pattern =
				"";

		RegularExpressionManagerConfigurations();
	};
}

#endif
