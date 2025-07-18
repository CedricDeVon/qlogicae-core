#pragma once

#include "pch.h"

#include "abstract_value_extractor.hpp"

namespace QLogicaeCore
{
    /*
    struct GroqCloudClientAPIConfigurations
    {
        std::function<std::string()> api_extractor;
        std::string model = "llama3-8b-8192";
        double top_p = 1.0;
        double temperature = 0.7;
        double frequency_penalty = 0.0;
        double presence_penalty = 0.0;
        uint32_t maximum_tokens = 1024;
        std::vector<std::string> stop_sequences;
        std::optional<std::string> system_prompt;
        bool is_streaming_enabled = false;
        uint8_t retry_count = 3;
        std::chrono::milliseconds timeout = std::chrono::seconds(10);
    };

    struct GroqCloudClientAPIRequest
    {
        std::string prompt = "";
    };

    struct GroqCloudClientAPIResponse
    {
        std::string body = "";
        uint32_t status_code = 0;
        std::optional<std::string> error;
    };

    class GroqCloudClientAPI
    {
    public:
        GroqCloudClientAPI() = default;
        ~GroqCloudClientAPI() = default;
        GroqCloudClientAPI(const GroqCloudClientAPI&) = delete;
        GroqCloudClientAPI(GroqCloudClientAPI&&) noexcept = delete;
        GroqCloudClientAPI(const GroqCloudClientAPIConfigurations&);
        GroqCloudClientAPI& operator=(GroqCloudClientAPI&&) = delete;
        GroqCloudClientAPI& operator=(const GroqCloudClientAPI&) = delete;


        std::function<void(const std::string_view&)> on_request;
        std::function<void(const std::string_view&)> on_response;
        std::function<void(const uint32_t&, const std::string_view&)> on_http_error;
        std::function<void(const uint32_t&, const std::chrono::milliseconds&)> on_retry;
        std::function<void()> on_timeout;
        std::function<void(const std::exception&)> on_exception;
        std::function<void()> on_cancellation;


    protected:
        mutable std::mutex _messages_mutex;
        mutable std::mutex _response_mutex;
        GroqCloudClientAPIConfigurations _prompt_config;

        
        

        bool _send_internal(const std::stop_token* token);
        std::string _build_request_body() const;
    };
    */
}

/*

namespace QLogicaeCore
{   
    class GroqCloudClient
    {
    public:
        
        void set_api_key(const std::string_view& api_key);
        void set_prompt_config(const PromptConfig& config);
        void set_timeout(const std::chrono::milliseconds& timeout);
        void set_streaming_enabled(const bool& enabled);
        void set_retry_count(const uint32_t& retry_count);

        void add_user_message(const std::string_view& message);
        void add_assistant_message(const std::string_view& message);
        void queue_user_message_async(const std::string_view& message);
        void clear_messages();

        bool send();
        std::future<bool> send_async();
        std::future<bool> send_async_with_cancel(const std::stop_token& token);
        void send_async_with_callback(const std::function<void(bool)>& callback);

        std::string get_last_response() const;
        std::string get_raw_response() const;
        uint32_t get_status_code() const;
        std::optional<std::string> get_error_message() const;

    };
}

*/

