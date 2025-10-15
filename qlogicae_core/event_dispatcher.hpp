#pragma once

#include "result.hpp"

#include <map>             
#include <mutex>
#include <memory>
#include <vector>
#include <future> 
#include <utility>         
#include <typeindex>
#include <functional>      
#include <shared_mutex>    
#include <unordered_map>

namespace QLogicaeCore
{
    template <typename... EventTypes>
    class EventDispatcher
    {
    public:
        using EventVariant = std::variant<EventTypes...>;

        class SubscriptionHandle
        {
        public:
            ~SubscriptionHandle();
            
            SubscriptionHandle(
                const SubscriptionHandle&
            ) = delete;

            SubscriptionHandle(
                SubscriptionHandle&& other
            ) noexcept;
            
            SubscriptionHandle(
                std::function<void()> unsubscribe_callback
            );
            
            SubscriptionHandle& operator = (
                const SubscriptionHandle&
            ) = delete;

            SubscriptionHandle& operator = (
                SubscriptionHandle&& other
            ) noexcept;
            
            void unsubscribe();

        private:
            std::atomic<bool> _active;

            std::function<void()> _unsubscribe;
        };

        EventDispatcher();

        ~EventDispatcher();

        EventDispatcher(
            const EventDispatcher&
        ) = delete;

        EventDispatcher& operator = (
            const EventDispatcher&
        ) = delete;

        template <typename EventT>
        void dispatch(
            const EventT& event
        );

        template <typename EventT>
        void dispatch_async(
            const EventT& event
        );
        
        template <typename EventT>
        SubscriptionHandle subscribe(
            std::function<void(const EventT&)> callback
        );

        template <typename EventT>
        void dispatch(
            Result<void>& result,
            const EventT& event
        );

        template <typename EventT>
        void dispatch_async(
            Result<std::future<void>>& result,
            const EventT& event
        );

        template <typename EventT>
        void subscribe(
            Result<SubscriptionHandle>& result,
            std::function<void(const EventT&)> callback
        );

        template <typename EventT>
        void setup(
            Result<void>& result
        );

    private:
        mutable std::shared_mutex _mutex;
        
        using CallbackPtr = std::shared_ptr<void>;

        std::unordered_map<std::type_index, std::vector<CallbackPtr>> _listeners;
        
        template <typename T>
        static constexpr bool _is_event_type();
    };

    template <typename... EventTypes>
    template <typename EventT>
    void EventDispatcher<EventTypes...>::setup(
        Result<void>& result
    )
    {
        result.set_to_success();
    }

    template <typename... EventTypes>
    EventDispatcher<EventTypes...>::SubscriptionHandle::SubscriptionHandle(
        std::function<void()> unsubscribe_callback
    )
        : _unsubscribe(std::move(unsubscribe_callback)), _active(true)
    {    
    }

    template <typename... EventTypes>
    EventDispatcher<EventTypes...>::SubscriptionHandle::~SubscriptionHandle()
    {
        unsubscribe();
    }

    template <typename... EventTypes>
    void EventDispatcher<EventTypes...>::SubscriptionHandle::unsubscribe()
    {
        if (_active.exchange(false) && _unsubscribe)
        {
            _unsubscribe();
        }
    }

    template <typename... EventTypes>
    EventDispatcher<EventTypes...>::SubscriptionHandle::SubscriptionHandle(
        SubscriptionHandle&& other
    ) noexcept
        : _unsubscribe(
            std::move(other._unsubscribe)),
            _active(other._active.load()
          )
    {
        other._active = false;
    }

    template <typename... EventTypes>
    auto EventDispatcher<EventTypes...>::SubscriptionHandle::operator=(
        SubscriptionHandle&& other) noexcept
            -> SubscriptionHandle&
    {
        if (this != &other)
        {
            unsubscribe();
            _unsubscribe = std::move(other._unsubscribe);
            _active = other._active.load();
            other._active = false;
        }

        return *this;
    }

    template <typename... EventTypes>
    EventDispatcher<EventTypes...>::EventDispatcher() = default;

    template <typename... EventTypes>
    EventDispatcher<EventTypes...>::~EventDispatcher() = default;

