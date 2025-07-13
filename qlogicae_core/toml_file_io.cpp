#pragma once

#include "pch.h"

#include "toml_file_io.hpp"

namespace QLogicaeCore
{
    TomlFileIO::TomlFileIO()
    {
        std::scoped_lock lock(_mutex);
        _toml_root = std::make_optional<toml::table*>(new toml::table{});
    }

    TomlFileIO::~TomlFileIO()
    {
        std::scoped_lock lock(_mutex);
        if (_toml_root.has_value())
        {
            delete _toml_root.value();
            _toml_root.reset();
        }
        _raw_buffer.reset();
    }

    TomlFileIO::TomlFileIO(const std::string_view& file_path)
        : AbstractFileIO(file_path)
    {
        std::scoped_lock lock(_mutex);
        _toml_root = std::make_optional<toml::table*>(new toml::table{});
    }

    TomlFileIO::TomlFileIO(
        const std::string_view& name,
        const std::string_view& file_path)
        : AbstractFileIO(name, file_path)
    {
        std::scoped_lock lock(_mutex);
        _toml_root = std::make_optional<toml::table*>(new toml::table{});
    }

    bool TomlFileIO::load()
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return false;
        }

        try
        {
            toml::table parsed_table = toml::parse_file(_file_path);
            if (_toml_root.has_value())
            {
                delete _toml_root.value();
            }
            _toml_root = new toml::table(std::move(parsed_table));
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool TomlFileIO::save()
    {
        return save_as(_file_path);
    }

    bool TomlFileIO::save_as(const std::string_view& file_path)
    {
        std::scoped_lock lock(_mutex);

        if (file_path.empty() || !_toml_root.has_value())
        {
            return false;
        }

        try
        {
            std::ostringstream output_stream;
            output_stream << toml::default_formatter{ *(_toml_root.value()) };
            std::string output = output_stream.str();

            fast_io::u8obuf_file output_file(
                std::u8string(reinterpret_cast<const char8_t*>(file_path.data()))
            );

            fast_io::io::print(
                output_file,
                std::u8string_view(
                    reinterpret_cast<const char8_t*>(output.data()),
                    output.size()));

            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool TomlFileIO::remove_value(const std::vector<std::string>& key_path)
    {
        std::scoped_lock lock(_mutex);

        if (!_toml_root.has_value() || key_path.empty())
        {
            return false;
        }

        toml::table* root = static_cast<toml::table*>(_toml_root.value());
        toml::node* current = root;

        for (std::size_t index = 0; index < key_path.size() - 1; ++index)
        {
            current = current->as_table()->get(key_path[index]);
            if (!current || !current->is_table())
            {
                return false;
            }
        }

        return current->as_table()->erase(key_path.back());
    }

    bool TomlFileIO::remove_keys(
        const std::vector<std::vector<std::string>>& keys)
    {
        bool success = true;
        for (const std::vector<std::string>& path : keys)
        {
            success &= remove_value(path);
        }
        return success;
    }

    std::future<bool> TomlFileIO::load_async()
    {
        return std::async(std::launch::async, [this]() -> bool
            {
                return load();
            });
    }

    std::future<bool> TomlFileIO::save_async()
    {
        return std::async(std::launch::async, [this]() -> bool
            {
                return save();
            });
    }

    std::future<bool> TomlFileIO::save_as_async(
        const std::string_view& file_path)
    {
        return std::async(std::launch::async, [this, file_path]() -> bool
            {
                return save_as(file_path);
            });
    }

    std::future<bool> TomlFileIO::remove_value_async(
        const std::vector<std::string>& key_path)
    {
        return std::async(std::launch::async, [this, key_path]() -> bool
            {
                return remove_value(key_path);
            });
    }

    std::future<bool> TomlFileIO::remove_keys_async(
        const std::vector<std::vector<std::string>>& keys)
    {
        return std::async(std::launch::async, [this, keys]()
            {
                return remove_keys(keys);
            });
    }
}
