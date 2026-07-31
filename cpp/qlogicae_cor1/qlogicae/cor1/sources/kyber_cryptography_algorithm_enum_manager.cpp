#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		KyberCryptographyAlgorithmEnumManager \
	)

#include "../includes/kyber_cryptography_algorithm_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	KyberCryptographyAlgorithmEnumManager
		::KyberCryptographyAlgorithmEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<KyberCryptographyAlgorithmEnumManagerConfigurations>()
    {
        
    }

	std::string
		KyberCryptographyAlgorithmEnumManager
			::convert_enum_to_string(
				const KyberCryptographyAlgorithm&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				"NONE",
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			switch (value)
			{
				case (KyberCryptographyAlgorithm::KYBER_512):
				{
					return
						"KYBER_512";
				}
				case (KyberCryptographyAlgorithm::KYBER_768):
				{
					return
						"KYBER_768";
				}
				case (KyberCryptographyAlgorithm::KYBER_1024):
				{
					return
						"KYBER_1024";
				}
				case (KyberCryptographyAlgorithm::NONE):
				{
					return
						"NONE";
				}				
				default:
				{
					return
						"NONE";
				}
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {	
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				"NONE"
			);
        }
	}

	std::string
		KyberCryptographyAlgorithmEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	std::string
		KyberCryptographyAlgorithmEnumManager
			::convert_enum_to_string_algorithm_name(
				const KyberCryptographyAlgorithm&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				"NONE",
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			switch (value)
			{
				case (KyberCryptographyAlgorithm::KYBER_512):
				{
					return
						"Kyber512";
				}
				case (KyberCryptographyAlgorithm::KYBER_768):
				{
					return
						"Kyber768";
				}
				case (KyberCryptographyAlgorithm::KYBER_1024):
				{
					return
						"Kyber1024";
				}
				case (KyberCryptographyAlgorithm::NONE):
				{
					return
						"NONE";
				}				
				default:
				{
					return
						"NONE";
				}
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {	
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				"NONE"
			);
        }
	}

	std::string
		KyberCryptographyAlgorithmEnumManager
			::convert_enum_to_string_algorithm_name()
	{
		return
			convert_enum_to_string_algorithm_name(
				configurations
					.type
			);
	}

	KyberCryptographyAlgorithm
		KyberCryptographyAlgorithmEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				KyberCryptographyAlgorithm::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			if
			(
				value == "KYBER_512"
			)
			{
				return
					KyberCryptographyAlgorithm
						::KYBER_512;
			}
			else if
			(
				value == "KYBER_768"
			)
			{
				return
					KyberCryptographyAlgorithm
						::KYBER_768;
			}
			else if
			(
				value == "KYBER_1024"
			)
			{
				return
					KyberCryptographyAlgorithm
						::KYBER_1024;
			}
			else if
			(
				value == "NONE"
			)
			{
				return
					KyberCryptographyAlgorithm
						::NONE;
			}
			else
			{
				return
					KyberCryptographyAlgorithm
						::NONE;
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {	
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				KyberCryptographyAlgorithm::NONE
			);			
        }
	}

	KyberCryptographyAlgorithm
		KyberCryptographyAlgorithmEnumManager
			::convert_string_to_enum()
	{
		return
			convert_string_to_enum(
				convert_enum_to_string(
					configurations
						.type
				)
			);
	}
}

#endif
