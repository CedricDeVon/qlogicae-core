#include "pch.hpp"

#include "validators.hpp"

namespace QLogicaeCore
{
    Validators::Validators()
    {
        
    }

    static bool match_std_regex(const std::string_view& input, const std::string_view& pattern)
    {
        try
        {
            return std::regex_match(input.begin(), input.end(), std::regex(pattern.data()));
        }
        catch (const std::regex_error&)
        {
            return false;
        }
    }

    bool Validators::is_not_empty(const std::string_view& value)
    {
        return !value.empty();
    }

    bool Validators::is_empty(const std::string_view& value)
    {
        return value.empty();
    }

    bool Validators::is_lowercase(const std::string_view& value)
    {
        if (value.empty())
        {
            return false;
        }
        return std::ranges::all_of(value, [](char character)
            {
                return std::islower(static_cast<unsigned char>(character));
            });
    }

    bool Validators::is_uppercase(const std::string_view& value)
    {
        if (value.empty())
        {
            return false;
        }
        return std::ranges::all_of(value, [](char character)
            {
                return std::isupper(static_cast<unsigned char>(character));
            });
    }

    bool Validators::is_first_letter_uppercase(const std::string_view& value)
    {
        if (value.empty())
        {
            return false;
        }
        return std::isupper(static_cast<unsigned char>(value.front()));
    }

    bool Validators::is_prefix_found(const std::string_view& value, const std::string_view& prefix)
    {
        if (value.empty() || prefix.empty())
        {
            return false;
        }
        return value.starts_with(prefix);
    }

    bool Validators::is_suffix_found(const std::string_view& value, const std::string_view& suffix)
    {
        if (value.empty() || suffix.empty())
        {
            return false;
        }
        return value.ends_with(suffix);
    }

    bool Validators::is_substring_found(const std::string_view& value, const std::string_view& substring)
    {
        if (value.empty() || substring.empty())
        {
            return false;
        }
        return value.find(substring) != std::string_view::npos;
    }

    bool Validators::is_port_in_range(const uint32_t& port, const uint32_t& minimum, const uint32_t& maximum)
    {
        return port >= minimum && port <= maximum;
    }

    bool Validators::is_port_in_range(const std::string_view& port, const uint32_t& minimum, const uint32_t& maximum)
    {
        uint32_t parsed_port = 0;
        auto [ptr, ec] = std::from_chars(port.data(), port.data() + port.size(), parsed_port);
        if (ec != std::errc())
        {
            return false;
        }
        return is_port_in_range(parsed_port, minimum, maximum);
    }

    bool Validators::is_alpanumeric(const std::string_view& value)
    {
        if (value.empty())
        {
            return false;
        }
        return std::ranges::all_of(value, [](char character)
            {
                return std::isalnum(static_cast<unsigned char>(character));
            });
    }

    bool Validators::is_decimal(const std::string_view& value)
    {
        if (value.empty())
        {
            return false;
        }
        bool has_decimal = false;
        for (char character : value)
        {
            if (character == '.')
            {
                if (has_decimal)
                {
                    return false;
                }
                has_decimal = true;
                continue;
            }
            if (!std::isdigit(static_cast<unsigned char>(character)))
            {
                return false;
            }
        }
        return true;
    }

    bool Validators::is_utf8(const std::string_view& value)
    {
        return std::string(value).find('\xC0') == std::string::npos;
    }

    bool Validators::is_utf16(const std::string_view& value)
    {
        if (value.size() < 2)
        {
            return false;
        }
        unsigned char byte1 = static_cast<unsigned char>(value[0]);
        unsigned char byte2 = static_cast<unsigned char>(value[1]);
        return (byte1 == 0xFF && byte2 == 0xFE) || (byte1 == 0xFE && byte2 == 0xFF);
    }

    bool Validators::is_time(const std::string_view& value, const std::string_view& format)
    {
        return is_date(value, format);
    }

    bool Validators::is_datetime(const std::string_view& value, const std::string_view& format)
    {
        return is_date(value, format);
    }

    bool Validators::is_date(const std::string_view& value, const std::string_view& format)
    {
        if (format != "%Y-%m-%d" || value.size() != 10 || value[4] != '-' || value[7] != '-')
        {
            return false;
        }
        int year = 0;
        int month = 0;
        int day = 0;
        auto parse = [](std::string_view str, int& out)
            {
                return std::from_chars(str.data(), str.data() + str.size(), out).ec == std::errc();
            };
        return parse(value.substr(0, 4), year) &&
            parse(value.substr(5, 2), month) &&
            parse(value.substr(8, 2), day) &&
            (year > 0 && month >= 1 && month <= 12 && day >= 1 && day <= 31);
    }

    bool Validators::is_past_date(const std::string_view& value, const std::string_view& format)
    {
        if (!is_date(value, format))
        {
            return false;
        }
        int year = 0;
        int month = 0;
        int day = 0;
        std::from_chars(value.data(), value.data() + 4, year);
        std::from_chars(value.data() + 5, value.data() + 7, month);
        std::from_chars(value.data() + 8, value.data() + 10, day);
        std::tm time = {};
        time.tm_year = year - 1900;
        time.tm_mon = month - 1;
        time.tm_mday = day;
        std::time_t input_time = std::mktime(&time);
        return input_time != -1 && input_time < std::time(nullptr);
    }

