#pragma once

#include "encoder.hpp"
#include "windows_registry.hpp"
#include "abstract_value_extractor.hpp"

namespace QLogicaeCore
{
    class WindowsRegistryValueExtractor :
        public AbstractValueExtractor
    {
    public:
        ~WindowsRegistryValueExtractor() = default;
        
        WindowsRegistryValueExtractor(
            const std::string&,
            const std::string&
        );
        
        WindowsRegistryValueExtractor(
            const std::wstring&,
            const std::wstring&
        );
        
        WindowsRegistryValueExtractor(
            const WindowsRegistryValueExtractor&
                windows_registry_value_extractor
        ) = delete;
        
        WindowsRegistryValueExtractor(
            WindowsRegistryValueExtractor&&
            windows_registry_value_extractor
        ) noexcept = delete;
        
        WindowsRegistryValueExtractor& operator = (
            WindowsRegistryValueExtractor&&
            windows_registry_value_extractor
        ) = delete;
        
        WindowsRegistryValueExtractor& operator = (
            const WindowsRegistryValueExtractor&
            windows_registry_value_extractor
        ) = delete;

        std::optional<std::string> get_value() const;
        
        std::optional<std::string> get_sub_key() const;
        
        std::optional<std::string> get_name_key() const;

        void get_value(Result<std::optional<std::string>>& result) const;

        void get_sub_key(Result<std::optional<std::string>>& result) const;

        void get_name_key(Result<std::optional<std::string>>& result) const;

    protected:
        const std::string _sub_key;
        const std::string _name_key;
    };
}

