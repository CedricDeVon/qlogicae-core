#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "encoder.hpp"
#include "dot_env.hpp"
#include "abstract_value_extractor.hpp"

namespace QLogicaeCore
{
    class DotEnvValueExtractor :
        public AbstractValueExtractor
    {
    public:
        DotEnvValueExtractor();
        
        ~DotEnvValueExtractor();

        DotEnvValueExtractor(
            const std::string& key
        );

        DotEnvValueExtractor(
            const std::wstring& key
        );

        DotEnvValueExtractor(
            const DotEnvValueExtractor& instance
        ) = delete;

        DotEnvValueExtractor(
            DotEnvValueExtractor&& instance
        ) noexcept = delete;

        DotEnvValueExtractor& operator = (
            DotEnvValueExtractor&& instance
        ) = delete;

        DotEnvValueExtractor& operator = (
            const DotEnvValueExtractor& instance
        ) = delete;

        bool setup();

        std::future<bool> setup_async();
        
        void setup(
            Result<void>& result
        );

        void setup_async(
            Result<std::future<void>>& result
        );

        bool setup(
            const std::string key
        );

        void setup_async(
            const std::function<void(const bool& result)>& callback
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback
        );

        void setup(
            Result<void>& result,
            const std::string key
        );
        
        std::future<bool> setup_async(
            const std::string key
        );

        void setup_async(
            const std::function<void(const bool& result)>& callback,
            const std::string key
        );

        void setup_async(
            Result<std::future<void>>& result,
            const std::string key
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::string key
        );
        
        bool setup(
            const std::wstring key
        );

        std::future<bool> setup_async(
            const std::wstring key
        );

        void setup_async(
            const std::function<void(const bool& result)>& callback,
            const std::wstring key
        );

        void setup(
            Result<void>& result,
            const std::wstring key
        );
     
        void setup_async(
            Result<std::future<void>>& result,
            const std::wstring key
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::wstring key
        );

        std::optional<std::wstring> get_key();

        std::optional<std::string> get_value();

        void get_key(
            Result<std::optional<std::wstring>>& result
        );

        void get_value(
            Result<std::string>& result
        );

        static DotEnvValueExtractor& get_instance();

        static void get_instance(
            Result<DotEnvValueExtractor*>& result
        );

    protected:
        std::wstring _key;
    };

    inline static DotEnvValueExtractor& DOT_ENV_VALUE_EXTRACTOR =
        DotEnvValueExtractor::get_instance();
}

