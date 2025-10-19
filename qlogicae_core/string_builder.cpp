#include "pch.hpp"

#include "string_builder.hpp"

namespace QLogicaeCore
{
    StringBuilder::StringBuilder(
        std::pmr::memory_resource* memory_resource_reference,
        ThreadPool* thread_pool_reference)
        : memory_resource_pointer(memory_resource_reference),
        thread_pool_pointer(thread_pool_reference)
    {
    }

    StringBuilder& StringBuilder::append(const std::string_view& text)
    {
        std::unique_lock lock(character_buffer_mutex);
        character_buffer_deque.insert(
            character_buffer_deque.end(),
            text.begin(),
            text.end());
        return *this;
    }

    StringBuilder& StringBuilder::append(const double& text)
    {
        return append(fmt::format("{}", text));
    }

    StringBuilder& StringBuilder::prepend(const std::string_view& text)
    {
        std::unique_lock lock(character_buffer_mutex);
        character_buffer_deque.insert(
            character_buffer_deque.begin(),
            text.begin(),
            text.end());
        return *this;
    }

    StringBuilder& StringBuilder::prepend(const double& text)
    {
        return prepend(fmt::format("{}", text));
    }

    StringBuilder& StringBuilder::insert(
        const std::string_view& text,
        const std::size_t& position)
    {
        std::unique_lock lock(character_buffer_mutex);
        std::size_t safe_position =
            std::min(position, character_buffer_deque.size());
        character_buffer_deque.insert(
            character_buffer_deque.begin() + safe_position,
            text.begin(),
            text.end());
        return *this;
    }

    StringBuilder& StringBuilder::insert(
        const double& text,
        const std::size_t& position)
    {
        return insert(fmt::format("{}", text), position);
    }

    StringBuilder& StringBuilder::clear()
    {
        std::unique_lock lock(character_buffer_mutex);
        character_buffer_deque.clear();
        return *this;
    }

    bool StringBuilder::is_empty()
    {
        std::shared_lock lock(character_buffer_mutex);
        return character_buffer_deque.empty();
    }

    std::size_t StringBuilder::get_size()
    {
        std::shared_lock lock(character_buffer_mutex);
        return character_buffer_deque.size();
    }

    StringBuilder& StringBuilder::reserve_capacity(const std::size_t& value)
    {
        std::unique_lock lock(character_buffer_mutex);
        std::deque<char> temp;
        temp.insert(temp.end(), character_buffer_deque.begin(),
            character_buffer_deque.end());
        character_buffer_deque.swap(temp);
        return *this;
    }

    StringBuilder& StringBuilder::shrink_to_fit()
    {
        std::unique_lock lock(character_buffer_mutex);
        std::deque<char> temp(character_buffer_deque.begin(),
            character_buffer_deque.end());
        character_buffer_deque.swap(temp);
        return *this;
    }

    StringBuilder& StringBuilder::left_trim()
    {
        return _utf8_trim(true, false);
    }

    StringBuilder& StringBuilder::right_trim()
    {
        return _utf8_trim(false, true);
    }

    StringBuilder& StringBuilder::left_and_right_trim()
    {
        return _utf8_trim(true, true);
    }

    std::pmr::string StringBuilder::_flatten(
        std::pmr::memory_resource* memory_resource_reference)
    {
        std::shared_lock lock(character_buffer_mutex);
        std::pmr::memory_resource* resource =
            memory_resource_reference ?
                memory_resource_reference : memory_resource_pointer;
        return std::pmr::string(
            character_buffer_deque.begin(),
            character_buffer_deque.end(),
            resource);
    }

