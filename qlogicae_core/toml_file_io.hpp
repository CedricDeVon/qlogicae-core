#pragma once

#include "result.hpp"
#include "utilities.hpp"
#include "abstract_file_io.hpp"
#include "vector_string_hash.hpp"
#include "vector_string_equal.hpp"

#include <toml++/toml.h>

#include <string>
#include <vector>
#include <optional>
#include <functional>

namespace QLogicaeCore
{
    class TomlFileIO :
        public AbstractFileIO
    {
    public:
        ~TomlFileIO();
        
        TomlFileIO();
        
        TomlFileIO(
            const std::string& file_path
        );
        
        TomlFileIO(
            const std::string& name,
            const std::string& file_path
        );
        
        TomlFileIO(
            const TomlFileIO& toml_file_io
        ) = delete;
        
        TomlFileIO(
            TomlFileIO&& toml_file_io
        ) noexcept = default;
        
        TomlFileIO& operator = (
            const TomlFileIO& toml_file_io
        ) = delete;
        
        TomlFileIO& operator = (
            TomlFileIO&& toml_file_io
        ) noexcept = default;

        bool setup(
            const std::string& file_path
        );

        bool setup(
            const std::string& name,
            const std::string& file_path
        );

        bool load();
        
        bool save();
        
        bool save_as(
            const std::string& file_path
        );
        
        template<typename ValueType>
        std::optional<ValueType> get_value(
            const std::vector<std::string>& key_path
        );
        
        template<typename ValueType>
        bool set_value(
            const std::vector<std::string>& key_path,
            const ValueType& value
        );
        
        bool remove_value(
            const std::vector<std::string>& key_path
        );
        
        template<typename ValueType>
        bool set_values(
            const std::unordered_map<std::vector<std::string>,
            ValueType, VectorStringHash, VectorStringEqual>& map
        );
        
        bool remove_keys(
            const std::vector<std::vector<std::string>>& keys
        );
        
        std::future<bool> load_async();
        
        std::future<bool> save_async();
        
        std::future<bool> save_as_async(
            const std::string& file_path
        );
        
        template<typename ValueType>
        std::future<std::optional<ValueType>>
            get_value_async(
                const std::vector<std::string>& key_path
        );
        
        template<typename ValueType>
        std::future<bool>
            set_value_async(
                const std::vector<std::string>& key_path,
                const ValueType& value
            );
        
        std::future<bool> remove_value_async(
            const std::vector<std::string>& key_path
        );
        
        template<typename ValueType>
        std::future<bool> set_values_async(
            const std::unordered_map<std::vector<std::string>,
            ValueType,
            VectorStringHash, VectorStringEqual>& values
        );
        
        std::future<bool> remove_keys_async(
            const std::vector<std::vector<std::string>>& keys
        );

        void load(
            Result<bool>& result
        );

        void save(
            Result<bool>& result
        );

        void save_as(
            Result<bool>& result,
            const std::string& file_path
        );

        void remove_value(
            Result<bool>& result,
            const std::vector<std::string>& key_path
        );

        void remove_keys(
            Result<bool>& result,
            const std::vector<std::vector<std::string>>& keys
        );

        void load_async(
            Result<std::future<bool>>& result
        );

        void save_async(
            Result<std::future<bool>>& result
        );

        void save_as_async(
            Result<std::future<bool>>& result,
            const std::string& file_path
        );

        void remove_value_async(
            Result<std::future<bool>>& result,
            const std::vector<std::string>& key_path
        );

        void remove_keys_async(
            Result<std::future<bool>>& result,
            const std::vector<std::vector<std::string>>& keys
        );

        template<typename ValueType>
        void get_value(
            Result<ValueType>& result,
            const std::vector<std::string>& key_path
        );

        template<typename ValueType>
        void set_value(
            Result<bool>& result,
            const std::vector<std::string>& key_path,
            const ValueType& value
        );

        template<typename ValueType>
        void set_values(
            Result<bool>& result,
            const std::unordered_map<std::vector<std::string>,
            ValueType, VectorStringHash, VectorStringEqual>& map
        );

        template<typename ValueType>
        void get_value_async(
            Result<std::future<ValueType>>& result,
            const std::vector<std::string>& key_path
        );

        template<typename ValueType>
        void set_value_async(
            Result<std::future<bool>>& result,
            const std::vector<std::string>& key_path,
            const ValueType& value
        );

        template<typename ValueType>
        void set_values_async(
            Result<std::future<bool>>& result,
            const std::unordered_map<std::vector<std::string>,
            ValueType,
            VectorStringHash, VectorStringEqual>& values
        );

        void setup(
            Result<void>& result,
            const std::string& file_path
        );

        void setup(
            Result<void>& result,
            const std::string& name,
            const std::string& file_path
        );

    private:
        std::optional<toml::table*> _toml_root;

        std::optional<std::string> _raw_buffer;
    };