    bool Validators::is_future_date(const std::string_view& value, const std::string_view& format)
    {
        if (!is_date(value, format))
        {
            return false;
        }
        int year = 0;
        int month = 0;
        int day = 0;
        std::from_chars(value.data(), value.data() + 4, year);
        std::from_chars(value.data() + 5, value.data() + 7, month);
        std::from_chars(value.data() + 8, value.data() + 10, day);
        std::tm time = {};
        time.tm_year = year - 1900;
        time.tm_mon = month - 1;
        time.tm_mday = day;
        std::time_t input_time = std::mktime(&time);
        return input_time != -1 && input_time > std::time(nullptr);
    }

    bool Validators::is_unix(const std::string_view& value)
    {
        int64_t timestamp = 0;
        auto [ptr, ec] = std::from_chars(value.data(), value.data() + value.size(), timestamp);
        if (ec != std::errc())
        {
            return false;
        }
        return timestamp >= 0;
    }

    bool Validators::is_utc(const std::string_view& value)
    {
        return value.ends_with("Z");
    }

    bool Validators::is_leap_year(const int64_t& value)
    {
        if (value < 0)
        {
            return false;
        }
        return (value % 4 == 0 && value % 100 != 0) || (value % 400 == 0);
    }

    bool Validators::is_leap_year(const std::string_view& value)
    {
        int64_t year = 0;
        auto [ptr, ec] = std::from_chars(value.data(), value.data() + value.size(), year);
        if (ec != std::errc())
        {
            return false;
        }
        return is_leap_year(year);
    }


    bool Validators::is_within_inclusive_range(const int64_t& minimum, const int64_t& maximum)
    {
        return minimum <= maximum;
    }

    bool Validators::is_within_inclusive_range(const std::string_view& minimum, const std::string_view& maximum)
    {
        int64_t min_value = 0;
        int64_t max_value = 0;
        if (std::from_chars(minimum.data(), minimum.data() + minimum.size(), min_value).ec != std::errc() ||
            std::from_chars(maximum.data(), maximum.data() + maximum.size(), max_value).ec != std::errc())
        {
            return false;
        }
        return is_within_inclusive_range(min_value, max_value);
    }

    bool Validators::is_within_exclusive_range(const int64_t& minimum, const int64_t& maximum)
    {
        return minimum < maximum;
    }

    bool Validators::is_within_exclusive_range(const std::string_view& minimum, const std::string_view& maximum)
    {
        int64_t min_value = 0;
        int64_t max_value = 0;
        if (std::from_chars(minimum.data(), minimum.data() + minimum.size(), min_value).ec != std::errc() ||
            std::from_chars(maximum.data(), maximum.data() + maximum.size(), max_value).ec != std::errc())
        {
            return false;
        }
        return is_within_exclusive_range(min_value, max_value);
    }

    bool Validators::is_even(const int64_t& value)
    {
        return value % 2 == 0;
    }

    bool Validators::is_even(const std::string_view& value)
    {
        int64_t number = 0;
        if (std::from_chars(value.data(), value.data() + value.size(), number).ec != std::errc())
        {
            return false;
        }
        return is_even(number);
    }

    bool Validators::is_odd(const int64_t& value)
    {
        return value % 2 != 0;
    }

    bool Validators::is_odd(const std::string_view& value)
    {
        int64_t number = 0;
        if (std::from_chars(value.data(), value.data() + value.size(), number).ec != std::errc())
        {
            return false;
        }
        return is_odd(number);
    }

