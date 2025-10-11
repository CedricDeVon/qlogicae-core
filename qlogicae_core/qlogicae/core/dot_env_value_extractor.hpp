#pragma once

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

    protected:
        const std::wstring _key;
    };
}
