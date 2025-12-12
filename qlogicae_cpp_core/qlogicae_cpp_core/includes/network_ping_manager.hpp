#pragma once

#include "result.hpp"
#include "interval_clock.hpp"
#include "instance_manager.hpp"
#include "network_ping_manager_response.hpp"
#include "network_ping_manager_configurations.hpp"

namespace QLogicaeCppCore
{
    class NetworkPingManager
    {
    public:
        NetworkPingManager();
        
        explicit NetworkPingManager(
            const NetworkPingManagerConfigurations& initial_configurations
        );

        ~NetworkPingManager();
        
        NetworkPingManager(
            const NetworkPingManager& instance
        ) = delete;
        
        NetworkPingManager(
            NetworkPingManager&& instance
        ) noexcept = delete;        

        NetworkPingManager& operator = (
            NetworkPingManager&& instance
        ) = delete;

        NetworkPingManager& operator = (
            const NetworkPingManager& instance
        ) = delete;

        void construct(
            Result<bool>& result
        );

        void construct(
            Result<bool>& result,
            const NetworkPingManagerConfigurations& initial_configurations
        );

        void destruct(
            Result<bool>& result
        );

        void get_is_listening(
            Result<bool>& result
        );

        void set_is_listening(
            Result<bool>& result,
            const bool&
        );

        void pause_listening(
            Result<bool>& result
        );

        void continue_listening(
            Result<bool>& result
        );

        NetworkPingManagerConfigurations configurations;

    protected:
        IntervalClock _interval;

        std::optional<int64_t> _ping();
    };

    /*
    inline static NetworkPingManager& NETWORK_PING_MANAGER =
        INSTANCE_MANAGER.get_instance<NetworkPingManager>();
    */
}
