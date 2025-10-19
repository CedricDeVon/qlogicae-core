#include "pch.hpp"

#include "regular_expression.hpp"

namespace QLogicaeCore
{
    RegularExpression& RegularExpression::get_instance()
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
        const std::string& pattern
    )
    {
        try
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at RegularExpression::add_pattern(): " +
                exception.what()
            );
        }
    }

    std::string RegularExpression::get_patterrn(
        const std::string& name
    )
    {
        try
        {
            std::shared_lock lock(_mutex);
     
            auto pair = _compiled_patterns.find(name);
            return (pair != _compiled_patterns.end()) ?
                pair->second.first : "";
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at RegularExpression::get_patterrn(): " +
                exception.what()
            );
        }
    }

    bool RegularExpression::has_pattern(
        const std::string& name
    )
    {
        try
        {
            std::shared_lock lock(_mutex);

            return _compiled_patterns.find(name) !=
                _compiled_patterns.end();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at RegularExpression::has_pattern(): " +
                exception.what()
            );
        }
    }

    void RegularExpression::clear_all_patterns()
    {
        try
        {
            std::unique_lock lock(_mutex);

            for (auto& [_, pair] : _compiled_patterns)
            {
                pcre2_code_free(pair.second);
            }

            _compiled_patterns.clear();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at RegularExpression::clear_all_patterns(): " +
                exception.what()
            );
        }
    }

    bool RegularExpression::match_named(
        const std::string& subject,
        const std::string& pattern_name
    )
    {
        try
        {
            std::shared_lock lock(_mutex);

            auto result =
                _compiled_patterns.find(pattern_name);
            if (result == _compiled_patterns.end())
            {
                return false;
            }

            return _do_match(
                subject,
                result->second.second
            );
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at RegularExpression::match_named(): " +
                exception.what()
            );
        }
    }

    bool RegularExpression::match_direct(
        const std::string& subject,
        const std::string& pattern
    )
    {
        try
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

            bool result =
                _do_match(
                    subject,
                    regular_expression
                );
            pcre2_code_free(regular_expression);

            return result;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at RegularExpression::match_direct(): " +
                exception.what()
            );
        }
    }

    std::future<bool> RegularExpression::match_named_async(
        const std::string& subject,
        const std::string& pattern_name
    )
    {
        return std::async(std::launch::async,
            [this, subject, pattern_name]() -> bool
        {
            return match_named(subject, pattern_name);            
        });
    }

    std::future<bool> RegularExpression::match_direct_async(
        const std::string& subject,
        const std::string& pattern_name
    )
    {
        return std::async(std::launch::async,
            [this, subject, pattern_name]() -> bool
        {
            return match_direct(subject, pattern_name);            
        });
    }

    bool RegularExpression::_do_match(
        const std::string& subject,
        pcre2_code* get_error_code
    )
    {
        try
        {
            pcre2_match_data* match_data =
                pcre2_match_data_create_from_pattern(
                    get_error_code,
                    nullptr
                );

            int result = pcre2_match(
                get_error_code,
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at RegularExpression::_do_match(): " +
                exception.what()
            );
        }
    }

    void RegularExpression::setup(
        Result<void>& result
    )
    {
        result.set_to_good_status_without_value();
    }

    void RegularExpression::clear_all_patterns(
        Result<void>& result
    )
    {
        std::unique_lock lock(_mutex);

        for (auto& [_, pair] : _compiled_patterns)
        {
            pcre2_code_free(pair.second);
        }

        _compiled_patterns.clear();

        result.set_to_good_status_without_value();
    }

    void RegularExpression::remove_pattern(
        Result<bool>& result,
        const std::string& name
    )
    {
        result.set_to_good_status_with_value(true);
    }

    void RegularExpression::has_pattern(
        Result<bool>& result,
        const std::string& name
    )
    {
        std::shared_lock lock(_mutex);

        result.set_to_good_status_with_value(
            _compiled_patterns.find(name) !=
                _compiled_patterns.end()
        );
    }

    void RegularExpression::get_patterrn(
        Result<std::string>& result,
        const std::string& value
    )
    {
        std::shared_lock lock(_mutex);

        auto pair = _compiled_patterns.find(value);
        if (pair != _compiled_patterns.end())
        {
            result.set_to_good_status_with_value(
                pair->second.first
            );
        }
        else
        {
            result.set_to_bad_status_with_value(
                ""
            );
        }
    }

    void RegularExpression::add_pattern(
        Result<void>& result,
        const std::string& name,
        const std::string& pattern
    )
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
            return result.set_to_bad_status_without_value();
        }

        std::unique_lock lock(_mutex);

        if (_compiled_patterns.contains(name))
        {
            pcre2_code_free(_compiled_patterns[name].second);
        }

        _compiled_patterns[name] = { pattern, regular_expression };
        result.set_to_good_status_without_value();
    }

    void RegularExpression::match_named(
        Result<bool>& result,
        const std::string& subject,
        const std::string& pattern_name
    )
    {
        std::shared_lock lock(_mutex);

        auto content = _compiled_patterns.find(pattern_name);
        if (content == _compiled_patterns.end())
        {
            return result.set_to_bad_status_without_value();
        }

        if (_do_match(subject, content->second.second))
        {
            result.set_to_good_status_without_value();
        }
        else
        {
            result.set_to_bad_status_without_value();
        }        
    }

    void RegularExpression::match_direct(
        Result<bool>& result,
        const std::string& subject,
        const std::string& pattern
    )
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
            return result.set_to_bad_status_without_value();
        }

        if (_do_match(subject, regular_expression))
        {
            result.set_to_good_status_without_value();
        }
        else
        {
            result.set_to_bad_status_without_value();
        }
        
        pcre2_code_free(regular_expression);
    }

    void RegularExpression::match_named_async(
        Result<std::future<bool>>& result,
        const std::string& name,
        const std::string& pattern
    )
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async,
            [this, name, pattern]() -> bool
            {
                Result<bool> result;

                match_named(result, name, pattern);          

                return result.get_value();
            }
        ));
    }

    void RegularExpression::match_direct_async(
        Result<std::future<bool>>& result,
        const std::string& name,
        const std::string& pattern
    )
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async,
            [this, name, pattern]() -> bool
            {
                Result<bool> result;

                match_direct(
                    result,
                    name,
                    pattern
                );

                return result.get_value();
            }
        ));
    }

    void RegularExpression::get_instance(
        Result<RegularExpression*>& result
    )
    {
        static RegularExpression instance;

        result.set_to_good_status_with_value(&instance);
    }
}

