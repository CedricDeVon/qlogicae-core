#include "pch.hpp"

#include "../includes/file_system.hpp"

namespace QLogicaeCore
{
    FileSystem::FileSystem()
    {

    }

    FileSystem::~FileSystem()
    {

    }

    bool FileSystem::setup()
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
                "QLogicaeCore::FileSystem::setup()",
                exception.what()
            );

            return false;
        }
    }

    void FileSystem::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    std::future<bool> FileSystem::setup_async()
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

    void FileSystem::setup_async(
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

    void FileSystem::setup_async(
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

    void FileSystem::setup_async(
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

    std::string FileSystem::get_executable_dir()
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
                "QLogicaeCore::FileSystem::get_executable_dir()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::FileSystem::get_executable_dir(): " +
                exception.what()
            );
        }
    }

    std::string FileSystem::get_executed_folder()
    {
        try
        {
            return std::filesystem::current_path().string();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::FileSystem::get_executed_folder()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::FileSystem::get_executed_folder(): " +
                exception.what()
            );
        }
    }

    std::string FileSystem::get_executable_folder()
    {
        try
        {
            return get_executable_dir();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::FileSystem::get_executable_folder()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::FileSystem::get_executable_folder(): " +
                exception.what()
            );
        }
    }

    std::string FileSystem::get_roaming_appdata_folder_path()
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
                "QLogicaeCore::FileSystem::get_roaming_appdata_folder_path()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::FileSystem::get_roaming_appdata_folder_path(): " +
                exception.what()
            );
        }
    }

    std::string FileSystem::get_local_appdata_folder_path()
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
                "QLogicaeCore::FileSystem::get_local_appdata_folder_path()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::FileSystem::get_local_appdata_folder_path(): " +
                exception.what()
            );
        }
    }

    std::string FileSystem::get_programdata_folder_path()
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
                "QLogicaeCore::FileSystem::get_programdata_folder_path()",
                exception.what()
            );

            throw std::runtime_error(
                std::string() +
                "QLogicaeCore::FileSystem::get_programdata_folder_path(): " +
                exception.what()
            );
        }
    }

    void FileSystem::get_executable_dir(
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

    void FileSystem::get_executable_folder(
        Result<std::string>& result
    )
    {
        get_executable_dir(result);
    }

    void FileSystem::get_executed_folder(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            std::filesystem::current_path().string()
        );
    }

    void FileSystem::get_roaming_appdata_folder_path(
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

    void FileSystem::get_local_appdata_folder_path(
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

    void FileSystem::get_programdata_folder_path(
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


    bool FileSystem::replace_file_if_found(
        const std::string& folder_path,
        const std::string& file_path
    )
    {
        if (!std::filesystem::exists(folder_path))
        {
            create_folder_path(folder_path);
        }

        if (std::filesystem::exists(file_path))
        {
            std::filesystem::remove(file_path);
        }

        return true;
    }

    bool FileSystem::remove_file_or_folder_if_found(
        const std::string& path
    )
    {
        if (std::filesystem::exists(path))
        {
            std::filesystem::remove(path);
        }

        return true;
    }

    bool FileSystem::copy_file_or_folder(
        const std::string& from_path,
        const std::string& to_path
    )
    {
        std::filesystem::copy_file(
            from_path,
            to_path,
            std::filesystem::copy_options::overwrite_existing
        );

        return true;
    }

    bool FileSystem::is_file_or_folder_path_found(
        const std::string& path
    )
    {
        if (!std::filesystem::exists(path))
        {
            QLogicaeCore::LOGGER.handle_exception_async(
                "QLogicaeCLI::FileSystem::is_file_or_folder_path_found()",
                "File or folder path '" + path + "' does not exist"
            );

            return false;
        }

        return true;
    }

    bool FileSystem::create_folder_path(
        const std::string& path,
        const bool& is_enabled
    )
    {
        if (!is_enabled)
        {
            return false;
        }

        if (!std::filesystem::exists(path))
        {
            std::filesystem::create_directories(path);

            return true;
        }

        return false;
    }

    bool FileSystem::clear_files(
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
                "QLogicaeCore::FileSystem::clear_files()",
                exception.what()
            );

            return false;
        }
    }

    void FileSystem::clear_files(
        Result<void>& result,
        const std::string& root_path
    )
    {
        std::string search_path = root_path + "\\*";
        WIN32_FIND_DATAA fd;
        HANDLE hFind = FindFirstFileA(search_path.c_str(), &fd);

        if (hFind == INVALID_HANDLE_VALUE) return;

        do
        {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                std::string file_path = root_path + "\\" + fd.cFileName;
                DeleteFileA(file_path.c_str());
            }
            else if (strcmp(fd.cFileName, ".") != 0 && strcmp(fd.cFileName, "..") != 0)
            {
                std::string subdir_path = root_path + "\\" + fd.cFileName;
                clear_files(result, subdir_path);
            }
        } while (FindNextFileA(hFind, &fd) != 0);

        FindClose(hFind);

        result.set_to_good_status_without_value();
    }


    std::future<bool> FileSystem::clear_files_async(
        const std::string& root_path
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, root_path,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    clear_files(
                        root_path
                    )
                );
            }
        );

        return future;
    }

    void FileSystem::clear_files_async(
        const std::function<void(const bool& result)>& callback,
        const std::string& root_path
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, root_path]() mutable
            {
                callback(
                    clear_files(
                        root_path
                    )
                );
            }
        );
    }

    void FileSystem::clear_files_async(
        Result<std::future<bool>>& result,
        const std::string& root_path
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, root_path,
            promise = std::move(promise)]() mutable
            {
                Result<void> result;

                clear_files(
                    result,
                    root_path
                );

                promise.set_value(
                    result.is_status_safe()
                );
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void FileSystem::clear_files_async(
        const std::function<void(Result<void>& result)>& callback,
        const std::string& root_path
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, root_path]() mutable
            {
                Result<void> result;

                clear_files(
                    result,
                    root_path
                );

                callback(
                    result
                );
            }
        );
    }

    bool FileSystem::terminate()
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
                "QLogicaeCore::FileSystem::terminate()",
                exception.what()
            );

            return false;
        }
    }

    void FileSystem::terminate(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    std::future<bool> FileSystem::terminate_async()
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

    void FileSystem::terminate_async(
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

    void FileSystem::terminate_async(
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

    void FileSystem::terminate_async(
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

    FileSystem& FileSystem::get_instance()
    {
        static FileSystem instance;

        return instance;
    }

    void FileSystem::get_instance(
        Result<FileSystem*>& results
    )
    {                
        results.set_to_good_status_with_value(
            &get_instance()
        );
    }
}
