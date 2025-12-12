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

        std::unordered_map<std::pair<std::shared_ptr<void>, std::string>, std::mutex, PairHashOperator>
            MUTEX_COLLECTION;

        std::unordered_map<std::pair<std::shared_ptr<void>, std::string>, std::timed_mutex, PairHashOperator>
            TIMED_MUTEX_COLLECTION;

        std::unordered_map<std::pair<std::shared_ptr<void>, std::string>, std::recursive_mutex, PairHashOperator>
            RECURSIVE_MUTEX_COLLECTION;

        std::unordered_map<std::pair<std::shared_ptr<void>, std::string>, std::recursive_timed_mutex, PairHashOperator>
            RECURSIVE_TIMED_MUTEX_COLLECTION;

        std::unordered_map<std::pair<std::shared_ptr<void>, std::string>, std::shared_mutex, PairHashOperator>
            SHARED_MUTEX_COLLECTION;

        std::unordered_map<std::pair<std::shared_ptr<void>, std::string>, std::recursive_timed_mutex, PairHashOperator>
            SHARED_TIMED_MUTEX_COLLECTION;
    };

    inline static MutexManager& MUTEX_MANAGER =
        InstanceManager::get_instance<MutexManager>();
}
