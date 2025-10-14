#include "pch.hpp"

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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at BinaryFileIO::open(): " + exception.what());
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at BinaryFileIO::close(): " + exception.what());
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at BinaryFileIO::is_open(): " + exception.what());
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at BinaryFileIO::read(): " + exception.what());
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at BinaryFileIO::write(): " + exception.what());
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at BinaryFileIO::append(): " + exception.what());
        }
    }

    std::future<std::vector<std::byte>> BinaryFileIO::read_async()
    {
        return std::async(std::launch::async,
            [this]() -> std::vector<std::byte>
        {
            return read();
        });
    }

    std::future<bool> BinaryFileIO::write_async(
        const std::span<const std::byte>& content)
    {
        return std::async(std::launch::async,
            [this, content]() -> bool
        {
            return write(content);
        });
    }

    std::future<bool> BinaryFileIO::append_async(
        const std::span<const std::byte>& content)
    {
        return std::async(std::launch::async, [this, content]() -> bool
        {
            return append(content);            
        });
    }

    std::future<bool> BinaryFileIO::open_async(const FileMode& file_mode)
    {
        return std::async(std::launch::async, [this, file_mode]() -> bool
        {
            return open(file_mode);
        });
    }

    std::future<bool> BinaryFileIO::close_async(const FileMode& file_mode)
    {
        return std::async(std::launch::async, [this, file_mode]() -> bool
        {
            return close(file_mode);            
        });
    }
}

