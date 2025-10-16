#include "pch.hpp"

#include "binary_file_io.hpp"

namespace QLogicaeCore
{
    BinaryFileIO::BinaryFileIO(
        const std::string& file_path
    ) :
            AbstractFileIO(file_path)
    {

    }

    BinaryFileIO::BinaryFileIO(
        const std::string& name,
        const std::string& file_path
    ) :
            AbstractFileIO(name, file_path)
    {

    }

    BinaryFileIO::~BinaryFileIO()
    {
        close(FileMode::READ);
        close(FileMode::WRITE);
        close(FileMode::APPEND);
    }

    bool BinaryFileIO::open(
        const FileMode& file_mode
    )
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
            throw std::runtime_error(
                std::string() +
                "Exception at BinaryFileIO::open(): " +
                exception.what()
            );
        }
    }

    bool BinaryFileIO::close(
        const FileMode& file_mode
    )
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
            throw std::runtime_error(
                std::string() +
                "Exception at BinaryFileIO::close(): " +
                exception.what()
            );
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
            throw std::runtime_error(
                std::string() +
                "Exception at BinaryFileIO::is_open(): " +
                exception.what()
            );
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
            throw std::runtime_error(
                std::string() +
                "Exception at BinaryFileIO::read(): " +
                exception.what()
            );
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
            throw std::runtime_error(
                std::string() +
                "Exception at BinaryFileIO::write(): " +
                exception.what()
            );
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
            throw std::runtime_error(
                std::string() +
                "Exception at BinaryFileIO::append(): " +
                exception.what()
            );
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



    void BinaryFileIO::open(
        Result<bool>& result,
        const FileMode& file_mode
    )
    {
        switch (file_mode)
        {
            case FileMode::READ:
            {
                if (!std::filesystem::exists(_file_path))
                {
                    return result.set_to_bad_status_without_value(
                        "File not found"
                    );
                }

                if (!_read_file)
                {
                    _read_file.emplace(_file_path);
                }

                return result.set_to_good_status_with_value(
                    true
                );
            }
            case FileMode::WRITE:
            {
                if (!_write_file)
                {
                    _write_file.emplace(_file_path);
                }

                return result.set_to_good_status_with_value(
                    true
                );
            }
            case FileMode::APPEND:
            {
                if (!_append_file)
                {
                    _append_file.emplace(
                        _file_path,
                        fast_io::open_mode::app
                    );
                }

                return result.set_to_good_status_with_value(
                    true
                );
            }
            default:
            {
                return result.set_to_bad_status_without_value(
                    "File open failed"
                );
            }
        }
    }

    void BinaryFileIO::close(
        Result<bool>& result,
        const FileMode& file_mode
    )
    {
        switch (file_mode)
        {
            case FileMode::READ:
            {
                if (_read_file)
                {
                    _read_file.reset();
                }

                return result.set_to_good_status_with_value(
                    true
                );
            }
            case FileMode::WRITE:
            {
                if (_write_file)
                {
                    _write_file.reset();
                }

                return result.set_to_good_status_with_value(
                    true
                );
            }
            case FileMode::APPEND:
            {
                if (_append_file)
                {
                    _append_file.reset();
                }

                return result.set_to_good_status_with_value(
                    true
                );
            }
            default:
            {
                return result.set_to_bad_status_without_value(
                    "File close failed"
                );
            }
        }
    }

    void BinaryFileIO::is_open(
        Result<bool>& result,
        const FileMode& file_mode
    )
    {
        switch (file_mode)
        {
            case FileMode::READ:
            {
                return result.set_to_good_status_with_value(
                    _read_file.has_value()
                );
            }
            case FileMode::WRITE:
            {
                return result.set_to_good_status_with_value(
                    _write_file.has_value()
                );
            }
            case FileMode::APPEND:
            {
                return result.set_to_good_status_with_value(
                    _append_file.has_value()
                );
            }
            default:
            {
                return result.set_to_bad_status_without_value(
                    "Invalid file mode"
                );
            }
        }
    }

    void BinaryFileIO::read(
        Result<std::vector<std::byte>>& result
    )
    {
        std::scoped_lock lock(_mutex);

        if (!open(FileMode::READ))
        {
            return result.set_to_bad_status_without_value(
                "File not open to read"
            );
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

        return result.set_to_good_status_with_value(
            content
        );
    }

    void BinaryFileIO::write(
        Result<bool>& result,
        const std::span<const std::byte>& content
    )
    {
        std::scoped_lock lock(_mutex);

        if (!open(FileMode::WRITE))
        {
            return result.set_to_bad_status_without_value(
                "File not open to write"
            );
        }

        fast_io::write(
            _write_file.value(),
            content.begin(),
            content.end()
        );

        close(FileMode::READ);
        close(FileMode::WRITE);
        close(FileMode::APPEND);

        result.set_to_good_status_with_value(
            true
        );
    }

    void BinaryFileIO::append(
        Result<bool>& result,
        const std::span<const std::byte>& content
    )
    {
        std::scoped_lock lock(_mutex);

        if (!open(FileMode::APPEND))
        {
            return result.set_to_bad_status_without_value(
                "File not open to write"
            );
        }

        fast_io::write(
            _append_file.value(),
            content.begin(),
            content.end()
        );

        close(FileMode::READ);
        close(FileMode::WRITE);
        close(FileMode::APPEND);

        result.set_to_good_status_with_value(
            true
        );
    }

    void BinaryFileIO::open_async(
        Result<std::future<bool>>& result,
        const FileMode& file_mode
    )
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async,
                [this, file_mode]() -> bool
                {
                    Result<bool> result;

                    open(
                        result,
                        file_mode
                    );

                    return result.get_value();
                })
        );
    }

    void BinaryFileIO::close_async(
        Result<std::future<bool>>& result,
        const FileMode& file_mode
    )
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async,
                [this, file_mode]() -> bool
                {
                    Result<bool> result;

                    close(
                        result,
                        file_mode
                    );

                    return result.get_value();
                })
        );
    }

    void BinaryFileIO::read_async(
        Result<std::future<std::vector<std::byte>>>& result
    )
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async,
                [this]() -> std::vector<std::byte>
                {
                    Result<std::vector<std::byte>> result;

                    read(result);

                    return result.get_value();
                })
        );
    }

    void BinaryFileIO::write_async(
        Result<std::future<bool>>& result,
        const std::span<const std::byte>& content
    )
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async,
                [this, content]() -> bool
                {
                    Result<bool> result;

                    write(
                        result,
                        content
                    );

                    return result.get_value();
                })
        );
    }

    void BinaryFileIO::append_async(
        Result<std::future<bool>>& result,
        const std::span<const std::byte>& content
    )
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async,
                [this, content]() -> bool
                {
                    Result<bool> result;

                    append(
                        result,
                        content
                    );

                    return result.get_value();
                })
        );
    }

    void BinaryFileIO::setup(
        Result<void>& result,
        const std::string& file_path
    )
    {
        _file_path = file_path;

        result.set_to_good_status_without_value();
    }

    void BinaryFileIO::setup(
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

