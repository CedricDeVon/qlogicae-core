#pragma once

#include "globals.hpp"

namespace QLogicaeCore
{
    static thread_local std::size_t current_thread_index =
        std::numeric_limits<std::size_t>::max();

    class ThreadPool
    {
    public:
        explicit ThreadPool(std::size_t thread_count =
            std::thread::hardware_concurrency(),
            std::size_t max_queue_size = 1024);
        
        ~ThreadPool();

        template <typename Callable>
        bool enqueue(
                Callable&& task,
                const TaskPriority& priority =
                    TaskPriority::MEDIUM
        );
        
        template <typename Callable>
        std::optional<std::future<void>> enqueue_task(
            Callable&& task,
            const TaskPriority& priority = TaskPriority::MEDIUM
        );
        
        std::size_t worker_count() const;
        
        std::size_t total_pending_tasks() const;
        
        static ThreadPool& get_instance();
        
        static std::size_t current_worker_index();

    protected:
        std::size_t max_queue_capacity;
        std::atomic<bool> should_stop{ false };
        std::vector<std::thread> worker_threads;
        std::atomic<std::size_t> round_robin_counter{ 0 };
        std::atomic<std::size_t> total_enqueued_tasks{ 0 };
        std::vector<std::unique_ptr<WorkerQueue>> worker_queues;

        void worker_loop(const std::size_t& thread_index);
        
        bool try_enqueue_to_worker(const std::size_t& worker_index,
            SmallTaskObject&& task,
            const TaskPriority& priority
        );
    };

    template <typename Callable>
    bool ThreadPool::enqueue(Callable&& task, const TaskPriority& priority)
    {
        if (should_stop)
        {
            return false;
        }

        std::size_t worker_index =
            round_robin_counter.fetch_add(1) % worker_queues.size();
        return try_enqueue_to_worker(worker_index,
            SmallTaskObject(std::forward<Callable>(task)),
            priority
        );
    }

    template <typename Callable>
    std::optional<std::future<void>> ThreadPool::enqueue_task(Callable&& task,
        const TaskPriority& priority)
    {
        if (should_stop)
        {
            return std::nullopt;
        }

        std::shared_ptr<std::promise<void>> task_promise =
            std::make_shared<std::promise<void>>();
        std::future<void> task_future = task_promise->get_future();

        bool success = enqueue(
            [task = std::forward<Callable>(task), task_promise]() mutable
            {
                try
                {
                    task();
                    task_promise->set_value();
                }
                catch (...)
                {
                    task_promise->set_exception(std::current_exception());
                }
            },
            priority
        );

        if (!success)
        {
            return std::nullopt;
        }

        return task_future;
    }
}
