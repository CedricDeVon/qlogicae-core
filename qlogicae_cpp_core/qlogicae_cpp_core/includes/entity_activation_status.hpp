#pragma once

namespace QLogicaeCppCore
{
	enum class EntityActivationStatus :
		uint8_t
	{
		ACTIVE,

		INACTIVE,

		PENDING,

		NONE
	};
}
