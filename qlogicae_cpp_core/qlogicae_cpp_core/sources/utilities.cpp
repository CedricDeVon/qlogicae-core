#include "pch.hpp"

#include "../includes/utilities.hpp"

namespace QLogicaeCppCore
{
    Utilities::Utilities()
    {
        Result<bool> result;

        construct(result);
    }

    Utilities::~Utilities()
    {
        Result<bool> result;

        destruct(result);
    }

    void Utilities::construct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            true
        );
    }

    void Utilities::destruct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            true
        );
    }

	void Utilities::sum(Result<int>& result, int x, int y)
	{
		result.set_to_good_status_with_value(x + y);
	}
}
