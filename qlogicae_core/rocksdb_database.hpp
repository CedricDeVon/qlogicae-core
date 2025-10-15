#pragma once

#include "result.hpp"
#include "utilities.hpp"
#include "rocksdb_config.hpp"

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
            const std::string_view&,
            const RocksDBConfig & = {}
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

        std::string get_file_path() const;
        
        void setup(
            const std::string& path,
            const RocksDBConfig& config = {}
        );

        bool is_path_found(
            const std::string_view&
        ) const;
        
        bool is_key_found(
            const std::string_view&
        ) const;

        bool remove_value(
            const std::string_view&
        );
        
        bool batch_execute();

        template <typename T>
        T get_value(
            const std::string_view&
        );

        template <typename T>
        void set_value(
            const std::string_view&,
            const T&
        );

        template <typename T>
        void batch_set_value(
            const std::string_view&,
            const T&
        );

        template <typename T>
        void batch_remove_value(
            const std::string_view&,
            const T&
        );

        std::future<bool> remove_value_async(
            const std::string_view&
        );
        
        std::future<bool> batch_execute_async();

        template <typename T>
        std::future<T> get_value_async(
            const std::string_view&
        );

        template <typename T>
        std::future<void> set_value_async(
            const std::string_view&,
            const T&
        );

        bool create_column_family(
            const std::string_view&
        );
        
        bool drop_column_family(
            const std::string_view&
        );
        
        bool use_column_family(
            const std::string_view&
        );

        void begin_batch();
        
        bool commit_batch();

        bool create_backup(
            const std::string_view&
        ) const;
        
        bool restore_backup(
            const std::string_view&
        );

        bool create_checkpoint(
            const std::string_view&
        ) const;

        std::optional<std::string> get_with_bounds(
            const std::string_view&,
            uint64_t,
            uint64_t
        );

        bool begin_transaction();
        
        bool commit_transaction();
        
        bool rollback_transaction();

        void get_file_path(
            Result<std::string>& result
        ) const;

        void setup(
            Result<void>& result,
            const std::string& path,
            const RocksDBConfig& config = {}
        );

        void is_path_found(
            Result<bool>& result,
            const std::string&
        ) const;

        void is_key_found(
            Result<bool>& result,
            const std::string&
        ) const;

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
        ) const;

        void restore_backup(
        Result<bool>& result,
        const std::string&
        );

        void create_checkpoint(
            Result<bool>& result,
            const std::string&
        ) const;

        void get_with_bounds(
            Result<std::optional<std::string>>& result,
            const std::string&,
            uint64_t,
            uint64_t
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

        void remove_value_async(
            Result<std::future<bool>>& result,
            const std::string&
        );

        void batch_execute_async(
            Result<std::future<bool>>& result
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

    protected:
        RocksDBConfig _config;
        
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

        rocksdb::ColumnFamilyHandle* get_cf_handle(const std::string& name) const;

        template <typename T>
        static std::string serialize(const T& value);

        template <typename T>
        static T deserialize(const std::string& data);
    };

    template <typename T>
    inline T RocksDBDatabase::get_value(const std::string_view& key)
    {
        std::shared_lock lock(_mutex);

        std::string value;
        auto s = _object->Get(_read_options, key.data(), &value);
        if (!s.ok())
            throw std::runtime_error("Failed to get key: " + std::string(key));

        return deserialize<T>(value);
    }

    template <typename T>
    inline void RocksDBDatabase::set_value(const std::string_view& key, const T& value)
    {
        std::unique_lock lock(_mutex);

        auto serialized = serialize(value);
        rocksdb::WriteOptions options;
        options.sync = true;
        auto s = _object->Put(options, key.data(), serialized);
        if (!s.ok()) {
            throw std::runtime_error("Failed to set key: " + std::string(key) + ", reason: " + s.ToString());
        }
    }

    template <typename T>
    inline void RocksDBDatabase::batch_set_value(const std::string_view& key, const T& value)
    {
        std::unique_lock lock(_mutex);

        _write_batch.Put(key.data(), serialize(value));
    }

    template <typename T>
    inline void RocksDBDatabase::batch_remove_value(const std::string_view& key, const T&)
    {
        std::unique_lock lock(_mutex);

        _write_batch.Delete(key.data());
    }

    template <typename T>
    inline std::future<T> RocksDBDatabase::get_value_async(const std::string_view& key)
    {
        return std::async(std::launch::async, [this, key = std::move(key)]() {
            return get_value<T>(key);
            });
    }

    template <typename T>
    inline std::future<void> RocksDBDatabase::set_value_async(const std::string_view& key, const T& value)
    {
        return std::async(std::launch::async, [this, key = std::move(key), value = std::move(value)]() {
            set_value<T>(key, value);
        });
    }

    template <typename T>
    inline static std::string RocksDBDatabase::serialize(const T& value)
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    template <typename T>
    inline static T RocksDBDatabase::deserialize(const std::string& data)
    {
        std::istringstream iss(data);
        T value;
        iss >> value;
        return value;
    }

    template <>
    inline std::string RocksDBDatabase::serialize<std::string>(const std::string& value)
    {
        return value;
    }

    template <>
    inline std::string RocksDBDatabase::deserialize<std::string>(const std::string& data)
    {
        return data;
    }





    template <typename Type>
    void RocksDBDatabase::get_value(
        Result<Type>& result,
        const std::string& key
    )
    {
        std::shared_lock lock(_mutex);

        std::string value;
        auto s = _object->Get(_read_options, key, &value);
        if (!s.ok())
        {
            result.set_to_failure();
            return;
        }
            
        result.set_to_success(
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
        std::unique_lock lock(_mutex);

        auto serialized = serialize(value);
        auto s = _object->Put(_options, key, serialized);
        if (!s.ok())
        {
            result.set_to_failure();
            return;
        }

        result.set_to_success();
    }

    template <typename Type>
    void RocksDBDatabase::batch_set_value(
        Result<void>& result,
        const std::string& key,
        const Type& value
    )
    {
        std::unique_lock lock(_mutex);

        _write_batch.Put(key, serialize(value));

        result.set_to_success();
    }

    template <typename Type>
    void RocksDBDatabase::batch_remove_value(
        Result<void>& result,
        const std::string& key,
        const Type& value
    )
    {
        std::unique_lock lock(_mutex);
        
        _write_batch.Delete(key);

        result.set_to_success();
    }

    template <typename Type>
    void RocksDBDatabase::get_value_async(
        Result<std::future<Type>>& result,
        const std::string& key
    )
    {
        result.set_to_success(
            std::async(std::launch::async, [this, key = std::move(key)]()
            {
                Result<Type> result;

                get_value<Type>(result, key);

                return result.get_data();
            })
        );
    }

    template <typename Type>
    void RocksDBDatabase::set_value_async(
        Result<std::future<void>>& result,
        const std::string& key,
        const Type& value
    )
    {
        result.set_to_success(
            std::async(std::launch::async,
                [this, key = std::move(key), value = std::move(value)]()
            {
                    Result<Type> result;

                    set_value<Type>(key, value);
            })
        );
    }
}
