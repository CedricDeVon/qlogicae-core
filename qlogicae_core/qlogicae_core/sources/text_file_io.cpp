#include "pch.hpp"

#include "../includes/text_file_io.hpp"

namespace QLogicaeCore
{
    TextFileIO::TextFileIO() :
        AbstractFileIO()
    {
        
    }

    TextFileIO::~TextFileIO()
    {
        close(FileMode::READ);
        close(FileMode::WRITE);
        close(FileMode::APPEND);
    }

    TextFileIO::TextFileIO(
        const std::string& file_path
    ) :
        AbstractFileIO(
            file_path
        )
    {

    }

    TextFileIO::TextFileIO(
        const std::string& name,
        const std::string& file_path
    ) :
            AbstractFileIO(
                name,
                file_path
            )
    {

    }

    bool TextFileIO::setup(
        const std::string& file_path
    )
    {
        try
        {
            Result<void> result;

            setup(
                result,
                file_path
            );

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TextFileIO::setup()",
                exception.what()
            );

        }
    }

    void TextFileIO::setup(
        Result<void>& result,
        const std::string& file_path
    )
    {
        _file_path = file_path;

        result.set_to_good_status_without_value();
    }

    bool TextFileIO::setup(
        const std::string& name,
        const std::string& file_path
    )
    {
        try
        {
            Result<void> result;

            setup(result, name, file_path);

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TextFileIO::setup()",
                exception.what()
            );

            return false;
        }
    }

    void TextFileIO::setup(
        Result<void>& result,
        const std::string& name,
        const std::string& file_path
    )
    {
        _name = name;
        _file_path = file_path;

        result.set_to_good_status_without_value();
    }

    bool TextFileIO::open(
        const FileMode& file_mode
    )
    {
        try
        {
            Result<bool> result;

            open(
                result,
                file_mode
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TextFileIO::open()",
                exception.what()
            );

            return false;
        }
    }

    void TextFileIO::open(
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
                return result.set_to_bad_status_with_value(
                    false, "File not found"
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
            return result.set_to_bad_status_with_value(
                false, "File open failed"
            );
        }
        }
    }

    bool TextFileIO::close(
        const FileMode& file_mode
    )
    {
        try
        {
            Result<bool> result;

            close(
                result,
                file_mode
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TextFileIO::close()",
                exception.what()
            );

            return false;
        }
    }

    void TextFileIO::close(
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
                return result.set_to_bad_status_with_value(
                    false, "File close found"
                );
            }
        }
    }

    bool TextFileIO::is_open(
        const FileMode& file_mode
    )
    {
        try
        {
            Result<bool> result;

            is_open(
                result,
                file_mode
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TextFileIO::is_open()",
                exception.what()
            );

            return false;
        }
    }

    void TextFileIO::is_open(
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
            return result.set_to_bad_status_with_value(
                false, "Invalid file mode"
            );
        }
        }
    }

    std::string TextFileIO::read()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            Result<std::string> result;

            read(
                result
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TextFileIO::read()",
                exception.what()
            );

            return "";
        }
    }

    void TextFileIO::read(
        Result<std::string>& result
    )
    {
        if (!open(FileMode::READ))
        {
            return result.set_to_bad_status_without_value(
                "File not open to read"
            );
        }

        fast_io::native_file_loader& file_loader =
            _read_file.value();
        std::string content{
            file_loader.begin(),
            file_loader.end()
        };

        return result.set_to_good_status_with_value(
            content
        );
    }

    bool TextFileIO::write(
        const std::string& content
    )
    {
        try
        {
            std::scoped_lock lock(_mutex);

            Result<bool> result;

            write(
                result,
                content
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TextFileIO::write()",
                exception.what()
            );

            return false;
        }
    }

    void TextFileIO::write(
        Result<bool>& result,
        const std::string& content
    )
    {
        if (!open(FileMode::WRITE))
        {
            return result.set_to_bad_status_without_value(
                "File not open to write"
            );
        }

        fast_io::io::print(
            _write_file.value(),
            content
        );

        close(FileMode::READ);
        close(FileMode::WRITE);
        close(FileMode::APPEND);

        result.set_to_good_status_with_value(
            true
        );
    }

    bool TextFileIO::append(
        const std::string& content
    )
    {
        try
        {
            std::scoped_lock lock(_mutex);

            Result<bool> result;

            append(
                result,
                content
            );

            return result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception(
                "QLogicaeCore::TextFileIO::open()",
                exception.what()
            );

            return false;
        }
    }

    void TextFileIO::append(
        Result<bool>& result,
        const std::string& content
    )
    {
        if (!open(FileMode::APPEND))
        {
            return result.set_to_bad_status_without_value(
                "File not open to append"
            );
        }

        fast_io::io::print(
            _append_file.value(),
            content
        );

        close(FileMode::READ);
        close(FileMode::WRITE);
        close(FileMode::APPEND);

        result.set_to_good_status_with_value(
            true
        );
    }

    std::future<std::string> TextFileIO::read_async(
        const std::function<void(const std::string& result)>& callback
    )
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                std::string result = read();

                promise.set_value(
                    result
                );

                if (callback)
                {
                    callback(result);
                }
            }
        );

        return future;
    }

    void TextFileIO::read_async(
        Result<std::future<std::string>>& result,
        const std::function<void(Result<std::string>& result)>& callback
    )
    {
        std::promise<std::string> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                Result<std::string> result;

                read(result);

                promise.set_value(
                    result.get_value()
                );

                callback(result);
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    std::future<bool> TextFileIO::write_async(
        const std::string& content,
        const std::function<void(const bool& result)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, content, promise = std::move(promise)]() mutable
            {
                bool result = write(content);

                promise.set_value(
                    result
                );

                if (callback)
                {
                    callback(result);
                }
            }
        );

        return future;
    }

    void TextFileIO::write_async(
        Result<std::future<bool>>& result,
        const std::string& content,
        const std::function<void(Result<bool>& result)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, content, promise = std::move(promise)]() mutable
            {
                Result<bool> result;

                write(result, content);

                promise.set_value(
                    result.get_value()
                );

                callback(result);
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    std::future<bool> TextFileIO::append_async(
        const std::string& content,
        const std::function<void(const bool& result)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, content, promise = std::move(promise)]() mutable
            {
                bool result = append(content);

                promise.set_value(
                    result
                );

                if (callback)
                {
                    callback(result);
                }
            }
        );

        return future;
    }

    void TextFileIO::append_async(
        Result<std::future<bool>>& result,
        const std::string& content,
        const std::function<void(Result<bool>& result)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, content, promise = std::move(promise)]() mutable
            {
                Result<bool> result;

                append(result, content);

                promise.set_value(
                    result.get_value()
                );

                callback(result);
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    std::future<bool> TextFileIO::open_async(
        const FileMode& file_mode,
        const std::function<void(const bool& result)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, file_mode, promise = std::move(promise)]() mutable
            {
                bool result = open(file_mode);

                promise.set_value(
                    result
                );

                if (callback)
                {
                    callback(result);
                }
            }
        );

        return future;
    }

    void TextFileIO::open_async(
        Result<std::future<bool>>& result,
        const FileMode& file_mode,
        const std::function<void(Result<bool>& result)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, file_mode, promise = std::move(promise)]() mutable
            {
                Result<bool> result;

                open(result, file_mode);

                promise.set_value(
                    result.get_value()
                );

                callback(result);
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    std::future<bool> TextFileIO::close_async(
        const FileMode& file_mode,
        const std::function<void(const bool& result)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, file_mode, promise = std::move(promise)]() mutable
            {
                bool result = close(file_mode);

                promise.set_value(
                    result
                );

                if (callback)
                {
                    callback(result);
                }
            }
        );

        return future;
    }

    void TextFileIO::close_async(
        Result<std::future<bool>>& result,
        const FileMode& file_mode,
        const std::function<void(Result<bool>& result)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, file_mode, promise = std::move(promise)]() mutable
            {
                Result<bool> result;

                close(result, file_mode);

                promise.set_value(
                    result.get_value()
                );

                callback(result);
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    TextFileIO& TextFileIO::get_instance()
    {
        static TextFileIO instance;

        return instance;
    }

    void TextFileIO::get_instance(
        Result<TextFileIO*>& result
    )
    {
        static TextFileIO instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}

