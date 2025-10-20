#include "pch.hpp"

#include "bcrypt_hash_cryptographer.hpp"

namespace QLogicaeCore
{
	BcryptHashCryptographer::BcryptHashCryptographer() :
		Cryptographer()
	{
		
	}

	bool BcryptHashCryptographer::setup()
	{
		Result<void> result;

		setup(result);

		return result.is_status_safe();
	}

    void BcryptHashCryptographer::setup(
        Result<void>& result
    )
    {        
        result.set_to_good_status_without_value();
    }

	std::string BcryptHashCryptographer::transform(
		const std::string& va
	)
	{
		try
		{
			std::string hash;
			hash.resize(crypto_pwhash_STRBYTES);

			bool is_successful = crypto_pwhash_str(
				hash.data(),
				va.c_str(), va.size(),
				crypto_pwhash_OPSLIMIT_MODERATE,
				crypto_pwhash_MEMLIMIT_MODERATE) != 0;
		
			return hash.c_str();
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string() +
				"Exception at BcryptHashCryptographer::transform(): " +
				exception.what()
			);
		}
	}

	bool BcryptHashCryptographer::reverse(
		const std::string& va,
		const std::string& vb
	)
	{
		try
		{
			return crypto_pwhash_str_verify(
				vb.c_str(),
				va.c_str(),
				va.size()
			) == 0;
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string() +
				"Exception at BcryptHashCryptographer::reverse(): " +
				exception.what()
			);
		}
	}

	std::future<bool> BcryptHashCryptographer::reverse_async(
		const std::string& va,
		const std::string& vb
	)
	{
		return std::async(std::launch::async, [this, va, vb]() -> bool
			{
				return reverse(va, vb);
			});
	}

	std::future<std::string> BcryptHashCryptographer::transform_async(
		const std::string& va
	)
	{
		return std::async(
			std::launch::async,
			[this, va]() -> std::string
			{
				return transform(va);
			}
		);
	}


    void BcryptHashCryptographer::transform(
        Result<std::string>& result,
        const std::string& text
	)
    {
		std::scoped_lock lock(_mutex);

        std::string hash;
        hash.resize(crypto_pwhash_STRBYTES);

        bool is_successful = crypto_pwhash_str(
            hash.data(),
            text.c_str(),
            text.size(),
            crypto_pwhash_OPSLIMIT_MODERATE,
            crypto_pwhash_MEMLIMIT_MODERATE
        ) == 0;

        result.set_to_good_status_with_value(
			(is_successful) ? hash.c_str() : ""
		);
    }

    void BcryptHashCryptographer::reverse(
        Result<bool>& result,
        const std::string& hash,
        const std::string& key
	)
    {
		std::scoped_lock lock(_mutex);

        bool verified = crypto_pwhash_str_verify(
            key.c_str(),
            hash.c_str(),
            hash.size()
        ) == 0;

        result.set_to_good_status_with_value(verified);
    }

    void BcryptHashCryptographer::transform_async(
        Result<std::future<std::string>>& result,
        const std::string& text
	)
    {
        result.set_to_good_status_with_value(
			std::async(
				std::launch::async,
				[this, text]() -> std::string
            {
                Result<std::string> result;

                transform(result, text);

                return result.get_value();
            })
        );
    }

    void BcryptHashCryptographer::reverse_async(
        Result<std::future<bool>>& result,
        const std::string& hash,
        const std::string& key
	)
    {
        result.set_to_good_status_with_value(
			std::async(
				std::launch::async,
				[this, hash, key]() -> bool
            {
                Result<bool> result;

                reverse(result, hash, key);

                return result.get_value();
            })
        );
    }
}
