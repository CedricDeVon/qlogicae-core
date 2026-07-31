#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsSystemAccessManager \
	)

#include "../includes/windows_system_access_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{	
    WindowsSystemAccessManager
		::WindowsSystemAccessManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<WindowsSystemAccessManagerConfigurations>()
	{
		
	}

	bool
		WindowsSystemAccessManager
			::run_process(
				const std::string&
					command
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				command.empty()
			);	

			STARTUPINFOA startup_info{};
			PROCESS_INFORMATION process_info{};
			startup_info.cb = sizeof(STARTUPINFOA);
			startup_info.dwFlags = STARTF_USESHOWWINDOW;
			startup_info.wShowWindow = SW_HIDE;

			std::string full_cmd =
				"cmd.exe /c \"" + command + "\"";
			
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
				return
					false;
			}

			CloseHandle(process_info.hThread);
			CloseHandle(process_info.hProcess);

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
		WindowsSystemAccessManager
			::has_admin_access()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

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

			return
				is_admin == TRUE;
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
		WindowsSystemAccessManager
			::restart_with_admin_access()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

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
				return
					false;
			}

			SHELLEXECUTEINFOW sei = { sizeof(sei) };
			sei.lpVerb = L"runas";
			sei.lpFile = file_path;
			sei.hwnd = nullptr;
			sei.nShow = SW_SHOWNORMAL;

			ShellExecuteExW(&sei);
			ExitProcess(0);

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
}

#endif

