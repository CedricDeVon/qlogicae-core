#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "utilities.hpp"
#include "regular_expression.hpp"
#include "validation_password_rules.hpp"

#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

namespace QLogicaeCore
{    
    class Validators
    {
    public:
        bool setup();

        void setup(
            Result<void>& result
        );

        std::future<bool> setup_async();

        void setup_async(
            const std::function<void(const bool& result)>& callback
        );

        void setup_async(
            Result<std::future<void>>& result
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback
        );

        bool is_not_empty(
            const std::string_view& value
        );
        
        bool is_empty(
            const std::string_view& value
        );
        
        bool is_lowercase(
            const std::string_view& value
        );
        
        bool is_uppercase(
            const std::string_view& value
        );
        
        bool is_first_letter_uppercase(
            const std::string_view& value
        );
        
        bool is_prefix_found(
            const std::string_view& value,
            const std::string_view& prefix
        );
        
        bool is_suffix_found(
            const std::string_view& value,
            const std::string_view& suffix
        );
        
        bool is_substring_found(
            const std::string_view& value,
            const std::string_view& substring
        );
        
        bool is_base64(
            const std::string_view& value
        );
        
        bool is_utf8(
            const std::string_view& value
        );
        
        bool is_utf16(
            const std::string_view& value
        );
        
        bool is_slug(
            const std::string_view& value
        );
        
        bool is_hex(
            const std::string_view& value
        );
        
        bool is_uuid4(
            const std::string_view& value
        );
        
        bool is_uuid6(
            const std::string_view& value
        );
        
        bool is_ipv4(
            const std::string_view& value
        );
        
        bool is_ipv6(
            const std::string_view& value
        );
        
        bool is_url(
            const std::string_view& value
        );
        
        bool is_uri(
            const std::string_view& value
        );
        
        bool is_mac_address(
            const std::string_view& value
        );
        
        bool is_hostname(
            const std::string_view& value
        );
        
        bool is_domain(
            const std::string_view& value
        );
        
        bool is_port_in_range(
            const uint32_t& port,
            const uint32_t& minimum = 1,
            const uint32_t& maximum = 65535
        );        

        bool is_port_in_range(
            const std::string_view& port,
            const uint32_t& minimum = 1,
            const uint32_t& maximum = 65535
        );
        
        bool is_alpanumeric(
            const std::string_view& value
        );
        
        bool is_decimal(
            const std::string_view& value
        );
        
        bool is_date(
            const std::string_view& value,
            const std::string_view& format
        );
        
        bool is_time(
            const std::string_view& value,
            const std::string_view& format
        );
        
        bool is_datetime(
            const std::string_view& value,
            const std::string_view& format
        );
        
        bool is_past_date(
            const std::string_view& value,
            const std::string_view& format
        );
        
        bool is_future_date(
            const std::string_view& value,
            const std::string_view& format
        );
        
        bool is_unix(
            const std::string_view& value
        );
        
        bool is_iso8601(
            const std::string_view& value
        );
        
        bool is_utc(
            const std::string_view& value
        );
        
        bool is_leap_year(
            const int64_t& value
        );
        
        bool is_leap_year(
            const std::string_view& value
        );        
        
        bool is_within_inclusive_range(
            const int64_t& minimum,
            const int64_t& maximum
        );
        
        bool is_within_inclusive_range(
            const std::string_view& minimum,
            const std::string_view& maximum
        );
        
        bool is_within_exclusive_range(
            const int64_t& minimum,
            const int64_t& maximum
        );
        
        bool is_within_exclusive_range(
            const std::string_view& minimum,
            const std::string_view& maximum
        );
        
        bool is_even(
            const int64_t& value
        );
        
        bool is_even(
            const std::string_view& value
        );
        
        bool is_odd(
            const int64_t& value
        );
        
        bool is_odd(
            const std::string_view& value
        );
        
        bool is_prime(
            const int64_t& value
        );
        
        bool is_prime(
            const std::string_view& value
        );
        
        bool is_divisible_by(
            const int64_t& value,
            const int64_t& divisor
        );
        
        bool is_divisible_by(
            const std::string_view& value,
            const std::string_view& divisor
        );
        
        bool is_percentage(
            const double& value
        );
        
        bool is_percentage(
            const std::string_view& value
        );
        
        bool is_latitude(
            const double& value
        );
        
        bool is_latitude(
            const std::string_view& value
        );
        
        bool is_longitude(
            const double& value
        );
        
        bool is_longitude(
            const std::string_view& value
        );
        
        bool is_coordinate(
            const double& latitude,
            const double& longitude
        );
        
