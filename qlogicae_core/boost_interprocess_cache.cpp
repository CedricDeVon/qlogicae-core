#include "pch.hpp"

#include "boost_interprocess_cache.hpp"

namespace QLogicaeCore
{
    BoostInterprocessCache::BoostInterprocessCache(
            const std::string& name,
            const BytesSize& size_in_bytes
    )
        : _segment(
            boost::interprocess::open_or_create,
            name.c_str(),
            static_cast<std::size_t>(size_in_bytes)
        )
    {
        boost::interprocess::shared_memory_object::remove(name.c_str());
        _data = _segment.find_or_construct<BoostInterprocessCacheSharedData>(
            UTILITIES.DEFAULT_BOOST_INTERPROCESS_CACHE_SEGMENT_NAME.c_str())(
                value_allocator_t(_segment.get_segment_manager()));
    }

    void BoostInterprocessCache::setup(
        Result<void>& result,
        const std::string& name,
        const BytesSize& size_in_bytes
    )
    {
        _segment = segment_t(
            boost::interprocess::open_or_create,
            name.c_str(),
            static_cast<std::size_t>(size_in_bytes)
        );void setup(
            Result<void>& result,
            const std::string& name,
            const BytesSize& size_in_bytes
        );

        boost::interprocess::shared_memory_object::remove(name.c_str());
        _data = _segment.find_or_construct<BoostInterprocessCacheSharedData>(
            UTILITIES.DEFAULT_BOOST_INTERPROCESS_CACHE_SEGMENT_NAME.c_str())(
                value_allocator_t(_segment.get_segment_manager()));
    }

    void BoostInterprocessCache::write(
        const char* key,
        const char* value,
        Result<void>& result
    )
    {
        boost::interprocess::scoped_lock lock(_data->_mutex);
        string_t shm_key(key, _segment.get_segment_manager());
        string_t shm_value(value, _segment.get_segment_manager());

        auto iterative = _data->map.find(shm_key);
        if (iterative != _data->map.end())
        {
            iterative->second.assign(
                shm_value.c_str(),
                shm_value.size()
            );
        }
        else
        {
            _data->map.emplace(
                std::move(shm_key),
                std::move(shm_value)
            );
        }

        result.set_to_success();
    }

    std::future<void> BoostInterprocessCache::write_async(
        const char* key,
        const char* value,
        Result<void>& result
    )
    {
        return std::async(std::launch::async, [this, key, value, &result]()
            {
                write(key, value, result);
            }
        );
    }

    void BoostInterprocessCache::read(
        const char* key,
        Result<const char*>& result
    )
    {
        boost::interprocess::scoped_lock lock(_data->_mutex);
    
        auto iterative = _data->map.find(
            string_t(key, _segment.get_segment_manager())
        );
        if (iterative != _data->map.end())
        {
            result.set_to_success(iterative->second.c_str());
        }
        else
        {
            result.set_to_failure();
        }
    }

    std::future<void> BoostInterprocessCache::read_async(
        const char* key,
        Result<const char*>& result
    )
    {
        return std::async(std::launch::async, [this, key, &result]()
            {
                read(key, result);
            }
        );
    }

    bool BoostInterprocessCache::is_key_found(const char* key)
    {
        boost::interprocess::scoped_lock lock(_data->_mutex);

        return _data->map.find(
            string_t(key, _segment.get_segment_manager())
        ) != _data->map.end();
    }

    std::future<bool> BoostInterprocessCache::is_key_found_async(
        const char* key
    )
    {
        return std::async(std::launch::async, [this, key]()
            {
                return is_key_found(key);
            }
        );
    }

    void BoostInterprocessCache::remove(
        const char* key,
        Result<void>& result
    )
    {
        boost::interprocess::scoped_lock lock(_data->_mutex);
    
        auto count = _data->map.erase(
            string_t(key, _segment.get_segment_manager())
        );
        if (count > 0)
        {
            result.set_to_success();
        }
        else
        {
            result.set_to_failure();
        }
    }

    std::future<void> BoostInterprocessCache::remove_async(
        const char* key,
        Result<void>& result
    )
    {
        return std::async(std::launch::async, [this, key, &result]()
            {
                remove(key, result);
            }
        );
    }

    void BoostInterprocessCache::clear(Result<void>& result)
    {
        boost::interprocess::scoped_lock lock(_data->_mutex);
        
        _data->map.clear();
        result.set_to_success();
    }

    std::future<void> BoostInterprocessCache::clear_async(
        Result<void>& result
    )
    {
        return std::async(std::launch::async, [this, &result]()
            {
                clear(result);
            }
        );
    }

    void BoostInterprocessCache::write_batch(
        const std::unordered_map<const char*,const char*>& items,
        Result<void>& result
    )
    {
        std::vector<std::pair<string_t, string_t>> temporaries;
        temporaries.reserve(items.size());

        for (const auto& [key, value] : items)
        {
            temporaries.emplace_back(
                string_t(key, _segment.get_segment_manager()),
                string_t(value, _segment.get_segment_manager())
            );
        }

        {
            boost::interprocess::scoped_lock lock(_data->_mutex);
            for (auto& [shm_key, shm_value] : temporaries)
            {
                auto iterative = _data->map.find(shm_key);
                if (iterative != _data->map.end())
                {
                    iterative->second.assign(
                        shm_value.c_str(),
                        shm_value.size()
                    );
                }
                else
                {
                    _data->map.emplace(
                        std::move(shm_key),
                        std::move(shm_value)
                    );                    
                }
            }
        }

        result.set_to_success();
    }

    std::future<void> BoostInterprocessCache::write_batch_async(
        const std::unordered_map<const char*, const char*>& items,
        Result<void>& result
    )
    {
        return std::async(std::launch::async, [this, &items, &result]()
            {
                write_batch(items, result);
            }
        );
    }

    void BoostInterprocessCache::read_batch(
        const std::vector<const char*>& keys,
        std::unordered_map<const char*, const char*>& out,
        Result<void>& result
    )
    {
        boost::interprocess::scoped_lock lock(_data->_mutex);
        for (const auto& key : keys)
        {
            auto iterative = _data->map.find(
                    string_t(
                        key,
                        _segment.get_segment_manager()
                    )
            );
            if (iterative != _data->map.end())
            {
                out[key] = iterative->second.c_str();
            }
        }
        result.set_to_success();
    }

    std::future<void> BoostInterprocessCache::read_batch_async(
        const std::vector<const char*>& keys,
        std::unordered_map<const char*, const char*>& out,
        Result<void>& result
    )
    {
        return std::async(std::launch::async, [this, &keys, &out, &result]()
            {
                read_batch(keys, out, result);
            }
        );
    }

    void BoostInterprocessCache::remove_batch(
        const std::vector<const char*>& keys, Result<void>& result
    )
    {
        boost::interprocess::scoped_lock lock(_data->_mutex);
    
        for (const auto& key : keys)
        {
            _data->map.erase(
                string_t(
                    key,
                    _segment.get_segment_manager()
                )
            );
        }

        result.set_to_success();
    }

    std::future<void> BoostInterprocessCache::remove_batch_async(
        const std::vector<const char*>& keys,
        Result<void>& result
    )
    {
        return std::async(std::launch::async, [this, &keys, &result]()
            {
                remove_batch(keys, result);
            }
        );
    }
}

