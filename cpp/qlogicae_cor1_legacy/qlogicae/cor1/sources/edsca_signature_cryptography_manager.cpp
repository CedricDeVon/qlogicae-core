#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EdscaSignatureCryptographyManager \
	)

#include "../includes/edsca_signature_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    EdscaSignatureCryptographyManager
		::EdscaSignatureCryptographyManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<EdscaSignatureCryptographyManagerConfigurations>()
	{
		construct();	
	}

	bool
		EdscaSignatureCryptographyManager
			::construct()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			return
				!(sodium_init() > 1);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::vector<std::uint8_t>
		EdscaSignatureCryptographyManager
			::sign(
				const std::vector<std::uint8_t>&
					text,
				const std::vector<std::uint8_t>&
					private_key
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!text.size() ||
				!private_key.size() ||
				private_key.size() != crypto_sign_SECRETKEYBYTES
			);

			std::vector<std::uint8_t>
				signature(
					crypto_sign_BYTES
				);
        
			crypto_sign_detached(
				signature.data(), nullptr,
				text.data(), text.size(),
				private_key.data()
			);

			return
				signature;
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
		EdscaSignatureCryptographyManager
			::verify(
				const std::vector<std::uint8_t>&
					text,
				const std::vector<std::uint8_t>&
					public_key,
				const std::vector<std::uint8_t>&
					signature
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!text.size() ||
				!public_key.size() ||
				!signature.size() ||
				public_key.size() != crypto_sign_PUBLICKEYBYTES ||
				signature.size() != crypto_sign_BYTES
			);	

			return
				crypto_sign_verify_detached(
					signature.data(),
					text.data(), text.size(),
					public_key.data()
				) == 0;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {	
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::string
		EdscaSignatureCryptographyManager
			::sign(
				const std::string&
					text,
				const std::string&
					private_key
			)
	{
		auto sig_vec = sign(
            std::vector<std::uint8_t>(text.begin(), text.end()),
            std::vector<std::uint8_t>(private_key.begin(), private_key.end())
        );

        return
			std::string(sig_vec.begin(), sig_vec.end());
	}

	bool
		EdscaSignatureCryptographyManager
			::verify(
				const std::string&
					text,
				const std::string&
					public_key,
				const std::string&
					signature
			)
	{
		return
			verify(
				std::vector<std::uint8_t>(text.begin(), text.end()),
				std::vector<std::uint8_t>(public_key.begin(), public_key.end()),
				std::vector<std::uint8_t>(signature.begin(), signature.end())
			);
	}
}

#endif

