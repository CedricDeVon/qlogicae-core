#pragma once

#include "result.hpp"
#include "json.hpp"
#include "abstract_file_io.hpp"

#include <rapidjson/writer.h>
#include <rapidjson/pointer.h>
#include <rapidjson/allocators.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>

#include <any>
#include <future>
#include <shared_mutex>

namespace QLogicaeCore
{    
    class JsonFileIO :
        public AbstractFileIO
    {
    public:
        JsonFileIO();

        ~JsonFileIO();        
        
        JsonFileIO(
            const std::string&
        );
        
        JsonFileIO(
            const JsonFileIO& instance
        ) = delete;
        
        JsonFileIO(
            JsonFileIO&& instance
        ) noexcept = delete;
        
        JsonFileIO(
            const std::string&,
            const bool&
        );
        
        JsonFileIO& operator=(
            const JsonFileIO& instance
        ) = delete;
        
        JsonFileIO& operator=(
            JsonFileIO&& instance
        ) noexcept = delete;
        
        JsonFileIO(
            const std::string&,
            const std::string&
        );

        bool setup(
            const std::string& file_path
        );

        bool setup(
            const std::string& file_path,
            const bool& is_formatting_allowed
        );

        bool setup(
            const std::string& name,
            const std::string& file_path
        );

        void setup(
            Result<void>& result,
            const std::string& file_path
        );

        void setup(
            Result<void>& result,
            const std::string& file_path,
            const bool& is_formatting_allowed
        );

        void setup(
            Result<void>& result,
            const std::string& name,
            const std::string& file_path
        );

        std::string read();
        
        bool write(
            const std::string&
        );

        bool get_is_formatting_allowed();
        
        bool is_key_path_valid(
            const JsonPath&
        );
        
        void set_is_formatting_allowed(
            const bool&
        );

        bool get_bool(
            const JsonPath&
        );
        
        double get_double(
            const JsonPath&
        );
        
        std::string get_string(
            const JsonPath&
        );
        
        std::nullptr_t get_null(
            const JsonPath&
        );
        
        std::vector<std::any> get_array(
            const JsonPath&
        );
        
        std::unordered_map<std::string, std::any> get_object(
            const JsonPath&
        );

        bool insert_bool(
            const JsonPath&,
            const bool&
        );
        
        bool insert_double(
            const JsonPath&,
            const double&
        );
        
        bool insert_string(
            const JsonPath&,
            const std::string&
        );
        
        bool insert_null(
            const JsonPath&,
            const std::nullptr_t&
        );
        
        bool insert_array(
            const JsonPath&,
            const std::vector<std::any>&
        );
        
        bool insert_object(
            const JsonPath&,
            const std::unordered_map<std::string, std::any>&
        );

        bool update_bool(
            const JsonPath&,
            const bool&
        );
        
        bool update_double(
            const JsonPath&,
            const double&
        );
        
        bool update_string(
            const JsonPath&,
            const std::string&
        );
        
        bool update_null(
            const JsonPath&,
            const std::nullptr_t&
        );
        
        bool update_array(
            const JsonPath&,
            const std::vector<std::any>&
        );
        
        bool update_object(
            const JsonPath&,
            const std::unordered_map<std::string, std::any>&
        );

        std::future<std::string> read_async();
        
        std::future<bool> write_async(
            const std::string&
        );

        std::future<bool> get_bool_async(
            const JsonPath&
        );
        
        std::future<double> get_double_async(
            const JsonPath&
        );
        
        std::future<std::string> get_string_async(
            const JsonPath&
        );
        
        std::future<std::nullptr_t> get_null_async(
            const JsonPath&
        );
        
        std::future<std::vector<std::any>> get_array_async(
            const JsonPath&
        );
        
        std::future<std::unordered_map<std::string, std::any>>
        get_object_async(
            const JsonPath&
        );

        std::future<bool> insert_bool_async(
            const JsonPath&,
            const bool&
        );
        
        std::future<bool> insert_double_async(
            const JsonPath&,
            const double&
        );
        
        std::future<bool> insert_string_async(
            const JsonPath&,
            const std::string&
        );
        
        std::future<bool> insert_null_async(
            const JsonPath&,
            const std::nullptr_t&
        );
        
        std::future<bool> insert_array_async(
            const JsonPath&,
            const std::vector<std::any>&
        );
        
        std::future<bool> insert_object_async(
            const JsonPath&,
            const std::unordered_map<std::string, std::any>&
        );

        std::future<bool> update_bool_async(
            const JsonPath&,
            const bool&
        );
        
        std::future<bool> update_double_async(
            const JsonPath&,
            const double&
        );
        
        std::future<bool> update_string_async(
            const JsonPath&,
            const std::string&
        );
        
        std::future<bool> update_null_async(
            const JsonPath&,
            const std::nullptr_t&
        );
        
        std::future<bool> update_array_async(
            const JsonPath&,
            const std::vector<std::any>&
        );

        std::future<bool> update_object_async(
            const JsonPath&,
            const std::unordered_map<std::string, std::any>&
        );

        void read(
            Result<std::string>& result
        );

        void write(
            Result<bool>& result,
            const std::string& content
        );

        void get_is_formatting_allowed(
            Result<bool>& result
        );

        void is_key_path_valid(
            Result<bool>& result,
            const JsonPath& path
        );

        void set_is_formatting_allowed(
            Result<bool>& result,
            const bool& value
        );

        void get_bool(
            Result<bool>& result,
            const JsonPath& path
        );

        void get_double(
            Result<double>& result,
            const JsonPath& path
        );

        void get_string(
            Result<std::string>& result,
            const JsonPath& path
        );

        void get_null(
            Result<std::nullptr_t>& result,
            const JsonPath& path
        );

        void get_array(
            Result<std::vector<std::any>>& result,
            const JsonPath& path
        );

        void get_object(
            Result<std::unordered_map<std::string, std::any>>& result,
            const JsonPath& path
        );

        void insert_bool(
            Result<bool>& result,
            const JsonPath& path,
            const bool& value
        );

        void insert_double(
            Result<bool>& result,
            const JsonPath& path,
            const double&
        );

        void insert_string(
            Result<bool>& result,
            const JsonPath& path,
            const std::string&
        );

        void insert_null(
            Result<bool>& result,
            const JsonPath& path,
            const std::nullptr_t&
        );

        void insert_array(
            Result<bool>& result,
            const JsonPath& path,
            const std::vector<std::any>&
        );

        void insert_object(
            Result<bool>& result,
            const JsonPath& path,
            const std::unordered_map<std::string, std::any>&
        );

        void update_bool(
            Result<bool>& result,
            const JsonPath& path,
            const bool& value
        );

        void update_double(
            Result<bool>& result,
            const JsonPath& path,
            const double&
        );

        void update_string(
            Result<bool>& result,
            const JsonPath& path,
            const std::string&
        );

        void update_null(
            Result<bool>& result,
            const JsonPath& path,
            const std::nullptr_t&
        );

        void update_array(
            Result<bool>& result,
            const JsonPath& path,
            const std::vector<std::any>&
        );

        void update_object(
            Result<bool>& result,
            const JsonPath& path,
            const std::unordered_map<std::string, std::any>&
        );

        void read_async(
            Result<std::future<std::string>>& result
        );

        void write_async(
            Result<std::future<bool>>& result,
            const std::string&
        );

        void get_bool_async(
            Result<std::future<bool>>& result,
            const JsonPath& path
        );

        void get_double_async(
            Result<std::future<double>>& result,
            const JsonPath& path
        );

        void get_string_async(
            Result<std::future<std::string>>& result,
            const JsonPath& path
        );

        void get_null_async(
            Result<std::future<std::nullptr_t>>& result,
            const JsonPath& path
        );

         void get_array_async(
            Result<std::future<std::vector<std::any>>>& result,
            const JsonPath& path
        );

        void get_object_async(
            Result<std::future<std::unordered_map<std::string, std::any>>>& result,
            const JsonPath& path
        );

        void insert_bool_async(
            Result<std::future<bool>>& result,
            const JsonPath& path,
            const bool& value
        );

        void insert_double_async(
            Result<std::future<bool>>& result,
            const JsonPath& path,
            const double&
        );

        void insert_string_async(
            Result<std::future<bool>>& result,
            const JsonPath& path,
            const std::string&
        );

        void insert_null_async(
            Result<std::future<bool>>& result,
            const JsonPath& path,
            const std::nullptr_t&
        );

        void insert_array_async(
            Result<std::future<bool>>& result,
            const JsonPath& path,
            const std::vector<std::any>&
        );

        void insert_object_async(
            Result<std::future<bool>>& result,
            const JsonPath& path,
            const std::unordered_map<std::string, std::any>&
        );

        void update_bool_async(
            Result<std::future<bool>>& result,
            const JsonPath& path,
            const bool&
        );

        void update_double_async(
            Result<std::future<bool>>& result,
            const JsonPath& path,
            const double&
        );

        void update_string_async(
            Result<std::future<bool>>& result,
            const JsonPath& path,
            const std::string&
        );

        void update_null_async(
            Result<std::future<bool>>& result,
            const JsonPath& path,
            const std::nullptr_t&
        );

        void update_array_async(
            Result<std::future<bool>>& result,
            const JsonPath& path,
            const std::vector<std::any>&
        );

        void update_object_async(
            Result<std::future<bool>>& result,
            const JsonPath& path,
            const std::unordered_map<std::string, std::any>&
        );

        static JsonFileIO& get_instance();

        static void get_instance(
            Result<JsonFileIO*>& result
        );

    protected:
        std::mutex _mutex;

        bool _is_formatting_allowed;

        rapidjson::Pointer build_pointer(
            const JsonPath&
        );

        std::string to_string(
            const rapidjson::Document&
        );

        rapidjson::Value make_value(
            const bool&,
            rapidjson::Document::AllocatorType&
        );

        rapidjson::Value make_value(
            const double&,
            rapidjson::Document::AllocatorType&
        );

        rapidjson::Value make_value(
            std::nullptr_t,
            rapidjson::Document::AllocatorType&
        );

        rapidjson::Value make_value(
            const std::string&,
            rapidjson::Document::AllocatorType&
        );

        rapidjson::Value make_value(
            const std::vector<std::any>&,
            rapidjson::Document::AllocatorType&
        );

        rapidjson::Value make_value(
            const std::unordered_map<std::string, std::any>&,
            rapidjson::Document::AllocatorType&
        );
    };

    inline static JsonFileIO& JSON_FILE_IO =
        JsonFileIO::get_instance();
}
