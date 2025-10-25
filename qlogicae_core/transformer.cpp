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
            get_log_level_string(level) +
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
            get_log_level_string(log_level) +
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

        }
    }

    void Transformer::to_exception_text_format(
        Result<std::string>& result,
        const std::string& origin,
        const std::string& text
    )
    {
        result.set_to_good_status_with_value(
            "Exception at " + origin + " - " + text
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
