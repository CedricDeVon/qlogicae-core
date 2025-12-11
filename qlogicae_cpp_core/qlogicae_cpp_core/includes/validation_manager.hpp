#pragma once

#include "result.hpp"
#include "instance_manager.hpp"
#include "validation_manager_password_rules.hpp"

namespace QLogicaeCppCore
{    
    class ValidationManager
    {
    public:        
        ValidationManager();

        ~ValidationManager();

        ValidationManager(
            const ValidationManager& instance
        ) = delete;

        ValidationManager(
            ValidationManager&& instance
        ) noexcept = delete;

        ValidationManager& operator = (
            ValidationManager&& instance
        ) = delete;

        ValidationManager& operator = (
            const ValidationManager& instance
        ) = delete;

        void construct(
            Result<bool>& result
        );

        void destruct(
            Result<bool>& result
        );

        void match_std_regex(
            Result<bool>& result,
            const std::string_view& input,
            const std::string_view& pattern
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
            const uint32_t& port
        );

        void is_port_in_range(
            Result<bool>& result,
            const uint32_t& port,
            const uint32_t& minimum,
            const uint32_t& maximum
        );
        
        void is_port_in_range(
            Result<bool>& result,
            const std::string_view& port
        );

        void is_port_in_range(
            Result<bool>& result,
            const std::string_view& port,
            const uint32_t& minimum,
            const uint32_t& maximum
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
            const uint8_t& age
        );

        void is_adult(
            Result<bool>& result,
            const uint8_t& age,
            const uint8_t& minimum_age
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
            const ValidationManagerPasswordRules& rules
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
    };

    template<std::ranges::input_range Range, typename Predicate>
    void ValidationManager::is_valid_range(
        Result<bool>& result,
        const Range& range,
        Predicate predicate
    )
    {
        result.set_to_good_status_with_value(
            std::ranges::all_of(range, predicate)
        );
    }

    template<typename Type>
    void ValidationManager::is_enum_value(
        Result<bool>& result,
        Type value,
        std::span<const Type> allowed
    )
    {
        result.set_to_good_status_with_value(
            std::ranges::find(allowed, value) != allowed.end()
        );
    }

    template<typename Type>
    void ValidationManager::is_unique(
        Result<bool>& result,
        const std::vector<Type>& values
    )
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
    void ValidationManager::is_sorted(
        Result<bool>& result,
        const std::vector<Type>& values
    )
    {
        result.set_to_good_status_with_value(
            std::ranges::is_sorted(values)
        );
    }

    template<typename Type>
    void ValidationManager::is_empty(
        Result<bool>& result,
        const std::vector<Type>& values
    )
    {
        result.set_to_good_status_with_value(values.empty());
    }

    template<typename Type>
    void ValidationManager::is_found(
        Result<bool>& result,
        const std::vector<Type>& values,
        std::function<bool(const Type&)> predicate
    )
    {
        result.set_to_good_status_with_value(std::ranges::any_of(values, predicate));
    }

    template void ValidationManager::is_valid_range<std::vector<int>, bool(*)(int)>(
        Result<bool>&,
        const std::vector<int>&, bool(*)(int)
    );
    
    template void ValidationManager::is_enum_value<int>(
        Result<bool>&, int,
        std::span<const int>
    );

    template void ValidationManager::is_unique<int>(
        Result<bool>&,
        const std::vector<int>&
    );
    
    template void ValidationManager::is_sorted<int>(
        Result<bool>&,
        const std::vector<int>&
    );
    
    template void ValidationManager::is_empty<int>(
        Result<bool>&,
        const std::vector<int>&
    );
    
    template void ValidationManager::is_found<int>(
        Result<bool>&,
        const std::vector<int>&, std::function<bool(const int&)>
    );

    inline static ValidationManager& VALIDATION_MANAGER =
        INSTANCE_MANAGER.get_instance<ValidationManager>();
}
