#include "pch.hpp"

#include "../includes/asynchronous_manager.hpp"

namespace QLogicaeCppCore
{
    AsynchronousManager::AsynchronousManager()        
    {
        _THREAD_POOL =
            std::make_shared<boost::asio::thread_pool>(
                std::thread::hardware_concurrency()
            );
    }

    AsynchronousManager::~AsynchronousManager()
    {
        Result<bool> result;

        complete_all_threads(result);
    }

    void AsynchronousManager::begin_one_thread(
        Result<bool>& result,
        const std::function<void()>& callback
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        if (_THREAD_POOL == nullptr)
        {
            _THREAD_POOL =
                std::make_shared<boost::asio::thread_pool>(
                    std::thread::hardware_concurrency());
        }

        boost::asio::post(*_THREAD_POOL, callback);

        result.set_to_good_status_with_value(
            true
        );
    }

    void AsynchronousManager::complete_all_threads(
        Result<bool>& result
    )
    {
        std::shared_ptr<boost::asio::thread_pool> pool;

        {
            std::lock_guard<std::mutex> lock(_mutex);
            pool = _THREAD_POOL;
            _THREAD_POOL.reset();
        }

        if (pool)
        {
            pool->join();
        }

        result.set_to_good_status_with_value(
            true
        );
    }
}
