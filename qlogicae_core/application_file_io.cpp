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
        set_is_enabled(true);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationFileIO::setup_async()
    {
        return std::async(
            std::launch::async,
            [this]() -> bool
            {
                return setup();
            }
        );
    }

    void ApplicationFileIO::setup_async(
        Result<std::future<void>>& result
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async,
                [this]() -> void
                {
                    Result<void> void_result;

                    setup(void_result);
                }
            )
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
