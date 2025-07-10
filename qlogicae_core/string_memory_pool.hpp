#pragma once

#include "pch.h"

namespace QLogicaeCore
{

    enum class CaseSensitivity {
        SENSITIVE,
        INSENSITIVE
    };

    struct CaseAwareHash {
        using is_transparent = void;

        CaseSensitivity sensitivity;

        explicit CaseAwareHash(CaseSensitivity s) : sensitivity(s) {}

        std::size_t operator()(const std::string& s) const noexcept { return hash_impl(s); }
        std::size_t operator()(const std::string_view& sv) const noexcept { return hash_impl(sv); }

    private:
        std::size_t hash_impl(std::string_view str) const noexcept {
            std::size_t hash = 14695981039346656037ull;
            for (char c : str) {
                char x = (sensitivity == CaseSensitivity::SENSITIVE)
                    ? c
                    : static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                hash = (hash ^ static_cast<unsigned char>(x)) * 1099511628211ull;
            }
            return hash;
        }
    };

    struct CaseAwareEqual {
        using is_transparent = void;

        CaseSensitivity sensitivity;

        explicit CaseAwareEqual(CaseSensitivity s) : sensitivity(s) {}

        bool operator()(const std::string& a, const std::string& b) const noexcept {
            return compare_impl(a, b);
        }

        bool operator()(const std::string_view& a, const std::string_view& b) const noexcept {
            return compare_impl(a, b);
        }

        bool operator()(const std::string& a, const std::string_view& b) const noexcept {
            return compare_impl(a, b);
        }

        bool operator()(const std::string_view& a, const std::string& b) const noexcept {
            return compare_impl(a, b);
        }

    private:
        bool compare_impl(std::string_view a, std::string_view b) const noexcept {
            if (a.size() != b.size()) return false;
            if (sensitivity == CaseSensitivity::SENSITIVE) return a == b;
            for (size_t i = 0; i < a.size(); ++i) {
                if (std::tolower(static_cast<unsigned char>(a[i])) !=
                    std::tolower(static_cast<unsigned char>(b[i])))
                    return false;
            }
            return true;
        }
    };

    class CharacterPool {
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
        struct CharacterPoolBlock {
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

    struct StringMemoryPoolSnapshot {
        std::size_t pool_hits = 0;
        std::size_t bytes_used = 0;
        std::size_t pool_misses = 0;
        std::size_t interned_count = 0;
    };

    class StringMemoryPoolDiagnostics {
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
    class StringMemoryPool {
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
        CharacterPool _character_pool;
        CaseSensitivity _sensitivity;
        mutable std::shared_mutex _mutex;
        StringMemoryPoolDiagnostics _diagnostics;
    };
}
