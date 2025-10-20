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
        const LogLevel& level)
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
        const LogLevel& log_level,
        const TimeFormat& time_format,
        const size_t& output_size        
    )
    {
        try
        {
            std::string result;
            result.reserve(output_size);

            result =
                "[" +
                TIME.now(time_format) +
                "] [" +
                get_log_level_string(log_level) +
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

    std::string Transformer::to_log_format(
        const std::string& text,
        const LogLevel& log_level,
        const size_t& output_size
    )
    {
        try
        {
            std::string result;
            result.reserve(output_size);

            result =
                "[" +
                TIME.now(TimeFormat::FULL_TIMESTAMP) +
                "] [" +
                get_log_level_string(log_level) +
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

    std::string Transformer::to_result_message_format(
        const std::string& text,
        const ResultStatus& result_status,
        const TimeFormat& time_format,
        const size_t& output_size
    )
    {
        std::string content;
        content.reserve(output_size);

        content =
            "[" +
            TIME.now(time_format) +
            "] [" +
            UTILITIES.RESULT_STATUS_ENUMS_2.at(result_status) +
            "]\t" +
            text +
            "\n";
        
        return content;
    }

    std::string Transformer::to_log_level_color_format(
        const std::string& text,
        const LogLevel& level,
        const size_t& output_size)
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
        const std::string& text)
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
        const std::string& text)
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
        const std::string& delimeter)
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
        const LogLevel& level
    )
    {
        switch (level)
        {
            case LogLevel::ALL:
            {
                return result.set_to_good_status_with_value("");
            }
            case LogLevel::INFO:
            {
                return result.set_to_good_status_with_value("");
            }
            case LogLevel::DEBUG:
            {
                return result.set_to_good_status_with_value("\033[94m");
            }
            case LogLevel::WARNING:
            {
                return result.set_to_good_status_with_value("\033[93m");
            }
            case LogLevel::EXCEPTION:
            {
                return result.set_to_good_status_with_value("\033[91m");
            }
            case LogLevel::CRITICAL:
            {
                return result.set_to_good_status_with_value("\033[95m");
            }
            case LogLevel::SUCCESS:
            {
                return result.set_to_good_status_with_value("\033[92m");
            }
            case LogLevel::HIGHLIGHTED_INFO:
            {
                return result.set_to_good_status_with_value("\033[94m");
            }
            default:
            {
                return result.set_to_good_status_with_value("");
            }
        }
    }

    void Transformer::to_log_format(
        Result<std::string>& result,
        const std::string& text,
        const LogLevel& level,
        const TimeFormat& time_format,
        const size_t& output_size
    )
    {
        std::string content;
        content.reserve(output_size);

        content =
            "[" +
            TIME.now(time_format) +
            "] [" +
            get_log_level_string(level) +
            "]\t" +
            text +
            "\n";

        result.set_to_good_status_with_value(content);
    }

    void Transformer::to_result_message_format(
        Result<std::string>& result,
        const std::string& text,
        const ResultStatus& result_status,
        const TimeFormat& time_format,
        const size_t& output_size
    )
    {
        std::string content;
        content.reserve(output_size);

        content =
            "[" +
            TIME.now(time_format) +
            "] [" +
            UTILITIES.RESULT_STATUS_ENUMS_2.at(result_status) +
            "]\t" +
            text +
            "\n";

        result.set_to_good_status_with_value(content);
    }

    void Transformer::to_log_level_color_format(
        Result<std::string>& result,
        const std::string& text,
        const LogLevel& level,
        const size_t& output_size
    )
    {
        std::string content;
        content.reserve(output_size);
        content = text;

        result.set_to_good_status_with_value(content);
    }

    void Transformer::to_none_format(
        Result<std::string>& result,
        const std::string& text
    )
    {
        if (text.empty())
        {
            return result.set_to_good_status_with_value(
                UTILITIES.STRING_NONE_1
            );            
        }

        result.set_to_good_status_with_value(text);
    }

    void Transformer::to_na_format(
        Result<std::string>& result,
        const std::string& text
    )
    {
        if (text.empty())
        {
            return result.set_to_good_status_with_value(
                UTILITIES.STRING_NONE_2
            );
        }

        result.set_to_good_status_with_value(text);
    }

    void Transformer::split(
        Result<std::vector<std::string>>& result,
        const std::string& text,
        const std::string& delimeter
    )
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
