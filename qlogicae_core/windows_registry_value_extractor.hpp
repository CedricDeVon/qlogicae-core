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
        WindowsRegistryValueExtractor();
        
        ~WindowsRegistryValueExtractor();
        
        WindowsRegistryValueExtractor(
            const std::string& sub_key,
            const std::string& name_key
        );
        
        WindowsRegistryValueExtractor(
            const std::wstring& sub_key,
            const std::wstring& name_key
        );
        
        WindowsRegistryValueExtractor(
            const WindowsRegistryValueExtractor&
                instance
        ) = delete;
        
        WindowsRegistryValueExtractor(
            WindowsRegistryValueExtractor&&
                instance
        ) noexcept = delete;
        
        WindowsRegistryValueExtractor& operator = (
            WindowsRegistryValueExtractor&&
                instance
        ) = delete;
        
        WindowsRegistryValueExtractor& operator = (
            const WindowsRegistryValueExtractor&
                instance
        ) = delete;

        bool setup();

        std::future<bool> setup_async();

        void setup_async(
            const std::function<void(const bool& result)>& callback
        );

        void setup(
            Result<void>& result
        );

        void setup_async(
            Result<std::future<void>>& result
        );
        void setup_async(
            const std::function<void(Result<void>& result)>& callback
        );

        bool setup(
            const std::string& sub_key,
            const std::string& name_key
        );

        std::future<bool> setup_async(
            const std::string& sub_key,
            const std::string& name_key
        );

        void setup_async(
            const std::function<void(const bool& result)>& callback,
            const std::string& sub_key,
            const std::string& name_key
        );

        bool setup(
            const std::wstring& sub_key,
            const std::wstring& name_key
        );

        std::future<bool> setup_async(
            const std::wstring& sub_key,
            const std::wstring& name_key
        );

        void setup_async(
            const std::function<void(const bool& result)>& callback,
            const std::wstring& sub_key,
            const std::wstring& name_key
        );

        void setup(
            Result<void>& result,
            const std::string& sub_key,
            const std::string& name_key
        );

        void setup_async(
            Result<std::future<void>>& result,
            const std::string& sub_key,
            const std::string& name_key
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::string& sub_key,
            const std::string& name_key
        );

        void setup(
            Result<void>& result,
            const std::wstring& sub_key,
            const std::wstring& name_key
        );

        void setup_async(
            Result<std::future<void>>& result,
            const std::wstring& sub_key,
            const std::wstring& name_key
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::wstring& sub_key,
            const std::wstring& name_key
        );

        std::optional<std::string> get_value();
        
        std::optional<std::string> get_sub_key();
        
        std::optional<std::string> get_name_key();

        void get_value(
            Result<std::string>& result
        );

        void get_sub_key(
            Result<std::string>& result
        );

        void get_name_key(
            Result<std::string>& result
        );

        static WindowsRegistryValueExtractor& get_instance();

        static void get_instance(
            Result<WindowsRegistryValueExtractor*>& result
        );

    protected:
        std::string _sub_key;

        std::string _name_key;
    };

    inline static WindowsRegistryValueExtractor& WINDOWS_REGISTRY_VALUE_EXTRACTOR =
        WindowsRegistryValueExtractor::get_instance();
}

