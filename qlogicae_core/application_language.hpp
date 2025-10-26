#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationLanguage :
        public AbstractApplication
    {
    public:
        bool setup();

        std::future<bool> setup_async(
            const std::function<void(const bool& result)>& callback =
            [](const bool& result) {}
        );

        void setup(
            Result<void>& result
        );

        void setup_async(
            Result<std::future<void>>& result,
            const std::function<void(Result<void>& result)>& callback =
            [](Result<void>& result) {}
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

