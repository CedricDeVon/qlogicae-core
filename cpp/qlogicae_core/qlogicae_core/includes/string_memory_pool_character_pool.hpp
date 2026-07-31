#pragma once

#include "utilities.hpp"
#include "string_memory_pool_character_pool_block.hpp"

#include <array>           
#include <mutex>           
#include <vector>          
#include <string>          
#include <memory>          
#include <cstddef>         
#include <iostream>        
#include <shared_mutex>    
#include <unordered_set>   

namespace QLogicaeCore
{
    class CharacterPool
    {
    public:
        explicit CharacterPool(
            const std::size_t& block_size = 4096
        );

        ~CharacterPool();

        CharacterPool(
            const CharacterPool&
        ) = delete;

        CharacterPool& operator = (
            const CharacterPool&
        ) = delete;

        void clear();

        char* allocate(
            const std::size_t& size
        );

        std::future<void> clear_async();

        std::future<char*> allocate_async(
            const std::size_t& size
        );

    private:
        char* _current;
        
        std::size_t _remaining;
        
        std::size_t _block_size;

        std::vector<CharacterPoolBlock*> _blocks;

        void allocate_block(
            const std::size_t& minimum_size
        );
    };
}
