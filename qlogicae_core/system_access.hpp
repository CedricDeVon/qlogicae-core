#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    class SystemAccess
    {
    public:
        bool has_admin_access() const;
        std::string get_executable_dir() const;
        void restart_with_admin_access() const;

        static SystemAccess& get_instance();

    protected:
        SystemAccess() = default;
        ~SystemAccess() = default;
        SystemAccess(const SystemAccess&) = delete;
        SystemAccess(SystemAccess&&) noexcept = delete;
        SystemAccess& operator = (SystemAccess&&) = delete;
        SystemAccess& operator = (const SystemAccess&) = delete;
    };

    inline static SystemAccess& SYSTEM_ACCESS =
        SystemAccess::get_instance();
}


