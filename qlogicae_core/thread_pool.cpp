#include "pch.h"

#include "thread_pool.hpp"

namespace QLogicaeCore
{
    ThreadPool::ThreadPool(std::size_t thread_count,
        std::size_t max_queue_size)
        : max_queue_capacity(max_queue_size)
    {
        thread_count = std::max<std::size_t>(1, thread_count);
        worker_queues.reserve(thread_count);
        worker_threads.reserve(thread_count);

        for (std::size_t i = 0; i < thread_count; ++i)
        {
            worker_queues.emplace_back(std::make_unique<WorkerQueue>());
            worker_threads.emplace_back([this, i]()
                {
                    worker_loop(i);
                });
        }
    }

    ThreadPool::~ThreadPool()
    {
        should_stop = true;

        for (std::unique_ptr<WorkerQueue>& queue : worker_queues)
        {
            std::lock_guard<std::mutex> lock(queue->queue_mutex);
            queue->wake_signal.notify_all();
        }

        for (std::thread& thread : worker_threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }
    
    ThreadPool& ThreadPool::get_instance()
    {
        static ThreadPool global_thread_pool(
            std::thread::hardware_concurrency(), 4096);
        return global_thread_pool;
    }

    std::size_t ThreadPool::current_worker_index()
    {
        return current_thread_index;
    }

    bool ThreadPool::try_enqueue_to_worker(const std::size_t& worker_index,
        SmallTaskObject&& task,
        const TaskPriority& priority
    )
    {
        try
        {
            std::unique_ptr<WorkerQueue>& queue = worker_queues[worker_index];
            std::lock_guard<std::mutex> lock(queue->queue_mutex);

            std::size_t queue_size = 0;
            for (const auto& [_, priority_queue] : queue->priority_queues)
            {
                queue_size += priority_queue.size();
            }

            if (queue_size >= max_queue_capacity)
            {
                return false;
            }

            queue->priority_queues[priority].push(std::move(task));
            ++total_enqueued_tasks;
            queue->wake_signal.notify_one();
            
            return true;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at ThreadPool::get_instance(): " + exception.what());
        }

    }

    void ThreadPool::worker_loop(const std::size_t& thread_index)
    {
        try
        {
            current_thread_index = thread_index;

            std::unique_ptr<WorkerQueue>& local_queue =
                worker_queues[thread_index];
            const std::size_t total_workers = worker_queues.size();

            while (!should_stop)
            {
                SmallTaskObject task_object;
                bool task_found = false;

                {
                    std::unique_lock<std::mutex> lock(local_queue->queue_mutex);

                    local_queue->wake_signal.wait(lock, [&]()
                        {
                            for (const auto& [_, queue] : local_queue->priority_queues)
                            {
                                if (!queue.empty())
                                {
                                    return true;
                                }
                            }
                            return should_stop.load();
                        });

                    if (should_stop)
                    {
                        return;
                    }

                    for (auto& [_, queue] : local_queue->priority_queues)
                    {
                        if (!queue.empty())
                        {
                            task_object = std::move(queue.front());
                            queue.pop();
                            task_found = true;
                            break;
                        }
                    }
                }

                if (task_found)
                {
                    task_object();
                }
                else
                {
                    for (std::size_t i = 0; i < total_workers; ++i)
                    {
                        if (i == thread_index)
                        {
                            continue;
                        }

                        std::unique_ptr<WorkerQueue>& neighbor_queue =
                            worker_queues[i];
                        std::lock_guard<std::mutex> neighbor_lock(
                            neighbor_queue->queue_mutex);

                        for (auto& [_, queue] : neighbor_queue->priority_queues)
                        {
                            if (!queue.empty())
                            {
                                task_object = std::move(queue.front());
                                queue.pop();
                                task_found = true;
                                break;
                            }
                        }

                        if (task_found)
                        {
                            break;
                        }
                    }

                    if (task_found)
                    {
                        task_object();
                    }
                    else
                    {
                        std::this_thread::yield();
                    }
                }
            }
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at ThreadPool::worker_loop(): " + exception.what());
        }
    }

    std::size_t ThreadPool::total_pending_tasks() const
    {
        try
        {
            std::size_t total = 0;

            for (const std::unique_ptr<WorkerQueue>& queue : worker_queues)
            {
                std::lock_guard<std::mutex> lock(queue->queue_mutex);
                for (const auto& [_, q] : queue->priority_queues)
                {
                    total += q.size();
                }
            }

            return total;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at ThreadPool::total_pending_tasks(): " + exception.what());
        }
    }

    std::size_t ThreadPool::worker_count() const
    {
        try
        {
            return worker_queues.size();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at ThreadPool::worker_count(): " + exception.what());
        }
    }
}
