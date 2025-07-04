#pragma once

#include "pch.h"

#include "abstract_file_io.hpp"

namespace QLogicaeCore
{
    class TextFileIO : public AbstractFileIO
    {
    public:
        ~TextFileIO();
        TextFileIO() = default;
        TextFileIO(const std::string_view&);
        TextFileIO(const TextFileIO&) = delete;
        TextFileIO(TextFileIO&&) noexcept = delete;
        TextFileIO& operator = (const TextFileIO&) = delete;
        TextFileIO& operator = (TextFileIO&&) noexcept = delete;
        TextFileIO(const std::string_view&, const std::string_view&);

        std::string read();
        bool open(const FileMode&);
        bool close(const FileMode&);
        bool is_open(const FileMode&);
        bool write(const std::string_view&);
        bool append(const std::string_view&);

        std::future<std::string> read_async();
        std::future<bool> open_async(const FileMode&);
        std::future<bool> close_async(const FileMode&);
        std::future<bool> write_async(const std::string_view&);
        std::future<bool> append_async(const std::string_view&);

    protected:
        std::optional<fast_io::obuf_file> _write_file;
        std::optional<fast_io::obuf_file> _append_file;
        std::optional<fast_io::native_file_loader> _read_file;
    };
}

