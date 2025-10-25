#pragma once

#include "result.hpp"
#include "encoder.hpp"
#include "cryptographer.hpp"

namespace QLogicaeCore
{
    class AES256SignatureCryptographer :
        public Cryptographer
    {
    public:
        AES256SignatureCryptographer();

        ~AES256SignatureCryptographer();

        AES256SignatureCryptographer(
            const AES256SignatureCryptographer&
                instance
        ) = delete;

        AES256SignatureCryptographer(
            AES256SignatureCryptographer&&
                instance
        ) noexcept = delete;

        AES256SignatureCryptographer& operator = (
            AES256SignatureCryptographer&&
                instance
        ) = delete;

        AES256SignatureCryptographer& operator = (
            const AES256SignatureCryptographer&
                instance
        ) = delete;

        bool setup();

        void setup(
            Result<void>& result
        );
        
        std::future<bool> setup_async();

        void setup_async(
            const std::function<void(const bool& result)>& callback
        );

        void setup_async(
            Result<std::future<void>>& result
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback
        );

        std::string reverse(
            const std::string& cipher,
            unsigned char* public_key
        );

        std::string reverse(
            const std::string& cipher,
            const std::string& public_key
        );

        std::string transform(
            const std::string& text,
            unsigned char* public_key,
            unsigned char* private_key
        );

        std::string transform(
            const std::string& text,
            const std::string& public_key,
            const std::string& private_key
        );

        std::future<std::string> reverse_async(
            const std::string& cipher,
            unsigned char* public_key
        );

        std::future<std::string> reverse_async(
            const std::string& cipher,
            const std::string& public_key
        );

        std::future<std::string> transform_async(
            const std::string& text,
            unsigned char* public_key,
            unsigned char* private_key
        );

        std::future<std::string> transform_async(
            const std::string& text,
            const std::string& public_key,
            const std::string& private_key
        );

        void reverse_async(
            const std::function<void(const std::string& result)>& callback,
            const std::string& cipher,
            unsigned char* public_key
        );

        void transform_async(
            const std::function<void(const std::string& result)>& callback,
            const std::string& text,
            unsigned char* public_key,
            unsigned char* private_key
        );

        void reverse_async(
            const std::function<void(const std::string& result)>& callback,
            const std::string& cipher,
            const std::string& public_key
        );

        void transform_async(
            const std::function<void(const std::string& result)>& callback,
            const std::string& text,
            const std::string& public_key,
            const std::string& private_key
        );

        void reverse_async(
            const std::function<void(Result<std::string>& result)>& callback,
            const std::string& cipher,
            unsigned char* public_key
        );

        void transform_async(
            const std::function<void(Result<std::string>& result)>& callback,
            const std::string& text,
            unsigned char* public_key,
            unsigned char* private_key
        );

        void reverse_async(
            const std::function<void(Result<std::string>& result)>& callback,
            const std::string& cipher,
            const std::string& public_key
        );

        void transform_async(
            const std::function<void(Result<std::string>& result)>& callback,
            const std::string& text,
            const std::string& public_key,
            const std::string& private_key
        );

        void reverse(
            Result<std::string>& result,
            const std::string& cipher,
            unsigned char* public_key
        );

        void reverse(
            Result<std::string>& result,
            const std::string& cipher,
            const std::string& public_key
        );

        void transform(
            Result<std::string>& result,
            const std::string& text,
            unsigned char* public_key,
            unsigned char* private_key
        );

        void transform(
            Result<std::string>& result,
            const std::string& text,
            const std::string& public_key,
            const std::string& private_key
        );

        void reverse_async(
            Result<std::future<std::string>>& result,
            const std::string& cipher,
            unsigned char* public_key
        );

        void reverse_async(
            Result<std::future<std::string>>& result,
            const std::string& cipher,
            const std::string& public_key
        );

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string& text,
            unsigned char* public_key,
            unsigned char* private_key
        );

        void transform_async(
            Result<std::future<std::string>>& result,
            const std::string& text,
            const std::string& public_key,
            const std::string& private_key
        );

        static AES256SignatureCryptographer& get_instance();

        static void get_instance(
            Result<AES256SignatureCryptographer*>& result
        );
    };

    inline static AES256SignatureCryptographer& AES256_SIGNATURE_CRYPTOGRAPHER =
        AES256SignatureCryptographer::get_instance();
}
