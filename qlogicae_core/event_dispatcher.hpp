#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    template <typename... EventTypes>
    class EventDispatcher {
    public:
        using EventVariant = std::variant<EventTypes...>;

        class SubscriptionHandle {
        public:
            SubscriptionHandle(std::function<void()> unsubscribe_fn);
            ~SubscriptionHandle();

            void unsubscribe();

            SubscriptionHandle(const SubscriptionHandle&) = delete;
            SubscriptionHandle& operator=(const SubscriptionHandle&) = delete;

            SubscriptionHandle(SubscriptionHandle&& other) noexcept;
            SubscriptionHandle& operator=(SubscriptionHandle&& other) noexcept;

        private:
            std::function<void()> _unsubscribe;
            std::atomic<bool> _active;
        };

        EventDispatcher();
        ~EventDispatcher();

        EventDispatcher(const EventDispatcher&) = delete;
        EventDispatcher& operator=(const EventDispatcher&) = delete;

        template <typename EventT>
        SubscriptionHandle subscribe(std::function<void(const EventT&)> callback);

        template <typename EventT>
        void dispatch(const EventT& event);

        template <typename EventT>
        void dispatch_async(const EventT& event);

    private:
        template <typename T>
        static constexpr bool is_event_type();

        using CallbackPtr = std::shared_ptr<void>;
        std::unordered_map<std::type_index, std::vector<CallbackPtr>> _listeners;
        mutable std::shared_mutex _mutex;
    };

    template <typename... EventTypes>
    EventDispatcher<EventTypes...>::SubscriptionHandle::SubscriptionHandle(std::function<void()> unsubscribe_fn)
        : _unsubscribe(std::move(unsubscribe_fn)), _active(true) {
    }

    template <typename... EventTypes>
    EventDispatcher<EventTypes...>::SubscriptionHandle::~SubscriptionHandle() {
        unsubscribe();
    }

    template <typename... EventTypes>
    void EventDispatcher<EventTypes...>::SubscriptionHandle::unsubscribe() {
        if (_active.exchange(false) && _unsubscribe)
            _unsubscribe();
    }

    template <typename... EventTypes>
    EventDispatcher<EventTypes...>::SubscriptionHandle::SubscriptionHandle(SubscriptionHandle&& other) noexcept
        : _unsubscribe(std::move(other._unsubscribe)), _active(other._active.load()) {
        other._active = false;
    }

    template <typename... EventTypes>
    auto EventDispatcher<EventTypes...>::SubscriptionHandle::operator=(SubscriptionHandle&& other) noexcept
        -> SubscriptionHandle& {
        if (this != &other) {
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
    auto EventDispatcher<EventTypes...>::subscribe(std::function<void(const EventT&)> callback) -> SubscriptionHandle {
        static_assert(is_event_type<EventT>(), "EventT must be a valid EventType");

        const std::type_index index = typeid(EventT);
        auto callback_ptr = std::make_shared<std::function<void(const EventT&)>>(std::move(callback));

        {
            std::unique_lock lock(_mutex);
            auto& listeners = _listeners[index];
            listeners.emplace_back(callback_ptr);
        }

        return SubscriptionHandle([this, callback_ptr, index]() {
            std::unique_lock lock(_mutex);
            auto& listeners = _listeners[index];
            listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
                [&](const auto& ptr) { return ptr == callback_ptr; }),
                listeners.end());
            });
    }

    template <typename... EventTypes>
    template <typename EventT>
    void EventDispatcher<EventTypes...>::dispatch(const EventT& event) {
        static_assert(is_event_type<EventT>(), "EventT must be a valid EventType");

        const std::type_index index = typeid(EventT);
        std::vector<std::shared_ptr<std::function<void(const EventT&)>>> callbacks_copy;

        {
            std::shared_lock lock(_mutex);
            auto it = _listeners.find(index);
            if (it != _listeners.end()) {
                for (const auto& fn_ptr : it->second) {
                    callbacks_copy.push_back(std::static_pointer_cast<std::function<void(const EventT&)>>(fn_ptr));
                }
            }
        }

        for (const auto& cb : callbacks_copy) {
            (*cb)(event);
        }
    }

    template <typename... EventTypes>
    template <typename EventT>
    void EventDispatcher<EventTypes...>::dispatch_async(const EventT& event) {
        static_assert(is_event_type<EventT>(), "EventT must be a valid EventType");

        std::thread([this, event]() {
            dispatch(event);
            }).detach();
    }

    template <typename... EventTypes>
    template <typename T>
    constexpr bool EventDispatcher<EventTypes...>::is_event_type() {
        return (std::is_same_v<T, EventTypes> || ...);
    }

}
