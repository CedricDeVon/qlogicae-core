#pragma once

#include "pch.h"

#include "encoder.hpp"
#include "dot_env.hpp"
#include "abstract_value_extractor.hpp"

namespace QLogicaeCore
{
    class DotEnvValueExtractor : public AbstractValueExtractor
    {
    public:
        ~DotEnvValueExtractor() = default;
        DotEnvValueExtractor(const std::string&);
        DotEnvValueExtractor(const std::wstring&);
        DotEnvValueExtractor(const DotEnvValueExtractor&) = delete;
        DotEnvValueExtractor(DotEnvValueExtractor&&) noexcept = delete;
        DotEnvValueExtractor& operator = (DotEnvValueExtractor&&) = delete;
        DotEnvValueExtractor& operator = (const DotEnvValueExtractor&) = delete;

        std::optional<std::wstring> get_key() const;
        std::optional<std::string> get_value() const;

    protected:
        const std::wstring _key;
    };
}
