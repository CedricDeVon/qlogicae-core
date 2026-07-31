#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RestApiManager \
	)

#include "../includes/rest_api_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        
	RestApiManager
		::RestApiManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RestApiManagerConfigurations>()
    {
		construct();
	}        

	RestApiManager
		::~RestApiManager()
    {
		destruct();
	}        

	bool
		RestApiManager
			::construct()
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<CurlPackageManager>()
				.setup();

			size_t
				size =
					8; 

			curl_pool
				.reserve(
					size
				);

			for
			(
				size_t index = 0;
				index < size;
				++index
			)
			{
				CURL*
					curl_handler =
						curl_easy_init();

				if (curl_handler)
				{
					curl_pool
						.push_back(
							curl_handler
						);
				}
			}

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

	bool
		RestApiManager
			::destruct()
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

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

	RestApiManagerResponse
		RestApiManager
			::execute_get_request(
				const std::string&
					path
			)
	{
		RestApiManagerResponse
			response;

		execute_request(
			response,
			"GET",
			path,
			""
		);

		return
			response;
	}

	RestApiManagerResponse
		RestApiManager
			::execute_post_request(
				const std::string&
					path,
				const std::string&
					body
			)
	{
		RestApiManagerResponse
			response;

		execute_request(
			response,
			"POST",
			path,
			body
		);

		return
			response;
	}

	RestApiManagerResponse
		RestApiManager
			::execute_put_request(
				const std::string&
					path,
				const std::string&
					body
			)
	{
		RestApiManagerResponse
			response;

		execute_request(
			response,
			"PUT",
			path,
			body
		);

		return
			response;
	}

	RestApiManagerResponse
		RestApiManager
			::execute_del_request(
				const std::string&
					path
			)
	{
		RestApiManagerResponse
			response;

		execute_request(
			response,
			"DELETE",
			path,
			""
		);

		return
			response;
	}

	RestApiManagerResponse
		RestApiManager
			::execute_head_request(
				const std::string&
					path
			)
	{
		RestApiManagerResponse
			response;

		execute_request(
			response,
			"HEAD",
			path,
			""
		);

		return
			response;
	}

	RestApiManagerResponse
		RestApiManager
			::execute_options_request(
				const std::string&
					path
			)
	{
		RestApiManagerResponse
			response;

		execute_request(
			response,
			"OPTIONS",
			path,
			""
		);

		return
			response;
	}

	RestApiManagerResponse
		RestApiManager
		::execute_raw_request(
			const std::string&
				method,
			const std::string&
				path,
			const std::string&
				body
		)
	{
		RestApiManagerResponse
			response;

		execute_request(
			response,
			method,
			path,
			body
		);

		return
			response;
	}

	bool	
		RestApiManager
			::execute_request(
				RestApiManagerResponse&
					response,
				const std::string&
					method,
				const std::string&
					path,
				const std::string&
					body
			)
	{
		try
		{			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				method.empty() ||
				path.empty() ||
				body.empty()
			);

			std::string url =
				setup_url(
					configurations
						.base_url,
					path
				);

			CURL* curl_handler = acquire_handle();

			curl_easy_setopt(curl_handler, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl_handler, CURLOPT_CUSTOMREQUEST, method.c_str());
			curl_easy_setopt(curl_handler, CURLOPT_FOLLOWLOCATION, configurations.follow_redirects ? 1L : 0L);

			curl_easy_setopt(curl_handler, CURLOPT_CONNECTTIMEOUT, configurations.wait_forever ? 0L : configurations.connect_timeout_seconds);
			curl_easy_setopt(curl_handler, CURLOPT_TIMEOUT, configurations.wait_forever ? 0L : configurations.request_timeout_seconds);

			if (configurations.enable_http2)
				curl_easy_setopt(curl_handler, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);

			std::string response_body;
			std::multimap<std::string, std::string> response_headers;

			if (configurations.capture_body)
			{
				curl_easy_setopt(
					curl_handler,
					CURLOPT_WRITEFUNCTION,
					[this](
						void*
							pointer,
						size_t
							size,
						size_t
							nmemb,
						void*
							userdata
					)
					{
						return write_cb(pointer, size, nmemb, userdata);
					}
				);
				curl_easy_setopt(curl_handler, CURLOPT_WRITEDATA, response_body);
			}
			else
			{
				curl_easy_setopt(curl_handler, CURLOPT_NOBODY, 1L);
			}

			if (configurations.capture_headers)
			{
				curl_easy_setopt(
					curl_handler,
					CURLOPT_HEADERFUNCTION,
					[this](
						void*
							pointer,
						size_t
							size,
						size_t
							nmemb,
						void*
							userdata
						)
					{
						return header_cb(pointer, size, nmemb, userdata);
					}
				);
				curl_easy_setopt(curl_handler, CURLOPT_HEADERDATA, response_headers);
			}

			struct curl_slist* header_list = nullptr;
			for (auto& hstr : configurations.default_headers)
				header_list = curl_slist_append(header_list, hstr.c_str());

			if (!configurations.bearer_token.empty())
			{
				std::string auth = "Authorization: Bearer " + configurations.bearer_token;
				header_list = curl_slist_append(header_list, auth.c_str());
			}

			if (header_list) curl_easy_setopt(curl_handler, CURLOPT_HTTPHEADER, header_list);
			if (!body.empty())
			{
				curl_easy_setopt(curl_handler, CURLOPT_POSTFIELDS, body.c_str());
				curl_easy_setopt(curl_handler, CURLOPT_POSTFIELDSIZE, body.size());
			}

			CURLcode res = curl_easy_perform(curl_handler);
			if (header_list) curl_slist_free_all(header_list);

			curl_easy_getinfo(curl_handler, CURLINFO_RESPONSE_CODE, &response.status_code);

			if (configurations.capture_body)
			{
				response.body = std::move(response_body);
			}
			if (configurations.capture_headers)
			{
				response.headers = std::move(response_headers);
			}
			if (configurations.capture_telemetry)
			{
				setup_telemetry(curl_handler, response);
			}

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			if (configurations.suppress_exceptions)
			{
				response.status_code = 0;
				response.body = (configurations.capture_body) ? "Request failed" : "";
				
				return
					true;
			};

			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();			
		}
	}
		
	CURL*
		RestApiManager
			::acquire_handle()
	{
		try
		{			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			CURL* curl_handler = curl_pool[pool_next];
			pool_next = (pool_next + 1) % curl_pool.size();
			curl_easy_reset(curl_handler);

			if (!configurations.trusted_ca_bundle_file.empty())
			{
				curl_easy_setopt(
					curl_handler,
					CURLOPT_CAINFO,
					configurations
						.trusted_ca_bundle_file.c_str()
				);
			}

			if (!configurations.pinned_cert_file.empty())
			{
				curl_easy_setopt(
					curl_handler,
					CURLOPT_PINNEDPUBLICKEY,
					configurations
						.pinned_cert_file.c_str()
				);
			}

			return
				curl_handler;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();	
		}
	}

	size_t
		RestApiManager
			::write_cb(
				void*
					pointer,
				size_t
					size,
				size_t
					nmemb,
				void*
					userdata
			)
	{
		try
		{			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_3,
				pointer == nullptr ||
				size == 0 ||
				nmemb == 0 ||
				userdata == nullptr
			);	

			auto* str = static_cast<std::string*>(userdata);
			str->append(static_cast<char*>(pointer), size * nmemb);

			return
				size * nmemb;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }	
	}

	size_t
		RestApiManager
			::header_cb(
				void*
					pointer,
				size_t
					size,
				size_t
					nmemb,
				void*
					userdata
			)
	{
		try
		{		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_3,
				pointer == nullptr ||
				size == 0 ||
				nmemb == 0 ||
				userdata == nullptr
			);	

			auto* headers = static_cast<std::multimap<std::string, std::string>*>(userdata);
			std::string line(static_cast<char*>(pointer), size * nmemb);
			auto colon = line.find(':');
			if (colon != std::string::npos)
			{
				std::string key = line.substr(0, colon);
				std::string value = line.substr(colon + 1);
				value.erase(0, value.find_first_not_of(" \t\r\n"));
				value.erase(value.find_last_not_of(" \t\r\n") + 1);
				headers->emplace(std::move(key), std::move(value));
			}

			return
				size * nmemb;
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
		RestApiManager
			::setup_telemetry(
				CURL*
					curl_handler,
				RestApiManagerResponse& 
					response
			)
	{
		try
		{			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			curl_easy_getinfo(
				curl_handler,
				CURLINFO_TOTAL_TIME,
				&response.total_timestamp_in_nanoseconds
			);
			curl_easy_getinfo(
				curl_handler,
				CURLINFO_NAMELOOKUP_TIME,
				&response.dns_timestamp_in_nanoseconds
			);
			curl_easy_getinfo(
				curl_handler,
				CURLINFO_CONNECT_TIME,
				&response.connect_timestamp_in_nanoseconds
			);
			curl_easy_getinfo(
				curl_handler,
				CURLINFO_APPCONNECT_TIME,
				&response.tls_timestamp_in_nanoseconds
			);
			curl_easy_getinfo(
				curl_handler,
				CURLINFO_STARTTRANSFER_TIME,
				&response.start_transfer_timestamp_in_nanoseconds
			);

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

	std::string
		RestApiManager
			::setup_url(
				const std::string&
					base,
				const std::string&
					path
			)
	{
		try
		{					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				base.empty() ||
				path.empty()
			);			

			bool
				base_slash =
					base.back() == '/';
			bool
				path_slash =
					path.front() == '/';

			if (base_slash && path_slash)
			{
				return
					base + path.substr(1);
			}

			if (!base_slash && !path_slash)
			{
				return
					base + "/" + path;
			}

			return
				base + path;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}
}

#endif
