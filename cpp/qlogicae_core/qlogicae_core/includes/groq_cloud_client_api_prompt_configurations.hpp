#pragma once

#include "utilities.hpp"

#include <cstdio>

namespace QLogicaeCore
{
    struct GroqCloudClientAPIPromptConfigurations
    {
        std::function<std::string()> api_key_extractor;
        
        std::string model =
            UTILITIES.DEFAULT_GROQ_CLOUD_CLIENT_API_TYPE.data();
        
        double top_p = 1.0;
        
        double temperature = 0.7;
        
        double frequency_penalty = 0.0;
        
        double presence_penalty = 0.0;
        
        uint32_t maximum_tokens = 1024;
        
        std::vector<std::string> stop_sequences;
        
        std::optional<std::string> system_prompt;
        
        bool is_streaming_enabled = false;
        
        uint8_t retry_count = 3;
        
        std::chrono::milliseconds timeout_duration =
            std::chrono::seconds(10);
    };
}