        bool is_coordinate(
            const std::string_view& latitude,
            const std::string_view& longitude
        );
        
        bool is_country_code(
            const std::string_view& value
        );
        
        bool is_currency_code(
            const std::string_view& value
        );
        
        bool is_language_code(
            const std::string_view& value
        );
        
        bool is_hex_color(
            const std::string_view& value
        );
        
        bool is_rgb_color(
            const std::string_view& value
        );
        
        bool is_rgba_color(
            const std::string_view& value
        );
        
        bool is_rgb_color(
            const uint8_t& red,
            const uint8_t& green,
            const uint8_t& blue
        );
        
        bool is_rgba_color(
            const uint8_t& red,
            const uint8_t& green,
            const uint8_t& blue,
            const uint8_t& alpha
        );
        
        bool is_file_path(
            const std::string_view& value
        );
        
        bool is_file_name(
            const std::string_view& value
        );
        
        bool is_file_extension(
            const std::string_view& value
        );
        
        bool is_file_extension_allowed(
            const std::string_view& value,
            const std::set<std::string>& allowed_extensions
        );
        
        bool is_mime_type(
            const std::string_view& value
        );
        
        bool is_base64_image(
            const std::string_view& value
        );
        
        bool is_data_uri(
            const std::string_view& value
        );
        
        bool is_file_size_allowed(
            const std::size_t& value,
            const std::size_t& maximum_size
        );
        
        bool is_file_type_allowed(
            const std::string_view& value,
            const std::set<std::string>& allowed_types
        );
        
        bool is_age(
            const uint8_t& value
        );
        
        bool is_age(
            const std::string_view& value
        );
        
        bool is_gender(
            const std::string_view& value
        );
        
        bool is_phone_number(
            const std::string_view& value
        );
        
        bool is_e164_phone_number(
            const std::string_view& value
        );
        
        bool is_country_calling_code(
            const std::string_view& value
        );
        
        bool is_address_line(
            const std::string_view& value
        );
        
        bool is_full_name(
            const std::string_view& value
        );
        
        bool is_first_name(
            const std::string_view& value
        );
        
        bool is_middle_name(
            const std::string_view& value
        );
        
        bool is_middle_initial(
            const std::string_view& value
        );
        
        bool is_adult(
            const uint8_t& age,
            const uint8_t& minimum_age = 18
        );
        
        bool is_juvenile(
            const uint8_t& age
        );
        
        bool is_child(
            const uint8_t& age
        );
        
        bool is_email(
            const std::string_view& value
        );
        
        bool is_strong_password(
            const std::string_view& value,
            const ValidationPasswordRules& rules
        );
        
        bool is_character_repeated(
            const std::string_view& value,
            const std::size_t& threshold
        );
        
        bool is_blacklisted_word_found(
            const std::string_view& value,
            const std::vector<std::string>& blacklist
        );
        
        template<std::ranges::input_range Range,
        typename Predicate>
            bool is_valid_range(
            const Range& range,
            Predicate predicate
        );
        
        template<typename Type>
        bool is_enum_value(
            Type value,
            std::span<const Type> allowed
        );
        
        template<typename Type>
        bool is_unique(
            const std::vector<Type>& values
        );
        
        template<typename Type>
        bool is_sorted(
            const std::vector<Type>& values
        );
        
        template<typename Type>
        bool is_empty(
            const std::vector<Type>& values
        );
        
        template<typename Type>
        bool is_found(
            const std::vector<Type>& values,
            std::function<bool(const Type&)> predicate
        );       

