#include "pch.hpp"

#include "../includes/file_system_manager.hpp"

namespace QLogicaeCppCore
{    
    FileSystemManager::FileSystemManager()
    {
        Result<bool> result;

        construct(result);
    }

    FileSystemManager::~FileSystemManager()
    {
        Result<bool> result;

        destruct(result);
    }

    void FileSystemManager::construct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(true);
    }

    void FileSystemManager::destruct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(true);
    }

    void FileSystemManager::get_executable_folder_path(
        Result<std::wstring>& result
    )
    {
        wchar_t buffer[MAX_PATH];

        if (GetModuleFileNameW(NULL, buffer, MAX_PATH) == 0)
        {
            result.set_to_bad_status_with_value(L"");

            return;
        }

        std::wstring path(buffer);

        result.set_to_good_status_with_value(
            path.substr(0, path.find_last_of(L"\\/"))
        );
    }

    void FileSystemManager::get_executed_folder_path(
        Result<std::wstring>& result
    )
    {
        wchar_t buffer[MAX_PATH];

        if (!GetCurrentDirectoryW(MAX_PATH, buffer))
        {
            result.set_to_bad_status_with_value(L"");

            return;
        }

        result.set_to_good_status_with_value(
            std::wstring(buffer)
        );
    }

    void FileSystemManager::get_program_data_folder_path(
        Result<std::wstring>& result
    )
    {
        wchar_t* path = nullptr;

        if (!SUCCEEDED(SHGetKnownFolderPath(
            FOLDERID_ProgramData, 0, NULL, &path))
        )
        {
            result.set_to_bad_status_with_value(L"");

            return;
        }
        
        result.set_to_good_status_with_value(
            std::wstring(path)
        );

        CoTaskMemFree(path);
    }

    void FileSystemManager::get_local_app_data_folder_path(
        Result<std::wstring>& result
    )
    {
        wchar_t* path = nullptr;

        if (!SUCCEEDED(SHGetKnownFolderPath(
            FOLDERID_LocalAppData, 0, NULL, &path))
        )
        {
            result.set_to_bad_status_with_value(L"");

            return;            
        }
        
        result.set_to_good_status_with_value(
            std::wstring(path)
        );

        CoTaskMemFree(path);
    }

    void FileSystemManager::get_roaming_app_data_folder_path(
        Result<std::wstring>& result
    )
    {
        wchar_t* path = nullptr;

        if (!SUCCEEDED(SHGetKnownFolderPath(
            FOLDERID_RoamingAppData, 0, NULL, &path))
        )
        {
            result.set_to_bad_status_with_value(L"");

            return;

        }
        
        result.set_to_good_status_with_value(
            std::wstring(path)
        );

        CoTaskMemFree(path);
    }

    void FileSystemManager::get_file_byte_size(
        Result<std::size_t>& result,
        const std::wstring_view& from_path
    )
    {
        WIN32_FILE_ATTRIBUTE_DATA data;
        if (!GetFileAttributesExW(
            from_path.data(), GetFileExInfoStandard, &data)
        )
        {
            result.set_to_bad_status_with_value(0);

            return;
        }
        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            result.set_to_bad_status_with_value(0);

            return;
        }

        ULARGE_INTEGER size;
        size.HighPart = data.nFileSizeHigh;
        size.LowPart = data.nFileSizeLow;
        
        result.set_to_good_status_with_value(
            size.QuadPart
        );
    }

    void FileSystemManager::get_folder_byte_size(
        Result<std::size_t>& result,
        const std::wstring_view& from_path,
        const bool& is_recursive
    )
    {
        std::size_t total = 0;
        WIN32_FIND_DATAW data;
        std::wstring search =
            std::wstring(from_path) + L"\\*";
        HANDLE h =
            FindFirstFileW(search.c_str(), &data);

        if (h == INVALID_HANDLE_VALUE)
        {
            result.set_to_bad_status_with_value(0);

            return;
        }
        do
        {
            Result<std::size_t> sub;
            
            std::wstring name = data.cFileName;
            if (name == L"." || name == L"..")
            {
                continue;
            }

            std::wstring full =
                std::wstring(from_path) + L"\\" + name;

            if (data.dwFileAttributes &
                    FILE_ATTRIBUTE_DIRECTORY)
            {
                if (is_recursive)
                {
                    get_folder_byte_size(
                        sub,
                        full,
                        true
                    );
                    
                    total += sub.get_value();
                }
            }
            else
            {
                ULARGE_INTEGER s;
                s.HighPart = data.nFileSizeHigh;
                s.LowPart = data.nFileSizeLow;
                total += s.QuadPart;
            }

        } while (FindNextFileW(h, &data));

        FindClose(h);
        
        result.set_to_good_status_with_value(total);
    }

    void FileSystemManager::get_absolute_path(
        Result<std::wstring_view>& result,
        const std::wstring_view& from_path
    )
    {
        static thread_local std::wstring buffer;
        buffer.assign(MAX_PATH, L'\0');
        DWORD len = GetFullPathNameW(
            from_path.data(),
            MAX_PATH, buffer.data(),
            nullptr
        );
        
        if (len == 0 || len > MAX_PATH)
        {
            result.set_to_bad_status_with_value(0);
        
            return;
        }
        
        buffer.resize(len);

        result.set_to_good_status_with_value(
            std::wstring_view(buffer)
        );
    }

    void FileSystemManager::get_relative_path(
        Result<std::wstring_view>& result,
        const std::wstring_view& from_path,
        const std::wstring_view& to_path
    )
    {
        std::filesystem::path p1(from_path);
        std::filesystem::path p2(to_path);
        std::error_code error_code_value;

        auto rel = std::filesystem::relative(
            p1, p2, error_code_value
        );

        if (error_code_value)
        {
            result.set_to_bad_status_with_value(0);

            return;
        }

        static thread_local std::wstring buffer;
        buffer = rel.wstring();

        result.set_to_good_status_with_value(
            std::wstring_view(buffer)
        );
    }

    void FileSystemManager::get_file_extension(
        Result<std::wstring>& result,
        const std::wstring_view& from_path
    )
    {
        std::filesystem::path file_path(from_path);

        result.set_to_good_status_with_value(
            file_path.extension().wstring()
        );
    }

    void FileSystemManager::get_file_stem(
        Result<std::wstring>& result,
        const std::wstring_view& from_path
    )
    {
        std::filesystem::path file_path(from_path);

        result.set_to_good_status_with_value(
            file_path.stem().wstring()
        );
    }

    void FileSystemManager::get_entity_paths(
        Result<std::vector<std::wstring>>& result,
        const std::wstring_view& from_path,
        const bool& is_recursive
    )
    {
        std::vector<std::wstring> data;
        std::filesystem::directory_options options =
            std::filesystem::directory_options::skip_permission_denied;
        
        if (is_recursive)
        {
            for (auto& entity : std::filesystem::recursive_directory_iterator(
                from_path, options)
            )
            {
                data.push_back(entity.path().wstring());
            }
        }
        else
        {
            for (auto& entity : std::filesystem::directory_iterator(
                from_path, options)
            )
            {
                data.push_back(entity.path().wstring());
            }
        }

        result.set_to_good_status_with_value(
            data
        );
    }

    void FileSystemManager::get_file_paths(
        Result<std::vector<std::wstring>>& result,
        const std::wstring_view& from_path,
        const bool& is_recursive
    )
    {
        std::vector<std::wstring> data;
        std::filesystem::directory_options options =
            std::filesystem::directory_options::skip_permission_denied;
        
        if (is_recursive)
        {
            for (auto& entity : std::filesystem::recursive_directory_iterator(
                from_path, options)
            )
            {
                if (!entity.is_directory())
                {
                    data.push_back(
                        entity.path().wstring()
                    );
                }
            }
        }
        else
        {
            for (auto& entity : std::filesystem::directory_iterator(
                from_path, options)
            )
            {
                if (!entity.is_directory())
                {
                    data.push_back(
                        entity.path().wstring()
                    );
                }
            }
        }

        result.set_to_good_status_with_value(
            data
        );
    }

    void FileSystemManager::get_folder_paths(
        Result<std::vector<std::wstring>>& result,
        const std::wstring_view& from_path,
        const bool& is_recursive
    )
    {
        std::vector<std::wstring> data;
        std::filesystem::directory_options options =
            std::filesystem::directory_options::skip_permission_denied;
        
        if (is_recursive)
        {
            for (auto& entity : std::filesystem::recursive_directory_iterator(
                from_path, options)
            )
            {
                if (entity.is_directory())
                {
                    data.push_back(entity.path().wstring());
                }
            }
        }
        else
        {
            for (auto& entity : std::filesystem::directory_iterator(
                from_path, options)
                )
            {
                if (entity.is_directory())
                {
                    data.push_back(entity.path().wstring());
                }
            }
        }

        result.set_to_good_status_with_value(
            data
        );
    }

    void FileSystemManager::is_path_found(
        Result<bool>& result,
        const std::wstring_view& from_path
    )
    {
        DWORD file_attribute = GetFileAttributesW(
            from_path.data()
        );

        if (file_attribute != INVALID_FILE_ATTRIBUTES)
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::is_entity(
        Result<bool>& result,
        const std::wstring_view& from_path
    )
    {
        DWORD file_attribute = GetFileAttributesW(
            from_path.data()
        );

        if (file_attribute != INVALID_FILE_ATTRIBUTES)
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::is_file(
        Result<bool>& result,
        const std::wstring_view& from_path
    )
    {
        DWORD file_attribute = GetFileAttributesW(
            from_path.data()
        );

        if (file_attribute != INVALID_FILE_ATTRIBUTES &&
            !(file_attribute & FILE_ATTRIBUTE_DIRECTORY)
            )
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::is_folder(
        Result<bool>& result,
        const std::wstring_view& from_path
    )
    {
        DWORD file_attribute = GetFileAttributesW(
            from_path.data()
        );

        if (file_attribute != INVALID_FILE_ATTRIBUTES &&
            (file_attribute & FILE_ATTRIBUTE_DIRECTORY)
            )
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::is_entity_user_permission_level_valid(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const std::filesystem::perms& permission_level
    )
    {
        std::error_code error_code_value;
        std::filesystem::perms p =
            std::filesystem::status(
                from_path, error_code_value
            ).permissions();

        if (error_code_value)
        {
            result.set_to_bad_status_with_value(false);

            return;
        }

        bool valid = (p & permission_level) == permission_level;
        
        result.set_to_good_status_with_value(valid);
    }

    void FileSystemManager::find_files_by_pattern(
        Result<std::vector<std::wstring>>& result,
        const std::wstring_view& from_path,
        const std::wstring_view& pattern,
        const bool& is_recursive
    )
    {
        std::vector<std::wstring> matches;
        std::filesystem::directory_options options =
            std::filesystem::directory_options::skip_permission_denied;
        
        if (is_recursive)
        {
            for (auto& entry : std::filesystem::recursive_directory_iterator(
                from_path, options)
            )
            {
                if (!entry.is_directory() &&
                    entry.path().filename().wstring().find(pattern) !=
                        std::wstring::npos)
                {
                    matches.push_back(entry.path().wstring());
                }
            }
        }
        else
        {
            for (auto& entry : std::filesystem::directory_iterator(
                from_path, options)
            )
            {
                if (!entry.is_directory() &&
                    entry.path().filename().wstring().find(pattern) !=
                        std::wstring::npos)
                {
                    matches.push_back(entry.path().wstring());
                }
            }
        }

        result.set_to_good_status_with_value(std::move(matches));
    }

    void FileSystemManager::set_entity_read_status(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const bool& value
    )
    {
        DWORD file_attribute = GetFileAttributesW(
            from_path.data()
        );
        
        if (file_attribute == INVALID_FILE_ATTRIBUTES)
        {
            result.set_to_bad_status_with_value(false);

            return;
        }

        if (value)
        {
            file_attribute &= ~FILE_ATTRIBUTE_READONLY;
        }
        else
        {
            file_attribute |= FILE_ATTRIBUTE_READONLY;
        }

        if (SetFileAttributesW(
            from_path.data(),
            file_attribute)
        )
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::set_entity_write_status(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const bool& value
    )
    {
        DWORD file_attribute =
            GetFileAttributesW(from_path.data());
        if (file_attribute == INVALID_FILE_ATTRIBUTES)
        {
            result.set_to_bad_status_with_value(false);

            return;
        }

        if (value)
        {
            file_attribute &= ~FILE_ATTRIBUTE_READONLY;
        }
        else
        {
            file_attribute |= FILE_ATTRIBUTE_READONLY;
        }

        if (SetFileAttributesW(from_path.data(), file_attribute))
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::set_entity_visibility(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const bool& value
    )
    {
        DWORD file_attribute =
            GetFileAttributesW(from_path.data());

        if (file_attribute == INVALID_FILE_ATTRIBUTES)
        {
            result.set_to_bad_status_with_value(false);

            return;
        }

        if (value)
        {
            file_attribute &= ~FILE_ATTRIBUTE_HIDDEN;
        }
        else
        {
            file_attribute |= FILE_ATTRIBUTE_HIDDEN;
        }

        if (SetFileAttributesW(
            from_path.data(), file_attribute)
        )
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::create_folder(
        Result<bool>& result,
        const std::wstring_view& from_path
    )
    {
        if (CreateDirectoryW(from_path.data(), nullptr) ||
            GetLastError() == ERROR_ALREADY_EXISTS
        )
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::copy_file(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const std::wstring_view& to_path
    )
    {
        if (CopyFileW(from_path.data(), to_path.data(), FALSE))
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::copy_folder(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const std::wstring_view& to_path,
        const bool& is_recursive
    )
    {
        std::error_code error_code_value;
        std::filesystem::copy_options options =
            std::filesystem::copy_options::skip_existing;

        if (is_recursive)
        {
            options |= std::filesystem::copy_options::recursive;
        }

        std::filesystem::copy(
            from_path,
            to_path,
            options,
            error_code_value
        );

        if (!error_code_value)
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::move_entity(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const std::wstring_view& to_path
    )
    {
        std::error_code error_code_value;
        std::filesystem::rename(
            from_path,
            to_path,
            error_code_value
        );

        if (!error_code_value)
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::move_file(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const std::wstring_view& to_path
    )
    {
        std::error_code error_code_value;
        std::filesystem::rename(
            from_path,
            to_path,
            error_code_value
        );

        if (!error_code_value)
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::move_folder(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const std::wstring_view& to_path
    )
    {
        std::error_code error_code_value;
        std::filesystem::rename(
            from_path,
            to_path,
            error_code_value
        );

        if (!error_code_value)
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::rename_entity(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const std::wstring_view& name
    )
    {
        std::filesystem::path new_path =
            std::filesystem::path(from_path).parent_path() / name;
        std::error_code error_code_value;
        std::filesystem::rename(
            from_path,
            new_path,
            error_code_value
        );

        if (!error_code_value)
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::rename_file(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const std::wstring_view& name
    )
    {
        rename_entity(result, from_path, name);
    }

    void FileSystemManager::rename_folder(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const std::wstring_view& name
    )
    {
        rename_entity(result, from_path, name);
    }

    void FileSystemManager::remove_file(
        Result<bool>& result,
        const std::wstring_view& from_path
    )
    {
        if (DeleteFileW(from_path.data()))
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::remove_folder(
        Result<bool>& result,
        const std::wstring_view& from_path
    )
    {
        if (RemoveDirectoryW(from_path.data()))
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }

    void FileSystemManager::remove_folder_sub_files(
        Result<bool>& result,
        const std::wstring_view& from_path,
        const bool& is_recursive
    )
    {
        std::error_code error_code_value;
        if (is_recursive)
        {
            std::filesystem::remove_all(
                from_path,
                error_code_value
            );
        }

        else
        {
            for (auto& entry : std::filesystem::directory_iterator(
                from_path, error_code_value)
            )
            {
                if (entry.is_directory())
                {
                    continue;
                }

                std::filesystem::remove(
                    entry.path(),
                    error_code_value
                );
            }
        }

        if (!error_code_value)
        {
            result.set_to_good_status_with_value(true);
        }
        else
        {
            result.set_to_bad_status_with_value(false);
        }
    }
}
