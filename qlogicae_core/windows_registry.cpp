#include "pch.hpp"

#include "windows_registry.hpp"

namespace QLogicaeCore
{
    struct RegularKeyDeleteHandler
    {
        void operator() (HKEY handler)
        {
            if (handler)
            {
                RegCloseKey(handler);
            }
        }
    };

    WindowsRegistry::WindowsRegistry(
        const HKEY root_hkey
    )
    {
        Result<void> void_result;

        setup(void_result, root_hkey);
    }

    bool WindowsRegistry::setup(
        const HKEY hkey
    )
    {
        Result<void> void_result;

        setup(void_result, hkey);

        return void_result.is_status_safe();
    }

    WindowsRegistry& WindowsRegistry::hkcu()
    {
        static WindowsRegistry hkcu(HKEY_CURRENT_USER);

        return hkcu;
    }

    WindowsRegistry& WindowsRegistry::hklm()
    {
        static WindowsRegistry hklm(HKEY_LOCAL_MACHINE);

        return hklm;
    }

    bool WindowsRegistry::set_sub_and_name_keys_via_utf16(
        const std::wstring_view sub_key,
        const std::wstring_view name_key
    )
    {
        _sub_key.assign(sub_key);
        _name_key.assign(name_key);

        return true;
    }

    bool WindowsRegistry::set_sub_and_name_keys_via_utf8(
        const std::string_view sub_key,
        const std::string_view name_key
    )
    {
        return set_sub_and_name_keys_via_utf16(
            ENCODER.from_utf8_to_utf16(sub_key),
            ENCODER.from_utf8_to_utf16(name_key)
        );
    }

    std::optional<std::wstring> WindowsRegistry::get_value_via_utf16(
        std::wstring_view sub_key,
        std::wstring_view name_key
    )
    {
        sub_key = (sub_key.empty()) ? _sub_key : sub_key;
        name_key = (name_key.empty()) ? _name_key : name_key;

        HKEY raw_key = nullptr;
        if (RegOpenKeyExW(_root_key, sub_key.data(),
            0, UTILITIES.REGULAR_ACCESS_FLAGS, &raw_key) != ERROR_SUCCESS)
        {
            return L"";
        }

        DWORD hkey_value_type = 0, hkey_value_size = 0;
        std::unique_ptr<
            std::remove_pointer<HKEY>::type,
            RegularKeyDeleteHandler> hKey(raw_key);
        if (RegQueryValueExW(hKey.get(), name_key.empty() ?
            nullptr : name_key.data(), nullptr,
            &hkey_value_type, nullptr, &hkey_value_size) !=
            ERROR_SUCCESS || hkey_value_type != REG_SZ)
        {
            return L"";
        }

        if (hkey_value_size > UTILITIES.HKEY_MAXIMUM_VALUE_SIZE)
        {
            return L"";
        }

        std::vector<wchar_t> hkey_value_buffer(
            (hkey_value_size / sizeof(wchar_t)) + 1);
        if (!(RegQueryValueExW(hKey.get(), name_key.empty() ?
            nullptr : name_key.data(), nullptr, &hkey_value_type,
            reinterpret_cast<LPBYTE>(
                hkey_value_buffer.data()), &hkey_value_size) ==
            ERROR_SUCCESS && hkey_value_type == REG_SZ))
        {
            return L"";
        }

        hkey_value_buffer.back() = L'\0';

        return std::wstring(hkey_value_buffer.data());
    }

    std::optional<std::string> WindowsRegistry::get_value_via_utf8(
        std::string_view sub_key,
        std::string_view name_key)
    {
        return ENCODER.from_utf16_to_utf8(
            get_value_via_utf16(
                ENCODER.from_utf8_to_utf16(sub_key),
                ENCODER.from_utf8_to_utf16(name_key)
            ).value()
        );
    }

    bool WindowsRegistry::set_value_via_utf16(
        std::wstring_view sub_key,
        std::wstring_view name_key,
        const std::wstring_view value)
    {
        name_key = (name_key.empty()) ? _name_key : name_key;
        sub_key = (sub_key.empty()) ? _sub_key : sub_key;

        HKEY raw_key = nullptr;
        if (RegCreateKeyExW(_root_key, sub_key.data(), 0, nullptr, 0,
            KEY_SET_VALUE, nullptr, &raw_key, nullptr) != ERROR_SUCCESS)
        {
            return false;
        }
        std::unique_ptr<
            std::remove_pointer<HKEY>::type, RegularKeyDeleteHandler> hKey(
                raw_key);

        return RegSetValueExW(hKey.get(), name_key.data(), 0, REG_SZ,
            reinterpret_cast<const BYTE*>(value.data()),
            static_cast<DWORD>(
                (value.size() + 1) * sizeof(wchar_t))) == ERROR_SUCCESS;
    }

