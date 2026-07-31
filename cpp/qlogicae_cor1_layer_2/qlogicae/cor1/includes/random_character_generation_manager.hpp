#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomCharacterGenerationManager \
	)

#include "character_domain.hpp"
#include "text_encoding_manager.hpp"
#include "character_domain_manager.hpp"
#include "random_seed_generation_manager.hpp"
#include "random_character_generation_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		RandomCharacterGenerationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RandomCharacterGenerationManagerConfigurations>
    {
    public:
		RandomCharacterGenerationManager();

		template <typename Type> Type
			generate_character(
				const CharacterDomain&
					character_domain,
				const std::unordered_set<Type>&
					xdz
			);

		template <typename Type> Type
			generate_character(
				const CharacterDomain&
					character_domain
			);

		template <typename Type> Type
			generate_character(
				const std::string&
					character_domain,
				const std::unordered_set<Type>&
					excluded
			);

		template <typename Type> Type
			generate_character(
				const std::string&
					character_domain
			);
	};

	template <typename Type> Type
		RandomCharacterGenerationManager
			::generate_character(
				const CharacterDomain&
					character_domain,
				const std::unordered_set<Type>&
					excluded
			)
    {
        try
		{		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			const std::string
				domain =
					QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<CharacterDomainManager>()
						.get_value
						(
							character_domain
						);

			if
			(
				domain
					.empty()
			)
			{
				return
					Type{};
			}

			std::size_t eligible_count = 0;
			for (const char c : domain)
			{
				if (excluded.find(static_cast<Type>(c)) == excluded.end())
				{
					++eligible_count;
				}
			}

			if (eligible_count == 0)
			{
				return Type{};
			}
				
			std::uniform_int_distribution<std::size_t> distribution(0, eligible_count - 1);
			std::size_t target_index =
				distribution(QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<RandomSeedGenerationManager>().random_indeterministic_seed_engine);
				
			for (const char c : domain)
			{
				const Type converted = static_cast<Type>(c);

				if (excluded.find(converted) == excluded.end())
				{
					if (target_index == 0)
					{
						return converted;
					}
					--target_index;
				}
			}

			return
				Type{}; 
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
    }

    template <typename Type> Type
		RandomCharacterGenerationManager
			::generate_character(
				const CharacterDomain&
					character_domain
			)
    {
        return
            generate_character<Type>
            (
                character_domain,
                {}
            );
    }

	template <typename Type> Type
		RandomCharacterGenerationManager
			::generate_character(
				const std::string&
					character_domain,
				const std::unordered_set<Type>&
					excluded
			)
	{
		try
		{			
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				character_domain.empty()
			);

			std::vector<Type> candidates;
			candidates.reserve(character_domain.size());

			for (const auto& ch : character_domain)
			{
				if (excluded.find(static_cast<Type>(ch)) == excluded.end())
					candidates.push_back(static_cast<Type>(ch));
			}

			if (candidates.empty())
			{
				return
					Type{};
			}

			const std::size_t index =
				std::uniform_int_distribution<std::size_t>(
					0,
					candidates.size() - 1
				)(QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<RandomSeedGenerationManager>().random_indeterministic_seed_engine);

			return
				candidates[index];
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}

	template <typename Type> Type
		RandomCharacterGenerationManager
			::generate_character(
				const std::string&
					character_domain
			)
	{
		return
			generate_character<Type>(
				character_domain,
				{}
			);
	}
}

#endif
