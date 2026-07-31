#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ValidationManager \
	)

#include "validation_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	class
		ValidationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ValidationManagerConfigurations>
	{
	public:
		ValidationManager();

		bool
			validate(
				const std::function<bool()>&
					conditional_callback
			);

		bool
			validate();
	};
}

#endif