    bool Validators::is_prime(const int64_t& value)
    {
        if (value < 2)
        {
            return false;
        }
        for (int64_t i = 2; i <= static_cast<int64_t>(std::sqrt(value)); ++i)
        {
            if (value % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    bool Validators::is_prime(const std::string_view& value)
    {
        int64_t number = 0;
        if (std::from_chars(value.data(), value.data() + value.size(), number).ec != std::errc())
        {
            return false;
        }
        return is_prime(number);
    }

    bool Validators::is_divisible_by(const int64_t& value, const int64_t& divisor)
    {
        if (divisor == 0)
        {
            return false;
        }
        return value % divisor == 0;
    }

    bool Validators::is_divisible_by(const std::string_view& value, const std::string_view& divisor)
    {
        int64_t val = 0;
        int64_t div = 0;
        if (std::from_chars(value.data(), value.data() + value.size(), val).ec != std::errc() ||
            std::from_chars(divisor.data(), divisor.data() + divisor.size(), div).ec != std::errc())
        {
            return false;
        }
        return is_divisible_by(val, div);
    }

    bool Validators::is_percentage(const double& value)
    {
        return value >= 0.0 && value <= 100.0;
    }

    bool Validators::is_percentage(const std::string_view& value)
    {
        double number = 0.0;
        if (std::from_chars(value.data(), value.data() + value.size(), number).ec != std::errc())
        {
            return false;
        }
        return is_percentage(number);
    }


    bool Validators::is_latitude(const double& value)
    {
        return value >= -90.0 && value <= 90.0;
    }

    bool Validators::is_latitude(const std::string_view& value)
    {
        double number = 0.0;
        if (std::from_chars(value.data(), value.data() + value.size(), number).ec != std::errc())
        {
            return false;
        }
        return is_latitude(number);
    }

    bool Validators::is_longitude(const double& value)
    {
        return value >= -180.0 && value <= 180.0;
    }

    bool Validators::is_longitude(const std::string_view& value)
    {
        double number = 0.0;
        if (std::from_chars(value.data(), value.data() + value.size(), number).ec != std::errc())
        {
            return false;
        }
        return is_longitude(number);
    }

    bool Validators::is_coordinate(const double& latitude, const double& longitude)
    {
        return is_latitude(latitude) && is_longitude(longitude);
    }

    bool Validators::is_coordinate(const std::string_view& latitude, const std::string_view& longitude)
    {
        return is_latitude(latitude) && is_longitude(longitude);
    }

    bool Validators::is_country_code(const std::string_view& value)
    {
        return value.size() == 2 &&
            std::ranges::all_of(value, [](char character)
                {
                    return std::isalpha(static_cast<unsigned char>(character));
                });
    }

    bool Validators::is_currency_code(const std::string_view& value)
    {
        return value.size() == 3 &&
            std::ranges::all_of(value, [](char character)
                {
                    return std::isalpha(static_cast<unsigned char>(character));
                });
    }

    bool Validators::is_language_code(const std::string_view& value)
    {
        return value.size() >= 2 && value.size() <= 3 &&
            std::ranges::all_of(value, [](char character)
                {
                    return std::isalpha(static_cast<unsigned char>(character));
                });
    }

    bool Validators::is_rgb_color(const uint8_t& red, const uint8_t& green, const uint8_t& blue)
    {
        return red <= 255 && green <= 255 && blue <= 255;
    }

    bool Validators::is_rgba_color(const uint8_t& red, const uint8_t& green, const uint8_t& blue, const uint8_t& alpha)
    {
        return red <= 255 && green <= 255 && blue <= 255 && alpha <= 255;
    }

    bool Validators::is_iso8601(const std::string_view& value)
    {
        return match_std_regex(value, R"(^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(Z|[+-]\d{2}:\d{2})?$)");
    }

    bool Validators::is_hex_color(const std::string_view& value)
    {
        return match_std_regex(value, R"(^#(?:[0-9a-fA-F]{3}){1,2}$)");
    }

    bool Validators::is_base64(const std::string_view& value)
    {
        return match_std_regex(value, R"(^([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{2}==|[A-Za-z0-9+/]{3}=)?$)");
    }

    bool Validators::is_slug(const std::string_view& value)
    {
        return match_std_regex(value, R"(^[a-z0-9]+(?:-[a-z0-9]+)*$)");
    }

    bool Validators::is_hex(const std::string_view& value)
    {
        return match_std_regex(value, R"(^(0x)?[0-9a-fA-F]+$)");
    }

    bool Validators::is_uuid4(const std::string_view& value)
    {
        return match_std_regex(value, R"(^[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-4[a-fA-F0-9]{3}-[89abAB][a-fA-F0-9]{3}-[a-fA-F0-9]{12}$)");
    }

    bool Validators::is_uuid6(const std::string_view& value)
    {
        return match_std_regex(value, R"(^[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-6[a-fA-F0-9]{3}-[89abAB][a-fA-F0-9]{3}-[a-fA-F0-9]{12}$)");
    }

    bool Validators::is_ipv4(const std::string_view& value)
    {
        return match_std_regex(value, R"(^((25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)\.){3}(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)$)");
    }

    bool Validators::is_ipv6(const std::string_view& value)
    {
        return match_std_regex(value, R"(^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$)");
    }

    bool Validators::is_url(const std::string_view& value)
    {
        return match_std_regex(value, R"(^https?:\/\/(?:www\.)?[a-zA-Z0-9.-]+(?:\:\d+)?(?:\/\S*)?$)");
    }

    bool Validators::is_uri(const std::string_view& value)
    {
        return match_std_regex(value,
            R"(^[a-zA-Z][a-zA-Z0-9+.-]*:\/\/[^\s\/?#]+(?:[\/?#][^\s]*)?$)");
    }

    bool Validators::is_mac_address(const std::string_view& value)
    {
        return match_std_regex(value, R"(^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$)");
    }

    bool Validators::is_hostname(const std::string_view& value)
    {
        return match_std_regex(value, R"(^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\-]*[A-Za-z0-9])$)");
    }

    bool Validators::is_domain(const std::string_view& value)
    {
        return match_std_regex(value, R"(^([a-zA-Z0-9]+(-[a-zA-Z0-9]+)*\.)+[a-zA-Z]{2,}$)");
    }

    bool Validators::is_rgb_color(const std::string_view& value)
    {
        return match_std_regex(value, R"(^rgb\((\s*\d{1,3}\s*,){2}\s*\d{1,3}\s*\)$)");
    }

    bool Validators::is_rgba_color(const std::string_view& value)
    {
        return match_std_regex(value, R"(^rgba\((\s*\d{1,3}\s*,){3}\s*(0|1|0?\.\d+)\s*\)$)");
    }

    bool Validators::is_file_path(const std::string_view& value)
    {
        return match_std_regex(value,
            R"(^(([a-zA-Z]:\\|\/)?([\w\-. ]+([\/\\][\w\-. ]+)*))$)");
    }

    bool Validators::is_file_name(const std::string_view& value)
    {
        return match_std_regex(value, R"(^[\w,\s-]+\.[A-Za-z]{1,6}$)");
    }

    bool Validators::is_file_extension(const std::string_view& value)
    {
        return match_std_regex(value, R"(^[a-zA-Z0-9]+$)");
    }

    bool Validators::is_file_extension_allowed(const std::string_view& value, const std::set<std::string>& allowed_extensions)
    {
        return allowed_extensions.contains(std::string(value));
    }

    bool Validators::is_mime_type(const std::string_view& value)
    {
        return match_std_regex(value,
            R"(^(application|audio|font|example|image|message|model|multipart|text|video|x-[a-z0-9]+)\/[a-zA-Z0-9!#$&^_.+-]+$)");
    }

    bool Validators::is_base64_image(const std::string_view& value)
    {
        return match_std_regex(value, R"(^data:image\/(png|jpeg|jpg|gif);base64,([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{2}==|[A-Za-z0-9+/]{3}=)?$)");
    }

    bool Validators::is_data_uri(const std::string_view& value)
    {
        return match_std_regex(value, R"(^data:[a-zA-Z0-9!#$&^_.+-]+\/[a-zA-Z0-9!#$&^_.+-]+;base64,([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{2}==|[A-Za-z0-9+/]{3}=)?$)");
    }

    bool Validators::is_phone_number(const std::string_view& value)
    {
        return match_std_regex(value, R"(^\+?(\d{1,3})?\s?(\(\d{3}\)|\d{3})[-.\s]?\d{3}[-.\s]?\d{4}$)");
    }

    bool Validators::is_e164_phone_number(const std::string_view& value)
    {
        return match_std_regex(value, R"(^\+\d{1,15}$)");
    }

    bool Validators::is_country_calling_code(const std::string_view& value)
    {
        return match_std_regex(value, R"(^\+\d{1,3}$)");
    }

    bool Validators::is_full_name(const std::string_view& value)
    {
        return match_std_regex(value, R"(^[a-zA-Z]+([ '-][a-zA-Z]+)*$)");
    }

    bool Validators::is_email(const std::string_view& value)
    {
        return match_std_regex(value, R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    }

    bool Validators::is_file_size_allowed(const std::size_t& value, const std::size_t& maximum_size)
    {
        return value <= maximum_size;
    }

    bool Validators::is_file_type_allowed(const std::string_view& value, const std::set<std::string>& allowed_types)
    {
        return allowed_types.contains(std::string(value));
    }

    bool Validators::is_age(const uint8_t& value)
    {
        return value <= 130;
    }

    bool Validators::is_age(const std::string_view& value)
    {
        uint8_t age = 0;
        if (std::from_chars(value.data(), value.data() + value.size(), age).ec != std::errc())
        {
            return false;
        }
        return is_age(age);
    }

    bool Validators::is_gender(const std::string_view& value)
    {
        std::string lower_case(value);
        std::ranges::transform(lower_case, lower_case.begin(), [](char c)
            {
                return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            });

        return lower_case == "m" || lower_case == "f" || lower_case == "o" ||
            lower_case == "male" || lower_case == "female" ||
            lower_case == "nonbinary" || lower_case == "other";
    }

    bool Validators::is_address_line(const std::string_view& value)
    {
        return value.size() >= 5 && value.size() <= 128;
    }

    bool Validators::is_first_name(const std::string_view& value)
    {
        return is_full_name(value);
    }

    bool Validators::is_middle_name(const std::string_view& value)
    {
        return is_full_name(value);
    }

    bool Validators::is_middle_initial(const std::string_view& value)
    {
        return value.size() == 1 && std::isalpha(static_cast<unsigned char>(value.front()));
    }

    bool Validators::is_adult(const uint8_t& age, const uint8_t& minimum_age)
    {
        return age >= minimum_age;
    }

    bool Validators::is_juvenile(const uint8_t& age)
    {
        return age < 18 && age >= 13;
    }

    bool Validators::is_child(const uint8_t& age)
    {
        return age < 13;
    }

    bool Validators::is_strong_password(const std::string_view& value, const ValidationPasswordRules& rules)
    {
        if (value.size() < rules.minimum_length || value.size() > rules.maximum_length)
        {
            return false;
        }

        bool has_upper = false;
        bool has_lower = false;
        bool has_digit = false;
        bool has_special = false;
        std::unordered_set<char> unique_chars;

        for (char c : value)
        {
            if (std::isupper(static_cast<unsigned char>(c))) has_upper = true;
            if (std::islower(static_cast<unsigned char>(c))) has_lower = true;
            if (std::isdigit(static_cast<unsigned char>(c))) has_digit = true;
            if (!std::isalnum(static_cast<unsigned char>(c))) has_special = true;
            unique_chars.insert(c);
        }

        if (rules.require_uppercase_characters && !has_upper) return false;
        if (rules.require_lowercase_characters && !has_lower) return false;
        if (rules.require_alpha_numerics && !has_digit) return false;
        if (rules.require_special_characters && !has_special) return false;
        if (rules.require_unique_characters && unique_chars.size() < value.size()) return false;

        return true;
    }

    bool Validators::is_character_repeated(const std::string_view& value, const std::size_t& threshold)
    {
        std::unordered_map<char, std::size_t> counts;
        for (char c : value)
        {
            if (++counts[c] > threshold)
            {
                return true;
            }
        }
        return false;
    }

    bool Validators::is_blacklisted_word_found(const std::string_view& value, const std::vector<std::string>& blacklist)
    {
        return std::ranges::any_of(blacklist, [&](const std::string& word)
            {
                return value.find(word) != std::string_view::npos;
            });
    }

    Validators& Validators::get_instance()
    {
        static Validators singleton_instance;
        return singleton_instance;
    }

    void Validators::is_not_empty(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(!value.empty());
    }

    void Validators::is_empty(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(value.empty());
    }

    void Validators::is_lowercase(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        if (value.empty())
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        bool ok = std::ranges::all_of(value, [](char character)
            {
                return std::islower(static_cast<unsigned char>(character));
            });

        result.set_to_good_status_with_value(ok);
    }

    void Validators::is_uppercase(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        if (value.empty())
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        bool ok = std::ranges::all_of(value, [](char character)
            {
                return std::isupper(static_cast<unsigned char>(character));
            });

        result.set_to_good_status_with_value(ok);
    }

    void Validators::is_first_letter_uppercase(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        if (value.empty())
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        result.set_to_good_status_with_value(
            std::isupper(static_cast<unsigned char>(value.front()))
        );
    }

    void Validators::is_prefix_found(
        Result<bool>& result,
        const std::string_view& value,
        const std::string_view& prefix
    )
    {
        if (value.empty() || prefix.empty())
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        result.set_to_good_status_with_value(value.starts_with(prefix));
    }

    void Validators::is_suffix_found(
        Result<bool>& result,
        const std::string_view& value,
        const std::string_view& suffix
    )
    {
        if (value.empty() || suffix.empty())
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        result.set_to_good_status_with_value(value.ends_with(suffix));
    }

    void Validators::is_substring_found(
        Result<bool>& result,
        const std::string_view& value,
        const std::string_view& substring
    )
    {
        if (value.empty() || substring.empty())
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        result.set_to_good_status_with_value(value.find(substring) !=
            std::string_view::npos);
    }

    void Validators::is_base64(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{2}==|[A-Za-z0-9+/]{3}=)?$)"));
    }

    void Validators::is_utf8(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(std::string(value).find('\xC0') ==
            std::string::npos);
    }

    void Validators::is_utf16(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        if (value.size() < 2)
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        unsigned char byte1 = static_cast<unsigned char>(value[0]);
        unsigned char byte2 = static_cast<unsigned char>(value[1]);
        result.set_to_good_status_with_value((byte1 == 0xFF && byte2 == 0xFE) ||
            (byte1 == 0xFE && byte2 == 0xFF));
    }

    void Validators::is_slug(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^[a-z0-9]+(?:-[a-z0-9]+)*$)"));
    }

    void Validators::is_hex(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^(0x)?[0-9a-fA-F]+$)"));
    }

