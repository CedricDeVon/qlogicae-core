#include "pch.h"

#include "json_file_io.hpp"
using namespace std;

namespace QLogicaeCore {

    using namespace rapidjson;

    JsonFileIO::~JsonFileIO() {}

    JsonFileIO::JsonFileIO(const std::string_view& path)
        : AbstractFileIO(path) {
        _is_formatting_allowed = false;
    }

    JsonFileIO::JsonFileIO(
        const std::string_view& path,
        const bool& is_formatting_allowed)
            : AbstractFileIO(path)
    {
        _is_formatting_allowed = is_formatting_allowed;
    }

    JsonFileIO::JsonFileIO(
        const std::string_view& name,
        const std::string_view& path)
            : AbstractFileIO(name, path)
    {
        _is_formatting_allowed = false;
    }

    bool JsonFileIO::get_is_formatting_allowed()
    {
        return _is_formatting_allowed;
    }

    void JsonFileIO::set_is_formatting_allowed(const bool& value)
    {
        _is_formatting_allowed = value;
    }

    std::string JsonFileIO::read()
    {
        if (_file_path.empty())
        {
            return "";
        }

        try
        {
            fast_io::native_file_loader loader{ _file_path };

            return std::string(
                loader.data(), loader.data() + loader.size());
        }
        catch (...)
        {
            return "";
        }
    }

    bool JsonFileIO::write(const std::string_view& content)
    {
        if (_file_path.empty())
        {
            return "";
        }

        try
        {
            fast_io::obuf_file writer{ _file_path };
            fast_io::io::print(writer, content);

            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    Pointer JsonFileIO::build_pointer(const JsonPath& key_path)
    {
        std::string pointer_string;
        for (const auto& key : key_path)
        {
            if (std::holds_alternative<std::string_view>(key))
            {
                pointer_string += "/" + std::string(
                    std::get<std::string_view>(key));
            }
            else
            {
                pointer_string += "/" + std::to_string(
                    std::get<int>(key));
            }
        }

        return Pointer(pointer_string.c_str());
    }

    std::string JsonFileIO::to_string(const Document& document)
    {
        StringBuffer buffer;
        PrettyWriter<StringBuffer> writer(buffer);
        document.Accept(writer);

        return buffer.GetString();
    }

    bool JsonFileIO::is_key_path_valid(const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return false;
        }

        Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);

        return pointer.Get(document) != nullptr;
    }

