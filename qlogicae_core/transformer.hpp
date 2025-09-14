#pragma once

#include "time.hpp"
#include "cli_io.hpp"

namespace QLogicaeCore
{
    class Transformer
    {
    public:
        std::string color_type(
            const LogLevel& log_level
        ) const;
        
        std::string to_na_format(
            const std::string& text = ""
        ) const;
        
        std::string to_none_format(
            const std::string& text = ""
        ) const;
        
        std::vector<std::string> split(
            const std::string& text,
            const std::string& delimeters
        ) const;
        
        std::string to_log_format(
            const std::string& text = "",
            const LogLevel& log_level = LogLevel::INFO,
            const size_t& length = 256
        ) const;
        
        std::string to_log_level_color_format(
            const std::string& text = "",
            const LogLevel& log_level = LogLevel::INFO,
            const size_t& length = 256
        ) const;
        
        static Transformer& get_instance();

    protected:
        Transformer() = default;
        
        ~Transformer() = default;
        
        Transformer(const Transformer& transformer) = delete;
        
        Transformer(Transformer&& transformer) noexcept = delete;
        
        Transformer& operator = (Transformer&& transformer) = delete;
        
        Transformer& operator = (const Transformer& transformer) = delete;
    };

    inline static Transformer& TRANSFORMER = Transformer::get_instance();
}
