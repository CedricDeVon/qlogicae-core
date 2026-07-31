#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EnumManager \
	)

#include "enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		EnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<EnumManagerConfigurations>
    {
    public:
		EnumManager();

		std::string
			convert_enum_string(
				const std::string&
					value,
				const TextCase&
					original_text_case,
				const TextCase&
					target_text_case
			);

		std::string
			convert_enum_string(
				const std::string&
					value,
				const TextCase&
					original_text_case
			);

		std::string
			convert_enum_string(
				const std::string&
					value
			);

		std::string
			convert_default_enum_string(
				const std::string&
					value
			);

		std::string
			get_none_string(
				const TextCase&
					text_case
			);

		std::string
			get_none_string();
    };
}

#endif
