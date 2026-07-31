#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		PairHashOperator \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		PairHashOperator
    {
        std::size_t operator()(
            const std::pair<void*,
            std::string>& pair
        ) const noexcept
        {
            return std::hash<void*>{}(pair.first) ^
                (std::hash<std::string>{}(pair.second) << 1);
        }
    };
}

#endif