    std::string JsonFileIO::get_string(const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return "";
        }

        Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return "";
        }

        auto pointer = build_pointer(path);
        const Value* value = pointer.Get(document);

        return (value && value->IsString()) ? value->GetString() : "";
    }

    bool JsonFileIO::get_bool(const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return false;
        }

        Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto ptr = build_pointer(path);
        const Value* val = ptr.Get(document);

        return (val && val->IsBool()) ? val->GetBool() : false;
    }

    double JsonFileIO::get_double(const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return 0.0;
        }

        Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return 0.0;
        }

        auto ptr = build_pointer(path);
        const Value* val = ptr.Get(document);

        return (val && val->IsNumber()) ? val->GetDouble() : 0.0;
    }

    std::nullptr_t JsonFileIO::get_null(const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return nullptr;
        }

        Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return nullptr;
        }

        auto ptr = build_pointer(path);
        const Value* val = ptr.Get(document);

        return (val && val->IsNull()) ? nullptr : nullptr;
    }

    std::vector<std::any> QLogicaeCore::JsonFileIO::get_array(
        const JsonPath& key_path)
    {
        if (_file_path.empty())
        {
            throw std::runtime_error("File path is empty.");
        }
        
        std::ifstream in_file(_file_path);
        if (!in_file.is_open())
        {
            throw std::runtime_error("Failed to open JSON file.");
        }
        
        std::string json_string((std::istreambuf_iterator<char>(in_file)),
            std::istreambuf_iterator<char>());
        
        rapidjson::Document document;
        if (document.Parse(json_string.c_str()).HasParseError())
        {
            throw std::runtime_error("Failed to parse JSON content.");
        }

        auto pointer = build_pointer(key_path);
        rapidjson::Value* array_value = pointer.Get(document);
        
        if (!array_value || !array_value->IsArray())
        {
            throw std::runtime_error("Value at path is not an array.");
        }
        
        std::vector<std::any> result;
        for (auto& value : array_value->GetArray())
        {
            if (value.IsString())
            {
                result.emplace_back(
                    std::string(value.GetString(), value.GetStringLength()));
            }
            else if (value.IsBool())
            {
                result.emplace_back(value.GetBool());
            }
            else if (value.IsInt() || value.IsUint())
            {
                result.emplace_back(static_cast<double>(value.GetInt()));
            }
            else if (value.IsDouble())
            {
                result.emplace_back(value.GetDouble());
            }
            else if (value.IsNull())
            {
                result.emplace_back(nullptr);
            }
            else
            {
                throw std::runtime_error("Unsupported array element type.");
            }
        }
        
        return result;
    }

    std::unordered_map<std::string, std::any>
        QLogicaeCore::JsonFileIO::get_object(const JsonPath& key_path)
    {
        if (_file_path.empty())
        {
            throw std::runtime_error("File path is empty.");
        }

        std::ifstream in_file(_file_path);
        if (!in_file.is_open())
        {
            throw std::runtime_error("Failed to open JSON file.");
        }

        std::string json_string((std::istreambuf_iterator<char>(in_file)),
            std::istreambuf_iterator<char>());

        rapidjson::Document document;
        if (document.Parse(json_string.c_str()).HasParseError())
        {
            throw std::runtime_error("Failed to parse JSON content.");
        }

        auto pointer = build_pointer(key_path);
        rapidjson::Value* value_pointer = pointer.Get(document);

        if (!value_pointer || !value_pointer->IsObject())
        {
            throw std::runtime_error("Value at path is not an object.");
        }

        std::function<std::any(const rapidjson::Value&)> parse_value;
        parse_value = [&](const rapidjson::Value& value) -> std::any {
            if (value.IsString())
            {
                return std::string(value.GetString());
            }
            else if (value.IsBool())
            {
                return value.GetBool();
            }
            else if (value.IsNumber())
            {
                return value.GetDouble();
            }
            else if (value.IsNull())
            {
                return nullptr;
            }
            else if (value.IsArray())
            {
                std::vector<std::any> array;
                for (const auto& element : value.GetArray())
                {
                    array.emplace_back(parse_value(element));
                }
                return array;
            }
            else if (value.IsObject())
            {
                std::unordered_map<std::string, std::any> nested_obj;
                for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it)
                {
                    std::string key(it->name.GetString(), it->name.GetStringLength());
                    nested_obj[key] = parse_value(it->value);
                }
                return nested_obj;
            }

            throw std::runtime_error("Unsupported JSON value encountered.");
            };

        std::unordered_map<std::string, std::any> result;
        for (auto it = value_pointer->MemberBegin(); it != value_pointer->MemberEnd(); ++it)
        {
            std::string key(it->name.GetString(), it->name.GetStringLength());
            result[key] = parse_value(it->value);
        }

        return result;
    }


    Value JsonFileIO::make_value(
        const std::string& str,
        Document::AllocatorType& allocator)
    {
        Value v;
        v.SetString(str.c_str(), static_cast<SizeType>(str.length()), allocator);

        return v;
    }

    Value JsonFileIO::make_value(const bool& b, Document::AllocatorType&)
    {
        Value v;
        v.SetBool(b);

        return v;
    }

    Value JsonFileIO::make_value(const double& d, Document::AllocatorType&)
    {
        Value v;
        v.SetDouble(d);

        return v;
    }

    Value JsonFileIO::make_value(std::nullptr_t, Document::AllocatorType&)
    {
        Value v;
        v.SetNull();

        return v;
    }

    Value JsonFileIO::make_value(
        const std::vector<std::any>& array,
        Document::AllocatorType& allocator)
    {
        Value arr(kArrayType);
        for (const auto& item : array)
        {
            if (item.type() == typeid(std::string))
            {
                arr.PushBack(
                    make_value(
                        std::any_cast<std::string>(item), allocator), allocator);
            }
            else if (item.type() == typeid(bool))
            {
                arr.PushBack(
                    make_value(
                        std::any_cast<bool>(item), allocator), allocator);
            }
            else if (item.type() == typeid(double))
            {
                arr.PushBack(
                    make_value(
                        std::any_cast<double>(item), allocator), allocator);
            }
            else if (item.type() == typeid(std::nullptr_t))
            {
                arr.PushBack(Value().SetNull(), allocator);
            }
            else
            {
                throw std::runtime_error("Unsupported array element type in make_value");
            }
        }
        return arr;
    }

    Value JsonFileIO::make_value(
        const std::unordered_map<std::string, std::any>& object,
        Document::AllocatorType& allocator)
    {
        Value val(kObjectType);
        for (const auto& [key, any_val] : object)
        {
            Value json_key;
            json_key.SetString(
                key.c_str(),
                static_cast<SizeType>(key.length()),
            allocator);

            if (any_val.type() == typeid(std::string))
            {
                val.AddMember(json_key, make_value(
                    std::any_cast<std::string>(any_val), allocator), allocator);
            }
            else if (any_val.type() == typeid(bool))
            {
                val.AddMember(json_key, make_value(
                    std::any_cast<bool>(any_val), allocator), allocator);
            }
            else if (any_val.type() == typeid(double))
            {
                val.AddMember(json_key, make_value(
                    std::any_cast<double>(any_val), allocator), allocator);
            }
            else if (any_val.type() == typeid(std::nullptr_t))
            {
                val.AddMember(json_key, Value().SetNull(), allocator);
            }
            else
            {
                throw std::runtime_error("Unsupported object value type in make_value");
            }

        }
        return val;
    }

    bool JsonFileIO::insert_string(
        const JsonPath& path,
        const std::string& value)
    {
        std::scoped_lock lock(_mutex);

        if (path.empty())
        {
            return false;
        }

        Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);
        Value& root = document;
        auto& allocator = document.GetAllocator();

        Value* existing = pointer.Get(root);
        if (existing && !existing->IsObject() &&
            path.back().index() == 1)
        {
            return false;
        }

        pointer.Create(root, allocator);
        pointer.Set(root, make_value(value, allocator), allocator);
        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, to_string(document));

        return true;
    }

    bool JsonFileIO::insert_bool(const JsonPath& path, const bool& value)
    {
        std::scoped_lock lock(_mutex);

        if (path.empty())
        {
            return false;
        }

        Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);
        Value& root = document;
        auto& allocator = document.GetAllocator();

        Value* existing = pointer.Get(root);
        if (existing && !existing->IsObject() &&
            path.back().index() == 1)
        {
            return false;
        }

        pointer.Create(root, allocator);
        pointer.Set(root, make_value(value, allocator), allocator);
        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, to_string(document));

        return true;
    }

    bool JsonFileIO::insert_double(
        const JsonPath& path,
        const double& value)
    {
        std::scoped_lock lock(_mutex);

        if (path.empty())
        {
            return false;
        }

        Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);
        Value& root = document;
        auto& allocator = document.GetAllocator();

        Value* existing = pointer.Get(root);
        if (existing && !existing->IsObject() &&
            path.back().index() == 1)
        {
            return false;
        }

        pointer.Create(root, allocator);
        pointer.Set(root, make_value(value, allocator), allocator);
        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, to_string(document));

        return true;
    }

    bool JsonFileIO::insert_null(
        const JsonPath& path,
        const std::nullptr_t& value)
    {
        std::scoped_lock lock(_mutex);

        if (path.empty())
        {
            return false;
        }

        Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);
        Value& root = document;
        auto& allocator = document.GetAllocator();

        Value* existing = pointer.Get(root);
        if (existing && !existing->IsObject() &&
            path.back().index() == 1)
        {
            return false;
        }

        pointer.Create(root, allocator);
        pointer.Set(root, make_value(value, allocator), allocator);
        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, to_string(document));

        return true;
    }

    bool JsonFileIO::insert_array(
        const JsonPath& path,
        const std::vector<std::any>& value)
    {
        std::scoped_lock lock(_mutex);
        
        if (path.empty())
        {
            return false;
        }

        Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);
        Value& root = document;
        auto& allocator = document.GetAllocator();

        Value* existing = pointer.Get(root);
        if (existing && !existing->IsObject() &&
            path.back().index() == 1)
        {
            return false;
        }

        pointer.Create(root, allocator);
        pointer.Set(root, make_value(value, allocator), allocator);
        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, to_string(document));

        return true;
    }

    bool JsonFileIO::insert_object(
        const JsonPath& path,
        const std::unordered_map<std::string, std::any>& value)
    {
        std::scoped_lock lock(_mutex);

        if (path.empty())
        {
            return false;
        }

        Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);
        Value& root = document;
        auto& allocator = document.GetAllocator();

        Value* existing = pointer.Get(root);
        if (existing && !existing->IsObject() &&
            path.back().index() == 1)
        {
            return false;
        }

        pointer.Create(root, allocator);
        pointer.Set(root, make_value(value, allocator), allocator);
        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, to_string(document));

        return true;
    }

    bool JsonFileIO::update_string(
        const JsonPath& path,
        const std::string& value)
    {
        return insert_string(path, value);
    }

    bool JsonFileIO::update_bool(
        const JsonPath& path,
        const bool& value)
    {
        return insert_bool(path, value);
    }

    bool JsonFileIO::update_double(
        const JsonPath& path,
        const double& value)
    {
        return insert_double(path, value);
    }

    bool JsonFileIO::update_null(
        const JsonPath& path,
        const std::nullptr_t& value)
    {
        return insert_null(path, value);
    }

    bool JsonFileIO::update_array(
        const JsonPath& path,
        const std::vector<std::any>& value)
    {
        return insert_array(path, value);
    }

    bool JsonFileIO::update_object(
        const JsonPath& path,
        const std::unordered_map<std::string, std::any>& value)
    {
        return insert_object(path, value);
    }

    std::future<std::string> JsonFileIO::get_string_async(
        const JsonPath& path)
    {
        return std::async(std::launch::async, [this, path]()
        {
            return get_string(path);
        });
    }

    std::future<bool> JsonFileIO::get_bool_async(
        const JsonPath& path)
    {
        return std::async(std::launch::async, [this, path]()
        {           
            return get_bool(path);
        });
    }

    std::future<double> JsonFileIO::get_double_async(
        const JsonPath& path)
    {
        return std::async(std::launch::async, [this, path]()
        {           
            return get_double(path);
        });
    }

    std::future<std::nullptr_t> JsonFileIO::get_null_async(
        const JsonPath& path)
    {
        return std::async(std::launch::async, [this, path]()
        {           
            return get_null(path);
        });
    }

    std::future<std::vector<std::any>> JsonFileIO::get_array_async(
        const JsonPath& path)
    {
        return std::async(std::launch::async, [this, path]()
        {           
            return get_array(path);
        });
    }

    std::future<std::unordered_map<std::string, std::any>>
        JsonFileIO::get_object_async(const JsonPath& path)
    {
        return std::async(std::launch::async, [this, path]()
        {           
            return get_object(path);
        });
    }

    std::future<bool> JsonFileIO::insert_string_async(
        const JsonPath& path, const std::string& value)
    {
        return std::async(std::launch::async, [this, path, value]()
        {           
            return insert_string(path, value);
        });
    }

    std::future<bool> JsonFileIO::insert_bool_async(
        const JsonPath& path, const bool& value)
    {
        return std::async(std::launch::async, [this, path, value]()
        {           
            return insert_bool(path, value);
        });
    }

    std::future<bool> JsonFileIO::insert_double_async(
        const JsonPath& path, const double& value)
    {
        return std::async(std::launch::async, [this, path, value]()
        {           
        return insert_double(path, value);
        });
    }

    std::future<bool> JsonFileIO::insert_null_async(
        const JsonPath& path, const std::nullptr_t& value)
    {
        return std::async(std::launch::async, [this, path, value]()
        {           
            return insert_null(path, value);
        });
    }

    std::future<bool> JsonFileIO::insert_array_async(
        const JsonPath& path, const std::vector<std::any>& value)
    {
        return std::async(std::launch::async, [this, path, value]()
        {           
            return insert_array(path, value);
        });
    }

    std::future<bool> JsonFileIO::insert_object_async(
        const JsonPath& path, const std::unordered_map<std::string,
        std::any>& value)
    {
        return std::async(std::launch::async, [this, path, value]()
        {           
            return insert_object(path, value);
        });
    }

    std::future<bool> JsonFileIO::update_string_async(
        const JsonPath& path, const std::string& value)
    {
        return std::async(std::launch::async, [this, path, value]()
        {           
            return update_string(path, value);
        });
    }

    std::future<bool> JsonFileIO::update_bool_async(
        const JsonPath& path, const bool& value)
    {
        return std::async(std::launch::async, [this, path, value]()
        {           
            return update_bool(path, value);
        });
    }

    std::future<bool> JsonFileIO::update_double_async(
        const JsonPath& path, const double& value)
    {
        return std::async(std::launch::async, [this, path, value]()
        {           
            return update_double(path, value);
        });
    }

    std::future<bool> JsonFileIO::update_null_async(
        const JsonPath& path, const std::nullptr_t& value)
    {
        return std::async(std::launch::async, [this, path, value]()
        {           
            return update_null(path, value);
        });
    }

    std::future<bool> JsonFileIO::update_array_async(
        const JsonPath& path, const std::vector<std::any>& value)
    {
        return std::async(std::launch::async, [this, path, value]()
        {           
            return update_array(path, value);
        });
    }

    std::future<bool> JsonFileIO::update_object_async(
        const JsonPath& path,
        const std::unordered_map<std::string, std::any>& value)
    {
        return std::async(std::launch::async, [this, path, value]()
        {           
            return update_object(path, value);
        });
    }
}
