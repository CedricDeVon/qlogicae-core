#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		GmailApiManagerConfigurations \
	)

#include "../includes/gmail_api_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	GmailApiManagerConfigurations
		::GmailApiManagerConfigurations() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<GmailApiManagerConfigurations>()
	{		
		is_inner_logging_enabled =
			true;

		subject_name =
			"";

		email_body_type =
			EmailBody::PLAIN;

		email_security_type =
			EmailSecurity::SSL;

		raw_body =
			"";

		full_smtp_server_address =
			"";

		sender_email_address =
			"";

		to_recipients =
			{};

		cc_recipients =
			{};

		bcc_recipients =
			{};

		attached_files =
			{};

		password_provider =
			[]() { return ""; };

		custom_headers =
			{};
	}
}

#endif
