#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonKeyIndexHashHandler \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		JsonKeyIndexHashHandler
	{
		size_t operator()(const std::vector<std::variant<std::string, size_t>>& vec) const
		{
			size_t seed = 0;
			for (const auto& elem : vec)
			{
				seed ^= std::visit([](auto&& val) {
					return std::hash<std::decay_t<decltype(val)>>{}(val);
					}, elem) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			}

			return
				seed;
		}
	};
}

#endif
