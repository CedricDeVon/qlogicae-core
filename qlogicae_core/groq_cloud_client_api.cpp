#include "pch.hpp"

#include "groq_cloud_client_api.hpp"

namespace QLogicaeCore
{
    GroqCloudClientAPI::GroqCloudClientAPI()
    {

    }

    GroqCloudClientAPI::GroqCloudClientAPI(const GroqCloudClientAPIPromptConfigurations& value)
    {
        set_prompt_configurations(value);
    }

    double GroqCloudClientAPI::get_top_p()
    {
        return _prompt_configurations.top_p;
    }

    std::string GroqCloudClientAPI::get_model()
    {
        return _prompt_configurations.model;
    }

    double GroqCloudClientAPI::get_temperature()
    {
        return _prompt_configurations.temperature;
    }

    uint8_t GroqCloudClientAPI::get_retry_count()
    {
        return _prompt_configurations.retry_count;
    }

    std::string GroqCloudClientAPI::get_api_key()
    {
        if (!_prompt_configurations.api_key_extractor)
        {
            return "";
        }
        return _prompt_configurations.api_key_extractor();
    }

    double GroqCloudClientAPI::get_presence_penalty()
    {
        return _prompt_configurations.presence_penalty;
    }

    uint32_t GroqCloudClientAPI::get_maximum_tokens()
    {
        return _prompt_configurations.maximum_tokens;
    }

    double GroqCloudClientAPI::get_frequency_penalty()
    {
        return _prompt_configurations.frequency_penalty;
    }

    bool GroqCloudClientAPI::get_is_streaming_enabled()
    {
        return _prompt_configurations.is_streaming_enabled;
    }

    std::vector<std::string> GroqCloudClientAPI::get_stop_sequences()
    {
        return _prompt_configurations.stop_sequences;
    }

    std::optional<std::string> GroqCloudClientAPI::get_system_prompt()
    {
        return _prompt_configurations.system_prompt;
    }

    std::chrono::milliseconds GroqCloudClientAPI::get_timeout_duration()
    {
        return _prompt_configurations.timeout_duration;
    }

    GroqCloudClientAPIPromptConfigurations GroqCloudClientAPI::get_prompt_configurations()
    {
        return _prompt_configurations;
    }

    void GroqCloudClientAPI::set_top_p(const double& value)
    {
        _prompt_configurations.top_p = value;
    }

    void GroqCloudClientAPI::set_temperature(const double& value)
    {
        _prompt_configurations.temperature = value;
    }

    void GroqCloudClientAPI::set_retry_count(const uint8_t& value)
    {
        _prompt_configurations.retry_count = value;
    }

    void GroqCloudClientAPI::set_model(const std::string_view& value)
    {
        _prompt_configurations.model = std::string(value);
    }

    void GroqCloudClientAPI::set_presence_penalty(const double& value)
    {
        _prompt_configurations.presence_penalty = value;
    }

    void GroqCloudClientAPI::set_maximum_tokens(const uint32_t& value)
    {
        _prompt_configurations.maximum_tokens = value;
    }

    void GroqCloudClientAPI::set_frequency_penalty(const double& value)
    {
        _prompt_configurations.frequency_penalty = value;
    }

    void GroqCloudClientAPI::set_is_streaming_enabled(const bool& value)
    {
        _prompt_configurations.is_streaming_enabled = value;
    }

    void GroqCloudClientAPI::set_api_key_extractor(std::function<std::string()> value)
    {
        _prompt_configurations.api_key_extractor = std::move(value);
    }

    void GroqCloudClientAPI::set_stop_sequences(const std::vector<std::string>& value)
    {
        _prompt_configurations.stop_sequences = value;
    }

    void GroqCloudClientAPI::set_system_prompt(const std::optional<std::string>& value)
    {
        _prompt_configurations.system_prompt = value;
    }

    void GroqCloudClientAPI::set_timeout_duration(const std::chrono::milliseconds& value)
    {
        _prompt_configurations.timeout_duration = value;
    }

    void GroqCloudClientAPI::set_prompt_configurations(const GroqCloudClientAPIPromptConfigurations& value)
    {
        _prompt_configurations = value;
    }

    GroqCloudClientAPIResponse GroqCloudClientAPI::prompt(const GroqCloudClientAPIRequest& value)
    {
        return prompt_async(value).get();
    }

    std::future<GroqCloudClientAPIResponse> GroqCloudClientAPI::prompt_async(const GroqCloudClientAPIRequest& value)
    {
        return std::async(std::launch::async, [this, value]() -> GroqCloudClientAPIResponse
            {
                GroqCloudClientAPIResponse response;
                try
                {
                    std::stop_source stop_source;
                    _send_internal(stop_source.get_token());
                    on_response.dispatch(response);
                }
                catch (const std::exception& exception)
                {
                    on_exception.dispatch(exception);
                }

                return response;
            });
    }

}

