#pragma once

#include "result.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationLanguage :
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

        static ApplicationLanguage& get_instance();

        static void get_instance(
            Result<ApplicationLanguage*>& result
        );

    protected:
        ApplicationLanguage();

        ~ApplicationLanguage();

        ApplicationLanguage(
            const ApplicationLanguage& instance
        ) = default;

        ApplicationLanguage(
            ApplicationLanguage&& instance
        ) noexcept = delete;

        ApplicationLanguage& operator = (
            ApplicationLanguage&& instance
        ) = default;

        ApplicationLanguage& operator = (
            const ApplicationLanguage& instance
        ) = delete;
    };

    inline static ApplicationLanguage& QLOGICAE_APPLICATION_LANGUAGE =
        ApplicationLanguage::get_instance();
}

