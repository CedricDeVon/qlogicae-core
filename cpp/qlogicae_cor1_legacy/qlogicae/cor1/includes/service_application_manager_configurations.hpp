#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ServiceApplicationManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		ServiceApplicationManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<ServiceApplicationManagerConfigurations>
    {
	public:				
        static std::string
			actual_name;

        static std::string
			display_name;

        static std::string
			description;

        static DWORD
			start_type;

		static bool
			is_service_worker_hook_delay_enabled;

		static DWORD
			service_worker_hook_delay;

		static bool
			is_heartbeat_worker_hook_delay_enabled;

		static DWORD
			heartbeat_worker_hook_delay;

		static bool
			is_watchdog_worker_hook_delay_enabled;

		static DWORD
			watchdog_worker_hook_delay;

		ServiceApplicationManagerConfigurations();
    };    
}

#endif
