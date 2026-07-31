#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EmailBodyEnumManager \
	)

#include "email_body.hpp"
#include "email_body_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		EmailBodyEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<EmailBodyEnumManagerConfigurations>
    {
    public:
		EmailBodyEnumManager();

		std::string
			convert_enum_to_string(
				const EmailBody&
					value
			);

		std::string
			convert_enum_to_string();

		EmailBody
			convert_string_to_enum(
				const std::string&
					value
			);

		EmailBody
			convert_string_to_enum();
    };
}

#endif
