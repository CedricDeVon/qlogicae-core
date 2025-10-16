#pragma once

#include <cstdint>

namespace QLogicaeCore
{
	enum class ResultStatus :
		uint8_t
	{
		GOOD,

		BAD,

		INFO,

		DEBUG,

		WARNING,

		EXCEPTION,

		ERROR_
	};
}
