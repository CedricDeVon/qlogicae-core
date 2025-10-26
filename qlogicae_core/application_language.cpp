#include "pch.hpp"

#include "utilities.hpp"
#include "application_language.hpp"

namespace QLogicaeCore
{
    ApplicationLanguage::ApplicationLanguage() :
        AbstractApplication()
    {

    }

    ApplicationLanguage::~ApplicationLanguage()
    {

    }

    bool ApplicationLanguage::setup()
    {
        Result<void> void_result;

        setup(void_result);

        return void_result.is_status_safe();
    }

    void ApplicationLanguage::setup(
        Result<void>& result
    )
    {
        try
        {
            if (_is_enabled)
            {
                LOGGER.handle_exception_async(
                    "QLogicaeCore::ApplicationCryptographer::setup()",
                    "Can only be called once"
                );

                return result.set_to_bad_status_without_value(
                    "QLogicaeCore::ApplicationLanguage::setup() - Can only be called once"
                );
            }

            set_is_enabled(true);

            result.set_to_good_status_without_value();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::ApplicationCryptographer::setup()",
                exception.what()
            );

            result.set_to_bad_status_without_value(
                std::string("QLogicaeCore::ApplicationLanguage::setup() - ") +
                exception.what()
            );
        }
    }

    std::future<bool> ApplicationLanguage::setup_async(
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

    void ApplicationLanguage::setup_async(
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

    ApplicationLanguage& ApplicationLanguage::get_instance()
    {
        static ApplicationLanguage instance;

        return instance;
    }

    void ApplicationLanguage::get_instance(
        Result<ApplicationLanguage*>& result
    )
    {
        static ApplicationLanguage instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}
