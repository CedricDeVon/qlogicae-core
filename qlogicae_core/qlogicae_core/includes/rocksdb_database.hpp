#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "utilities.hpp"
#include "rocksdb_configurations.hpp"

#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/table.h>
#include <rocksdb/options.h>
#include <rocksdb/iterator.h>
#include <rocksdb/listener.h>
#include <rocksdb/convenience.h>
#include <rocksdb/write_batch.h>
#include <rocksdb/filter_policy.h>
#include <rocksdb/compaction_filter.h>
#include <rocksdb/utilities/checkpoint.h>
#include <rocksdb/utilities/backup_engine.h>
#include <rocksdb/utilities/transaction_db.h>

#include <any>
#include <vector>
#include <string>
#include <future>
#include <algorithm>
#include <typeindex>
#include <Windows.h>
#include <memory_resource>

namespace QLogicaeCore
{
    class RocksDBDatabase
    {
    public:
        RocksDBDatabase();
        
        ~RocksDBDatabase();

        RocksDBDatabase(
            const std::string&,
            const RocksDBConfigurations& = {}
        );
        
        RocksDBDatabase(
            const RocksDBDatabase&
        ) = delete;
        
        RocksDBDatabase(
            RocksDBDatabase&&
        ) noexcept = delete;
        
        RocksDBDatabase& operator=(
            const RocksDBDatabase&
        ) = delete;
        
        RocksDBDatabase& operator=(
            RocksDBDatabase&&
        ) = delete;

        std::string get_file_path();
        
        bool setup();

        void setup(
            Result<void>& result
        );

        std::future<bool> setup_async();

        void setup_async(
            const std::function<void(const bool& result)>& callback
        );

        void setup_async(
            Result<std::future<void>>& result
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback
        );

        bool setup(
            const std::string& path,
            const RocksDBConfigurations& configurations
        );

        void setup(
            Result<void>& result,
            const std::string& path,
            const RocksDBConfigurations& configurations
        );

        std::future<bool> setup_async(
            const std::string& path,
            const RocksDBConfigurations& configurations
        );

        void setup_async(
            const std::function<void(const bool& result)>& callback,
            const std::string& path,
            const RocksDBConfigurations& configurations
        );

        void setup_async(
            Result<std::future<void>>& result,
            const std::string& path,
            const RocksDBConfigurations& configurations
        );

        void setup_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::string& path,
            const RocksDBConfigurations& configurations
        );

        bool is_path_found(
            const std::string&
        );
        
        bool is_key_found(
            const std::string&
        );

        bool remove_value(
            const std::string&
        );
        
        bool batch_execute();

        template <typename Type>
        Type get_value(
            const std::string&
        );

        template <typename Type>
        void set_value(
            const std::string&,
            const Type&
        );

        template <typename Type>
        void batch_set_value(
            const std::string&,
            const Type&
        );

        template <typename Type>
        void batch_remove_value(
            const std::string&,
            const Type&
        );

        bool create_column_family(
            const std::string&
        );
        
        bool drop_column_family(
            const std::string&
        );
        
        bool use_column_family(
            const std::string&
        );

        void begin_batch();
        
        bool commit_batch();

        bool create_backup(
            const std::string&
        );
        
        bool restore_backup(
            const std::string&
        );

        bool create_checkpoint(
            const std::string&
        );

        std::optional<std::string> get_with_bounds(
            const std::string&,
            const uint64_t&,
            const uint64_t&
        );

        bool begin_transaction();
        
        bool commit_transaction();
        
        bool rollback_transaction();

        void get_file_path(
            Result<std::string>& result
        );

        void is_path_found(
            Result<bool>& result,
            const std::string&
        );

        void is_key_found(
            Result<bool>& result,
            const std::string&
        );

        void remove_value(
            Result<bool>& result,
            const std::string&
        );

        void batch_execute(
            Result<bool>& result    
        );

        void create_column_family(
            Result<bool>& result,
            const std::string&
        );

        void drop_column_family(
            Result<bool>& result,
            const std::string&
        );

        void use_column_family(
            Result<bool>& result,
            const std::string&
        );

        void begin_batch(
            Result<bool>& result
        );

        void commit_batch(
            Result<bool>& result
        );

        void create_backup(
            Result<bool>& result,
            const std::string&
        );

        void restore_backup(
        Result<bool>& result,
        const std::string&
        );

        void create_checkpoint(
            Result<bool>& result,
            const std::string&
        );

