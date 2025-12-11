#include "pch.hpp"

#include "../includes/function_wrapper.hpp"

namespace QLogicaeCppCore
{    
    FunctionWrapper::FunctionWrapper()
    {
        Result<bool> result;

        construct(result);
    }

    FunctionWrapper::~FunctionWrapper()
    {
        Result<bool> result;

        destruct(result);
    }

    void FunctionWrapper::construct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            true
        );
    }

    void FunctionWrapper::destruct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            true
        );
    }
}

