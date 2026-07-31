#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ServiceApplicationManager \
	)

#include "service_application_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		ServiceApplicationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ServiceApplicationManagerConfigurations>
    {
    public:		
		static SERVICE_STATUS
			service_status;

        static SERVICE_STATUS_HANDLE
			service_handle;

        static HANDLE
			stop_event;
		
        static HANDLE
			worker_thread;
		
        static HANDLE
			heartbeat_thread;
		
        static HANDLE
			watchdog_thread;

        static std::atomic<bool>
			running;

        static std::atomic<int>
			heartbeat_counter;

        static std::unordered_map<std::string, std::function<bool()>>
            hook_callbacks;

		ServiceApplicationManager();
		
		~ServiceApplicationManager();

		bool
			construct();

		bool
			destruct();

        bool
            execute_install_command();

        bool
            execute_update_command();

        bool
            execute_uninstall_command();

        int
            execute_run_command();

        bool
            execute_start_command();

        bool
            execute_stop_command();

        static bool
            execute_hook_callback(
                const std::string&
                    key
            );

        static bool
            set_hook_callback(
                const std::string&
                    key,
                const std::function<bool()>&
                    callback
            );

        static bool
            is_hook_callback_found(
                const std::string&
                    key
            );
        
        static bool
			handle_backup(const std::string& path);

        static DWORD WINAPI
            handle_heartbeat_worker(LPVOID);

        static DWORD WINAPI
            handle_watchdog_worker(LPVOID);

        static DWORD WINAPI
            handle_service_worker(LPVOID);

        static void WINAPI
            handle_control_handler(DWORD code);

        static void WINAPI
            handle_service_main(DWORD, LPSTR*);

    };
}

#endif
