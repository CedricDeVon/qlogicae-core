#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Aes256CipherCryptographyManager \
	)

#include "../includes/aes256_cipher_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    Aes256CipherCryptographyManager
		::Aes256CipherCryptographyManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<Aes256CipherCryptographyManagerConfigurations>()
	{
		
	}

	std::string
		Aes256CipherCryptographyManager
			::encrypt_text(
				const std::string&
					text,
				const std::string&
					private_key,
				const std::string&
					nonce
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				text,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				text.empty() ||
				private_key.empty() ||
				nonce.empty()
			);		

			std::vector<unsigned char>
				ciphertext(
					text.size() +
					crypto_aead_aes256gcm_ABYTES
				);

			unsigned long long
				ciphertext_length =
					0;

			if (
				crypto_aead_aes256gcm_encrypt(
					ciphertext.data(),
					&ciphertext_length,
					reinterpret_cast<const unsigned char*>(text.data()),
					static_cast<unsigned long long>(text.size()),
					nullptr,
					0,
					nullptr,
					reinterpret_cast<const unsigned char*>(nonce.data()),
					reinterpret_cast<const unsigned char*>(private_key.data())
				) != 0
			)
			{
				return
					text;
			}

			std::string
				encoded(
					sodium_base64_ENCODED_LEN(
						static_cast<size_t>(ciphertext_length),
						sodium_base64_VARIANT_ORIGINAL
					),
					'\0'
				);

			sodium_bin2base64(
				encoded.data(),
				encoded.size(),
				ciphertext.data(),
				static_cast<size_t>(ciphertext_length),
				sodium_base64_VARIANT_ORIGINAL
			);

			encoded.resize(std::strlen(encoded.c_str()));

			return
				encoded;
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

	std::string
		Aes256CipherCryptographyManager
			::decrypt_text(
				const std::string&
					text,
				const std::string&
					private_key,
				const std::string&
					nonce
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				text,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				text.empty() ||
				private_key.empty() ||
				nonce.empty()
			);			

			std::vector<unsigned char>
				decoded(text.size());

			size_t
				decoded_length =
					0;

			if (
				sodium_base642bin(
					decoded.data(),
					decoded.size(),
					text.c_str(),
					text.size(),
					nullptr,
					&decoded_length,
					nullptr,
					sodium_base64_VARIANT_ORIGINAL
				) != 0
			)
			{
				return
					text;
			}

			if (decoded_length < crypto_aead_aes256gcm_ABYTES)
			{
				return
					text;
			}

			std::vector<unsigned char>
				plaintext(
					decoded_length -
					crypto_aead_aes256gcm_ABYTES
				);

			unsigned long long
				plaintext_length =
					0;

			if (
				crypto_aead_aes256gcm_decrypt(
					plaintext.data(),
					&plaintext_length,
					nullptr,
					decoded.data(),
					decoded_length,
					nullptr,
					0,
					reinterpret_cast<const unsigned char*>(nonce.data()),
					reinterpret_cast<const unsigned char*>(private_key.data())
				) != 0
			)
			{
				return
					text;
			}

			return std::string(
				reinterpret_cast<const char*>(plaintext.data()),
				static_cast<size_t>(plaintext_length)
			);
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
		Aes256CipherCryptographyManager
			::encrypt_text(
				std::vector<uint8_t>&
					text,
				const std::vector<uint8_t>&
					private_key,
				const std::vector<uint8_t>&
					nonce
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!text.size() ||
				!private_key.size() ||
				!nonce.size() ||
				private_key.size() !=
				crypto_aead_aes256gcm_KEYBYTES ||
				nonce.size() !=
				crypto_aead_aes256gcm_NPUBBYTES
			);			
			
			std::vector<uint8_t>
				ciphertext(
					text.size() +
					crypto_aead_aes256gcm_ABYTES
				);

			unsigned long long
				ciphertext_length =
					0;

			if
			(
				crypto_aead_aes256gcm_encrypt(
					reinterpret_cast<unsigned char*>(
						ciphertext.data()
					),
					&ciphertext_length,
					reinterpret_cast<const unsigned char*>(
						text.data()
					),
					static_cast<unsigned long long>(
						text.size()
					),
					nullptr,
					0,
					nullptr,
					reinterpret_cast<const unsigned char*>(
						nonce.data()
					),
					reinterpret_cast<const unsigned char*>(
						private_key.data()
					)
				) != 0
			)
			{
				return
					false;
			}

			ciphertext.resize(
				static_cast<size_t>(
					ciphertext_length
				)
			);

			text =
				std::move(
					ciphertext
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
		Aes256CipherCryptographyManager
			::decrypt_text(
				std::vector<uint8_t>&
					text,
				const std::vector<uint8_t>&
					private_key,
				const std::vector<uint8_t>&
					nonce
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!text.size() ||
				!private_key.size() ||
				!nonce.size() ||
				text.size() <
				crypto_aead_aes256gcm_ABYTES ||
				private_key.size() !=
				crypto_aead_aes256gcm_KEYBYTES ||
				nonce.size() !=
				crypto_aead_aes256gcm_NPUBBYTES
			);			
			
			std::vector<uint8_t>
				plaintext(
					text.size() -
					crypto_aead_aes256gcm_ABYTES
				);

			unsigned long long
				plaintext_length =
					0;

			if
			(
				crypto_aead_aes256gcm_decrypt(
					reinterpret_cast<unsigned char*>(
						plaintext.data()
					),
					&plaintext_length,
					nullptr,
					reinterpret_cast<const unsigned char*>(
						text.data()
					),
					static_cast<unsigned long long>(
						text.size()
					),
					nullptr,
					0,
					reinterpret_cast<const unsigned char*>(
						nonce.data()
					),
					reinterpret_cast<const unsigned char*>(
						private_key.data()
					)
				) != 0
			)
			{
				return
					false;
			}

			plaintext.resize(
				static_cast<size_t>(
					plaintext_length
				)
			);

			text =
				std::move(
					plaintext
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
}

#endif
