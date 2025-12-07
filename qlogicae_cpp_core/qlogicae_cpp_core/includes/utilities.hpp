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

        boost::asio::thread_pool THREAD_POOL;

        int a = 101;

        void sum(Result<int>& result, int x, int y);        
    };

    inline static Utilities& UTILITIES =
        INSTANCE_MANAGER.get_instance<Utilities>();
}