        void get_with_bounds(
            Result<std::optional<std::string>>& result,
            const std::string&,
            const uint64_t&,
            const uint64_t&
        );

        void begin_transaction(
            Result<bool>& result
        );

        void commit_transaction(
            Result<bool>& result
        );

        void rollback_transaction(
            Result<bool>& result
        );

        template <typename Type>
        void get_value(
            Result<Type>& result,
            const std::string&
        );

        template <typename Type>
        void set_value(
            Result<void>& result,
            const std::string&,
            const Type&
        );

        template <typename Type>
        void batch_set_value(
            Result<void>& result,
            const std::string&,
            const Type&
        );

        template <typename Type>
        void batch_remove_value(
            Result<void>& result,
            const std::string&,
            const Type&
        );

        bool terminate();

        void terminate(
            Result<void>& result
        );

        std::future<bool> remove_value_async(
            const std::string&
        );

        std::future<bool> batch_execute_async();

        void remove_value_async(
            Result<std::future<bool>>& result,
            const std::string&
        );

        void batch_execute_async(
            Result<std::future<bool>>& result
        );

        void remove_value_async(
            const std::function<void(const bool& result)>& callback,
            const std::string& key
        );

        void batch_execute_async(
            const std::function<void(const bool& result)>& callback
        );

        void remove_value_async(
            const std::function<void(Result<bool>& result)>& callback,
            const std::string& key
        );

        void batch_execute_async(
            const std::function<void(Result<bool>& result)>& callback
        );

        template <typename Type>
        std::future<Type> get_value_async(
            const std::string&
        );

        template <typename Type>
        std::future<void> set_value_async(
            const std::string&,
            const Type&
        );

        template <typename Type>
        void get_value_async(
            Result<std::future<Type>>& result,
            const std::string&
        );

        template <typename Type>
        void set_value_async(
            Result<std::future<void>>& result,
            const std::string&,
            const Type&
        );

        template <typename Type>
        void get_value_async(
            const std::function<void(const Type& result)>& callback,
            const std::string&
        );

        template <typename Type>
        void set_value_async(
            const std::function<void()>& callback,
            const std::string&,
            const Type&
        );

        template <typename Type>
        void get_value_async(
            const std::function<void(Result<Type>& result)>& callback,
            const std::string&
        );

        template <typename Type>
        void set_value_async(
            const std::function<void(Result<void>& result)>& callback,
            const std::string&,
            const Type&
        );

        std::future<bool> terminate_async();

        void terminate_async(
            const std::function<void(const bool& result)>& callback
        );

        void terminate_async(
            Result<std::future<void>>& result
        );

        void terminate_async(
            const std::function<void(Result<void>& result)>& callback
        );

        static RocksDBDatabase& get_instance();

        static void get_instance(
            Result<RocksDBDatabase*>& result
        );

    protected:
        RocksDBConfigurations _config;
        
        rocksdb::DB* _object{};
        
        std::string _file_path;
        
        rocksdb::Options _options;
        
        rocksdb::WriteOptions _write_options;
        
        rocksdb::BlockBasedTableOptions _table_options;
        
        rocksdb::TransactionDBOptions _txn_db_options;
        
        rocksdb::Status _status;
        
        mutable std::shared_mutex _mutex;
        
        rocksdb::WriteBatch _write_batch;
        
        std::vector<std::string> _cf_names;
        
        rocksdb::ReadOptions _read_options;
        
        rocksdb::Transaction* _transaction{};
        
        rocksdb::TransactionDB* _transaction_db{};
        
        rocksdb::TransactionDBOptions _txn_options;
        
        std::unique_ptr<const rocksdb::FilterPolicy> _bloom_filter;

        std::unordered_map<std::string, rocksdb::ColumnFamilyHandle*> _column_families;

        void open_db();
        
        void close_db();
        
        void setup_db();

        rocksdb::ColumnFamilyHandle* get_cf_handle(const std::string& name);

        template <typename Type>
        static std::string serialize(const Type& value);

