#include "pch.hpp"

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

    TomlFileIO::TomlFileIO(
        const std::string& file_path
    )
        : AbstractFileIO(file_path)
    {
        std::scoped_lock lock(_mutex);
        _toml_root = std::make_optional<toml::table*>(new toml::table{});
    }

    TomlFileIO::TomlFileIO(
        const std::string& name,
        const std::string& file_path)
        : AbstractFileIO(name, file_path)
    {
        std::scoped_lock lock(_mutex);
        _toml_root = std::make_optional<toml::table*>(new toml::table{});
    }

    bool TomlFileIO::setup(
        const std::string& file_path
    )
    {
        Result<void> void_result;

        setup(void_result, file_path);

        return void_result.is_status_safe();
    }

    bool TomlFileIO::setup(
        const std::string& name,
        const std::string& file_path
    )
    {
        Result<void> void_result;

        setup(void_result, name, file_path);

        return void_result.is_status_safe();
    }

    bool TomlFileIO::load()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (_file_path.empty())
            {
                return false;
            }

            toml::table parsed_table = toml::parse_file(_file_path);
            if (_toml_root.has_value())
            {
                delete _toml_root.value();
            }
            _toml_root = new toml::table(std::move(parsed_table));
            return true;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at TomlFileIO::is_cancelled(): " +
                exception.what()
            );
        }
    }

    bool TomlFileIO::save()
    {
        return save_as(_file_path);
    }

    bool TomlFileIO::save_as(
        const std::string& file_path
    )
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (file_path.empty() || !_toml_root.has_value())
            {
                return false;
            }

            std::ostringstream output_stream;
            output_stream << toml::default_formatter{ *(_toml_root.value()) };
            std::string output = output_stream.str();

            fast_io::u8obuf_file output_file(
                std::u8string(reinterpret_cast<const char8_t*>(file_path.data()))
            );

            fast_io::io::print(
                output_file,
                std::u8string(
                    reinterpret_cast<const char8_t*>(output.data()),
                    output.size()));

            return true;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at TomlFileIO::save_as(): " +
                exception.what()
            );
        }
    }

    bool TomlFileIO::remove_value(
        const std::vector<std::string>& key_path
    )
    {
        try
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at TomlFileIO::remove_value(): " +
                exception.what()
            );
        }
    }

    bool TomlFileIO::remove_keys(
        const std::vector<std::vector<std::string>>& keys
    )
    {
        try
        {
            bool success = true;
            for (const std::vector<std::string>& path : keys)
            {
                success &= remove_value(path);
            }
            return success;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at TomlFileIO::remove_keys(): " +
                exception.what()
            );
        }
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
        const std::string& file_path)
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



    void TomlFileIO::load(
        Result<bool>& result
    )
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return result.set_to_bad_status_without_value(
                "File is empty"
            );
        }

        toml::table parsed_table = toml::parse_file(_file_path);
        if (_toml_root.has_value())
        {
            delete _toml_root.value();
        }
        _toml_root = new toml::table(std::move(parsed_table));
        result.set_to_good_status_with_value(
            true
        );
    }

    void TomlFileIO::save(
        Result<bool>& result
    )
    {
        save_as(result, _file_path);
    }

    void TomlFileIO::save_as(
        Result<bool>& result,
        const std::string& file_path
    )
    {
        std::scoped_lock lock(_mutex);

        if (file_path.empty() || !_toml_root.has_value())
        {
            return result.set_to_bad_status_without_value(
                "File is empty"
            );
        }

        std::ostringstream output_stream;
        output_stream << toml::default_formatter{ *(_toml_root.value()) };
        std::string output = output_stream.str();

        fast_io::u8obuf_file output_file(
            std::u8string(reinterpret_cast<const char8_t*>(file_path.data()))
        );

        fast_io::io::print(
            output_file,
            std::u8string(
                reinterpret_cast<const char8_t*>(output.data()),
                output.size()));

        result.set_to_good_status_with_value(
            true
        );
    }

    void TomlFileIO::remove_value(
        Result<bool>& result,
        const std::vector<std::string>& key_path
    )
    {
        std::scoped_lock lock(_mutex);

        if (!_toml_root.has_value() || key_path.empty())
        {
            return result.set_to_bad_status_without_value(
                "File or key path is empty"
            );
        }

        toml::table* root = static_cast<toml::table*>(_toml_root.value());
        toml::node* current = root;

        for (std::size_t index = 0; index < key_path.size() - 1; ++index)
        {
            current = current->as_table()->get(key_path[index]);
            if (!current || !current->is_table())
            {
                return result.set_to_bad_status_without_value(
                    "Value is null or not a table"
                );
            }
        }

        result.set_to_good_status_with_value(
            current->as_table()->erase(key_path.back())
        );
    }

    void TomlFileIO::remove_keys(
        Result<bool>& result,
        const std::vector<std::vector<std::string>>& keys
    )
    {
        bool success = true;
        for (const std::vector<std::string>& path : keys)
        {
            success &= remove_value(path);
        }

        result.set_to_good_status_with_value(
            success
        );
    }

    void TomlFileIO::load_async(
        Result<std::future<bool>>& result
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async, [this]() -> bool
            {
                Result<bool> result;

                load(
                    result
                );

                return result.get_value();
            })
        );
    }

    void TomlFileIO::save_async(
        Result<std::future<bool>>& result
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async, [this]() -> bool
            {
                Result<bool> result;

                save(
                    result
                );

                return result.get_value();
            })
        );
    }

    void TomlFileIO::save_as_async(
        Result<std::future<bool>>& result,
        const std::string& file_path
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async, [this, file_path]() -> bool
            {
                Result<bool> result;

                save_as(
                    result,
                    file_path
                );

                return result.get_value();
            })
        );
    }

    void TomlFileIO::remove_value_async(
        Result<std::future<bool>>& result,
        const std::vector<std::string>& key_path
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async, [this, key_path]() -> bool
            {
                Result<bool> result;

                remove_value(
                    result,
                    key_path
                );

                return result.get_value();
            })
        );
    }

    void TomlFileIO::remove_keys_async(
        Result<std::future<bool>>& result,
        const std::vector<std::vector<std::string>>& keys
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async, [this, keys]() -> bool
            {
                Result<bool> result;

                remove_keys(
                    result,
                    keys
                );

                return result.get_value();
            })
        );
    }

    void TomlFileIO::setup(
        Result<void>& result,
        const std::string& file_path
    )
    {
        _file_path = file_path;

        result.set_to_good_status_without_value();
    }

    void TomlFileIO::setup(
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
