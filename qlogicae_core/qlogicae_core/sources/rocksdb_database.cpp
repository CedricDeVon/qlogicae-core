#include "pch.hpp"

#include "../includes/rocksdb_database.hpp"

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
        setup_db();
    }

    RocksDBDatabase::RocksDBDatabase(
        const std::string& path,
        const RocksDBConfigurations& config
    ) :
            _file_path(path),
            _config(config)
    {
        setup_db();
        open_db();
    }

    bool RocksDBDatabase::setup()
    {
        try
        {
            Result<void> result;

            setup(
                result
            );

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::setup()",
                exception.what()
            );

            return false;
        }
    }

    void RocksDBDatabase::setup(
        Result<void>& result
    )
    {
        close_db();

        _file_path = "";
        _config = {};

        setup_db();
        open_db();

        result.set_to_good_status_without_value();
    }

    std::future<bool> RocksDBDatabase::setup_async()
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    setup()
                );
            }
        );

        return future;
    }

    void RocksDBDatabase::setup_async(
        Result<std::future<void>>& result
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(
                    result
                );

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void RocksDBDatabase::setup_async(
        const std::function<void(const bool& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                callback(
                    setup()
                );
            }
        );
    }

    void RocksDBDatabase::setup_async(
        const std::function<void(Result<void>& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                Result<void> result;

                setup(
                    result
                );

                callback(
                    result
                );
            }
        );
    }

    bool RocksDBDatabase::setup(
        const std::string& path,
        const RocksDBConfigurations& configurations
    )
    {
        try
        {
            Result<void> result;

            setup(
                result,
                path,
                configurations
            );

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::setup()",
                exception.what()
            );

            return false;
        }
    }

    void RocksDBDatabase::setup(
        Result<void>& result,
        const std::string& path,
        const RocksDBConfigurations& configurations
    )
    {
        close_db();

        _file_path = path;
        _config = configurations;

        setup_db();
        open_db();

        result.set_to_good_status_without_value();
    }

    std::future<bool> RocksDBDatabase::setup_async(
        const std::string& path,
        const RocksDBConfigurations& configurations
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, path, configurations,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    setup(
                        path,
                        configurations
                    )
                );
            }
        );

        return future;
    }

    void RocksDBDatabase::setup_async(
        Result<std::future<void>>& result,
        const std::string& path,
        const RocksDBConfigurations& configurations
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, path, configurations,
            promise = std::move(promise)]() mutable
            {
                Result<void> result;

                setup(
                    result,
                    path,
                    configurations
                );

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void RocksDBDatabase::setup_async(
        const std::function<void(const bool& result)>& callback,
        const std::string& path,
        const RocksDBConfigurations& configurations
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, path, configurations, callback]() mutable
            {
                callback(
                    setup(
                        path,
                        configurations
                    )
                );
            }
        );
    }

    void RocksDBDatabase::setup_async(
        const std::function<void(Result<void>& result)>& callback,
        const std::string& path,
        const RocksDBConfigurations& configurations
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, path, configurations, callback]() mutable
            {
                Result<void> result;

                setup(
                    result,
                    path,
                    configurations
                );

                callback(
                    result
                );
            }
        );
    }

    std::string RocksDBDatabase::get_file_path()
    {
        return _file_path;
    }

    bool RocksDBDatabase::is_path_found(
        const std::string& path
    )
    {
        return std::filesystem::exists(path);
    }

    bool RocksDBDatabase::is_key_found(
        const std::string& key
    )
    {        
        try
        {
            if (_object == nullptr)
            {
                return false;
            }

            std::string value;

            return _object->Get(
                _read_options,
                std::string(key),
                &value
            ).ok();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::is_key_found()",
                exception.what()
            );

            return false;
        }        
    }

    bool RocksDBDatabase::remove_value(
        const std::string& key
    )
    {
        try
        {
            std::unique_lock lock(_mutex);

            return _object->Delete(_write_options, key).ok();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::remove_value()",
                exception.what()
            );

            return false;
        }        
    }

    bool RocksDBDatabase::batch_execute()
    {
        try
        {
            std::unique_lock lock(_mutex);

            auto string = _object->Write(
                _write_options, &_write_batch);
            _write_batch.Clear();

            return string.ok();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::batch_execute()",
                exception.what()
            );

            return false;
        }        
    }

    std::future<bool> RocksDBDatabase::remove_value_async(
        const std::string& key
    )
    {        
        std::string key_str(key);
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, key_str,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    remove_value(key_str)
                );
            }
        );

        return future;
    }

    std::future<bool> RocksDBDatabase::batch_execute_async()
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, 
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    batch_execute()
                );
            }
        );

        return future;
    }

    bool RocksDBDatabase::create_column_family(
        const std::string& name
    )
    {
        try
        {
            std::unique_lock lock(_mutex);

            std::string name_key(name);
            rocksdb::ColumnFamilyHandle* handle = nullptr;
            bool result = _object->CreateColumnFamily(
                rocksdb::ColumnFamilyOptions(), name_key, &handle).ok();
            if (result)
            {
                _column_families.emplace(std::move(name_key), handle);
            }
            return result;
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::create_column_family()",
                exception.what()
            );

            return false;
        }        
    }

    bool RocksDBDatabase::drop_column_family(
        const std::string& name
    )
    {
        try
        {
            std::unique_lock lock(_mutex);

            std::string name_key(name);
            auto iterator = _column_families.find(name_key);
            if (iterator == _column_families.end())
            {                
                return false;
            }
            bool result = _object->DropColumnFamily(iterator->second).ok();
            if (result)
            {
                _object->DestroyColumnFamilyHandle(iterator->second);
                _column_families.erase(iterator);
            }

            return result;
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::drop_column_family()",
                exception.what()
            );

            return false;
        }        
    }

    bool RocksDBDatabase::use_column_family(
        const std::string& name
    )
    {
        return _column_families.contains(
            name
        );
    }

    void RocksDBDatabase::begin_batch()
    {
        try
        {
            std::unique_lock lock(_mutex);

            _write_batch.Clear();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::begin_batch()",
                exception.what()
            );
        }        
    }

    bool RocksDBDatabase::commit_batch()
    {
        try
        {
            return batch_execute();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::commit_batch()",
                exception.what()
            );

            return false;
        }        
    }

    bool RocksDBDatabase::create_backup(
        const std::string& path
    )
    {
        try
        {
            std::shared_lock lock(_mutex);

            rocksdb::BackupEngine* backup;
            rocksdb::BackupEngineOptions options(path);
            auto result = rocksdb::BackupEngine::Open(
                rocksdb::Env::Default(), options, &backup);
            if (!result.ok())
            {                
                return false;
            }
            result = backup->CreateNewBackup(_object);
            delete backup;

            return result.ok();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::create_backup()",
                exception.what()
            );

            return false;
        }        
    }

    bool RocksDBDatabase::restore_backup(
        const std::string& path
    )
    {
        try
        {
            std::unique_lock lock(_mutex);

            close_db();

            rocksdb::BackupEngineReadOnly* backup;
            rocksdb::BackupEngineOptions options(path);
            auto result = rocksdb::BackupEngineReadOnly::Open(
                rocksdb::Env::Default(),
                options, &backup
            );
            if (!result.ok())
            {                
                return false;
            }
            result = backup->RestoreDBFromLatestBackup(_file_path, _file_path);
            delete backup;
            if (!result.ok())
            {
                return false;
            }
            open_db();

            return true;
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::restore_backup()",
                exception.what()
            );

            return false;
        }        
    }

    bool RocksDBDatabase::create_checkpoint(
        const std::string& path
    )
    {
        try
        {
            std::shared_lock lock(_mutex);

            rocksdb::Checkpoint* checkpoint;
            auto string = rocksdb::Checkpoint::Create(_object, &checkpoint);
            if (!string.ok())
            {                
                return false;
            }
            string = checkpoint->CreateCheckpoint(path);
            delete checkpoint;

            return string.ok();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::create_checkpoint()",
                exception.what()
            );

            return false;
        }        
    }

    std::optional<std::string> RocksDBDatabase::get_with_bounds(
        const std::string& key,
        const uint64_t& offset,
        const uint64_t& size
    )
    {
        try
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
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::get_with_bounds()",
                exception.what()
            );

            return std::nullopt;
        }        
    }

    bool RocksDBDatabase::begin_transaction()
    {
        try
        {
            std::unique_lock lock(_mutex);

            if (_transaction)
            {                
                return false;
            }
            _transaction = _transaction_db->BeginTransaction(
                _write_options);

            return _transaction != nullptr;
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::begin_transaction()",
                exception.what()
            );

            return false;
        }        
    }

    bool RocksDBDatabase::commit_transaction()
    {
        try
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
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::commit_transaction()",
                exception.what()
            );

            return false;
        }        
    }

    bool RocksDBDatabase::rollback_transaction()
    {
        try
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
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::rollback_transaction()",
                exception.what()
            );

            return false;
        }        
    }

    void RocksDBDatabase::setup_db()
    {
        try
        {
            _options.create_if_missing = _config.create_if_missing;
            _options.max_open_files = _config.max_open_files;
            _options.use_fsync = _config.use_fsync;
            _options.use_direct_reads = _config.use_direct_reads;
            _options.use_direct_io_for_flush_and_compaction =
                _config.use_direct_io_for_flush_and_compaction;
            _options.max_background_flushes = _config.max_background_flushes;
            _options.compression = _config.compression;

            _options.compaction_style = _config.compaction_style;
            _options.level0_file_num_compaction_trigger =
                _config.level0_file_num_compaction_trigger;
            _options.level0_slowdown_writes_trigger =
                _config.level0_slowdown_writes_trigger;
            _options.level0_stop_writes_trigger =
                _config.level0_stop_writes_trigger;

            _options.write_buffer_size = _config.write_buffer_size;
            _options.max_write_buffer_number = _config.max_write_buffer_number;
            _options.min_write_buffer_number_to_merge =
                _config.min_write_buffer_number_to_merge;
            _options.target_file_size_base = _config.target_file_size_base;
            _options.max_bytes_for_level_base = _config.max_bytes_for_level_base;
            _options.bytes_per_sync = _config.bytes_per_sync;

            _write_options.sync = _config.write_sync;
            _write_options.disableWAL = _config.write_disable_wal;

            _table_options.no_block_cache = _config.no_block_cache;
            _table_options.block_restart_interval = _config.block_restart_interval;
            _table_options.block_size = _config.block_size;

            _options.IncreaseParallelism(static_cast<int>(
                std::thread::hardware_concurrency()));
            _options.OptimizeLevelStyleCompaction();
            _options.env->SetBackgroundThreads(static_cast<int>(
                _config.background_threads));

            _table_options.filter_policy.reset(
                rocksdb::NewBloomFilterPolicy(_config.new_bloom_filter_policy));

            _options.table_factory.reset(
                rocksdb::NewBlockBasedTableFactory(_table_options));
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::setup_db()",
                exception.what()
            );
        }        
    }

    void RocksDBDatabase::open_db()
    {
        try
        {
            if (!std::filesystem::exists(_file_path))
            {
                std::filesystem::create_directories(_file_path);
            }

            _status = rocksdb::TransactionDB::Open(
                _options, _txn_db_options, _file_path, &_transaction_db);

            if (!_status.ok())
            {                                
                return;
            }

            _object = _transaction_db;
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::open_db()",
                exception.what()
            );
        }        
    }

    void RocksDBDatabase::close_db()
    {
        try
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
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::close_db()",
                exception.what()
            );
        }        
    }

    rocksdb::ColumnFamilyHandle* RocksDBDatabase::get_cf_handle(
        const std::string& name
    )
    {
        try
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
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::get_cf_handle()",
                exception.what()
            );

            return nullptr;
        }        
    }

    void RocksDBDatabase::get_file_path(
        Result<std::string>& result
    )
    {
        result.set_to_good_status_with_value(
            _file_path
        );
    }

    void RocksDBDatabase::is_path_found(
        Result<bool>& result,
        const std::string& path
    )
    {
        std::shared_lock lock(_mutex);

        result.set_to_good_status_with_value(
            std::filesystem::exists(path)
        );
    }

    void RocksDBDatabase::is_key_found(
        Result<bool>& result,
        const std::string& key
    )
    {
        std::shared_lock lock(_mutex);

        if (_object == nullptr)
        {            
            return result.set_to_bad_status_without_value();
        }

        std::string result_value;
        
        result.set_to_good_status_with_value(
            _object->Get(
                _read_options,
                std::string(key),
                &result_value
            ).ok()
        );
    }

    void RocksDBDatabase::remove_value(
        Result<bool>& result,
        const std::string& key
    )
    {
        std::unique_lock lock(_mutex);

        result.set_to_good_status_with_value(
            _object->Delete(_write_options, key).ok()
        );
    }

    void RocksDBDatabase::batch_execute(
        Result<bool>& result
    )
    {
        std::unique_lock lock(_mutex);

        auto result_value = _object->Write(
            _write_options, &_write_batch);
        _write_batch.Clear();

        result.set_to_good_status_with_value(
            result_value.ok()
        );
    }

    void RocksDBDatabase::create_column_family(
        Result<bool>& result,
        const std::string& name
    )
    {
        std::unique_lock lock(_mutex);

        std::string name_key(name);
        rocksdb::ColumnFamilyHandle* handle = nullptr;
        bool result_value = _object->CreateColumnFamily(
            rocksdb::ColumnFamilyOptions(),
            name_key,
            &handle
        ).ok();
        if (result_value)
        {
            _column_families.emplace(
                std::move(name_key),
                handle
            );
        }

        result.set_to_good_status_with_value(
            result_value
        );
    }

    void RocksDBDatabase::drop_column_family(
        Result<bool>& result,
        const std::string& name
    )
    {
        std::unique_lock lock(_mutex);

        std::string name_key(name);
        auto iterator = _column_families.find(name_key);
        if (iterator == _column_families.end())
        {            
            return result.set_to_bad_status_without_value();
        }
        bool result_value = _object->DropColumnFamily(
            iterator->second
        ).ok();
        if (result_value)
        {
            _object->DestroyColumnFamilyHandle(
                iterator->second
            );
            _column_families.erase(iterator);
        }
        result.set_to_good_status_with_value(
            result_value
        );
    }

    void RocksDBDatabase::use_column_family(
        Result<bool>& result,
        const std::string& name
    )
    {
        result.set_to_good_status_with_value(
            _column_families.contains(name)
        );
    }

    void RocksDBDatabase::begin_batch(
        Result<bool>& result
    )
    {
        std::unique_lock lock(_mutex);

        _write_batch.Clear();
    }

    void RocksDBDatabase::commit_batch(
        Result<bool>& result
    )
    {
        batch_execute(result);
    }

    void RocksDBDatabase::create_backup(
        Result<bool>& result,
        const std::string& path
    )
    {
        std::shared_lock lock(_mutex);

        rocksdb::BackupEngine* backup;
        rocksdb::BackupEngineOptions options(
            path
        );
        auto result_value = rocksdb::BackupEngine::Open(
            rocksdb::Env::Default(),
            options,
            &backup
        );
        if (!result_value.ok())
        {            
            return result.set_to_bad_status_without_value();
        }
        result_value = backup->CreateNewBackup(_object);
        delete backup;

        result.set_to_good_status_with_value(
            result_value.ok()
        );
    }

    void RocksDBDatabase::restore_backup(
        Result<bool>& result,
        const std::string& path
    )
    {
        std::unique_lock lock(_mutex);

        close_db();
        rocksdb::BackupEngineReadOnly* backup;
        rocksdb::BackupEngineOptions options(path);
        auto result_value = rocksdb::BackupEngineReadOnly::Open(
            rocksdb::Env::Default(),
            options, &backup
        );
        if (!result_value.ok())
        {            
            return result.set_to_bad_status_without_value();
        }
        result_value = backup->RestoreDBFromLatestBackup(
            _file_path,
            _file_path
        );
        delete backup;
        if (!result_value.ok())
        {            
            return result.set_to_bad_status_without_value();
        }
        open_db();

        result.set_to_good_status_with_value(
            true
        );
    }

    void RocksDBDatabase::create_checkpoint(
        Result<bool>& result,
        const std::string& path
    )
    {
        std::shared_lock lock(_mutex);

        rocksdb::Checkpoint* checkpoint;
        auto result_value = rocksdb::Checkpoint::Create(
            _object,
            &checkpoint
        );
        if (!result_value.ok())
        {            
            return result.set_to_bad_status_without_value();
        }
        result_value = checkpoint->CreateCheckpoint(
            path
        );
        delete checkpoint;

        result.set_to_good_status_with_value(
            result_value.ok()
        );
    }

    void RocksDBDatabase::get_with_bounds(
        Result<std::optional<std::string>>& result,
        const std::string& key,
        const uint64_t& offset,
        const uint64_t& size
    )
    {
        std::shared_lock lock(_mutex);

        if (_object == nullptr)
        {
            return result.set_to_bad_status_without_value();
        }

        rocksdb::PinnableSlice pvalue;
        rocksdb::ReadOptions options;
        options.verify_checksums = true;
        bool result_value = _object->Get(options, _object->DefaultColumnFamily(),
            std::string(key), &pvalue).ok();
        if (!result_value)
        {
            return result.set_to_bad_status_without_value();
        }

        const uint64_t psize = static_cast<uint64_t>(pvalue.size());
        if (offset >= psize)
        {
            return result.set_to_bad_status_without_value();
        }
        
        result.set_to_good_status_with_value(
            std::string(pvalue.data() +
                static_cast<size_t>(offset),
                static_cast<size_t>(
                    std::min<uint64_t>(size, psize - offset)
                )
            )
        );
    }

    void RocksDBDatabase::begin_transaction(
        Result<bool>& result
    )
    {
        std::unique_lock lock(_mutex);

        if (_transaction)
        {
            return result.set_to_bad_status_without_value();
        }
        _transaction = _transaction_db->BeginTransaction(
            _write_options);

        result.set_to_good_status_with_value(
            _transaction != nullptr
        );
    }

    void RocksDBDatabase::commit_transaction(
        Result<bool>& result
    )
    {
        std::unique_lock lock(_mutex);

        if (!_transaction)
        {
            return result.set_to_bad_status_without_value();
        }

        auto result_value = _transaction->Commit();
        delete _transaction;
        _transaction = nullptr;

        result.set_to_good_status_with_value(
            result_value.ok()
        );
    }

    void RocksDBDatabase::rollback_transaction(
        Result<bool>& result
    )
    {
        std::unique_lock lock(_mutex);

        if (!_transaction)
        {            
            return result.set_to_bad_status_without_value();
        }

        auto result_value = _transaction->Rollback();
        delete _transaction;
        _transaction = nullptr;

        result.set_to_good_status_with_value(
            result_value.ok()
        );
    }

    void RocksDBDatabase::remove_value_async(
        Result<std::future<bool>>& result,
        const std::string& key
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, key,
            promise = std::move(promise)]() mutable
            {
                Result<bool> result;

                remove_value(
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

    void RocksDBDatabase::batch_execute_async(
        Result<std::future<bool>>& result
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                Result<bool> result;

                batch_execute(
                    result
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

    void RocksDBDatabase::remove_value_async(
        const std::function<void(const bool& result)>& callback,
        const std::string& key
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, key, callback, promise = std::move(promise)]() mutable
            {
                bool result_value = remove_value(
                    key
                );

                promise.set_value(
                    result_value
                );

                callback(
                    result_value
                );
            }
        );
    }

    void RocksDBDatabase::batch_execute_async(
        const std::function<void(const bool& result)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                bool result_value = batch_execute();

                promise.set_value(
                    result_value
                );

                callback(
                    result_value
                );
            }
        );
    }

    void RocksDBDatabase::remove_value_async(
        const std::function<void(Result<bool>& result)>& callback,
        const std::string& key
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, key, callback, promise = std::move(promise)]() mutable
            {
                Result<bool> result;

                remove_value(result, key);

                promise.set_value(
                    result.get_value()
                );

                callback(
                    result
                );
            }
        );
    }

    void RocksDBDatabase::batch_execute_async(
        const std::function<void(Result<bool>& result)>& callback
    )
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback, promise = std::move(promise)]() mutable
            {
                Result<bool> result;

                batch_execute(result);

                promise.set_value(
                    result.get_value()
                );

                callback(
                    result
                );
            }
        );
    }


    bool RocksDBDatabase::terminate()
    {
        try
        {
            Result<void> result;

            terminate(
                result
            );

            return result.is_status_safe();
        }
        catch (const std::exception& exception)
        {
            LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::terminate()",
                exception.what()
            );

            return false;
        }
    }

    void RocksDBDatabase::terminate(
        Result<void>& result
    )
    {
        close_db();

        result.set_to_good_status_without_value();
    }

    std::future<bool> RocksDBDatabase::terminate_async()
    {
        std::promise<bool> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                promise.set_value(
                    terminate()
                );
            }
        );

        return future;
    }

    void RocksDBDatabase::terminate_async(
        Result<std::future<void>>& result
    )
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this,
            promise = std::move(promise)]() mutable
            {
                Result<void> result;

                terminate(
                    result
                );

                promise.set_value();
            }
        );

        result.set_to_good_status_with_value(
            std::move(future)
        );
    }

    void RocksDBDatabase::terminate_async(
        const std::function<void(const bool& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                callback(
                    terminate()
                );
            }
        );
    }

    void RocksDBDatabase::terminate_async(
        const std::function<void(Result<void>& result)>& callback
    )
    {
        boost::asio::post(
            UTILITIES.BOOST_ASIO_POOL,
            [this, callback]() mutable
            {
                Result<void> result;

                terminate(
                    result
                );

                callback(
                    result
                );
            }
        );
    }

    RocksDBDatabase& RocksDBDatabase::get_instance()
    {
        static RocksDBDatabase instance;

        return instance;
    }

    void RocksDBDatabase::get_instance(
        Result<RocksDBDatabase*>& result
    )
    {
        static RocksDBDatabase instance;

        result.set_to_good_status_with_value(
            &instance
        );
    }
}
