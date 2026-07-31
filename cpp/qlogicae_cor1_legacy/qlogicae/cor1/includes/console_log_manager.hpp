#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ConsoleLogManager \
	)

#include "log_level.hpp"
#include "text_log_manager.hpp"
#include "console_log_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		ConsoleLogManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ConsoleLogManagerConfigurations>
    {
    public:
		ConsoleLogManager();

		bool
			log_formatted_text(
				const std::string&
					text,
				const LogLevel&
					log_level
			);

		bool
			log_formatted_text(
				const std::string&
					text
			);

		bool
			log_formatted_text();


		bool
			log_raw_text(
				const std::string&
					text
			);

		bool
			log_raw_text();
    };
}

#endif
