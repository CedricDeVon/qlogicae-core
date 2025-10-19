#pragma once

#include "result.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationCryptographer :
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

        static ApplicationCryptographer& get_instance();

        static void get_instance(
            Result<ApplicationCryptographer*>& result
        );

    protected:
        ApplicationCryptographer();

        ~ApplicationCryptographer();

        ApplicationCryptographer(
            const ApplicationCryptographer& instance
        ) = default;

        ApplicationCryptographer(
            ApplicationCryptographer&& instance
        ) noexcept = delete;

        ApplicationCryptographer& operator = (
            ApplicationCryptographer&& instance
        ) = default;

        ApplicationCryptographer& operator = (
            const ApplicationCryptographer& instance
        ) = delete;
    };

    inline static ApplicationCryptographer& QLOGICAE_APPLICATION_CRYPTOGRAPHER =
        ApplicationCryptographer::get_instance();    
}
