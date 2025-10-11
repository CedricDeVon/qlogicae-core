#pragma once

#include "groq_cloud_client_api_chat_message.hpp"

namespace QLogicaeCore
{
    struct GroqCloudClientAPIRequest
    {
        std::vector<GroqCloudClientAPIChatMessage> messages;
    };
}
