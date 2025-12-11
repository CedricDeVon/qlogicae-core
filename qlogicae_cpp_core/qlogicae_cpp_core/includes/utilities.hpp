#pragma once

#include "result.hpp"
#include "instance_manager.hpp"

namespace QLogicaeCppCore
{
    class Utilities
    {
    public:        
        Utilities();

        ~Utilities();

        Utilities(
            const Utilities& instance
        ) = delete;

        Utilities(
            Utilities&& instance
        ) noexcept = delete;

        Utilities& operator = (
            Utilities&& instance
        ) = delete;

        Utilities& operator = (
            const Utilities& instance
        ) = delete;

        void construct(
            Result<bool>& result
        );

        void destruct(
            Result<bool>& result
        );

        void sum(Result<int>& result, int x, int y);
    };

    inline static Utilities& UTILITIES =
        INSTANCE_MANAGER.get_instance<Utilities>();
}
