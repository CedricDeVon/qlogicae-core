#pragma once

#include "case_sensitivity.hpp"

#include <cstdio>

namespace QLogicaeCore
{
    struct CaseAwareHash
    {
        using is_transparent = void;

        CaseSensitivity sensitivity;

        explicit CaseAwareHash(CaseSensitivity s) : sensitivity(s) {}

        std::size_t operator()(const std::string& s) const noexcept { return hash_impl(s); }
        std::size_t operator()(const std::string_view& sv) const noexcept { return hash_impl(sv); }

    private:
        std::size_t hash_impl(std::string_view str) const noexcept
        {
            std::size_t hash = 14695981039346656037ull;
            for (char c : str)
            {
                char x = (sensitivity == CaseSensitivity::SENSITIVE)
                    ? c
                    : static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                hash = (hash ^ static_cast<unsigned char>(x)) * 1099511628211ull;
            }
            return hash;
        }
    };
}
