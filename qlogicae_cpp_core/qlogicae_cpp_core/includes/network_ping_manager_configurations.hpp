#pragma once

#include "instance_manager.hpp"
#include "network_ping_manager_response.hpp"

namespace QLogicaeCppCore
{
    struct NetworkPingManagerConfigurations
    {
        std::function<void(const NetworkPingManagerResponse& response)> callback =
            [](const NetworkPingManagerResponse& response) {};

        std::string host_address
        {
            "1.1.1.1"
        };        

        std::string name = "";

        std::chrono::milliseconds delay_in_milliseconds
        {
            100
        };
        
        bool is_listening
        {
            true
        };
    };

    inline static NetworkPingManagerConfigurations& NETWORK_PING_MANAGER_CONFIGURATIONS =
        INSTANCE_MANAGER.get_instance<NetworkPingManagerConfigurations>();
}
