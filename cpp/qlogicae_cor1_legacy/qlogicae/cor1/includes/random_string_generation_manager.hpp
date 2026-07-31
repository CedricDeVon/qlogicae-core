#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomStringGenerationManager \
	)

#include "character_domain.hpp"
#include "character_domain_manager.hpp"
#include "random_seed_generation_manager.hpp"
#include "random_string_generation_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		RandomStringGenerationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RandomStringGenerationManagerConfigurations>
    {
    public:
		RandomStringGenerationManager();

		template <typename OutputType = std::string, typename ExcludedType = char> OutputType
			generate_string(
				const CharacterDomain&
					character_domain,
				const size_t&
					length,
				const std::unordered_set<ExcludedType>&
					excluded
			);

		template <typename OutputType = std::string, typename ExcludedType = char> OutputType
			generate_string(
				const OutputType&
					character_domain,
				const size_t&
					length,
				const std::unordered_set<ExcludedType>&
					excluded
			);

		template <typename OutputType = std::string, typename ExcludedType = char> OutputType
			generate_string(
				const CharacterDomain&
					character_domain,
				const size_t&
					length
			);

		template <typename OutputType = std::string, typename ExcludedType = char> OutputType
			generate_string(
				const CharacterDomain&
					character_domain
			);		

		template <typename OutputType = std::string, typename ExcludedType = char> OutputType
			generate_string(
				const OutputType&
					character_domain,
				const size_t&
					length
			);		

		template <typename OutputType = std::string, typename ExcludedType = char> OutputType
			generate_string(
				const OutputType&
					character_domain
			);

		template <typename OutputType = std::string, typename ExcludedType = char> OutputType
			generate_string();		
	};

	template <typename OutputType, typename ExcludedType> OutputType
		RandomStringGenerationManager
			::generate_string(
				const CharacterDomain&
					character_domain,
				const size_t&
					length,
				const std::unordered_set<ExcludedType>&
					excluded
			)
	{
		try
        {            
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				OutputType {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				character_domain == CharacterDomain::NONE ||
				length < 1
			);

			OutputType result;
			result.reserve(length);

			const std::string domain =
				SingletonManager::get_singleton<CharacterDomainManager>().get_value(character_domain);

			std::vector<typename OutputType::value_type> filtered;
			filtered.reserve(domain.size());

			for (const char c : domain)
			{
				auto converted = static_cast<typename OutputType::value_type>(c);
				if (excluded.find(converted) == excluded.end())
				{
					filtered.push_back(converted);
				}
			}

			if (filtered.empty())
			{
				return OutputType{};
			}

			std::uniform_int_distribution<std::size_t> distribution(0, filtered.size() - 1);
			for (size_t i = 0; i < length; ++i)
			{
				result.push_back(filtered[distribution(SingletonManager::get_singleton<RandomSeedGenerationManager
					>().random_indeterministic_seed_engine)]);
			}

			return result;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {			
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				OutputType {}
			);
        }
	}

	template <typename OutputType, typename ExcludedType> OutputType
		RandomStringGenerationManager
			::generate_string(
				const OutputType&
					character_domain,
				const size_t&
					length,
				const std::unordered_set<ExcludedType>&
					excluded
			)
	{
		try
        {           
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				OutputType {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				length < 1
			);

			OutputType result;
			result.reserve(length);

			std::vector<typename OutputType::value_type> filtered;
			filtered.reserve(character_domain.size());

			for (const char c : character_domain)
			{
				auto converted = static_cast<typename OutputType::value_type>(c);
				if (excluded.find(converted) == excluded.end())
				{
					filtered.push_back(converted);
				}
			}

			if (filtered.empty())
			{
				return OutputType{};
			}

			std::uniform_int_distribution<std::size_t> distribution(0, filtered.size() - 1);
			for (size_t i = 0; i < length; ++i)
			{
				result.push_back(filtered[distribution(SingletonManager::get_singleton<RandomSeedGenerationManager
					>().random_indeterministic_seed_engine)]);
			}

			return result;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {			
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				OutputType {}
			);
        }
	}

	template <typename OutputType, typename ExcludedType> OutputType
		RandomStringGenerationManager
			::generate_string(
				const CharacterDomain&
					character_domain,
				const size_t&
					length
			)
	{
		return
			generate_string<OutputType, ExcludedType>
			(
				character_domain,
				length,
				std::unordered_set<ExcludedType> {}
			);
	}


	template <typename OutputType, typename ExcludedType> OutputType
		RandomStringGenerationManager
			::generate_string(
				const CharacterDomain&
					character_domain
			)
	{
		return
			generate_string<OutputType, ExcludedType>
			(
				character_domain,
				configurations
					.length,
				std::unordered_set<ExcludedType> {}
			);
	}

	template <typename OutputType, typename ExcludedType> OutputType
		RandomStringGenerationManager
			::generate_string(
				const OutputType&
					character_domain,
				const size_t&
					length
			)
	{
		return
			generate_string<OutputType, ExcludedType>
			(
				character_domain,
				length,
				std::unordered_set<ExcludedType> {}
			);
	}

	template <typename OutputType, typename ExcludedType> OutputType
		RandomStringGenerationManager
			::generate_string(
				const OutputType&
					character_domain
			)
	{
		return
			generate_string<OutputType, ExcludedType>
			(
				character_domain,
				configurations
					.length,
				std::unordered_set<ExcludedType> {}
			);
	}

	template <typename OutputType, typename ExcludedType> OutputType
		RandomStringGenerationManager
			::generate_string()
	{
		return
			generate_string<OutputType, ExcludedType>
			(
				configurations
					.character_domain,
				configurations
					.length,
				std::unordered_set<ExcludedType> {}
			);
	}
}

#endif
