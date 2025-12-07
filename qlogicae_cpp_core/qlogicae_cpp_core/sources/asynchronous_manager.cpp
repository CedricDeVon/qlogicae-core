#include "pch.hpp"

#include "../includes/asynchronous_manager.hpp"

namespace QLogicaeCppCore
{
    AsynchronousManager::AsynchronousManager() :
        _THREAD_POOL(std::thread::hardware_concurrency())
    {
        
    }

    AsynchronousManager::~AsynchronousManager()
    {

    }

    void AsynchronousManager::begin_one_thread(
        const std::function<void()>& callback
    )
    {
        try
        {
            boost::asio::post(
                _THREAD_POOL,
                callback
            );
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                exception.what()
            );
        }
    }

    void AsynchronousManager::complete_all_threads()
    {
        try
        {
            _THREAD_POOL.join();           
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                exception.what()
            );
        }
    }
}
