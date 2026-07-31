#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		GmailApiManager \
	)

#include "gmail_api_manager_response.hpp"
#include "gmail_api_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		GmailApiManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<GmailApiManagerConfigurations>
    {
    public:
		GmailApiManager();

		~GmailApiManager();

		bool
			construct();

		bool
			destruct();

		GmailApiManagerResponse
			send_email();
	};
}

#endif
