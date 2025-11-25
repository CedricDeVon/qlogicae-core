#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "utilities.hpp"
#include "rocksdb_database.hpp"
#include "application_utilities.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    struct ApplicationCacheConfigurations
    {

    };

    class ApplicationCache :
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



        bool is_cache_found(
            const std::string& cache_name
        );

        void is_cache_found(
            Result<void>& result,
            const std::string& cache_name
        );

        bool is_cache_key_path_found(
            const std::string& cache_name,
            const std::string& key_path
        );

        void is_cache_key_path_found(
            Result<void>& result,
            const std::string& cache_name,
            const std::string& key_path
        );

        ApplicationCacheConfigurations get_configurations();

        void get_configurations(
            Result<ApplicationCacheConfigurations>& result
        );



        bool load();

        void load(
            Result<void>& result
        );

        std::future<bool> load_async();

        void load_async(
            const std::function<void(const bool& result)>& callback
        );

        void load_async(
            Result<std::future<void>>& result
        );

        void load_async(
            const std::function<void(Result<void>& result)>& callback
        );



        bool unload();

        void unload(
            Result<void>& result
        );

        std::future<bool> unload_async();

        void unload_async(
            const std::function<void(const bool& result)>& callback
        );

        void unload_async(
            Result<std::future<void>>& result
        );

        void unload_async(
            const std::function<void(Result<void>& result)>& callback
        );



        std::string read_one(
            const std::string& cache_name,
            const std::string& key_path
        );

        void read_one(
            Result<std::string>& result,
            const std::string& cache_name,
            const std::string& key_path
        );

        std::future<std::string> read_one_async(
            const std::string& cache_name,
            const std::string& key_path
        );

        void read_one_async(
            const std::function<void(const std::string& result)>& callback,
            const std::string& cache_name,
            const std::string& key_path
        );

        void read_one_async(
            Result<std::future<std::string>>& result,
            const std::string& cache_name,
            const std::string& key_path
        );

        void read_one_async(
            const std::function<void(Result<std::string>& result)>& callback,
            const std::string& cache_name,
            const std::string& key_path
        );

        std::unordered_map<std::string, std::string> read_all(
            const std::string& cache_name
        );

        void read_all(
            Result<std::unordered_map<std::string, std::string>>& result,
            const std::string& cache_name
        );

        std::future<std::unordered_map<std::string, std::string>> read_all_async(
            const std::string& cache_name
        );

        void read_all_async(
            const std::function<void(const std::unordered_map<std::string, std::string>& result)>& callback,
            const std::string& cache_name
        );

        void read_all_async(
            Result<std::future<std::unordered_map<std::string, std::string>>>& result,
            const std::string& cache_name
        );

        void read_all_async(
            const std::function<void(Result<std::unordered_map<std::string, std::string>>& result)>& callback,
            const std::string& cache_name
        );



        bool update_one(
            const std::string& cache_name,
            const std::string& key_path,
            const std::string& value
        );

        void update_one(
            Result<void>& result,
            const std::string& cache_name,
            const std::string& key_path,
            const std::string& value
        );

        std::future<bool> update_one_async(
            const std::string& cache_name,
            const std::string& key_path,
            const std::string& value
        );

        void update_one_async(
            const std::function<void(const bool& result)>& callback,
            const std::string& cache_name,
            const std::string& key_path,
            const std::string& value
        );

        void update_one_async(
            Result<std::future<void>>& result,
            const std::string& cache_name,
            const std::string& key_path,
            const std::string& value
        );

        void update_one_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::string& cache_name,
            const std::string& key_path,
            const std::string& value
        );

        bool update_all(
            const std::string& cache_name,
            const std::string& value
        );

        void update_all(
            Result<void>& result,
            const std::string& cache_name,
            const std::string& value
        );

        std::future<bool> update_all_async(
            const std::string& cache_name,
            const std::string& value
        );

        void update_all_async(
            const std::function<void(const bool& result)>& callback,
            const std::string& cache_name,
            const std::string& value
        );

        void update_all_async(
            Result<std::future<void>>& result,
            const std::string& cache_name,
            const std::string& value
        );

        void update_all_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::string& cache_name,
            const std::string& value
        );



        bool delete_one(
            const std::string& cache_name,
            const std::string& key_path
        );

        void delete_one(
            Result<void>& result,
            const std::string& cache_name,
            const std::string& key_path
        );

        std::future<bool> delete_one_async(
            const std::string& cache_name,
            const std::string& key_path
        );

        void delete_one_async(
            const std::function<void(const bool& result)>& callback,
            const std::string& cache_name,
            const std::string& key_path
        );

        void delete_one_async(
            Result<std::future<void>>& result,
            const std::string& cache_name,
            const std::string& key_path
        );

        void delete_one_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::string& cache_name,
            const std::string& key_path
        );

        bool delete_all(
            std::string& cache_name
        );

        void delete_all(
            Result<void>& result,
            std::string& cache_name
        );

        std::future<bool> delete_all_async(
            std::string& cache_name
        );

        void delete_all_async(
            const std::function<void(const bool& result)>& callback,
            std::string& cache_name
        );

        void delete_all_async(
            Result<std::future<void>>& result,
            std::string& cache_name
        );

        void delete_all_async(
            const std::function<void(Result<void>& result)>& callback,
            std::string& cache_name
        );



        bool clear_one(
            std::string& cache_name
        );

        void clear_one(
            Result<void>& result,
            std::string& cache_name
        );

        std::future<bool> clear_one_async(
            std::string& cache_name
        );

        void clear_one_async(
            const std::function<void(const bool& result)>& callback,
            std::string& cache_name
        );

        void clear_one_async(
            Result<std::future<void>>& result,
            std::string& cache_name
        );

        void clear_one_async(
            const std::function<void(Result<void>& result)>& callback,
            std::string& cache_name
        );

        bool clear_all();

        void clear_all(
            Result<void>& result
        );

        std::future<bool> clear_all_async();

        void clear_all_async(
            const std::function<void(const bool& result)>& callback
        );

        void clear_all_async(
            Result<std::future<void>>& result
        );

        void clear_all_async(
            const std::function<void(Result<void>& result)>& callback
        );



        bool sync_one_backup(
            std::string& cache_name
        );

        void sync_one_backup(
            Result<void>& result,
            std::string& cache_name
        );

        std::future<bool> sync_one_backup_async(
            std::string& cache_name
        );

        void sync_one_backup_async(
            const std::function<void(const bool& result)>& callback,
            std::string& cache_name
        );

        void sync_one_backup_async(
            Result<std::future<void>>& result,
            std::string& cache_name
        );

        void sync_one_backup_async(
            const std::function<void(Result<void>& result)>& callback,
            std::string& cache_name
        );

        bool sync_all_backups();

        void sync_all_backups(
            Result<void>& result
        );

        std::future<bool> sync_all_backups_async();

        void sync_all_backups_async(
            const std::function<void(const bool& result)>& callback
        );

        void sync_all_backups_async(
            Result<std::future<void>>& result
        );

        void sync_all_backups_async(
            const std::function<void(Result<void>& result)>& callback
        );

    

        bool retrieve_one_backup(
            std::string& cache_name
        );

        void retrieve_one_backup(
            Result<void>& result,
            std::string& cache_name
        );

        std::future<bool> retrieve_one_backup_async(
            std::string& cache_name
        );

        void retrieve_one_backup_async(
            const std::function<void(const bool& result)>& callback,
            std::string& cache_name
        );

        void retrieve_one_backup_async(
            Result<std::future<void>>& result,
            std::string& cache_name
        );

        void retrieve_one_backup_async(
            const std::function<void(Result<void>& result)>& callback,
            std::string& cache_name
        );

        bool retrieve_all_backups();

        void retrieve_all_backups(
            Result<void>& result
        );

        std::future<bool> retrieve_all_backups_async();

        void retrieve_all_backups_async(
            const std::function<void(const bool& result)>& callback
        );

        void retrieve_all_backups_async(
            Result<std::future<void>>& result
        );

        void retrieve_all_backups_async(
            const std::function<void(Result<void>& result)>& callback
        );



        bool terminate();

        void terminate(
            Result<void>& result
        );

        std::future<bool> terminate_async(
            const std::function<void(const bool& result)>& callback =
            [](const bool& result) {}
        );

        void terminate_async(
            Result<std::future<void>>& result,
            const std::function<void(Result<void>& result)>& callback =
            [](Result<void>& result) {}
        );

        static ApplicationCache& get_instance();

        static void get_instance(
            Result<ApplicationCache*>& result
        );

    protected:
        ApplicationCache();

        ~ApplicationCache();

        ApplicationCache(
            const ApplicationCache& instance
        ) = default;

        ApplicationCache(
            ApplicationCache&& instance
        ) noexcept = delete;

        ApplicationCache& operator = (
            ApplicationCache&& instance
        ) = default;

        ApplicationCache& operator = (
            const ApplicationCache& instance
        ) = delete;

        ApplicationCacheConfigurations _configurations;
    };

    inline static ApplicationCache& QLOGICAE_APPLICATION_CACHE =
        ApplicationCache::get_instance();
}
