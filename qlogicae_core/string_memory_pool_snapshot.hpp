#pragma once

namespace QLogicaeCore
{
    struct StringMemoryPoolSnapshot
    {
        std::size_t pool_hits = 0;
        std::size_t bytes_used = 0;
        std::size_t pool_misses = 0;
        std::size_t interned_count = 0;
    };
}
