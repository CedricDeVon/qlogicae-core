#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "encoder.hpp"

#include <windows.h>
#include <filesystem>

namespace QLogicaeCore
{
    class SystemAccess
    {
    public:
        bool setup();

        void setup(
            Result<void>& result
        );

        std::future<bool> setup_async();

        void setup_async(
            const std::function<void(const bool& result)>& callback
        );

        void setup_async(
            Result<std::future<void>>& result
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback
        );

        bool run_process(
            const std::string& command
        );

        void run_process(
            Result<bool>& result,
            const std::string& command
        );

        std::future<bool> run_process_async(
            const std::string& command
        );

        void run_process_async(
            const std::function<void(const bool& result)>& callback,
            const std::string& command
        );

        void run_process_async(
            Result<std::future<bool>>& result,
            const std::string& command
        );

        void run_process_async(
            const std::function<void(Result<bool>& result)>& callback,
            const std::string& command
        );

        bool has_admin_access();
        
        std::string get_executable_dir();

        std::string get_executable_folder();

        std::string get_executed_folder();
        
        void restart_with_admin_access();
        
        std::string get_programdata_folder_path();
        
        std::string get_local_appdata_folder_path();
        
        std::string get_roaming_appdata_folder_path();

        void has_admin_access(
            Result<void>& result
        );

        void get_executable_dir(
            Result<std::string>& result
        );

        void get_executable_folder(
            Result<std::string>& result
        );

        void get_executed_folder(
            Result<std::string>& result
        );

        void restart_with_admin_access(
            Result<void>& result
        );

        void get_programdata_folder_path(
            Result<std::string>& result
        );

        void get_local_appdata_folder_path(
            Result<std::string>& result
        );

        void get_roaming_appdata_folder_path(
            Result<std::string>& result
        );

        bool clear_files(
            const std::string& root_path
        );

        void clear_files(
            Result<void>& result,
            const std::string& root_path
        );

        static SystemAccess& get_instance();

        static void get_instance(
            Result<SystemAccess*>& results
        );

    protected:
        SystemAccess();
        
        ~SystemAccess();
        
        SystemAccess(
            const SystemAccess& instance
        ) = delete;
        
        SystemAccess(
            SystemAccess&& instance
        ) noexcept = delete;
        
        SystemAccess& operator = (
            SystemAccess&& instance
        ) = delete;
        
        SystemAccess& operator = (
            const SystemAccess& instance
        ) = delete;
    };

    inline static SystemAccess& SYSTEM_ACCESS =
        SystemAccess::get_instance();
}
