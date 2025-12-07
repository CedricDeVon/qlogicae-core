#pragma once

#include "result.hpp"
#include "instance_manager.hpp"

#include <boost/asio.hpp>
#include <boost/thread/thread_pool.hpp>

#include <functional>

namespace QLogicaeCppCore
{
    class AsynchronousManager
    {
    public:
        AsynchronousManager();

        ~AsynchronousManager();

        AsynchronousManager(
            const AsynchronousManager& instance
        ) = delete;

        AsynchronousManager(
            AsynchronousManager&& instance
        ) noexcept = delete;

        AsynchronousManager& operator = (
            AsynchronousManager&& instance
            ) = delete;

        AsynchronousManager& operator = (
            const AsynchronousManager& instance
            ) = delete;

        void begin_one_thread(
            const std::function<void()>& callback
        );

        void complete_all_threads();

    protected:
        boost::asio::thread_pool _THREAD_POOL;

    };

    inline static AsynchronousManager& ASYNCHRONOUS_MANAGER =
        INSTANCE_MANAGER.get_instance<AsynchronousManager>();
}
