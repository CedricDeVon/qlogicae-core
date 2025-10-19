#pragma once

namespace QLogicaeCore
{
    struct JsonWebTokenTransformInput
    {
        std::string issuer;

        std::string data;

        std::string public_key;

        std::string private_key;

        std::chrono::seconds lifetime;

        std::map<std::string, std::string> claims;
    };
}
