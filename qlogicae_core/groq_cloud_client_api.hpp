#pragma once

#include "globals.hpp"
#include "event_dispatcher.hpp"
#include "abstract_value_extractor.hpp"

namespace QLogicaeCore
{
    class GroqCloudClientAPI
    {
    public:
        GroqCloudClientAPI();

        ~GroqCloudClientAPI() = default;
        
        GroqCloudClientAPI(
            const GroqCloudClientAPI& groq_cloud_client_api
        ) = delete;
        
        GroqCloudClientAPI(
            GroqCloudClientAPI&& groq_cloud_client_api
        ) noexcept = delete;
        
        GroqCloudClientAPI(
            const GroqCloudClientAPIPromptConfigurations&
                groq_cloud_client_api
        );
        
        GroqCloudClientAPI& operator=(
            GroqCloudClientAPI&& groq_cloud_client_api
        ) = delete;
        
        GroqCloudClientAPI& operator=(
            const GroqCloudClientAPI& groq_cloud_client_api
        ) = delete;

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

        GroqCloudClientAPIPromptConfigurations
            get_prompt_configurations();

        void set_top_p(
            const double& value
        );

        void set_temperature(
            const double& value
        );

        void set_retry_count(
            const uint8_t& value
        );

        void set_model(
            const std::string_view& value
        );

        void set_presence_penalty(
            const double& value
        );

        void set_maximum_tokens(
            const uint32_t& value
        );

        void set_frequency_penalty(
            const double& value
        );

        void set_is_streaming_enabled(
            const bool& value
        );

        void set_api_key_extractor(
            std::function<std::string()> value
        );

        void set_stop_sequences(
            const std::vector<std::string>& value
        );

        void set_system_prompt(
            const std::optional<std::string>& value
        );

        void set_timeout_duration(
            const std::chrono::milliseconds& value
        );

        void set_prompt_configurations(
            const GroqCloudClientAPIPromptConfigurations& value
        );

        GroqCloudClientAPIResponse prompt(
            const GroqCloudClientAPIRequest& value
        );

        std::future<GroqCloudClientAPIResponse> prompt_async(
            const GroqCloudClientAPIRequest& value
        );

        EventDispatcher<void> on_retry;
        EventDispatcher<void> on_timeout;
        EventDispatcher<void> on_cancelled;
        EventDispatcher<std::exception> on_exception;
        EventDispatcher<std::string_view> on_stream_chunk;
        EventDispatcher<GroqCloudClientAPIResponse> on_response;
        EventDispatcher<uint32_t, std::string_view> on_http_error;

    protected:
        mutable std::mutex _messages_mutex;
        mutable std::mutex _response_mutex;
        GroqCloudClientAPIPromptConfigurations _prompt_configurations;      

        std::string _build_request_body() const;

        bool _send_internal(const std::stop_token& token);
    };
}



