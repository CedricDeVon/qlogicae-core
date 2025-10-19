#include "pch.hpp"

#include "json_file_io.hpp"

namespace QLogicaeCore
{
    JsonFileIO::~JsonFileIO() {}

    JsonFileIO::JsonFileIO(const std::string& path
    )
        : AbstractFileIO(path)
    {        
        _is_formatting_allowed = false;
    }

    JsonFileIO::JsonFileIO(
        const std::string& path,
        const bool& is_formatting_allowed
    )
            : AbstractFileIO(path)
    {
        _is_formatting_allowed = is_formatting_allowed;
    }

    JsonFileIO::JsonFileIO(
        const std::string& name,
        const std::string& path
    )
            : AbstractFileIO(name, path)
    {
        _is_formatting_allowed = false;
    }

    bool JsonFileIO::setup(
        const std::string& file_path
    )
    {
        Result<void> void_result;

        setup(void_result, file_path);

        return void_result.is_status_safe();
    }

    bool JsonFileIO::setup(
        const std::string& file_path,
        const bool& is_formatting_allowed
    )
    {
        Result<void> void_result;

        setup(void_result, file_path, is_formatting_allowed);

        return void_result.is_status_safe();
    }

    bool JsonFileIO::setup(
        const std::string& name,
        const std::string& file_path
    )
    {
        Result<void> void_result;

        setup(void_result, name, file_path);

        return void_result.is_status_safe();
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

    bool JsonFileIO::write(const std::string& content)
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

    rapidjson::Pointer JsonFileIO::build_pointer(const JsonPath& key_path)
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

        return rapidjson::Pointer(pointer_string.c_str());
    }

    std::string JsonFileIO::to_string(const rapidjson::Document& document)
    {
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
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

        rapidjson::Document document;
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

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return "";
        }

        auto pointer = build_pointer(path);
        const rapidjson::Value* value = pointer.Get(document);

