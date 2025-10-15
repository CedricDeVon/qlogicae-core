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
    class JsonFileIO : public AbstractFileIO
    {
    public:
        ~JsonFileIO();
        
        JsonFileIO() = default;
        
        JsonFileIO(const std::string&);
        
        JsonFileIO(const JsonFileIO&) = delete;
        
        JsonFileIO(JsonFileIO&&) noexcept = delete;
        
        JsonFileIO(const std::string&, const bool&);
        
        JsonFileIO& operator=(const JsonFileIO&) = delete;
        
        JsonFileIO& operator=(JsonFileIO&&) noexcept = delete;
        
        JsonFileIO(const std::string&, const std::string&);

        std::string read();
        
        bool write(const std::string&);

        bool get_is_formatting_allowed();
        
        bool is_key_path_valid(const JsonPath&);
        
        void set_is_formatting_allowed(const bool&);

        bool get_bool(const JsonPath&);
        
        double get_double(const JsonPath&);
        
        std::string get_string(const JsonPath&);
        
        std::nullptr_t get_null(const JsonPath&);
        
        std::vector<std::any> get_array(const JsonPath&);
        
        std::unordered_map<std::string, std::any> get_object(const JsonPath&);

        bool insert_bool(const JsonPath&, const bool&);
        
        bool insert_double(const JsonPath&, const double&);
        
        bool insert_string(const JsonPath&, const std::string&);
        
        bool insert_null(const JsonPath&, const std::nullptr_t&);
        
        bool insert_array(const JsonPath&, const std::vector<std::any>&);
        
        bool insert_object(const JsonPath&, const std::unordered_map<std::string, std::any>&);

        bool update_bool(const JsonPath&, const bool&);
        
        bool update_double(const JsonPath&, const double&);
        
        bool update_string(const JsonPath&, const std::string&);
        
        bool update_null(const JsonPath&, const std::nullptr_t&);
        
        bool update_array(const JsonPath&, const std::vector<std::any>&);
        
        bool update_object(const JsonPath&, const std::unordered_map<std::string, std::any>&);



        std::future<std::string> read_async();
        
        std::future<bool> write_async(const std::string&);

        std::future<bool> get_bool_async(const JsonPath&);
        
        std::future<double> get_double_async(const JsonPath&);
        
        std::future<std::string> get_string_async(const JsonPath&);
        
        std::future<std::nullptr_t> get_null_async(const JsonPath&);
        
        std::future<std::vector<std::any>> get_array_async(const JsonPath&);
        
        std::future<std::unordered_map<std::string, std::any>> get_object_async(const JsonPath&);

        std::future<bool> insert_bool_async(const JsonPath&, const bool&);
        
        std::future<bool> insert_double_async(const JsonPath&, const double&);
        
        std::future<bool> insert_string_async(const JsonPath&, const std::string&);
        
        std::future<bool> insert_null_async(const JsonPath&, const std::nullptr_t&);
        
        std::future<bool> insert_array_async(const JsonPath&, const std::vector<std::any>&);
        
        std::future<bool> insert_object_async(const JsonPath&, const std::unordered_map<std::string, std::any>&);

        std::future<bool> update_bool_async(const JsonPath&, const bool&);
        
        std::future<bool> update_double_async(const JsonPath&, const double&);
        
        std::future<bool> update_string_async(const JsonPath&, const std::string&);
        
        std::future<bool> update_null_async(const JsonPath&, const std::nullptr_t&);
        
        std::future<bool> update_array_async(const JsonPath&, const std::vector<std::any>&);

        std::future<bool> update_object_async(const JsonPath&, const std::unordered_map<std::string, std::any>&);

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

    protected:
        std::mutex _mutex;
        bool _is_formatting_allowed;

        rapidjson::Pointer build_pointer(const JsonPath&);

        std::string to_string(const rapidjson::Document&);

        rapidjson::Value make_value(const bool&, rapidjson::Document::AllocatorType&);

        rapidjson::Value make_value(const double&, rapidjson::Document::AllocatorType&);

        rapidjson::Value make_value(std::nullptr_t, rapidjson::Document::AllocatorType&);

        rapidjson::Value make_value(const std::string&, rapidjson::Document::AllocatorType&);

        rapidjson::Value make_value(const std::vector<std::any>&, rapidjson::Document::AllocatorType&);

        rapidjson::Value make_value(const std::unordered_map<std::string, std::any>&, rapidjson::Document::AllocatorType&);
    };
}

