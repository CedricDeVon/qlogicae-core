#include "pch.hpp"

#include "../includes/network_ping_manager.hpp"

namespace QLogicaeCppCore
{
    NetworkPingManager::NetworkPingManager()
    {
        Result<bool> result;

        construct(result);
    }

    NetworkPingManager::~NetworkPingManager()
    {
        Result<bool> result;

        destruct(result);
    }

    NetworkPingManager::NetworkPingManager(
        const NetworkPingManagerConfigurations& initial_configurations
    )        
    {
        Result<bool> result;

        construct(
            result,
            initial_configurations
        );
    }

    void NetworkPingManager::construct(
        Result<bool>& result
    )
    {
        NetworkPingManagerConfigurations initial_configurations;

        construct(
            result,
            initial_configurations
        );
    }

    void NetworkPingManager::construct(
        Result<bool>& result,
        const NetworkPingManagerConfigurations& initial_configurations
    )
    {
        configurations = initial_configurations;

        auto self = this;

        _interval.construct(
            result,
            IntervalClockConfigurations
            {
                [self](size_t) -> bool
                {
                    auto pingResult = self->_ping();
                    if (pingResult && self->configurations.callback)
                    {
                        self->configurations.callback(
                            NetworkPingManagerResponse{*pingResult}
                        );
                    }
                    return self->configurations.is_listening;
                },

                configurations.delay_in_milliseconds,
                false
            }
        );

        if (configurations.is_listening)
        {
            _interval.start(result);
        }

        result.set_to_good_status_with_value(
            true
        );
    }

    void NetworkPingManager::destruct(
        Result<bool>& result
    )
    {        
        _interval.pause(result);
        configurations.is_listening = false;

        result.set_to_good_status_with_value(
            true
        );
    }

    void NetworkPingManager::get_is_listening(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(configurations.is_listening);
    }

    void NetworkPingManager::set_is_listening(
        Result<bool>& result,
        const bool& is_listening
    )
    {
        if (is_listening)
        {
            _interval.resume(result);
            if (result.get_status() == ResultStatus::GOOD)
            {
                configurations.is_listening = true;
            }
        }
        else
        {
            _interval.pause(result);
            if (result.get_status() == ResultStatus::GOOD)
            {
                configurations.is_listening = false;
            }
        }

        result.set_to_good_status_with_value(true);
    }

    void NetworkPingManager::pause_listening(
        Result<bool>& result
    )
    {
        if (configurations.is_listening)
        {
            set_is_listening(result, false);
            return;
        }

        result.set_to_bad_status_with_value(false);
    }

    void NetworkPingManager::continue_listening(
        Result<bool>& result
    )
    {
        if (!configurations.is_listening)
        {
            set_is_listening(result, true);
            return;
        }

        result.set_to_bad_status_with_value(false);
    }

    std::optional<int64_t> NetworkPingManager::_ping()
    {        
        try
        {
            boost::asio::io_context io;
            boost::asio::ip::tcp::resolver resolver(io);
            auto endpoints = resolver.resolve(configurations.host_address, "80");

            boost::asio::ip::tcp::socket socket(io);
            auto start = std::chrono::steady_clock::now();
            boost::asio::connect(socket, endpoints);
            auto end = std::chrono::steady_clock::now();

            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
        catch (...)
        {
            return std::nullopt;
        }
    }
}
