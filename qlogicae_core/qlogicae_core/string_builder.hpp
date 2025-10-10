#pragma once

#include "thread_pool.hpp"

#include <string>
#include <vector>
#include <string_view>
#include <memory_resource>

namespace QLogicaeCore
{
    inline thread_local std::array<std::byte, 4096> default_pool_buffer;
    inline thread_local std::pmr::monotonic_buffer_resource
        default_fallback_pool{
            default_pool_buffer.data(),
            default_pool_buffer.size(),
            std::pmr::get_default_resource()
    };

    class StringBuilder
    {
    public:
        StringBuilder(
            std::pmr::memory_resource* memory_resource_reference =
                &default_fallback_pool,
            ThreadPool* thread_pool_reference = nullptr
        );

        bool is_empty() const;
        
        StringBuilder& clear();
        
        std::string take_string();
        
        StringBuilder& left_trim();
        
        StringBuilder& right_trim();
        
        std::size_t get_size() const;        

        StringBuilder& shrink_to_fit();
        
        std::pmr::string take_pmr_string();
        
        StringBuilder& left_and_right_trim();
        
        const std::string& to_string() const;
        
        const std::pmr::string& to_pmr_string() const;
        
        StringBuilder& append(const double& text);
        
        StringBuilder& append(const std::string_view& text);
        
        StringBuilder& prepend(const double& text);
        
        StringBuilder& prepend(const std::string_view& text);
        
        StringBuilder& reserve_capacity(const std::size_t& value);
        
        StringBuilder& insert(
            const double& text,
            const std::size_t& position
        );
        
        StringBuilder& insert(
            const std::string_view& text,
            const std::size_t& position
        );

        std::future<void> async_clear();
        
        std::future<std::string> async_take_string();
        
        std::future<std::string> async_to_string() const;
        
        std::future<std::pmr::string> async_take_pmr_string();
        
        std::future<std::pmr::string> async_to_pmr_string() const;
        
        std::future<void> async_append(const double& text);
        
        std::future<void> async_append(const std::string_view& text);
        
        std::future<void> async_prepend(const double& text);
        
        std::future<void> async_prepend(const std::string_view& text);
        
        std::future<void> async_insert(
            const double& text,
            const std::size_t& position
        );
        
        std::future<void> async_insert(
            const std::string_view& text,
            const std::size_t& position
        );

    protected:
        ThreadPool* thread_pool_pointer;
        std::deque<char> character_buffer_deque;
        mutable std::shared_mutex character_buffer_mutex;
        std::pmr::memory_resource* memory_resource_pointer;
        
        StringBuilder& _utf8_trim(bool trim_left, bool trim_right);        
        
        std::pmr::string _flatten(
            std::pmr::memory_resource* memory_resource_reference = nullptr
        ) const;
    };
}
