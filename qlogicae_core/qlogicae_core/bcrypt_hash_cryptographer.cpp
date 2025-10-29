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
		try
		{
			Result<void> result;

			setup(result);

			return result.is_status_safe();
		}
		catch (const std::exception& exception)
		{
			LOGGER.handle_exception_async(
				"QLogicaeCore::BcryptHashCryptographer::setup()",
				exception.what()
			);

			return false;
		}
	}

    void BcryptHashCryptographer::setup(
        Result<void>& result
    )
    {        
        result.set_to_good_status_without_value();
    }

	std::future<bool> BcryptHashCryptographer::setup_async()
	{
		std::promise<bool> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this,
			promise = std::move(promise)]() mutable
			{
				promise.set_value(
					setup()
				);
			}
		);

		return future;
	}

	void BcryptHashCryptographer::setup_async(
		const std::function<void(const bool& result)>& callback
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback]() mutable
			{
				callback(
					setup()
				);
			}
		);
	}

	void BcryptHashCryptographer::setup_async(
		Result<std::future<void>>& result
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this,
			promise = std::move(promise)]() mutable
			{
				Result<void> result;

				setup(result);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void BcryptHashCryptographer::setup_async(
		const std::function<void(Result<void>& result)>& callback
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback]() mutable
			{
				Result<void> result;

				setup(result);

				callback(
					result
				);
			}
		);
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
			LOGGER.handle_exception_async(
				"QLogicaeCore::BcryptHashCryptographer::transform()",
				exception.what()
			);

			return "";
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
			LOGGER.handle_exception_async(
				"QLogicaeCore::BcryptHashCryptographer::reverse()",
				exception.what()
			);

			return false;
		}
	}

	std::future<bool> BcryptHashCryptographer::reverse_async(
		const std::string& va,
		const std::string& vb
	)
	{
		std::promise<bool> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, va, vb,
			promise = std::move(promise)]() mutable
			{
				promise.set_value(
					reverse(
						va,
						vb
					)
				);
			}
		);

		return future;
	}

	std::future<std::string> BcryptHashCryptographer::transform_async(
		const std::string& va
	)
	{
		std::promise<std::string> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, va,
			promise = std::move(promise)]() mutable
			{
				promise.set_value(
					transform(
						va
					)
				);
			}
		);

		return future;
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
		std::promise<std::string> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text,
			promise = std::move(promise)]() mutable
			{
				Result<std::string> result;

				transform(
					result,
					text
				);

				promise.set_value(
					result.get_value()
				);
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
    }

    void BcryptHashCryptographer::reverse_async(
        Result<std::future<bool>>& result,
        const std::string& hash,
        const std::string& key
	)
    {
		std::promise<bool> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, hash, key,
			promise = std::move(promise)]() mutable
			{
				Result<bool> result;

				reverse(
					result,
					hash,
					key
				);

				promise.set_value(
					result.get_value()
				);
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
    }
    
    void BcryptHashCryptographer::reverse_async(
        const std::function<void(const bool& result)>& callback,
        const std::string& hash,
        const std::string& key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, hash, key, callback]() mutable
            {
                callback(
                    reverse(
                        hash,
                        key
                    )
                );
            }
        );
    }

    void BcryptHashCryptographer::transform_async(
        const std::function<void(const std::string& result)>& callback,
        const std::string& text
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, text, callback]() mutable
            {
                callback(
                    transform(
                        text
                    )
                );
            }
        );
    }

    void BcryptHashCryptographer::reverse_async(
        const std::function<void(Result<bool>& result)>& callback,
        const std::string& hash,
        const std::string& key
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, hash, key, callback]() mutable
            {
                Result<bool> result;

                reverse(
                    result,
                    hash,
                    key
                );

                callback(
                    result
                );
            }
        );
    }

    void BcryptHashCryptographer::transform_async(
        const std::function<void(Result<std::string>& result)>& callback,
        const std::string& text
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, text, callback]() mutable
            {
                Result<std::string> result;

                transform(
                    result,
                    text
                );

                callback(
                    result
                );
            }
        );
    }

	BcryptHashCryptographer& BcryptHashCryptographer::get_instance()
	{
		static BcryptHashCryptographer instance;

		return instance;
	}

	void BcryptHashCryptographer::get_instance(
		QLogicaeCore::Result<BcryptHashCryptographer*>& result
	)
	{
		static BcryptHashCryptographer instance;

		result.set_to_good_status_with_value(&instance);
	}
}
