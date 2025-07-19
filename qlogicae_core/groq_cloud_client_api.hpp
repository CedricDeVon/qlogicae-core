#pragma once

#include "pch.h"

#include "event_dispatcher.hpp"
#include "abstract_value_extractor.hpp"

namespace QLogicaeCore
{
    struct GroqCloudClientAPIPromptConfigurations
    {
        std::function<std::string()> api_key_extractor;
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
        std::chrono::milliseconds timeout_duration = std::chrono::seconds(10);
    };

    struct GroqCloudClientAPIChatMessage
    {
        std::string role;
        std::string content;
    };

    struct GroqCloudClientAPIRequest
    {
        std::vector<GroqCloudClientAPIChatMessage> messages;
    };

    struct GroqCloudClientAPIResponse
    {
        std::string id = "";
        std::string object = "";
        std::string model = "";
        uint32_t timestamp_created = 0;
        
        uint32_t total_tokens = 0;
        uint32_t prompt_tokens = 0;
        uint32_t completion_tokens = 0;
        
        uint32_t index = 0;
        std::string role = "";
		std::string content = "";
		std::string finish_reason = "";

        uint32_t status_code = 0;
        std::optional<std::string> error_type;
        std::optional<std::string> error_message;
    };

    class GroqCloudClientAPI
    {
    public:
        GroqCloudClientAPI();
        ~GroqCloudClientAPI() = default;
        GroqCloudClientAPI(const GroqCloudClientAPI&) = delete;
        GroqCloudClientAPI(GroqCloudClientAPI&&) noexcept = delete;
        GroqCloudClientAPI(const GroqCloudClientAPIPromptConfigurations&);
        GroqCloudClientAPI& operator=(GroqCloudClientAPI&&) = delete;
        GroqCloudClientAPI& operator=(const GroqCloudClientAPI&) = delete;

        double get_top_p();
        std::string get_model();
        double get_temperature();
        uint8_t get_retry_count();
        std::string get_api_key();
        double get_presence_penalty();
        uint32_t get_maximum_tokens();
        double get_frequency_penalty();
        bool get_is_streaming_enabled();
        std::vector<std::string> get_stop_sequences();
        std::optional<std::string> get_system_prompt();
        std::chrono::milliseconds get_timeout_duration();
        GroqCloudClientAPIPromptConfigurations get_prompt_configurations();

        void set_top_p(const double& value);
        void set_temperature(const double& value);
        void set_retry_count(const uint8_t& value);
        void set_model(const std::string_view& value);
        void set_presence_penalty(const double& value);
        void set_maximum_tokens(const uint32_t& value);
        void set_frequency_penalty(const double& value);
        void set_is_streaming_enabled(const bool& value);
        void set_api_key_extractor(std::function<std::string()> value);
        void set_stop_sequences(const std::vector<std::string>& value);
        void set_system_prompt(const std::optional<std::string>& value);
        void set_timeout_duration(const std::chrono::milliseconds& value);
        void set_prompt_configurations(const GroqCloudClientAPIPromptConfigurations& value);

        GroqCloudClientAPIResponse prompt(const GroqCloudClientAPIRequest& value);
        std::future<GroqCloudClientAPIResponse> prompt_async(const GroqCloudClientAPIRequest& value);

    protected:
        mutable std::mutex _messages_mutex;
        mutable std::mutex _response_mutex;
        GroqCloudClientAPIPromptConfigurations _prompt_configurations;      

        bool _send_internal(const std::stop_token& token);
        std::string _build_request_body() const;
    };
}

/*

*/

