#pragma once

#include "pch.h"

#include "system_access.hpp"

namespace QLogicaeCore
{
    bool QLogicaeCore::SystemAccess::has_admin_access() const
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
            CheckTokenMembership(nullptr, administrators_group, &is_admin);
            FreeSid(administrators_group);
        }

        return is_admin == TRUE;
    }

    std::string SystemAccess::get_executable_dir() const
    {
        wchar_t buffer[MAX_PATH];
        DWORD length = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
        if (length == 0 || length == MAX_PATH)
        {
            return {};
        }
        std::filesystem::path dir = std::filesystem::path(buffer).parent_path();
        const std::wstring& wstr = dir.wstring();
        if (wstr.empty())
        {
            return {};
        }
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), -1, nullptr, 0, nullptr, nullptr);
        std::string result(size_needed - 1, 0);
        WideCharToMultiByte(CP_UTF8, 0, wstr.data(), -1, result.data(), size_needed, nullptr, nullptr);

        return result;
    }

    void QLogicaeCore::SystemAccess::restart_with_admin_access() const
    {
        wchar_t file_path[MAX_PATH];
        if (::GetEnvironmentVariableW(L"VSAPPIDDIR", nullptr, 0) > 0 ||
            GetModuleFileNameW(nullptr, file_path, MAX_PATH) == 0)
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

    std::string SystemAccess::get_roaming_appdata_folder_path() const
    {
        wchar_t* path = nullptr;
        std::wstring result;
        if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path)))
        {
            result.assign(path);
            CoTaskMemFree(path);
        }

        return QLogicaeCore::ENCODER.from_utf16_to_utf8(result);
    }

    std::string SystemAccess::get_local_appdata_folder_path() const
    {
        wchar_t* path = nullptr;
        std::wstring result;
        if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path)))
        {
            result.assign(path);
            CoTaskMemFree(path);
        }

        return QLogicaeCore::ENCODER.from_utf16_to_utf8(result);
    }

    std::string SystemAccess::get_programdata_folder_path() const
    {
        wchar_t* path = nullptr;
        std::wstring result;
        if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_ProgramData, 0, NULL, &path)))
        {
            result.assign(path);
            CoTaskMemFree(path);
        }

        return QLogicaeCore::ENCODER.from_utf16_to_utf8(result);
    }

    QLogicaeCore::SystemAccess& QLogicaeCore::SystemAccess::get_instance()
    {
        static SystemAccess get_instance;
        return get_instance;
    }
}

