#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Argon2idHashCryptographyManager \
	)

#include "../includes/argon2id_hash_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    Argon2idHashCryptographyManager
		::Argon2idHashCryptographyManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<Argon2idHashCryptographyManagerConfigurations>()
	{

	}

	std::string
		Argon2idHashCryptographyManager
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
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				text.empty()
			);

			std::array<char, 512> vb{};
			int vc = argon2id_hash_encoded(
				3,
				1 << 16,
				2,
				text.data(),
				text.size(),
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<RandomValueGenerationManager>()
					.generate_random_salt()
					.data(),
				16,
				32,
				vb.data(),
				vb.size()
			);

			return
				(vc == ARGON2_OK) ?
					vb.data() :
					text;
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
		Argon2idHashCryptographyManager
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

			return 
				argon2id_verify(
					hash.data(), text.data(), text.size()
				) == ARGON2_OK;
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
		Argon2idHashCryptographyManager
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

			std::array<char, 512>
				encoded_hash{};

			const int
				result =
					argon2id_hash_encoded(
						3,
						1 << 16,
						2,
						reinterpret_cast<const void*>(
							text.data()
						),
						text.size(),
						QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<RandomValueGenerationManager>()
						.generate_random_salt()
						.data(),
						16,
						32,
						encoded_hash.data(),
						encoded_hash.size()
					);

			if
			(
				result !=
				ARGON2_OK
			)
			{
				return
					false;
			}

			text.assign(
				reinterpret_cast<const uint8_t*>(
					encoded_hash.data()
				),
				reinterpret_cast<const uint8_t*>(
					encoded_hash.data()
				) +
				std::strlen(
					encoded_hash.data()
				)
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
		Argon2idHashCryptographyManager
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

			return
				argon2id_verify(
					reinterpret_cast<const char*>(
						hash.data()
					),
					reinterpret_cast<const void*>(
						text.data()
					),
					text.size()
				) ==
				ARGON2_OK;
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
