#pragma once

#include "pch.h"

namespace QLogicaeCore
{    
    struct Constants
    {
        static constexpr unsigned int DEFAULT_MILLISECONDS_PER_CALLBACK = 1000;
        static constexpr bool DEFAULT_IS_LISTENING = true;

        static constexpr HKEY DEFAULT_HKEY = HKEY_CURRENT_USER;
        static constexpr int HKEY_MAXIMUM_VALUE_SIZE = 1 << 16;
        static constexpr std::wstring_view DEFAULT_NAME_KEY = L"Data";
        static constexpr std::wstring_view DEFAULT_SUB_KEY = L"Software\\App";
        static constexpr REGSAM REGULAR_ACCESS_FLAGS = KEY_READ | KEY_SET_VALUE;

        static constexpr size_t RANDOM_SIZE_T_BITS = 8;
        static constexpr double RANDOM_DOUBLE_MINIMUM = 0.0;
        static constexpr double RANDOM_DOUBLE_MAXIMUM = 1.0;
        static constexpr double RANDOM_BOOLEAN_MAXIMUM = 0.5;
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

        static constexpr std::string_view LOG_PART_1 = "[";
        static constexpr std::string_view LOG_PART_2 = "] [";
        static constexpr std::string_view LOG_PART_3 = "]\t";
        static constexpr std::string_view LOG_PART_4 = "\n";
        static constexpr std::string_view LOG_LEVEL_ALL = "INFO";
        static constexpr std::string_view LOG_LEVEL_INFO = "INFO";
        static constexpr std::string_view LOG_LEVEL_DEBUG = "DEBUG";
        static constexpr std::string_view LOG_LEVEL_SUCCESS = "SUCCESS";
        static constexpr std::string_view LOG_LEVEL_WARNING = "WARNING";
        static constexpr std::string_view LOG_LEVEL_CRITICAL = "CRITICAL";
        static constexpr std::string_view LOG_LEVEL_EXCEPTION = "EXCEPTION";
        static constexpr std::string_view LOG_LEVEL_HIGHLIGHTED_INFO = "INFO";

        static constexpr std::string_view DEFAULT_HOST_ADDRESS = "1.1.1.1";
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

    enum class JsonValueType
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

    enum class EncodingType
    {
        HEX,
        UTF8,
        BASE64
    };

    
    enum class FileMode
    {
        READ,
        WRITE,
        APPEND
    };

    enum class TimeFormat
    {
        Unix,
        ISO8601,
        FullTimestamp,
        Hour12,
        Hour24,
        MillisMicrosNanos,
        DateDashed,
        DateMDYSlashed,
        DateDMYSlashed,
        DateDMYSpaced,
        DateVerbose
    };

    enum class TimeZone
    {
        UTC,
        Local
    };

    enum class LogMedium
    {
        ALL,
        FILE,
        CONSOLE
    };

    enum class LogLevel
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

    constexpr std::string_view get_log_level_string(const LogLevel& level)
    {
        switch (level)
        {
        case LogLevel::ALL: return Constants::LOG_LEVEL_INFO;
        case LogLevel::INFO: return Constants::LOG_LEVEL_INFO;
        case LogLevel::DEBUG: return Constants::LOG_LEVEL_DEBUG;
        case LogLevel::SUCCESS: return Constants::LOG_LEVEL_SUCCESS;
        case LogLevel::WARNING: return Constants::LOG_LEVEL_WARNING;
        case LogLevel::CRITICAL: return Constants::LOG_LEVEL_CRITICAL;
        case LogLevel::EXCEPTION: return Constants::LOG_LEVEL_EXCEPTION;
        case LogLevel::HIGHLIGHTED_INFO: return Constants::LOG_LEVEL_HIGHLIGHTED_INFO;
        }

        return Constants::LOG_LEVEL_INFO;
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

    enum class TaskPriority
    {
        High = 0,
        Normal = 1,
        Low = 2
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
}