    bool WindowsRegistry::set_value_via_utf8(
        std::string_view sub_key,
        std::string_view name_key,
        const std::string_view value)
    {
        return set_value_via_utf16(
            ENCODER.from_utf8_to_utf16(sub_key),
            ENCODER.from_utf8_to_utf16(name_key),
            ENCODER.from_utf8_to_utf16(value)
        );
    }

    bool WindowsRegistry::is_sub_and_name_key_path_found_via_utf16(
        std::wstring_view sub_key,
        std::wstring_view name_key)
    {
        return !(get_value_via_utf16(sub_key, name_key).value().empty());
    }

    bool WindowsRegistry::is_sub_and_name_key_path_found_via_utf8(
        std::string_view sub_key,
        std::string_view name_key)
    {
        return !(get_value_via_utf16(
            ENCODER.from_utf8_to_utf16(sub_key),
            ENCODER.from_utf8_to_utf16(name_key)
        ).value().empty());
    }

    bool WindowsRegistry::remove_value_via_utf16(
        std::wstring_view sub_key,
        std::wstring_view name_key)
    {
        sub_key = (sub_key.empty()) ? _sub_key : sub_key;
        name_key = (name_key.empty()) ? _name_key : name_key;

        HKEY raw_key = nullptr;
        if (RegOpenKeyExW(_root_key, sub_key.data(), 0,
            KEY_SET_VALUE, &raw_key) != ERROR_SUCCESS)
        {
            return false;
        }
        std::unique_ptr<
            std::remove_pointer<HKEY>::type,
            RegularKeyDeleteHandler> hKey(raw_key);

        return RegDeleteValueW(hKey.get(), name_key.data()) == ERROR_SUCCESS;
    }

    bool WindowsRegistry::remove_value_via_utf8(
        std::string_view sub_key,
        std::string_view name_key)
    {
        return remove_value_via_utf16(
            ENCODER.from_utf8_to_utf16(sub_key),
            ENCODER.from_utf8_to_utf16(name_key)
        );
    }

    std::unordered_map<std::string, std::wstring> WindowsRegistry::get_values_via_utf16(
        std::wstring_view sub_key)
    {
        std::unordered_map<std::string, std::wstring> result;

        sub_key = sub_key.empty() ? _sub_key : sub_key;

        HKEY raw_key = nullptr;
        if (RegOpenKeyExW(_root_key, sub_key.data(), 0, KEY_READ, &raw_key) != ERROR_SUCCESS)
        {
            return result;
        }

        std::unique_ptr<std::remove_pointer<HKEY>::type, ValueEnumKeyDeleteHandler> hkey(raw_key);

        DWORD index = 0;
        wchar_t value_name[32767] = { 0 };
        DWORD value_name_size = 32767;
        DWORD value_type = 0;
        BYTE value_data[65535] = { 0 };
        DWORD value_data_size = 65535;

        while (true)
        {
            value_name_size = 32767;
            value_data_size = 65535;

            LONG enum_result = RegEnumValueW(
                hkey.get(),
                index++,
                value_name,
                &value_name_size,
                nullptr,
                &value_type,
                value_data,
                &value_data_size);

            if (enum_result == ERROR_NO_MORE_ITEMS)
            {
                break;
            }

            if (enum_result == ERROR_SUCCESS && value_type == REG_SZ)
            {
                std::wstring name(value_name, value_name_size);
                std::wstring value(reinterpret_cast<wchar_t*>(value_data));
                result.emplace(ENCODER.from_utf16_to_utf8(name), value);
            }
        }

        return result;
    }

    std::unordered_map<std::string, std::string> WindowsRegistry::get_values_via_utf8(
        std::string_view sub_key
    )
    {
        std::unordered_map<std::string, std::string> utf8_result;

        const std::wstring wide_sub_key =
            ENCODER.from_utf8_to_utf16(sub_key);
        const auto wide_map = get_values_via_utf16(wide_sub_key);

        for (const auto& [key, value] : wide_map)
        {
            utf8_result.emplace(
                key,
                ENCODER.from_utf16_to_utf8(value)
            );
        }

        return utf8_result;
    }



