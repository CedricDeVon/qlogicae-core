#include "pch.hpp"

// #include "main.hpp"

// #pragma comment(linker, "/SUBSYSTEM:WINDOWS")
// #pragma comment(linker, "/ENTRY:mainCRTStartup")

// #include <iostream>
// #include <Windows.h>

int main(int, char**)
{    
    return 0;
}

/*

#include <iostream>
#include <string>
#include <cstdio>
#include <nlohmann/json.hpp>

std::string run_python()
{
    std::string output;
    char buffer[128];

    FILE* pipe = _popen("python script.py","r");

    while(fgets(buffer,sizeof(buffer),pipe))
    {
        output += buffer;
    }

    _pclose(pipe);
    return output;
}

int main()
{
    std::string raw = run_python();

    auto json = nlohmann::json::parse(raw);

    std::cout << json["result"] << std::endl;
}




#include <Windows.h>

#pragma warning(push)
#pragma warning(disable : 4244 4251 4275)

#pragma warning(pop)

namespace config
{
    struct ServiceConfig
    {
        std::string name = "MinimalCppService";
        std::string display_name = "Minimal C++ Service";
        std::string description = "Enterprise Windows Service Framework";

        DWORD start_type = SERVICE_AUTO_START;

        std::string log_file = "C:\\service_logs\\service.log";
        std::string config_file = "C:\\service_config\\service.json";
    };

    inline ServiceConfig load()
    {
        return ServiceConfig{};
    }

    inline void reload(ServiceConfig& cfg)
    {
        cfg = load();
    }
}

namespace logging
{
    enum class level { info, warn, error, critical };

    inline HANDLE event_source = nullptr;

    inline void init(const std::string& name)
    {
        event_source =
            RegisterEventSourceA(nullptr, name.c_str());
    }

    inline void event(level lvl, const std::string& msg)
    {
        if (!event_source) return;

        WORD type = EVENTLOG_INFORMATION_TYPE;

        if (lvl == level::warn) type = EVENTLOG_WARNING_TYPE;
        if (lvl == level::error || lvl == level::critical)
            type = EVENTLOG_ERROR_TYPE;

        LPCSTR s[1]{ msg.c_str() };

        ReportEventA(event_source, type, 0, 0, nullptr, 1, 0, s, nullptr);
    }

    inline void file(const std::string& path, const std::string& msg)
    {
        std::ofstream f(path, std::ios::app);
        f << msg << "\n";
    }
}

namespace deploy
{
    inline std::string exe_path()
    {
        char buf[MAX_PATH]{};
        GetModuleFileNameA(nullptr, buf, MAX_PATH);
        return std::string(buf);
    }

    inline bool backup(const std::string& path)
    {
        return CopyFileA(path.c_str(), (path + ".bak").c_str(), FALSE);
    }

    inline bool rollback(const std::string& path)
    {
        return CopyFileA((path + ".bak").c_str(), path.c_str(), FALSE);
    }
}

SERVICE_STATUS service_status{};
SERVICE_STATUS_HANDLE service_handle{};

HANDLE stop_event{};
HANDLE worker_thread{};
HANDLE heartbeat_thread{};
HANDLE watchdog_thread{};

std::atomic<bool> running{false};

std::atomic<int> heartbeat_counter{0};

DWORD WINAPI heartbeat_worker(LPVOID)
{
    while (WaitForSingleObject(stop_event, 5000) != WAIT_OBJECT_0)
    {
        heartbeat_counter++;

        logging::event(
            logging::level::info,
            "heartbeat tick: " + std::to_string(heartbeat_counter.load()));

        Sleep(5000);
    }
    return 0;
}

DWORD WINAPI watchdog_worker(LPVOID)
{
    int last = 0;

    while (WaitForSingleObject(stop_event, 5000) != WAIT_OBJECT_0)
    {
        int current = heartbeat_counter.load();

        if (current == last)
        {
            logging::event(logging::level::critical, "watchdog detected stall");
        }

        last = current;
    }

    return 0;
}

DWORD WINAPI service_worker(LPVOID)
{
    while (WaitForSingleObject(stop_event, 0) != WAIT_OBJECT_0)
    {
        Sleep(1000);
    }
    return 0;
}

void WINAPI control_handler(DWORD code)
{
    if (code == SERVICE_CONTROL_STOP)
    {
        service_status.dwCurrentState = SERVICE_STOP_PENDING;
        SetServiceStatus(service_handle, &service_status);

        SetEvent(stop_event);

        logging::event(logging::level::info, "service stopping");
    }
}

void WINAPI service_main(DWORD, LPSTR*)
{
    auto cfg = config::load();
    logging::init(cfg.name);

    service_handle =
        RegisterServiceCtrlHandlerA(cfg.name.c_str(), control_handler);

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
        CreateThread(nullptr, 0, service_worker, nullptr, 0, nullptr);

    heartbeat_thread =
        CreateThread(nullptr, 0, heartbeat_worker, nullptr, 0, nullptr);

    watchdog_thread =
        CreateThread(nullptr, 0, watchdog_worker, nullptr, 0, nullptr);

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

bool install_service()
{
    auto cfg = config::load();
    std::string path = deploy::exe_path();

    deploy::backup(path);

    SC_HANDLE scm =
        OpenSCManagerA(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);

    if (!scm) return false;

    SC_HANDLE svc =
        CreateServiceA(
            scm,
            cfg.name.c_str(),
            cfg.display_name.c_str(),
            SERVICE_ALL_ACCESS,
            SERVICE_WIN32_OWN_PROCESS,
            cfg.start_type,
            SERVICE_ERROR_NORMAL,
            path.c_str(),
            nullptr, nullptr, nullptr, nullptr, nullptr);

    if (!svc)
    {
        CloseServiceHandle(scm);
        return false;
    }

    SERVICE_DESCRIPTIONA desc{};
    desc.lpDescription = const_cast<LPSTR>(cfg.description.c_str());

    ChangeServiceConfig2A(
        svc,
        SERVICE_CONFIG_DESCRIPTION,
        &desc);

    SC_ACTION actions[1];
    actions[0].Type = SC_ACTION_RESTART;
    actions[0].Delay = 5000;

    SERVICE_FAILURE_ACTIONSA fail{};
    fail.cActions = 1;
    fail.lpsaActions = actions;

    ChangeServiceConfig2A(
        svc,
        SERVICE_CONFIG_FAILURE_ACTIONS,
        &fail);

    CloseServiceHandle(svc);
    CloseServiceHandle(scm);

    return true;
}

bool update_service()
{
    auto cfg = config::load();

    SC_HANDLE scm =
        OpenSCManagerA(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);

    if (!scm) return false;

    SC_HANDLE svc =
        OpenServiceA(scm, cfg.name.c_str(), SERVICE_CHANGE_CONFIG);

    if (!svc)
    {
        CloseServiceHandle(scm);
        return false;
    }

    ChangeServiceConfigA(
        svc,
        SERVICE_NO_CHANGE,
        cfg.start_type,
        SERVICE_NO_CHANGE,
        nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr);

    SERVICE_DESCRIPTIONA desc{};
    desc.lpDescription = const_cast<LPSTR>(cfg.description.c_str());

    ChangeServiceConfig2A(
        svc,
        SERVICE_CONFIG_DESCRIPTION,
        &desc);

    CloseServiceHandle(svc);
    CloseServiceHandle(scm);

    return true;
}

bool uninstall_service()
{
    auto cfg = config::load();

    SC_HANDLE scm =
        OpenSCManagerA(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);

    if (!scm) return false;

    SC_HANDLE svc =
        OpenServiceA(scm, cfg.name.c_str(), DELETE);

    if (!svc)
    {
        CloseServiceHandle(scm);
        return false;
    }

    DeleteService(svc);

    CloseServiceHandle(svc);
    CloseServiceHandle(scm);

    return true;
}

int run_service()
{
    auto cfg = config::load();

    SERVICE_TABLE_ENTRYA table[]
    {
        { const_cast<LPSTR>(cfg.name.c_str()), service_main },
        { nullptr, nullptr }
    };

    return StartServiceCtrlDispatcherA(table)
        ? 0
        : GetLastError();
}

bool start_service()
{
    auto cfg = config::load();

    SC_HANDLE scm =
        OpenSCManagerA(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);

    if (!scm) return false;

    SC_HANDLE svc =
        OpenServiceA(scm, cfg.name.c_str(), SERVICE_START);

    if (!svc)
    {
        CloseServiceHandle(scm);
        return false;
    }

    bool ok = StartServiceA(svc, 0, nullptr);

    CloseServiceHandle(svc);
    CloseServiceHandle(scm);

    return ok;
}

bool stop_service()
{
    auto cfg = config::load();

    SC_HANDLE scm =
        OpenSCManagerA(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);

    if (!scm) return false;

    SC_HANDLE svc =
        OpenServiceA(scm, cfg.name.c_str(), SERVICE_STOP);

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

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        std::string a = argv[1];

        if (a == "--install") return install_service() ? 0 : 1;
        if (a == "--update") return update_service() ? 0 : 1;
        if (a == "--uninstall") return uninstall_service() ? 0 : 1;
        if (a == "--start") return start_service() ? 0 : 1;
        if (a == "--stop") return stop_service() ? 0 : 1;
    }

    return run_service();
}
namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_SANDBOX_NAMESPACE_NAME
{

}
*/
