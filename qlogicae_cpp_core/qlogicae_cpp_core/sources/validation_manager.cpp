#include "pch.hpp"

#include "../includes/validation_manager.hpp"

namespace QLogicaeCppCore
{
    ValidationManager::ValidationManager()
    {
        Result<bool> result;

        construct(result);
    }

    ValidationManager::~ValidationManager()
    {
        Result<bool> result;

        destruct(result);
    }

    void ValidationManager::construct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            true
        );
    }

    void ValidationManager::destruct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            true
        );
    }

    void ValidationManager::match_std_regex(
        Result<bool>& result,
        const std::string_view& input,
        const std::string_view& pattern
    )
    {
        result.set_to_good_status_with_value(
            std::regex_match(
                input.begin(),
                input.end(),
                std::regex(pattern.data())
            )
        );
    }

    void ValidationManager::is_not_empty(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(
            !value.empty()
        );
    }

    void ValidationManager::is_empty(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(
            value.empty()
        );
    }

    void ValidationManager::is_lowercase(
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
                return std::islower(
                    static_cast<unsigned char>(character)
                );
            });

        result.set_to_good_status_with_value(ok);
    }

    void ValidationManager::is_uppercase(
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
                return std::isupper(
                    static_cast<unsigned char>(character)
                );
            });

        result.set_to_good_status_with_value(ok);
    }

    void ValidationManager::is_first_letter_uppercase(
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
            std::isupper(
                static_cast<unsigned char>(value.front())
            )
        );
    }

    void ValidationManager::is_prefix_found(
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

        result.set_to_good_status_with_value(
            value.starts_with(prefix)
        );
    }

    void ValidationManager::is_suffix_found(
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

        result.set_to_good_status_with_value(
            value.ends_with(suffix)
        );
    }

    void ValidationManager::is_substring_found(
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

        result.set_to_good_status_with_value(
            value.find(substring) != std::string_view::npos
        );
    }

    void ValidationManager::is_base64(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{2}==|[A-Za-z0-9+/]{3}=)?$)"
        );
    }

    void ValidationManager::is_utf8(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(
            std::string(value).find('\xC0') == std::string::npos
        );
    }

    void ValidationManager::is_utf16(
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
        result.set_to_good_status_with_value(
            (byte1 == 0xFF && byte2 == 0xFE) ||
            (byte1 == 0xFE && byte2 == 0xFF)
        );
    }

    void ValidationManager::is_slug(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^[a-z0-9]+(?:-[a-z0-9]+)*$)"
        );
    }

    void ValidationManager::is_hex(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^(0x)?[0-9a-fA-F]+$)"
        );
    }

    void ValidationManager::is_uuid4(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-4[a-fA-F0-9]{3}-[89abAB][a-fA-F0-9]{3}-[a-fA-F0-9]{12}$)"
        );
    }

    void ValidationManager::is_uuid6(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-6[a-fA-F0-9]{3}-[89abAB][a-fA-F0-9]{3}-[a-fA-F0-9]{12}$)"
        );
    }

    void ValidationManager::is_ipv4(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^((25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)\.){3}(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)$)"
        );
    }

    void ValidationManager::is_ipv6(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$)"
        );
    }

    void ValidationManager::is_url(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^https?:\/\/(?:www\.)?[a-zA-Z0-9.-]+(?:\:\d+)?(?:\/\S*)?$)"
        );
    }

    void ValidationManager::is_uri(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^[a-zA-Z][a-zA-Z0-9+.-]*:\/\/[^\s\/?#]+(?:[\/?#][^\s]*)?$)"
        );
    }

    void ValidationManager::is_mac_address(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$)"
        );
    }

    void ValidationManager::is_hostname(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\-]*[A-Za-z0-9])$)"
        );
    }

    void ValidationManager::is_domain(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^([a-zA-Z0-9]+(-[a-zA-Z0-9]+)*\.)+[a-zA-Z]{2,}$)"
        );
    }

    void ValidationManager::is_port_in_range(
        Result<bool>& result,
        const uint32_t& port,
        const uint32_t& minimum,
        const uint32_t& maximum
    )
    {
        result.set_to_good_status_with_value(
            port >= minimum && port <= maximum
        );
    }

    void ValidationManager::is_port_in_range(
        Result<bool>& result,
        const std::string_view& port,
        const uint32_t& minimum,
        const uint32_t& maximum)
    {
        uint32_t parsed_port = 0;
        auto [ptr, ec] = std::from_chars(
            port.data(),
            port.data() + port.size(),
            parsed_port
        );
        if (ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        
        result.set_to_good_status_with_value(
            parsed_port >= minimum &&
            parsed_port <= maximum
        );
    }

    void ValidationManager::is_alpanumeric(
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
                return std::isalnum(
                    static_cast<unsigned char>(character)
                );
            });

        result.set_to_good_status_with_value(ok);
    }

    void ValidationManager::is_decimal(
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

    void ValidationManager::is_time(
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

    void ValidationManager::is_datetime(
        Result<bool>& result,
        const std::string_view& value,
        const std::string_view& format
    )
    {
        is_time(result, value, format);
    }

    void ValidationManager::is_date(
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

    void ValidationManager::is_past_date(
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

        result.set_to_good_status_with_value(
            input_time != -1 && input_time < std::time(nullptr)
        );
    }

    void ValidationManager::is_future_date(
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
        result.set_to_good_status_with_value(
            input_time != -1 && input_time > std::time(nullptr)
        );
    }

    void ValidationManager::is_unix(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        int64_t timestamp = 0;
        auto [ptr, ec] = std::from_chars(
            value.data(), value.data() + value.size(), timestamp
        );
        if (ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
        
            return;
        }

        result.set_to_good_status_with_value(
            timestamp >= 0
        );
    }

    void ValidationManager::is_utc(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(
            value.ends_with("Z")
        );
    }

    void ValidationManager::is_leap_year(
        Result<bool>& result,
        const int64_t& value)
    {
        if (value < 0)
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        result.set_to_good_status_with_value(
            (value % 4 == 0 && value % 100 != 0) ||
            (value % 400 == 0)
        );
    }

    void ValidationManager::is_leap_year(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        int64_t year = 0;
        auto [ptr, ec] = std::from_chars(
            value.data(), value.data() + value.size(), year
        );
        
        if (ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
        
            return;
        }

        is_leap_year(result, year);
    }

    void ValidationManager::is_within_inclusive_range(
        Result<bool>& result,
        const int64_t& minimum,
        const int64_t& maximum
    )
    {
        result.set_to_good_status_with_value(
            minimum <= maximum
        );
    }

    void ValidationManager::is_within_inclusive_range(
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

    void ValidationManager::is_within_exclusive_range(
        Result<bool>& result,
        const int64_t& minimum,
        const int64_t& maximum
    )
    {
        result.set_to_good_status_with_value(
            minimum < maximum
        );
    }

    void ValidationManager::is_within_exclusive_range(
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

    void ValidationManager::is_even(
        Result<bool>& result,
        const int64_t& value
    )
    {
        result.set_to_good_status_with_value(
            value % 2 == 0
        );
    }

    void ValidationManager::is_even(
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

        result.set_to_good_status_with_value(
            number % 2 == 0
        );
    }

    void ValidationManager::is_odd(
        Result<bool>& result,
        const int64_t& value
    )
    {
        result.set_to_good_status_with_value(
            value % 2 != 0
        );
    }

    void ValidationManager::is_odd(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        int64_t number = 0;
        if (std::from_chars(value.data(),
            value.data() + value.size(),
            number).ec != std::errc()
        )
        {
            result.set_to_good_status_with_value(false);

            return;
        }

        result.set_to_good_status_with_value(number % 2 != 0);
    }

    void ValidationManager::is_prime(
        Result<bool>& result,
        const int64_t& value
    )
    {
        if (value < 2)
        {
            result.set_to_good_status_with_value(false);

            return;
        }

        for (int64_t i = 2; i <= static_cast<int64_t>(
            std::sqrt(value)); ++i
        )
        {
            if (value % i == 0)
            {
                result.set_to_good_status_with_value(false);
        
                return;
            }
        }
        
        result.set_to_good_status_with_value(true);
    }

    void ValidationManager::is_prime(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        int64_t number = 0;
        if (std::from_chars(value.data(),
            value.data() + value.size(),
            number).ec != std::errc()
        )
        {
            result.set_to_good_status_with_value(false);
        
            return;
        }
        
        is_prime(result, number);
    }

    void ValidationManager::is_divisible_by(
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

    void ValidationManager::is_divisible_by(
        Result<bool>& result,
        const std::string_view& value,
        const std::string_view& divisor
    )
    {
        int64_t val = 0;
        int64_t div = 0;
        if (std::from_chars(value.data(),
            value.data() + value.size(),
            val).ec != std::errc() ||
            std::from_chars(divisor.data(),
                divisor.data() + divisor.size(),
                div).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);
        
            return;
        }
        
        is_divisible_by(result, val, div);
    }

    void ValidationManager::is_percentage(
        Result<bool>& result,
        const double& value
    )
    {
        result.set_to_good_status_with_value(
            value >= 0.0 && value <= 100.0
        );
    }

    void ValidationManager::is_percentage(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        double number = 0.0;
        if (std::from_chars(value.data(),
            value.data() + value.size(),
            number).ec != std::errc()
        )
        {
            result.set_to_good_status_with_value(false);
            return;
        }
        result.set_to_good_status_with_value(
            number >= 0.0 && number <= 100.0
        );
    }

    void ValidationManager::is_latitude(
        Result<bool>& result,
        const double& value
    )
    {
        result.set_to_good_status_with_value(
            value >= -90.0 && value <= 90.0
        );
    }

    void ValidationManager::is_latitude(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        double number = 0.0;
        if (std::from_chars(value.data(),
            value.data() + value.size(),
            number).ec != std::errc()
        )
        {
            result.set_to_good_status_with_value(false);
        
            return;
        }

        is_latitude(result, number);
    }

    void ValidationManager::is_longitude(
        Result<bool>& result,
        const double& value
    )
    {
        result.set_to_good_status_with_value(
            value >= -180.0 && value <= 180.0
        );
    }

    void ValidationManager::is_longitude(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        double number = 0.0;
        if (std::from_chars(value.data(),
            value.data() + value.size(),
            number).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);

            return;
        }

        is_longitude(result, number);
    }

    void ValidationManager::is_coordinate(
        Result<bool>& result,
        const double& latitude,
        const double& longitude
    )
    {
        bool lat_ok =
            (latitude >= -90.0 && latitude <= 90.0);
        bool lon_ok =
            (longitude >= -180.0 && longitude <= 180.0);

        result.set_to_good_status_with_value(
            lat_ok && lon_ok
        );
    }

    void ValidationManager::is_coordinate(
        Result<bool>& result,
        const std::string_view& latitude,
        const std::string_view& longitude
    )
    {
        double lat_num = 0.0;
        double lon_num = 0.0;
        if (std::from_chars(latitude.data(),
            latitude.data() + latitude.size(),
            lat_num).ec != std::errc() ||
            std::from_chars(longitude.data(),
                longitude.data() + longitude.size(),
                lon_num).ec != std::errc())
        {
            result.set_to_good_status_with_value(false);

            return;
        }

        is_coordinate(result, lat_num, lon_num);
    }

    void ValidationManager::is_country_code(
        Result<bool>& result,
        const std::string_view& value)
    {
        bool ok = value.size() == 2 &&
            std::ranges::all_of(value, [](char character)
                {
                    return std::isalpha(
                        static_cast<unsigned char>(character)
                    );
                }
            );

        result.set_to_good_status_with_value(ok);
    }

    void ValidationManager::is_currency_code(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        bool ok = value.size() == 3 &&
            std::ranges::all_of(value, [](char character)
                {
                    return std::isalpha(
                        static_cast<unsigned char>(character)
                    );
                }
            );

        result.set_to_good_status_with_value(ok);
    }

    void ValidationManager::is_language_code(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        bool ok = value.size() >= 2 && value.size() <= 3 &&
            std::ranges::all_of(value, [](char character)
                {
                    return std::isalpha(
                        static_cast<unsigned char>(character)
                    );
                }
            );

        result.set_to_good_status_with_value(ok);
    }

    void ValidationManager::is_rgb_color(
        Result<bool>& result,
        const uint8_t& red,
        const uint8_t& green,
        const uint8_t& blue)
    {
        result.set_to_good_status_with_value(
            red <= 255 && green <= 255 && blue <= 255
        );
    }

    void ValidationManager::is_rgba_color(
        Result<bool>& result,
        const uint8_t& red,
        const uint8_t& green,
        const uint8_t& blue,
        const uint8_t& alpha)
    {
        result.set_to_good_status_with_value(
            red <= 255 && green <= 255 && blue <= 255 && alpha <= 255
        );
    }

    void ValidationManager::is_iso8601(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value,
            R"(^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(Z|[+-]\d{2}:\d{2})?$)"
        );
    }

    void ValidationManager::is_hex_color(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value,
            R"(^#(?:[0-9a-fA-F]{3}){1,2}$)"
        );
    }

    void ValidationManager::is_rgb_color(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value,
            R"(^rgb\((\s*\d{1,3}\s*,){2}\s*\d{1,3}\s*\)$)"
        );
    }

    void ValidationManager::is_rgba_color(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value,
            R"(^rgba\((\s*\d{1,3}\s*,){3}\s*(0|1|0?\.\d+)\s*\)$)"
        );
    }

    void ValidationManager::is_file_path(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value,
            R"(^(([a-zA-Z]:\\|\/)?([\w\-. ]+([\/\\][\w\-. ]+)*))$)"
        );
    }

    void ValidationManager::is_file_name(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value,
            R"(^[\w,\s-]+\.[A-Za-z]{1,6}$)"
        );
    }

    void ValidationManager::is_file_extension(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value,
            R"(^[a-zA-Z0-9]+$)"
        );
    }

    void ValidationManager::is_file_extension_allowed(
        Result<bool>& result,
        const std::string_view& value,
        const std::set<std::string>& allowed_extensions)
    {
        result.set_to_good_status_with_value(
            allowed_extensions.contains(std::string(value))
        );
    }

    void ValidationManager::is_mime_type(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value,
            R"(^(application|audio|font|example|image|message|model|multipart|text|video|x-[a-z0-9]+)\/[a-zA-Z0-9!#$&^_.+-]+$)"
        );
    }

    void ValidationManager::is_base64_image(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value,
            R"(^data:image\/(png|jpeg|jpg|gif);base64,([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{2}==|[A-Za-z0-9+/]{3}=)?$)"
        );
    }

    void ValidationManager::is_data_uri(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value,
            R"(^data:[a-zA-Z0-9!#$&^_.+-]+\/[a-zA-Z0-9!#$&^_.+-]+;base64,([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{2}==|[A-Za-z0-9+/]{3}=)?$)"
        );
    }

    void ValidationManager::is_phone_number(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value,
            R"(^\+?(\d{1,3})?\s?(\(\d{3}\)|\d{3})[-.\s]?\d{3}[-.\s]?\d{4}$)"
        );
    }

    void ValidationManager::is_e164_phone_number(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value, R"(^\+\d{1,15}$)"
        );
    }

    void ValidationManager::is_country_calling_code(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value, R"(^\+\d{1,3}$)"
        );
    }

    void ValidationManager::is_full_name(
        Result<bool>& result,
        const std::string_view& value)
    {
        match_std_regex(
            result,
            value,
            R"(^[a-zA-Z]+([ '-][a-zA-Z]+)*$)"
        );
    }

    void ValidationManager::is_email(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        match_std_regex(
            result,
            value,
            R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)"
        );
    }

    void ValidationManager::is_file_size_allowed(
        Result<bool>& result,
        const std::size_t& value,
        const std::size_t& maximum_size
    )
    {
        result.set_to_good_status_with_value(
            value <= maximum_size
        );
    }

    void ValidationManager::is_file_type_allowed(
        Result<bool>& result,
        const std::string_view& value,
        const std::set<std::string>& allowed_types
    )
    {
        result.set_to_good_status_with_value(
            allowed_types.contains(std::string(value))
        );
    }

    void ValidationManager::is_age(
        Result<bool>& result,
        const uint8_t& value
    )
    {
        result.set_to_good_status_with_value(
            value <= 130
        );
    }

    void ValidationManager::is_age(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        uint8_t age = 0;
        if (std::from_chars(value.data(),
            value.data() + value.size(),
            age).ec != std::errc()
        )
        {
            result.set_to_good_status_with_value(false);
        
            return;
        }

        result.set_to_good_status_with_value(
            age <= 130
        );
    }

    void ValidationManager::is_gender(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        std::string lower_case(value);
        std::ranges::transform(lower_case, lower_case.begin(), [](char c)
            {
                return static_cast<char>(
                    std::tolower(static_cast<unsigned char>(c))
                );
            });

        bool ok = lower_case == "m" || lower_case == "f" || lower_case == "o" ||
            lower_case == "male" || lower_case == "female" ||
            lower_case == "nonbinary" || lower_case == "other";

        result.set_to_good_status_with_value(ok);
    }

    void ValidationManager::is_address_line(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        result.set_to_good_status_with_value(
            value.size() >= 5 && value.size() <= 128
        );
    }

    void ValidationManager::is_first_name(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        is_full_name(result, value);
    }

    void ValidationManager::is_middle_name(
        Result<bool>& result,
        const std::string_view& value
    )
    {
        is_full_name(result, value);
    }

    void ValidationManager::is_middle_initial(
        Result<bool>& result,
        const std::string_view& value)
    {
        result.set_to_good_status_with_value(value.size() == 1 &&
            std::isalpha(static_cast<unsigned char>(value.front()))
        );
    }

    void ValidationManager::is_adult(
        Result<bool>& result,
        const uint8_t& age
    )
    {
        result.set_to_good_status_with_value(
            age >= 18
        );
    }

    void ValidationManager::is_adult(
        Result<bool>& result,
        const uint8_t& age,
        const uint8_t& minimum_age
    )
    {
        result.set_to_good_status_with_value(
            age >= minimum_age
        );
    }

    void ValidationManager::is_juvenile(
        Result<bool>& result,
        const uint8_t& age
    )
    {
        result.set_to_good_status_with_value(
            age < 18 && age >= 13
        );
    }

    void ValidationManager::is_child(
        Result<bool>& result,
        const uint8_t& age
    )
    {
        result.set_to_good_status_with_value(
            age < 13
        );
    }

    void ValidationManager::is_strong_password(
        Result<bool>& result,
        const std::string_view& value,
        const ValidationManagerPasswordRules& rules
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

    void ValidationManager::is_character_repeated(
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

    void ValidationManager::is_blacklisted_word_found(
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
}
