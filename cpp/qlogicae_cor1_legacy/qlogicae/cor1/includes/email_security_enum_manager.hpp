#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EmailSecurityEnumManager \
	)

#include "email_security.hpp"
#include "email_security_enum_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		EmailSecurityEnumManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<EmailSecurityEnumManagerConfigurations>
    {
    public:
		EmailSecurityEnumManager();

		std::string
			convert_enum_to_string(
				const EmailSecurity&
					value
			);

		std::string
			convert_enum_to_string();

		EmailSecurity
			convert_string_to_enum(
				const std::string&
					value
			);

		EmailSecurity
			convert_string_to_enum();
    };
}

#endif
