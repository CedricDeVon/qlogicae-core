#pragma once

namespace QLogicaeCore
{
    struct VectorStringHash
    {
        std::size_t operator()(
            const std::vector<std::string>& vec
        ) const noexcept
        {
            std::size_t seed = 0;
            std::hash<std::string> string_hasher;
            for (const auto& s : vec)
            {
                seed ^=
                    string_hasher(s) +
                    0x9e3779b9 +
                    (seed << 6) +
                    (seed >> 2);
            }
            return seed;
        }
    };
}
