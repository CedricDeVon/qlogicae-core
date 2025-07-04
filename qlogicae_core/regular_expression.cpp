#pragma once

#include "pch.h"

#include "regular_expression.hpp"

namespace QLogicaeCore
{
    RegularExpression& RegularExpression::instance()
    {
        static RegularExpression singleton;
        return singleton;
    }

    RegularExpression::~RegularExpression()
    {
        clear_all_patterns();
    }

    bool RegularExpression::add_pattern(
        const std::string& name,
        const std::string& pattern)
    {
        int error_number;
        PCRE2_SIZE error_offset;

        pcre2_code* regular_expression = pcre2_compile(
            (PCRE2_SPTR)pattern.c_str(),
            PCRE2_ZERO_TERMINATED,
            0,
            &error_number,
            &error_offset,
            nullptr
        );

        if (!regular_expression)
        {
            return false;
        }

        std::unique_lock lock(_mutex);

        if (_compiled_patterns.contains(name))
        {
            pcre2_code_free(_compiled_patterns[name].second);
        }

        _compiled_patterns[name] = { pattern, regular_expression };
        return true;
    }

    std::string RegularExpression::get_patterrn(
        const std::string& name) const
    {
        std::shared_lock lock(_mutex);
        auto pair = _compiled_patterns.find(name);
        return (pair != _compiled_patterns.end()) ?
            pair->second.first : "";
    }

    bool RegularExpression::has_pattern(
        const std::string& name) const
    {
        std::shared_lock lock(_mutex);
        return _compiled_patterns.find(name) != _compiled_patterns.end();
    }

    void RegularExpression::clear_all_patterns()
    {
        std::unique_lock lock(_mutex);
        for (auto& [_, pair] : _compiled_patterns)
        {
            pcre2_code_free(pair.second);
        }

        _compiled_patterns.clear();
    }

    bool RegularExpression::match_named(
        const std::string& subject,
        const std::string& pattern_name)
    {
        std::shared_lock lock(_mutex);
        auto result = _compiled_patterns.find(pattern_name);
        if (result == _compiled_patterns.end())
        {
            return false;
        }

        return _do_match(subject, result->second.second);
    }

    bool RegularExpression::match_direct(
        const std::string& subject,
        const std::string& pattern)
    {
        int error_number;
        PCRE2_SIZE error_offset;

        pcre2_code* regular_expression = pcre2_compile(
            (PCRE2_SPTR)pattern.c_str(),
            PCRE2_ZERO_TERMINATED,
            0,
            &error_number,
            &error_offset,
            nullptr
        );

        if (!regular_expression)
        {
            return false;
        }

        bool result = _do_match(subject, regular_expression);
        pcre2_code_free(regular_expression);

        return result;
    }

    std::future<bool> RegularExpression::match_named_async(
        const std::string& subject,
        const std::string& pattern_name)
    {
        return std::async(std::launch::async,
            [this, subject, pattern_name]() -> bool
        {
            try
            {
                return match_named(subject, pattern_name);
            }
            catch (...)
            {
                return false;
            }
        });
    }

    std::future<bool> RegularExpression::match_direct_async(
        const std::string& subject,
        const std::string& pattern_name)
    {
        return std::async(std::launch::async,
            [this, subject, pattern_name]() -> bool
        {
            try
            {
                return match_direct(subject, pattern_name);
            }
            catch (...)
            {
                return false;
            }
        });
    }

    bool RegularExpression::_do_match(
        const std::string& subject,
        pcre2_code* code) const
    {
        pcre2_match_data* match_data =
            pcre2_match_data_create_from_pattern(code, nullptr);

        int result = pcre2_match(
            code,
            (PCRE2_SPTR)subject.c_str(),
            subject.length(),
            0,
            0,
            match_data,
            nullptr
        );

        pcre2_match_data_free(match_data);

        return result >= 0;
    }
}

