#pragma once

#include "pch.h"

#include "text_file_io.hpp"

namespace QLogicaeCore
{
    TextFileIO::TextFileIO(
        const std::string_view& file_path) :
        AbstractFileIO(file_path)
    {

    }

    TextFileIO::TextFileIO(
        const std::string_view& name,
        const std::string_view& file_path) :
            AbstractFileIO(name, file_path)
    {

    }

    TextFileIO::~TextFileIO()
    {
        close(FileMode::READ);
        close(FileMode::WRITE);
        close(FileMode::APPEND);
    }

    bool TextFileIO::open(const FileMode& file_mode)
    {
        try
        {
            switch (file_mode)
            {
            case FileMode::READ:
                if (!std::filesystem::exists(_file_path))
                {
                    return false;
                }
                if (!_read_file)
                {
                    _read_file.emplace(_file_path);
                }
                return true;

            case FileMode::WRITE:
                if (!_write_file)
                {
                    _write_file.emplace(_file_path);
                }
                return true;

            case FileMode::APPEND:
                if (!_append_file)
                {
                    _append_file.emplace(
                        _file_path,
                        fast_io::open_mode::app
                    );
                }
                return true;

            default:
                return false;
            }
        }
        catch (...)
        {
            return false;
        }
    }

    bool TextFileIO::close(const FileMode& file_mode)
    {
        try
        {
            switch (file_mode)
            {
            case FileMode::READ:
                if (_read_file)
                {
                    _read_file.reset();
                }
                return true;

            case FileMode::WRITE:
                if (_write_file)
                {
                    _write_file.reset();
                }
                return true;

            case FileMode::APPEND:
                if (_append_file)
                {
                    _append_file.reset();
                }
                return true;

            default:
                return false;
            }
        }
        catch (...)
        {
            return false;
        }
    }

    bool TextFileIO::is_open(const FileMode& file_mode)
    {
        try
        {
            switch (file_mode)
            {
            case FileMode::READ:
                return _read_file.has_value();

            case FileMode::WRITE:
                return _write_file.has_value();

            case FileMode::APPEND:
                return _append_file.has_value();

            default:
                return false;
            }
        }
        catch (...)
        {
            return false;
        }
    }

    std::string TextFileIO::read()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!open(FileMode::READ))
            {
                return "";
            }

            fast_io::native_file_loader& file_loader =
                _read_file.value();
            std::string content{
                file_loader.begin(),
                file_loader.end()
            };

            return content;
        }
        catch (...)
        {
            return "";
        }
    }

    bool TextFileIO::write(const std::string_view& content)
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!open(FileMode::WRITE))
            {
                return false;
            }

            fast_io::io::print(_write_file.value(), content);

            close(FileMode::READ);
            close(FileMode::WRITE);
            close(FileMode::APPEND);

            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool TextFileIO::append(const std::string_view& content)
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!open(FileMode::APPEND))
            {
                return false;
            }

            fast_io::io::print(_append_file.value(), content);

            close(FileMode::READ);
            close(FileMode::WRITE);
            close(FileMode::APPEND);

            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    std::future<std::string> TextFileIO::read_async()
    {
        return std::async(std::launch::async,
            [this]() -> std::string
        {
            try
            {
                return read();
            }
            catch (...)
            {
                return {};
            }
        });
    }

    std::future<bool> TextFileIO::write_async(
        const std::string_view& content)
    {
        return std::async(std::launch::async,
            [this, content]() -> bool
        {
            try
            {
                return write(content);
            }
            catch (...)
            {
                return false;
            }
        });
    }

    std::future<bool> TextFileIO::append_async(
        const std::string_view& content)
    {
        return std::async(std::launch::async,
            [this, content]() -> bool
        {
            try
            {
                return append(content);
            }
            catch (...)
            {
                return false;
            }
        });
    }

    std::future<bool> TextFileIO::open_async(
        const FileMode& file_mode)
    {
        return std::async(std::launch::async,
            [this, file_mode]() -> bool
        {
            try
            {
                return open(file_mode);
            }
            catch (...)
            {
                return false;
            }
        });
    }

    std::future<bool> TextFileIO::close_async(
        const FileMode& file_mode)
    {
        return std::async(std::launch::async,
            [this, file_mode]() -> bool
        {
            try
            {
                return close(file_mode);
            }
            catch (...)
            {
                return false;
            }
        });
    }
}