        void is_not_empty(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_empty(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_lowercase(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_uppercase(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_first_letter_uppercase(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_prefix_found(
            Result<bool>& result,
            const std::string_view& value,
            const std::string_view& prefix
        );
        
        void is_suffix_found(
            Result<bool>& result,
            const std::string_view& value,
            const std::string_view& suffix
        );
        
        void is_substring_found(
            Result<bool>& result,
            const std::string_view& value,
            const std::string_view& substring
        );
        
        void is_base64(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_utf8(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_utf16(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_slug(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_hex(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_uuid4(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_uuid6(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_ipv4(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_ipv6(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_url(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_uri(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_mac_address(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_hostname(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_domain(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_port_in_range(
            Result<bool>& result,
            const uint32_t& port,
            const uint32_t& minimum = 1,
            const uint32_t& maximum = 65535
        );
        
        void is_port_in_range(
            Result<bool>& result,
            const std::string_view& port,
            const uint32_t& minimum = 1,
            const uint32_t& maximum = 65535
        );
        
        void is_alpanumeric(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_decimal(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_date(
            Result<bool>& result,
            const std::string_view& value,
            const std::string_view& format
        );
        
        void is_time(
            Result<bool>& result,
            const std::string_view& value,
            const std::string_view& format
        );
        
        void is_datetime(
            Result<bool>& result,
            const std::string_view& value,
            const std::string_view& format
        );
        
        void is_past_date(
            Result<bool>& result,
            const std::string_view& value,
            const std::string_view& format
        );
        
        void is_future_date(
            Result<bool>& result,
            const std::string_view& value,
            const std::string_view& format
        );
        
        void is_unix(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_iso8601(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_utc(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_leap_year(
            Result<bool>& result,
            const int64_t& value
        );
        
        void is_leap_year(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_within_inclusive_range(
            Result<bool>& result,
            const int64_t& minimum,
            const int64_t& maximum
        );
        
        void is_within_inclusive_range(
            Result<bool>& result,
            const std::string_view& minimum,
            const std::string_view& maximum
        );
        
        void is_within_exclusive_range(
            Result<bool>& result,
            const int64_t& minimum,
            const int64_t& maximum
        );
        
        void is_within_exclusive_range(
            Result<bool>& result,
            const std::string_view& minimum,
            const std::string_view& maximum
        );
        
        void is_even(
            Result<bool>& result,
            const int64_t& value
        );
        
        void is_even(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_odd(
            Result<bool>& result,
            const int64_t& value
        );
        
        void is_odd(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_prime(
            Result<bool>& result,
            const int64_t& value
        );
        
        void is_prime(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_divisible_by(
            Result<bool>& result,
            const int64_t& value,
            const int64_t& divisor
        );
        
        void is_divisible_by(
            Result<bool>& result,
            const std::string_view& value,
            const std::string_view& divisor
        );
        
        void is_percentage(
            Result<bool>& result,
            const double& value
        );
        
        void is_percentage(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_latitude(
            Result<bool>& result,
            const double& value
        );
        
        void is_latitude(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_longitude(
            Result<bool>& result,
            const double& value
        );
        
        void is_longitude(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_coordinate(
            Result<bool>& result,
            const double& latitude,
            const double& longitude
        );
        
        void is_coordinate(
            Result<bool>& result,
            const std::string_view& latitude,
            const std::string_view& longitude
        );
        
        void is_country_code(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_currency_code(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_language_code(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_hex_color(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_rgb_color(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_rgba_color(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_rgb_color(
            Result<bool>& result,
            const uint8_t& red,
            const uint8_t& green,
            const uint8_t& blue
        );
        
        void is_rgba_color(
            Result<bool>& result,
            const uint8_t& red,
            const uint8_t& green,
            const uint8_t& blue,
            const uint8_t& alpha
        );
        
        void is_file_path(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_file_name(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_file_extension(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_file_extension_allowed(
            Result<bool>& result,
            const std::string_view& value,
            const std::set<std::string>& allowed_extensions
        );
        
        void is_mime_type(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_base64_image(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_data_uri(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_file_size_allowed(
            Result<bool>& result,
            const std::size_t& value,
            const std::size_t& maximum_size
        );
        
        void is_file_type_allowed(
            Result<bool>& result,
            const std::string_view& value,
            const std::set<std::string>& allowed_types
        );
        
        void is_age(
            Result<bool>& result,
            const uint8_t& value
        );
        
        void is_age(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_gender(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_phone_number(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_e164_phone_number(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_country_calling_code(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_address_line(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_full_name(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_first_name(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_middle_name(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_middle_initial(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_adult(
            Result<bool>& result,
            const uint8_t& age,
            const uint8_t& minimum_age = 18
        );
        
        void is_juvenile(
            Result<bool>& result,
            const uint8_t& age
        );
        
        void is_child(
            Result<bool>& result,
            const uint8_t& age
        );
        
        void is_email(
            Result<bool>& result,
            const std::string_view& value
        );
        
        void is_strong_password(
            Result<bool>& result,
            const std::string_view& value,
            const ValidationPasswordRules& rules
        );
        
        void is_character_repeated(
            Result<bool>& result,
            const std::string_view& value,
            const std::size_t& threshold
        );
        
        void is_blacklisted_word_found(
            Result<bool>& result,
            const std::string_view& value,
            const std::vector<std::string>& blacklist
        );

        template<std::ranges::input_range Range,
        typename Predicate>
            void is_valid_range(
                Result<bool>& result,
                const Range& range,
                Predicate predicate
        );

        template<typename Type>
        void is_enum_value(
            Result<bool>& result,
            Type value,
            std::span<const Type> allowed
        );

        template<typename Type>
        void is_unique(
            Result<bool>& result,
            const std::vector<Type>& values
        );

        template<typename Type>
        void is_sorted(
            Result<bool>& result,
            const std::vector<Type>& values
        );

        template<typename Type>
        void is_empty(
            Result<bool>& result,
            const std::vector<Type>& values
        );

        template<typename Type>
        void is_found(
            Result<bool>& result,
            const std::vector<Type>& values,
            std::function<bool(
            const Type&)> predicate
        );

        static Validators& get_instance();

        static void get_instance(
            Result<Validators*>& result
        );

    protected:
        Validators();
        
        ~Validators();
        
        Validators(
            const Validators& instance
        ) = delete;
        
        Validators(
            Validators&& instance
        ) noexcept = delete;
        
        Validators& operator = (
            Validators&& instance
            ) = delete;
        
        Validators& operator = (
            const Validators& instance
            ) = delete;
    };

    template<std::ranges::input_range Range, typename Predicate>
    bool Validators::is_valid_range(const Range& range, Predicate predicate)
    {
        return std::ranges::all_of(range, predicate);
    }

    template<typename Type>
    bool Validators::is_enum_value(Type value, std::span<const Type> allowed)
    {
        return std::ranges::find(allowed, value) != allowed.end();
    }

    template<typename Type>
    bool Validators::is_unique(const std::vector<Type>& values)
    {
        std::unordered_set<Type> seen;
        for (const Type& item : values)
        {
            if (!seen.insert(item).second)
            {
                return false;
            }
        }
        return true;
    }

    template<typename Type>
    bool Validators::is_sorted(const std::vector<Type>& values)
    {
        return std::ranges::is_sorted(values);
    }

    template<typename Type>
    bool Validators::is_empty(const std::vector<Type>& values)
    {
        return values.empty();
    }

    template<typename Type>
    bool Validators::is_found(const std::vector<Type>& values, std::function<bool(const Type&)> predicate)
    {
        return std::ranges::any_of(values, predicate);
    }

    template bool Validators::is_empty<int>(const std::vector<int>&);
    
    template bool Validators::is_unique<int>(const std::vector<int>&);
    
    template bool Validators::is_sorted<int>(const std::vector<int>&);
    
    template bool Validators::is_enum_value<int>(int, std::span<const int>);
    
    template bool Validators::is_found<int>(const std::vector<int>&, std::function<bool(const int&)>);
    
    template bool Validators::is_valid_range<std::vector<int>, bool(*)(int)>(const std::vector<int>&, bool(*)(int));

    template<std::ranges::input_range Range, typename Predicate>
                void Validators::is_valid_range(Result<bool>& result,
        const Range& range,
        Predicate predicate)
    {
        result.set_to_good_status_with_value(std::ranges::all_of(range, predicate));
    }

    template<typename Type>
                void Validators::is_enum_value(Result<bool>& result,
        Type value,
        std::span<const Type> allowed)
    {
        result.set_to_good_status_with_value(std::ranges::find(allowed, value) != allowed.end());
    }

    template<typename Type>
                void Validators::is_unique(Result<bool>& result,
        const std::vector<Type>& values)
    {
        std::unordered_set<Type> seen;
        for (const Type& item : values)
        {
            if (!seen.insert(item).second)
            {
                result.set_to_good_status_with_value(false);
                return;
            }
        }
        result.set_to_good_status_with_value(true);
    }

    template<typename Type>
                void Validators::is_sorted(Result<bool>& result,
        const std::vector<Type>& values)
    {
        result.set_to_good_status_with_value(std::ranges::is_sorted(values));
    }

    template<typename Type>
                void Validators::is_empty(Result<bool>& result,
        const std::vector<Type>& values)
    {
        result.set_to_good_status_with_value(values.empty());
    }

    template<typename Type>
                void Validators::is_found(Result<bool>& result,
        const std::vector<Type>& values,
        std::function<bool(const Type&)> predicate)
    {
        result.set_to_good_status_with_value(std::ranges::any_of(values, predicate));
    }

    template void Validators::is_valid_range<std::vector<int>, bool(*)(int)>(
        Result<bool>&, const std::vector<int>&, bool(*)(int));
    
        template void Validators::is_enum_value<int>(Result<bool>&, int,
        std::span<const int>);

        template void Validators::is_unique<int>(Result<bool>&, const std::vector<int>&);
    
        template void Validators::is_sorted<int>(Result<bool>&, const std::vector<int>&);
    
        template void Validators::is_empty<int>(Result<bool>&, const std::vector<int>&);
    
        template void Validators::is_found<int>(Result<bool>&,
        
        const std::vector<int>&, std::function<bool(const int&)>);

    inline static Validators& VALIDATORS =
        Validators::get_instance();

}
