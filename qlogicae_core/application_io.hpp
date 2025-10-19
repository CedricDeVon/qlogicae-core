#pragma once

#include "result.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationIO :
        public AbstractApplication
    {
    public:
        bool setup();

        void setup(
            Result<void>& result
        );

        std::future<bool> setup_async();

        void setup_async(
            Result<std::future<void>>& result
        );

        static ApplicationIO& get_instance();

        static void get_instance(
            Result<ApplicationIO*>& result
        );

    protected:
        ApplicationIO();

        ~ApplicationIO();

        ApplicationIO(
            const ApplicationIO& instance
        ) = default;

        ApplicationIO(
            ApplicationIO&& instance
        ) noexcept = delete;

        ApplicationIO& operator = (
            ApplicationIO&& instance
        ) = default;

        ApplicationIO& operator = (
            const ApplicationIO& instance
        ) = delete;
    };

    inline static ApplicationIO& QLOGICAE_APPLICATION_IO =
        ApplicationIO::get_instance();
}
