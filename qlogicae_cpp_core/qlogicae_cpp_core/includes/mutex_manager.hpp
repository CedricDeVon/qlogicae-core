#pragma once

#include "result.hpp"
#include "instance_manager.hpp"
#include "pair_hash_operator.hpp"

namespace QLogicaeCppCore
{
    class MutexManager
    {
    public:
        MutexManager();

        ~MutexManager();

        MutexManager(
            const MutexManager& instance
        ) = delete;

        MutexManager(
            MutexManager&& instance
        ) noexcept = delete;

        MutexManager& operator = (
            MutexManager&& instance
        ) = delete;

        MutexManager& operator = (
            const MutexManager& instance
        ) = delete;

        void construct(
            Result<bool>& result
        );

        void destruct(
            Result<bool>& result
        );
       
    protected:
    };

    inline static MutexManager& MUTEX_MANAGER =
        InstanceManager::get_instance<MutexManager>();
}

/*
        std::unordered_map<std::pair<void*, std::string>, std::mutex, PairHashOperator> _mutex_table;

Lock a mutex for a particular object and name
auto& mtx = mutex_table[{this, "main"}];
std::scoped_lock lock(mtx);

Core Mutexes	        mutex, timed_mutex, recursive_mutex, recursive_timed_mutex
Shared Mutexes	        shared_mutex, shared_timed_mutex
Lock Wrappers	        lock_guard, unique_lock, shared_lock, scoped_lock
Lock Utilities	        lock, try_lock
Condition Variables	    condition_variable, condition_variable_any
Atomic Synchronization	atomic_flag, all atomic<T>
Other C++20 Sync Tools	latch, barrier, atomic_wait/notify, jthread

*/
