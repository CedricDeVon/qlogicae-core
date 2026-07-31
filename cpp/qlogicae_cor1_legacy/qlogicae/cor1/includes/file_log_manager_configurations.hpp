#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileLogManagerConfigurations \
	)

#include "log_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		FileLogManagerConfigurations :
			LogManagerConfigurations<FileLogManagerConfigurations>
    {
	public:
		std::unordered_map<std::string, std::function<std::string()>>
			file_output_paths =
				{};

		FileLogManagerConfigurations();
    };
}

#endif
