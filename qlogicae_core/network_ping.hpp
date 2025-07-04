#pragma once

#include "pch.h"

#include "interval.hpp"

namespace QLogicaeCore
{
    struct NetworkPingResponse
    {
        int64_t round_trip_time_in_milliseconds;
    };

    struct NetworkPingSettings
    {
        std::chrono::milliseconds milliseconds_per_callback
        {
            QLogicaeCore::Constants::DEFAULT_MILLISECONDS_PER_CALLBACK
        };
        std::string host_address
        {
            "1.1.1.1"
        };
        bool is_listening
        {
            QLogicaeCore::Constants::DEFAULT_IS_LISTENING
        };
        std::string name;
        std::function<void(const NetworkPingResponse&)> callback;
    };

    class NetworkPing
    {
    public:
        NetworkPing() = default;
        ~NetworkPing() = default;
        NetworkPing(const NetworkPing&) = delete;
        NetworkPing(NetworkPing&&) noexcept = delete;
        explicit NetworkPing(const NetworkPingSettings&);
        NetworkPing& operator = (NetworkPing&&) = delete;
        NetworkPing& operator = (const NetworkPing&) = delete;

        bool get_is_listening() const;
        void set_is_listening(const bool&);
        std::string_view get_name() const;
        void set_name(const std::string_view&);
        std::string_view get_host_address() const;
        void set_host_address(const std::string_view&);
        std::chrono::milliseconds get_milliseconds_per_callback() const;
        void set_milliseconds_per_callback(const std::chrono::milliseconds&);
        
        bool pause_listening();
        bool continue_listening();

    protected:
        QLogicaeCore::Interval _interval;
        QLogicaeCore::NetworkPingSettings _settings;

        std::optional<int64_t> _ping();
    };
}
