#include "pch.hpp"

#include "../includes/boost_interprocess_cache_shared_data.hpp"

namespace QLogicaeCore
{
    BoostInterprocessCacheSharedData::BoostInterprocessCacheSharedData(
        const value_allocator_t& alloc
    ) :
        map(std::less<string_t>(), alloc)
    {

    }
}

