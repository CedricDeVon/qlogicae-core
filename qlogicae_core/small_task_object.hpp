#pragma once

namespace QLogicaeCore
{
    struct SmallTaskObject
    {
        SmallTaskObject() = default;

        template <typename Callable>
        SmallTaskObject(Callable&& callable)
        {
            function_wrapper = [callable =
                std::forward<Callable>(callable)]() mutable
                {
                    callable();
                };
        }

        void operator()() const
        {
            function_wrapper();
        }

        std::function<void()> function_wrapper;
    };
}
