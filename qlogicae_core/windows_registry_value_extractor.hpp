#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "windows_registry.hpp"
#include "abstract_value_extractor.hpp"

namespace QLogicaeCore
{
    class WindowsRegistryValueExtractor : public AbstractValueExtractor
    {
    public:
        ~WindowsRegistryValueExtractor() = default;
        WindowsRegistryValueExtractor(const std::string&, const std::string&);
        WindowsRegistryValueExtractor(const std::wstring&, const std::wstring&);
        WindowsRegistryValueExtractor(const WindowsRegistryValueExtractor&) = delete;
        WindowsRegistryValueExtractor(WindowsRegistryValueExtractor&&) noexcept = delete;
        WindowsRegistryValueExtractor& operator = (WindowsRegistryValueExtractor&&) = delete;
        WindowsRegistryValueExtractor& operator = (const WindowsRegistryValueExtractor&) = delete;

        std::optional<std::string> get_value() const;
        std::optional<std::string> get_sub_key() const;
        std::optional<std::string> get_name_key() const;

    protected:
        const std::string _sub_key;
        const std::string _name_key;
    };
}
