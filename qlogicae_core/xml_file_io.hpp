#pragma once

#include "utilities.hpp"
#include "abstract_file_io.hpp" 
#include "vector_string_hash.hpp"

#include <pugixml.hpp> 

#include <string>
#include <vector>
#include <future>
#include <optional>

namespace QLogicaeCore
{
    class XmlFileIO :
        public AbstractFileIO
    {
    public:
        ~XmlFileIO();
        
        XmlFileIO() = default;
        
        XmlFileIO(const XmlFileIO&) = delete;
        
        XmlFileIO(XmlFileIO&&) noexcept = default;
        
        XmlFileIO(const std::string_view& file_path);
        
        XmlFileIO& operator=(const XmlFileIO&) = delete;
        
        XmlFileIO& operator=(
            XmlFileIO&&) noexcept = default;
        
        XmlFileIO(
            const std::string_view& file_path,
            const std::string_view& name
        );

        bool load();
        
        bool save();
        
        bool clear();
        
        bool save_as(const std::string_view& file_path);
        
        template<typename ValueType>
        std::optional<ValueType> get_value(
            const std::vector<std::string>& key_path) const;
        
        template<typename ValueType>
        bool set_value(
            const std::vector<std::string>& key_path,
            const ValueType& value);
        
        template<typename ValueType>
        bool set_values(
            const std::unordered_map<std::vector<std::string>,
            ValueType, VectorStringHash>& map);
        
        template<typename ValueType>
        bool append_value(
            const std::vector<std::string>& key_path,
            const ValueType& value);
        
        template<typename ValueType>
        bool append_values(
            const std::unordered_map<std::vector<std::string>,
            ValueType, VectorStringHash>& map);
        
        bool remove_value(const std::vector<std::string>& key_path);
        
        bool remove_values(
            const std::vector<std::vector<std::string>>& keys);
        
        bool has_key(const std::vector<std::string>& key_path) const;
        
        template<typename ValueType>
        std::vector<ValueType> get_all_values(
            const std::vector<std::string>& key_path) const;
        
        std::vector<std::string> get_children(
            const std::vector<std::string>& key_path) const;
        
        std::string get_root_name() const;
        
        bool set_root(const std::string& tag_name);
        
        bool save_with_indent(std::size_t indent_spaces);
        
        template<typename ValueType>
        std::optional<ValueType> get_attribute(
            const std::vector<std::string>& key_path,
            const std::string& attribute_name) const;
        
        template<typename ValueType>
        bool set_attribute(
            const std::vector<std::string>& key_path,
            const std::string& attribute_name,
            const ValueType& value);
        
        std::vector<std::string> select_node_texts(
            const std::string& xpath) const;
        
        std::optional<std::string> select_node_text(
            const std::string& xpath) const;
        
        bool validate_against_schema(const std::string& xsd_path) const;
        
        std::vector<std::string> select_attributes(
            const std::string& xpath,
            const std::string& attribute_name) const;
        
        std::optional<std::string> select_attribute(
            const std::string& xpath,
            const std::string& attribute_name) const;

        std::future<bool> load_async();
        
        std::future<bool> save_async();
        
        std::future<bool> clear_async();
        
        std::future<bool> save_as_async(
            const std::string_view& file_path);
        
        template<typename ValueType>
        std::future<std::optional<ValueType>>
            get_value_async(
                const std::vector<std::string>& key_path) const;
        
        template<typename ValueType>
        std::future<bool>
            set_value_async(
                const std::vector<std::string>& key_path,
                const ValueType& value);
        
        template<typename ValueType>
        std::future<bool> set_values_async(
            const std::unordered_map<std::vector<std::string>,
            ValueType, VectorStringHash>& values);
        
        template<typename ValueType>
        std::future<bool>
            append_value_async(
                const std::vector<std::string>& key_path,
                const ValueType& value);
        
        template<typename ValueType>
        std::future<bool> append_values_async(
            const std::unordered_map<std::vector<std::string>,
            ValueType, VectorStringHash>& values);
        
        std::future<bool> remove_value_async(
            const std::vector<std::string>& key_path);
        
        std::future<bool> remove_values_async(
            const std::vector<std::vector<std::string>>& keys);
        
        std::future<bool> has_key_async(
            const std::vector<std::string>& key_path) const;
        
        template<typename ValueType>
        std::future<std::vector<ValueType>> get_all_values_async(
            const std::vector<std::string>& key_path) const;
        
        std::future<std::vector<std::string>> get_children_async(
            const std::vector<std::string>& key_path) const;
        
        std::future<std::string> get_root_name_async() const;
        
        std::future<bool> save_with_indent_async(std::size_t indent_spaces);
        
        std::future<std::optional<std::string>>
            select_node_text_async(const std::string& xpath) const;
        
        std::future<std::vector<std::string>>
            select_node_texts_async(const std::string& xpath) const;
        
        std::future<bool> validate_against_schema_async(
            const std::string& xsd_path
        ) const;
        
        template<typename ValueType>
        std::future<std::optional<ValueType>> get_attribute_async(
            const std::vector<std::string>& key_path,
            const std::string& attribute_name
        ) const;
        
        template<typename ValueType>
        std::future<bool> set_attribute_async(
            const std::vector<std::string>& key_path,
            const std::string& attribute_name,
            const ValueType& value
        );
        
        std::future<bool> set_root_async(const std::string& tag_name);

    protected:
        pugi::xml_document _xml_document;
        pugi::xml_node _navigate_to_path(
            const std::vector<std::string>& key_path,
            bool create_missing) const;
    };

