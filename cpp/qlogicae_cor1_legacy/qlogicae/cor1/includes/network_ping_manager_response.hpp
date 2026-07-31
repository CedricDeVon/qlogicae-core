#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		NetworkPingManagerResponse \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		NetworkPingManagerResponse
	{
		double
			sent_duration;

		double
			receive_duration;

		double
			roundtrip_duration;
	};
}

#endif
