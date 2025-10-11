#pragma once

#include "case_sensitivity.hpp"

#include <cstdio>

namespace QLogicaeCore
{
    struct CaseAwareEqual
    {
        using is_transparent = void;

        CaseSensitivity sensitivity;

        explicit CaseAwareEqual(CaseSensitivity s) : sensitivity(s) {}

        bool operator()(const std::string& a, const std::string& b) const noexcept
        {
            return compare_impl(a, b);
        }

        bool operator()(const std::string_view& a, const std::string_view& b) const noexcept
        {
            return compare_impl(a, b);
        }

        bool operator()(const std::string& a, const std::string_view& b) const noexcept
        {
            return compare_impl(a, b);
        }

        bool operator()(const std::string_view& a, const std::string& b) const noexcept
        {
            return compare_impl(a, b);
        }

    private:
        bool compare_impl(std::string_view a, std::string_view b) const noexcept
        {
            if (a.size() != b.size()) return false;
            if (sensitivity == CaseSensitivity::SENSITIVE) return a == b;
            for (size_t i = 0; i < a.size(); ++i) {
                if (std::tolower(static_cast<unsigned char>(a[i])) !=
                    std::tolower(static_cast<unsigned char>(b[i])))
                    return false;
            }
            return true;
        }
    };
}
