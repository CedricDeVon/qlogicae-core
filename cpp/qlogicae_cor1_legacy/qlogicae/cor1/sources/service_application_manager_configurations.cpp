#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ServiceApplicationManagerConfigurations \
	)

#include "../includes/service_application_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	std::string
		ServiceApplicationManagerConfigurations
			::actual_name =
				"QLogicae Service";

    std::string
		ServiceApplicationManagerConfigurations
			::display_name =
				"QLogicae Service";

    std::string
		ServiceApplicationManagerConfigurations
			::description =
				"Description";

    DWORD
		ServiceApplicationManagerConfigurations
			::start_type =
				SERVICE_AUTO_START;

	bool
		ServiceApplicationManagerConfigurations
			::is_service_worker_hook_delay_enabled =
				true;

	DWORD
		ServiceApplicationManagerConfigurations
			::service_worker_hook_delay =
				5000;

	bool
		ServiceApplicationManagerConfigurations
			::is_heartbeat_worker_hook_delay_enabled =
				true;

	DWORD
		ServiceApplicationManagerConfigurations
			::heartbeat_worker_hook_delay =
				1000;

	bool
		ServiceApplicationManagerConfigurations
			::is_watchdog_worker_hook_delay_enabled =
				true;

	DWORD
		ServiceApplicationManagerConfigurations
			::watchdog_worker_hook_delay =
				1000;

	ServiceApplicationManagerConfigurations
		::ServiceApplicationManagerConfigurations() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<ServiceApplicationManagerConfigurations>()
	{
		
	}
}

#endif

