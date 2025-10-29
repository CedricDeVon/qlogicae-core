#include "pch.hpp"

#include "string_memory_pool_diagnostics.hpp"

namespace QLogicaeCore
{
    void StringMemoryPoolDiagnostics::reset()
    {
        pool_hits = 0;

        pool_misses = 0;

        interned_count = 0;

        bytes_used = 0;
    }
}
