#pragma once

#include "result.hpp"
#include "instance_manager.hpp"

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
            Result<bool>& result,
            const std::function<void()>& callback
        );

        void complete_all_threads(
            Result<bool>& result
        );

    protected:
        std::mutex _mutex;

        std::shared_ptr<boost::asio::thread_pool> _THREAD_POOL;

    };

    inline static AsynchronousManager& ASYNCHRONOUS_MANAGER =
        INSTANCE_MANAGER.get_instance<AsynchronousManager>();
}
