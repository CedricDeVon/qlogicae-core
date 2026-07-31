#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		DilithiumCryptographyAlgorithmEnumManager \
	)

#include "../includes/dilithium_cryptography_algorithm_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	DilithiumCryptographyAlgorithmEnumManager
		::DilithiumCryptographyAlgorithmEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<DilithiumCryptographyAlgorithmEnumManagerConfigurations>()
    {
        
    }

	std::string
		DilithiumCryptographyAlgorithmEnumManager
			::convert_enum_to_string(
				const DilithiumCryptographyAlgorithm&
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
				case (DilithiumCryptographyAlgorithm::DILITHIUM_2):
				{
					return
						"DILITHIUM_2";
				}
				case (DilithiumCryptographyAlgorithm::DILITHIUM_3):
				{
					return
						"DILITHIUM_3";
				}
				case (DilithiumCryptographyAlgorithm::DILITHIUM_5):
				{
					return
						"DILITHIUM_5";
				}
				case (DilithiumCryptographyAlgorithm::NONE):
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
		DilithiumCryptographyAlgorithmEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	std::string
		DilithiumCryptographyAlgorithmEnumManager
			::convert_enum_to_string_algorithm_name(
				const DilithiumCryptographyAlgorithm&
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
				case (DilithiumCryptographyAlgorithm::DILITHIUM_2):
				{
					return
						"ML-DSA-44";
				}
				case (DilithiumCryptographyAlgorithm::DILITHIUM_3):
				{
					return
						"ML-DSA-65";
				}
				case (DilithiumCryptographyAlgorithm::DILITHIUM_5):
				{
					return
						"ML-DSA-87";
				}
				case (DilithiumCryptographyAlgorithm::NONE):
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
		DilithiumCryptographyAlgorithmEnumManager
			::convert_enum_to_string_algorithm_name()
	{
		return
			convert_enum_to_string_algorithm_name(
				configurations
					.type
			);
	}

	DilithiumCryptographyAlgorithm
		DilithiumCryptographyAlgorithmEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				DilithiumCryptographyAlgorithm::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			if
			(
				value == "DILITHIUM_2"
			)
			{
				return
					DilithiumCryptographyAlgorithm
						::DILITHIUM_2;
			}
			else if
			(
				value == "DILITHIUM_3"
			)
			{
				return
					DilithiumCryptographyAlgorithm
						::DILITHIUM_3;
			}
			else if
			(
				value == "DILITHIUM_5"
			)
			{
				return
					DilithiumCryptographyAlgorithm
						::DILITHIUM_5;
			}
			else if
			(
				value == "NONE"
			)
			{
				return
					DilithiumCryptographyAlgorithm
						::NONE;
			}
			else
			{
				return
					DilithiumCryptographyAlgorithm
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
				DilithiumCryptographyAlgorithm::NONE
			);			
        }
	}

	DilithiumCryptographyAlgorithm
		DilithiumCryptographyAlgorithmEnumManager
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
