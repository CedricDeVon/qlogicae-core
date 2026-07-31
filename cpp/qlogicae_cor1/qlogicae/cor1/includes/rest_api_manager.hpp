#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RestApiManager \
	)

#include "rest_api_manager_response.hpp"
#include "rest_api_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		RestApiManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RestApiManagerConfigurations>
    {
    public:      
		std::vector<CURL*>
			curl_pool;

		size_t
			pool_next;

		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_3
		);

		RestApiManager();

		~RestApiManager();

		bool
			construct();

		bool
			destruct();

		RestApiManagerResponse
			execute_get_request(
				const std::string&
					path
			);

		RestApiManagerResponse
			execute_post_request(
				const std::string&
					path,
				const std::string&
					body
			);

		RestApiManagerResponse
			execute_put_request(
				const std::string&
					path,
				const std::string&
					body
			);

		RestApiManagerResponse
			execute_del_request(
				const std::string&
					path
			);

		RestApiManagerResponse
			execute_head_request(
				const std::string&
					path
			);

		RestApiManagerResponse
			execute_options_request(
				const std::string&
					path
			);

		RestApiManagerResponse
			execute_raw_request(
				const std::string&
					method,
				const std::string&
					path,
				const std::string&
					body
			);

		bool
			execute_request(
				RestApiManagerResponse&
					response,
				const std::string&
					method,
				const std::string&
					path,
				const std::string&
					body
			);

		CURL*
			acquire_handle();

		bool
			setup_telemetry(
				CURL*
					curl_handler,
				RestApiManagerResponse& 
					response
			);

		std::string
			setup_url(
				const std::string&
					base,
				const std::string&
					path
			);

		size_t
			write_cb(
				void*
					pointer,
				size_t
					size,
				size_t
					nmemb,
				void*
					userdata
			);

		size_t
			header_cb(
				void*
					pointer,
				size_t
					size,
				size_t
					nmemb,
				void*
					userdata
			);
    };    
}

#endif
