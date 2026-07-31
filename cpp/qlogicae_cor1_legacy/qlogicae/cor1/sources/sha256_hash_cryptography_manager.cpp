#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Sha256HashCryptographyManager \
	)

#include "../includes/sha256_hash_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    Sha256HashCryptographyManager
		::Sha256HashCryptographyManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<Sha256HashCryptographyManagerConfigurations>()
	{

	}

	std::string
		Sha256HashCryptographyManager
			::hash_text(
				const std::string&
					text
			)
	{
		try
        {				
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				text,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				text.empty()
			);

			unsigned char
				hash[crypto_hash_sha256_BYTES];

			crypto_hash_sha256(
				hash,
				reinterpret_cast<const unsigned char*>(text.data()),
				static_cast<unsigned long long>(text.size())
			);

			std::string
				hex(
					crypto_hash_sha256_BYTES * 2,
					'\0'
				);

			sodium_bin2hex(
				hex.data(),
				hex.size() + 1,
				hash,
				crypto_hash_sha256_BYTES
			);

			return
				hex;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				text
			);
        }
	}

	bool
		Sha256HashCryptographyManager
			::verify_text(
				const std::string&
					text,
				const std::string&
					hash
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				text.empty() ||
				hash.empty()
			);		

			const std::string computed_hash = hash_text(text);

			if (computed_hash.empty())
				return false;

			return
				computed_hash == hash;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}
		
	bool
		Sha256HashCryptographyManager
			::hash_text(
				std::vector<uint8_t>&
					text
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!text.size()
			);			
			
			unsigned char
				hash[
					crypto_hash_sha256_BYTES
				];

			crypto_hash_sha256(
				hash,
				reinterpret_cast<const unsigned char*>(
					text.data()
				),
				static_cast<unsigned long long>(
					text.size()
				)
			);

			std::vector<uint8_t>
				hex(
					(crypto_hash_sha256_BYTES * 2) + 1,
					0
				);

			sodium_bin2hex(
				reinterpret_cast<char*>(
					hex.data()
				),
				hex.size(),
				hash,
				crypto_hash_sha256_BYTES
			);

			hex.resize(
				std::strlen(
					reinterpret_cast<const char*>(
						hex.data()
					)
				)
			);

			text =
				std::move(
					hex
				);

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		Sha256HashCryptographyManager
			::verify_text(
				const std::vector<uint8_t>&
					text,
				const std::vector<uint8_t>&
					hash
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!text.size() ||
				!hash.size()
			);			

			unsigned char
				computed_hash[
					crypto_hash_sha256_BYTES
				];

			crypto_hash_sha256(
				computed_hash,
				reinterpret_cast<const unsigned char*>(
					text.data()
				),
				static_cast<unsigned long long>(
					text.size()
				)
			);

			std::vector<uint8_t>
				computed_hex(
					(crypto_hash_sha256_BYTES * 2) + 1,
					0
				);

			sodium_bin2hex(
				reinterpret_cast<char*>(
					computed_hex.data()
				),
				computed_hex.size(),
				computed_hash,
				crypto_hash_sha256_BYTES
			);

			computed_hex.resize(
				std::strlen(
					reinterpret_cast<const char*>(
						computed_hex.data()
					)
				)
			);

			return
				computed_hex ==
				hash;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}
}

#endif
