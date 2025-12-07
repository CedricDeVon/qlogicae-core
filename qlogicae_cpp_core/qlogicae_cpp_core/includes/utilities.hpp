#pragma once

#include "result.hpp"
#include "instance_manager.hpp"

#include <boost/asio.hpp>

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

        int a = 101;

        void sum(Result<int>& result, int x, int y);
        
    protected:
        boost::asio::thread_pool _THREAD_POOL;
    };

    inline static Utilities& UTILITIES =
        INSTANCE_MANAGER.get_instance<Utilities>();
}
