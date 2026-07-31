#pragma once

#include "result.hpp"
#include "utilities.hpp"
#include "worker_queue.hpp"
#include "task_priority.hpp"
#include "small_task_object.hpp"

namespace QLogicaeCore
{
    static thread_local std::size_t current_thread_index =
        std::numeric_limits<std::size_t>::max();

    class ThreadPool
    {
    public:
        explicit ThreadPool(
            std::size_t thread_count =
            std::thread::hardware_concurrency(),
            std::size_t max_queue_size = 1024
        );
        
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
            const TaskPriority& priority =
                TaskPriority::MEDIUM
        );
        
        std::size_t worker_count();
        
        std::size_t total_pending_tasks();
        
        static ThreadPool& get_instance();
        
        static std::size_t current_worker_index();

        void setup(
            Result<void>& result,
            std::size_t thread_count =
                std::thread::hardware_concurrency(),
            std::size_t max_queue_size = 1024
        );

        void worker_count(
            Result<std::size_t>& result
        );

        void total_pending_tasks(
            Result<std::size_t>& result
        );

        void get_instance(
            Result<ThreadPool*>& result
        );

        void current_worker_index(
            Result<std::size_t>& result
        );

        template <typename Callable>
        void enqueue(
            Result<bool>& result,
            Callable&& task,
            const TaskPriority& priority = TaskPriority::MEDIUM);

        template <typename Callable>
        void enqueue_task(
            Result<std::optional<std::future<void>>>& result,
            Callable&& task,
            const TaskPriority& priority = TaskPriority::MEDIUM);

    protected:
        std::size_t _max_queue_capacity;
        
        std::atomic<bool> _should_stop { false };
        
        std::vector<std::thread> _worker_threads;
        
        std::atomic<std::size_t> _round_robin_counter { 0 };
        
        std::atomic<std::size_t> _total_enqueued_tasks { 0 };
        
        std::vector<std::unique_ptr<WorkerQueue>> _worker_queues;

        void _worker_loop(const std::size_t& thread_index);
        
        bool _try_enqueue_to_worker(const std::size_t& worker_index,
            SmallTaskObject&& task,
            const TaskPriority& priority
        );
    };

    template <typename Callable>
    bool ThreadPool::enqueue(Callable&& task, const TaskPriority& priority)
    {
        if (_should_stop)
        {
            return false;
        }

        std::size_t worker_index =
            _round_robin_counter.fetch_add(1) % _worker_queues.size();
        return _try_enqueue_to_worker(worker_index,
            SmallTaskObject(std::forward<Callable>(task)),
            priority
        );
    }

    template <typename Callable>
    std::optional<std::future<void>> ThreadPool::enqueue_task(Callable&& task,
        const TaskPriority& priority)
    {
        if (_should_stop)
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

    template <typename Callable>
    void ThreadPool::enqueue(Result<bool>& result,
        Callable&& task,
        const TaskPriority& priority)
    {
        if (_should_stop)
        {
            result.set_to_bad_status_with_value(false);
            return;
        }

        std::size_t worker_index =
            _round_robin_counter.fetch_add(1) % _worker_queues.size();
        bool success = _try_enqueue_to_worker(worker_index,
            SmallTaskObject(std::forward<Callable>(task)),
            priority
        );

        result.set_to_good_status_with_value(success);
    }

    template <typename Callable>
    void ThreadPool::enqueue_task(Result<std::optional<std::future<void>>>& result,
        Callable&& task,
        const TaskPriority& priority)
    {
        if (_should_stop)
        {
            result.set_to_bad_status_with_value(std::nullopt);
            return;
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
            result.set_to_bad_status_with_value(std::nullopt);
            return;
        }

        result.set_to_good_status_with_value(task_future);
    }
}
