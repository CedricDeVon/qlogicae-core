#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		DilithiumCryptographyManager \
	)

#include "../includes/dilithium_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    DilithiumCryptographyManager
		::DilithiumCryptographyManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<DilithiumCryptographyManagerConfigurations>()
	{
		
	}

	bool
		DilithiumCryptographyManager
			::generate_keypair(
				const DilithiumCryptographyAlgorithm&
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
				algorithm == DilithiumCryptographyAlgorithm::NONE
			);			

			OQS_SIG* sig = OQS_SIG_new(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<DilithiumCryptographyAlgorithmEnumManager>()
					.convert_enum_to_string_algorithm_name(algorithm).c_str()
			);
			if (sig == nullptr)
			{
				return false;
			}

			public_key.resize(sig->length_public_key);
			private_key.resize(sig->length_secret_key);

			if (OQS_SIG_keypair(sig, public_key.data(), private_key.data()) != OQS_SUCCESS)
			{
				OQS_SIG_free(sig);
				return false;
			}

			OQS_SIG_free(sig);

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
		DilithiumCryptographyManager
			::sign_text(
				const DilithiumCryptographyAlgorithm&
					algorithm,
				const std::vector<uint8_t>&
					private_key,
				const std::vector<uint8_t>&
					message,
				std::vector<uint8_t>&
					signature
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				algorithm == DilithiumCryptographyAlgorithm::NONE ||
				private_key.empty() ||
				message.empty()
			);			

			OQS_SIG* sig = OQS_SIG_new(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<DilithiumCryptographyAlgorithmEnumManager>()
					.convert_enum_to_string_algorithm_name(algorithm).c_str()
			);
			if (sig == nullptr)
			{
				return false;
			}

			if(private_key.size() != sig->length_secret_key)
			{
				OQS_SIG_free(sig);
				return false;
			}

			signature.resize(sig->length_signature);
			size_t signature_len = 0;

			if (OQS_SIG_sign(
				sig,
				signature.data(),
				&signature_len,
				message.data(),
				message.size(),
				private_key.data()
			) != OQS_SUCCESS)
			{
				OQS_SIG_free(sig);
				return false;
			}

			if(signature_len > sig->length_signature)
			{
				OQS_SIG_free(sig);
				return false;
			}

			signature.resize(signature_len);

			OQS_SIG_free(sig);

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
		DilithiumCryptographyManager
			::verify_text(
				const DilithiumCryptographyAlgorithm&
					algorithm,
				const std::vector<uint8_t>&
					public_key,
				const std::vector<uint8_t>&
					message,
				const std::vector<uint8_t>&
					signature
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				algorithm == DilithiumCryptographyAlgorithm::NONE ||
				public_key.empty() ||
				message.empty() ||
				signature.empty()
			);			

			OQS_SIG* sig = OQS_SIG_new(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<DilithiumCryptographyAlgorithmEnumManager>()
					.convert_enum_to_string_algorithm_name(algorithm).c_str()
			);
			if (sig == nullptr)
			{
				return false;
			}

			if (public_key.size() != sig->length_public_key)
			{
				OQS_SIG_free(sig);
				return false;
			}

			OQS_STATUS status = OQS_SIG_verify(
				sig,
				message.data(),
				message.size(),
				signature.data(),
				signature.size(),
				public_key.data()
			);

			OQS_SIG_free(sig);

			return status == OQS_SUCCESS;
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
		DilithiumCryptographyManager
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
		DilithiumCryptographyManager
			::sign_text(
				const std::vector<uint8_t>&
					private_key,
				const std::vector<uint8_t>&
					message,
				std::vector<uint8_t>&
					signature
			)
	{
		return
			sign_text(
				configurations
					.algorithm,
				private_key,
				message,
				signature
			);
	}

	bool
		DilithiumCryptographyManager
			::verify_text(
				const std::vector<uint8_t>&
					public_key,
				const std::vector<uint8_t>&
					message,
				const std::vector<uint8_t>&
					signature
			)
	{
		return
			verify_text(
				configurations
					.algorithm,
				public_key,
				message,
				signature
			);
	}
}

#endif
