#pragma once

#include "result.hpp"
#include "encoder.hpp"
#include "utilities.hpp"
#include "value_enum_key_delete_handler.hpp"

#include <windows.h>

namespace QLogicaeCore
{
    class WindowsRegistry
    {
    public:
        std::unordered_map<std::string, std::string>
            get_values_via_utf8(
                std::string_view value
        ) const;
        
        std::unordered_map<std::string, std::wstring>
            get_values_via_utf16(
                std::wstring_view value
        ) const;
        
        bool remove_value_via_utf8(
            std::string_view sub_path,
            std::string_view name
        ) const;
        
        bool remove_value_via_utf16(
            std::wstring_view sub_path,
            std::wstring_view name
        ) const;
        
        bool set_sub_and_name_keys_via_utf8(
            const std::string_view sub_path,
            const std::string_view name
        );
        
        bool set_sub_and_name_keys_via_utf16(
            const std::wstring_view sub_path,
            const std::wstring_view name
        );
        
        bool is_sub_and_name_key_path_found_via_utf8(
            std::string_view sub_path,
            std::string_view name
        ) const;
        
        std::optional<std::string> get_value_via_utf8(
            std::string_view sub_path,
            std::string_view name
        ) const;
        
        bool is_sub_and_name_key_path_found_via_utf16(
            std::wstring_view sub_path,
            std::wstring_view name
        ) const;
        
        bool set_value_via_utf8(
            std::string_view sub_path,
            std::string_view name,
            const std::string_view value
        ) const;
        
        std::optional<std::wstring> get_value_via_utf16(
            std::wstring_view sub_path,
            std::wstring_view name
        ) const;
        
        bool set_value_via_utf16(
            std::wstring_view sub_path,
            std::wstring_view name,
            const std::wstring_view value
        ) const;

        void get_values_via_utf8(
            Result<std::unordered_map<std::string, std::string>>& result,
            const std::string_view value
        ) const;

        void get_values_via_utf16(
            Result<std::unordered_map<std::string, std::wstring>>& result,
            const std::wstring_view value
        ) const;

        void remove_value_via_utf8(
            Result<void>& result,
            const std::string_view sub_path,
            const std::string_view name
        ) const;

        void remove_value_via_utf16(
            Result<void>& result,
            const std::wstring_view sub_path,
            const std::wstring_view name
        ) const;

        void set_sub_and_name_keys_via_utf8(
            Result<void>& result,
            const std::string_view sub_path,
            const std::string_view name
        );

        void set_sub_and_name_keys_via_utf16(
            Result<void>& result,
            const std::wstring_view sub_path,
            const std::wstring_view name
        );

        void is_sub_and_name_key_path_found_via_utf8(
            Result<bool>& result,
            const std::string_view sub_path,
            const std::string_view name
        ) const;

        void get_value_via_utf8(
            Result<std::optional<std::string>>& result,
            const std::string_view sub_path,
            const std::string_view name
        ) const;

        void is_sub_and_name_key_path_found_via_utf16(
            Result<bool>& result,
            const std::wstring_view sub_path,
            const std::wstring_view name
        ) const;

        void set_value_via_utf8(
            Result<void>& result,
            const std::string_view sub_path,
            const std::string_view name,
            const std::string_view value
        ) const;

        void get_value_via_utf16(
            Result<std::optional<std::wstring>>& result,
            const std::wstring_view sub_path,
            const std::wstring_view name
        ) const;

        void set_value_via_utf16(
            Result<void>& result,
            const std::wstring_view sub_path,
            const std::wstring_view name,
            const std::wstring_view value
        ) const;

        void setup(
            Result<void>& result,
            const HKEY hkey = UTILITIES.DEFAULT_HKEY
        );

        static WindowsRegistry& hkcu();

        static WindowsRegistry& hklm();

    protected:
        ~WindowsRegistry() = default;
        
        WindowsRegistry(
            const WindowsRegistry& windows_registry
        ) = delete;
        
        WindowsRegistry(
            WindowsRegistry&& windows_registry
        ) noexcept = delete;
        
        WindowsRegistry(
            const HKEY hkey = UTILITIES.DEFAULT_HKEY
        );
        
        WindowsRegistry& operator = 
            (WindowsRegistry&& windows_registry
        ) = delete;
        
        WindowsRegistry& operator = (
            const WindowsRegistry& windows_registry
        ) = delete;

        HKEY _root_key;

        std::wstring _sub_key;

        std::wstring _name_key;
    };
}