    template<typename ValueType>
    std::optional<ValueType> TomlFileIO::get_value(
        const std::vector<std::string>& key_path)
    {
        std::scoped_lock lock(_mutex);

        if (!_toml_root.has_value() || key_path.empty())
        {
            return std::nullopt;
        }

        const toml::node* node = _toml_root.value();

        for (const auto& key : key_path)
        {
            if (!node || !node->is_table())
            {
                return std::nullopt;
            }

            const toml::table* table = node->as_table();
            const toml::node* next = table->get(key);

            if (!next)
            {
                return std::nullopt;
            }

            node = next;
        }

        if constexpr (std::is_same_v<ValueType, std::vector<std::string>>)
        {
            const toml::array* array = node ? node->as_array() : nullptr;
            if (!array) return std::nullopt;

            std::vector<std::string> result;
            for (const auto& item : *array)
            {
                if (const auto str = item.value<std::string>())
                {
                    result.push_back(*str);
                }
                else
                {
                    return std::nullopt;
                }
            }
            return result;
        }
        else
        {
            if (!node) return std::nullopt;
            auto value = node->value<ValueType>();
            if (value) return value;
            return std::nullopt;
        }
    }

    template<typename ValueType>
    bool TomlFileIO::set_value(
        const std::vector<std::string>& key_path,
        const ValueType& value)
    {
        std::scoped_lock lock(_mutex);

        if (!_toml_root.has_value() || key_path.empty())
        {
            return false;
        }

        toml::table* current_table =
            static_cast<toml::table*>(_toml_root.value());

        for (std::size_t i = 0; i < key_path.size() - 1; ++i)
        {
            toml::node* child = current_table->get(key_path[i]);

            if (!child)
            {
                auto [iter, _] = current_table->insert(
                    key_path[i], toml::table{});
                child = &iter->second;
            }

            if (!child->is_table())
            {
                return false;
            }

            current_table = child->as_table();
        }

        if constexpr (std::is_same_v<ValueType, std::vector<std::string>>)
        {
            toml::array array;
            for (const auto& item : value)
            {
                array.push_back(item);
            }
            current_table->insert_or_assign(
                key_path.back(), std::move(array));
        }
        else
        {
            current_table->insert_or_assign(key_path.back(), value);
        }

        return true;
    }

    template<typename ValueType>
    bool TomlFileIO::set_values(
        const std::unordered_map<std::vector<std::string>, ValueType,
        VectorStringHash, VectorStringEqual>& map)
    {
        bool success = true;
        for (const auto& pair : map)
        {
            success &= set_value(pair.first, pair.second);
        }
        return success;
    }

    template<typename ValueType>
    std::future<std::optional<ValueType>> TomlFileIO::get_value_async(
        const std::vector<std::string>& key_path)
    {
        return std::async(std::launch::async, [this, key_path]()
            {
                return get_value<ValueType>(key_path);
            });
    }

    template<typename ValueType>
    std::future<bool> TomlFileIO::set_value_async(
        const std::vector<std::string>& key_path,
        const ValueType& value)
    {
        return std::async(std::launch::async, [this, key_path, value]()
            {
                return set_value<ValueType>(key_path, value);
            });
    }

    template<typename ValueType>
    std::future<bool> TomlFileIO::set_values_async(
        const std::unordered_map<std::vector<std::string>, ValueType,
        VectorStringHash, VectorStringEqual>& values)
    {
        return std::async(std::launch::async, [this, values]()
            {
                return set_values<ValueType>(values);
            });
    }


