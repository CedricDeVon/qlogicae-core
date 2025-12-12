#include "pch.hpp"

#include "../includes/regular_expression_manager.hpp"

namespace QLogicaeCppCore
{    
    RegularExpressionManager::RegularExpressionManager()
    {
        Result<bool> result;

        construct(result);
    }

    RegularExpressionManager::~RegularExpressionManager()
    {
        Result<bool> result;

        destruct(result);
    }

    void RegularExpressionManager::construct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            true
        );
    }

    void RegularExpressionManager::destruct(
        Result<bool>& result
    )
    {
        clear_all_patterns(
            result
        );
    }

    void RegularExpressionManager::clear_all_patterns(
        Result<bool>& result
    )
    {
        MUTEX_MANAGER.lock_mutex<
            std::unique_lock<std::shared_mutex>,
            std::shared_mutex>(
                result,
                this
        );

        for (auto& [_, pair] : _compiled_patterns)
        {
            pcre2_code_free(pair.second);
        }

        _compiled_patterns.clear();

        result.set_to_good_status_with_value(
            true
        );
    }

    void RegularExpressionManager::remove_pattern(
        Result<bool>& result,
        const std::string_view& name
    )
    {
        MUTEX_MANAGER.lock_mutex<
            std::shared_lock<std::shared_mutex>,
            std::shared_mutex>(
                result,
                this
        );

        auto pair = _compiled_patterns.find(name.data());

        if (pair != _compiled_patterns.end())
        {
            _compiled_patterns.erase(name.data());
            result.set_to_good_status_with_value(
                true
            );
            return;
        }

        result.set_to_good_status_with_value(
            false
        );
    }

    void RegularExpressionManager::has_pattern(
        Result<bool>& result,
        const std::string_view& name
    )
    {
        MUTEX_MANAGER.lock_mutex<
            std::shared_lock<std::shared_mutex>,
            std::shared_mutex>(
                result,
                this
            );

        result.set_to_good_status_with_value(
            _compiled_patterns.find(name.data()) !=
            _compiled_patterns.end()
        );
    }

    void RegularExpressionManager::get_patterrn(
        Result<std::string>& result,
        const std::string_view& value
    )
    {
        Result<bool> bool_result;

        MUTEX_MANAGER.lock_mutex<
            std::shared_lock<std::shared_mutex>,
            std::shared_mutex>(
                bool_result,
                this
            );

        auto pair = _compiled_patterns.find(value.data());

        result.set_to_good_status_with_value(
            (pair != _compiled_patterns.end()) ? pair->second.first : ""
        );
    }

    void RegularExpressionManager::add_pattern(
        Result<bool>& result,
        const std::string_view& name,
        const std::string_view& pattern
    )
    {
        int error_number;
        PCRE2_SIZE error_offset;

        pcre2_code* regular_expression = pcre2_compile(
            (PCRE2_SPTR)pattern.data(),
            PCRE2_ZERO_TERMINATED,
            0,
            &error_number,
            &error_offset,
            nullptr
        );

        if (!regular_expression)
        {
            return result.set_to_bad_status_with_value(
                false
            );
        }

        MUTEX_MANAGER.lock_mutex<
            std::unique_lock<std::shared_mutex>,
            std::shared_mutex>(
                result,
                this
            );

        if (_compiled_patterns.contains(name.data()))
        {
            pcre2_code_free(_compiled_patterns[name.data()].second);
        }

        _compiled_patterns[name.data()] = { pattern.data(), regular_expression };
        result.set_to_good_status_with_value(
            true
        );
    }

    void RegularExpressionManager::match_named(
        Result<bool>& result,
        const std::string_view& subject,
        const std::string_view& pattern_name
    )
    {
        MUTEX_MANAGER.lock_mutex<
            std::shared_lock<std::shared_mutex>,
            std::shared_mutex>(
                result,
                this
            );

        auto content = _compiled_patterns.find(pattern_name.data());
        if (content == _compiled_patterns.end())
        {
            return result.set_to_bad_status_with_value(
                false
            );
        }

        _do_match(
            result,
            subject,
            content->second.second
        );
    }

    void RegularExpressionManager::match_direct(
        Result<bool>& result,
        const std::string_view& subject,
        const std::string_view& pattern
    )
    {
        int error_number;
        PCRE2_SIZE error_offset;

        pcre2_code* regular_expression = pcre2_compile(
            (PCRE2_SPTR)pattern.data(),
            PCRE2_ZERO_TERMINATED,
            0,
            &error_number,
            &error_offset,
            nullptr
        );

        if (!regular_expression)
        {
            return result.set_to_bad_status_with_value(
                false
            );
        }

        _do_match(
            result,
            subject,
            regular_expression
        );
        
        pcre2_code_free(
            regular_expression
        );
    }

    void RegularExpressionManager::_do_match(
        Result<bool>& result,
        const std::string_view& subject,
        pcre2_code* get_error_code
    )
    {
        pcre2_match_data* match_data =
            pcre2_match_data_create_from_pattern(
                get_error_code,
                nullptr
            );

        int result_value = pcre2_match(
            get_error_code,
            (PCRE2_SPTR)subject.data(),
            subject.length(),
            0,
            0,
            match_data,
            nullptr
        );

        pcre2_match_data_free(match_data);

        result.set_to_good_status_with_value(
            result_value >= 0
        );
    }
}

