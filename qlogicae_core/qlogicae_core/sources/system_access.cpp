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

    std::string SystemAccess::get_executable_dir()
    {
        try
        {
            wchar_t buffer[MAX_PATH];
            DWORD length = GetModuleFileNameW(
                nullptr,
                buffer,
                MAX_PATH
            );
            if (length == 0 ||
                length == MAX_PATH
                )
            {
                return {};
            }

            std::filesystem::path dir =
                std::filesystem::path(buffer)
                .parent_path();
            const std::wstring& wstr =
                dir.wstring();
            if (wstr.empty())
            {
                return {};
            }

            int size_needed =
                WideCharToMultiByte(
                    CP_UTF8,
                    0,
                    wstr.data(),
                    -1,
                    nullptr,
                    0,
                    nullptr,
                    nullptr
                );
            std::string result(
                size_needed - 1,
                0
            );
            WideCharToMultiByte(
                CP_UTF8,
                0,
                wstr.data(),
                -1,
                result.data(),
                size_needed,
                nullptr,
                nullptr
            );

            return result;
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::SystemAccess::get_executable_dir()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::SystemAccess::get_executable_dir(): " +
                exception.what()
            );
        }
    }

    std::string SystemAccess::get_executed_folder()
    {
        try
        {
            return std::filesystem::current_path().string();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::SystemAccess::get_executed_folder()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::SystemAccess::get_executed_folder(): " +
                exception.what()
            );
        }
    }

    std::string SystemAccess::get_executable_folder()
    {
        try
        {
            return get_executable_dir();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::SystemAccess::get_executable_folder()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::SystemAccess::get_executable_folder(): " +
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

    std::string SystemAccess::get_roaming_appdata_folder_path()
    {
        try
        {
            wchar_t* path = nullptr;
            std::wstring result;
            if (SUCCEEDED(SHGetKnownFolderPath(
                FOLDERID_RoamingAppData,
                0,
                NULL,
                &path
            )
            ))
            {
                result.assign(path);
                CoTaskMemFree(path);
            }

            return ENCODER.from_utf16_to_utf8(
                result
            );
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::SystemAccess::get_roaming_appdata_folder_path()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::SystemAccess::get_roaming_appdata_folder_path(): " +
                exception.what()
            );
        }
    }

    std::string SystemAccess::get_local_appdata_folder_path()
    {
        try
        {
            wchar_t* path = nullptr;
            std::wstring result;
            if (SUCCEEDED(SHGetKnownFolderPath(
                FOLDERID_LocalAppData,
                0,
                NULL,
                &path))
                )
            {
                result.assign(path);
                CoTaskMemFree(path);
            }

            return ENCODER.from_utf16_to_utf8(
                result
            );
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::SystemAccess::get_local_appdata_folder_path()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::SystemAccess::get_local_appdata_folder_path(): " +
                exception.what()
            );
        }
    }

    std::string SystemAccess::get_programdata_folder_path()
    {
        try
        {
            wchar_t* path = nullptr;
            std::wstring result;
            if (SUCCEEDED(
                SHGetKnownFolderPath(
                    FOLDERID_ProgramData,
                    0,
                    NULL,
                    &path)
            ))
            {
                result.assign(path);
                CoTaskMemFree(path);
            }

            return ENCODER.from_utf16_to_utf8(result);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::SystemAccess::get_programdata_folder_path()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::SystemAccess::get_programdata_folder_path(): " +
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

    void SystemAccess::get_executable_dir(
        Result<std::string>& result
    )
    {
        wchar_t buffer[MAX_PATH];
        DWORD length = GetModuleFileNameW(
            nullptr,
            buffer,
            MAX_PATH
        );
        if (length == 0 || length == MAX_PATH)
        {
            return result.set_to_bad_status_without_value();
        }

        std::filesystem::path dir =
            std::filesystem::path(buffer)
            .parent_path();
        const std::wstring& wstr =
            dir.wstring();
        if (wstr.empty())
        {
            return result.set_to_bad_status_without_value();
        }

        int size_needed = WideCharToMultiByte(
            CP_UTF8,
            0,
            wstr.data(),
            -1,
            nullptr,
            0,
            nullptr,
            nullptr
        );
        std::string converted(
            size_needed - 1,
            0
        );
        WideCharToMultiByte(
            CP_UTF8,
            0,
            wstr.data(),
            -1,
            converted.data(),
            size_needed,
            nullptr,
            nullptr
        );

        result.set_to_good_status_with_value(
            converted
        );
    }

    void SystemAccess::get_executable_folder(
        Result<std::string>& result
    )
    {
        get_executable_dir(result);
    }

    void SystemAccess::get_executed_folder(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            std::filesystem::current_path().string()
        );
    }

    void SystemAccess::restart_with_admin_access(
        Result<void>& result
    )
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
            return result.set_to_bad_status_without_value(
                "Not admin"
            );
        }

        SHELLEXECUTEINFOW sei = { sizeof(sei) };
        sei.lpVerb = L"runas";
        sei.lpFile = file_path;
        sei.hwnd = nullptr;
        sei.nShow = SW_SHOWNORMAL;

        ShellExecuteExW(&sei);
        ExitProcess(0);

        result.set_to_good_status_without_value();
    }

    void SystemAccess::get_roaming_appdata_folder_path(
        Result<std::string>& result
    )
    {
        wchar_t* path = nullptr;
        std::wstring wresult;
        if (SUCCEEDED(SHGetKnownFolderPath(
            FOLDERID_RoamingAppData,
            0,
            NULL,
            &path))
            )
        {
            wresult.assign(path);
            CoTaskMemFree(path);
        }

        ENCODER.from_utf16_to_utf8(result, wresult);
    }

    void SystemAccess::get_local_appdata_folder_path(
        Result<std::string>& result
    )
    {
        wchar_t* path = nullptr;
        std::wstring wresult;
        if (SUCCEEDED(SHGetKnownFolderPath(
            FOLDERID_LocalAppData,
            0,
            NULL,
            &path))
            )
        {
            wresult.assign(path);
            CoTaskMemFree(path);
        }

        ENCODER.from_utf16_to_utf8(result, wresult);
    }

    void SystemAccess::get_programdata_folder_path(
        Result<std::string>& result
    )
    {
        wchar_t* path = nullptr;
        std::wstring wresult;
        if (SUCCEEDED(SHGetKnownFolderPath(
            FOLDERID_ProgramData,
            0,
            NULL,
            &path))
            )
        {
            wresult.assign(path);
            CoTaskMemFree(path);
        }

        ENCODER.from_utf16_to_utf8(result, wresult);
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
        STARTUPINFOA si{};
        PROCESS_INFORMATION pi{};
        si.cb = sizeof(si);

        if (!CreateProcessA(
            nullptr,
            const_cast<LPSTR>(command.c_str()),
            nullptr,
            nullptr,
            FALSE,
            0,
            nullptr,
            nullptr,
            &si,
            &pi)
            )
        {
            result.set_to_good_status_with_value(
                false
            );
        }

        WaitForSingleObject(pi.hProcess, INFINITE);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        result.set_to_good_status_with_value(
            true
        );
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

    bool SystemAccess::clear_files(
        const std::string& root_path
    )
    {
        try
        {
            Result<void> void_result;

            clear_files(
                void_result,
                root_path
            );

            return void_result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::SystemAccess::clear_files()",
                exception.what()
            );

            return false;
        }
    }

    void SystemAccess::clear_files(
        Result<void>& result,
        const std::string& root_path
    )
    {
        if (root_path.empty() ||
            !std::filesystem::exists(root_path) ||
            !std::filesystem::is_directory(root_path))
        {
            return result.set_to_bad_status_without_value();
        }

        std::wstring wroot = std::filesystem::path(root_path).wstring();

        std::wstring escaped;
        escaped.reserve(wroot.size());
        for (wchar_t character : wroot)
        {
            if (character == L'\'')
            {
                escaped.push_back(L'\'');
                escaped.push_back(L'\'');
            }
            else
            {
                escaped.push_back(character);
            }
        }

        std::wstring cmd =
            L"powershell.exe -NoProfile -NoLogo -Command "
            L"\"Get-ChildItem -LiteralPath '" + escaped +
            L"' -Recurse -File | Remove-Item -Force\"";

        int code = _wsystem(cmd.c_str());

        return (code != 0) ?
            result.set_to_bad_status_without_value() :
            result.set_to_good_status_without_value();
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
