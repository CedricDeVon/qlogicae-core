#include "pch.hpp"

#include "bcrypt_hash_cryptographer.hpp"

namespace QLogicaeCore
{
	BcryptHashCryptographer::BcryptHashCryptographer() :
		Cryptographer()
	{
		
	}

	std::string BcryptHashCryptographer::transform(
		const std::string& va) const
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
			throw std::runtime_error(std::string() + "Exception at BcryptHashCryptographer::transform(): " + exception.what());
		}
	}

	bool BcryptHashCryptographer::reverse(
		const std::string& va, const std::string& vb) const
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
			throw std::runtime_error(std::string() + "Exception at BcryptHashCryptographer::reverse(): " + exception.what());
		}
	}

	std::future<bool> BcryptHashCryptographer::reverse_async(
		const std::string& va,
		const std::string& vb) const
	{
		return std::async(std::launch::async, [this, va, vb]() -> bool
			{
				return reverse(va, vb);
			});
	}

	std::future<std::string> BcryptHashCryptographer::transform_async(
		const std::string& va) const
	{
		return std::async(std::launch::async, [this, va]() -> std::string
			{
				return transform(va);
			});
	}


    void BcryptHashCryptographer::transform(
        Result<std::string>& result,
        const std::string& text) const
    {
        std::string hash;
        hash.resize(crypto_pwhash_STRBYTES);

        bool is_successful = crypto_pwhash_str(
            hash.data(),
            text.c_str(),
            text.size(),
            crypto_pwhash_OPSLIMIT_MODERATE,
            crypto_pwhash_MEMLIMIT_MODERATE
        ) == 0;

        if (is_successful)
        {
            result.set_to_success(hash.c_str());
        }
        else
        {
            result.set_to_failure("");
        }
    }

    void BcryptHashCryptographer::reverse(
        Result<bool>& result,
        const std::string& hash,
        const std::string& key) const
    {
        bool verified = crypto_pwhash_str_verify(
            key.c_str(),
            hash.c_str(),
            hash.size()
        ) == 0;

        if (verified)
        {
            result.set_to_success(true);
        }
        else
        {
            result.set_to_failure(false);
        }
    }

    void BcryptHashCryptographer::transform_async(
        Result<std::future<std::string>>& result,
        const std::string& text) const
    {
        result.set_to_success(std::async(std::launch::async, [this, text]() -> std::string
            {
                std::string hash;
                hash.resize(crypto_pwhash_STRBYTES);

                bool is_successful = crypto_pwhash_str(
                    hash.data(),
                    text.c_str(),
                    text.size(),
                    crypto_pwhash_OPSLIMIT_MODERATE,
                    crypto_pwhash_MEMLIMIT_MODERATE
                ) == 0;

                if (is_successful)
                {
                    return hash.c_str();
                }

                return "";
            }));
    }

    void BcryptHashCryptographer::reverse_async(
        Result<std::future<bool>>& result,
        const std::string& hash,
        const std::string& key) const
    {
        result.set_to_success(std::async(std::launch::async, [this, hash, key]() -> bool
            {
                return crypto_pwhash_str_verify(
                    key.c_str(),
                    hash.c_str(),
                    hash.size()
                ) == 0;
            }));
    }
}
