#pragma once

#include "pch.h"

#include "thread_pool.hpp"

namespace QLogicaeCore
{
    inline std::pmr::monotonic_buffer_resource default_string_pool;

    class StringBuilder
    {
    public:
        explicit StringBuilder(std::pmr::memory_resource* resource = &default_string_pool,
            ThreadPool* thread_pool = nullptr);

        template <typename... argument_types>
        static std::string format_string(fmt::format_string<argument_types...> fmt_str,
            argument_types&&... args)
        {
            return fmt::format(fmt_str, std::forward<argument_types>(args)...);
        }

        StringBuilder& append(const std::string_view& text);
        StringBuilder& append(const std::wstring_view& text);
        StringBuilder& append(const std::u8string_view& text);

        StringBuilder& prepend(const std::string_view& text);
        StringBuilder& prepend(const std::wstring_view& text);
        StringBuilder& prepend(const std::u8string_view& text);

        StringBuilder& insert(const std::size_t& position, const std::string_view& text);
        StringBuilder& insert(const std::size_t& position, const std::wstring_view& text);
        StringBuilder& insert(const std::size_t& position, const std::u8string_view& text);

        template <typename... argument_types>
        StringBuilder& append_formatted(const std::string_view& fmt_str,
            argument_types&&... args);

        template <typename... argument_types>
        StringBuilder& prepend_formatted(const std::string_view& fmt_str,
            argument_types&&... args);

        template <typename... argument_types>
        StringBuilder& insert_formatted(const std::size_t& position,
            const std::string_view& fmt_str,
            argument_types&&... args);

        StringBuilder& clear();
        bool is_empty() const;
        std::size_t get_size() const;
        StringBuilder& reserve_capacity(const std::size_t& capacity);

        StringBuilder& trim();
        StringBuilder& left_trim();
        StringBuilder& right_trim();

        template <typename text_range>
        StringBuilder& append_multiple(const text_range& items);

        template <typename text_range>
        StringBuilder& append_formatted_multiple(const std::string_view& fmt_str,
            const text_range& items);

        template <typename text_range>
        StringBuilder& join(const std::string_view& delimiter,
            const text_range& items);

        template <typename text_range>
        StringBuilder& join_formatted(const std::string_view& delimiter,
            const text_range& items,
            const std::string_view& fmt_str);

        template <typename text_range>
        StringBuilder& join_formatted_indexed(const std::string_view& delimiter,
            const text_range& items,
            const std::string_view& fmt_str);

        template <typename text_range>
        void enqueue_batch(const text_range& items);

        const std::pmr::string& to_string() const;
        std::pmr::string&& take_string();

        std::future<std::pmr::string> async_to_string() const;
        std::future<std::pmr::string> async_take_string();
        std::future<void> async_append(const std::string_view& text);

        template <typename... argument_types>
        std::future<void> async_append_formatted(const std::string_view& fmt_str,
            argument_types&&... args);

        std::future<void> async_clear();

    protected:
        std::pmr::string _character_buffer;
        std::pmr::memory_resource* _memory_resource;
        mutable std::shared_mutex _mutex;
        ThreadPool* _thread_pool;
    };
}