    template<typename ValueType>
    std::optional<ValueType> XmlFileIO::get_attribute(
        const std::vector<std::string>& key_path,
        const std::string& attribute_name) const
    {
        static_assert(std::is_constructible_v<std::string, ValueType> ||
            std::is_arithmetic_v<ValueType>,
            "ValueType must be string or arithmetic");

        std::scoped_lock<std::mutex> lock(_mutex);

        pugi::xml_node node = _navigate_to_path(key_path, false);
        if (!node)
        {
            return std::nullopt;
        }

        pugi::xml_attribute attr = node.attribute(attribute_name.c_str());
        if (!attr)
        {
            return std::nullopt;
        }

        const char* attr_value = attr.value();
        if (attr_value == nullptr || attr_value[0] == '\0')
        {
            return std::nullopt;
        }

        std::istringstream input_stream(attr_value);
        input_stream >> std::noskipws;

        ValueType value{};
        input_stream >> value;

        if (input_stream.fail() ||
            input_stream.peek() != std::char_traits<char>::eof())
        {
            return std::nullopt;
        }

        return value;
    }

    template<typename ValueType>
    std::future<std::vector<ValueType>>
        XmlFileIO::get_all_values_async(
            const std::vector<std::string>& key_path) const
    {
        return std::async(std::launch::async,
            [this, key_path]()
            {
                return get_all_values<ValueType>(key_path);
            });
    }

    template<typename ValueType>
    std::future<std::optional<ValueType>>
        QLogicaeCore::XmlFileIO::get_attribute_async(
            const std::vector<std::string>& key_path,
            const std::string& attribute_name) const
    {
        return std::async(std::launch::async,
            [this, key_path, attribute_name]()
            {
                return get_attribute<ValueType>(key_path, attribute_name);
            });
    }

    template<typename ValueType>
    std::future<bool> QLogicaeCore::XmlFileIO::set_attribute_async(
        const std::vector<std::string>& key_path,
        const std::string& attribute_name,
        const ValueType& value)
    {
        return std::async(std::launch::async,
            [this, key_path, attribute_name, value]()
            {
                return set_attribute<ValueType>(
                    key_path, attribute_name, value);
            });
    }

    template<typename ValueType>
    bool QLogicaeCore::XmlFileIO::set_attribute(
        const std::vector<std::string>& key_path,
        const std::string& attribute_name,
        const ValueType& value)
    {
        static_assert(std::is_constructible_v<std::string, ValueType> ||
            std::is_arithmetic_v<ValueType>,
            "ValueType must be string or arithmetic");

        std::scoped_lock<std::mutex> lock(_mutex);

        pugi::xml_node node = _navigate_to_path(key_path, false);
        if (!node)
        {
            return false;
        }

        pugi::xml_attribute attr = node.attribute(attribute_name.c_str());
        if (!attr)
        {
            attr = node.append_attribute(attribute_name.c_str());
            if (!attr)
            {
                return false;
            }
        }

        std::ostringstream output_stream;
        output_stream << value;
        if (output_stream.fail())
        {
            return false;
        }

        attr.set_value(output_stream.str().c_str());
        return true;
    }

    template<typename ValueType>
    std::vector<ValueType> XmlFileIO::get_all_values(
        const std::vector<std::string>& key_path) const
    {
        static_assert(std::is_default_constructible_v<ValueType>,
            "ValueType must be default constructible");
        static_assert(std::is_constructible_v<std::string, ValueType> ||
            std::is_arithmetic_v<ValueType>,
            "ValueType must be string or arithmetic");

        std::scoped_lock<std::mutex> lock(_mutex);

        std::vector<ValueType> values;

        if (key_path.empty())
        {
            return values;
        }

        std::vector<std::string> parent_path(
            key_path.begin(), key_path.end() - 1);

        std::string last_key = key_path.back();

        pugi::xml_node parent_node =
            _navigate_to_path(parent_path, false);

        if (!parent_node)
        {
            return values;
        }

        for (pugi::xml_node node = parent_node.child(last_key.c_str());
            node;
            node = node.next_sibling(last_key.c_str()))
        {
            const char* node_text = node.text().as_string();

            if (node_text == nullptr || node_text[0] == '\0')
            {
                continue;
            }

            std::istringstream input_stream(node_text);
            input_stream >> std::noskipws;

            ValueType value;
            input_stream >> value;

            if (input_stream.fail() ||
                input_stream.peek() != std::char_traits<char>::eof())
            {
                continue;
            }

            values.push_back(value);
        }

        return values;
    }

