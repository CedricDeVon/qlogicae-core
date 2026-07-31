#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		NetworkPingManager \
	)

#include "network_ping_manager_response.hpp"
#include "network_ping_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		NetworkPingManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<NetworkPingManagerConfigurations>
    {
    public:
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		NetworkPingManager();

		~NetworkPingManager();

		bool
			construct();

		bool
			destruct();

		NetworkPingManagerResponse
			get_icmp_ping(
				const std::string&
					host_address
			);

		NetworkPingManagerResponse
			get_icmp_ping();

		NetworkPingManagerResponse
			get_tcp_ping(
				const std::string&
					host_address
			);

		NetworkPingManagerResponse
			get_tcp_ping();

		double
			scale_duration(
				const std::chrono::nanoseconds&
					duration,
				const TimeScaleUnit&
					unit
		);
	};
}

#endif
