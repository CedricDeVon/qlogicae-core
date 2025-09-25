#pragma once

#include "encoder.hpp"

namespace QLogicaeCore
{
    class SystemAccess
    {
    public:
        bool has_admin_access() const;
        
        std::string get_executable_dir() const;

        std::string get_executable_folder() const;

        std::string get_executed_folder() const;
        
        void restart_with_admin_access() const;
        
        std::string get_programdata_folder_path() const;
        
        std::string get_local_appdata_folder_path() const;
        
        std::string get_roaming_appdata_folder_path() const;

        static SystemAccess& get_instance();

    protected:
        SystemAccess() = default;
        
        ~SystemAccess() = default;
        
        SystemAccess(const SystemAccess& system_access) = delete;
        
        SystemAccess(SystemAccess&& system_access) noexcept = delete;
        
        SystemAccess& operator = (SystemAccess&& system_access) = delete;
        
        SystemAccess& operator = (const SystemAccess& system_access) = delete;
    };

    inline static SystemAccess& SYSTEM_ACCESS =
        SystemAccess::get_instance();
}


