#include "pch.hpp"

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
            throw std::runtime_error(
                std::string("Exception at Transformer::color_type(): ") +
                exception.what()
            );
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
            throw std::runtime_error(
                std::string("Exception at Transformer::to_log_format(): ") +
                exception.what()
            );
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
            throw std::runtime_error(
                std::string("Exception at Transformer::to_log_level_color_format(): ") +
                exception.what()
            );
        }
    }

    std::string Transformer::to_none_format(
        const std::string& text) const
    {
        try
        {
            if (text.empty())
            {
                return UTILITIES.STRING_NONE_1;
            }

            return text;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Transformer::to_none_format(): ") +
                exception.what()
            );
        }
    }

    std::string Transformer::to_na_format(
        const std::string& text) const
    {
        try
        {
            if (text.empty())
            {
                return UTILITIES.STRING_NONE_2;
            }

            return text;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string("Exception at Transformer::to_na_format(): ") +
                exception.what()
            );
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
            throw std::runtime_error
            (std::string("Exception at Transformer::split(): ") +
                exception.what()
            );
        }
    }

    void Transformer::color_type(
        Result<std::string>& result,
        const LogLevel& level) const
    {
        switch (level)
        {
            case LogLevel::ALL:
            {
                result.set_to_good_status_with_value("");
            }
            case LogLevel::INFO:
            {
                result.set_to_good_status_with_value("");
            }
            case LogLevel::DEBUG:
            {
                result.set_to_good_status_with_value("\033[94m");
            }
            case LogLevel::WARNING:
            {
                result.set_to_good_status_with_value("\033[93m");
            }
            case LogLevel::EXCEPTION:
            {
                result.set_to_good_status_with_value("\033[91m");
            }
            case LogLevel::CRITICAL:
            {
                result.set_to_good_status_with_value("\033[95m");
            }
            case LogLevel::SUCCESS:
            {
                result.set_to_good_status_with_value("\033[92m");
            }
            case LogLevel::HIGHLIGHTED_INFO:
            {
                result.set_to_good_status_with_value("\033[94m");
            }
            default:
            {
                result.set_to_good_status_with_value("");
            }
        }
    }

    void Transformer::to_log_format(
        Result<std::string>& result,
        const std::string& text,
        const LogLevel& level,
        const size_t& output_size) const
    {
        std::string content;
        content.reserve(output_size);

        content =
            "[" +
            TIME.now(TimeFormat::FULL_TIMESTAMP) +
            "] [" +
            get_log_level_string(level) +
            "]\t" +
            text +
            "\n";

        result.set_to_good_status_with_value(content);
    }

    void Transformer::to_log_level_color_format(
        Result<std::string>& result,
        const std::string& text,
        const LogLevel& level,
        const size_t& output_size) const
    {
        std::string content;
        content.reserve(output_size);
        content = text;

        result.set_to_good_status_with_value(content);
    }

    void Transformer::to_none_format(
        Result<std::string>& result,
        const std::string& text) const
    {
        if (text.empty())
        {
            result.set_to_good_status_with_value(
                UTILITIES.STRING_NONE_1
            );
        }

        result.set_to_good_status_with_value(text);
    }

    void Transformer::to_na_format(
        Result<std::string>& result,
        const std::string& text) const
    {
        if (text.empty())
        {
            result.set_to_good_status_with_value(
                UTILITIES.STRING_NONE_2
            );
        }

        result.set_to_good_status_with_value(text);
    }

    void Transformer::split(
        Result<std::vector<std::string>>& result,
        const std::string& text,
        const std::string& delimeter) const
    {
        auto content = absl::StrSplit(text, delimeter);

        result.set_to_good_status_with_value(
            std::vector<std::string>(content.begin(), content.end())
        );
    }

    void Transformer::setup(Result<void>& result)
    {
        result.set_to_good_status_without_value();
    }
}