        return (value && value->IsString()) ? value->GetString() : "";
    }

    bool JsonFileIO::get_bool(const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return false;
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto ptr = build_pointer(path);
        const rapidjson::Value* val = ptr.Get(document);

        return (val && val->IsBool()) ? val->GetBool() : false;
    }

    double JsonFileIO::get_double(const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return 0.0;
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return 0.0;
        }

        auto ptr = build_pointer(path);
        const rapidjson::Value* val = ptr.Get(document);

        return (val && val->IsNumber()) ? val->GetDouble() : 0.0;
    }

    std::nullptr_t JsonFileIO::get_null(const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return nullptr;
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return nullptr;
        }

        auto ptr = build_pointer(path);
        const rapidjson::Value* val = ptr.Get(document);

        return (val && val->IsNull()) ? nullptr : nullptr;
    }

    std::vector<std::any> QLogicaeCore::JsonFileIO::get_array(
        const JsonPath& key_path)
    {
        if (_file_path.empty())
        {
            throw std::runtime_error("Exception at JsonFileIO::get_array(): File path is empty");
        }

        std::ifstream in_file(_file_path);
        if (!in_file.is_open())
        {
            throw std::runtime_error("Exception at JsonFileIO::get_array(): Failed to open JSON file '" + _file_path + "'");
        }

        std::string json_string((std::istreambuf_iterator<char>(in_file)),
            std::istreambuf_iterator<char>());

        rapidjson::Document document;
        if (document.Parse(json_string.c_str()).HasParseError())
        {
            throw std::runtime_error("Exception at JsonFileIO::get_array(): Failed to parse JSON content");
        }

        auto pointer = build_pointer(key_path);
        rapidjson::Value* array_value = pointer.Get(document);

        if (!array_value || !array_value->IsArray())
        {
            throw std::runtime_error("Exception at JsonFileIO::get_array(): Value at path is not an array");
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
                throw std::runtime_error("Exception at JsonFileIO::get_array(): Unsupported array element type");
            }
        }

        return result;
    }

    std::unordered_map<std::string, std::any>
        QLogicaeCore::JsonFileIO::get_object(const JsonPath& key_path)
    {
        if (_file_path.empty())
        {
            throw std::runtime_error("Exception at JsonFileIO::get_object(): File path is empty");
        }

        std::ifstream in_file(_file_path);
        if (!in_file.is_open())
        {
            throw std::runtime_error("Exception at JsonFileIO::get_object(): Failed to open JSON file '" + _file_path + "'");
        }

        std::string json_string((std::istreambuf_iterator<char>(in_file)),
            std::istreambuf_iterator<char>());

        rapidjson::Document document;
        if (document.Parse(json_string.c_str()).HasParseError())
        {
            throw std::runtime_error("Exception at JsonFileIO::get_object(): Failed to parse JSON content");
        }

        auto pointer = build_pointer(key_path);
        rapidjson::Value* value_pointer = pointer.Get(document);

        if (!value_pointer || !value_pointer->IsObject())
        {
            throw std::runtime_error("Exception at JsonFileIO::get_object(): Value at path is not an object");
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

            throw std::runtime_error("Exception at JsonFileIO::get_object(): Unsupported JSON value encountered");
            };

        std::unordered_map<std::string, std::any> result;
        for (auto it = value_pointer->MemberBegin(); it != value_pointer->MemberEnd(); ++it)
        {
            std::string key(it->name.GetString(), it->name.GetStringLength());
            result[key] = parse_value(it->value);
        }

        return result;
    }


    rapidjson::Value JsonFileIO::make_value(
        const std::string& str,
        rapidjson::Document::AllocatorType& allocator)
    {
        rapidjson::Value v;
        v.SetString(str.c_str(), static_cast<rapidjson::SizeType>(str.length()), allocator);

        return v;
    }

    rapidjson::Value JsonFileIO::make_value(const bool& b, rapidjson::Document::AllocatorType&)
    {
        rapidjson::Value v;
        v.SetBool(b);

        return v;
    }

    rapidjson::Value JsonFileIO::make_value(const double& d, rapidjson::Document::AllocatorType&)
    {
        rapidjson::Value v;
        v.SetDouble(d);

        return v;
    }

    rapidjson::Value JsonFileIO::make_value(std::nullptr_t, rapidjson::Document::AllocatorType&)
    {
        rapidjson::Value v;
        v.SetNull();

        return v;
    }

    rapidjson::Value JsonFileIO::make_value(
        const std::vector<std::any>& array,
        rapidjson::Document::AllocatorType& allocator)
    {
        rapidjson::Value arr(rapidjson::kArrayType);
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
                arr.PushBack(rapidjson::Value().SetNull(), allocator);
            }
            else
            {
                throw std::runtime_error("Exception at JsonFileIO::make_value(): Unsupported array element type in make_value");
            }
        }
        return arr;
    }

    rapidjson::Value JsonFileIO::make_value(
        const std::unordered_map<std::string, std::any>& object,
        rapidjson::Document::AllocatorType& allocator)
    {
        rapidjson::Value val(rapidjson::kObjectType);
        for (const auto& [key, any_val] : object)
        {
            rapidjson::Value json_key;
            json_key.SetString(
                key.c_str(),
                static_cast<rapidjson::SizeType>(key.length()),
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
                val.AddMember(json_key, rapidjson::Value().SetNull(), allocator);
            }
            else
            {
                throw std::runtime_error("Exception at JsonFileIO::make_value(): Unsupported object value type in make_value");
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

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);
        rapidjson::Value& root = document;
        auto& allocator = document.GetAllocator();

        rapidjson::Value* existing = pointer.Get(root);
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

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);
        rapidjson::Value& root = document;
        auto& allocator = document.GetAllocator();

        rapidjson::Value* existing = pointer.Get(root);
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

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);
        rapidjson::Value& root = document;
        auto& allocator = document.GetAllocator();

        rapidjson::Value* existing = pointer.Get(root);
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

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);
        rapidjson::Value& root = document;
        auto& allocator = document.GetAllocator();

        rapidjson::Value* existing = pointer.Get(root);
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

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);
        rapidjson::Value& root = document;
        auto& allocator = document.GetAllocator();

        rapidjson::Value* existing = pointer.Get(root);
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

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return false;
        }

        auto pointer = build_pointer(path);
        rapidjson::Value& root = document;
        auto& allocator = document.GetAllocator();

        rapidjson::Value* existing = pointer.Get(root);
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

    std::future<std::string> JsonFileIO::read_async()
    {
        return std::async(std::launch::async, [this]() {
            return this->read();
            });
    }

    std::future<bool> JsonFileIO::write_async(const std::string& content)
    {
        return std::async(std::launch::async, [this, content]() {
            return this->write(content);
            });
    }

    void JsonFileIO::read(Result<std::string>& result)
    {
        if (_file_path.empty())
        {
            return result.set_to_bad_status_with_value("");
        }

        fast_io::native_file_loader loader{ _file_path };
        std::string content(loader.data(), loader.data() + loader.size());
        result.set_to_good_status_with_value(content);
    }

    void JsonFileIO::write(Result<bool>& result, const std::string& content)
    {
        if (_file_path.empty())
        {
            return result.set_to_bad_status_with_value(false);
        }

        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, content);
        result.set_to_good_status_with_value(true);
    }

    void JsonFileIO::get_is_formatting_allowed(Result<bool>& result)
    {
        result.set_to_good_status_with_value(_is_formatting_allowed);
    }

    void JsonFileIO::is_key_path_valid(Result<bool>& result,
        const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return result.set_to_bad_status_with_value(false);
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value(false);
        }

        auto pointer = build_pointer(path);
        bool is_valid = pointer.Get(document) != nullptr;
        result.set_to_good_status_with_value(is_valid);
    }

    void JsonFileIO::set_is_formatting_allowed(
        Result<bool>& result,
        const bool& value
    )
    {
        _is_formatting_allowed = value;

        result.set_to_good_status_with_value(true);
    }

    void JsonFileIO::get_bool(Result<bool>& result, const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return result.set_to_bad_status_with_value(false);
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value(false);
        }

        auto ptr = build_pointer(path);
        const rapidjson::Value* val = ptr.Get(document);
        bool value = (val && val->IsBool()) ? val->GetBool() : false;
        result.set_to_good_status_with_value(value);
    }

    void JsonFileIO::get_double(Result<double>& result, const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return result.set_to_bad_status_with_value(0.0);
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value(0.0);
        }

        auto ptr = build_pointer(path);
        const rapidjson::Value* val = ptr.Get(document);
        double value = (val && val->IsNumber()) ? val->GetDouble() : 0.0;
        result.set_to_good_status_with_value(value);
    }

    void JsonFileIO::get_string(Result<std::string>& result,
        const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return result.set_to_bad_status_with_value("");
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value("");
        }

        auto pointer = build_pointer(path);
        const rapidjson::Value* value = pointer.Get(document);
        std::string str_value =
            (value && value->IsString()) ? value->GetString() : "";
        result.set_to_good_status_with_value(str_value);
    }

    void JsonFileIO::get_null(Result<std::nullptr_t>& result,
        const JsonPath& path)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return result.set_to_bad_status_with_value(nullptr);
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value(nullptr);
        }

        auto ptr = build_pointer(path);
        const rapidjson::Value* val = ptr.Get(document);
        result.set_to_good_status_with_value(nullptr);
    }

    void JsonFileIO::get_array(Result<std::vector<std::any>>& result,
        const JsonPath& path)
    {
        if (_file_path.empty())
        {
            return result.set_to_bad_status_with_value({});
        }

        std::ifstream in_file(_file_path);
        if (!in_file.is_open())
        {
            return result.set_to_bad_status_with_value({});
        }

        std::string json_string((std::istreambuf_iterator<char>(in_file)),
            std::istreambuf_iterator<char>());

        rapidjson::Document document;
        if (document.Parse(json_string.c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value({});
        }

        auto pointer = build_pointer(path);
        rapidjson::Value* array_value = pointer.Get(document);
        if (!array_value || !array_value->IsArray())
        {
            return result.set_to_bad_status_with_value({});
        }

        std::vector<std::any> values;
        for (auto& value : array_value->GetArray())
        {
            if (value.IsString())
            {
                values.emplace_back(std::string(value.GetString(),
                    value.GetStringLength()));
            }
            else if (value.IsBool())
            {
                values.emplace_back(value.GetBool());
            }
            else if (value.IsInt() || value.IsUint())
            {
                values.emplace_back(static_cast<double>(value.GetInt()));
            }
            else if (value.IsDouble())
            {
                values.emplace_back(value.GetDouble());
            }
            else if (value.IsNull())
            {
                values.emplace_back(nullptr);
            }
        }

        result.set_to_good_status_with_value(values);
    }

    void JsonFileIO::get_object(
        Result<std::unordered_map<std::string, std::any>>& result,
        const JsonPath& path
    )
    {
        if (_file_path.empty())
        {
            return result.set_to_bad_status_with_value({});
        }

        std::ifstream in_file(_file_path);
        if (!in_file.is_open())
        {
            return result.set_to_bad_status_with_value({});
        }

        std::string json_string((std::istreambuf_iterator<char>(in_file)),
            std::istreambuf_iterator<char>());

        rapidjson::Document document;
        if (document.Parse(json_string.c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value({});
        }

        auto pointer = build_pointer(path);
        rapidjson::Value* value_pointer = pointer.Get(document);
        if (!value_pointer || !value_pointer->IsObject())
        {
            return result.set_to_bad_status_with_value({});
        }

        std::function<std::any(const rapidjson::Value&)> parse_value;
        parse_value = [&](const rapidjson::Value& value) -> std::any {
            if (value.IsString())
            {
                return std::string(value.GetString());
            }
            if (value.IsBool())
            {
                return value.GetBool();
            }
            if (value.IsNumber())
            {
                return value.GetDouble();
            }
            if (value.IsNull())
            {
                return nullptr;
            }
            if (value.IsArray())
            {
                std::vector<std::any> arr;
                for (const auto& elem : value.GetArray())
                {
                    arr.emplace_back(parse_value(elem));
                }
                return arr;
            }
            if (value.IsObject())
            {
                std::unordered_map<std::string, std::any> obj;
                for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it)
                {
                    std::string key(it->name.GetString(),
                        it->name.GetStringLength());
                    obj[key] = parse_value(it->value);
                }
                return obj;
            }
            return std::any();
            };

        std::unordered_map<std::string, std::any> map;
        for (auto it = value_pointer->MemberBegin();
            it != value_pointer->MemberEnd(); ++it)
        {
            std::string key(it->name.GetString(), it->name.GetStringLength());
            map[key] = parse_value(it->value);
        }

        result.set_to_good_status_with_value(map);
    }

    void JsonFileIO::insert_string(
        Result<bool>& result,
        const JsonPath& path,
        const std::string& value
    )
    {
        std::scoped_lock lock(_mutex);

        if (path.empty())
        {
            return result.set_to_bad_status_with_value(false);
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value(false);
        }

        auto pointer = build_pointer(path);
        rapidjson::Value& root = document;
        auto& allocator = document.GetAllocator();

        rapidjson::Value* existing = pointer.Get(root);
        if (existing && !existing->IsObject() && path.back().index() == 1)
        {
            return result.set_to_bad_status_with_value(false);
        }

        pointer.Create(root, allocator);
        pointer.Set(root, make_value(value, allocator), allocator);

        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, to_string(document));
        result.set_to_good_status_with_value(true);
    }

    void JsonFileIO::insert_bool(
        Result<bool>& result,
        const JsonPath& path,
        const bool& value
    )
    {
        std::scoped_lock lock(_mutex);

        if (path.empty())
        {
            return result.set_to_bad_status_with_value(false);
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value(false);
        }

        auto pointer = build_pointer(path);
        rapidjson::Value& root = document;
        auto& allocator = document.GetAllocator();

        rapidjson::Value* existing = pointer.Get(root);
        if (existing && !existing->IsObject() && path.back().index() == 1)
        {
            return result.set_to_bad_status_with_value(false);
        }

        pointer.Create(root, allocator);
        pointer.Set(root, make_value(value, allocator), allocator);

        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, to_string(document));
        result.set_to_good_status_with_value(true);
    }

    void JsonFileIO::insert_double(
        Result<bool>& result,
        const JsonPath& path,
        const double& value
    )
    {
        std::scoped_lock lock(_mutex);

        if (path.empty())
        {
            return result.set_to_bad_status_with_value(false);
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value(false);
        }

        auto pointer = build_pointer(path);
        rapidjson::Value& root = document;
        auto& allocator = document.GetAllocator();

        rapidjson::Value* existing = pointer.Get(root);
        if (existing && !existing->IsObject() && path.back().index() == 1)
        {
            return result.set_to_bad_status_with_value(false);
        }

        pointer.Create(root, allocator);
        pointer.Set(root, make_value(value, allocator), allocator);

        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, to_string(document));
        result.set_to_good_status_with_value(true);
    }

    void JsonFileIO::insert_null(
        Result<bool>& result,
        const JsonPath& path,
        const std::nullptr_t& value
    )
    {
        std::scoped_lock lock(_mutex);

        if (path.empty())
        {
            return result.set_to_bad_status_with_value(false);
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value(false);
        }

        auto pointer = build_pointer(path);
        rapidjson::Value& root = document;
        auto& allocator = document.GetAllocator();

        rapidjson::Value* existing = pointer.Get(root);
        if (existing && !existing->IsObject() && path.back().index() == 1)
        {
            return result.set_to_bad_status_with_value(false);
        }

        pointer.Create(root, allocator);
        pointer.Set(root, make_value(value, allocator), allocator);

        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, to_string(document));
        result.set_to_good_status_with_value(true);
    }

    void JsonFileIO::insert_array(
        Result<bool>& result,
        const JsonPath& path,
        const std::vector<std::any>& value
    )
    {
        std::scoped_lock lock(_mutex);

        if (path.empty())
        {
            return result.set_to_bad_status_with_value(false);
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value(false);
        }

        auto pointer = build_pointer(path);
        rapidjson::Value& root = document;
        auto& allocator = document.GetAllocator();

        rapidjson::Value* existing = pointer.Get(root);
        if (existing && !existing->IsObject() && path.back().index() == 1)
        {
            return result.set_to_bad_status_with_value(false);
        }

        pointer.Create(root, allocator);
        pointer.Set(root, make_value(value, allocator), allocator);

        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, to_string(document));
        result.set_to_good_status_with_value(true);
    }

    void JsonFileIO::insert_object(
        Result<bool>& result,
        const JsonPath& path,
        const std::unordered_map<std::string, std::any>& value
    )
    {
        std::scoped_lock lock(_mutex);

        if (path.empty())
        {
            return result.set_to_bad_status_with_value(false);
        }

        rapidjson::Document document;
        if (document.Parse(read().c_str()).HasParseError())
        {
            return result.set_to_bad_status_with_value(false);
        }

        auto pointer = build_pointer(path);
        rapidjson::Value& root = document;
        auto& allocator = document.GetAllocator();

        rapidjson::Value* existing = pointer.Get(root);
        if (existing && !existing->IsObject() && path.back().index() == 1)
        {
            return result.set_to_bad_status_with_value(false);
        }

        pointer.Create(root, allocator);
        pointer.Set(root, make_value(value, allocator), allocator);

        fast_io::obuf_file writer{ _file_path };
        fast_io::io::print(writer, to_string(document));
        result.set_to_good_status_with_value(true);
    }

    void JsonFileIO::update_string(
        Result<bool>& result,
        const JsonPath& path,
        const std::string& value
    )
    {
        insert_string(result, path, value);
    }

    void JsonFileIO::update_bool(
        Result<bool>& result,
        const JsonPath& path,
        const bool& value
    )
    {
        insert_bool(result, path, value);
    }

    void JsonFileIO::update_double(
        Result<bool>& result,
        const JsonPath& path,
        const double& value
    )
    {
        insert_double(result, path, value);
    }

    void JsonFileIO::update_null(
        Result<bool>& result,
        const JsonPath& path,
        const std::nullptr_t& value
    )
    {
        insert_null(result, path, value);
    }

    void JsonFileIO::update_array(
        Result<bool>& result,
        const JsonPath& path,
        const std::vector<std::any>& value
    )
    {
        insert_array(result, path, value);
    }

    void JsonFileIO::update_object(
        Result<bool>& result,
        const JsonPath& path,
        const std::unordered_map<std::string, std::any>& value
    )
    {
        insert_object(result, path, value);
    }

    void JsonFileIO::read_async(Result<std::future<std::string>>& result)
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this]()
            {
                Result<std::string> result;
                read(result);
                return result.get_value();
            }));
    }

    void JsonFileIO::write_async(
        Result<std::future<bool>>& result,
        const std::string& content
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, content]()
            {
                Result<bool> result;
                write(result, content);
                return result.get_value();
            }));
    }

    void JsonFileIO::get_bool_async(
        Result<std::future<bool>>& result,
        const JsonPath& path
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path]()
            {
                Result<bool> result;
                get_bool(result, path);
                return result.get_value();
            }));
    }

    void JsonFileIO::get_double_async(
        Result<std::future<double>>& result,
        const JsonPath& path
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path]()
            {
                Result<double> result;
                get_double(result, path);
                return result.get_value();
            }));
    }

    void JsonFileIO::get_string_async(
        Result<std::future<std::string>>& result,
        const JsonPath& path
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path]()
            {
                Result<std::string> result;
                get_string(result, path);
                return result.get_value();
            }));
    }

    void JsonFileIO::get_null_async(
        Result<std::future<std::nullptr_t>>& result,
        const JsonPath& path
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path]()
            {
                Result<std::nullptr_t> result;
                get_null(result, path);
                return result.get_value();
            }));
    }

    void JsonFileIO::get_array_async(
        Result<std::future<std::vector<std::any>>>& result,
        const JsonPath& path
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path]()
            {
                Result<std::vector<std::any>> result;
                get_array(result, path);
                return result.get_value();
            }));
    }

    void JsonFileIO::get_object_async(
        Result<std::future<std::unordered_map<std::string, std::any>>>& result,
        const JsonPath& path
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path]()
            {
                Result<std::unordered_map<std::string, std::any>> result;
                get_object(result, path);
                return result.get_value();
            }));
    }

    void JsonFileIO::insert_bool_async(
        Result<std::future<bool>>& result,
        const JsonPath& path,
        const bool& value
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path, value]()
            {
                Result<bool> result;
                insert_bool(result, path, value);
                return result.get_value();
            }));
    }

    void JsonFileIO::insert_double_async(
        Result<std::future<bool>>& result,
        const JsonPath& path,
        const double& value
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path, value]()
            {
                Result<bool> result;
                insert_double(result, path, value);
                return result.get_value();
            }));
    }

    void JsonFileIO::insert_string_async(
        Result<std::future<bool>>& result,
        const JsonPath& path,
        const std::string& value
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path, value]()
            {
                Result<bool> result;
                insert_string(result, path, value);
                return result.get_value();
            }));
    }

    void JsonFileIO::insert_null_async(
        Result<std::future<bool>>& result,
        const JsonPath& path,
        const std::nullptr_t& value
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path, value]()
            {
                Result<bool> result;
                insert_null(result, path, value);
                return result.get_value();
            }));
    }

    void JsonFileIO::insert_array_async(
        Result<std::future<bool>>& result,
        const JsonPath& path,
        const std::vector<std::any>& value
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path, value]()
            {
                Result<bool> result;
                insert_array(result, path, value);
                return result.get_value();
            }));
    }

    void JsonFileIO::insert_object_async(
        Result<std::future<bool>>& result,
        const JsonPath& path,
        const std::unordered_map<std::string, std::any>& value
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path, value]()
            {
                Result<bool> result;
                insert_object(result, path, value);
                return result.get_value();
            }));
    }

    void JsonFileIO::update_bool_async(
        Result<std::future<bool>>& result,
        const JsonPath& path,
        const bool& value
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path, value]()
            {
                Result<bool> result;
                update_bool(result, path, value);
                return result.get_value();
            }));
    }

    void JsonFileIO::update_double_async(
        Result<std::future<bool>>& result,
        const JsonPath& path,
        const double& value
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path, value]()
            {
                Result<bool> result;
                update_double(result, path, value);
                return result.get_value();
            }));
    }

    void JsonFileIO::update_string_async(
        Result<std::future<bool>>& result,
        const JsonPath& path,
        const std::string& value
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path, value]()
            {
                Result<bool> result;
                update_string(result, path, value);
                return result.get_value();
            }));
    }

    void JsonFileIO::update_null_async(
        Result<std::future<bool>>& result,
        const JsonPath& path,
        const std::nullptr_t& value
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path, value]()
            {
                Result<bool> result;
                update_null(result, path, value);
                return result.get_value();
            }));
    }

    void JsonFileIO::update_array_async(
        Result<std::future<bool>>& result,
        const JsonPath& path,
        const std::vector<std::any>& value
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path, value]()
            {
                Result<bool> result;
                update_array(result, path, value);
                return result.get_value();
            }));
    }

    void JsonFileIO::update_object_async(
        Result<std::future<bool>>& result,
        const JsonPath& path,
        const std::unordered_map<std::string, std::any>& value
    )
    {
        result.set_to_good_status_with_value(std::async(std::launch::async,
            [this, path, value]()
            {
                Result<bool> result;
                update_object(result, path, value);
                return result.get_value();
            }));
    }

    void JsonFileIO::setup(
        Result<void>& result,
        const std::string& file_path
    )
    {
        _file_path = file_path;

        result.set_to_good_status_without_value();
    }

    void JsonFileIO::setup(
        Result<void>& result,
        const std::string& file_path,
        const bool& is_formatting_allowed
    )
    {
        _file_path = file_path;
        _is_formatting_allowed = is_formatting_allowed;

        result.set_to_good_status_without_value();
    }

    void JsonFileIO::setup(
        Result<void>& result,
        const std::string& name,
        const std::string& file_path
    )
    {
        _name = name;
        _file_path = file_path;

        result.set_to_good_status_without_value();
    }
}

