#pragma once

namespace QLogicaeCore
{
    struct JsonWebTokenReverseResult
    {
        bool is_successful = false;

        std::string message;

        std::string subject;

        std::map<std::string, std::string> headers;

        std::map<std::string, std::string> payloads;
    };
}
