#include "pch.hpp"

#include "application_file_io.hpp"

namespace QLogicaeCore
{
    ApplicationFileIO::ApplicationFileIO() :
        AbstractApplication()
    {

    }

    ApplicationFileIO::~ApplicationFileIO()
    {

    }

    bool ApplicationFileIO::setup()
    {
        Result<void> void_result;

        setup(void_result);

        return void_result.is_status_safe();
    }

    void ApplicationFileIO::setup(
        Result<void>& result
    )
    {
        try
        {
            if (_is_enabled)
            {
                return result.set_to_bad_status_without_value(
                    "Exception at ApplicationFileIO::setup() - Can only be called once"
                );
            }

            set_is_enabled(true);

            result.set_to_good_status_without_value();
        }
        catch (const std::exception& exception)
        {
            result.set_to_bad_status_without_value(
                std::string("Exception at ApplicationFileIO::setup() - ") +
                exception.what()
            );
        }
    }

    std::future<bool> ApplicationFileIO::setup_async(
        const std::function<void(const bool& value)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                bool value = setup();

                promise.set_value(
                    value
                );

                if (callback)
                {
                    callback(
                        value
                    );
                }
            }
        );

        return future;
    }

    void ApplicationFileIO::setup_async(
        Result<std::future<void>>& result,
        const std::function<void(Result<void>& result)>& callback
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(result);

                promise.set_value();

                callback(
                    result
                );
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }


    ApplicationFileIO& ApplicationFileIO::get_instance()
    {
        static ApplicationFileIO instance;

        return instance;
    }

    void ApplicationFileIO::get_instance(
        Result<ApplicationFileIO*>& result
    )
    {
        static ApplicationFileIO instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}