    template<typename ValueType>
    std::optional<ValueType> XmlFileIO::get_value(
        const std::vector<std::string>& key_path) const
    {
        static_assert(std::is_default_constructible_v<ValueType>,
            "ValueType must be default constructible");
        static_assert(std::is_constructible_v<std::string, ValueType> ||
            std::is_arithmetic_v<ValueType>,
            "ValueType must be string or arithmetic");

        std::scoped_lock<std::mutex> lock(_mutex);

        if (key_path.empty())
        {
            return std::nullopt;
        }

        pugi::xml_node current_node = _xml_document;

        for (const std::string& key : key_path)
        {
            current_node = current_node.child(key.c_str());
            if (!current_node)
            {
                return std::nullopt;
            }
        }

        const char* node_text = current_node.text().as_string();

        if (node_text == nullptr || node_text[0] == '\0')
        {
            return std::nullopt;
        }

        std::istringstream input_stream(node_text);
        input_stream >> std::noskipws;

        ValueType value{};
        input_stream >> value;

        if (input_stream.fail() ||
            input_stream.peek() != std::char_traits<char>::eof())
        {
            return std::nullopt;
        }

        return value;
    }

    template<typename ValueType>
    bool XmlFileIO::set_value(
        const std::vector<std::string>& key_path,
        const ValueType& value)
    {
        for (const auto& tag : key_path)
        {
            if (tag.length() > 256)
            {
                return false;
            }
        }

        static_assert(std::is_constructible_v<std::string, ValueType> ||
            std::is_arithmetic_v<ValueType>,
            "ValueType must be string or arithmetic");

        std::scoped_lock<std::mutex> lock(_mutex);

        if (key_path.empty())
        {
            return false;
        }

        pugi::xml_node target_node =
            _navigate_to_path(key_path, true);

        if (!target_node)
        {
            return false;
        }

        std::ostringstream output_stream;
        output_stream << value;

        if (output_stream.fail())
        {
            return false;
        }

        target_node.text().set(output_stream.str().c_str());

        return true;
    }

    template<typename ValueType>
    bool XmlFileIO::append_value(
        const std::vector<std::string>& key_path,
        const ValueType& value)
    {
        static_assert(std::is_constructible_v<std::string, ValueType> ||
            std::is_arithmetic_v<ValueType>,
            "ValueType must be string or arithmetic");

        std::scoped_lock<std::mutex> lock(_mutex);

        if (key_path.empty())
        {
            return false;
        }

        std::vector<std::string> parent_path(
            key_path.begin(), key_path.end() - 1);

        std::string last_key = key_path.back();

        pugi::xml_node parent_node =
            _navigate_to_path(parent_path, true);

        if (!parent_node)
        {
            return false;
        }

        pugi::xml_node new_node = parent_node.append_child(
            last_key.c_str());

        if (!new_node)
        {
            return false;
        }

        std::ostringstream output_stream;
        output_stream << value;

        if (output_stream.fail())
        {
            return false;
        }

        new_node.text().set(output_stream.str().c_str());

        return true;
    }

    template<typename ValueType>
    bool XmlFileIO::set_values(
        const std::unordered_map<std::vector<std::string>,
        ValueType, VectorStringHash,
        std::equal_to<std::vector<std::string>>>& map)
    {
        for (const std::pair<const std::vector<std::string>,
            ValueType>& entry : map)
        {
            if (!set_value(entry.first, entry.second))
            {
                return false;
            }
        }

        return true;
    }

    template<typename ValueType>
    bool XmlFileIO::append_values(
        const std::unordered_map<std::vector<std::string>,
        ValueType, VectorStringHash>& map)
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        for (const std::pair<const std::vector<std::string>,
            ValueType>& entry : map)
        {
            if (!append_value(entry.first, entry.second))
            {
                return false;
            }
        }

        return true;
    }

    template<typename ValueType>
    std::future<bool> XmlFileIO::set_values_async(
        const std::unordered_map<std::vector<std::string>,
        ValueType, VectorStringHash>& values)
    {
        return std::async(std::launch::async,
            [this, values]()
            {
                return set_values(values);
            });
    }

    template<typename ValueType>
    std::future<bool> XmlFileIO::append_value_async(
        const std::vector<std::string>& key_path,
        const ValueType& value)
    {
        return std::async(std::launch::async,
            [this, key_path, value]()
            {
                return append_value(key_path,
                    value);
            });
    }

    template<typename ValueType>
    std::future<bool> XmlFileIO::append_values_async(
        const std::unordered_map<std::vector<std::string>, ValueType, VectorStringHash>& values)
    {
        return std::async(std::launch::async,
            [this, values]()
            {
                return append_values(values);
            });
    }

    template<typename ValueType>
    std::future<std::optional<ValueType>>
        XmlFileIO::get_value_async(
            const std::vector<std::string>& key_path) const
    {
        return std::async(std::launch::async,
            [this, key_path]()
            {
                return this->get_value<ValueType>(key_path);
            });
    }

    template<typename ValueType>
    std::future<bool> XmlFileIO::set_value_async(
        const std::vector<std::string>& key_path,
        const ValueType& value)
    {
        return std::async(std::launch::async,
            [this, key_path, value]()
            {
                return this->set_value<ValueType>(key_path, value);
            });
    }
}
