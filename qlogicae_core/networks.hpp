#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    class Networks
    {
    public:
        static Networks& get_instance();

    protected:
        Networks() = default;
        ~Networks() = default;
        Networks(const Networks&) = delete;
        Networks(Networks&&) noexcept = delete;
        Networks& operator = (Networks&&) = delete;
        Networks& operator = (const Networks&) = delete;
    };

    inline static Networks& NETWORKS = Networks::get_instance();
}

