#pragma once

#include <cstdint>

namespace QLogicaeCppCore
{
	enum class EntityActivationStatus :
		uint8_t
	{
		ACTIVE,

		INACTIVE,

		PENDING
	};
}