    template <typename... EventTypes>
    template <typename EventT>
    auto EventDispatcher<EventTypes...>::subscribe(
        std::function<void(const EventT&)> callback) -> SubscriptionHandle
    {
        static_assert(_is_event_type<EventT>(), "Exception at EventDispatcher::subscribe(): EventT must be a valid EventType");

        const std::type_index index = typeid(EventT);
        auto callback_ptr =
            std::make_shared<std::function<void(const EventT&)>>(
                std::move(callback
            )
        );

        {
            std::unique_lock lock(_mutex);
            auto& listeners = _listeners[index];
            listeners.emplace_back(callback_ptr);
        }

        return SubscriptionHandle([this, callback_ptr, index]()
            {
                std::unique_lock lock(_mutex);
                auto& listeners = _listeners[index];
                listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
                    [&](const auto& ptr) { return ptr == callback_ptr; }),
                    listeners.end());
            }
        );
    }

    template <typename... EventTypes>
    template <typename EventT>
    void EventDispatcher<EventTypes...>::dispatch(
        const EventT& event
    )
    {
        static_assert(_is_event_type<EventT>(), "Exception at EventDispatcher::dispatch(): EventT must be a valid EventType");

        const std::type_index index = typeid(EventT);
        std::vector<std::shared_ptr<std::function<void(const EventT&)>>> callbacks_copy;

        {
            std::shared_lock lock(_mutex);

            auto listener = _listeners.find(index);
            if (listener != _listeners.end())
            {
                for (const auto& function_pointer : listener->second)
                {
                    callbacks_copy.push_back(
                        std::static_pointer_cast<std::function<void(
                            const EventT&)>>(function_pointer)
                    );
                }
            }
        }

        for (const auto& callback : callbacks_copy)
        {
            (*callback)(event);
        }
    }

    template <typename... EventTypes>
    template <typename EventT>
    void EventDispatcher<EventTypes...>::dispatch_async(const EventT& event)
    {
        static_assert(_is_event_type<EventT>(), "Exception at EventDispatcher::dispatch_async(): EventT must be a valid EventType");

        std::thread([this, event]()
            {
                dispatch(event);
            }
        ).detach();
    }

    template <typename... EventTypes>
    template <typename T>
    constexpr bool EventDispatcher<EventTypes...>::_is_event_type()
    {
        return (std::is_same_v<T, EventTypes> || ...);

    }

    template <typename... EventTypes>
    template <typename EventT>
    void EventDispatcher<EventTypes...>::subscribe(
        Result<SubscriptionHandle>& result,
        std::function<void(const EventT&)> callback)
    {        
        const std::type_index index = typeid(EventT);
        auto callback_ptr =
            std::make_shared<std::function<void(const EventT&)>>(
                std::move(callback
                )
            );

        {
            std::unique_lock lock(_mutex);
            auto& listeners = _listeners[index];
            listeners.emplace_back(callback_ptr);
        }

        result.set_to_success(SubscriptionHandle([this, callback_ptr, index]()
            {
                std::unique_lock lock(_mutex);
                auto& listeners = _listeners[index];
                listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
                    [&](const auto& ptr) { return ptr == callback_ptr; }),
                    listeners.end());
            }
        ));
    }

    template <typename... EventTypes>
    template <typename EventT>
    void EventDispatcher<EventTypes...>::dispatch(
        Result<void>& result,
        const EventT& event
    )
    {        
        const std::type_index index = typeid(EventT);
        std::vector<std::shared_ptr<std::function<void(const EventT&)>>> callbacks_copy;

        {
            std::shared_lock lock(_mutex);

            auto listener = _listeners.find(index);
            if (listener != _listeners.end())
            {
                for (const auto& function_pointer : listener->second)
                {
                    callbacks_copy.push_back(
                        std::static_pointer_cast<std::function<void(
                            const EventT&)>>(function_pointer)
                    );
                }
            }
        }

        for (const auto& callback : callbacks_copy)
        {
            (*callback)(event);
        }

        result.set_to_success();
    }

    template <typename... EventTypes>
    template <typename EventT>
    void EventDispatcher<EventTypes...>::dispatch_async(
        Result<std::future<void>>& result,
        const EventT& event
    )
    {
        result.set_to_success(std::thread([this, event]()
            {
                dispatch(event);
            }
        ).detach());        
    }
}
