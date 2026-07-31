#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomSeedGenerationManager \
	)

#include "random_seed_generation_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		RandomSeedGenerationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RandomSeedGenerationManagerConfigurations>
    {
    public:
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_3
		);

		std::mt19937
			random_indeterministic_seed_engine;

		std::mt19937
			random_deterministic_seed_engine;

		std::mt19937
			random_cryptography_seed_engine;

		RandomSeedGenerationManager();

		~RandomSeedGenerationManager();

		bool
			construct();

		bool
			destruct();

		bool
			setup_indeterministic_seed();

		bool
			setup_deterministic_seed(
				const std::uint64_t&
					value
			);

		bool
			setup_cryptography_seed();

		uint64_t
			generate_indeterministic_seed();

		uint64_t
			generate_deterministic_seed(
				const std::uint64_t&
					value
			);

		uint64_t
			generate_cryptography_seed();

		std::uint64_t
			mix_entropy();

		std::uint64_t
			mix_split_64(
				const std::uint64_t&
					value
			);
	};
}

#endif
