#pragma once

#include "time.hpp"
#include "logger.hpp"
#include "result.hpp"
#include "log_level.hpp"
#include "time_format.hpp"
#include "result_status.hpp"

namespace QLogicaeCore
{
    class Transformer
    {
    public:
        bool setup();
        
        std::future<bool> setup_async(
            const std::function<void(const bool& result)>& callback =
            [](const bool& result) {}
        );

        void setup(
            Result<void>& result
        );

        void setup_async(
            Result<std::future<void>>& result,
            const std::function<void(Result<void>& result)>& callback =
            [](Result<void>& result) {}
        );

        std::string color_type(
            const LogLevel& log_level
        );

        void color_type(
            Result<std::string>& result,
            const LogLevel& log_level
        );

        std::string to_na_format(
            const std::string& text = ""
        );

        void to_na_format(
            Result<std::string>& result,
            const std::string& text = ""
        );

        std::string to_none_format(
            const std::string& text = ""
        );

        void to_none_format(
            Result<std::string>& result,
            const std::string& text = ""
        );

        std::vector<std::string> split(
            const std::string& text,
            const std::string& delimeters
        );

        void split(
            Result<std::vector<std::string>>& result,
            const std::string& text,
            const std::string& delimeters
        );

        std::string to_log_format(
            const std::string& text,
            const LogLevel& log_level,
            const size_t& length = 128
        );

        void to_log_format(
            Result<std::string>& result,
            const std::string& text,
            const LogLevel& log_level,
            const size_t& length = 128
        );

        std::string to_log_format(
            const std::string& text,
            const LogLevel& log_level,
            const TimeFormat& time_format,
            const size_t& length = 128
        );

        void to_log_format(
            Result<std::string>& result,
            const std::string& text,
            const LogLevel& log_level,
            const TimeFormat& time_format,
            const size_t& length = 128
        );

        std::string to_log_format(
            const std::string& name,
            const std::string& text,
            const LogLevel& log_level,
            const TimeFormat& time_format,
            const size_t& length = 128
        );

        void to_log_format(
            Result<std::string>& result,
            const std::string& name,
            const std::string& text,
            const LogLevel& log_level,
            const TimeFormat& time_format,
            const size_t& length = 128
        );

        std::string to_log_level_color_format(
            const std::string& text = "",
            const LogLevel& log_level = LogLevel::INFO,
            const size_t& length = 128
        );

        void to_log_level_color_format(
            Result<std::string>& result,
            const std::string& text = "",
            const LogLevel& log_level = LogLevel::INFO,
            const size_t& length = 128
        );

        std::string to_result_message_format(
            const std::string& text = "",
            const ResultStatus& result_status = ResultStatus::INFO,
            const TimeFormat& time_format =
            TimeFormat::FULL_TIMESTAMP,
            const size_t& length = 128
        );

        void to_result_message_format(
            Result<std::string>& result,
            const std::string& text = "",
            const ResultStatus& result_status = ResultStatus::INFO,
            const TimeFormat& time_format =
            TimeFormat::FULL_TIMESTAMP,
            const size_t& length = 128
        );

        std::string to_exception_text_format(
            const std::string& origin,
            const std::string& message
        );

        void to_exception_text_format(
            Result<std::string>& result,
            const std::string& origin,
            const std::string& message
        );

        std::string to_uppercase(
            const std::string text
        );

        std::string to_lowercase(
            const std::string text
        );

        std::string to_capitalized(
            const std::string text
        );

        void to_uppercase(
            Result<std::string>& result,
            const std::string text
        );

        void to_lowercase(
            Result<std::string>& result,
            const std::string text
        );

        void to_capitalized(
            Result<std::string>& result,
            const std::string text
        );

        std::wstring to_uppercase(
            const std::wstring text
        );

        std::wstring to_lowercase(
            const std::wstring text
        );

        std::wstring to_capitalized(
            const std::wstring text
        );

        void to_uppercase(
            Result<std::wstring>& result,
            const std::wstring text
        );

        void to_lowercase(
            Result<std::wstring>& result,
            const std::wstring text
        );

        void to_capitalized(
            Result<std::wstring>& result,
            const std::wstring text
        );

        const char* to_uppercase(
            const char* text
        );

        const char* to_lowercase(
            const char* text
        );

        const char* to_capitalized(
            const char* text
        );

        void to_uppercase(
            Result<const char*>& result,
            const char* text
        );

        void to_lowercase(
            Result<const char*>& result,
            const char* text
        );

        void to_capitalized(
            Result<const char*>& result,
            const char* text
        );

        static Transformer& get_instance();

        static void get_instance(
            Result<Transformer*>& result
        );

    protected:
        Transformer();
        
        ~Transformer();
        
        Transformer(
            const Transformer& instance
        ) = delete;
        
        Transformer(
            Transformer&& instance
        ) noexcept = delete;
        
        Transformer& operator = (
            Transformer&& instance
            ) = delete;
        
        Transformer& operator = (
            const Transformer& instance
            ) = delete;
    };

    constexpr std::string get_log_level_string(
        const LogLevel& level        
    )
    {
        switch (level)
        {
            case LogLevel::ALL:
                return UTILITIES.LOG_LEVEL_INFO;
            
            case LogLevel::INFO:
                return UTILITIES.LOG_LEVEL_INFO;
            
            case LogLevel::DEBUG:
                return UTILITIES.LOG_LEVEL_DEBUG;
            
            case LogLevel::SUCCESS:
                return UTILITIES.LOG_LEVEL_SUCCESS;
            
            case LogLevel::WARNING:
                return UTILITIES.LOG_LEVEL_WARNING;
            
            case LogLevel::CRITICAL:
                return UTILITIES.LOG_LEVEL_CRITICAL;
            
            case LogLevel::EXCEPTION:
                return UTILITIES.LOG_LEVEL_EXCEPTION;

            case LogLevel::HIGHLIGHTED_INFO:
                return UTILITIES.LOG_LEVEL_HIGHLIGHTED_INFO;

            default:
                return UTILITIES.LOG_LEVEL_INFO;
        }
    }

    constexpr void get_log_level_string(
        const LogLevel& level,
        Result<std::string>& result
    )
    {
        switch (level)
        {
            case LogLevel::ALL:
                result.set_to_good_status_with_value(UTILITIES.LOG_LEVEL_INFO);
                break;

            case LogLevel::INFO:
                result.set_to_good_status_with_value(UTILITIES.LOG_LEVEL_INFO);
                break;

            case LogLevel::DEBUG:
                result.set_to_good_status_with_value(UTILITIES.LOG_LEVEL_DEBUG);
                break;

            case LogLevel::SUCCESS:
                result.set_to_good_status_with_value(UTILITIES.LOG_LEVEL_SUCCESS);
                break;

            case LogLevel::WARNING:
                result.set_to_good_status_with_value(UTILITIES.LOG_LEVEL_WARNING);
                break;

            case LogLevel::CRITICAL:
                result.set_to_good_status_with_value(UTILITIES.LOG_LEVEL_CRITICAL);
                break;

            case LogLevel::EXCEPTION:
                result.set_to_good_status_with_value(UTILITIES.LOG_LEVEL_EXCEPTION);
                break;

            case LogLevel::HIGHLIGHTED_INFO:
                result.set_to_good_status_with_value(UTILITIES.LOG_LEVEL_HIGHLIGHTED_INFO);
                break;

            default:
                result.set_to_good_status_with_value(UTILITIES.LOG_LEVEL_INFO);
        }
    }

    inline static Transformer& TRANSFORMER =
        Transformer::get_instance();
}
