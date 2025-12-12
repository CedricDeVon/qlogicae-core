#pragma once

#include "instance_manager.hpp"

namespace QLogicaeCppCore
{
    struct IntervalClockConfigurations
    {
        std::function<bool(size_t)> callback = [](size_t current_interval) { return true; };
        
        std::chrono::milliseconds delay_in_milliseconds { 1000 };
        
        size_t maximum_interval_count = 1;
        
        bool is_executed_immediately = true;
    };

    inline static IntervalClockConfigurations& INTERVAL_CONFIGURATIONS = 
        INSTANCE_MANAGER.get_instance<IntervalClockConfigurations>();
}
