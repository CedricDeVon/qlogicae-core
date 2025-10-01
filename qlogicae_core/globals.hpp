#pragma once

#include <sqlite3.h>
#include <absl/time/time.h>
#include <rapidjson/document.h>

#include <ios>
#include <map>
#include <mutex>
#include <queue>
#include <chrono>
#include <vector>
#include <variant>
#include <cstdint>
#include <Windows.h>
#include <functional>
#include <string_view>
#include <unordered_map>
#include <condition_variable>

namespace QLogicaeCore
{    
    enum class EncodingType : uint8_t
    {
        HEX,
        UTF8,
        BASE64
    };

    enum class FileMode : uint8_t
    {
        READ,
        WRITE,
        APPEND
    };

    enum class TimeScaleUnit : uint8_t
    {
        NANOSECONDS,
        MICROSECONDS,
        MILLISECONDS,
        SECONDS,
        MINUTES,
        HOURS,
        DAYS,
        WEEKS,
        MONTHS,
        YEARS
    };

    enum class TimeFormat : uint8_t
    {
        UNIX,
        ISO8601,
        SECOND_LEVEL_TIMESTAMP,
        MILLISECOND_LEVEL_TIMESTAMP,
        MICROSECOND_LEVEL_TIMESTAMP,
        FULL_TIMESTAMP,
        FULL_DASHED_TIMESTAMP,
        HOUR_12,
        HOUR_24,
        MILLISECOND_MICROSECOND_NANOSECOND,
        DATE_DASHED,
        DATE_MDY_SLASHED,
        DATE_DMY_SLASHED,
        DATE_DMY_SPACED,
        DATE_VERBOSE
    };

    enum class TimeZone : uint8_t
    {
        UTC,
        LOCAL
    };

    enum class LogMedium : uint8_t
    {
        ALL,
        FILE,
        CONSOLE
    };

    enum class LogLevel : uint8_t
    {
        ALL,
        INFO,
        DEBUG,
        WARNING,
        SUCCESS,
        CRITICAL,
        EXCEPTION,
        HIGHLIGHTED_INFO
    };

    enum class TaskPriority : uint8_t
    {
        HIGH = 0,
        MEDIUM = 1,
        LOW = 2
    };

    enum class TemperatureUnitType : uint8_t
    {
        CELSIUS,
        FAHRENHEIT,
        KELVIN,
        NONE
    };

    enum class CaseSensitivity : uint8_t
    {
        SENSITIVE,
        INSENSITIVE
    };

    enum class WindowsRegistryRootPath : uint8_t
    {
        HKCU,
        HKLM
    };

    enum class UTF : uint8_t
    {
        T8,
        T16
    };

    enum class EnvironmentVariable : uint8_t
    {
        USER,
        SYSTEM
    };

    enum class QLogicaeVisualStudio2022BuildArchitecture : uint8_t
    {
        X64,
        X86
    };

    enum class QLogicaeVisualStudio2022Build : uint8_t
    {
        RELEASE,
        DEBUG
    };

    enum class SupportedQLogicaeIDE : uint8_t
    {
        VISUAL_STUDIO_2022
    };

    enum class SupportedQLogicaeInstaller : uint8_t
    {
        INNO_SETUP
    };

    struct Constants
    {
        static constexpr unsigned int DEFAULT_MILLISECONDS_PER_CALLBACK = 1000;
        static constexpr bool DEFAULT_IS_LISTENING = true;

        static constexpr HKEY DEFAULT_HKEY = HKEY_CURRENT_USER;
        static constexpr int HKEY_MAXIMUM_VALUE_SIZE = 1 << 16;
        static constexpr DWORD HKEY_MAXIMUM_VALUE_NAME_SIZE = 32767;
        static constexpr DWORD HKEY_MAXIMUM_VALUE_DATA_SIZE = 65535;
        static constexpr std::wstring_view DEFAULT_NAME_KEY = L"Data";
        static constexpr std::wstring_view DEFAULT_SUB_KEY = L"Software\\App";
        static constexpr REGSAM REGULAR_ACCESS_FLAGS = KEY_READ | KEY_SET_VALUE;

