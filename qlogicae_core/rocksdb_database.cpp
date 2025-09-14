#include "pch.h"

#include "rocksdb_database.hpp"

namespace QLogicaeCore
{
    RocksDBDatabase::~RocksDBDatabase()
    {
        close_db();
    }

    RocksDBDatabase::RocksDBDatabase() :
        _file_path(""),
        _config({})
    {
    }

    RocksDBDatabase::RocksDBDatabase(
        const std::string_view& path,
        const RocksDBConfig& config)
            : _file_path(path), _config(config)
    {
        open_db();
    }

    std::string RocksDBDatabase::get_file_path() const
    {
        return _file_path;
    }

    void RocksDBDatabase::setup(
        const std::string& path,
        const RocksDBConfig& config)
    {
        close_db();

        _file_path = path;
        _config = config;

        open_db();
    }

    bool RocksDBDatabase::is_path_found(
        const std::string_view& path) const
    {
        try
        {
            std::shared_lock lock(_mutex);

            return std::filesystem::exists(path);
        }
        catch (...)
        {
            return false;
        }
    }

    bool RocksDBDatabase::is_key_found(
        const std::string_view& key) const
    {
        std::shared_lock lock(_mutex);

        if (_object == nullptr)
        {
            return false;
        }
        std::string value;
        auto s = _object->Get(_read_options, std::string(key), &value);

        return s.ok();
    }

    bool RocksDBDatabase::remove_value(
        const std::string_view& key)
    {
        std::unique_lock lock(_mutex);

        auto string = _object->Delete(
            rocksdb::WriteOptions(), key.data());

        return string.ok();
    }

    bool RocksDBDatabase::batch_execute()
    {
        std::unique_lock lock(_mutex);

        auto string = _object->Write(
            rocksdb::WriteOptions(), &_write_batch);
        _write_batch.Clear();

        return string.ok();
    }

    std::future<bool> RocksDBDatabase::remove_value_async(
        const std::string_view& key)
    {
        std::string key_str(key);
        return std::async(std::launch::async,
            [this, key_str = std::move(key_str)]()
            {
                return remove_value(key_str);
            }
        );
    }

    std::future<bool> RocksDBDatabase::batch_execute_async()
    {
        return std::async(std::launch::async, [this]()
        {
            return batch_execute();
        });
    }

    bool RocksDBDatabase::create_column_family(
        const std::string_view& name)
    {
        std::unique_lock lock(_mutex);

        std::string name_key(name);
        rocksdb::ColumnFamilyHandle* handle = nullptr;
        auto s = _object->CreateColumnFamily(
            rocksdb::ColumnFamilyOptions(), name_key, &handle);
        if (s.ok())
        {
            _column_families.emplace(std::move(name_key), handle);
        }
        return s.ok();
    }

    bool RocksDBDatabase::drop_column_family(
        const std::string_view& name)
    {
        std::unique_lock lock(_mutex);

        std::string name_key(name);
        auto iterator = _column_families.find(name_key);
        if (iterator == _column_families.end())
        {
            return false;
        }
        auto s = _object->DropColumnFamily(iterator->second);
        if (s.ok())
        {
            _object->DestroyColumnFamilyHandle(iterator->second);
            _column_families.erase(iterator);
        }
        return s.ok();
    }

    bool RocksDBDatabase::use_column_family(const std::string_view& name)
    {
        return _column_families.contains(name.data());
    }

    void RocksDBDatabase::begin_batch()
    {
        std::unique_lock lock(_mutex);

        _write_batch.Clear();
    }

    bool RocksDBDatabase::commit_batch()
    {
        return batch_execute();
    }

    bool RocksDBDatabase::create_backup(const std::string_view& path) const
    {
        std::shared_lock lock(_mutex);

        rocksdb::BackupEngine* backup;
        rocksdb::BackupEngineOptions options(path.data());
        auto string = rocksdb::BackupEngine::Open(
            rocksdb::Env::Default(), options, &backup);
        if (!string.ok())
        {
            return false;
        }
        string = backup->CreateNewBackup(_object);
        delete backup;

        return string.ok();
    }

    bool RocksDBDatabase::restore_backup(const std::string_view& path)
    {
        std::unique_lock lock(_mutex);

        close_db();
        rocksdb::BackupEngineReadOnly* backup;
        rocksdb::BackupEngineOptions options(path.data());
        auto string = rocksdb::BackupEngineReadOnly::Open(
            rocksdb::Env::Default(),
            options, &backup
        );
        if (!string.ok())
        {
            return false;
        }
        string = backup->RestoreDBFromLatestBackup(_file_path, _file_path);
        delete backup;
        if (!string.ok())
        {
            return false;
        }
        open_db();

        return true;
    }

