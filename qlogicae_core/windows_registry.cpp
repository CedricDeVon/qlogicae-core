#include "pch.h"

#include "windows_registry.hpp"

struct RegularKeyDeleteHandler
{
    void operator() (HKEY handler) const
    {
        if (handler)
        {
            RegCloseKey(handler);
        }
    }
};

QLogicaeCore::WindowsRegistry::WindowsRegistry(const HKEY root_hkey)
{
    _root_key = root_hkey;
    _sub_key.assign(Constants::DEFAULT_SUB_KEY);
    _name_key.assign(Constants::DEFAULT_NAME_KEY);
}

QLogicaeCore::WindowsRegistry& QLogicaeCore::WindowsRegistry::hkcu()
{
    static QLogicaeCore::WindowsRegistry hkcu(HKEY_CURRENT_USER);

    return hkcu;
}

QLogicaeCore::WindowsRegistry& QLogicaeCore::WindowsRegistry::hklm()
{
    static QLogicaeCore::WindowsRegistry hklm(HKEY_LOCAL_MACHINE);

    return hklm;
}

bool QLogicaeCore::WindowsRegistry::set_sub_and_name_keys_via_utf16(
    const std::wstring_view sub_key,
    const std::wstring_view name_key)
{
    _sub_key.assign(sub_key);
    _name_key.assign(name_key);

    return true;
}

bool QLogicaeCore::WindowsRegistry::set_sub_and_name_keys_via_utf8(
    const std::string_view sub_key,
    const std::string_view name_key)
{
    return set_sub_and_name_keys_via_utf16(
        QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(sub_key),
        QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(name_key)
    );
}

std::optional<std::wstring> QLogicaeCore::WindowsRegistry::get_value_via_utf16(
    std::wstring_view sub_key,
    std::wstring_view name_key) const
{
    sub_key = (sub_key.empty()) ? _sub_key : sub_key;
    name_key = (name_key.empty()) ? _name_key : name_key;

    HKEY raw_key = nullptr;
    if (RegOpenKeyExW(_root_key, sub_key.data(),
        0, Constants::REGULAR_ACCESS_FLAGS, &raw_key) != ERROR_SUCCESS)
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

    if (hkey_value_size > Constants::HKEY_MAXIMUM_VALUE_SIZE)
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

std::optional<std::string> QLogicaeCore::WindowsRegistry::get_value_via_utf8(
    std::string_view sub_key,
    std::string_view name_key) const
{
    return QLogicaeCore::Encoder::get_instance().from_utf16_to_utf8(
        get_value_via_utf16(
            QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(sub_key),
            QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(name_key)
        ).value()
    );
}

bool QLogicaeCore::WindowsRegistry::set_value_via_utf16(
    std::wstring_view sub_key,
    std::wstring_view name_key,
    const std::wstring_view value) const
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

bool QLogicaeCore::WindowsRegistry::set_value_via_utf8(
    std::string_view sub_key,
    std::string_view name_key,
    const std::string_view value) const
{
    return set_value_via_utf16(
        QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(sub_key),
        QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(name_key),
        QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(value)
    );
}

bool QLogicaeCore::WindowsRegistry::is_sub_and_name_key_path_found_via_utf16(
    std::wstring_view sub_key,
    std::wstring_view name_key) const
{
    return !(get_value_via_utf16(sub_key, name_key).value().empty());
}

bool QLogicaeCore::WindowsRegistry::is_sub_and_name_key_path_found_via_utf8(
    std::string_view sub_key,
    std::string_view name_key) const
{
    return !(get_value_via_utf16(
        QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(sub_key),
        QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(name_key)
    ).value().empty());
}

bool QLogicaeCore::WindowsRegistry::remove_value_via_utf16(
    std::wstring_view sub_key,
    std::wstring_view name_key) const
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

bool QLogicaeCore::WindowsRegistry::remove_value_via_utf8(
    std::string_view sub_key,
    std::string_view name_key) const
{
    return remove_value_via_utf16(
        QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(sub_key),
        QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(name_key)
    );
}

std::unordered_map<std::string, std::wstring> QLogicaeCore::WindowsRegistry::get_values_via_utf16(
    std::wstring_view sub_key) const
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
    wchar_t value_name[Constants::HKEY_MAXIMUM_VALUE_NAME_SIZE] = { 0 };
    DWORD value_name_size = Constants::HKEY_MAXIMUM_VALUE_NAME_SIZE;
    DWORD value_type = 0;
    BYTE value_data[Constants::HKEY_MAXIMUM_VALUE_DATA_SIZE] = { 0 };
    DWORD value_data_size = Constants::HKEY_MAXIMUM_VALUE_DATA_SIZE;

    while (true)
    {
        value_name_size = Constants::HKEY_MAXIMUM_VALUE_NAME_SIZE;
        value_data_size = Constants::HKEY_MAXIMUM_VALUE_DATA_SIZE;

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
            result.emplace(QLogicaeCore::Encoder::get_instance().from_utf16_to_utf8(name), value);
        }
    }

    return result;
}

std::unordered_map<std::string, std::string> QLogicaeCore::WindowsRegistry::get_values_via_utf8(
    std::string_view sub_key) const
{
    std::unordered_map<std::string, std::string> utf8_result;

    const std::wstring wide_sub_key = QLogicaeCore::Encoder::get_instance().from_utf8_to_utf16(sub_key);
    const auto wide_map = get_values_via_utf16(wide_sub_key);

    for (const auto& [key, value] : wide_map)
    {
        utf8_result.emplace(
            key,
            QLogicaeCore::Encoder::get_instance().from_utf16_to_utf8(value)
        );
    }

    return utf8_result;
}