        static constexpr size_t RANDOM_SIZE_T_BITS = 8;
        static constexpr double RANDOM_DOUBLE_MINIMUM = 0.0;
        static constexpr double RANDOM_DOUBLE_MAXIMUM = 1.0;
        static constexpr double RANDOM_BOOLEAN_MAXIMUM = 0.5;
        static constexpr std::string_view HEXADECIMAL_CHARACTERS = "0123456789abcdef";
        static constexpr std::string_view ALPHA_NUMERIC_CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        static constexpr std::string_view FULL_VISIBLE_ASCII_CHARACTERSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

        static constexpr unsigned int NUMBER_ZERO = 0;
        static constexpr double NUMBER_ZERO_POINT_ZERO = 0.0;
        static constexpr unsigned int NUMBER_ONE = 1;
        static constexpr unsigned int NUMBER_TEN = 10;
        static constexpr unsigned int NUMBER_HUNDRED = 100;
        static constexpr unsigned int NUMBER_THOUSAND = 1'000;
        static constexpr unsigned int NUMBER_MILLION = 1'000'000;
        static constexpr unsigned int NUMBER_BILLION = 1'000'000'000;

        static constexpr unsigned int UNIX_START_YEAR_OFFSET = 1'900;
        static constexpr char TIME_FORMAT_ISO_8601[] = "%Y-%m-%dT%H:%M:%S";
        static constexpr char TIME_FORMAT_FULL_TIMESTAMP[] = "%Y-%m-%d] [%H:%M:%S";
        static constexpr char TIME_FORMAT_FULL_DASHED_TIMESTAMP[] = "%Y-%m-%d-%H-%M-%S";
        static constexpr char TIME_FORMAT_HOUR_12[] = "%I:%M:%S %p";
        static constexpr char TIME_FORMAT_HOUR_24[] = "%H:%M:%S";
        static constexpr char TIME_FORMAT_DATE_DASHED[] = "%Y-%m-%d";
        static constexpr char TIME_FORMAT_DATE_MDY_SLASHED[] = "%m/%d/%Y";
        static constexpr char TIME_FORMAT_DATE_DMY_SLASHED[] = "%d/%m/%Y";
        static constexpr char TIME_FORMAT_DATE_DMY_SPACED[] = "%d %m %Y";
        static constexpr char TIME_FORMAT_DATE_VERBOSE[] = "%A, %B %d, %Y";
        static constexpr char TIME_FORMAT_EMPTY[] = "";
        static constexpr char TIME_FORMAT_INVALID[] = "Invalid TimeFormat";
        static constexpr char TIME_FORMAT_PART_1[] = "ms: ";
        static constexpr char TIME_FORMAT_PART_2[] = ", us: ";
        static constexpr char TIME_FORMAT_PART_3[] = ", ns: ";
        static constexpr char TIME_FORMAT_PART_4 = '.';
        static constexpr char TIME_FORMAT_PART_5 = ':';
        static constexpr char TIME_FORMAT_PART_6 = '0';
        static constexpr std::streamsize TIME_FORMAT_MIL_MIC_NAN_STREAM_SIZE = 3;

        static constexpr std::string_view STRING_EMPTY = "";
        static constexpr std::string_view STRING_NONE_1 = "None";
        static constexpr std::string_view STRING_NONE_2 = "N/A";

        static constexpr std::string_view LOG_LEVEL_ALL = "INFO";
        static constexpr std::string_view LOG_LEVEL_INFO = "INFO";
        static constexpr std::string_view LOG_LEVEL_DEBUG = "DEBUG";
        static constexpr std::string_view LOG_LEVEL_SUCCESS = "SUCCESS";
        static constexpr std::string_view LOG_LEVEL_WARNING = "WARNING";
        static constexpr std::string_view LOG_LEVEL_CRITICAL = "CRITICAL";
        static constexpr std::string_view LOG_LEVEL_EXCEPTION = "EXCEPTION";
        static constexpr std::string_view LOG_LEVEL_HIGHLIGHTED_INFO = "INFO";

        static constexpr std::string_view DEFAULT_HOST_ADDRESS = "1.1.1.1";

        static constexpr double SECONDS_OVER_NANOSECONDS = 1'000'000'000.0;
        static constexpr double SECONDS_OVER_MICROSECONDS = 1'000'000.0;
        static constexpr double SECONDS_OVER_MILLISECONDS = 1'000.0;
        static constexpr double SECONDS_PER_MINUTE = 60.0;
        static constexpr double SECONDS_PER_HOUR = 3'600.0;
        static constexpr double SECONDS_PER_DAY = 86'400.0;
        static constexpr double SECONDS_PER_WEEK = 604'800.0;
        static constexpr double SECONDS_PER_MONTH = 2'629'746.0;
        static constexpr double SECONDS_PER_YEAR = 31'557'600.0;

