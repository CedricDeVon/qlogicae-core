#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		StateManagerItem \
	)

namespace
    QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		StateManagerItem
	{
	public:		
		std::string
			key =
				{};

		std::any
			current_value =
				{};

		std::any
			initial_value =
				{};

		std::unordered_map<std::string, std::function<std::any()>>
			signals =
				{};
	};
}

#endif
