#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		KyberCryptographyManager \
	)

#include "../includes/kyber_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    KyberCryptographyManager
		::KyberCryptographyManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<KyberCryptographyManagerConfigurations>()
	{
		
	}

	bool
		KyberCryptographyManager
			::generate_keypair(
				const KyberCryptographyAlgorithm&
					algorithm,
				std::vector<uint8_t>&
					public_key,
				std::vector<uint8_t>&
					private_key
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				algorithm == KyberCryptographyAlgorithm::NONE
			);			

			OQS_KEM* kem = OQS_KEM_new(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<KyberCryptographyAlgorithmEnumManager>()
					.convert_enum_to_string_algorithm_name(algorithm).c_str()
			);
			if (kem == nullptr)
			{
				return false;
			}

			if (kem->length_public_key == 0 ||
				kem->length_secret_key == 0)
			{
				OQS_KEM_free(kem);
				return false;
			}

			public_key.resize(kem->length_public_key);
			private_key.resize(kem->length_secret_key);

			if (OQS_KEM_keypair(kem, public_key.data(), private_key.data()) != OQS_SUCCESS)
			{
				OQS_KEM_free(kem);
				return false;
			}

			OQS_KEM_free(kem);

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
		KyberCryptographyManager
			::encrypt_text(
				const KyberCryptographyAlgorithm&
					algorithm,
				const std::vector<uint8_t>&
					public_key,
				std::vector<uint8_t>&
					ciphertext,
				std::vector<uint8_t>&
					shared_secret
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				algorithm == KyberCryptographyAlgorithm::NONE ||
				public_key.empty()
			);			

			OQS_KEM* kem = OQS_KEM_new(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<KyberCryptographyAlgorithmEnumManager>()
					.convert_enum_to_string_algorithm_name(algorithm).c_str()
			);
			if (kem == nullptr)
			{
				return false;
			}

			if (public_key.size() != kem->length_public_key)
			{
				OQS_KEM_free(kem);
				return false;
			}

			ciphertext.resize(kem->length_ciphertext);
			shared_secret.resize(kem->length_shared_secret);

			if (OQS_KEM_encaps(
				kem,
				ciphertext.data(),
				shared_secret.data(),
				public_key.data()
			) != OQS_SUCCESS)
			{
				OQS_KEM_free(kem);
				return false;
			}

			OQS_KEM_free(kem);

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
		KyberCryptographyManager
			::decrypt_text(
				const KyberCryptographyAlgorithm&
					algorithm,
				const std::vector<uint8_t>&
					private_key,
				const std::vector<uint8_t>&
					ciphertext,
				std::vector<uint8_t>&
					shared_secret
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				algorithm == KyberCryptographyAlgorithm::NONE ||
				private_key.empty() ||
				ciphertext.empty() 
			);			

			OQS_KEM* kem = OQS_KEM_new(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<KyberCryptographyAlgorithmEnumManager>()
					.convert_enum_to_string_algorithm_name(algorithm).c_str()
			);
			if (kem == nullptr)
			{
				return false;
			}

			if (private_key.size() != kem->length_secret_key ||
				ciphertext.size() != kem->length_ciphertext)
			{
				OQS_KEM_free(kem);
				return false;
			}

			shared_secret.resize(kem->length_shared_secret);

			if (OQS_KEM_decaps(
				kem,
				shared_secret.data(),
				ciphertext.data(),
				private_key.data()
			) != OQS_SUCCESS)
			{
				OQS_KEM_free(kem);
				return false;
			}

			OQS_KEM_free(kem);

			return true;
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
		KyberCryptographyManager
			::generate_keypair(
				std::vector<uint8_t>&
					public_key,
				std::vector<uint8_t>&
					private_key
			)
	{
		return
			generate_keypair(
				configurations
					.algorithm,
				public_key,
				private_key
			);
	}

	bool
		KyberCryptographyManager
			::encrypt_text(
				const std::vector<uint8_t>&
					public_key,
				std::vector<uint8_t>&
					ciphertext,
				std::vector<uint8_t>&
					shared_secret
			)
	{
		return
			encrypt_text(
				configurations
					.algorithm,
				public_key,
				ciphertext,
				shared_secret
			);
	}

	bool
		KyberCryptographyManager
			::decrypt_text(
				const std::vector<uint8_t>&
					private_key,
				const std::vector<uint8_t>&
					ciphertext,
				std::vector<uint8_t>&
					shared_secret
			)
	{
		return
			decrypt_text(
				configurations
					.algorithm,
				private_key,
				ciphertext,
				shared_secret
			);
	}
}

#endif