        static constexpr std::string_view TIME_SCALE_UNIT_FULL_NAME_NANOSECONDS = "Nanosecond(s)";
        static constexpr std::string_view TIME_SCALE_UNIT_FULL_NAME_MICROSECONDS = "Microsecond(s)";
        static constexpr std::string_view TIME_SCALE_UNIT_FULL_NAME_MILLISECONDS = "Millisecond(s)";
        static constexpr std::string_view TIME_SCALE_UNIT_FULL_NAME_SECONDS = "Second(s)";
        static constexpr std::string_view TIME_SCALE_UNIT_FULL_NAME_MINUTES = "Minute(s)";
        static constexpr std::string_view TIME_SCALE_UNIT_FULL_NAME_HOURS = "Hour(s)";
        static constexpr std::string_view TIME_SCALE_UNIT_FULL_NAME_DAYS = "Day(s)";
        static constexpr std::string_view TIME_SCALE_UNIT_FULL_NAME_WEEKS = "Week(s)";
        static constexpr std::string_view TIME_SCALE_UNIT_FULL_NAME_MONTHS = "Month(s)";
        static constexpr std::string_view TIME_SCALE_UNIT_FULL_NAME_YEARS = "Year(s)";
        
        static constexpr std::string_view TIME_SCALE_UNIT_ABBREVIATION_NANOSECONDS = "ns";
        static constexpr std::string_view TIME_SCALE_UNIT_ABBREVIATION_MICROSECONDS = "us";
        static constexpr std::string_view TIME_SCALE_UNIT_ABBREVIATION_MILLISECONDS = "ms";
        static constexpr std::string_view TIME_SCALE_UNIT_ABBREVIATION_SECONDS = "s";
        static constexpr std::string_view TIME_SCALE_UNIT_ABBREVIATION_MINUTES = "min";
        static constexpr std::string_view TIME_SCALE_UNIT_ABBREVIATION_HOURS = "h";
        static constexpr std::string_view TIME_SCALE_UNIT_ABBREVIATION_DAYS = "d";
        static constexpr std::string_view TIME_SCALE_UNIT_ABBREVIATION_WEEKS = "wk";
        static constexpr std::string_view TIME_SCALE_UNIT_ABBREVIATION_MONTHS = "mo";
        static constexpr std::string_view TIME_SCALE_UNIT_ABBREVIATION_YEARS = "yr";

        static constexpr std::string_view TEMPERATURE_UNIT_TYPE_CELSIUS = "celsius";
        static constexpr std::string_view TEMPERATURE_UNIT_TYPE_FAHRENHEIT = "fahrenheit";
        static constexpr std::string_view TEMPERATURE_UNIT_TYPE_KELVIN = "kelvin";
        static constexpr std::string_view TEMPERATURE_UNIT_TYPE_NONE = "none";

        static constexpr std::string_view DEFAULT_FILE_URI_IO_MIMETYPE =
            "application/octet-stream";
        static constexpr std::string_view DEFAULT_GROQ_CLOUD_CLIENT_API_TYPE =
            "llama3-8b-8192";
        static constexpr std::string_view DEFAULT_GMAIL_MAILER_SMTP_SERVER =
            "smtp.gmail.com:465";

        static constexpr double EPSILON = 1e-12;

        static std::unordered_map<std::string_view, TimeScaleUnit> TIME_SCALE_UNIT_ABBREVIATION_STRINGS;        
        static std::unordered_map<std::string_view, TemperatureUnitType> TEMPERATURE_UNIT_TYPE_STRINGS;
        static std::unordered_map<TemperatureUnitType, std::string_view> TEMPERATURE_UNIT_TYPE_ENUMS;
    };

    struct ValueEnumKeyDeleteHandler
    {
        void operator()(HKEY handler) const
        {
            if (handler)
            {
                RegCloseKey(handler);
            }
        }
    };

    struct NetworkPingResponse
    {
        int64_t round_trip_time_in_milliseconds;
    };

