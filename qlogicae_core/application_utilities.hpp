#pragma once

#include "result.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationUtilities :
        AbstractApplication
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

        static ApplicationUtilities& get_instance();

        static void get_instance(
            Result<ApplicationUtilities*>& result
        );

    protected:
        ApplicationUtilities();

        ~ApplicationUtilities();

        ApplicationUtilities(
            const ApplicationUtilities& instance
        ) = default;

        ApplicationUtilities(
            ApplicationUtilities&& instance
        ) noexcept = delete;

        ApplicationUtilities& operator = (
            ApplicationUtilities&& instance
        ) = default;

        ApplicationUtilities& operator = (
            const ApplicationUtilities& instance
        ) = delete;
    };

    inline static ApplicationUtilities& QLOGICAE_APPLICATION_UTILITIES =
        ApplicationUtilities::get_instance();
}
