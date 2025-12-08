#pragma once

namespace QLogicaeCppCore
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
