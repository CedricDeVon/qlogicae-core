#pragma once

#include "task_priority.hpp"
#include "small_task_object.hpp"

namespace QLogicaeCore
{
    struct WorkerQueue
    {
        std::map<TaskPriority, std::queue<SmallTaskObject>> priority_queues;

        std::mutex queue_mutex;

        std::condition_variable wake_signal;
    };
}
