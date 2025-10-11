#pragma once

namespace QLogicaeCore
{
    struct JsonWebTokenReverseInput
    {
        std::string token;
        std::string issuer;
        std::string public_key;
    };
}