    struct NetworkPingSettings
    {
        std::chrono::milliseconds milliseconds_per_callback
        {
            QLogicaeCore::Constants::DEFAULT_MILLISECONDS_PER_CALLBACK
        };
        std::string host_address
        {
            QLogicaeCore::Constants::DEFAULT_HOST_ADDRESS
        };
        bool is_listening
        {
            QLogicaeCore::Constants::DEFAULT_IS_LISTENING
        };
        std::string name;
        std::function<void(const NetworkPingResponse&)> callback;
    };

    struct Json;

    enum class JsonValueType : uint8_t
    {
        NONE,
        NUMBER,
        FLOAT,
        STRING,
        ARRAY,
        OBJECT
    };

    bool convert_to_rapidjson_value(
        const Json&, rapidjson::Value&,
        rapidjson::Document::AllocatorType&);

    using JsonValuePointer = std::shared_ptr<Json>;

    using JsonValue = std::variant<
        std::nullptr_t,
        bool,
        int64_t,
        uint64_t,
        double,
        std::string,
        std::vector<JsonValuePointer>,
        std::map<std::string, JsonValuePointer>
    >;

    struct Json
    {
        JsonValue value;
        using Array = std::vector<JsonValuePointer>;
        using Object = std::map<std::string, JsonValuePointer>;

    };

    struct JsonVisitor
    {
        rapidjson::Value& target;
        rapidjson::Document::AllocatorType& allocator;

        void operator()(std::nullptr_t) const
        {
            target.SetNull();
        }
        void operator()(bool b) const
        {
            target.SetBool(b);
        }
        void operator()(int64_t i) const
        {
            target.SetInt64(i);
        }
        void operator()(uint64_t u) const
        {
            target.SetUint64(u);
        }
        void operator()(double d) const
        {
            target.SetDouble(d);
        }
        void operator()(const std::string& s) const
        {
            target.SetString(s.c_str(), static_cast<rapidjson::SizeType>(s.size()), allocator);
        }
        void operator()(const std::vector<std::shared_ptr<Json>>& items) const
        {
            target.SetArray();
            for (const auto& item : items)
            {
                rapidjson::Value value;

                convert_to_rapidjson_value(*item, value, allocator);
                target.PushBack(std::move(value), allocator);
            }
        }
        void operator()(const std::map<std::string, std::shared_ptr<Json>>& object) const
        {
            target.SetObject();
            for (const auto& [key, value_pointer] : object)
            {
                rapidjson::Value json_key, json_val;

                json_key.SetString(key.c_str(), static_cast<rapidjson::SizeType>(key.size()), allocator);
                convert_to_rapidjson_value(*value_pointer, json_val, allocator);
                target.AddMember(std::move(json_key), std::move(json_val), allocator);
            }
        }
    };

    constexpr std::string get_log_level_string(const LogLevel& level)
    {
        switch (level)
        {
        case LogLevel::ALL: return Constants::LOG_LEVEL_INFO.data();
        case LogLevel::INFO: return Constants::LOG_LEVEL_INFO.data();
        case LogLevel::DEBUG: return Constants::LOG_LEVEL_DEBUG.data();
        case LogLevel::SUCCESS: return Constants::LOG_LEVEL_SUCCESS.data();
        case LogLevel::WARNING: return Constants::LOG_LEVEL_WARNING.data();
        case LogLevel::CRITICAL: return Constants::LOG_LEVEL_CRITICAL.data();
        case LogLevel::EXCEPTION: return Constants::LOG_LEVEL_EXCEPTION.data();
        case LogLevel::HIGHLIGHTED_INFO: return Constants::LOG_LEVEL_HIGHLIGHTED_INFO.data();
        }
        
        return Constants::LOG_LEVEL_INFO.data();
    }

    struct CryptographerProperties
    {
        size_t size_t_1 = 0;
        size_t size_t_2 = 0;
        size_t size_t_3 = 0;
        size_t size_t_4 = 0;
        uint32_t uint32_t_1 = 0;
        uint32_t uint32_t_2 = 0;
        uint32_t uint32_t_3 = 0;
        uint32_t uint32_t_4 = 0;
    };

    static CryptographerProperties default_cryptographer_3_properties
    {
        .size_t_1 = 32,
        .size_t_2 = 16,
        .uint32_t_1 = 3,
        .uint32_t_2 = 1 << 16,
        .uint32_t_3 = 2
    };

    struct SmallTaskObject
    {
        SmallTaskObject() = default;

