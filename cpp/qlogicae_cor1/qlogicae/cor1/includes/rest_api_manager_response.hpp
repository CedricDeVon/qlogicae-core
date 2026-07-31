#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RestApiManagerResponse \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		RestApiManagerResponse
	{
	public:	
		double
			total_timestamp_in_nanoseconds =
				0.0;

		double
			dns_timestamp_in_nanoseconds =
				0.0;

		double
			connect_timestamp_in_nanoseconds =
				0.0;

		double
			tls_timestamp_in_nanoseconds =
				0.0;

		double
			start_transfer_timestamp_in_nanoseconds =
				0.0;

		long int
			status_code =
				0;

		std::string
			body =
				"";

		std::multimap<std::string, std::string>
			headers =
				{};
	};
}

#endif
