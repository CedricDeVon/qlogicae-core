#include "pch.hpp"

#include "transformer.hpp"

namespace QLogicaeCore
{    
    Transformer::Transformer()
    {

    }

    Transformer::~Transformer()
    {

    }

    bool Transformer::setup()
    {
        try
        {
            Result<void> result;

            setup(result);

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Transformer::setup()",
                exception.what()
            );

            return false;
        }
    }

    void Transformer::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    std::string Transformer::color_type(
        const LogLevel& level
    )
    {
        try
        {
            Result<std::string> string_result;

            color_type(string_result, level);

            return string_result.get_value();

        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Transformer::color_type()",
                exception.what()
            );

            return "";
        }
    }

    std::future<bool> Transformer::setup_async(
        const std::function<void(const bool& value)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                bool value = setup();

                promise.set_value(
                    value
                );

                if (callback)
                {
                    callback(
                        value
                    );
                }
            }
        );

        return future;
    }

    void Transformer::setup_async(
        Result<std::future<void>>& result,
        const std::function<void(Result<void>& result)>& callback
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(result);

                promise.set_value();

                callback(
                    result
                );
            }
        );

        result.set_to_good_status_with_value(
            std::move(
                future
            )
        );
    }
    void Transformer::color_type(
        Result<std::string>& result,
        const LogLevel& log_level
    )
    {
        switch (log_level)
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

    std::string Transformer::to_na_format(
        const std::string& text
    )
    {
        try
        {
            Result<std::string> string_result;

            to_na_format(string_result, text);

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Transformer::to_na_format()",
                exception.what()
            );

            return "";
        }
    }

    void Transformer::to_na_format(
        Result<std::string>& result,
        const std::string& text
    )
    {        
        result.set_to_good_status_with_value(
            (!text.empty()) ? text : UTILITIES.STRING_NONE_2
        );
    }

    std::string Transformer::to_none_format(
        const std::string& text
    )
    {
        try
        {
            Result<std::string> string_result;

            to_none_format(string_result, text);

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Transformer::to_none_format()",
                exception.what()
            );

            return "";
        }
    }

    void Transformer::to_none_format(
        Result<std::string>& result,
        const std::string& text
    )
    {
        result.set_to_good_status_with_value(
            (!text.empty()) ? text : UTILITIES.STRING_NONE_1
        );
    }

    std::vector<std::string> Transformer::split(
        const std::string& text,
        const std::string& delimeter
    )
    {
        try
        {
            Result<std::vector<std::string>> string_vector_result;

            split(
                string_vector_result,
                text,
                delimeter
            );

            return string_vector_result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Transformer::split()",
                exception.what()
            );

            return {};
        }
    }

    void Transformer::split(
        Result<std::vector<std::string>>& result,
        const std::string& text,
        const std::string& delimeter
    )
    {
        auto content = absl::StrSplit(
            text,
            delimeter
        );

        result.set_to_good_status_with_value(
            std::vector<std::string>(
                content.begin(),
                content.end()
            )
        );
    }

    std::string Transformer::to_log_format(
        const std::string& text,
        const LogLevel& log_level,
        const TimeFormat& time_format,
        const size_t& output_length        
    )
    {
        try
        {
            Result<std::string> string_result;

            to_log_format(
                string_result,
                text,
                log_level,
                time_format,
                output_length
            );

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Transformer::to_log_format()",
                exception.what()
            );

            return "";
        }
    }

    void Transformer::to_log_format(
        Result<std::string>& result,
        const std::string& text,
        const LogLevel& level,
        const TimeFormat& time_format,
        const size_t& output_length
    )
    {
        result.get_value().reserve(output_length);
        result.set_value(
            "[" +
            TIME.now(time_format) +
            "] [" +
            UTILITIES.LOG_LEVEL_ENUMS_2.at(level) +
            "]\t" +
            text +
            "\n"
        );
        result.set_status_to_good();
    }

    std::string Transformer::to_log_format(
        const std::string& name,
        const std::string& text,
        const LogLevel& log_level,
        const TimeFormat& time_format,
        const size_t& output_length
    )
    {
        try
        {
            Result<std::string> string_result;

            to_log_format(
                string_result,
                name,
                text,
                log_level,
                time_format,
                output_length
            );

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Transformer::to_log_format()",
                exception.what()
            );

            return "";
        }
    }

    void Transformer::to_log_format(
        Result<std::string>& result,
        const std::string& name,
        const std::string& text,
        const LogLevel& level,
        const TimeFormat& time_format,
        const size_t& output_length
    )
    {
        result.get_value().reserve(output_length);
        result.set_value(
            "[" +
            name +
            "] [" +
            TIME.now(time_format) +
            "] [" +
            UTILITIES.LOG_LEVEL_ENUMS_2.at(level) +
            "]\t" +
            text +
            "\n"
        );
        result.set_status_to_good();
    }

    std::string Transformer::to_log_format(
        const std::string& text,
        const LogLevel& log_level,
        const size_t& output_length
    )
    {
        try
        {
            Result<std::string> string_result;

            to_log_format(
                string_result,
                text,
                log_level,
                output_length
            );

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Transformer::to_log_format()",
                exception.what()
            );

            return "";
        }
    }

    void Transformer::to_log_format(
        Result<std::string>& result,
        const std::string& text,
        const LogLevel& log_level,
        const size_t& output_length
    )
    {
        result.get_value().reserve(output_length);
        result.set_value(
            "[" +
            TIME.now(TimeFormat::FULL_TIMESTAMP) +
            "] [" +
            UTILITIES.LOG_LEVEL_ENUMS_2.at(log_level) +
            "]\t" +
            text +
            "\n"
        );
        result.set_status_to_good();
    }



    std::string Transformer::to_log_level_color_format(
        const std::string& text,
        const LogLevel& log_level,
        const size_t& output_length
    )
    {
        try
        {
            Result<std::string> string_result;

            to_log_level_color_format(
                string_result,
                text,
                log_level,
                output_length
            );

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Transformer::to_log_level_color_format()",
                exception.what()
            );

            return "";
        }
    }

    void Transformer::to_log_level_color_format(
        Result<std::string>& result,
        const std::string& text,
        const LogLevel& log_level,
        const size_t& output_length
    )
    {
        std::string output;
        output.reserve(output_length);

        output = text;

        result.set_to_good_status_with_value(
            output
        );
    }



    std::string Transformer::to_result_message_format(
        const std::string& text,
        const ResultStatus& result_status,
        const TimeFormat& time_format,
        const size_t& output_length
    )
    {
        try
        {
            Result<std::string> string_result;

            to_result_message_format(
                string_result,
                text,
                result_status,
                time_format,
                output_length
            );

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Transformer::to_result_message_format()",
                exception.what()
            );

            return "";
        }
    }

    void Transformer::to_result_message_format(
        Result<std::string>& result,
        const std::string& text,
        const ResultStatus& result_status,
        const TimeFormat& time_format,
        const size_t& output_length
    )
    {
        result.get_value().reserve(output_length);
        result.set_value(
            "[" +
            TIME.now(time_format) +
            "] [" +
            UTILITIES.RESULT_STATUS_ENUMS_2.at(result_status) +
            "]\t" +
            text +
            "\n"
        );
        result.set_status_to_good();
    }

    std::string Transformer::to_exception_text_format(
        const std::string& origin,
        const std::string& text
    )
    {
        try
        {
            Result<std::string> string_result;

            to_exception_text_format(
                string_result,
                origin,
                text
            );

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::Transformer::to_exception_text_format()",
                exception.what()
            );

            return "";
        }
    }

    void Transformer::to_exception_text_format(
        Result<std::string>& result,
        const std::string& origin,
        const std::string& text
    )
    {
        result.set_to_good_status_with_value(
            "'" + origin + "' - " + text
        );
    }

    std::string Transformer::to_uppercase(
        const std::string text
    )
    {
        return absl::AsciiStrToUpper(text);
    }

    std::string Transformer::to_lowercase(
        const std::string text
    )
    {
        return absl::AsciiStrToLower(text);
    }

    std::string Transformer::to_capitalized(
        const std::string text
    )
    {
        if (text.empty())
        {
            return text;
        }

        std::string result = absl::AsciiStrToLower(text);
        result[0] = static_cast<char>(std::toupper(result[0]));
        return result;
    }

    void Transformer::to_uppercase(
        Result<std::string>& result,
        const std::string text
    )
    {
        result.set_to_good_status_with_value(
            absl::AsciiStrToUpper(text)
        );
    }

    void Transformer::to_lowercase(
        Result<std::string>& result,
        const std::string text
    )
    {
        result.set_to_good_status_with_value(
            absl::AsciiStrToLower(text)
        );
    }

    void Transformer::to_capitalized(
        Result<std::string>& result,
        const std::string text
    )
    {
        if (text.empty())
        {
            result.set_to_good_status_with_value(text);
            return;
        }

        std::string output = absl::AsciiStrToLower(text);
        output[0] = static_cast<char>(std::toupper(output[0]));
        result.set_to_good_status_with_value(output);
    }

    std::wstring Transformer::to_uppercase(
        const std::wstring text
    )
    {
        std::wstring result = text;
        std::transform(
            result.begin(),
            result.end(),
            result.begin(),
            ::towupper
        );
        return result;
    }

    std::wstring Transformer::to_lowercase(
        const std::wstring text
    )
    {
        std::wstring result = text;
        std::transform(
            result.begin(),
            result.end(),
            result.begin(),
            ::towlower
        );
        return result;
    }

    std::wstring Transformer::to_capitalized(
        const std::wstring text
    )
    {
        if (text.empty())
        {
            return text;
        }

        std::wstring result = text;
        std::transform(
            result.begin(),
            result.end(),
            result.begin(),
            ::towlower
        );
        result[0] = static_cast<wchar_t>(
            std::towupper(result[0])
            );
        return result;
    }

    void Transformer::to_uppercase(
        Result<std::wstring>& result,
        const std::wstring text
    )
    {
        std::wstring output = text;
        std::transform(
            output.begin(),
            output.end(),
            output.begin(),
            ::towupper
        );
        result.set_to_good_status_with_value(output);
    }

    void Transformer::to_lowercase(
        Result<std::wstring>& result,
        const std::wstring text
    )
    {
        std::wstring output = text;
        std::transform(
            output.begin(),
            output.end(),
            output.begin(),
            ::towlower
        );
        result.set_to_good_status_with_value(output);
    }

    void Transformer::to_capitalized(
        Result<std::wstring>& result,
        const std::wstring text
    )
    {
        if (text.empty())
        {
            result.set_to_good_status_with_value(text);
            return;
        }

        std::wstring output = text;
        std::transform(
            output.begin(),
            output.end(),
            output.begin(),
            ::towlower
        );
        output[0] = static_cast<wchar_t>(
            std::towupper(output[0])
            );
        result.set_to_good_status_with_value(output);
    }

    const char* Transformer::to_uppercase(
        const char* text
    )
    {
        if (!text)
        {
            return "";
        }

        static thread_local std::string buffer;
        buffer = absl::AsciiStrToUpper(text);
        return buffer.c_str();
    }

    const char* Transformer::to_lowercase(
        const char* text
    )
    {
        if (!text)
        {
            return "";
        }

        static thread_local std::string buffer;
        buffer = absl::AsciiStrToLower(text);
        return buffer.c_str();
    }

    const char* Transformer::to_capitalized(
        const char* text
    )
    {
        if (!text)
        {
            return "";
        }

        static thread_local std::string buffer;
        std::string temp = absl::AsciiStrToLower(text);

        if (!temp.empty())
        {
            temp[0] = static_cast<char>(
                std::toupper(temp[0])
                );
        }

        buffer = temp;
        return buffer.c_str();
    }

    void Transformer::to_uppercase(
        Result<const char*>& result,
        const char* text
    )
    {
        result.set_to_good_status_with_value(
            to_uppercase(text)
        );
    }

    void Transformer::to_lowercase(
        Result<const char*>& result,
        const char* text
    )
    {
        result.set_to_good_status_with_value(
            to_lowercase(text)
        );
    }

    void Transformer::to_capitalized(
        Result<const char*>& result,
        const char* text
    )
    {
        result.set_to_good_status_with_value(
            to_capitalized(text)
        );
    }

    Transformer& Transformer::get_instance()
    {
        static Transformer instance;

        return instance;
    }

    void Transformer::get_instance(
        Result<Transformer*>& result
    )
    {
        static Transformer instance;

        result.set_to_good_status_with_value(&instance);
    }
}
