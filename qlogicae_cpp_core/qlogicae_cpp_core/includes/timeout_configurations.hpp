#pragma once

#include "instance_manager.hpp"

namespace QLogicaeCppCore
{
    struct TimeoutConfigurations
    {
        std::function<void()> callback = []() {};

        std::chrono::milliseconds delay_in_milliseconds{ 100 };

        bool is_executed_immediately = true;                 
    };

    inline static TimeoutConfigurations& TIMEOUT_CONFIGURATIONS =
        INSTANCE_MANAGER.get_instance<TimeoutConfigurations>();
}
