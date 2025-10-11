#pragma once

#include "utilities.hpp"

namespace QLogicaeCore
{

    class CharacterPool
    {
    public:
        explicit CharacterPool(const std::size_t& block_size = 4096);
        
        ~CharacterPool();

        CharacterPool(const CharacterPool&) = delete;
        
        CharacterPool& operator=(const CharacterPool&) = delete;

        void clear();
        
        char* allocate(const std::size_t& size);

        std::future<void> clear_async();
        
        std::future<char*> allocate_async(const std::size_t& size);

    private:
        struct CharacterPoolBlock
        {
            std::unique_ptr<char[]> data;
            std::size_t size;
            CharacterPoolBlock* next;

            explicit CharacterPoolBlock(std::size_t sz)
                : data(new char[sz]), size(sz), next(nullptr) {
            }
        };

        char* _current;
        std::size_t _remaining;
        std::size_t _block_size;
        std::vector<CharacterPoolBlock*> _blocks;

        void allocate_block(const std::size_t& minimum_size);
    };

    class StringMemoryPoolDiagnostics
    {
    public:
        StringMemoryPoolDiagnostics() = default;
        
        StringMemoryPoolDiagnostics(const StringMemoryPoolDiagnostics&) = delete;
        
        StringMemoryPoolDiagnostics& operator=(const StringMemoryPoolDiagnostics&) = delete;

        std::atomic<std::size_t> pool_hits{ 0 };
        std::atomic<std::size_t> bytes_used{ 0 };
        std::atomic<std::size_t> pool_misses{ 0 };
        std::atomic<std::size_t> interned_count{ 0 };
        
        void reset() {
            pool_hits = 0;
            pool_misses = 0;
            interned_count = 0;
            bytes_used = 0;
        }
    };

    template<typename Allocator = std::pmr::polymorphic_allocator<std::string>>
    class StringMemoryPool
    {
    public:
        StringMemoryPool(
            CaseSensitivity sensitivity = CaseSensitivity::SENSITIVE,
            std::size_t character_pool_block_size = 4096,
            std::pmr::memory_resource* resource = std::pmr::get_default_resource()
        );

        std::size_t get_size() const;
        
        const StringMemoryPoolDiagnostics& get_diagnostics() const;
        
        StringMemoryPoolSnapshot get_diagnostics_snapshot() const;
        
        bool is_found(const std::string_view& string) const;
        
        void clear();
        
        const std::string* get_internal(const std::string_view& string);

        std::future<std::size_t> get_size_async() const;
        
        std::future<StringMemoryPoolSnapshot> get_diagnostics_async() const;
        
        std::future<bool> is_found_async(const std::string_view& string) const;
        
        std::future<void> clear_async();
        
        std::future<const std::string*> get_internal_async(const std::string_view& string);

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

