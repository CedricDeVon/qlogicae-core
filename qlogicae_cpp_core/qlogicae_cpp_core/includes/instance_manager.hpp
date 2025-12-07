#pragma once

#include "result.hpp"

namespace QLogicaeCppCore
{
    class InstanceManager
    {
    public:
        InstanceManager();

        ~InstanceManager();

        InstanceManager(
            const InstanceManager& instance
        ) = delete;

        InstanceManager(
            InstanceManager&& instance
        ) noexcept = delete;

        InstanceManager& operator = (
            InstanceManager&& instance
            ) = delete;

        InstanceManager& operator = (
            const InstanceManager& instance
            ) = delete;

        template <typename Type>
        static Type& get_instance();

        template <typename Type>
        static void get_instance(
            Result<Type*>& result
        );
    };

    template <typename Type>
    Type& InstanceManager::get_instance()
    {
        Type* result_value;
        Result<Type*> result;

        get_instance(result);
        result.get_value(result_value);

        return *result_value;
    }

    template <typename Type>
    void InstanceManager::get_instance(
        Result<Type*>& result
    )
    {
        static Type instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }

    inline static InstanceManager& INSTANCE_MANAGER =
        InstanceManager::get_instance<InstanceManager>();
}
