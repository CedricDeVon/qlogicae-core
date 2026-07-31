#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		NetworkPingManagerConfigurations \
	)

#include "network_ping_manager_response.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		NetworkPingManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<NetworkPingManagerConfigurations>
    {
	public:		
        std::string
			host_address =
				"1.1.1.1";

		TimeScaleUnit
			time_scale_unit =
				TimeScaleUnit
					::MILLISECONDS;

		std::chrono::milliseconds
			timeout =
				std::chrono::milliseconds { 1000 };

		NetworkPingManagerConfigurations();
    };
}

#endif
