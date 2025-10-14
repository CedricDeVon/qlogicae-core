#pragma once

#include "result.hpp"
#include "encoder.hpp"
#include "dot_env.hpp"
#include "abstract_value_extractor.hpp"

namespace QLogicaeCore
{
    class DotEnvValueExtractor :
        public AbstractValueExtractor
    {
    public:
        ~DotEnvValueExtractor() = default;

        DotEnvValueExtractor(const std::string& key);

        DotEnvValueExtractor(const std::wstring& key);

        DotEnvValueExtractor(
            const DotEnvValueExtractor& dot_env_value_extractor
        ) = delete;

        DotEnvValueExtractor(
            DotEnvValueExtractor&& dot_env_value_extractor
        ) noexcept = delete;

        DotEnvValueExtractor& operator = (
            DotEnvValueExtractor&& dot_env_value_extractor
        ) = delete;

        DotEnvValueExtractor& operator = (
            const DotEnvValueExtractor& dot_env_value_extractor
        ) = delete;

        std::optional<std::wstring> get_key() const;

        std::optional<std::string> get_value() const;

        void get_key(Result<std::optional<std::wstring>>& result) const;

        void get_value(Result<std::string>& result) const;

        void setup(
            Result<void>& result,
            const std::string key
        );

        void setup(
            Result<void>& result,
            const std::wstring key
        );

    protected:
        std::wstring _key;
    };
}

