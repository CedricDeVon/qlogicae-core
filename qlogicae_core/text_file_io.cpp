#include "pch.hpp"

#include "text_file_io.hpp"

namespace QLogicaeCore
{
    TextFileIO::TextFileIO(
        const std::string& file_path) :
        AbstractFileIO(file_path)
    {

    }

    TextFileIO::TextFileIO(
        const std::string& name,
        const std::string& file_path) :
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at TextFileIO::open(): " + exception.what());
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at TextFileIO::close(): " + exception.what());
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at TextFileIO::is_open(): " + exception.what());
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at TextFileIO::read(): " + exception.what());
        }
    }

    bool TextFileIO::write(const std::string& content)
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at TextFileIO::write(): " + exception.what());
        }
    }

    bool TextFileIO::append(const std::string& content)
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at TextFileIO::append(): " + exception.what());
        }
    }

    std::future<std::string> TextFileIO::read_async()
    {
        return std::async(std::launch::async,
            [this]() -> std::string
        {
            return read();            
        });
    }

    std::future<bool> TextFileIO::write_async(
        const std::string& content)
    {
        return std::async(std::launch::async,
            [this, content]() -> bool
        {
            return write(content);            
        });
    }

    std::future<bool> TextFileIO::append_async(
        const std::string& content)
    {
        return std::async(std::launch::async,
            [this, content]() -> bool
        {
            return append(content);            
        });
    }

    std::future<bool> TextFileIO::open_async(
        const FileMode& file_mode)
    {
        return std::async(std::launch::async,
            [this, file_mode]() -> bool
        {
            return open(file_mode);            
        });
    }

    std::future<bool> TextFileIO::close_async(
        const FileMode& file_mode)
    {
        return std::async(std::launch::async,
            [this, file_mode]() -> bool
        {
            return close(file_mode);            
        });
    }

    void TextFileIO::setup(
        Result<void>& result,
        const std::string& file_path
    )
    {
        _file_path = file_path;

        result.set_to_success();
    }

    void TextFileIO::setup(
        Result<void>& result,
        const std::string& name,
        const std::string& file_path
    )
    {
        _name = name;
        _file_path = file_path;

        result.set_to_success();
    }
}
