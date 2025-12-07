#include "pch.hpp"

#include "../includes/utilities.hpp"

namespace QLogicaeCppCore
{
	Utilities::Utilities()
	{

	}

	Utilities::~Utilities()
	{

	}

	void Utilities::sum(Result<int>& result, int x, int y)
	{
		result.set_to_good_status_with_value(x + y);
	}
}

