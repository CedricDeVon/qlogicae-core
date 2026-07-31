#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsSystemAccessManager \
	)

#include "windows_system_access_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	class
		WindowsSystemAccessManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<WindowsSystemAccessManagerConfigurations>
	{
	public:
		WindowsSystemAccessManager();

		bool
			run_process(
				const std::string&
					command
			);

		bool
			has_admin_access();

		bool
			restart_with_admin_access();
	};
}

#endif
