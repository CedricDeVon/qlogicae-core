#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileLogManager \
	)

#include "log_level.hpp"
#include "text_log_manager.hpp"
#include "file_log_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		FileLogManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileLogManagerConfigurations>
    {
    public:
		FileLogManager();

		~FileLogManager();

		bool
			destruct();

		bool
			reset();

		std::string
			get_file_output_path(
				const std::string&
					key
			);

		bool
			is_file_output_path_found(
				const std::string&
					key
			);

		bool
			set_file_output_path(
				const std::string&
					key,
				const std::function<std::string()>&
					value
			);

		bool
			remove_file_output_path(
				const std::string&
					key
			);
		
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
