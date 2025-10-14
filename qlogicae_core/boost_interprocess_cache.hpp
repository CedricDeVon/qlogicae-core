#pragma once

#include "result.hpp"
#include "utilities.hpp"
#include "byte_size.hpp"
#include "boost_interprocess_cache_shared_data.hpp"

#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

#include <string>
#include <vector>
#include <future>
#include <memory>
#include <utility>
#include <functional>
#include <unordered_map>

namespace QLogicaeCore
{    
    using segment_t = boost::interprocess::managed_shared_memory;
    
    using manager_t = segment_t::segment_manager;
    
    using char_allocator_t = boost::interprocess::allocator<char, manager_t>;
    
    using string_t = boost::interprocess::basic_string<char, std::char_traits<char>, char_allocator_t>;
    
    using value_allocator_t = boost::interprocess::allocator<std::pair<const string_t, string_t>, manager_t>;

    using map_t = boost::interprocess::map<string_t, string_t, std::less<string_t>, value_allocator_t>;

    class BoostInterprocessCache
    {
    public:
        explicit BoostInterprocessCache(
            const std::string& name = UTILITIES.DEFAULT_BOOST_INTERPROCESS_CACHE,
            const BytesSize& size = BytesSize::KB_4
        );

        void setup(
            Result<void>& result,
            const std::string& name = UTILITIES.DEFAULT_BOOST_INTERPROCESS_CACHE,
            const BytesSize& size = BytesSize::KB_4
        );

        void clear(
            Result<void>& result
        );
        
        bool is_key_found(
            const char* key
        );

        void remove(
            const char* key,
            Result<void>& result
        );

        void read(
            const char* key,
            Result<const char*>& result
        );
        
        void write(
            const char* key,
            const char* value, Result<void>& result
        );

        void remove_batch(
            const std::vector<const char*>& keys,
            Result<void>& result
        );

        void write_batch(
            const std::unordered_map<const char*, const char*>& items,
            Result<void>& result
        );

        void read_batch(
            const std::vector<const char*>& keys,
            std::unordered_map<const char*, const char*>& out,
            Result<void>& result
        );
        
        std::future<void> write_async(
            const char* key,
            const char* value, 
            Result<void>& result
        );

        std::future<void> read_async(
            const char* key,
            Result<const char*>& result
        );
        
        std::future<bool> is_key_found_async(
            const char* key
        );
        
        std::future<void> remove_async(
            const char* key,
            Result<void>& result
        );
        
        std::future<void> clear_async(
            Result<void>& result
        );
        
        std::future<void> write_batch_async(
            const std::unordered_map<const char*, const char*>& items,
            Result<void>& result
        );
        
        std::future<void> read_batch_async(
            const std::vector<const char*>& keys,
            std::unordered_map<const char*, const char*>& out,
            Result<void>& result
        );
        
        std::future<void> remove_batch_async(
            const std::vector<const char*>& keys,
            Result<void>& result
        );
    
    private:
        segment_t _segment;

        BoostInterprocessCacheSharedData* _data = nullptr;
    };
}