        template <typename Type>
        static Type deserialize(const std::string& data);
    };

    template <typename Type>
    inline Type RocksDBDatabase::get_value(
        const std::string& key
    )
    {
        try
        {
            std::shared_lock lock(_mutex);

            std::string value = "";

            _object->Get(_read_options, key, &value);

            return deserialize<Type>(value);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::get_value()",
                exception.what()
            );

            return deserialize<Type>("");
        }
    }

    template <typename Type>
    inline void RocksDBDatabase::set_value(
        const std::string& key,
        const Type& value
    )
    {
        try
        {
            std::unique_lock lock(_mutex);

            auto result_value = _object->Put(
                _write_options,
                key,
                serialize(value)
            );
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::set_value()",
                exception.what()
            );
        }
    }

    template <typename Type>
    inline void RocksDBDatabase::batch_set_value(
        const std::string& key,
        const Type& value
    )
    {
        try
        {
            std::unique_lock lock(_mutex);

            _write_batch.Put(key, serialize(value));
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::batch_set_value()",
                exception.what()
            );
        }
    }

    template <typename Type>
    inline void RocksDBDatabase::batch_remove_value(
        const std::string& key,
        const Type&
    )
    {
        try
        {
            std::unique_lock lock(_mutex);

            _write_batch.Delete(key);
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::batch_remove_value()",
                exception.what()
            );
        }
    }

    template <typename Type>
    inline std::future<Type> RocksDBDatabase::get_value_async(
        const std::string& key
    )
    {
        std::promise<Type> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, key,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    get_value<Type>(
                        key
                    )
                );
            }
        );

        return future;
    }

    template <typename Type>
    inline std::future<void> RocksDBDatabase::set_value_async(
        const std::string& key,
        const Type& value
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, key, value,
            promise = std::move(promise)]() mutable
            {
                set_value<Type>(key, value);

                promise.set_value();
            }
        );

        return future;
    }

    template <typename Type>
    inline static std::string RocksDBDatabase::serialize(
        const Type& value
    )
    {
        try
        {            
            std::ostringstream oss;

            oss << value;

            return oss.str();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::serialize()",
                exception.what()
            );

            return {};
        }        
    }

    template <typename Type>
    inline static Type RocksDBDatabase::deserialize(
        const std::string& data
    )
    {
        try
        {
            std::istringstream iss(data);

            Type value;
            iss >> value;

            return value;
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::deserialize()",
                exception.what()
            );

            return {};
        }        
    }

    template <>
    inline std::string RocksDBDatabase::serialize<std::string>(
        const std::string& value
    )
    {
        try
        {
            return value;
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::serialize()",
                exception.what()
            );

            return {};
        }        
    }

    template <>
    inline std::string RocksDBDatabase::deserialize<std::string>(
        const std::string& data
    )
    {
        try
        {
            return data;
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::deserialize()",
                exception.what()
            );

            return {};
        }
    }

    template <typename Type>
    void RocksDBDatabase::get_value(
        Result<Type>& result,
        const std::string& key
    )
    {        
        std::string value;
        if (!_object->Get(_read_options, key, &value).ok())
        {            
            return result.set_to_bad_status_without_value();
        }
            
        result.set_to_good_status_with_value(
            deserialize<Type>(value)
        );
    }

    template <typename Type>
    void RocksDBDatabase::set_value(
        Result<void>& result,
        const std::string& key,
        const Type& value
    )
    {        
        auto serialized = serialize(value);
        if (!_object->Put(_options, key, serialized).ok())
        {            
            return result.set_to_bad_status_without_value();
        }

        result.set_to_good_status_without_value();
    }

    template <typename Type>
    void RocksDBDatabase::batch_set_value(
        Result<void>& result,
        const std::string& key,
        const Type& value
    )
    {        
        _write_batch.Put(key, serialize(value));

        result.set_to_good_status_without_value();
    }

    template <typename Type>
    void RocksDBDatabase::batch_remove_value(
        Result<void>& result,
        const std::string& key,
        const Type& value
    )
    {        
        _write_batch.Delete(key);

        result.set_to_good_status_without_value();
    }

    template <typename Type>
    void RocksDBDatabase::get_value_async(
        Result<std::future<Type>>& result,
        const std::string& key
    )
    {
        std::promise<Type> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, key,
            promise = std::move(promise)]() mutable
            {
                Result<Type> result;

                get_value<Type>(
                    result,
                    key
                );

                promise.set_value(
                    result.get_value()
                );
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    template <typename Type>
    void RocksDBDatabase::set_value_async(
        Result<std::future<void>>& result,
        const std::string& key,
        const Type& value
    )
    {
        std::promise<Type> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, key, value,
            promise = std::move(promise)]() mutable
            {
                Result<Type> result;

                set_value<Type>(
                    result,
                    key,
                    value
                );

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    inline static RocksDBDatabase& ROCKSDB_DATABASE = 
        RocksDBDatabase::get_instance();
}
