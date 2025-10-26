#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "utilities.hpp"
#include "abstract_value_extractor.hpp"

namespace QLogicaeCore
{
    class PlaceholderValueExtractor :
        public AbstractValueExtractor
    {
    public:
        PlaceholderValueExtractor();
        
        ~PlaceholderValueExtractor();
        
        PlaceholderValueExtractor(
            const std::string& value
        );
        
        PlaceholderValueExtractor(
            const PlaceholderValueExtractor&
                instance
        ) = delete;
        
        PlaceholderValueExtractor(
            PlaceholderValueExtractor&&
                instance
        ) noexcept = delete;
        
        PlaceholderValueExtractor& operator =
            (PlaceholderValueExtractor&&
                instance
        ) = delete;
        
        PlaceholderValueExtractor& operator =
            (const PlaceholderValueExtractor&
                instance
        ) = delete;

        bool setup();

        std::future<bool> setup_async();

        void setup_async(
            const std::function<void(const bool& result)>& callback
        );
        
        void setup(
            Result<void>& result
        );

        void setup_async(
            Result<std::future<void>>& result
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback
        );

        bool setup(
            const std::string& value
        );

        std::future<bool> setup_async(
            const std::string& value
        );

        void setup_async(
            Result<std::future<void>>& result,
            const std::string& value
        );

        void setup(
            Result<void>& result,
            const std::string& value
        );

        void setup_async(
            const std::function<void(const bool& result)>& callback,
            const std::string& value
        );
        
        void setup_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::string& value
        );

        std::optional<std::string> get_value();

        void get_value(
            Result<std::string>& result
        );

        static PlaceholderValueExtractor& get_instance();

        static void get_instance(
            Result<PlaceholderValueExtractor*>& result
        );

    protected:
        std::string _value;
    };

    inline static PlaceholderValueExtractor& PLACEHOLDER_VALUE_EXTRACTOR =
        PlaceholderValueExtractor::get_instance();
}
