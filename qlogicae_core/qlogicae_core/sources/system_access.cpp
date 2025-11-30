#include "pch.hpp"

#include "../includes/system_access.hpp"

namespace QLogicaeCore
{
    SystemAccess::SystemAccess()
    {

    }

    SystemAccess::~SystemAccess()
    {

    }

    bool SystemAccess::setup()
    {
        try
        {
            Result<void> result;

            setup(result);

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::SystemAccess::setup()",
                exception.what()
            );

            return false;
        }
    }

    void SystemAccess::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    std::future<bool> SystemAccess::setup_async()
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    setup()
                );
            }
        );

        return future;
    }

    void SystemAccess::setup_async(
        const std::function<void(const bool& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                callback(
                    setup()
                );
            }
        );
    }

    void SystemAccess::setup_async(
        Result<std::future<void>>& result
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(result);

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void SystemAccess::setup_async(
        const std::function<void(Result<void>& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                Result<void> result;

                setup(result);

                callback(
                    result
                );
            }
        );
    }

    bool SystemAccess::has_admin_access()
    {
        try
        {
            BOOL is_admin = FALSE;
            PSID administrators_group = nullptr;
            SID_IDENTIFIER_AUTHORITY nt_authority = SECURITY_NT_AUTHORITY;

            if (AllocateAndInitializeSid(
                &nt_authority,
                2,
                SECURITY_BUILTIN_DOMAIN_RID,
                DOMAIN_ALIAS_RID_ADMINS,
                0, 0, 0, 0, 0, 0,
                &administrators_group))
            {
                CheckTokenMembership(
                    nullptr,
                    administrators_group,
                    &is_admin
                );
                FreeSid(administrators_group);
            }

            return is_admin == TRUE;
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::SystemAccess::has_admin_access()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() + "QLogicaeCore::SystemAccess::has_admin_access(): " +
                exception.what()
            );
        }
    }

    void SystemAccess::restart_with_admin_access()
    {
        try
        {
            wchar_t file_path[MAX_PATH];
            if (::GetEnvironmentVariableW(
                L"VSAPPIDDIR",
                nullptr,
                0
            ) > 0 ||
                GetModuleFileNameW(
                    nullptr,
                    file_path,
                    MAX_PATH
                ) == 0)
            {
                ExitProcess(1);
                return;
            }

            SHELLEXECUTEINFOW sei = { sizeof(sei) };
            sei.lpVerb = L"runas";
            sei.lpFile = file_path;
            sei.hwnd = nullptr;
            sei.nShow = SW_SHOWNORMAL;

            ShellExecuteExW(&sei);
            ExitProcess(0);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::SystemAccess::restart_with_admin_access()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::SystemAccess::restart_with_admin_access(): " +
                exception.what()
            );
        }
    }

    void SystemAccess::has_admin_access(
        Result<void>& result
    )
    {
        BOOL is_admin = FALSE;
        PSID administrators_group = nullptr;
        SID_IDENTIFIER_AUTHORITY nt_authority =
            SECURITY_NT_AUTHORITY;

        if (AllocateAndInitializeSid(
            &nt_authority,
            2,
            SECURITY_BUILTIN_DOMAIN_RID,
            DOMAIN_ALIAS_RID_ADMINS,
            0, 0, 0, 0, 0, 0,
            &administrators_group)
            )
        {
            CheckTokenMembership(
                nullptr,
                administrators_group,
                &is_admin
            );
            FreeSid(administrators_group);
        }

        if (is_admin == TRUE)
        {
            return result.set_to_good_status_without_value();
        }
        else
        {
            return result.set_to_bad_status_without_value();
        }
    }

    bool SystemAccess::run_process(
        const std::string& command
    )
    {
        try
        {
            Result<bool> result;

            run_process(result, command);

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::SystemAccess::run_process()",
                exception.what()
            );

            return false;
        }
    }

    void SystemAccess::run_process(
        Result<bool>& result,
        const std::string& command
    )
    {        
        STARTUPINFOA startup_info{};
        PROCESS_INFORMATION process_info{};
        startup_info.cb = sizeof(STARTUPINFOA);
        startup_info.dwFlags = STARTF_USESHOWWINDOW;
        startup_info.wShowWindow = SW_HIDE;

        std::string full_cmd =
            absl::StrCat("cmd.exe /c \"", command, "\"");

        BOOL created = CreateProcessA(
            NULL,
            const_cast<LPSTR>(full_cmd.c_str()),
            NULL,
            NULL,
            FALSE,
            CREATE_NO_WINDOW,
            NULL,
            NULL,
            &startup_info,
            &process_info
        );

        if (created == FALSE)
        {
            result.set_to_bad_status_with_value(false);
            return;
        }

        CloseHandle(process_info.hThread);
        CloseHandle(process_info.hProcess);

        result.set_to_good_status_with_value(true);
    }

    std::future<bool> SystemAccess::run_process_async(
        const std::string& command
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, command,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    run_process(
                        command
                    )
                );
            }
        );

        return future;
    }

    void SystemAccess::run_process_async(
        const std::function<void(const bool& result)>& callback,
        const std::string& command
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, command]() mutable
            {
                callback(
                    run_process(
                        command
                    )
                );
            }
        );
    }

    void SystemAccess::run_process_async(
        Result<std::future<bool>>& result,
        const std::string& command
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, command,
            promise = std::move(promise)]() mutable
            {
                Result<bool> result;

                run_process(
                    result,
                    command
                );

                promise.set_value(
                    result.get_value()
                );
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void SystemAccess::run_process_async(
        const std::function<void(Result<bool>& result)>& callback,
        const std::string& command
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, command]() mutable
            {
                Result<bool> result;

                run_process(
                    result,
                    command
                );

                callback(
                    result
                );
            }
        );
    }

    bool SystemAccess::terminate()
    {
        try
        {
            Result<void> result;

            terminate(result);

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::SystemAccess::terminate()",
                exception.what()
            );

            return false;
        }
    }

    void SystemAccess::terminate(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    std::future<bool> SystemAccess::terminate_async()
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    terminate()
                );
            }
        );

        return future;
    }

    void SystemAccess::terminate_async(
        const std::function<void(const bool& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                callback(
                    terminate()
                );
            }
        );
    }

    void SystemAccess::terminate_async(
        Result<std::future<void>>& result
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                Result<void> result;

                terminate(result);

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void SystemAccess::terminate_async(
        const std::function<void(Result<void>& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                Result<void> result;

                terminate(result);

                callback(
                    result
                );
            }
        );
    }

    SystemAccess& SystemAccess::get_instance()
    {
        static SystemAccess get_instance;

        return get_instance;
    }

    void SystemAccess::get_instance(
        Result<SystemAccess*>& results
    )
    {
        static SystemAccess instance;

        results.set_to_good_status_with_value(&instance);
    }
}
