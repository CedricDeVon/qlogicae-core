#pragma once

#include "json.hpp"

namespace QLogicaeCore
{
    bool convert_to_rapidjson_value(
        const Json&, rapidjson::Value&,
        rapidjson::Document::AllocatorType&);

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
}
