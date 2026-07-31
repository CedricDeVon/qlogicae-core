#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		LogManagerConfigurations \
	)

#include "log_level.hpp"
#include "log_format.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	template <typename DerivedConfigurations> struct
		LogManagerConfigurations :
			AbstractConfigurations<DerivedConfigurations>
    {
	public:		
		bool
			is_output_override_enabled =
				false;

		bool
			is_output_enabled =
				false;

		LogLevel
			log_level =
				LogLevel
					::INFO;

		std::string
			text =
				"Message";

		LogManagerConfigurations();		
    };

	template <typename DerivedConfigurations>
		LogManagerConfigurations<DerivedConfigurations>
			::LogManagerConfigurations() :
					AbstractConfigurations<DerivedConfigurations>()
	{
		
	}
}

#endif
