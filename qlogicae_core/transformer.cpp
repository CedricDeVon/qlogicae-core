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
        try
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
        catch (const std::exception& exception)
        {
            CLI_IO.print_with_new_line_async(std::string("Exception at Transformer::color_type(): ") + exception.what());

            return "";
        }
    }

    std::string Transformer::to_log_format(
        const std::string& text,
        const LogLevel& level,
        const size_t& output_size) const
    {
        try
        {
            std::string result;
            result.reserve(output_size);

            result =
                "[" +
                TIME.now(TimeFormat::FULL_TIMESTAMP) +
                "] [" +
                get_log_level_string(level) +
                "]\t" +
                text +
                "\n";

            return result;
        }
        catch (const std::exception& exception)
        {
            CLI_IO.print_with_new_line_async(std::string("Exception at Transformer::to_log_format(): ") + exception.what());

            return "";
        }
    }

    std::string Transformer::to_log_level_color_format(
        const std::string& text,
        const LogLevel& level,
        const size_t& output_size) const
    {
        try
        {
            std::string result;
            result.reserve(output_size);

            result = text;

            return result;
        }
        catch (const std::exception& exception)
        {
            CLI_IO.print_with_new_line_async(std::string("Exception at Transformer::to_log_level_color_format(): ") + exception.what());

            return "";
        }
    }

    std::string Transformer::to_none_format(
        const std::string& text) const
    {
        try
        {
            if (text.empty())
            {
                return Constants::STRING_NONE_1;
            }

            return text;
        }
        catch (const std::exception& exception)
        {
            CLI_IO.print_with_new_line_async(std::string("Exception at Transformer::to_none_format(): ") + exception.what());

            return "";
        }
    }

    std::string Transformer::to_na_format(
        const std::string& text) const
    {
        try
        {
            if (text.empty())
            {
                return Constants::STRING_NONE_2;
            }

            return text;
        }
        catch (const std::exception& exception)
        {
            CLI_IO.print_with_new_line_async(std::string("Exception at Transformer::to_na_format(): ") + exception.what());

            return "";
        }
    }

    std::vector<std::string> Transformer::split(
        const std::string& text,
        const std::string& delimeter) const
    {
        try
        {
            auto result = absl::StrSplit(text, delimeter);

            return std::vector<std::string>(result.begin(), result.end());
        }
        catch (const std::exception& exception)
        {
            CLI_IO.print_with_new_line_async(std::string("Exception at Transformer::split(): ") + exception.what());

            return {};
        }
    }
}
