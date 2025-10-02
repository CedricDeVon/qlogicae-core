#pragma once

#include "utilities.hpp"
#include "abstract_file_io.hpp"

#include <fast_io.h>                      
#include <fast_io_device.h>                
#include <fast_io_legacy.h>

#include <string>
#include <cstdint>
#include <optional>

namespace QLogicaeCore
{
    class TextFileIO :
        public AbstractFileIO
    {
    public:
        ~TextFileIO();
        
        TextFileIO() = default;
        
        TextFileIO(
            const std::string_view& file_path
        );
        
        TextFileIO(
            const TextFileIO& text_file_io
        ) = delete;
        
        TextFileIO(
            TextFileIO&& text_file_io
        ) noexcept = delete;
        
        TextFileIO& operator = (
            const TextFileIO& text_file_io
        ) = delete;
        
        TextFileIO& operator = (
            TextFileIO&& text_file_io
        ) noexcept = delete;
        
        TextFileIO(
            const std::string_view& name,
            const std::string_view& file_path
        );

        std::string read();
        
        bool open(const FileMode& file_mode);
        
        bool close(const FileMode& file_mode);
        
        bool is_open(const FileMode& file_mode);
        
        bool write(const std::string_view& text);
        
        bool append(const std::string_view& text);

        std::future<std::string> read_async();
        
        std::future<bool> open_async(const FileMode& file_mode);
        
        std::future<bool> close_async(const FileMode& file_mode);
        
        std::future<bool> write_async(const std::string_view& text);
        
        std::future<bool> append_async(const std::string_view& text);

    protected:
        std::optional<fast_io::obuf_file> _write_file;
        std::optional<fast_io::obuf_file> _append_file;
        std::optional<fast_io::native_file_loader> _read_file;
    };
}

