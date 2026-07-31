#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextErrorManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		TextErrorManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<TextErrorManagerConfigurations>
	{
	public:
		bool
			is_specified_length_enabled =
				false;			

		size_t
			specified_length =
				128;

		std::string
			title =
				"Exception";
				
		std::string
			origin =
				"";

		std::string
			separator =
				"-";

		TextErrorManagerConfigurations();
	};
}

#endif
