#include "pch.hpp"

#include "application_cryptographer.hpp"

namespace QLogicaeCore
{
    ApplicationCryptographer::ApplicationCryptographer() :
        AbstractApplication()
    {

    }

    ApplicationCryptographer::~ApplicationCryptographer()
    {

    }

    bool ApplicationCryptographer::setup()
    {
        Result<void> void_result;

        setup(void_result);

        return void_result.is_status_safe();
    }

    void ApplicationCryptographer::setup(
        Result<void>& result
    )
    {
        if (_is_enabled)
        {
            return result.set_to_bad_status_without_value();
        }

        AES256_CIPHER_CRYPTOGRAPHER.setup(
            result
        );
        if (result.is_status_unsafe())
        {
            return result.set_to_bad_status_without_value();
        }

        AES256_SIGNATURE_CRYPTOGRAPHER.setup(
            result
        );
        if (result.is_status_unsafe())
        {
            return result.set_to_bad_status_without_value();
        }

        ARGON2ID_HASH_CRYPTOGRAPHER.setup(
            result
        );
        if (result.is_status_unsafe())
        {
            return result.set_to_bad_status_without_value();
        }

        BCRYPT_HASH_CRYPTOGRAPHER.setup(
            result
        );
        if (result.is_status_unsafe())
        {
            return result.set_to_bad_status_without_value();
        }

        SHA256_HASH_CRYPTOGRAPHER.setup(
            result
        );
        if (result.is_status_unsafe())
        {
            return result.set_to_bad_status_without_value();
        }

        XCHACHA20_POLY1305_CIPHER_CRYPTOGRAPHER.setup(
            result
        );
        if (result.is_status_unsafe())
        {
            return result.set_to_bad_status_without_value();
        }

        JSONWEBTOKEN_SIGNATURE_CRYPTOGRAPHER.setup(
            result
        );
        if (result.is_status_unsafe())
        {
            return result.set_to_bad_status_without_value();
        }

        set_is_enabled(true);

        result.set_to_good_status_without_value();
    }

    std::future<bool> ApplicationCryptographer::setup_async()
    {
        return std::async(
            std::launch::async,
            [this]() -> bool
            {
                return setup();
            }
        );
    }

    void ApplicationCryptographer::setup_async(
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

    ApplicationCryptographer& ApplicationCryptographer::get_instance()
    {
        static ApplicationCryptographer instance;

        return instance;
    }

    void ApplicationCryptographer::get_instance(
        Result<ApplicationCryptographer*>& result
    )
    {
        static ApplicationCryptographer instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}
