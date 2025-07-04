#pragma once

#include "pch.h"

#include "abstract_file_io.hpp"

namespace QLogicaeCore
{
    class TomlFileIO : public AbstractFileIO
    {
    public:
        ~TomlFileIO();
        TomlFileIO() = default;
        TomlFileIO(const std::string_view&);
        TomlFileIO(const TomlFileIO&) = delete;
        TomlFileIO(TomlFileIO&&) noexcept = default;
        TomlFileIO& operator = (const TomlFileIO&) = delete;
        TomlFileIO& operator = (TomlFileIO&&) noexcept = default;
        TomlFileIO(const std::string_view&, const std::string_view&);

        std::string read();
        bool write(const std::string_view&);
        bool remove_value(const std::vector<std::variant<std::string_view, int>>&);
        bool is_key_path_valid(const std::vector<std::variant<std::string_view, int>>&);
        template <typename Type> Type get_value(const std::vector<std::variant<std::string_view, int>>&);
        template <typename Type> bool set_value(const std::vector<std::variant<std::string_view, int>>&, const Type&);

        std::future<std::string> read_async();
        std::future<bool> write_async(const std::string_view&);
        std::future<bool> remove_value_async(const std::vector<std::variant<std::string_view, int>>&);
        template <typename Type> std::future<Type> get_value_async(const std::vector<std::variant<std::string_view, int>>&);
        template <typename Type> std::future<bool> set_value_async(const std::vector<std::variant<std::string_view, int>>&, const Type&);
    
    protected:
        std::optional<fast_io::obuf_file> _write_file;
        std::optional<fast_io::obuf_file> _append_file;
        std::optional<toml::table> _temporary_toml_table_1;
    };
}

