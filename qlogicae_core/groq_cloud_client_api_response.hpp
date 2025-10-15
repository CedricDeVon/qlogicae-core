#pragma once

namespace QLogicaeCore
{
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
}
