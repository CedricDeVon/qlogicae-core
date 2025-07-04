#pragma once

#include "pch.h"

#include "network_ping.hpp"

namespace QLogicaeCore
{
    NetworkPing::NetworkPing(const NetworkPingSettings& settings) :
        _settings(settings),
        _interval(
            [this](size_t) -> bool
            {
                auto result = _ping();
                if (result && _settings.callback)
                {
                    _settings.callback(
                        NetworkPingResponse{ *result }
                    );
                }
                return _settings.is_listening;
            },
            settings.milliseconds_per_callback,
            std::nullopt,
            true)
    {
        if (_settings.is_listening)
        {
            _interval.start();
        }
    }

    bool NetworkPing::continue_listening()
    {
        if (!_settings.is_listening)
        {
            _settings.is_listening = true;
            _interval.resume();

            return true;
        }

        return false;
    }

    bool NetworkPing::pause_listening()
    {
        if (_settings.is_listening)
        {
            _settings.is_listening = false;
            _interval.pause();

            return true;
        }

        return false;
    }

    bool NetworkPing::get_is_listening() const
    {
        return _settings.is_listening;
    }

    void NetworkPing::set_is_listening(const bool& is_listening)
    {
        _settings.is_listening = is_listening;
        is_listening ? _interval.resume() : _interval.pause();
    }

    std::string_view NetworkPing::get_name() const
    {
        return _settings.name;
    }

    void NetworkPing::set_name(const std::string_view& name)
    {
        _settings.name = std::string(name);
    }

    std::string_view NetworkPing::get_host_address() const
    {
        return _settings.host_address;
    }

    void NetworkPing::set_host_address(const std::string_view& address)
    {
        _settings.host_address = std::string(address);
    }

    std::chrono::milliseconds NetworkPing::
        get_milliseconds_per_callback() const
    {
        return _settings.milliseconds_per_callback;
    }

    void NetworkPing::set_milliseconds_per_callback(
        const std::chrono::milliseconds& milliseconds)
    {
        _settings.milliseconds_per_callback = milliseconds;
        _interval.set_interval(milliseconds);
    }

    std::optional<int64_t> NetworkPing::_ping()
    {
        try
        {
            boost::asio::io_context io;
            boost::asio::ip::tcp::resolver resolver(io);
            auto endpoints = resolver.resolve(_settings.host_address, "80");

            boost::asio::ip::tcp::socket socket(io);
            auto start = std::chrono::steady_clock::now();
            boost::asio::connect(socket, endpoints);
            auto end = std::chrono::steady_clock::now();

            return std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start
            ).count();
        }
        catch (...)
        {
            return std::nullopt;
        }
    }
}