    bool RocksDBDatabase::create_checkpoint(
        const std::string_view& path) const
    {
        std::shared_lock lock(_mutex);

        rocksdb::Checkpoint* checkpoint;
        auto string = rocksdb::Checkpoint::Create(_object, &checkpoint);
        if (!string.ok())
        {
            return false;
        }
        string = checkpoint->CreateCheckpoint(path.data());
        delete checkpoint;

        return string.ok();
    }

    std::optional<std::string> RocksDBDatabase::get_with_bounds(
        const std::string_view& key, uint64_t offset, uint64_t size)
    {
        std::shared_lock lock(_mutex);

        if (_object == nullptr)
        {
            return std::nullopt;
        }
        rocksdb::PinnableSlice pvalue;
        rocksdb::ReadOptions options;
        options.verify_checksums = true;
        auto s = _object->Get(options, _object->DefaultColumnFamily(),
            std::string(key), &pvalue);
        if (!s.ok())
        {
            return std::nullopt;
        }
        const uint64_t psize = static_cast<uint64_t>(pvalue.size());
        if (offset >= psize)
        {
            return std::nullopt;
        }
        const uint64_t max_size = psize - offset;
        const size_t use_size = static_cast<size_t>(std::min<uint64_t>(size, max_size));

        return std::string(pvalue.data() + static_cast<size_t>(offset), use_size);
    }

    bool RocksDBDatabase::begin_transaction()
    {
        std::unique_lock lock(_mutex);

        if (_transaction)
        {
            return false;
        }
        _transaction = _transaction_db->BeginTransaction(
            rocksdb::WriteOptions());

        return _transaction != nullptr;
    }

    bool RocksDBDatabase::commit_transaction()
    {
        std::unique_lock lock(_mutex);

        if (!_transaction)
        {
            return false;
        }
        auto string = _transaction->Commit();
        delete _transaction;
        _transaction = nullptr;

        return string.ok();
    }

    bool RocksDBDatabase::rollback_transaction()
    {
        std::unique_lock lock(_mutex);

        if (!_transaction)
        {
            return false;
        }
        auto string = _transaction->Rollback();
        delete _transaction;
        _transaction = nullptr;

        return string.ok();
    }

    void RocksDBDatabase::open_db()
    {
        if (!std::filesystem::exists(_file_path))
        {
            std::filesystem::create_directories(_file_path);
        }

        _options.create_if_missing = true;
        _options.max_background_jobs =
            static_cast<int>(_config.max_background_jobs);
        _options.write_buffer_size =
            static_cast<size_t>(_config.write_buffer_size);

        rocksdb::BlockBasedTableOptions table_options;
        table_options.filter_policy.reset(
            rocksdb::NewBloomFilterPolicy(10));

        _options.table_factory.reset(
            rocksdb::NewBlockBasedTableFactory(table_options));

        rocksdb::TransactionDBOptions txn_db_options;
        rocksdb::Status status = rocksdb::TransactionDB::Open(
            _options, txn_db_options, _file_path, &_transaction_db);

        if (!status.ok())
        {
            throw std::runtime_error(
                "Exception at RocksDBDatabase::open_db(): Failed to open RocksDB: " + status.ToString());
        }

        _object = _transaction_db;
    }

    void RocksDBDatabase::close_db()
    {
        std::unique_lock lock(_mutex);

        if (_object != nullptr)
        {
            for (auto& [name, handle] : _column_families)
            {
                if (handle != nullptr)
                {
                    _object->DestroyColumnFamilyHandle(handle);
                }
            }
        }
        _column_families.clear();

        if (_transaction != nullptr)
        {
            delete _transaction;
            _transaction = nullptr;
        }
        if (_transaction_db != nullptr)
        {
            delete _transaction_db;
            _transaction_db = nullptr;
        }
        _object = nullptr;
    }

    rocksdb::ColumnFamilyHandle* RocksDBDatabase::get_cf_handle(
        const std::string& name) const
    {
        std::string name_key(name);
        auto iterator = _column_families.find(name_key);
        if (iterator != _column_families.end())
        {
            return iterator->second;
        }
        if (_object != nullptr)
        {
            return _object->DefaultColumnFamily();
        }
        return nullptr;
    }
}