    template<typename ValueType>
    void TomlFileIO::get_value(
        Result<ValueType>& result,
        const std::vector<std::string>& key_path
    )
    {
        std::scoped_lock lock(_mutex);

        if (!_toml_root.has_value() || key_path.empty())
        {
            return result.set_to_bad_status_without_value(
                "File has no value or key path is empty"
            );
        }

        const toml::node* node = _toml_root.value();

        for (const auto& key : key_path)
        {
            if (!node || !node->is_table())
            {
                return result.set_to_bad_status_without_value(
                    "Node is empty or is not a table"
                );
            }

            const toml::table* table = node->as_table();
            const toml::node* next = table->get(key);

            if (!next)
            {
                return result.set_to_bad_status_without_value(
                    "Table is empty"
                );
            }

            node = next;
        }

        if constexpr (std::is_same_v<ValueType, std::vector<std::string>>)
        {
            const toml::array* array = node ? node->as_array() : nullptr;
            if (!array)
            {
                return result.set_to_bad_status_without_value(
                    "Array is empty"
                );
            }

            std::vector<std::string> values;
            for (const auto& item : *array)
            {
                if (const auto str = item.value<std::string>())
                {
                    values.push_back(*str);
                }
                else
                {
                    return result.set_to_bad_status_without_value(
                        "List is empty"
                    );
                }
            }

            return result.set_to_good_status_without_value(
                values
            );
        }
        else
        {
            if (!node)
            {
                return result.set_to_bad_status_without_value(
                    "Node is empty"
                );
            }
            auto value = node->value<ValueType>();
            if (value)
            {
                return result.set_to_good_status_without_value(
                    value
                );
            }

            return result.set_to_bad_status_without_value(
                "Value does not exist"
            );
        }
    }

    template<typename ValueType>
    void TomlFileIO::set_value(
        Result<bool>& result,
        const std::vector<std::string>& key_path,
        const ValueType& value
    )
    {
        std::scoped_lock lock(_mutex);

        if (!_toml_root.has_value() || key_path.empty())
        {
            return result.set_to_bad_status_without_value(
                "Root has no value or key path is empty"
            );
        }

        toml::table* current_table =
            static_cast<toml::table*>(_toml_root.value());

        for (std::size_t i = 0; i < key_path.size() - 1; ++i)
        {
            toml::node* child = current_table->get(key_path[i]);

            if (!child)
            {
                auto [iter, _] = current_table->insert(
                    key_path[i], toml::table{});
                child = &iter->second;
            }

            if (!child->is_table())
            {
                return result.set_to_bad_status_without_value(
                    "Table is empty"
                );
            }

            current_table = child->as_table();
        }

        if constexpr (std::is_same_v<ValueType, std::vector<std::string>>)
        {
            toml::array array;
            for (const auto& item : value)
            {
                array.push_back(item);
            }
            current_table->insert_or_assign(
                key_path.back(),
                std::move(array)
            );
        }
        else
        {
            current_table->insert_or_assign(key_path.back(), value);
        }

        return result.set_to_good_status_without_value(
            true
        );
    }

    template<typename ValueType>
    void TomlFileIO::set_values(
        Result<bool>& result,
        const std::unordered_map<std::vector<std::string>,
        ValueType, VectorStringHash, VectorStringEqual>& map
    )
    {
        bool success = true;
        for (const auto& pair : map)
        {
            success &= set_value(pair.first, pair.second);
        }

        return result.set_to_good_status_without_value(
            success
        );
    }

    template<typename ValueType>
    void TomlFileIO::get_value_async(
        Result<std::future<ValueType>>& result,
        const std::vector<std::string>& key_path
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async, [this, key_path]() -> ValueType
            {
                Result<ValueType> result;

                get_value<ValueType>(result, key_path);

                return result.get_value();
            })
        );
    }

    template<typename ValueType>
    void TomlFileIO::set_value_async(
        Result<std::future<bool>>& result,
        const std::vector<std::string>& key_path,
        const ValueType& value
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async, [this, key_path, value]() -> bool
            {
                Result<bool> result;

                set_value<ValueType>(result, key_path, value);

                return result.get_value();
            })
        );
    }

    template<typename ValueType>
    void TomlFileIO::set_values_async(
        Result<std::future<bool>>& result,
        const std::unordered_map<std::vector<std::string>,
        ValueType,
        VectorStringHash, VectorStringEqual>& values
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async, [this, values]() -> bool
            {
                Result<bool> result;

                set_values<ValueType>(result, values);

                return result.get_value();
            })
        );
    }
}
