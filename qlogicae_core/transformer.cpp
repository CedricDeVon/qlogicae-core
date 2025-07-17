#pragma once

#include "pch.h"

#include "transformer.hpp"

namespace QLogicaeCore
{
    Transformer& Transformer::get_instance()
    {
        static Transformer singleton;

        return singleton;
    }

    std::string Transformer::color_type(
        const LogLevel& level) const
    {
        switch(level)
        {
            case LogLevel::ALL:
            {
                return "";
            }
            case LogLevel::INFO:
            {
                return "";
            }
            case LogLevel::DEBUG:
            {
                return "\033[94m";
            }
            case LogLevel::WARNING:
            {
                return "\033[93m";
            }
            case LogLevel::EXCEPTION:
            {
                return "\033[91m";
            }
            case LogLevel::CRITICAL:
            {
                return "\033[95m";
            }
            case LogLevel::SUCCESS:
            {
                return "\033[92m";
            }
            case LogLevel::HIGHLIGHTED_INFO:
            {
                return "\033[94m";
            }
            default:
            {
                return "";
            }
        }
    }

    std::string Transformer::to_log_format(
        const std::string_view& text,
        const LogLevel& level,
        const size_t& output_size) const
    {
        std::string result;
        result.reserve(output_size);

        fmt::format_to(
            std::back_inserter(result),
            "{}{}{}{}{}{}{}{}\033[0m",
            color_type(level),
            Constants::LOG_PART_1,
            Time::get_instance().now(TimeFormat::FullTimestamp),
            Constants::LOG_PART_2,
            get_log_level_string(level),
            Constants::LOG_PART_3,
            text,
            Constants::LOG_PART_4
        );

        return result;
    }

    std::string Transformer::to_log_level_color_format(
        const std::string_view& text,
        const LogLevel& level,
        const size_t& output_size) const
    {
        std::string result;
        result.reserve(output_size);

        fmt::format_to(
            std::back_inserter(result),
            "{}{}\033[0m",
            color_type(level),
            text
        );

        return result;
    }

    std::string Transformer::to_none_format(
        const std::string& text) const
    {
        if (text.empty())
        {
            return Constants::STRING_NONE_1.data();
        }

        return text;
    }

    std::string Transformer::to_na_format(
        const std::string& text) const
    {
        if (text.empty())
        {
            return Constants::STRING_NONE_2.data();
        }

        return text;
    }

    std::vector<std::string> Transformer::split(
        const std::string& text,
        const std::string& delimeter) const
    {
        auto result = absl::StrSplit(text, delimeter);
        
        return std::vector<std::string>(result.begin(), result.end());
    }
}
