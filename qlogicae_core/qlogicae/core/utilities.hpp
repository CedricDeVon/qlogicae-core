#pragma once

#include <sqlite3.h>
#include <absl/time/time.h>
#include <rapidjson/document.h>

#include <ios>
#include <map>
#include <mutex>
#include <queue>
#include <future>
#include <chrono>
#include <vector>
#include <variant>
#include <cstdint>
#include <Windows.h>
#include <functional>
#include <string_view>
#include <unordered_map>
#include <condition_variable>

#include "system_access.hpp"

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

	class Utilities
	{
	public:
        const unsigned int DEFAULT_MILLISECONDS_PER_CALLBACK =
            1000;
        
        const bool DEFAULT_IS_LISTENING =
            true;

        const HKEY DEFAULT_HKEY =
            HKEY_CURRENT_USER;
        
        const DWORD HKEY_MAXIMUM_VALUE_SIZE =
            1 << 16;
        
        const std::wstring DEFAULT_NAME_KEY =
            L"Data";
        
        const std::wstring DEFAULT_SUB_KEY =
            L"Software\\App";
        
        const REGSAM REGULAR_ACCESS_FLAGS =
            KEY_READ | KEY_SET_VALUE;

        const size_t RANDOM_SIZE_T_BITS =
            8;
        
        const double RANDOM_DOUBLE_MINIMUM =
            0.0;
        
        const double RANDOM_DOUBLE_MAXIMUM =
            1.0;
        
        const double RANDOM_BOOLEAN_MAXIMUM =
            0.5;
        
        const std::string HEXADECIMAL_CHARACTERSET_1 =
            "0123456789abcdef";

        const std::string HEXADECIMAL_CHARACTERSET_2 =
            "0123456789ABCDEF";
        
        const std::string ALPHANUMERIC_CHARACTERSET =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        
        const std::string FULL_VISIBLE_ASCII_CHARACTERSET =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

        const unsigned int UNIX_START_YEAR_OFFSET =
            1'900;
        
        const char TIME_FORMAT_ISO_8601[18] =
            "%Y-%m-%dT%H:%M:%S";
        
        const char TIME_FORMAT_FULL_TIMESTAMP[20] =
            "%Y-%m-%d] [%H:%M:%S";
        
        const char TIME_FORMAT_FULL_DASHED_TIMESTAMP[18] =
            "%Y-%m-%d-%H-%M-%S";
        
        const char TIME_FORMAT_HOUR_12[12] =
            "%I:%M:%S %p";
        
        const char TIME_FORMAT_HOUR_24[9] =
            "%H:%M:%S";
        
        const char TIME_FORMAT_DATE_DASHED[9] = 
            "%Y-%m-%d";
        
        const char TIME_FORMAT_DATE_MDY_SLASHED[9] =
            "%m/%d/%Y";
        
        const char TIME_FORMAT_DATE_DMY_SLASHED[9] =
            "%d/%m/%Y";
        
        const char TIME_FORMAT_DATE_DMY_SPACED[9] =
            "%d %m %Y";
        
        const char TIME_FORMAT_DATE_VERBOSE[14] =
            "%A, %B %d, %Y";
        
        const char TIME_FORMAT_EMPTY[1] =
            "";
        
        const char TIME_FORMAT_INVALID[19] =
            "Invalid TimeFormat";
        
        const char TIME_FORMAT_PART_1[5] =
            "ms: ";
        
        const char TIME_FORMAT_PART_2[7] =
            ", us: ";
        
        const char TIME_FORMAT_PART_3[7] =
            ", ns: ";
        
        const char TIME_FORMAT_PART_4 =
            '.';
        
        const char TIME_FORMAT_PART_5 =
            ':';
        
        const char TIME_FORMAT_PART_6 =
            '0';
        
        const std::streamsize TIME_FORMAT_MIL_MIC_NAN_STREAM_SIZE =
            3;

        const std::string STRING_EMPTY =
            "";
        
        const std::string STRING_NONE_1 =
            "None";
        
        const std::string STRING_NONE_2 =
            "N/A";

        const std::string LOG_LEVEL_ALL =
            "INFO";
        
        const std::string LOG_LEVEL_INFO =
            "INFO";
        
        const std::string LOG_LEVEL_DEBUG =
            "DEBUG";
        
        const std::string LOG_LEVEL_SUCCESS =
            "SUCCESS";
        
        const std::string LOG_LEVEL_WARNING =
            "WARNING";
        
        const std::string LOG_LEVEL_CRITICAL =
            "CRITICAL";
        
        const std::string LOG_LEVEL_EXCEPTION =
            "EXCEPTION";
        
        const std::string LOG_LEVEL_HIGHLIGHTED_INFO =
            "INFO";

        const std::string DEFAULT_HOST_ADDRESS =
            "1.1.1.1";

        const double SECONDS_OVER_NANOSECONDS =
            1'000'000'000.0;
        
        const double SECONDS_OVER_MICROSECONDS =
            1'000'000.0;
        
        const double SECONDS_OVER_MILLISECONDS =
            1'000.0;
        
        const double SECONDS_PER_MINUTE =
            60.0;
        
        const double SECONDS_PER_HOUR =
            3'600.0;
        
        const double SECONDS_PER_DAY =
            86'400.0;
        
        const double SECONDS_PER_WEEK =
            604'800.0;

        const double SECONDS_PER_MONTH =
            2'629'746.0;

        const double SECONDS_PER_YEAR =
            31'557'600.0;

        const std::string TIME_SCALE_UNIT_FULL_NAME_NANOSECONDS =
            "Nanosecond(s)";

        const std::string TIME_SCALE_UNIT_FULL_NAME_MICROSECONDS =
            "Microsecond(s)";

        const std::string TIME_SCALE_UNIT_FULL_NAME_MILLISECONDS =
            "Millisecond(s)";

        const std::string TIME_SCALE_UNIT_FULL_NAME_SECONDS =
            "Second(s)";

        const std::string TIME_SCALE_UNIT_FULL_NAME_MINUTES =
            "Minute(s)";

        const std::string TIME_SCALE_UNIT_FULL_NAME_HOURS =
            "Hour(s)";

        const std::string TIME_SCALE_UNIT_FULL_NAME_DAYS =
            "Day(s)";

        const std::string TIME_SCALE_UNIT_FULL_NAME_WEEKS =
            "Week(s)";

        const std::string TIME_SCALE_UNIT_FULL_NAME_MONTHS =
            "Month(s)";

        const std::string TIME_SCALE_UNIT_FULL_NAME_YEARS =
            "Year(s)";

        const std::string TIME_SCALE_UNIT_ABBREVIATION_NANOSECONDS =
            "ns";

        const std::string TIME_SCALE_UNIT_ABBREVIATION_MICROSECONDS =
            "us";

        const std::string TIME_SCALE_UNIT_ABBREVIATION_MILLISECONDS =
            "ms";

        const std::string TIME_SCALE_UNIT_ABBREVIATION_SECONDS =
            "s";

        const std::string TIME_SCALE_UNIT_ABBREVIATION_MINUTES =
            "min";

        const std::string TIME_SCALE_UNIT_ABBREVIATION_HOURS =
            "h";

        const std::string TIME_SCALE_UNIT_ABBREVIATION_DAYS =
            "d";

        const std::string TIME_SCALE_UNIT_ABBREVIATION_WEEKS =
            "wk";

        const std::string TIME_SCALE_UNIT_ABBREVIATION_MONTHS =
            "mo";

        const std::string TIME_SCALE_UNIT_ABBREVIATION_YEARS =
            "yr";

        const std::string TEMPERATURE_UNIT_TYPE_CELSIUS =
            "celsius";

        const std::string TEMPERATURE_UNIT_TYPE_FAHRENHEIT =
            "fahrenheit";

        const std::string TEMPERATURE_UNIT_TYPE_KELVIN =
            "kelvin";

        const std::string TEMPERATURE_UNIT_TYPE_NONE =
            "none";

        const std::string DEFAULT_FILE_URI_IO_MIMETYPE =
            "application/octet-stream";

        const std::string DEFAULT_GROQ_CLOUD_CLIENT_API_TYPE =
            "llama3-8b-8192";

        const std::string DEFAULT_GMAIL_MAILER_SMTP_SERVER =
            "smtp.gmail.com:465";

        const double EPSILON = 1e-12;

        const std::string INNO_SETUP = "inno-setup";

        const std::string VISUAL_STUDIO_2022_1 = "vs2022";

        const std::string VISUAL_STUDIO_2022_2 = "Visual Studio 2022";

        const std::string VISUAL_STUDIO_2022_X64_BUILD_ARCHITECTURE = "x64";

        const std::string VISUAL_STUDIO_2022_X86_BUILD_ARCHITECTURE = "x86";

        const std::string VISUAL_STUDIO_2022_RELEASE_BUILD = "Release";

        const std::string VISUAL_STUDIO_2022_DEBUG_BUILD = "Debug";

        const std::string WINDOWS_REGISTRY_HKCU_ROOT_PATH_1 = "hkcu";

        const std::string WINDOWS_REGISTRY_HKLM_ROOT_PATH_1 = "hklm";

        const std::string WINDOWS_REGISTRY_HKCU_ROOT_PATH_2 = "HKCU";

        const std::string WINDOWS_REGISTRY_HKLM_ROOT_PATH_2 = "HKLM";

        const std::string ENVIRONMENT_VARIABLE_USER_1 = "user";

        const std::string ENVIRONMENT_VARIABLE_SYSTEM_1 = "system";

        const std::string ENVIRONMENT_VARIABLE_USER_2 = "USER";

        const std::string ENVIRONMENT_VARIABLE_SYSTEM_2 = "SYSTEM";

        const std::unordered_map<TimeScaleUnit, std::string_view> TIME_SCALE_UNIT_ABBREVIATION_ENUMS =
        {
            { TimeScaleUnit::NANOSECONDS, TIME_SCALE_UNIT_ABBREVIATION_NANOSECONDS },
            { TimeScaleUnit::MICROSECONDS, TIME_SCALE_UNIT_ABBREVIATION_MICROSECONDS },
            { TimeScaleUnit::MILLISECONDS, TIME_SCALE_UNIT_ABBREVIATION_MILLISECONDS },
            { TimeScaleUnit::SECONDS, TIME_SCALE_UNIT_ABBREVIATION_SECONDS },
            { TimeScaleUnit::MINUTES, TIME_SCALE_UNIT_ABBREVIATION_MINUTES },
            { TimeScaleUnit::HOURS, TIME_SCALE_UNIT_ABBREVIATION_HOURS },
            { TimeScaleUnit::DAYS, TIME_SCALE_UNIT_ABBREVIATION_DAYS },
            { TimeScaleUnit::WEEKS, TIME_SCALE_UNIT_ABBREVIATION_WEEKS },
            { TimeScaleUnit::MONTHS, TIME_SCALE_UNIT_ABBREVIATION_MONTHS },
            { TimeScaleUnit::YEARS, TIME_SCALE_UNIT_ABBREVIATION_YEARS }
        };

        const std::unordered_map<std::string_view, TimeScaleUnit> TIME_SCALE_UNIT_ABBREVIATION_STRINGS =
        {
            { TIME_SCALE_UNIT_ABBREVIATION_NANOSECONDS, TimeScaleUnit::NANOSECONDS },
            { TIME_SCALE_UNIT_ABBREVIATION_MICROSECONDS, TimeScaleUnit::MICROSECONDS },
            { TIME_SCALE_UNIT_ABBREVIATION_MILLISECONDS, TimeScaleUnit::MILLISECONDS },
            { TIME_SCALE_UNIT_ABBREVIATION_SECONDS, TimeScaleUnit::SECONDS },
            { TIME_SCALE_UNIT_ABBREVIATION_MINUTES, TimeScaleUnit::MINUTES },
            { TIME_SCALE_UNIT_ABBREVIATION_HOURS, TimeScaleUnit::HOURS },
            { TIME_SCALE_UNIT_ABBREVIATION_DAYS, TimeScaleUnit::DAYS },
            { TIME_SCALE_UNIT_ABBREVIATION_WEEKS, TimeScaleUnit::WEEKS },
            { TIME_SCALE_UNIT_ABBREVIATION_MONTHS, TimeScaleUnit::MONTHS },
            { TIME_SCALE_UNIT_ABBREVIATION_YEARS, TimeScaleUnit::YEARS }
        };

        const std::unordered_map<TemperatureUnitType, std::string_view> TEMPERATURE_UNIT_TYPE_ENUMS =
        {
            { TemperatureUnitType::CELSIUS, TEMPERATURE_UNIT_TYPE_CELSIUS },
            { TemperatureUnitType::FAHRENHEIT, TEMPERATURE_UNIT_TYPE_FAHRENHEIT },
            { TemperatureUnitType::KELVIN, TEMPERATURE_UNIT_TYPE_KELVIN },
            { TemperatureUnitType::NONE, TEMPERATURE_UNIT_TYPE_NONE }
        };

        const std::unordered_map<std::string_view, TemperatureUnitType> TEMPERATURE_UNIT_TYPE_STRINGS =
        {
            { TEMPERATURE_UNIT_TYPE_CELSIUS, TemperatureUnitType::CELSIUS },
            { TEMPERATURE_UNIT_TYPE_FAHRENHEIT, TemperatureUnitType::FAHRENHEIT },
            { TEMPERATURE_UNIT_TYPE_KELVIN, TemperatureUnitType::KELVIN },
            { TEMPERATURE_UNIT_TYPE_NONE, TemperatureUnitType::NONE }
        };

        const std::unordered_map<QLogicaeVisualStudio2022BuildArchitecture, std::string_view> VISUAL_STUDIO_2022_BUILD_ARCHITECTURE_ENUMS =
        {
            { QLogicaeVisualStudio2022BuildArchitecture::X64, VISUAL_STUDIO_2022_X64_BUILD_ARCHITECTURE },
            { QLogicaeVisualStudio2022BuildArchitecture::X86, VISUAL_STUDIO_2022_X86_BUILD_ARCHITECTURE }
        };

        const std::unordered_map<std::string_view, QLogicaeVisualStudio2022BuildArchitecture> VISUAL_STUDIO_2022_BUILD_ARCHITECTURE_STRINGS =
        {
            { VISUAL_STUDIO_2022_X64_BUILD_ARCHITECTURE, QLogicaeVisualStudio2022BuildArchitecture::X64 },
            { VISUAL_STUDIO_2022_X86_BUILD_ARCHITECTURE, QLogicaeVisualStudio2022BuildArchitecture::X86 },
        };
        
        const std::unordered_map<QLogicaeVisualStudio2022Build, std::string_view> VISUAL_STUDIO_2022_BUILD_ENUMS =
        {
            { QLogicaeVisualStudio2022Build::RELEASE, VISUAL_STUDIO_2022_RELEASE_BUILD },
            { QLogicaeVisualStudio2022Build::DEBUG, VISUAL_STUDIO_2022_DEBUG_BUILD }
        };

        const std::unordered_map<std::string_view, QLogicaeVisualStudio2022Build> VISUAL_STUDIO_2022_BUILD_STRINGS =
        {
            { VISUAL_STUDIO_2022_RELEASE_BUILD, QLogicaeVisualStudio2022Build::RELEASE },
            { VISUAL_STUDIO_2022_DEBUG_BUILD, QLogicaeVisualStudio2022Build::DEBUG },
        };

        const std::unordered_map<WindowsRegistryRootPath, std::string_view> WINDOWS_REGISTRY_ROOT_PATH_ENUMS =
        {
            { WindowsRegistryRootPath::HKCU, WINDOWS_REGISTRY_HKCU_ROOT_PATH_1 },
            { WindowsRegistryRootPath::HKLM, WINDOWS_REGISTRY_HKLM_ROOT_PATH_1 }
        };

        const std::unordered_map<std::string_view, WindowsRegistryRootPath> WINDOWS_REGISTRY_ROOT_PATH_STRINGS =
        {
            { WINDOWS_REGISTRY_HKCU_ROOT_PATH_1, WindowsRegistryRootPath::HKCU },
            { WINDOWS_REGISTRY_HKLM_ROOT_PATH_1, WindowsRegistryRootPath::HKLM },
        };

        const std::unordered_map<EnvironmentVariable, std::string_view> ENVIRONMENT_VARIABLE_ENUMS =
        {
            { EnvironmentVariable::USER, ENVIRONMENT_VARIABLE_USER_1 },
            { EnvironmentVariable::SYSTEM, ENVIRONMENT_VARIABLE_SYSTEM_1 }
        };

        const std::unordered_map<std::string_view, EnvironmentVariable> ENVIRONMENT_VARIABLE_STRINGS =
        {
            { ENVIRONMENT_VARIABLE_USER_1, EnvironmentVariable::USER },
            { ENVIRONMENT_VARIABLE_SYSTEM_1, EnvironmentVariable::SYSTEM },
        };

        const std::unordered_map<SupportedQLogicaeIDE, std::string_view> SUPPORTED_IDE_ENUMS =
        {
            { SupportedQLogicaeIDE::VISUAL_STUDIO_2022, VISUAL_STUDIO_2022_1 }
        };

        const std::unordered_map<std::string_view, SupportedQLogicaeIDE> SUPPORTED_IDE_STRINGS =
        {
            { VISUAL_STUDIO_2022_1, SupportedQLogicaeIDE::VISUAL_STUDIO_2022 }
        };

        const std::unordered_map<SupportedQLogicaeInstaller, std::string_view> SUPPORTED_INSTALLER_ENUMS =
        {
            { SupportedQLogicaeInstaller::INNO_SETUP, INNO_SETUP }
        };

        const std::unordered_map<std::string_view, SupportedQLogicaeInstaller> SUPPORTED_INSTALLER_STRINGS =
        {
            { INNO_SETUP, SupportedQLogicaeInstaller::INNO_SETUP }
        };       

		const std::string RELATIVE_DOT_QLOGICAE_FOLDER_PATH =
			".qlogicae";

		const std::string RELATIVE_QLOGICAE_FOLDER_PATH =
			"qlogicae";

		const std::string RELATIVE_APPLICATION_FOLDER_PATH =
			"application";

		const std::string RELATIVE_CONFIGURATIONS_FOLDER_PATH =
			"configurations";

		const std::string RELATIVE_ASSETS_FOLDER_PATH =
			"assets";

		const std::string RELATIVE_DOCUMENTATION_FOLDER_PATH =
			"documentation";

		const std::string RELATIVE_QLOGICAE_FILE_PATH =
			"qlogicae.json";

		const std::string RELATIVE_ENVIRONMENT_FILE_PATH =
			"environment.json";

		const std::string RELATIVE_LICENSE_FILE_PATH =
			"LICENSE.txt";

		const std::string RELATIVE_APPLICATION_ICON_FILE_PATH =
			"application.ico";

        const std::string RELATIVE_QLOGICAE_WINDOWS_REGISTRY_SUB_PATH =
            "Software\\QLogicae";

        std::string FULL_EXECUTABLE_FOLDER_PATH;

        std::string FULL_EXECUTED_FOLDER_PATH;

        std::string FULL_ROAMING_APPDATA_FOLDER_PATH;

        std::string FULL_LOCAL_APPDATA_FOLDER_PATH;

        std::string FULL_PROGRAMDATA_FOLDER_PATH;

		std::string FULL_APPLICATION_QLOGICAE_FOLDER_PATH;

		std::string FULL_APPLICATION_QLOGICAE_PRIVATE_FOLDER_PATH;

		std::string FULL_APPLICATION_QLOGICAE_PUBLIC_FOLDER_PATH;
			
		std::string FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_FOLDER_PATH;
			
		std::string FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_FOLDER_PATH;
			
		std::string FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_QLOGICAE_FILE_PATH;
			
		std::string FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_ENVIRONMENT_FILE_PATH;
			
		std::string FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_ASSETS_FOLDER_PATH;
			
		std::string FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_ASSETS_APPLICATION_ICON_FILE_PATH;
			
		std::string FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_DOCUMENTATION_FOLDER_PATH;
			
		std::string FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_DOCUMENTATION_LICENSE_FILE_PATH;
			
		static Utilities& get_instance();

	protected:
		Utilities();
		~Utilities() = default;
		Utilities(const Utilities&) = default;
		Utilities(Utilities&&) noexcept = delete;
		Utilities& operator = (Utilities&&) = default;
		Utilities& operator = (const Utilities&) = delete;

		std::mutex _mutex;
	};

    inline static Utilities& UTILITIES =
        Utilities::get_instance();

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

    struct NetworkPingResponse
    {
        int64_t round_trip_time_in_milliseconds;
    };

    struct NetworkPingSettings
    {
        std::chrono::milliseconds milliseconds_per_callback
        {
            UTILITIES.DEFAULT_MILLISECONDS_PER_CALLBACK
        };
        std::string host_address
        {
            UTILITIES.DEFAULT_HOST_ADDRESS
        };
        bool is_listening
        {
            UTILITIES.DEFAULT_IS_LISTENING
        };
        std::string name;
        std::function<void(const NetworkPingResponse&)> callback;
    };

    struct GroqCloudClientAPIPromptConfigurations
    {
        std::function<std::string()> api_key_extractor;
        std::string model = UTILITIES.DEFAULT_GROQ_CLOUD_CLIENT_API_TYPE.data();
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
    
    constexpr std::string get_log_level_string(const LogLevel& level)
    {
        switch (level)
        {
        case LogLevel::ALL: return UTILITIES.LOG_LEVEL_INFO;
        case LogLevel::INFO: return UTILITIES.LOG_LEVEL_INFO;
        case LogLevel::DEBUG: return UTILITIES.LOG_LEVEL_DEBUG;
        case LogLevel::SUCCESS: return UTILITIES.LOG_LEVEL_SUCCESS;
        case LogLevel::WARNING: return UTILITIES.LOG_LEVEL_WARNING;
        case LogLevel::CRITICAL: return UTILITIES.LOG_LEVEL_CRITICAL;
        case LogLevel::EXCEPTION: return UTILITIES.LOG_LEVEL_EXCEPTION;
        case LogLevel::HIGHLIGHTED_INFO: return UTILITIES.LOG_LEVEL_HIGHLIGHTED_INFO;
        }
        
        return UTILITIES.LOG_LEVEL_INFO;
    }
}

