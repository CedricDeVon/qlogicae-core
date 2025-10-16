#include "pch.hpp"

#include "windows_registry_value_extractor.hpp"

namespace QLogicaeCore
{
    WindowsRegistryValueExtractor::WindowsRegistryValueExtractor(
        const std::string& sub_key, const std::string& name_key) :
            _sub_key(sub_key), _name_key(name_key)
    {

    }

    WindowsRegistryValueExtractor::WindowsRegistryValueExtractor(
        const std::wstring& sub_key, const std::wstring& name_key) :
            _sub_key(ENCODER.from_utf16_to_utf8(sub_key)),
            _name_key(ENCODER.from_utf16_to_utf8(name_key))
    {

    }

    std::optional<std::string>
        WindowsRegistryValueExtractor::get_sub_key() const
    {
        return _sub_key;
    }

    std::optional<std::string>
        WindowsRegistryValueExtractor::get_name_key() const
    {
        return _name_key;
    }

    std::optional<std::string>
        WindowsRegistryValueExtractor::get_value() const
    {
        try
        {
            return WindowsRegistry::hkcu()
                .get_value_via_utf8(_sub_key, _name_key).value();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string("Exception at WindowsRegistryValueExtractor::get_value(): ") + exception.what());
        }
    }

    void WindowsRegistryValueExtractor::get_sub_key(
        Result<std::optional<std::string>>& result
    ) const
    {
        result.set_to_good_status_with_value(_sub_key);
    }

    void WindowsRegistryValueExtractor::get_name_key(
        Result<std::optional<std::string>>& result
    ) const
    {
        result.set_to_good_status_with_value(_name_key);
    }

    void WindowsRegistryValueExtractor::get_value(
        Result<std::string>& result
    ) const
    {
        result.set_to_good_status_with_value(WindowsRegistry::hkcu()
            .get_value_via_utf8(_sub_key, _name_key).value()
        );        
    }

    void WindowsRegistryValueExtractor::setup(
        Result<void>& result,
        const std::string sub_key,
        const std::string name_key
    )
    {
        _sub_key = sub_key;
        _name_key = name_key;

        result.set_to_good_status_without_value();
    }

    void WindowsRegistryValueExtractor::setup(
        Result<void>& result,
        const std::wstring sub_key,
        const std::wstring name_key
    )
    {
        Result<std::string> string_result;
        ENCODER.from_utf16_to_utf8(string_result, sub_key);
        _sub_key = string_result.get_value();
        
        ENCODER.from_utf16_to_utf8(string_result, name_key);
        _name_key = string_result.get_value();

        result.set_to_good_status_without_value();
    }
}
