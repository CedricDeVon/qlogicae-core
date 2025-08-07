#pragma once

#include "pch.h"

#include "encoder.hpp"

namespace QLogicaeCore
{
    class WindowsRegistry
    {
    public:
        std::unordered_map<std::string, std::string> get_values_via_utf8(std::string_view) const;
        std::unordered_map<std::string, std::wstring> get_values_via_utf16(std::wstring_view) const;
        
        bool remove_value_via_utf8(std::string_view, std::string_view) const;
        bool remove_value_via_utf16(std::wstring_view, std::wstring_view) const;
        bool set_sub_and_name_keys_via_utf8(const std::string_view, const std::string_view);
        bool set_sub_and_name_keys_via_utf16(const std::wstring_view, const std::wstring_view);
        bool is_sub_and_name_key_path_found_via_utf8(std::string_view, std::string_view) const;
        std::optional<std::string> get_value_via_utf8(std::string_view, std::string_view) const;
        bool is_sub_and_name_key_path_found_via_utf16(std::wstring_view, std::wstring_view) const;
        bool set_value_via_utf8(std::string_view, std::string_view, const std::string_view) const;
        std::optional<std::wstring> get_value_via_utf16(std::wstring_view, std::wstring_view) const;
        bool set_value_via_utf16(std::wstring_view, std::wstring_view, const std::wstring_view) const;

        static WindowsRegistry& hkcu();
        static WindowsRegistry& hklm();

    protected:
        HKEY _root_key;
        std::wstring _sub_key;
        std::wstring _name_key;

        ~WindowsRegistry() = default;
        WindowsRegistry(const WindowsRegistry&) = delete;
        WindowsRegistry(WindowsRegistry&&) noexcept = delete;
        WindowsRegistry(const HKEY = Constants::DEFAULT_HKEY);
        WindowsRegistry& operator = (WindowsRegistry&&) = delete;
        WindowsRegistry& operator = (const WindowsRegistry&) = delete;
    };
}
