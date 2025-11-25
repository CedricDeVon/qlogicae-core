#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationLanguage :
        public AbstractApplication
    {
    public:
        bool setup();

        std::future<bool> setup_async(
            const std::function<void(const bool& result)>& callback =
            [](const bool& result) {}
        );

        void setup(
            Result<void>& result
        );

        void setup_async(
            Result<std::future<void>>& result,
            const std::function<void(Result<void>& result)>& callback =
            [](Result<void>& result) {}
        );



        bool is_language_found(
            const std::string& language_name
        );

        void is_language_found(
            Result<void>& result,
            const std::string& language_name
        );

        bool is_language_key_found(
            const std::string& language_name,
            const std::string& key
        );

        void is_language_key_found(
            Result<void>& result,
            const std::string& language_name,
            const std::string& key
        );



        bool load(
            const std::string& langauge_name
        );

        void load(
            Result<void>& result,
            const std::string& langauge_name
        );

        std::future<bool> load_async(
            const std::string& langauge_name
        );

        void load_async(
            const std::function<void(const bool& result)>& callback,
            const std::string& langauge_name
        );

        void load_async(
            Result<std::future<void>>& result,
            const std::string& langauge_name
        );

        void load_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::string& langauge_name
        );



        bool unload(
            const std::string& langauge_name
        );

        void unload(
            Result<void>& result,
            const std::string& langauge_name
        );

        std::future<bool> unload_async(
            const std::string& langauge_name
        );

        void unload_async(
            const std::function<void(const bool& result)>& callback,
            const std::string& langauge_name
        );

        void unload_async(
            Result<std::future<void>>& result,
            const std::string& langauge_name
        );

        void unload_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::string& langauge_name
        );



        std::string read_one(
            const std::string& language_name,
            const std::string& key
        );

        void read_one(
            Result<std::string>& result,
            const std::string& language_name,
            const std::string& key
        );

        std::future<std::string> read_one_async(
            const std::string& language_name,
            const std::string& key
        );

        void read_one_async(
            const std::function<void(const std::string& result)>& callback,
            const std::string& language_name,
            const std::string& key
        );

        void read_one_async(
            Result<std::future<std::string>>& result,
            const std::string& language_name,
            const std::string& key
        );

        void read_one_async(
            const std::function<void(Result<std::string>& result)>& callback,
            const std::string& language_name,
            const std::string& key
        );

        std::unordered_map<std::string, std::string> read_all(
            const std::string& language_name
        );

        void read_all(
            Result<std::unordered_map<std::string, std::string>>& result,
            const std::string& language_name
        );

        std::future<std::unordered_map<std::string, std::string>> read_all_async(
            const std::string& language_name
        );

        void read_all_async(
            const std::function<void(const std::unordered_map<std::string, std::string>& result)>& callback,
            const std::string& language_name
        );

        void read_all_async(
            Result<std::future<std::unordered_map<std::string, std::string>>>& result,
            const std::string& language_name
        );

        void read_all_async(
            const std::function<void(Result<std::unordered_map<std::string, std::string>>& result)>& callback,
            const std::string& language_name
        );


        bool terminate();

        std::future<bool> terminate_async(
            const std::function<void(const bool& result)>& callback =
            [](const bool& result) {}
        );

        void terminate(
            Result<void>& result
        );

        void terminate_async(
            Result<std::future<void>>& result,
            const std::function<void(Result<void>& result)>& callback =
            [](Result<void>& result) {}
        );

        static ApplicationLanguage& get_instance();

        static void get_instance(
            Result<ApplicationLanguage*>& result
        );

    protected:
        ApplicationLanguage();

        ~ApplicationLanguage();

        ApplicationLanguage(
            const ApplicationLanguage& instance
        ) = default;

        ApplicationLanguage(
            ApplicationLanguage&& instance
        ) noexcept = delete;

        ApplicationLanguage& operator = (
            ApplicationLanguage&& instance
        ) = default;

        ApplicationLanguage& operator = (
            const ApplicationLanguage& instance
        ) = delete;
    };

    inline static ApplicationLanguage& QLOGICAE_APPLICATION_LANGUAGE =
        ApplicationLanguage::get_instance();
}

