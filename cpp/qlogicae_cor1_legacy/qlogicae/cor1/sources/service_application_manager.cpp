#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ServiceApplicationManager \
	)

#include "../includes/service_application_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
    SERVICE_STATUS
		ServiceApplicationManager
            ::service_status =
                {};

    SERVICE_STATUS_HANDLE
		ServiceApplicationManager
            ::service_handle =
                {};

    HANDLE
		ServiceApplicationManager
            ::stop_event =
                {};
		
    HANDLE
		ServiceApplicationManager
            ::worker_thread =
                {};
		
    HANDLE
		ServiceApplicationManager
            ::heartbeat_thread =
                {};
		
    HANDLE
		ServiceApplicationManager
            ::watchdog_thread =
                {};

    std::atomic<bool>
		ServiceApplicationManager
            ::running =
                { false };
        
    std::atomic<int>
		ServiceApplicationManager
            ::heartbeat_counter =
                { 0 };
        
    std::unordered_map<std::string, std::function<bool()>>
        ServiceApplicationManager
            ::hook_callbacks =
                {};
         
	ServiceApplicationManager
		::ServiceApplicationManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ServiceApplicationManagerConfigurations>()
    {        
		construct();
    }
	
	ServiceApplicationManager
		::~ServiceApplicationManager()
	{
		destruct();
	}
    
    bool
		ServiceApplicationManager
			::construct()
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

            set_hook_callback(
                "service_worker_hook",
                []() { return true; }
            );

            set_hook_callback(
                "heartbeat_worker_hook",
                []() { return true; }
            );

            set_hook_callback(
                "watchdog_worker_hook",
                []() { return true; }
            );

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	bool
		ServiceApplicationManager
			::destruct()
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}
    
    bool
        ServiceApplicationManager
            ::execute_hook_callback(
                const std::string&
                    key
            )
    {
        return
            (hook_callbacks.contains(key)) ?
                hook_callbacks[key]() :
                false;
    }

    bool
        ServiceApplicationManager
            ::set_hook_callback(
                const std::string&
                    key,
                const std::function<bool()>&
                    callback
            )
    {
        hook_callbacks[key] =
            callback;

		return
			true;
    }

    bool
        ServiceApplicationManager
			::is_hook_callback_found(
                const std::string&
                    key
            )
    {
        return
            hook_callbacks
                .contains(key);
    }

    bool
        ServiceApplicationManager
			::handle_backup(const std::string& path)
    {
        return CopyFileA(path.c_str(),(path + ".bak").c_str(),FALSE);
    }

    DWORD WINAPI
        ServiceApplicationManager
			::handle_heartbeat_worker(LPVOID) 
    {
        while (WaitForSingleObject(stop_event, ServiceApplicationManagerConfigurations::heartbeat_worker_hook_delay) != WAIT_OBJECT_0)
        {
            if (ServiceApplicationManagerConfigurations::is_heartbeat_worker_hook_delay_enabled)
            {
                Sleep(ServiceApplicationManagerConfigurations::heartbeat_worker_hook_delay);
            }
            execute_hook_callback("heartbeat_worker_hook");

            heartbeat_counter++;            
        }

        return 0;
    }

    DWORD WINAPI
        ServiceApplicationManager
			::handle_watchdog_worker(LPVOID)
    {
        int last = 0;
        while (WaitForSingleObject(stop_event, ServiceApplicationManagerConfigurations::watchdog_worker_hook_delay) != WAIT_OBJECT_0)
        {
            if (ServiceApplicationManagerConfigurations::is_watchdog_worker_hook_delay_enabled)
            {
                Sleep(ServiceApplicationManagerConfigurations::watchdog_worker_hook_delay);
            }

            execute_hook_callback("watchdog_worker_hook");

            int current = heartbeat_counter.load();

            last = current;
        }

        return 0;
    }

    DWORD WINAPI
        ServiceApplicationManager
			::handle_service_worker(LPVOID)
    {
        while (WaitForSingleObject(stop_event, 0) != WAIT_OBJECT_0)
        {
            if (ServiceApplicationManagerConfigurations::is_service_worker_hook_delay_enabled)
            {
                Sleep(ServiceApplicationManagerConfigurations::service_worker_hook_delay);
            }           

            execute_hook_callback("service_worker_hook");
        }

        return 0;
    }

    void WINAPI
        ServiceApplicationManager
			::handle_control_handler(DWORD code)
    {
        if (code == SERVICE_CONTROL_STOP)
        {
            service_status.dwCurrentState = SERVICE_STOP_PENDING;
            SetServiceStatus(service_handle, &service_status);

            SetEvent(stop_event);
        }
    }

    void WINAPI
        ServiceApplicationManager
			::handle_service_main(DWORD, LPSTR*)
    {            
        service_handle =
            RegisterServiceCtrlHandlerA(ServiceApplicationManagerConfigurations::actual_name.c_str(), &handle_control_handler);

        ZeroMemory(&service_status, sizeof(service_status));

        service_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
        service_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
        service_status.dwCurrentState = SERVICE_START_PENDING;

        SetServiceStatus(service_handle, &service_status);

        stop_event = CreateEventA(nullptr, TRUE, FALSE, nullptr);

        if (!stop_event)
        {
            service_status.dwCurrentState = SERVICE_STOPPED;
            SetServiceStatus(service_handle, &service_status);
            return;
        }

        worker_thread =
            CreateThread(nullptr, 0, &handle_service_worker, nullptr, 0, nullptr);

        heartbeat_thread =
            CreateThread(nullptr, 0, &handle_heartbeat_worker, nullptr, 0, nullptr);

        watchdog_thread =
            CreateThread(nullptr, 0, &handle_watchdog_worker, nullptr, 0, nullptr);

        running = true;

        service_status.dwCurrentState = SERVICE_RUNNING;
        SetServiceStatus(service_handle, &service_status);

        WaitForSingleObject(worker_thread, INFINITE);

        running = false;

        CloseHandle(worker_thread);
        CloseHandle(heartbeat_thread);
        CloseHandle(watchdog_thread);
        CloseHandle(stop_event);

        service_status.dwCurrentState = SERVICE_STOPPED;
        SetServiceStatus(service_handle, &service_status);
    }    

    bool
        ServiceApplicationManager
            ::execute_install_command()
    {           
        try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

            std::string path = SingletonManager
                ::get_singleton<FileSystemManager>()
                    .get_executable_file_path();

            handle_backup(path);

            SC_HANDLE scm =
                OpenSCManagerA(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);

            if (!scm) return false;

            SC_HANDLE svc =
                CreateServiceA(
                    scm,
                    ServiceApplicationManagerConfigurations::actual_name.c_str(),
                    configurations.display_name.c_str(),
                    SERVICE_ALL_ACCESS,
                    SERVICE_WIN32_OWN_PROCESS,
                    configurations.start_type,
                    SERVICE_ERROR_NORMAL,
                    path.c_str(),
                    nullptr, nullptr, nullptr, nullptr, nullptr);

            if (!svc)
            {
                CloseServiceHandle(scm);
                return false;
            }

            SERVICE_DESCRIPTIONA desc{};
            desc.lpDescription = const_cast<LPSTR>(configurations.description.c_str());

            ChangeServiceConfig2A(
                svc,
                SERVICE_CONFIG_DESCRIPTION,
                &desc);

            SC_ACTION actions[1];
            actions[0].Type = SC_ACTION_RESTART;

            if (ServiceApplicationManagerConfigurations::is_service_worker_hook_delay_enabled)
            {
                actions[0].Delay = ServiceApplicationManagerConfigurations::service_worker_hook_delay;            
            }

            SERVICE_FAILURE_ACTIONSA fail{};
            fail.cActions = 1;
            fail.lpsaActions = actions;

            ChangeServiceConfig2A(
                svc,
                SERVICE_CONFIG_FAILURE_ACTIONS,
                &fail);

            CloseServiceHandle(svc);
            CloseServiceHandle(scm);

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
    }

    bool
        ServiceApplicationManager
            ::execute_update_command()
    {            
        try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

            SC_HANDLE scm =
                OpenSCManagerA(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);

            if (!scm) return false;

            SC_HANDLE svc =
                OpenServiceA(scm, ServiceApplicationManagerConfigurations::actual_name.c_str(), SERVICE_CHANGE_CONFIG);

            if (!svc)
            {
                CloseServiceHandle(scm);
                return false;
            }

            ChangeServiceConfigA(
                svc,
                SERVICE_NO_CHANGE,
                configurations.start_type,
                SERVICE_NO_CHANGE,
                nullptr, nullptr, nullptr,
                nullptr, nullptr, nullptr, nullptr);

            SERVICE_DESCRIPTIONA desc{};
            desc.lpDescription = const_cast<LPSTR>(configurations.description.c_str());

            ChangeServiceConfig2A(
                svc,
                SERVICE_CONFIG_DESCRIPTION,
                &desc);

            CloseServiceHandle(svc);
            CloseServiceHandle(scm);

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
    }

    bool
        ServiceApplicationManager
            ::execute_uninstall_command()
    {            
        try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

            SC_HANDLE scm =
                OpenSCManagerA(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);

            if (!scm) return false;

            SC_HANDLE svc =
                OpenServiceA(scm, ServiceApplicationManagerConfigurations::actual_name.c_str(), DELETE);

            if (!svc)
            {
                CloseServiceHandle(scm);
                return false;
            }

            DeleteService(svc);

            CloseServiceHandle(svc);
            CloseServiceHandle(scm);

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
    }

    int
        ServiceApplicationManager
            ::execute_run_command()
    {
        try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			SERVICE_TABLE_ENTRYA table[]
            {
                { const_cast<LPSTR>(ServiceApplicationManagerConfigurations::actual_name.c_str()), &handle_service_main },
                { nullptr, nullptr }
            };

            return StartServiceCtrlDispatcherA(table)
                ? 0 : GetLastError();
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}            
    }

    bool
        ServiceApplicationManager
            ::execute_start_command()
    {            
        try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			SC_HANDLE scm =
                OpenSCManagerA(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);

            if (!scm) return false;

            SC_HANDLE svc =
                OpenServiceA(scm, ServiceApplicationManagerConfigurations::actual_name.c_str(), SERVICE_START);

            if (!svc)
            {
                CloseServiceHandle(scm);
                return false;
            }

            bool
            ok = StartServiceA(svc, 0, nullptr);

            CloseServiceHandle(svc);
            CloseServiceHandle(scm);

            return ok;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
    }

    bool
        ServiceApplicationManager
            ::execute_stop_command()
    {            
        try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			SC_HANDLE scm =
                OpenSCManagerA(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);

            if (!scm) return false;

            SC_HANDLE svc =
                OpenServiceA(scm, ServiceApplicationManagerConfigurations::actual_name.c_str(), SERVICE_STOP);

            if (!svc)
            {
                CloseServiceHandle(scm);
                return false;
            }

            SERVICE_STATUS status{};
            ControlService(svc, SERVICE_CONTROL_STOP, &status);

            CloseServiceHandle(svc);
            CloseServiceHandle(scm);

            return true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
    }
}

#endif
