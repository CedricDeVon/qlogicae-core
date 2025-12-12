#pragma once

#include "result.hpp"
#include "instance_manager.hpp"
#include "pair_hash_operator.hpp"

namespace QLogicaeCppCore
{
    template<typename LockType, typename MutexType>
    concept ValidLock =
        (std::is_same_v<LockType, std::unique_lock<MutexType>> ||
            std::is_same_v<LockType, std::shared_lock<MutexType>>);

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

        template<typename LockType, typename MutexType>
        void lock_mutex(
            Result<bool>& result,
            const void* pointer
        ) requires ValidLock<LockType, MutexType>;

        template<typename LockType, typename MutexType>
        void lock_mutex(
            Result<bool>& result,
            const void* pointer,
            const std::string_view& name
        ) requires ValidLock<LockType, MutexType>;

        std::unordered_map<std::pair<void*, std::string>, std::mutex, PairHashOperator>
            MUTEX_COLLECTION;

        std::unordered_map<std::pair<void*, std::string>, std::timed_mutex, PairHashOperator>
            TIMED_MUTEX_COLLECTION;

        std::unordered_map<std::pair<void*, std::string>, std::recursive_mutex, PairHashOperator>
            RECURSIVE_MUTEX_COLLECTION;

        std::unordered_map<std::pair<void*, std::string>, std::recursive_timed_mutex, PairHashOperator>
            RECURSIVE_TIMED_MUTEX_COLLECTION;

        std::unordered_map<std::pair<void*, std::string>, std::shared_mutex, PairHashOperator>
            SHARED_MUTEX_COLLECTION;

        std::unordered_map<std::pair<void*, std::string>, std::recursive_timed_mutex, PairHashOperator>
            SHARED_TIMED_MUTEX_COLLECTION;
    };

    template<typename LockType, typename MutexType>
    void MutexManager::lock_mutex(
        Result<bool>& result,
        const void* pointer
    ) requires ValidLock<LockType, MutexType>
    {
        lock_mutex<LockType, MutexType>(
            result,
            pointer,
            "static"
        );
    }

    template<typename LockType, typename MutexType>
    void MutexManager::lock_mutex(
        Result<bool>& result,
        const void* pointer,
        const std::string_view& name
    ) requires ValidLock<LockType, MutexType>
    {
        MutexType* mutex_ptr = nullptr;
        void* ptr = const_cast<void*>(pointer);
        std::string key_name{ name };

        if constexpr (std::is_same_v<MutexType, std::mutex>)
        {
            mutex_ptr = &MUTEX_COLLECTION[{ptr, key_name}];
        }
        else if constexpr (std::is_same_v<MutexType, std::timed_mutex>)
        {
            mutex_ptr = &TIMED_MUTEX_COLLECTION[{ptr, key_name}];
        }
        else if constexpr (std::is_same_v<MutexType, std::recursive_mutex>)
        {
            mutex_ptr = &RECURSIVE_MUTEX_COLLECTION[{ptr, key_name}];
        }
        else if constexpr (std::is_same_v<MutexType, std::recursive_timed_mutex>)
        {
            mutex_ptr = &RECURSIVE_TIMED_MUTEX_COLLECTION[{ptr, key_name}];
        }
        else if constexpr (std::is_same_v<MutexType, std::shared_mutex>)
        {
            mutex_ptr = &SHARED_MUTEX_COLLECTION[{ptr, key_name}];
        }
        else if constexpr (std::is_same_v<MutexType, std::recursive_timed_mutex>)
        {
            mutex_ptr = &SHARED_MUTEX_COLLECTION[{ptr, key_name}];
        }
        else
        {
            result.set_to_bad_status_with_value(false);
            return;
        }

        LockType lock(*mutex_ptr);
        result.set_to_good_status_with_value(true);
    }

    inline static MutexManager& MUTEX_MANAGER =
        InstanceManager::get_instance<MutexManager>();
}
