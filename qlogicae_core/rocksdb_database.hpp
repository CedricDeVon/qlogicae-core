#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    struct RocksDBConfig
    {
        size_t block_cache_size = 64 * 1024 * 1024;
        size_t write_buffer_size = 64 * 1024 * 1024;
        int max_background_jobs = 4;
    };

    class RocksDBDatabase
    {
    public:
        RocksDBDatabase() = default;
        ~RocksDBDatabase();

        RocksDBDatabase(const std::string_view&, const RocksDBConfig & = {});
        RocksDBDatabase(const RocksDBDatabase&) = delete;
        RocksDBDatabase(RocksDBDatabase&&) noexcept = delete;
        RocksDBDatabase& operator=(const RocksDBDatabase&) = delete;
        RocksDBDatabase& operator=(RocksDBDatabase&&) = delete;

        bool is_key_found(const std::string_view&) const;

        bool remove_value(const std::string_view&);
        bool batch_execute();

        template <typename T>
        T get_value(const std::string_view&);

        template <typename T>
        void set_value(const std::string_view&, const T&);

        template <typename T>
        void batch_set_value(const std::string_view&, const T&);

        template <typename T>
        void batch_remove_value(const std::string_view&, const T&);

        std::future<bool> remove_value_async(const std::string_view&);
        std::future<bool> batch_execute_async();

        template <typename T>
        std::future<T> get_value_async(const std::string_view&);

        template <typename T>
        std::future<void> set_value_async(const std::string_view&, const T&);

        bool create_column_family(const std::string_view&);
        bool drop_column_family(const std::string_view&);
        bool use_column_family(const std::string_view&);

        void begin_batch();
        bool commit_batch();

        bool create_backup(const std::string_view&) const;
        bool restore_backup(const std::string_view&);

        bool create_checkpoint(const std::string_view&) const;

        std::optional<std::string> get_with_bounds(
            const std::string_view&, uint64_t, uint64_t);

        bool begin_transaction();
        bool commit_transaction();
        bool rollback_transaction();

    protected:
        rocksdb::DB* _object{};
        rocksdb::TransactionDB* _transaction_db{};
        rocksdb::Transaction* _transaction{};
        rocksdb::WriteBatch _write_batch;

        std::unordered_map<std::string, rocksdb::ColumnFamilyHandle*> _column_families;
        rocksdb::Options _options;
        rocksdb::TransactionDBOptions _txn_options;
        std::vector<std::string> _cf_names;
        rocksdb::ReadOptions _read_options;
        std::unique_ptr<const rocksdb::FilterPolicy> _bloom_filter;

        std::string _file_path;
        RocksDBConfig _config;
        mutable std::shared_mutex _mutex;

        void open_db();
        void close_db();
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
    inline std::string RocksDBDatabase::serialize<std::string>(const std::string& value) {
        return value;
    }

    template <>
    inline std::string RocksDBDatabase::deserialize<std::string>(const std::string& data) {
        return data;
    }
}

