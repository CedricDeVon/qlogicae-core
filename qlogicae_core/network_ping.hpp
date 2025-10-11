#pragma once

#include "utilities.hpp"
#include "interval.hpp"
#include "network_ping_settings.hpp"

#include <cstdint>

namespace QLogicaeCore
{
    class NetworkPing
    {
    public:
        NetworkPing() = default;
        
        ~NetworkPing() = default;
        
        NetworkPing(const NetworkPing& network_ping) = delete;
        
        NetworkPing(NetworkPing&& network_ping) noexcept = delete;
        
        explicit NetworkPing(const NetworkPingSettings& network_ping);
        
        NetworkPing& operator = (NetworkPing&& network_ping) = delete;
        
        NetworkPing& operator = (const NetworkPing& network_ping) = delete;

        bool get_is_listening() const;
        
        void set_is_listening(const bool&);
        
        std::string_view get_name() const;
        
        void set_name(const std::string_view& value);
        
        std::string_view get_host_address() const;
        
        void set_host_address(const std::string_view& value);
        
        std::chrono::milliseconds get_milliseconds_per_callback() const;
        
        void set_milliseconds_per_callback(
            const std::chrono::milliseconds& value
        );
        
        bool pause_listening();
        
        bool continue_listening();

    protected:
        Interval _interval;
        NetworkPingSettings _settings;

        std::optional<int64_t> _ping();
    };
}

