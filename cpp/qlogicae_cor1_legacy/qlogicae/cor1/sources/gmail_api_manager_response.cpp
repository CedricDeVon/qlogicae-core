#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		GmailApiManagerResponse \
	)

#include "../includes/gmail_api_manager_response.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	GmailApiManagerResponse
		::GmailApiManagerResponse()
	{		
		status =
			ResultsStatus
				::GOOD;

		message =
			"";
	}
}

#endif
