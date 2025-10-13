#pragma once

#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

namespace QLogicaeCore
{
    using segment_t = boost::interprocess::managed_shared_memory;
    using manager_t = segment_t::segment_manager;
    using char_allocator_t = boost::interprocess::allocator<char, manager_t>;
    using string_t = boost::interprocess::basic_string<char, std::char_traits<char>, char_allocator_t>;
    using value_allocator_t = boost::interprocess::allocator<std::pair<const string_t, string_t>, manager_t>;
    using map_t = boost::interprocess::map<string_t, string_t, std::less<string_t>, value_allocator_t>;

    struct BoostInterprocessCacheSharedData
    {
        boost::interprocess::interprocess_mutex _mutex;

        map_t map;
        BoostInterprocessCacheSharedData(
            const value_allocator_t& alloc
        );
    };
}