    void WindowsRegistry::setup(
        Result<void>& result,
        const HKEY hkey
    )
    {
        _root_key = hkey;
        _sub_key.assign(UTILITIES.DEFAULT_SUB_KEY);
        _name_key.assign(UTILITIES.DEFAULT_NAME_KEY);

        result.set_to_good_status_without_value();
    }

    void WindowsRegistry::get_values_via_utf8(
        Result<std::unordered_map<std::string, std::string>>& result,
        const std::string_view value
    )
    {
        result.set_to_good_status_with_value(
            WindowsRegistry::get_values_via_utf8(value)
        );
    }

    void WindowsRegistry::get_values_via_utf16(
        Result<std::unordered_map<std::string, std::wstring>>& result,
        const std::wstring_view value
    )
    {
        result.set_to_good_status_with_value(
            WindowsRegistry::get_values_via_utf16(value)
        );
    }

    void WindowsRegistry::remove_value_via_utf8(
        Result<void>& result,
        const std::string_view sub_path,
        const std::string_view name
    )
    {
        WindowsRegistry::remove_value_via_utf8(
            sub_path,
            name
        );

        result.set_to_good_status_without_value();
    }

    void WindowsRegistry::remove_value_via_utf16(
        Result<void>& result,
        const std::wstring_view sub_path,
        const std::wstring_view name
    )
    {
        WindowsRegistry::remove_value_via_utf16(
            sub_path,
            name
        );

        result.set_to_good_status_without_value();
    }

    void WindowsRegistry::set_sub_and_name_keys_via_utf8(
        Result<void>& result,
        const std::string_view sub_path,
        const std::string_view name
    )
    {
        WindowsRegistry::set_sub_and_name_keys_via_utf8(
            sub_path,
            name
        );

        result.set_to_good_status_without_value();
    }

    void WindowsRegistry::set_sub_and_name_keys_via_utf16(
        Result<void>& result,
        const std::wstring_view sub_path,
        const std::wstring_view name
    )
    {
        WindowsRegistry::set_sub_and_name_keys_via_utf16(
            sub_path,
            name
        );

        result.set_to_good_status_without_value();
    }

    void WindowsRegistry::is_sub_and_name_key_path_found_via_utf8(
        Result<bool>& result,
        const std::string_view sub_path,
        const std::string_view name
    )
    {
        result.set_to_good_status_with_value(
            WindowsRegistry::is_sub_and_name_key_path_found_via_utf8(
                sub_path,
                name
            )
        );
    }

    void WindowsRegistry::is_sub_and_name_key_path_found_via_utf16(
        Result<bool>& result,
        const std::wstring_view sub_path,
        const std::wstring_view name
    )
    {
        result.set_to_good_status_with_value(
            WindowsRegistry::is_sub_and_name_key_path_found_via_utf16(
                sub_path,
                name
            )
        );
    }

    void WindowsRegistry::get_value_via_utf8(
        Result<std::string>& result,
        const std::string_view sub_path,
        const std::string_view name
    )
    {
        const auto value = WindowsRegistry::get_value_via_utf8(
            sub_path,
            name
        );

        result.set_to_good_status_with_value(
            value.has_value() ? value.value() : std::string()
        );
    }

    void WindowsRegistry::get_value_via_utf16(
        Result<std::wstring>& result,
        const std::wstring_view sub_path,
        const std::wstring_view name
    )
    {
        const auto value = WindowsRegistry::get_value_via_utf16(
            sub_path,
            name
        );

        result.set_to_good_status_with_value(
            value.has_value() ? value.value() : std::wstring()
        );
    }

    void WindowsRegistry::set_value_via_utf8(
        Result<void>& result,
        const std::string_view sub_path,
        const std::string_view name,
        const std::string_view value
    )
    {
        WindowsRegistry::set_value_via_utf8(
            sub_path,
            name,
            value
        );

        result.set_to_good_status_without_value();
    }

    void WindowsRegistry::set_value_via_utf16(
        Result<void>& result,
        const std::wstring_view sub_path,
        const std::wstring_view name,
        const std::wstring_view value
    )
    {
        WindowsRegistry::set_value_via_utf16(
            sub_path,
            name,
            value
        );

        result.set_to_good_status_without_value();
    }
}
