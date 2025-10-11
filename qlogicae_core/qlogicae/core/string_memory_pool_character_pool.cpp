#include "pch.hpp"

#include "string_memory_pool_character_pool.hpp"

namespace QLogicaeCore
{
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
}
