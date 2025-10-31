#include "pch.hpp"

#include "windows_registry_value_extractor.hpp"

namespace QLogicaeCore
{
    WindowsRegistryValueExtractor::WindowsRegistryValueExtractor()
    {

    }

    WindowsRegistryValueExtractor::~WindowsRegistryValueExtractor()
    {

    }

    WindowsRegistryValueExtractor::WindowsRegistryValueExtractor(
        const std::string& sub_key,
        const std::string& name_key
    ) :
            _sub_key(sub_key),
            _name_key(name_key)
    {

    }

    WindowsRegistryValueExtractor::WindowsRegistryValueExtractor(
        const std::wstring& sub_key,
        const std::wstring& name_key
    ) :
            _sub_key(
                ENCODER.from_utf16_to_utf8(sub_key)
            ),
            _name_key(
                ENCODER.from_utf16_to_utf8(name_key)
            )
    {

    }

    bool WindowsRegistryValueExtractor::setup()
    {
        try
        {
            Result<void> void_result;

            setup(
                void_result
            );

            return void_result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::WindowsRegistryValueExtractor::setup()",
                exception.what()
            );

            return false;
        }
    }

    void WindowsRegistryValueExtractor::setup(
        Result<void>& result
    )
    {
        _sub_key = "";
        _name_key = "";

        result.set_to_good_status_without_value();
    }

    std::future<bool> WindowsRegistryValueExtractor::setup_async()
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    setup()
                );
            }
        );

        return future;
    }

    void WindowsRegistryValueExtractor::setup_async(
        Result<std::future<void>>& result
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(
                    result
                );

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void WindowsRegistryValueExtractor::setup_async(
        const std::function<void(const bool& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                callback(
                    setup()
                );
            }
        );
    }

    void WindowsRegistryValueExtractor::setup_async(
        const std::function<void(Result<void>& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                Result<void> result;

                setup(
                    result
                );

                callback(
                    result
                );
            }
        );
    }

    bool WindowsRegistryValueExtractor::setup(
        const std::string& sub_key,
        const std::string& name_key
    )
    {
        try
        {
            Result<void> void_result;

            setup(
                void_result,
                sub_key,
                name_key
            );

            return void_result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::WindowsRegistryValueExtractor::setup()",
                exception.what()
            );

            return false;
        }
    }

    bool WindowsRegistryValueExtractor::setup(
        const std::wstring& sub_key,
        const std::wstring& name_key
    )
    {
        try
        {
            Result<void> void_result;

            setup(
                void_result,
                sub_key,
                name_key
            );

            return void_result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::WindowsRegistryValueExtractor::setup()",
                exception.what()
            );

            return false;
        }
    }

    std::future<bool> WindowsRegistryValueExtractor::setup_async(
        const std::string& sub_key,
        const std::string& name_key
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, sub_key, name_key,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    setup(
                        sub_key,
                        name_key
                    )
                );
            }
        );

        return future;
    }

    std::future<bool> WindowsRegistryValueExtractor::setup_async(
        const std::wstring& sub_key,
        const std::wstring& name_key
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, sub_key, name_key,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    setup(
                        sub_key,
                        name_key
                    )
                );
            }
        );

        return future;
    }

    void WindowsRegistryValueExtractor::setup_async(
        Result<std::future<void>>& result,
        const std::string& sub_key,
        const std::string& name_key
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, sub_key, name_key,
            promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(
                    result,
                    sub_key,
                    name_key
                );

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void WindowsRegistryValueExtractor::setup_async(
        Result<std::future<void>>& result,
        const std::wstring& sub_key,
        const std::wstring& name_key
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, sub_key, name_key,
            promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(
                    result,
                    sub_key,
                    name_key
                );

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void WindowsRegistryValueExtractor::setup_async(
        const std::function<void(const bool& result)>& callback,
        const std::string& sub_key,
        const std::string& name_key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, sub_key, name_key]() mutable
            {
                callback(
                    setup(
                        sub_key,
                        name_key
                    )
                );
            }
        );
    }

    void WindowsRegistryValueExtractor::setup_async(
        const std::function<void(const bool& result)>& callback,
        const std::wstring& sub_key,
        const std::wstring& name_key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, sub_key, name_key]() mutable
            {
                callback(
                    setup(
                        sub_key,
                        name_key
                    )
                );
            }
        );
    }

    void WindowsRegistryValueExtractor::setup_async(
        const std::function<void(Result<void>& result)>& callback,
        const std::string& sub_key,
        const std::string& name_key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, sub_key, name_key]() mutable
            {
                Result<void> result;

                setup(
                    result,
                    sub_key,
                    name_key
                );

                callback(
                    result
                );
            }
        );
    }

    void WindowsRegistryValueExtractor::setup_async(
        const std::function<void(Result<void>& result)>& callback,
        const std::wstring& sub_key,
        const std::wstring& name_key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, sub_key, name_key]() mutable
            {
                Result<void> result;

                setup(
                    result,
                    sub_key,
                    name_key
                );

                callback(
                    result
                );
            }
        );
    }

    std::optional<std::string>
        WindowsRegistryValueExtractor::get_sub_key()
    {
        Result<std::string> string_result;

        get_sub_key(
            string_result
        );

        return string_result.get_value();
    }

    std::optional<std::string>
        WindowsRegistryValueExtractor::get_name_key()
    {
        Result<std::string> string_result;

        get_name_key(
            string_result
        );

        return string_result.get_value();
    }

    std::optional<std::string>
        WindowsRegistryValueExtractor::get_value()
    {
        try
        {
            Result<std::string> string_result;

            get_value(
                string_result
            );

            return string_result.get_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::WindowsRegistryValueExtractor::get_value()",
                exception.what()
            );

            throw std::runtime_error(std::string("WindowsRegistryValueExtractor::get_value() - ") + exception.what());
        }
    }

    void WindowsRegistryValueExtractor::setup(
        Result<void>& result,
        const std::string& sub_key,
        const std::string& name_key
    )
    {
        _sub_key = sub_key;
        _name_key = name_key;

        result.set_to_good_status_without_value();
    }

    void WindowsRegistryValueExtractor::setup(
        Result<void>& result,
        const std::wstring& sub_key,
        const std::wstring& name_key
    )
    {
        Result<std::string> string_result;
        ENCODER.from_utf16_to_utf8(string_result, sub_key);
        _sub_key = string_result.get_value();

        ENCODER.from_utf16_to_utf8(string_result, name_key);
        _name_key = string_result.get_value();

        result.set_to_good_status_without_value();
    }

    void WindowsRegistryValueExtractor::get_sub_key(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(_sub_key);
    }

    void WindowsRegistryValueExtractor::get_name_key(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(_name_key);
    }

    void WindowsRegistryValueExtractor::get_value(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(WindowsRegistry::hkcu()
            .get_value_via_utf8(_sub_key, _name_key).value()
        );        
    }

    WindowsRegistryValueExtractor& WindowsRegistryValueExtractor::get_instance()
    {
        static WindowsRegistryValueExtractor instance;

        return instance;
    }

    void WindowsRegistryValueExtractor::get_instance(
        QLogicaeCore::Result<WindowsRegistryValueExtractor*>& result
    )
    {
        static WindowsRegistryValueExtractor instance;

        result.set_to_good_status_with_value(&instance);
    }
}
