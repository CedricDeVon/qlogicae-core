#pragma once

#include "result.hpp"
#include "interval.hpp"
#include "instance_manager.hpp"
#include "network_ping_settings.hpp"

namespace QLogicaeCppCore
{
    class NetworkPingManager
    {
    public:
        NetworkPingManager();
        
        ~NetworkPingManager();
        
        NetworkPingManager(
            const NetworkPingManager& instance
        ) = delete;
        
        NetworkPingManager(
            NetworkPingManager&& instance
        ) noexcept = delete;
        
        explicit NetworkPingManager(
            const NetworkPingSettings& instance
        );
        
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
            const NetworkPingSettings& network_ping_settings
        );

        void destruct(
            Result<bool>& result
        );

        void get_is_listening(
            Result<bool>& result
        );

        void set_is_listening(
            Result<bool>& result, const bool&
        );

        void get_name(
            Result<std::string_view>& result
        );

        void set_name(
            Result<bool>& result,
            const std::string_view& value
        );

        void get_host_address(
            Result<std::string_view>& result
        );

        void set_host_address(
            Result<bool>& result,
            const std::string_view& value
        );

        void get_milliseconds_per_callback(
            Result<std::chrono::milliseconds>& result
        );

        void set_milliseconds_per_callback(
            Result<bool>& result, 
            const std::chrono::milliseconds& value
        );

        void pause_listening(
            Result<bool>& result
        );

        void continue_listening(
            Result<bool>& result
        );

    protected:
        Interval _interval;

        NetworkPingSettings _settings;

        std::optional<int64_t> _ping();
    };
}
