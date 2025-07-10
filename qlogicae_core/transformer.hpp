#pragma once

#include "pch.h"

#include "time.hpp"

namespace QLogicaeCore
{
    class Transformer
    {
    public:
        std::string color_type(const LogLevel&) const;
        std::string to_na_format(const std::string& = "") const;
        std::string to_none_format(const std::string& = "") const;
        std::vector<std::string> split(const std::string&, const std::string&) const;
        std::string to_log_format(const std::string_view& = "", const LogLevel& = LogLevel::INFO, const size_t& = 256) const;
        std::string to_log_level_color_format(const std::string_view & = "", const LogLevel & = LogLevel::INFO, const size_t & = 256) const;
        
        static Transformer& instance();

    protected:
        Transformer() = default;
        ~Transformer() = default;
        Transformer(const Transformer&) = delete;
        Transformer(Transformer&&) noexcept = delete;
        Transformer& operator = (Transformer&&) = delete;
        Transformer& operator = (const Transformer&) = delete;
    };
}


