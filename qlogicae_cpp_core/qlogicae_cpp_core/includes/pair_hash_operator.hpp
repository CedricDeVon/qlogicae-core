#pragma once

namespace QLogicaeCppCore
{
    struct PairHashOperator
    {
        std::size_t operator()(
            const std::pair<void*,
            std::string>& pair
        ) const noexcept
        {
            std::size_t hash_1 = std::hash<void*>{}(pair.first);
            std::size_t hash_2 = std::hash<std::string>{}(pair.second);

            return hash_1 ^ (hash_2 << 1);
        }
    };
}
