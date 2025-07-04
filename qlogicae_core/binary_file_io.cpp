#pragma once

#include "pch.h"

#include "binary_file_io.hpp"

namespace QLogicaeCore
{
    BinaryFileIO::BinaryFileIO(
        const std::string_view& file_path) :
        AbstractFileIO(file_path)
    {
    }

    BinaryFileIO::BinaryFileIO(
        const std::string_view& name,
        const std::string_view& file_path) :
        AbstractFileIO(name, file_path)
    {
    }

    BinaryFileIO::~BinaryFileIO()
    {
        close(FileMode::READ);
        close(FileMode::WRITE);
        close(FileMode::APPEND);
    }

    bool BinaryFileIO::open(const FileMode& file_mode)
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

    bool BinaryFileIO::close(const FileMode& file_mode)
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

    bool BinaryFileIO::is_open(const FileMode& file_mode)
    {
        try
        {
            switch (file_mode)
            {
                case FileMode::READ:
                {
                    return _read_file.has_value();
                }
                case FileMode::WRITE:
                {
                    return _write_file.has_value();
                }
                case FileMode::APPEND:
                {
                    return _append_file.has_value();
                }
                default:
                {
                    return false;
                }
            }
        }
        catch (...)
        {
            return false;
        }
    }

    std::vector<std::byte> BinaryFileIO::read()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!open(FileMode::READ))
            {
                return {};
            }

            fast_io::native_file_loader& file_loader =
                _read_file.value();
            auto span_bytes =
                std::as_bytes(
                    std::span(
                        file_loader.data(),
                        file_loader.size()
                    )
                );
            std::vector<std::byte> content(
                span_bytes.begin(),
                span_bytes.end()
            );

            return content;
        }
        catch (...)
        {
            return {};
        }
    }

    bool BinaryFileIO::write(
        const std::span<const std::byte>& content
    )
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!open(FileMode::WRITE))
            {
                return false;
            }

            fast_io::write(
                _write_file.value(),
                content.begin(),
                content.end()
            );

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

    bool BinaryFileIO::append(
        const std::span<const std::byte>& content)
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!open(FileMode::APPEND))
            {
                return false;
            }

            fast_io::write(
                _append_file.value(), 
                content.begin(),
                content.end()
            );

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

    std::future<std::vector<std::byte>> BinaryFileIO::read_async()
    {
        return std::async(std::launch::async,
            [this]() -> std::vector<std::byte>
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

    std::future<bool> BinaryFileIO::write_async(
        const std::span<const std::byte>& content)
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

    std::future<bool> BinaryFileIO::append_async(
        const std::span<const std::byte>& content)
    {
        return std::async(std::launch::async, [this, content]() -> bool
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

    std::future<bool> BinaryFileIO::open_async(const FileMode& file_mode)
    {
        return std::async(std::launch::async, [this, file_mode]() -> bool
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

    std::future<bool> BinaryFileIO::close_async(const FileMode& file_mode)
    {
        return std::async(std::launch::async, [this, file_mode]() -> bool
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
