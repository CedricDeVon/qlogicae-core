#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomValueGenerationManager \
	)

#include "random_value_generation_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		RandomValueGenerationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RandomValueGenerationManagerConfigurations>
    {
    public:
		RandomValueGenerationManager();

		~RandomValueGenerationManager();

		bool
			construct();

		bool
			destruct();

		std::array<unsigned char, 16>
			generate_random_salt();

		bool
			generate_random_bytes(
				unsigned char*
					buffer,
				const size_t&
					size
			);	
	};
}

#endif
