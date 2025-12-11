#include "pch.hpp"

#include "../includes/mutex_manager.hpp"

namespace QLogicaeCppCore
{
    MutexManager::MutexManager()
    {
        Result<bool> result;

        construct(result);
    }

    MutexManager::~MutexManager()
    {
        Result<bool> result;

        destruct(result);
    }

    void MutexManager::construct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            true
        );
    }

    void MutexManager::destruct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            true
        );
    }
}
