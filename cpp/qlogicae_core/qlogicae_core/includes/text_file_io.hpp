#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "utilities.hpp"
#include "file_mode.hpp"
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
        TextFileIO();

        ~TextFileIO();        
        
        TextFileIO(
            const std::string& file_path
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
            const std::string& name,
            const std::string& file_path
        );

        bool setup(
            const std::string& file_path
        );

        void setup(
            Result<void>& result,
            const std::string& file_path
        );

        bool setup(
            const std::string& name,
            const std::string& file_path
        );

        void setup(
            Result<void>& result,
            const std::string& name,
            const std::string& file_path
        );

        std::string read();

        void read(
            Result<std::string>& result
        );

        bool open(
            const FileMode& file_mode
        );

        void open(
            Result<bool>& result,
            const FileMode& file_mode
        );

        bool close(
            const FileMode& file_mode
        );

        void close(
            Result<bool>& result,
            const FileMode& file_mode
        );

        bool is_open(
            const FileMode& file_mode
        );

        void is_open(
            Result<bool>& result,
            const FileMode& file_mode
        );

        bool write(
            const std::string& text
        );

        void write(
            Result<bool>& result,
            const std::string& text
        );

        bool append(
            const std::string& text
        );

        void append(
            Result<bool>& result,
            const std::string& text
        );

        std::future<std::string> read_async(
            const std::function<void(const std::string& result)>& callback =
                [](const std::string& result) {}
        );

        void read_async(
            Result<std::future<std::string>>& result,
            const std::function<void(Result<std::string>& result)>& callback =
                [](Result<std::string>& result) {}
        );

        std::future<bool> open_async(
            const FileMode& file_mode,
            const std::function<void(const bool& result)>& callback =
                [](const bool& result) {}
        );

        void open_async(
            Result<std::future<bool>>& result,
            const FileMode& file_mode,
            const std::function<void(Result<bool>& result)>& callback =
                [](Result<bool>& result) {}
        );

        std::future<bool> close_async(
            const FileMode& file_mode,
            const std::function<void(const bool& result)>& callback =
                [](const bool& result) {}
        );

        void close_async(
            Result<std::future<bool>>& result,
            const FileMode& file_mode,
            const std::function<void(Result<bool>& result)>& callback =
                [](Result<bool>& result) {}
        );

        std::future<bool> write_async(
            const std::string& text,
            const std::function<void(const bool& result)>& callback =
                [](const bool& result) {}
        );

        void write_async(
            Result<std::future<bool>>& result,
            const std::string& text,
            const std::function<void(Result<bool>& result)>& callback =
                [](Result<bool>& result) {}
        );

        std::future<bool> append_async(
            const std::string& text,
            const std::function<void(const bool& result)>& callback =
                [](const bool& result) {}
        );

        void append_async(
            Result<std::future<bool>>& result,
            const std::string& text,
            const std::function<void(Result<bool>& result)>& callback =
                [](Result<bool>& result) {}
        );

        static TextFileIO& get_instance();

        static void get_instance(
            Result<TextFileIO*>& result
        );

    protected:
        std::optional<fast_io::obuf_file> _write_file;
        
        std::optional<fast_io::obuf_file> _append_file;

        std::optional<fast_io::native_file_loader> _read_file;
    };

    inline static TextFileIO& TEXT_FILE_IO =
        TextFileIO::get_instance();
}
