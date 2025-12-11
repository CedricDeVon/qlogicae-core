#pragma once

#include "instance_manager.hpp"

namespace QLogicaeCppCore
{
    struct NetworkPingManagerResponse
    {
        int64_t delay_in_milliseconds = 100;
    };

    inline static NetworkPingManagerResponse& NETWORK_PING_MANAGER_RESPONSE =
        INSTANCE_MANAGER.get_instance<NetworkPingManagerResponse>();
}