        template <typename Callable>
        SmallTaskObject(Callable&& callable)
        {
            function_wrapper = [callable =
                std::forward<Callable>(callable)]() mutable
                {
                    callable();
                };
        }

        void operator()() const
        {
            function_wrapper();
        }

        std::function<void()> function_wrapper;
    };

    struct WorkerQueue
    {
        std::map<TaskPriority, std::queue<SmallTaskObject>> priority_queues;
        std::mutex queue_mutex;
        std::condition_variable wake_signal;
    };

    struct JsonWebTokenTransformInput
    {
        std::string issuer;
        std::string data;
        std::string public_key;
        std::string private_key;
        std::chrono::seconds lifetime;
        std::map<std::string, std::string> claims;
    };

    struct JsonWebTokenReverseInput
    {
        std::string token;
        std::string issuer;
        std::string public_key;
    };

    struct JsonWebTokenReverseResult
    {
        bool is_successful = false;
        std::string message;
        std::string subject;
        std::map<std::string, std::string> headers;
        std::map<std::string, std::string> payloads;
    };

    struct VectorStringHash
    {
        std::size_t operator()(const std::vector<std::string>& vec) const noexcept
        {
            std::size_t seed = 0;
            std::hash<std::string> string_hasher;
            for (const auto& s : vec)
            {
                seed ^= string_hasher(s) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };

    struct VectorStringEqual
    {
        bool operator()(const std::vector<std::string>& lhs,
            const std::vector<std::string>& rhs) const noexcept
        {
            return lhs == rhs;
        }
    };

    struct ValidationPasswordRules
    {
        std::size_t minimum_length = 8;
        std::size_t maximum_length = 128;
        bool require_alpha_numerics = true;
        bool require_unique_characters = false;
        bool require_special_characters = true;
        bool require_uppercase_characters = true;
        bool require_lowercase_characters = true;
    };

    struct SQLiteBackend
    {
    public:
        explicit SQLiteBackend(sqlite3* raw_database);
        ~SQLiteBackend();

        sqlite3* database_handle;
    };

    struct SQLiteStatementData
    {
    public:
        explicit SQLiteStatementData(sqlite3_stmt* raw_statement);
        ~SQLiteStatementData();

        sqlite3_stmt* get() const noexcept;

    protected:
        sqlite3_stmt* statement_handle;
    };

    struct GroqCloudClientAPIPromptConfigurations
    {
        std::function<std::string()> api_key_extractor;
        std::string model = Constants::DEFAULT_GROQ_CLOUD_CLIENT_API_TYPE.data();
        double top_p = 1.0;
        double temperature = 0.7;
        double frequency_penalty = 0.0;
        double presence_penalty = 0.0;
        uint32_t maximum_tokens = 1024;
        std::vector<std::string> stop_sequences;
        std::optional<std::string> system_prompt;
        bool is_streaming_enabled = false;
        uint8_t retry_count = 3;
        std::chrono::milliseconds timeout_duration =
            std::chrono::seconds(10);
    };

    struct GroqCloudClientAPIChatMessage
    {
        std::string role;
        std::string content;
    };

    struct GroqCloudClientAPIRequest
    {
        std::vector<GroqCloudClientAPIChatMessage> messages;
    };

    struct GroqCloudClientAPIResponse
    {
        std::string id = "";
        std::string object = "";
        std::string model = "";
        uint32_t timestamp_created = 0;
        uint32_t total_tokens = 0;
        uint32_t prompt_tokens = 0;
        uint32_t completion_tokens = 0;
        uint32_t index = 0;
        std::string role = "";
        std::string content = "";
        std::string finish_reason = "";
        uint32_t status_code = 0;
        std::optional<std::string> error_type;
        std::optional<std::string> error_message;
    };

    struct RocksDBConfig
    {
        size_t block_cache_size = 64 * 1024 * 1024;
        size_t write_buffer_size = 64 * 1024 * 1024;
        int max_background_jobs = 4;
    };

    struct OutlierRemovalOptions
    {
        double factor;
        double threshold;
        double proportion;
        double significance_level;
    };

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

    struct StringMemoryPoolSnapshot
    {
        std::size_t pool_hits = 0;
        std::size_t bytes_used = 0;
        std::size_t pool_misses = 0;
        std::size_t interned_count = 0;
    };
}