    void Validators::is_uuid4(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-4[a-fA-F0-9]{3}-[89abAB][a-fA-F0-9]{3}-[a-fA-F0-9]{12}$)"));
    }

    void Validators::is_uuid6(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-6[a-fA-F0-9]{3}-[89abAB][a-fA-F0-9]{3}-[a-fA-F0-9]{12}$)"));
    }

    void Validators::is_ipv4(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^((25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)\.){3}(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)$)"));
    }

    void Validators::is_ipv6(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$)"));
    }

    void Validators::is_url(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^https?:\/\/(?:www\.)?[a-zA-Z0-9.-]+(?:\:\d+)?(?:\/\S*)?$)"));
    }

    void Validators::is_uri(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^[a-zA-Z][a-zA-Z0-9+.-]*:\/\/[^\s\/?#]+(?:[\/?#][^\s]*)?$)"));
    }

    void Validators::is_mac_address(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$)"));
    }

    void Validators::is_hostname(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\-]*[A-Za-z0-9])$)"));
    }

    void Validators::is_domain(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^([a-zA-Z0-9]+(-[a-zA-Z0-9]+)*\.)+[a-zA-Z]{2,}$)"));
    }

    void Validators::is_port_in_range(
        Result<bool>& result,
        const uint32_t& port,
        const uint32_t& minimum,
        const uint32_t& maximum)
    {
        result.set_to_good_status_with_value(port >= minimum && port <= maximum);
    }

    void Validators::is_port_in_range(
        Result<bool>& result,
        const std::string_view& port,
        const uint32_t& minimum,
        const uint32_t& maximum)
    {
        uint32_t parsed_port = 0;
        auto [ptr, ec] = std::from_chars(port.data(), port.data() + port.size(),
            parsed_port);
        if (ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        result.set_to_good_status_with_value(parsed_port >= minimum &&
            parsed_port <= maximum);
    }

    void Validators::is_alpanumeric(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        if (value.empty())
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        bool ok = std::ranges::all_of(value, [](char character)
            {
                return std::isalnum(static_cast<unsigned char>(character));
            });

        result.set_to_good_status_with_value(ok);
    }

    void Validators::is_decimal(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        if (value.empty())
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        bool has_decimal = false;
        for (char character : value)
        {
            if (character == '.')
            {
                if (has_decimal)
                {
                    result.set_to_good_status_with_value(false);
                    return;
                }
                has_decimal = true;
                continue;
            }
            if (!std::isdigit(static_cast<unsigned char>(character)))
            {
                result.set_to_good_status_with_value(false);
                return;
            }
        }

        result.set_to_good_status_with_value(true);
    }

    void Validators::is_time(
        Result<bool>& result,
        const std::string_view& value,
        const std::string_view& format
    )
    {
        int year = 0;
        int month = 0;
        int day = 0;

        if (format != "%Y-%m-%d" || value.size() != 10 || value[4] != '-' ||
            value[7] != '-')
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        auto parse = [](std::string_view str, int& out)
            {
                return std::from_chars(str.data(), str.data() + str.size(),
                    out).ec == std::errc();
            };

        result.set_to_good_status_with_value(parse(value.substr(0, 4), year) &&
            parse(value.substr(5, 2), month) &&
            parse(value.substr(8, 2), day) &&
            (year > 0 && month >= 1 && month <= 12 &&
                day >= 1 && day <= 31));
    }

    void Validators::is_datetime(
        Result<bool>& result,
        const std::string_view& value,
        const std::string_view& format
    )
    {
        is_time(result, value, format);
    }

    void Validators::is_date(
        Result<bool>& result,
        const std::string_view& value,
        const std::string_view& format
    )
    {
        if (format != "%Y-%m-%d" || value.size() != 10 || value[4] != '-' ||
            value[7] != '-')
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        int year = 0;
        int month = 0;
        int day = 0;

        auto parse = [](std::string_view str, int& out)
            {
                return std::from_chars(str.data(), str.data() + str.size(),
                    out).ec == std::errc();
            };

        result.set_to_good_status_with_value(parse(value.substr(0, 4), year) &&
            parse(value.substr(5, 2), month) &&
            parse(value.substr(8, 2), day) &&
            (year > 0 && month >= 1 && month <= 12 &&
                day >= 1 && day <= 31));
    }

    void Validators::is_past_date(
        Result<bool>& result,
        const std::string_view& value,
        const std::string_view& format
    )
    {
        bool ok = false;
        {
            Result<bool> tmp;
            tmp.set_to_bad_status_without_value();
            is_date(tmp, value, format);
            tmp.get_value(ok);
        }

        if (!ok)
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        int year = 0;
        int month = 0;
        int day = 0;
        std::from_chars(value.data(), value.data() + 4, year);
        std::from_chars(value.data() + 5, value.data() + 7, month);
        std::from_chars(value.data() + 8, value.data() + 10, day);
        std::tm time_tm = {};
        time_tm.tm_year = year - 1900;
        time_tm.tm_mon = month - 1;
        time_tm.tm_mday = day;
        std::time_t input_time = std::mktime(&time_tm);
        result.set_to_good_status_with_value(input_time != -1 && input_time < std::time(nullptr));
    }

    void Validators::is_future_date(
        Result<bool>& result,
        const std::string_view& value,
        const std::string_view& format
    )
    {
        bool ok = false;
        {
            Result<bool> tmp;
            tmp.set_to_bad_status_without_value();
            is_date(tmp, value, format);
            tmp.get_value(ok);
        }

        if (!ok)
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        int year = 0;
        int month = 0;
        int day = 0;
        std::from_chars(value.data(), value.data() + 4, year);
        std::from_chars(value.data() + 5, value.data() + 7, month);
        std::from_chars(value.data() + 8, value.data() + 10, day);
        std::tm time_tm = {};
        time_tm.tm_year = year - 1900;
        time_tm.tm_mon = month - 1;
        time_tm.tm_mday = day;
        std::time_t input_time = std::mktime(&time_tm);
        result.set_to_good_status_with_value(input_time != -1 && input_time > std::time(nullptr));
    }

    void Validators::is_unix(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        int64_t timestamp = 0;
        auto [ptr, ec] = std::from_chars(value.data(), value.data() + value.size(),
            timestamp);
        if (ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        result.set_to_good_status_with_value(timestamp >= 0);
    }

    void Validators::is_utc(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(value.ends_with("Z"));
    }

    void Validators::is_leap_year(
        Result<bool>& result,
        const int64_t& value)
    {
        if (value < 0)
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        result.set_to_good_status_with_value((value % 4 == 0 && value % 100 != 0) ||
            (value % 400 == 0));
    }

    void Validators::is_leap_year(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        int64_t year = 0;
        auto [ptr, ec] = std::from_chars(value.data(), value.data() + value.size(),
            year);
        if (ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        is_leap_year(result, year);
    }

    void Validators::is_within_inclusive_range(
        Result<bool>& result,
        const int64_t& minimum,
        const int64_t& maximum
    )
    {
        result.set_to_good_status_with_value(minimum <= maximum);
    }

    void Validators::is_within_inclusive_range(
        Result<bool>& result,
        const std::string_view& minimum,
        const std::string_view& maximum
    )
    {
        int64_t min_value = 0;
        int64_t max_value = 0;
        if (std::from_chars(minimum.data(), minimum.data() + minimum.size(),
            min_value).ec != std::errc() ||
            std::from_chars(maximum.data(), maximum.data() + maximum.size(),
                max_value).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        result.set_to_good_status_with_value(min_value <= max_value);
    }

    void Validators::is_within_exclusive_range(
        Result<bool>& result,
        const int64_t& minimum,
        const int64_t& maximum
    )
    {
        result.set_to_good_status_with_value(minimum < maximum);
    }

    void Validators::is_within_exclusive_range(
        Result<bool>& result,
        const std::string_view& minimum,
        const std::string_view& maximum
    )
    {
        int64_t min_value = 0;
        int64_t max_value = 0;
        if (std::from_chars(minimum.data(), minimum.data() + minimum.size(),
            min_value).ec != std::errc() ||
            std::from_chars(maximum.data(), maximum.data() + maximum.size(),
                max_value).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        result.set_to_good_status_with_value(min_value < max_value);
    }

    void Validators::is_even(
        Result<bool>& result,
        const int64_t& value
    )
    {
        result.set_to_good_status_with_value(value % 2 == 0);
    }

    void Validators::is_even(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        int64_t number = 0;
        if (std::from_chars(value.data(), value.data() + value.size(),
            number).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        result.set_to_good_status_with_value(number % 2 == 0);
    }

    void Validators::is_odd(
        Result<bool>& result,
        const int64_t& value
    )
    {
        result.set_to_good_status_with_value(value % 2 != 0);
    }

    void Validators::is_odd(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        int64_t number = 0;
        if (std::from_chars(value.data(), value.data() + value.size(),
            number).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        result.set_to_good_status_with_value(number % 2 != 0);
    }

    void Validators::is_prime(
        Result<bool>& result,
        const int64_t& value
    )
    {
        if (value < 2)
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        for (int64_t i = 2; i <= static_cast<int64_t>(std::sqrt(value)); ++i)
        {
            if (value % i == 0)
            {
                result.set_to_good_status_with_value(false);
                return;
            }
        }
        result.set_to_good_status_with_value(true);
    }

    void Validators::is_prime(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        int64_t number = 0;
        if (std::from_chars(value.data(), value.data() + value.size(),
            number).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        is_prime(result, number);
    }

    void Validators::is_divisible_by(
        Result<bool>& result,
        const int64_t& value,
        const int64_t& divisor
    )
    {
        if (divisor == 0)
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        result.set_to_good_status_with_value(value % divisor == 0);
    }

    void Validators::is_divisible_by(
        Result<bool>& result,
        const std::string_view& value,
        const std::string_view& divisor
    )
    {
        int64_t val = 0;
        int64_t div = 0;
        if (std::from_chars(value.data(), value.data() + value.size(),
            val).ec != std::errc() ||
            std::from_chars(divisor.data(), divisor.data() + divisor.size(),
                div).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        is_divisible_by(result, val, div);
    }

    void Validators::is_percentage(
        Result<bool>& result,
        const double& value
    )
    {
        result.set_to_good_status_with_value(value >= 0.0 && value <= 100.0);
    }

    void Validators::is_percentage(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        double number = 0.0;
        if (std::from_chars(value.data(), value.data() + value.size(),
            number).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        result.set_to_good_status_with_value(number >= 0.0 && number <= 100.0);
    }

    void Validators::is_latitude(
        Result<bool>& result,
        const double& value
    )
    {
        result.set_to_good_status_with_value(value >= -90.0 && value <= 90.0);
    }

    void Validators::is_latitude(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        double number = 0.0;
        if (std::from_chars(value.data(), value.data() + value.size(),
            number).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        is_latitude(result, number);
    }

    void Validators::is_longitude(
        Result<bool>& result,
        const double& value
    )
    {
        result.set_to_good_status_with_value(value >= -180.0 && value <= 180.0);
    }

    void Validators::is_longitude(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        double number = 0.0;
        if (std::from_chars(value.data(), value.data() + value.size(),
            number).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        is_longitude(result, number);
    }

    void Validators::is_coordinate(
        Result<bool>& result,
        const double& latitude,
        const double& longitude
    )
    {
        bool lat_ok = (latitude >= -90.0 && latitude <= 90.0);
        bool lon_ok = (longitude >= -180.0 && longitude <= 180.0);
        result.set_to_good_status_with_value(lat_ok && lon_ok);
    }

    void Validators::is_coordinate(
        Result<bool>& result,
        const std::string_view& latitude,
        const std::string_view& longitude
    )
    {
        double lat_num = 0.0;
        double lon_num = 0.0;
        if (std::from_chars(latitude.data(), latitude.data() + latitude.size(),
            lat_num).ec != std::errc() ||
            std::from_chars(longitude.data(), longitude.data() + longitude.size(),
                lon_num).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        is_coordinate(result, lat_num, lon_num);
    }

    void Validators::is_country_code(
        Result<bool>& result,
        const std::string_view& value)
    {
        bool ok = value.size() == 2 &&
            std::ranges::all_of(value, [](char character)
                {
                    return std::isalpha(static_cast<unsigned char>(character));
                });
        result.set_to_good_status_with_value(ok);
    }

    void Validators::is_currency_code(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        bool ok = value.size() == 3 &&
            std::ranges::all_of(value, [](char character)
                {
                    return std::isalpha(static_cast<unsigned char>(character));
                });
        result.set_to_good_status_with_value(ok);
    }

    void Validators::is_language_code(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        bool ok = value.size() >= 2 && value.size() <= 3 &&
            std::ranges::all_of(value, [](char character)
                {
                    return std::isalpha(static_cast<unsigned char>(character));
                });
        result.set_to_good_status_with_value(ok);
    }

    void Validators::is_rgb_color(
        Result<bool>& result,
        const uint8_t& red,
        const uint8_t& green,
        const uint8_t& blue)
    {
        result.set_to_good_status_with_value(red <= 255 && green <= 255 && blue <= 255);
    }

    void Validators::is_rgba_color(
        Result<bool>& result,
        const uint8_t& red,
        const uint8_t& green,
        const uint8_t& blue,
        const uint8_t& alpha)
    {
        result.set_to_good_status_with_value(red <= 255 && green <= 255 && blue <= 255 &&
            alpha <= 255);
    }

    void Validators::is_iso8601(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(Z|[+-]\d{2}:\d{2})?$)"));
    }

    void Validators::is_hex_color(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^#(?:[0-9a-fA-F]{3}){1,2}$)"));
    }

    void Validators::is_rgb_color(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^rgb\((\s*\d{1,3}\s*,){2}\s*\d{1,3}\s*\)$)"));
    }

    void Validators::is_rgba_color(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^rgba\((\s*\d{1,3}\s*,){3}\s*(0|1|0?\.\d+)\s*\)$)"));
    }

    void Validators::is_file_path(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^(([a-zA-Z]:\\|\/)?([\w\-. ]+([\/\\][\w\-. ]+)*))$)"));
    }

    void Validators::is_file_name(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^[\w,\s-]+\.[A-Za-z]{1,6}$)"));
    }

    void Validators::is_file_extension(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^[a-zA-Z0-9]+$)"));
    }

    void Validators::is_file_extension_allowed(
        Result<bool>& result,
        const std::string_view& value,
        const std::set<std::string>& allowed_extensions)
    {
        result.set_to_good_status_with_value(allowed_extensions.contains(std::string(value)));
    }

    void Validators::is_mime_type(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^(application|audio|font|example|image|message|model|multipart|text|video|x-[a-z0-9]+)\/[a-zA-Z0-9!#$&^_.+-]+$)"));
    }

    void Validators::is_base64_image(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^data:image\/(png|jpeg|jpg|gif);base64,([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{2}==|[A-Za-z0-9+/]{3}=)?$)"));
    }

    void Validators::is_data_uri(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^data:[a-zA-Z0-9!#$&^_.+-]+\/[a-zA-Z0-9!#$&^_.+-]+;base64,([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{2}==|[A-Za-z0-9+/]{3}=)?$)"));
    }

    void Validators::is_phone_number(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^\+?(\d{1,3})?\s?(\(\d{3}\)|\d{3})[-.\s]?\d{3}[-.\s]?\d{4}$)"));
    }

    void Validators::is_e164_phone_number(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value, R"(^\+\d{1,15}$)"));
    }

    void Validators::is_country_calling_code(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value, R"(^\+\d{1,3}$)"));
    }

    void Validators::is_full_name(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^[a-zA-Z]+([ '-][a-zA-Z]+)*$)"));
    }

    void Validators::is_email(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(match_std_regex(value,
            R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)"));
    }

    void Validators::is_file_size_allowed(
        Result<bool>& result,
        const std::size_t& value,
        const std::size_t& maximum_size
    )
    {
        result.set_to_good_status_with_value(value <= maximum_size);
    }

    void Validators::is_file_type_allowed(
        Result<bool>& result,
        const std::string_view& value,
        const std::set<std::string>& allowed_types
    )
    {
        result.set_to_good_status_with_value(allowed_types.contains(std::string(value)));
    }

    void Validators::is_age(
        Result<bool>& result,
        const uint8_t& value
    )
    {
        result.set_to_good_status_with_value(value <= 130);
    }

    void Validators::is_age(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        uint8_t age = 0;
        if (std::from_chars(value.data(), value.data() + value.size(),
            age).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        result.set_to_good_status_with_value(age <= 130);
    }

    void Validators::is_gender(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        std::string lower_case(value);
        std::ranges::transform(lower_case, lower_case.begin(), [](char c)
            {
                return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            });

        bool ok = lower_case == "m" || lower_case == "f" || lower_case == "o" ||
            lower_case == "male" || lower_case == "female" ||
            lower_case == "nonbinary" || lower_case == "other";

        result.set_to_good_status_with_value(ok);
    }

    void Validators::is_address_line(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(value.size() >= 5 && value.size() <= 128);
    }

    void Validators::is_first_name(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        is_full_name(result, value);
    }

    void Validators::is_middle_name(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        is_full_name(result, value);
    }

    void Validators::is_middle_initial(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(value.size() == 1 &&
            std::isalpha(static_cast<unsigned char>(value.front())));
    }

    void Validators::is_adult(
        Result<bool>& result,
        const uint8_t& age,
        const uint8_t& minimum_age
    )
    {
        result.set_to_good_status_with_value(age >= minimum_age);
    }

    void Validators::is_juvenile(
        Result<bool>& result,
        const uint8_t& age
    )
    {
        result.set_to_good_status_with_value(age < 18 && age >= 13);
    }

    void Validators::is_child(
        Result<bool>& result,
        const uint8_t& age
    )
    {
        result.set_to_good_status_with_value(age < 13);
    }

    void Validators::is_strong_password(
        Result<bool>& result,
        const std::string_view& value,
        const ValidationPasswordRules& rules
    )
    {
        if (value.size() < rules.minimum_length ||
            value.size() > rules.maximum_length)
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        bool has_upper = false;
        bool has_lower = false;
        bool has_digit = false;
        bool has_special = false;
        std::unordered_set<char> unique_chars;

        for (char c : value)
        {
            if (std::isupper(static_cast<unsigned char>(c))) has_upper = true;
            if (std::islower(static_cast<unsigned char>(c))) has_lower = true;
            if (std::isdigit(static_cast<unsigned char>(c))) has_digit = true;
            if (!std::isalnum(static_cast<unsigned char>(c))) has_special = true;
            unique_chars.insert(c);
        }

        if (rules.require_uppercase_characters && !has_upper)
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        if (rules.require_lowercase_characters && !has_lower)
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        if (rules.require_alpha_numerics && !has_digit)
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        if (rules.require_special_characters && !has_special)
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        if (rules.require_unique_characters &&
            unique_chars.size() < value.size())
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        result.set_to_good_status_with_value(true);
    }

    void Validators::is_character_repeated(
        Result<bool>& result,
        const std::string_view& value,
        const std::size_t& threshold)
    {
        std::unordered_map<char, std::size_t> counts;
        for (char c : value)
        {
            if (++counts[c] > threshold)
            {
                result.set_to_good_status_with_value(true);
                return;
            }
        }
        result.set_to_good_status_with_value(false);
    }

    void Validators::is_blacklisted_word_found(
        Result<bool>& result,
        const std::string_view& value,
        const std::vector<std::string>& blacklist)
    {
        bool found = std::ranges::any_of(blacklist,
            [&](const std::string& word)
            {
                return value.find(word) != std::string_view::npos;
            });

        result.set_to_good_status_with_value(found);
    }

    void Validators::get_instance(
        Result<Validators*>& result
    )
    {
        static Validators singleton_instance;

        result.set_to_good_status_with_value(&singleton_instance);
    }   
}
