#pragma once

#include "utilities.hpp"
#include "regular_expression.hpp"

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
        bool is_not_empty(const std::string_view& value);
        
        bool is_empty(const std::string_view& value);
        
        bool is_lowercase(const std::string_view& value);
        
        bool is_uppercase(const std::string_view& value);
        
        bool is_first_letter_uppercase(const std::string_view& value);
        
        bool is_prefix_found(const std::string_view& value, const std::string_view& prefix);
        
        bool is_suffix_found(const std::string_view& value, const std::string_view& suffix);
        
        bool is_substring_found(const std::string_view& value, const std::string_view& substring);
        
        bool is_base64(const std::string_view& value);
        
        bool is_utf8(const std::string_view& value);
        
        bool is_utf16(const std::string_view& value);
        
        bool is_slug(const std::string_view& value);
        
        bool is_hex(const std::string_view& value);
        
        bool is_uuid4(const std::string_view& value);
        
        bool is_uuid6(const std::string_view& value);
        
        bool is_ipv4(const std::string_view& value);
        
        bool is_ipv6(const std::string_view& value);
        
        bool is_url(const std::string_view& value);
        
        bool is_uri(const std::string_view& value);
        
        bool is_mac_address(const std::string_view& value);
        
        bool is_hostname(const std::string_view& value);
        
        bool is_domain(const std::string_view& value);
        
        bool is_port_in_range(const uint32_t& port, const uint32_t& minimum = 1, const uint32_t& maximum = 65535);        

        bool is_port_in_range(const std::string_view& port, const uint32_t& minimum = 1, const uint32_t& maximum = 65535);
        
        bool is_alpanumeric(const std::string_view& value);
        
        bool is_decimal(const std::string_view& value);
        
        bool is_date(const std::string_view& value, const std::string_view& format);
        
        bool is_time(const std::string_view& value, const std::string_view& format);
        
        bool is_datetime(const std::string_view& value, const std::string_view& format);
        
        bool is_past_date(const std::string_view& value, const std::string_view& format);
        
        bool is_future_date(const std::string_view& value, const std::string_view& format);
        
        bool is_unix(const std::string_view& value);
        
        bool is_iso8601(const std::string_view& value);
        
        bool is_utc(const std::string_view& value);
        
        bool is_leap_year(const int64_t& value);
        
        bool is_leap_year(const std::string_view& value);        
        
        bool is_within_inclusive_range(const int64_t& minimum, const int64_t& maximum);
        
        bool is_within_inclusive_range(const std::string_view& minimum, const std::string_view& maximum);
        
        bool is_within_exclusive_range(const int64_t& minimum, const int64_t& maximum);
        
        bool is_within_exclusive_range(const std::string_view& minimum, const std::string_view& maximum);
        
        bool is_even(const int64_t& value);
        
        bool is_even(const std::string_view& value);
        
        bool is_odd(const int64_t& value);
        
        bool is_odd(const std::string_view& value);
        
        bool is_prime(const int64_t& value);
        
        bool is_prime(const std::string_view& value);
        
        bool is_divisible_by(const int64_t& value, const int64_t& divisor);
        
        bool is_divisible_by(const std::string_view& value, const std::string_view& divisor);
        
        bool is_percentage(const double& value);
        
        bool is_percentage(const std::string_view& value);
        
        bool is_latitude(const double& value);
        
        bool is_latitude(const std::string_view& value);
        
        bool is_longitude(const double& value);
        
        bool is_longitude(const std::string_view& value);
        
        bool is_coordinate(const double& latitude, const double& longitude);
        
        bool is_coordinate(const std::string_view& latitude, const std::string_view& longitude);
        
        bool is_country_code(const std::string_view& value);
        
        bool is_currency_code(const std::string_view& value);
        
        bool is_language_code(const std::string_view& value);
        
        bool is_hex_color(const std::string_view& value);
        
        bool is_rgb_color(const std::string_view& value);
        
        bool is_rgba_color(const std::string_view& value);
        
        bool is_rgb_color(const uint8_t& red, const uint8_t& green, const uint8_t& blue);
        
        bool is_rgba_color(const uint8_t& red, const uint8_t& green, const uint8_t& blue, const uint8_t& alpha);
        
        bool is_file_path(const std::string_view& value);
        
        bool is_file_name(const std::string_view& value);
        
        bool is_file_extension(const std::string_view& value);
        
        bool is_file_extension_allowed(const std::string_view& value, const std::set<std::string>& allowed_extensions);
        
        bool is_mime_type(const std::string_view& value);
        
        bool is_base64_image(const std::string_view& value);
        
        bool is_data_uri(const std::string_view& value);
        
        bool is_file_size_allowed(const std::size_t& value, const std::size_t& maximum_size);
        
        bool is_file_type_allowed(const std::string_view& value, const std::set<std::string>& allowed_types);
        
        bool is_age(const uint8_t& value);
        
        bool is_age(const std::string_view& value);
        
        bool is_gender(const std::string_view& value);
        
        bool is_phone_number(const std::string_view& value);
        
        bool is_e164_phone_number(const std::string_view& value);
        
        bool is_country_calling_code(const std::string_view& value);
        
        bool is_address_line(const std::string_view& value);
        
        bool is_full_name(const std::string_view& value);
        
        bool is_first_name(const std::string_view& value);
        
        bool is_middle_name(const std::string_view& value);
        
        bool is_middle_initial(const std::string_view& value);
        
        bool is_adult(const uint8_t& age, const uint8_t& minimum_age = 18);
        
        bool is_juvenile(const uint8_t& age);
        
        bool is_child(const uint8_t& age);
        
        bool is_email(const std::string_view& value);
        
        bool is_strong_password(const std::string_view& value, const ValidationPasswordRules& rules);
        
        bool is_character_repeated(const std::string_view& value, const std::size_t& threshold);
        
        bool is_blacklisted_word_found(const std::string_view& value, const std::vector<std::string>& blacklist);
        
        template<std::ranges::input_range Range, typename Predicate>
        bool is_valid_range(const Range& range, Predicate predicate);
        
        template<typename Type>
        bool is_enum_value(Type value, std::span<const Type> allowed);
        
        template<typename Type>
        bool is_unique(const std::vector<Type>& values);
        
        template<typename Type>
        bool is_sorted(const std::vector<Type>& values);
        
        template<typename Type>
        bool is_empty(const std::vector<Type>& values);
        
        template<typename Type>
        bool is_found(const std::vector<Type>& values, std::function<bool(const Type&)> predicate);
       
        static Validators& get_instance();

    protected:
        Validators();
        
        ~Validators() = default;
        
        Validators(const Validators&) = delete;
        
        Validators(Validators&&) noexcept = delete;
        
        Validators& operator = (Validators&&) = delete;
        
        Validators& operator = (const Validators&) = delete;
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

    inline static Validators& VALIDATORS =
        Validators::get_instance();

    template bool Validators::is_empty<int>(const std::vector<int>&);
    template bool Validators::is_unique<int>(const std::vector<int>&);
    template bool Validators::is_sorted<int>(const std::vector<int>&);
    template bool Validators::is_enum_value<int>(int, std::span<const int>);
    template bool Validators::is_found<int>(const std::vector<int>&, std::function<bool(const int&)>);
    template bool Validators::is_valid_range<std::vector<int>, bool(*)(int)>(const std::vector<int>&, bool(*)(int));
}
