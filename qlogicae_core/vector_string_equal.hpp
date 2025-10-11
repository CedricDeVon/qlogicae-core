#pragma once

namespace QLogicaeCore
{
    struct VectorStringEqual
    {
        bool operator()(const std::vector<std::string>& lhs,
            const std::vector<std::string>& rhs) const noexcept
        {
            return lhs == rhs;
        }
    };
}
