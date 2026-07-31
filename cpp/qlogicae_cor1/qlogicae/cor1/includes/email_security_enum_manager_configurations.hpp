#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EmailSecurityEnumManagerConfigurations \
	)

#include "email_security.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		EmailSecurityEnumManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<EmailSecurityEnumManagerConfigurations>
	{
	public:	
		EmailSecurity
			type =
				EmailSecurity
					::SSL;

		EmailSecurityEnumManagerConfigurations();
	};
}

#endif
