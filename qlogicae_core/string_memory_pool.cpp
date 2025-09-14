#include "pch.h"

#include "string_memory_pool.hpp"

namespace QLogicaeCore {
    CharacterPool::CharacterPool(const std::size_t& block_size)
        : _current(nullptr),
        _remaining(0),
        _block_size(block_size)
    {

    }

    CharacterPool::~CharacterPool()
    {
        clear();
    }

    void CharacterPool::clear()
    {
        try
        {
            for (auto* block : _blocks)
            {
                delete block;
            }
            _blocks.clear();
            _current = nullptr;
            _remaining = 0;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CharacterPool::clear(): " + exception.what());
        }
    }

    void CharacterPool::allocate_block(const std::size_t& minimum_size)
    {
        try
        {
            std::size_t size = std::max(minimum_size, _block_size);
            CharacterPoolBlock* block = new CharacterPoolBlock(size);
            _blocks.push_back(block);
            _current = block->data.get();
            _remaining = size;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CharacterPool::allocate_block(): " + exception.what());
        }
    }

    char* CharacterPool::allocate(const std::size_t& size)
    {
        try
        {
            if (size == 0)
            {
                return nullptr;
            }            
            
            if (size > _remaining)
            {
                allocate_block(size);
            }

            char* result = _current;
            _current += size;
            _remaining -= size;

            return result;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CharacterPool::allocate(): " + exception.what());
        }
    }

    std::future<void> CharacterPool::clear_async()
    {
        return std::async(std::launch::async, [this]() { this->clear(); });
    }

    std::future<char*> CharacterPool::allocate_async(const std::size_t& size)
    {
        return std::async(std::launch::async, [this, size]() { return this->allocate(size); });
    }

    template<typename Allocator>
    StringMemoryPool<Allocator>::StringMemoryPool(
        CaseSensitivity sensitivity,
        std::size_t character_pool_block_size,
        std::pmr::memory_resource* resource
    )
        : _data(0, CaseAwareHash(sensitivity), CaseAwareEqual(sensitivity), Allocator(resource)),
            _allocator(resource),
            _character_pool(character_pool_block_size),
            _sensitivity(sensitivity)
    {

    }

    template<typename Allocator>
    std::size_t StringMemoryPool<Allocator>::get_size() const
    {
        std::shared_lock lock(_mutex);

        return _data.size();
    }

    template<typename Allocator>
    const StringMemoryPoolDiagnostics& StringMemoryPool<Allocator>::get_diagnostics() const
    {
        return _diagnostics;
    }

    template<typename Allocator>
    bool StringMemoryPool<Allocator>::is_found(const std::string_view& str) const
    {
        std::shared_lock lock(_mutex);

        return _data.find(str) != _data.end() || _data.find(std::string(str)) != _data.end();
    }

    template<typename Allocator>
    void StringMemoryPool<Allocator>::clear()
    {
        try
        {
            std::unique_lock lock(_mutex);

            _data.clear();
            _character_pool.clear();
            _diagnostics.reset();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at StringMemoryPool<Allocator>::clear(): " + exception.what());
        }
    }

    template<typename Allocator>
    const std::string* StringMemoryPool<Allocator>::get_internal(const std::string_view& string)
    {
        try
        {
            {
                std::shared_lock lock(_mutex);
                auto it = _data.find(string);
                if (it != _data.end()) {
                    ++_diagnostics.pool_hits;
                    return &(*it);
                }
            }

            std::unique_lock lock(_mutex);
            auto it = _data.find(string);
            if (it != _data.end()) {
                ++_diagnostics.pool_hits;
                return &(*it);
            }

            char* mem = _character_pool.allocate(string.size() + 1);
            std::memcpy(mem, string.data(), string.size());
            mem[string.size()] = '\0';

            std::string pooled(mem, string.size());
            auto [inserted, ok] = _data.emplace(std::move(pooled));

            ++_diagnostics.pool_misses;
            _diagnostics.interned_count = _data.size();
            _diagnostics.bytes_used += string.size() + 1;

            return &(*inserted);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at StringMemoryPool<Allocator>::get_internal(): " + exception.what());
        }
    }

    template<typename Allocator>
    StringMemoryPoolSnapshot StringMemoryPool<Allocator>::get_diagnostics_snapshot() const
    {
        try
        {
            return StringMemoryPoolSnapshot{
                _diagnostics.pool_hits.load(),
                _diagnostics.bytes_used.load(),
                _diagnostics.pool_misses.load(),
                _diagnostics.interned_count.load()
            };
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at StringMemoryPool<Allocator>::get_diagnostics_snapshot()(): " + exception.what());
        }
    }

    template<typename Allocator>
    std::future<std::size_t> StringMemoryPool<Allocator>::get_size_async() const
    {
        return std::async(std::launch::async, [this]() { return get_size(); });
    }

    template<typename Allocator>
    std::future<StringMemoryPoolSnapshot> StringMemoryPool<Allocator>::get_diagnostics_async() const
    {
        return std::async(std::launch::async, [this]()
            {
                return this->get_diagnostics_snapshot();
            });
    }

    template<typename Allocator>
    std::future<bool> StringMemoryPool<Allocator>::is_found_async(const std::string_view& string) const
    {
        return std::async(std::launch::async, [this, string]() { return is_found(string); });
    }

    template<typename Allocator>
    std::future<void> StringMemoryPool<Allocator>::clear_async()
    {
        return std::async(std::launch::async, [this]() { clear(); });
    }

    template<typename Allocator>
    std::future<const std::string*> StringMemoryPool<Allocator>::get_internal_async(const std::string_view& string)
    {
        return std::async(std::launch::async, [this, string]() { return get_internal(string); });
    }

    template class StringMemoryPool<std::pmr::polymorphic_allocator<std::string>>;
}
