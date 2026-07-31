#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemManager \
	)

#include "../includes/file_system_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{    
	FileSystemManager
		::FileSystemManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileSystemManagerConfigurations>()
    {
        construct();
    }

    FileSystemManager
		::~FileSystemManager()
    {
        destruct();
    }

    bool
        FileSystemManager
			::construct()
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
        FileSystemManager
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
		FileSystemManager
			::clear_file_text(
				const std::wstring&
					file_path
			)
	{
		return
			clear_file_text(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
						.convert_text<std::wstring, std::string>(
							file_path
						)
			);		
	}

	bool
		FileSystemManager
			::clear_file_text(
				const std::string&
					file_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			std::string
				text =
					"";

			fast_io::obuf_file
				write_file(
					file_path
				);

			fast_io::write(
				write_file,
				text.begin(),
				text.end()
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

	std::wstring
        FileSystemManager
			::get_executable_folder_wstring_path()
    {
        try
        {       
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);
     
			wchar_t buffer[MAX_PATH];
			DWORD length =
				GetModuleFileNameW(
					nullptr,
					buffer,
					MAX_PATH
				);

			if (length == 0 || length == MAX_PATH)
			{
				return L"";
			}

			wchar_t* last_separator =
				wcsrchr(buffer, L'\\');

			if (last_separator != nullptr)
			{
				*last_separator = L'\0';
			}

			return std::wstring(buffer);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }
	
	std::wstring
        FileSystemManager
			::get_executable_file_wstring_path()
    {
        try
        {       
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);
     
			wchar_t buffer[MAX_PATH];
			DWORD length =
				GetModuleFileNameW(
					nullptr,
					buffer,
					MAX_PATH
				);

			if (length == 0 || length == MAX_PATH)
			{
				return L"";
			}

			return std::wstring(buffer);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

	std::wstring
        FileSystemManager
			::get_executed_folder_wstring_path()
    {
        try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			DWORD required_size =
				GetCurrentDirectoryW(0, nullptr);

			if (required_size == 0)
			{
				return L"";
			}

			std::wstring path;
			path.resize(required_size - 1);

			if (!GetCurrentDirectoryW(
					required_size,
					path.data()))
			{
				return L"";
			}

			return path;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

	std::wstring
        FileSystemManager
			::get_program_data_folder_wstring_path()
    {
        try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			wchar_t buffer[MAX_PATH];

			HRESULT result =
				SHGetFolderPathW(
					nullptr,
					CSIDL_COMMON_APPDATA,
					nullptr,
					SHGFP_TYPE_CURRENT,
					buffer
				);

			if (FAILED(result))
			{
				return L"";
			}

			return std::wstring(buffer);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

    std::wstring
        FileSystemManager
			::get_local_app_data_folder_wstring_path()
    {
        try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			wchar_t buffer[MAX_PATH];

			HRESULT result =
				SHGetFolderPathW(
					nullptr,
					CSIDL_LOCAL_APPDATA,
					nullptr,
					SHGFP_TYPE_CURRENT,
					buffer
				);

			if (FAILED(result))
			{
				return L"";
			}

			return std::wstring(buffer);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

	std::wstring
        FileSystemManager
			::get_roaming_app_data_folder_wstring_path()
    {
        try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			wchar_t buffer[MAX_PATH];

			HRESULT result =
				SHGetFolderPathW(
					nullptr,
					CSIDL_APPDATA,
					nullptr,
					SHGFP_TYPE_CURRENT,
					buffer
				);

			if (FAILED(result))
			{
				return L"";
			}

			return std::wstring(buffer);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

	size_t
		FileSystemManager
			::get_line_count(
				const std::wstring&
					origin_path
			)
	{	
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			HANDLE file =
			CreateFileW(
				origin_path.c_str(),
				GENERIC_READ,
				FILE_SHARE_READ,
				nullptr,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				nullptr
			);

			if (file == INVALID_HANDLE_VALUE)
			{
				return 0;
			}

			LARGE_INTEGER size{};
			if (!GetFileSizeEx(file, &size) ||
				size.QuadPart == 0)
			{
				CloseHandle(file);
				return 0;
			}

			HANDLE mapping =
				CreateFileMappingW(
					file,
					nullptr,
					PAGE_READONLY,
					0,
					0,
					nullptr
				);

			if (!mapping)
			{
				CloseHandle(file);
				return 0;
			}

			const char* data =
				static_cast<const char*>(
					MapViewOfFile(
						mapping,
						FILE_MAP_READ,
						0,
						0,
						0
					)
				);

			if (!data)
			{
				CloseHandle(mapping);
				CloseHandle(file);
				return 0;
			}

			size_t count{0};
			const char* ptr = data;
			const char* end = data + size.QuadPart;

			__m256i newline = _mm256_set1_epi8('\n');

			while (ptr + 32 <= end)
			{
				__m256i chunk =
					_mm256_loadu_si256(
						reinterpret_cast<const __m256i*>(ptr)
					);

				__m256i cmp =
					_mm256_cmpeq_epi8(chunk, newline);

				unsigned mask =
					_mm256_movemask_epi8(cmp);

				count += __popcnt(mask);

				ptr += 32;
			}

			while (ptr < end)
			{
				if (*ptr == '\n')
				{
					++count;
				}
				++ptr;
			}

			if (*(end - 1) != '\n')
			{
				++count;
			}

			UnmapViewOfFile(data);
			CloseHandle(mapping);
			CloseHandle(file);

			return count;

        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	size_t
		FileSystemManager
			::get_column_count(
				const std::wstring&
					origin_path,
				const size_t&
					line_number
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				line_number == 0
			);		
	
			HANDLE file =
				CreateFileW(
					origin_path.c_str(),
					GENERIC_READ,
					FILE_SHARE_READ,
					nullptr,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					nullptr
				);

			if (file == INVALID_HANDLE_VALUE)
			{
				return 0;
			}

			LARGE_INTEGER size{};
			if (!GetFileSizeEx(file, &size) ||
				size.QuadPart == 0)
			{
				CloseHandle(file);
				return 0;
			}

			HANDLE mapping =
				CreateFileMappingW(
					file,
					nullptr,
					PAGE_READONLY,
					0,
					0,
					nullptr
				);

			if (!mapping)
			{
				CloseHandle(file);
				return 0;
			}

			const char* data =
				static_cast<const char*>(
					MapViewOfFile(
						mapping,
						FILE_MAP_READ,
						0,
						0,
						0
					)
				);

			if (!data)
			{
				CloseHandle(mapping);
				CloseHandle(file);
				return 0;
			}

			const char* ptr = data;
			const char* end = data + size.QuadPart;

			size_t current_line{1};

			while (ptr < end && current_line < line_number)
			{
				if (*ptr == '\n')
				{
					++current_line;
				}
				++ptr;
			}

			if (current_line != line_number)
			{
				UnmapViewOfFile(data);
				CloseHandle(mapping);
				CloseHandle(file);
				return 0;
			}

			size_t column_count{0};

			while (ptr < end && *ptr != '\n')
			{
				if (*ptr != '\r')
				{
					++column_count;
				}
				++ptr;
			}

			UnmapViewOfFile(data);
			CloseHandle(mapping);
			CloseHandle(file);

			return column_count;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	size_t
		FileSystemManager
			::get_character_count(
				const std::wstring&
					origin_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);	

			HANDLE file =
				CreateFileW(
					origin_path.c_str(),
					GENERIC_READ,
					FILE_SHARE_READ,
					nullptr,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					nullptr
				);

			if (file == INVALID_HANDLE_VALUE)
			{
				return 0;
			}

			LARGE_INTEGER size{};
			if (!GetFileSizeEx(file, &size))
			{
				CloseHandle(file);
				return 0;
			}

			CloseHandle(file);

			return
				static_cast<size_t>(size.QuadPart);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}
	
    size_t
		FileSystemManager
			::get_file_byte_size(
				const std::wstring&
					origin_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			WIN32_FILE_ATTRIBUTE_DATA data;
			if (!GetFileAttributesExW(
				origin_path.data(), GetFileExInfoStandard, &data)
			)
			{
				return
					0;
			}
			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				return
					0;
			}

			ULARGE_INTEGER size;
			size.HighPart = data.nFileSizeHigh;
			size.LowPart = data.nFileSizeLow;

			return
				static_cast<size_t>(size.QuadPart);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	size_t
		FileSystemManager
			::get_folder_byte_size(
				const std::wstring&
					origin_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			wchar_t search_path[MAX_PATH];
			wsprintfW(search_path, L"%s\\*", origin_path.data());

			WIN32_FIND_DATAW find_data;
			HANDLE handle =
				FindFirstFileW(search_path, &find_data);

			if (handle == INVALID_HANDLE_VALUE)
			{
				return 0;
			}

			size_t total_size = 0;

			do
			{
				if (wcscmp(find_data.cFileName, L".") == 0 ||
					wcscmp(find_data.cFileName, L"..") == 0)
				{
					continue;
				}

				wchar_t entity_path[MAX_PATH];
				wsprintfW(
					entity_path,
					L"%s\\%s",
					origin_path.data(),
					find_data.cFileName
				);

				if (find_data.dwFileAttributes &
					FILE_ATTRIBUTE_DIRECTORY)
				{
					if ((find_data.dwFileAttributes &
						FILE_ATTRIBUTE_REPARSE_POINT) == 0)
					{
						total_size +=
							get_folder_byte_size(entity_path);
					}
				}
				else
				{
					LARGE_INTEGER size;
					size.HighPart = find_data.nFileSizeHigh;
					size.LowPart = find_data.nFileSizeLow;

					total_size +=
						static_cast<size_t>(size.QuadPart);
				}
			} while (FindNextFileW(handle, &find_data));

			FindClose(handle);

			return total_size;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::wstring
		FileSystemManager
			::get_absolute_path(
				const std::wstring&
					origin_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			wchar_t buffer[MAX_PATH];
			DWORD len = GetFullPathNameW(origin_path.data(), MAX_PATH, buffer, nullptr);
			if (len == 0 || len > MAX_PATH) return L"";
			return std::wstring(buffer, len);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::wstring
		FileSystemManager
			::get_relative_path(
				const std::wstring&
					origin_path,
				const std::wstring&
					target_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!std::filesystem::exists(origin_path) ||
				!std::filesystem::exists(target_path)
			);			

			std::wstring origin = origin_path;
			std::wstring target = target_path;

			if (std::filesystem::is_directory(origin) &&
				origin.back() != L'\\')
			{
				origin.push_back(L'\\'); 
			}

			DWORD attr_from = std::filesystem::is_directory(origin) ? FILE_ATTRIBUTE_DIRECTORY : 0;
			DWORD attr_to = std::filesystem::is_directory(target) ? FILE_ATTRIBUTE_DIRECTORY : 0;

			wchar_t buffer[MAX_PATH];
			BOOL result = PathRelativePathToW(
				buffer,
				origin.c_str(),
				attr_from,
				target.c_str(),
				attr_to
			);

			return (result == FALSE) ? L"" : std::wstring(buffer);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::wstring
		FileSystemManager
			::get_file_extension(
				const std::wstring&
					origin_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			return
				std::wstring(PathFindExtensionW(origin_path.data()));
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::wstring
		FileSystemManager
			::get_file_stem(
				const std::wstring&
					origin_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			wchar_t* filename = PathFindFileNameW(origin_path.data());
			PathRemoveExtensionW(filename);
			return std::wstring(filename);
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
		FileSystemManager
			::is_path_found(
				const std::wstring&
					origin_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			return
				(GetFileAttributesW(
					origin_path.data()
				) != INVALID_FILE_ATTRIBUTES);
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
		FileSystemManager
			::is_entity(
				const std::wstring&
					origin_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);	

			return
				(GetFileAttributesW(
					origin_path.data()
				) != INVALID_FILE_ATTRIBUTES);
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
		FileSystemManager
			::is_file(
				const std::wstring&
					origin_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			DWORD file_attribute =
				GetFileAttributesW(
					origin_path.data()
				);

			return
				(file_attribute != INVALID_FILE_ATTRIBUTES &&
				!(file_attribute & FILE_ATTRIBUTE_DIRECTORY));
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
		FileSystemManager
			::is_folder(
				const std::wstring&
					origin_path
			)
	{
		try
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			DWORD file_attribute =
				GetFileAttributesW(
					origin_path.data()
				);

			return
				(file_attribute != INVALID_FILE_ATTRIBUTES &&
				(file_attribute & FILE_ATTRIBUTE_DIRECTORY));
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
		FileSystemManager
			::is_entity_user_permission_level_valid(
				const std::wstring&
					origin_path,
				const std::filesystem::perms&
					permission_level
			)
	{
		try
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			std::error_code ec;
			auto perms = std::filesystem::status(origin_path.data(), ec).permissions();
			if (ec) return false;
			return (perms & permission_level) == permission_level;
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
		FileSystemManager
			::set_entity_read_status(
				const std::wstring&
					origin_path,
				const bool&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			DWORD attributes = ::GetFileAttributesW(origin_path.data());
			if (attributes == INVALID_FILE_ATTRIBUTES)
			{
				return false;
			}

			if (value)
			{
				attributes |= FILE_ATTRIBUTE_READONLY;
			}
			else
			{
				attributes &= ~FILE_ATTRIBUTE_READONLY;
			}

			return SetFileAttributesW(origin_path.data(), attributes) != FALSE;
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
		FileSystemManager
			::set_entity_write_status(
				const std::wstring&
					origin_path,
				const bool&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			DWORD attributes = GetFileAttributesW(origin_path.data());
			if (attributes == INVALID_FILE_ATTRIBUTES)
			{
				return
					false;
			}

			if (value)
			{
				attributes &= ~FILE_ATTRIBUTE_READONLY;
			}
			else
			{
				attributes |= FILE_ATTRIBUTE_READONLY;
			}

			return
				SetFileAttributesW(origin_path.data(), attributes) != FALSE;
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
		FileSystemManager
			::set_entity_visibility(
				const std::wstring&
					origin_path,
				const bool&
					value
			)
	{
		try
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			DWORD attributes = GetFileAttributesW(origin_path.data());
			if (attributes == INVALID_FILE_ATTRIBUTES)
			{
				return
					false;
			}

			if (value)
			{
				attributes &= ~FILE_ATTRIBUTE_HIDDEN;
			}
			else
			{
				attributes |= FILE_ATTRIBUTE_HIDDEN;
			}

			return
				SetFileAttributesW(origin_path.data(), attributes) != FALSE;
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
		FileSystemManager
			::create_folder(
				const std::wstring&
					origin_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			return
				(CreateDirectoryW(origin_path.data(), nullptr) ||
					GetLastError() == ERROR_ALREADY_EXISTS);
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
		FileSystemManager
			::copy_file(
				const std::wstring&
					origin_path,
				const std::wstring&
					target_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			return
				CopyFileW(origin_path.data(), target_path.data(), FALSE);
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
		FileSystemManager
			::copy_folder(
				const std::wstring&
					origin_path,
				const std::wstring&
					target_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!std::filesystem::exists(origin_path) ||
				!std::filesystem::is_directory(origin_path)
			);			

			std::filesystem::copy(origin_path, target_path,
				std::filesystem::copy_options::recursive |
				std::filesystem::copy_options::overwrite_existing);

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

	bool
		FileSystemManager
			::move_entity(
				const std::wstring&
					origin_path,
				const std::wstring&
					target_path
			)
	{
		try
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			std::filesystem::path from(origin_path);
			std::filesystem::path to(target_path);

			if (!std::filesystem::exists(from))
			{
				return false;
			}

			std::filesystem::rename(from, to);
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

	bool
		FileSystemManager
			::move_file(
				const std::wstring&
					origin_path,
				const std::wstring&
					target_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			std::filesystem::path from(origin_path);
			std::filesystem::path to(target_path);

			if (!std::filesystem::exists(from) || std::filesystem::is_directory(from))
			{
				return false;
			}

			std::filesystem::rename(from, to);
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

	bool
		FileSystemManager
			::move_folder(
				const std::wstring&
					origin_path,
				const std::wstring&
					target_path
			)
	{
		try
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			std::filesystem::path from(origin_path);
			std::filesystem::path to(target_path);

			if (!std::filesystem::exists(from) || !std::filesystem::is_directory(from))
			{
				return false;
			}

			std::filesystem::rename(from, to);
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

	bool
		FileSystemManager
			::rename_entity(
				const std::wstring&
					origin_path,
				const std::wstring&
					name
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			auto parent_path = std::filesystem::path(origin_path).parent_path();
			auto target_path = parent_path / name;
			return move_file(origin_path, target_path.wstring());
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
		FileSystemManager
			::rename_file(
				const std::wstring&
					origin_path,
				const std::wstring&
					name
			)
	{
		try
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);	

			auto parent_path = std::filesystem::path(origin_path).parent_path();
			auto target_path = parent_path / name;
			return move_file(origin_path, target_path.wstring());
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
		FileSystemManager
			::rename_folder(
				const std::wstring&
					origin_path,
				const std::wstring&
					name
			)
	{
		try
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			auto parent_path = std::filesystem::path(origin_path).parent_path();
			auto target_path = parent_path / name;
			return move_folder(origin_path, target_path.wstring());
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
		FileSystemManager
			::remove_file(
				const std::wstring
					origin_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			return
				DeleteFileW(origin_path.data());
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
		FileSystemManager
			::remove_folder(
				const std::wstring
					origin_path
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			if (!std::filesystem::exists(origin_path) ||
				!std::filesystem::is_directory(origin_path))
			{
				return false;
			}

			std::error_code ec;
			std::filesystem::remove_all(origin_path, ec);

			return !std::filesystem::exists(origin_path);
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
		FileSystemManager
			::remove_folder_sub_files(
				const std::wstring
					origin_path
			)
	{
		try
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			wchar_t search_path[MAX_PATH];
			wsprintfW(search_path, L"%s\\*", origin_path.data());

			WIN32_FIND_DATAW find_data;
			HANDLE handle =
				FindFirstFileW(search_path, &find_data);

			if (handle == INVALID_HANDLE_VALUE)
			{
				return false;
			}

			bool success = true;

			do
			{
				if (wcscmp(find_data.cFileName, L".") == 0 ||
					wcscmp(find_data.cFileName, L"..") == 0)
				{
					continue;
				}

				if ((find_data.dwFileAttributes &
					FILE_ATTRIBUTE_DIRECTORY) == 0)
				{
					wchar_t file_path[MAX_PATH];
					wsprintfW(
						file_path,
						L"%s\\%s",
						origin_path.data(),
						find_data.cFileName
					);

					if (!DeleteFileW(file_path))
					{
						success = false;
					}
				}
			} while (FindNextFileW(handle, &find_data));

			FindClose(handle);

			return success;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::vector<std::wstring>
		FileSystemManager
		::get_folder_paths(
			const std::wstring& origin_path,
			const std::function<bool()>& pattern
		)
	{
		try
        {				
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!std::filesystem::exists(origin_path) ||
				!pattern
			);		

			const auto paths =
				enumerate(
					std::filesystem::path(origin_path),
					pattern,
					false,
					true
				);

			std::vector<std::wstring> result;

			for (const auto& p : paths)
			{
				result.push_back(p.wstring());
			}

			return result;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::vector<std::wstring>
		FileSystemManager
		::get_entity_paths(
			const std::wstring& origin_path
		)
	{
		return get_entity_paths(origin_path, []() { return true; });
	}

	std::vector<std::wstring>
		FileSystemManager
		::get_file_paths(
			const std::wstring& origin_path
		)
	{
		return get_file_paths(origin_path, []() { return true; });
	}

	std::vector<std::wstring>
		FileSystemManager
		::get_folder_paths(
			const std::wstring& origin_path
		)
	{
		return get_folder_paths(origin_path, []() { return true; });
	}

	std::string
        FileSystemManager
			::get_executable_folder_path()
    {
        return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_executable_folder_wstring_path()
				);
    }

	std::string
        FileSystemManager
			::get_executable_file_path()
    {
        return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_executable_file_wstring_path()
				);
    }

	std::string
        FileSystemManager
			::get_executed_folder_path()
    {
        return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_executed_folder_wstring_path()
				);
    }

	std::string
        FileSystemManager
			::get_program_data_folder_path()
    {
        return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_program_data_folder_wstring_path()
				);
    }

    std::string
        FileSystemManager
			::get_local_app_data_folder_path()
    {
        return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_local_app_data_folder_wstring_path()
				);
	}
	
    std::string
        FileSystemManager
			::get_roaming_app_data_folder_path()
    {
        return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_roaming_app_data_folder_wstring_path()
				);
    }
	
	size_t
		FileSystemManager
			::get_line_count(
				const std::string&
					origin_path
			)
	{
		return
			get_line_count(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					)
			);
	}

	size_t
		FileSystemManager
			::get_column_count(
				const std::string&
					origin_path,
				const size_t&
					line_number
			)
	{
		return
			get_column_count(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
					line_number
			);
	}

	size_t
		FileSystemManager
			::get_character_count(
				const std::string&
					origin_path
			)
	{
		return
			get_character_count(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					)
			);
	}

	size_t
        FileSystemManager
			::get_file_byte_size(            
				const std::string&
					origin_path
			)
	{
		return
			get_file_byte_size(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					)
			);
	}

    size_t
        FileSystemManager
			::get_folder_byte_size(            
				const std::string&
					origin_path
			)
	{
		return
			get_folder_byte_size(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					)
			);
	}

    std::string
        FileSystemManager
			::get_absolute_path(
				const std::string&
					origin_path
			)
	{
		return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_absolute_path(
						QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
							.convert_text<std::string, std::wstring>(
								origin_path
							)
					)
				);	
	}

    std::string
        FileSystemManager
			::get_relative_path(
				const std::string&
					origin_path,
				const std::string&
					target_path
			)
	{
		return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_relative_path(
						QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
							.convert_text<std::string, std::wstring>(
								origin_path
							),
						QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
							.convert_text<std::string, std::wstring>(
								target_path
							)
					)
				);
	}

    std::string
        FileSystemManager
			::get_file_extension(
				const std::string&
					origin_path
			)
	{
		return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_file_extension(
						QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
							.convert_text<std::string, std::wstring>(
								origin_path
							)
					)
				);	
	}

    std::string
        FileSystemManager
			::get_file_stem(
				const std::string&
					origin_path
			)
	{
		return
			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
				.convert_text<std::wstring, std::string>(
					get_file_stem(
						QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
							.convert_text<std::string, std::wstring>(
								origin_path
							)
					)
				);	
	}

    bool
        FileSystemManager
			::is_path_found(
				const std::string&
					origin_path
			)
	{
		return
			is_path_found(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					)
			);	
	}

    bool
        FileSystemManager
			::is_entity(
				const std::string&
					origin_path
			)
	{
		return
			is_entity(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					)
			);
	}

    bool
        FileSystemManager
			::is_file(
				const std::string&
					origin_path
			)
	{
		return
			is_file(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					)
			);
	}

    bool
        FileSystemManager
			::is_folder(
				const std::string&
					origin_path
			)
	{
		return
			is_folder(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					)
			);
	}

    bool
        FileSystemManager
			::is_entity_user_permission_level_valid(
				const std::string&
					origin_path,
				const std::filesystem::perms&
					permission_level
			)
	{
		return
			is_entity_user_permission_level_valid(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
				permission_level
			);
	}

    bool
        FileSystemManager
			::set_entity_read_status(
				const std::string&
					origin_path,
				const bool&
					value
			)
	{
		return
			set_entity_read_status(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
				value
			);	
	}

    bool
        FileSystemManager
			::set_entity_write_status(
				const std::string&
					origin_path,
				const bool&
					value
			)
	{
		return
			set_entity_write_status(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
				value
			);		
	}

    bool
        FileSystemManager
			::set_entity_visibility(
				const std::string&
					origin_path,
				const bool&
					value
			)
	{
		return
			set_entity_visibility(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
				value
			);
	}

    bool
        FileSystemManager
			::create_folder(
				const std::string&
					origin_path
			)
	{
		return
			create_folder(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					)
			);
	}

    bool
        FileSystemManager
			::copy_file(
				const std::string&
					origin_path,
				const std::string&
					target_path
			)
	{
		return
			copy_file(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						target_path
					)
			);	
	}

    bool
        FileSystemManager
			::copy_folder(
				const std::string&
					origin_path,
				const std::string&
					target_path
			)
	{
		return
			copy_folder(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						target_path
					)
			);		
	}

    bool
        FileSystemManager
			::move_entity(
				const std::string&
					origin_path,
				const std::string&
					target_path
			)
	{
		return
			move_entity(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						target_path
					)
			);	
	}

    bool
        FileSystemManager
			::move_file(
				const std::string&
					origin_path,
				const std::string&
					target_path
			)
	{
		return
			move_file(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						target_path
					)
			);
	}

    bool
        FileSystemManager
			::move_folder(
				const std::string&
					origin_path,
				const std::string&
					target_path
			)
	{
		return
			move_folder(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						target_path
					)
			);	
	}

    bool
        FileSystemManager
			::rename_entity(
				const std::string&
					origin_path,
				const std::string&
					name
			)
	{
		return
			rename_entity(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						name
					)
			);	
	}

    bool
        FileSystemManager
			::rename_file(
				const std::string&
					origin_path,
				const std::string&
					name
			)
	{
		return
			rename_file(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						name
					)
			);	
	}

    bool
        FileSystemManager
			::rename_folder(
				const std::string&
					origin_path,
				const std::string&
					name
			)
	{
		return
			rename_folder(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						name
					)
			);
	}

    bool
        FileSystemManager
			::remove_file(
				const std::string&
					origin_path
			)
	{
		return
			remove_file(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					)
			);		
	}

    bool
        FileSystemManager
			::remove_folder(
				const std::string&
					origin_path
			)
	{
		return
			remove_folder(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					)
			);	
	}

    bool
        FileSystemManager
			::remove_folder_sub_files(
				const std::string&
					origin_path
			)
	{
		return
			remove_folder_sub_files(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextManager>()
					.convert_text<std::string, std::wstring>(
						origin_path
					)
			);
	}

	std::vector<std::filesystem::path>
		FileSystemManager
			::enumerate(
				const std::filesystem::path&
					origin_path,
				const std::function<bool()>&
					pattern,
				const bool&
					include_files,
				const bool&
					include_folders
			)
    {
		try
        {				
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				!std::filesystem::exists(origin_path) ||
				!std::filesystem::is_directory(origin_path)
			);	

			std::error_code ec;
			std::vector<std::filesystem::path> result;

			for (const auto& entry :
				std::filesystem::directory_iterator(origin_path, ec))
			{
				if (ec)
				{
					break;
				}

				const bool is_file =
					entry.is_regular_file(ec);

				const bool is_directory =
					entry.is_directory(ec);

				if (is_file && include_files)
				{
					if (!pattern || pattern())
					{
						result.push_back(entry.path());
					}
				}
				else if (is_directory && include_folders)
				{
					if (!pattern || pattern())
					{
						result.push_back(entry.path());
					}
				}
			}

			return result;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

	std::vector<std::wstring>
		FileSystemManager
		::get_entity_paths(
			const std::wstring& origin_path,
			const std::function<bool()>& pattern
		)
	{
		try
        {				
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!std::filesystem::exists(origin_path) ||
				!pattern
			);		

			const auto paths =
				enumerate(
					std::filesystem::path(origin_path),
					pattern,
					true,
					true
				);

			std::vector<std::wstring> result;

			for (const auto& p : paths)
			{
				result.push_back(p.wstring());
			}

			return result;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::vector<std::wstring>
		FileSystemManager
		::get_file_paths(
			const std::wstring& origin_path,
			const std::function<bool()>& pattern
		)
	{
		try
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!std::filesystem::exists(origin_path) ||
				!pattern
			);			

			const auto paths =
				enumerate(
					std::filesystem::path(origin_path),
					pattern,
					true,
					false
				);

			std::vector<std::wstring> result;

			for (const auto& p : paths)
			{
				result.push_back(p.wstring());
			}

			return result;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }	
	}

	std::vector<std::string>
		FileSystemManager
		::get_entity_paths(
			const std::string& origin_path,
			const std::function<bool()>& pattern
		)
	{
		try
        {				
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				!std::filesystem::exists(origin_path) ||
				!std::filesystem::is_directory(origin_path)
			);

			const auto paths =
				enumerate(
					std::filesystem::path(origin_path),
					pattern,
					true,
					true
				);

			std::vector<std::string> result;

			for (const auto& p : paths)
			{
				result.push_back(p.string());
			}

			return result;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }	
	}

	std::vector<std::string>
		FileSystemManager
		::get_file_paths(
			const std::string& origin_path,
			const std::function<bool()>& pattern
		)
	{
		try
        {				
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				!std::filesystem::exists(origin_path) ||
				!std::filesystem::is_directory(origin_path)
			);			

			const auto paths =
				enumerate(
					std::filesystem::path(origin_path),
					pattern,
					true,
					false
				);

			std::vector<std::string> result;

			for (const auto& p : paths)
			{
				result.push_back(p.string());
			}

			return result;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }		
	}

	std::vector<std::string>
		FileSystemManager
		::get_folder_paths(
			const std::string& origin_path,
			const std::function<bool()>& pattern
		)
	{
		try
        {				
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				!std::filesystem::exists(origin_path) ||
				!std::filesystem::is_directory(origin_path)
			);

			const auto paths =
				enumerate(
					std::filesystem::path(origin_path),
					pattern,
					false,
					true
				);

			std::vector<std::string> result;

			for (const auto& p : paths)
			{
				result.push_back(p.string());
			}

			return result;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::vector<std::string>
		FileSystemManager
		::get_entity_paths(
			const std::string& origin_path
		)
	{
		return get_entity_paths(origin_path, []() { return true; });
	}

	std::vector<std::string>
		FileSystemManager
		::get_file_paths(
			const std::string& origin_path
		)
	{
		return get_file_paths(origin_path, []() { return true; });
	}

	std::vector<std::string>
		FileSystemManager
		::get_folder_paths(
			const std::string& origin_path
		)
	{
		return get_folder_paths(origin_path, []() { return true; });
	}

}

#endif
