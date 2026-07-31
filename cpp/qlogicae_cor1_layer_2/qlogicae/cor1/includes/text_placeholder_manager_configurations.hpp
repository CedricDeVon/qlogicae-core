#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextPlaceholderManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		TextPlaceholderManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<TextPlaceholderManagerConfigurations>
	{
	public:		
		bool
			is_conditional_callback_enabled =
				true;

		std::function<bool(const std::string& text)>
			conditional_callback =
				[](const std::string& text){ return text.empty(); };

		std::string
			placeholder =
				"None";

		TextPlaceholderManagerConfigurations();
	};
}

#endif
