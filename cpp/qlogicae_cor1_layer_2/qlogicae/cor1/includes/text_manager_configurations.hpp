#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		TextManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<TextManagerConfigurations>
    {
	public:
		std::unordered_map<std::string, std::string>
			replace_text_tokens_dictionary =
				{}; // NOTE: Using the 'default_configurations.' strategy will result in google unit test crashes

		std::string
			split_text_delimeter = 
				",";

		bool
			is_specified_length_enabled =
				false;

		size_t
			specified_length =
				128;

		TextManagerConfigurations();
    };    
}

#endif
