#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		VectorStringHashHandler \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		VectorStringHashHandler
	{
		std::size_t operator()(
			const std::vector<std::string>&
				values
			) const
		{
			std::size_t
				seed =
					values.size();

			for
			(
				const auto&
					value :
					values
			)
			{
				seed ^=
					std::hash<std::string>{}(value)
					+ 0x9e3779b9 + (seed << 6) + (seed >> 2);
			}

			return
				seed;
		}			
	};

	struct
		VectorStringEqualHandler
	{
		bool operator()(const std::vector<std::string>& a,
			const std::vector<std::string>& b) const
		{
			return a == b;
		}
	};
}

#endif