    StringBuilder& StringBuilder::_utf8_trim(
        bool trim_left, bool trim_right)
    {
        std::unique_lock lock(character_buffer_mutex);

        auto is_unicode_space = [](const char* pointer) -> bool
            {
                utf8proc_int32_t codepoint;
                utf8proc_ssize_t result = utf8proc_iterate(
                    reinterpret_cast<const unsigned char*>(pointer),
                    -1, &codepoint);
                if (result < 1)
                {
                    return false;
                }
                return utf8proc_category(codepoint) ==
                    UTF8PROC_CATEGORY_ZS;
            };

        auto begin = character_buffer_deque.begin();
        auto end = character_buffer_deque.end();

        if (trim_left)
        {
            while (begin < end && is_unicode_space(&(*begin)))
            {
                ++begin;
            }
        }

        if (trim_right)
        {
            while (begin < end && is_unicode_space(&(*(end - 1))))
            {
                --end;
            }
        }

        std::deque<char> trimmed(begin, end);
        character_buffer_deque.swap(trimmed);

        return *this;
    }

    const std::pmr::string& StringBuilder::to_pmr_string()
    {
        thread_local std::pmr::string temporary(memory_resource_pointer);
        temporary = _flatten();
        return temporary;
    }

    std::pmr::string StringBuilder::take_pmr_string()
    {
        std::unique_lock lock(character_buffer_mutex);
        std::pmr::string result(
            character_buffer_deque.begin(),
            character_buffer_deque.end(),
            memory_resource_pointer);
        character_buffer_deque.clear();
        return result;
    }

    std::string StringBuilder::take_string()
    {
        std::unique_lock lock(character_buffer_mutex);
        std::string result(
            character_buffer_deque.begin(),
            character_buffer_deque.end());
        character_buffer_deque.clear();
        return result;
    }


    const std::string& StringBuilder::to_string()
    {
        thread_local std::string temporary;
        std::shared_lock lock(character_buffer_mutex);
        temporary.assign(
            character_buffer_deque.begin(),
            character_buffer_deque.end());
        return temporary;
    }

    std::future<std::pmr::string> StringBuilder::async_to_pmr_string()
    {
        return std::async(std::launch::async, [this]() -> std::pmr::string
            {
                return _flatten();
            });
    }

    std::future<std::pmr::string> StringBuilder::async_take_pmr_string()
    {
        return std::async(std::launch::async, [this]() -> std::pmr::string
            {
                return take_pmr_string();
            });
    }

    std::future<std::string> StringBuilder::async_to_string()
    {
        return std::async(std::launch::async, [this]() -> std::string
            {
                std::shared_lock lock(character_buffer_mutex);
                return std::string(
                    character_buffer_deque.begin(),
                    character_buffer_deque.end());
            });
    }

    std::future<std::string> StringBuilder::async_take_string()
    {
        return std::async(std::launch::async, [this]() -> std::string
            {
                return take_string();
            });
    }

    std::future<void> StringBuilder::async_append(
        const std::string_view& text)
    {
        return std::async(std::launch::async, [this, text]()
            {
                append(text);
            });
    }

    std::future<void> StringBuilder::async_prepend(
        const std::string_view& text)
    {
        return std::async(std::launch::async, [this, text]()
            {
                prepend(text);
            });
    }

    std::future<void> StringBuilder::async_insert(
        const std::string_view& text, const std::size_t& position)
    {
        return std::async(std::launch::async, [this, text, position]()
            {
                insert(text, position);
            });
    }

    std::future<void> StringBuilder::async_append(
        const double& text)
    {
        return std::async(std::launch::async, [this, text]()
            {
                append(text);
            });
    }

    std::future<void> StringBuilder::async_prepend(
        const double& text)
    {
        return std::async(std::launch::async, [this, text]()
            {
                prepend(text);
            });
    }

    std::future<void> StringBuilder::async_insert(
        const double& text, const std::size_t& position)
    {
        return std::async(std::launch::async, [this, text, position]()
            {
                insert(text, position);
            });
    }

    std::future<void> StringBuilder::async_clear()
    {
        return std::async(std::launch::async, [this]()
            {
                clear();
            });
    }

    void StringBuilder::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }
}

