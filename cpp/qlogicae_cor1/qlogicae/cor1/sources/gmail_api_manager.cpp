#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		GmailApiManager \
	)

#include "../includes/gmail_api_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
   GmailApiManager
		::GmailApiManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<GmailApiManagerConfigurations>()
	{
		construct();	
	}

	GmailApiManager
		::~GmailApiManager()
	{
		destruct();		
	}
    
    bool
        GmailApiManager
			::construct()
    {
        try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			return
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<CurlPackageManager>()
					.setup();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

    bool
        GmailApiManager
			::destruct()
    {
        try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			curl_global_cleanup();

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

	GmailApiManagerResponse
		GmailApiManager
			::send_email()
	{
		CURL* curl = nullptr;
		curl_mime* mixed = nullptr;
		curl_mime* related = nullptr;
		curl_mimepart* related_part = nullptr;
		curl_mimepart* body_part = nullptr;
		struct curl_slist* headers = nullptr;
		struct curl_slist* recipients = nullptr;
		
		GmailApiManagerResponse
			response;

		try
        {	
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				[&response]() { response.status = ResultsStatus::BAD; return response; }(),
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!configurations.full_smtp_server_address.size() ||
				!configurations.sender_email_address.size() ||
				configurations.to_recipients.empty() ||
				!configurations.password_provider ||
				!configurations.password_provider().size()
			);		

			curl = curl_easy_init();
			if (curl)
			{
				if (configurations.is_inner_logging_enabled)
				{
					curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
				}				

				size_t
					index =
						0;
				std::string
					temporary_text =
						"";
				size_t
					subject_name_size =
						configurations
							.subject_name
								.size();
				size_t
					sender_email_address_size =
						configurations
							.sender_email_address
								.size();
				size_t
					to_recipients_size =
						configurations
							.to_recipients
								.size();
				size_t
					cc_recipients_size =
						configurations
							.cc_recipients
								.size();
				size_t
					bcc_recipients_size =
						configurations
							.bcc_recipients
								.size();
				size_t
					custom_headers_size =
						configurations
							.custom_headers
								.size();

				if (subject_name_size)
				{
					temporary_text =
						"Subject: " + configurations.subject_name;
					headers =
						curl_slist_append(
							headers,
							temporary_text
								.c_str()
						);
				}

				if (sender_email_address_size)
				{
					temporary_text =
						"From: <" + configurations.sender_email_address + ">";
					headers =
						curl_slist_append(
							headers,
							temporary_text
								.c_str()
						);
				}

				if (to_recipients_size)
				{
					temporary_text =
						"To: ";
					for
					(
						index = 0;
						index < to_recipients_size;
						++index
					)
					{
						temporary_text +=
							"<" + configurations.to_recipients[index] + ">";
						if (index < to_recipients_size - 1)
						{
							temporary_text += ", ";
						}					
					}
					headers =
						curl_slist_append(
							headers,
							temporary_text
								.c_str()
						);
				}	
				
				if (cc_recipients_size)
				{
					temporary_text =
						"Cc: ";
					for
					(
						index = 0;
						index < cc_recipients_size;
						++index
					)
					{
						temporary_text +=
							"<" + configurations.cc_recipients[index] + ">";
						if (index < cc_recipients_size - 1)
						{
							temporary_text += ", ";
						}					
					}
					headers =
						curl_slist_append(
							headers,
							temporary_text.c_str()
						);
				}

				if (custom_headers_size)
				{
					for
					(
						const auto&
							pair :
							configurations
								.custom_headers
					)
					{
						headers =
							curl_slist_append(
								headers,
								(pair.first + ": " + pair.second).c_str()
							);
					}
				}
								
				curl_easy_setopt(
					curl,
					CURLOPT_HTTPHEADER,
					headers
				);
				curl_easy_setopt(
					curl,
					CURLOPT_URL,
					configurations
						.full_smtp_server_address
							.c_str()
				);
				curl_easy_setopt(
					curl,
					CURLOPT_USERNAME,
					configurations
						.sender_email_address
							.c_str()
				);
				curl_easy_setopt(
					curl,
					CURLOPT_PASSWORD,
					configurations
						.password_provider()
							.c_str()
				);
				curl_easy_setopt(
					curl,
					CURLOPT_MAIL_FROM,
					("<" + configurations.sender_email_address + ">").c_str());

				switch (configurations.email_security_type)
				{
					case (EmailSecurity::SSL):
					{
						curl_easy_setopt(
							curl,
							CURLOPT_USE_SSL,
							CURLUSESSL_ALL
						);
						curl_easy_setopt(
							curl,
							CURLOPT_SSL_VERIFYPEER,
							1L
						);
						curl_easy_setopt(
							curl,
							CURLOPT_SSL_VERIFYHOST,
							2L
						);
						break;
					}
				}			
					
				for
				(
					const std::string&
						item :
						configurations
							.to_recipients
				)
				{
					recipients = curl_slist_append(
						recipients,
						("<" + item + ">").c_str());
				}
				for
				(
					const std::string&
						item :
						configurations
							.cc_recipients
				)
				{
					recipients = curl_slist_append(
						recipients,
						("<" + item + ">").c_str());
				}
				for
				(
					const std::string&
						item :
						configurations
							.bcc_recipients
				)
				{
					recipients = curl_slist_append(
						recipients,
						("<" + item + ">").c_str());
				}
				curl_easy_setopt(
					curl,
					CURLOPT_MAIL_RCPT,
					recipients
				);

				mixed = curl_mime_init(curl);
				related = curl_mime_init(curl);
				body_part = curl_mime_addpart(related);
				curl_mime_data(body_part, configurations.raw_body.c_str(), CURL_ZERO_TERMINATED);
				switch (configurations.email_body_type)
				{
					case (EmailBody::HTML):
					{
						curl_mime_type(body_part, "text/html");
						break;
					}
					case (EmailBody::PLAIN):
					{
						curl_mime_type(body_part, "text/plain");
						break;
					}
					default:
					{
						curl_mime_type(body_part, "text/plain");
						break;
					}
				}
				
				related_part =
					curl_mime_addpart(
						mixed
					);
				curl_mime_subparts(
					related_part,
					related
				);
				curl_mime_type(
					related_part,
					"multipart/related"
				);

				if (configurations.attached_files.size())
				{
					curl_mimepart* part = curl_mime_addpart(related);
					part = curl_mime_addpart(mixed);
					curl_mime_type(part, "multipart/related");

					for (const auto& attached_file : configurations.attached_files)
					{
						curl_mimepart* part = curl_mime_addpart(mixed);
						curl_mime_filedata(part, attached_file.file_path.c_str());
						curl_mime_type(part, attached_file.mime_type.c_str());
						curl_mime_encoder(part, "base64");
						curl_mime_filename(part, attached_file.file_name.c_str());

						struct curl_slist* headers = nullptr;
						headers = curl_slist_append(headers, ("Content-Disposition: attachment; filename=\"" + attached_file.file_name + "\"").c_str());
						curl_mime_headers(part, headers, 1);
					}
				}

				curl_easy_setopt(curl, CURLOPT_MIMEPOST, mixed);
				CURLcode res = curl_easy_perform(curl);
				if (res != CURLE_OK)
				{
					response
						.status =
							ResultsStatus::BAD;

					response
						.message =
							curl_easy_strerror(
								res
							);					
				}
				else
				{
					response
						.status =
							ResultsStatus::GOOD;

					response
						.message =
							"";
				}

				curl_slist_free_all(
					recipients
				);
				curl_mime_free(
					mixed
				);
				curl_easy_cleanup(
					curl
				);
			}

			curl_global_cleanup();

			return
				response;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			if (recipients)
			{
				curl_slist_free_all(
					recipients
				);
			}
			if (mixed)
			{
				curl_mime_free(
					mixed
				);
			}
			if (curl)
			{
				curl_easy_cleanup(
					curl
				);
			}			
			curl_global_cleanup();

			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				[&response]() { response.status = ResultsStatus::BAD; return response; }()
			);
        }
	}
}

#endif
