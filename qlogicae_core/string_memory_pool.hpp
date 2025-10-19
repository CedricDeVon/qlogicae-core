#pragma once

#include "utilities.hpp"
#include "case_aware_hash.hpp"
#include "case_aware_equal.hpp"
#include "case_sensitivity.hpp"
#include "string_memory_pool_snapshot.hpp"
#include "string_memory_pool_diagnostics.hpp"
#include "string_memory_pool_character_pool.hpp"
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
    template<typename Allocator =
        std::pmr::polymorphic_allocator<std::string>>
    class StringMemoryPool
    {
    public:
        StringMemoryPool(
            CaseSensitivity sensitivity =
                CaseSensitivity::SENSITIVE,
            std::size_t character_pool_block_size =
                4096,
            std::pmr::memory_resource* resource =
                std::pmr::get_default_resource()
        );

        std::size_t get_size();
        
        const StringMemoryPoolDiagnostics& get_diagnostics();
        
        StringMemoryPoolSnapshot get_diagnostics_snapshot();
        
        bool is_found(
            const std::string_view& string
        );
        
        void clear();
        
        const std::string* get_internal(
            const std::string_view& string
        );

        std::future<std::size_t> get_size_async();
        
        std::future<StringMemoryPoolSnapshot> get_diagnostics_async();
        
        std::future<bool> is_found_async(
            const std::string_view& string
        );
        
        std::future<void> clear_async();
        
        std::future<const std::string*> get_internal_async(
            const std::string_view& string
        );

    private:
        std::unordered_set<
            std::string,
            CaseAwareHash,
            CaseAwareEqual,
            Allocator
        > _data;

        Allocator _allocator;
        
        CaseSensitivity _sensitivity;
        
        CharacterPool _character_pool;
        
        mutable std::shared_mutex _mutex;

        StringMemoryPoolDiagnostics _diagnostics;
    };
}
