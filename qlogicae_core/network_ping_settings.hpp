#pragma once

#include "utilities.hpp"
#include "network_ping_response.hpp"

#include <cstdint>

namespace QLogicaeCore
{
    struct NetworkPingSettings
    {
        std::chrono::milliseconds milliseconds_per_callback
        {
            UTILITIES.DEFAULT_MILLISECONDS_PER_CALLBACK
        };
        std::string host_address
        {
            UTILITIES.DEFAULT_HOST_ADDRESS
        };
        bool is_listening
        {
            UTILITIES.DEFAULT_IS_LISTENING
        };
        std::string name;
        std::function<void(const NetworkPingResponse&)> callback;
    };
}
