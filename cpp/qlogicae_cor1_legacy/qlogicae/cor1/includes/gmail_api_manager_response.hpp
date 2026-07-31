#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		GmailApiManagerResponse \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		GmailApiManagerResponse
    {
		ResultsStatus
			status =
				ResultsStatus
					::GOOD;

		std::string
			message =
				"";

		GmailApiManagerResponse();
    };
}

#endif
