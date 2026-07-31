#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RocksDbDatabaseManager \
	)

#include "../includes/rocksdb_database_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{	    
	RocksDbDatabaseManager
		::RocksDbDatabaseManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RocksDbDatabaseManagerConfigurations>()
	{
		construct();
	}

	RocksDbDatabaseManager
		::~RocksDbDatabaseManager()
	{
		destruct();
	}

    bool
		RocksDbDatabaseManager
			::construct()
    {
        try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			RocksDbDatabaseManagerConfigurations
				new_configurations;

			configurations =
				new_configurations;

			options.create_if_missing = configurations.create_if_missing;
            options.max_open_files = configurations.max_open_files;
            options.use_fsync = configurations.use_fsync;
            options.use_direct_reads = configurations.use_direct_reads;
            options.use_direct_io_for_flush_and_compaction =
                configurations.use_direct_io_for_flush_and_compaction;
            options.max_background_flushes = configurations.max_background_flushes;
            options.compression = configurations.compression;

            options.compaction_style = configurations.compaction_style;
            options.level0_file_num_compaction_trigger =
                configurations.level0_file_num_compaction_trigger;
            options.level0_slowdown_writes_trigger =
                configurations.level0_slowdown_writes_trigger;
            options.level0_stop_writes_trigger =
                configurations.level0_stop_writes_trigger;

            options.write_buffer_size = configurations.write_buffer_size;
            options.max_write_buffer_number = configurations.max_write_buffer_number;
            options.min_write_buffer_number_to_merge =
                configurations.min_write_buffer_number_to_merge;
            options.target_file_size_base = configurations.target_file_size_base;
            options.max_bytes_for_level_base = configurations.max_bytes_for_level_base;
            options.bytes_per_sync = configurations.bytes_per_sync;

            write_options.sync = configurations.write_sync;
            write_options.disableWAL = configurations.write_disable_wal;

            table_options.no_block_cache = configurations.no_block_cache;
            table_options.block_restart_interval = configurations.block_restart_interval;
            table_options.block_size = configurations.block_size;

            options.IncreaseParallelism(static_cast<int>(
                std::thread::hardware_concurrency()));
            options.OptimizeLevelStyleCompaction();
            options.env->SetBackgroundThreads(static_cast<int>(
                configurations.background_threads));

            table_options.filter_policy.reset(
                rocksdb::NewBloomFilterPolicy(configurations.new_bloom_filter_policy));

            options.table_factory.reset(
                rocksdb::NewBlockBasedTableFactory(table_options));

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

    bool
		RocksDbDatabaseManager
			::destruct()
    {
        try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
    }

	bool
		RocksDbDatabaseManager
			::setup(
				const RocksDbDatabaseManagerConfigurations&
					new_configurations
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			configurations =
				new_configurations;

			options.create_if_missing = configurations.create_if_missing;
            options.max_open_files = configurations.max_open_files;
            options.use_fsync = configurations.use_fsync;
            options.use_direct_reads = configurations.use_direct_reads;
            options.use_direct_io_for_flush_and_compaction =
                configurations.use_direct_io_for_flush_and_compaction;
            options.max_background_flushes = configurations.max_background_flushes;
            options.compression = configurations.compression;

            options.compaction_style = configurations.compaction_style;
            options.level0_file_num_compaction_trigger =
                configurations.level0_file_num_compaction_trigger;
            options.level0_slowdown_writes_trigger =
                configurations.level0_slowdown_writes_trigger;
            options.level0_stop_writes_trigger =
                configurations.level0_stop_writes_trigger;

            options.write_buffer_size = configurations.write_buffer_size;
            options.max_write_buffer_number = configurations.max_write_buffer_number;
            options.min_write_buffer_number_to_merge =
                configurations.min_write_buffer_number_to_merge;
            options.target_file_size_base = configurations.target_file_size_base;
            options.max_bytes_for_level_base = configurations.max_bytes_for_level_base;
            options.bytes_per_sync = configurations.bytes_per_sync;

            write_options.sync = configurations.write_sync;
            write_options.disableWAL = configurations.write_disable_wal;

            table_options.no_block_cache = configurations.no_block_cache;
            table_options.block_restart_interval = configurations.block_restart_interval;
            table_options.block_size = configurations.block_size;

            options.IncreaseParallelism(static_cast<int>(
                std::thread::hardware_concurrency()));
            options.OptimizeLevelStyleCompaction();
            options.env->SetBackgroundThreads(static_cast<int>(
                configurations.background_threads));

            table_options.filter_policy.reset(
                rocksdb::NewBloomFilterPolicy(configurations.new_bloom_filter_policy));

            options.table_factory.reset(
                rocksdb::NewBlockBasedTableFactory(table_options));

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::is_path_found(
				const std::string&
					value
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				value.empty()
			);		

			return
				std::filesystem::exists(value);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::is_key_found(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				value.empty() ||
				object == nullptr
			);			

			std::string result;

			return object->Get(
				read_options,
				std::string(value),
				&result
			).ok();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::remove_value(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				value.empty()
			);	

			return
				object->Delete(
					write_options,
					value
				).ok();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::create_column_family(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				value.empty()
			);	

			rocksdb::ColumnFamilyHandle* handle = nullptr;

			bool result = object->CreateColumnFamily(
				rocksdb::ColumnFamilyOptions(), value, &handle).ok();

			if (result)
			{
				column_families.emplace(std::move(value), handle);
			}
	
			return
				result;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::drop_column_family(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				value.empty()
			);		

			auto iterator = column_families.find(value);

			if (iterator == column_families.end())
			{
				return
					false;
			}

			bool result = object->DropColumnFamily(iterator->second).ok();

			if (result)
			{
				object->DestroyColumnFamilyHandle(iterator->second);
				column_families.erase(iterator);
			}

			return
				result;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::use_column_family(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				value.empty()
			);
		
			return
				column_families.contains(
					value
				);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::create_backup(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				value.empty()
			);			

			rocksdb::BackupEngine* backup;
			rocksdb::BackupEngineOptions options(value);

			auto result = rocksdb::BackupEngine::Open(
				rocksdb::Env::Default(), options, &backup);

			if (!result.ok())
			{
				return false;
			}

			result = backup->CreateNewBackup(object);
			delete backup;

			return
				result.ok();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::restore_backup(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				value.empty()
			);		

			close();

			rocksdb::BackupEngineReadOnly* backup;
			rocksdb::BackupEngineOptions options(value);

			auto result = rocksdb::BackupEngineReadOnly::Open(
				rocksdb::Env::Default(),
				options, &backup
			);

			if (!result.ok())
			{
				return false;
			}

			result = backup->RestoreDBFromLatestBackup(configurations.file_path, configurations.file_path);
			delete backup;
			if (!result.ok())
			{
				return false;
			}
		
			return
				open();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::create_checkpoint(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				value.empty()
			);			

			rocksdb::Checkpoint* checkpoint;
			auto string = rocksdb::Checkpoint::Create(object, &checkpoint);

			if (!string.ok())
			{
				return false;
			}

			string = checkpoint->CreateCheckpoint(value);
			delete checkpoint;

			return
				string.ok();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::string
		RocksDbDatabaseManager
			::get_with_bounds(
				const std::string&
					value,
				const uint64_t&
					size,
				const uint64_t&
					offset
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				value.empty() ||
				object == nullptr
			);			

			rocksdb::PinnableSlice pvalue;
			rocksdb::ReadOptions options;
			options.verify_checksums = true;

			auto s = object->Get(options, object->DefaultColumnFamily(),
				value, &pvalue);

			if (!s.ok())
			{
				return
					"";
			}

			const uint64_t psize =
				static_cast<uint64_t>(pvalue.size());

			if (offset >= psize)
			{
				return
					"";
			}

			const uint64_t max_size =
				psize - offset;

			const size_t use_size =
				static_cast<size_t>(std::min<uint64_t>(size, max_size));

			return
				std::string(
					pvalue.data() + static_cast<size_t>(offset), use_size
				);
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			return
				handle_error_outputs<std::string>(
					exception
				);
        }
	}

	bool
		RocksDbDatabaseManager
			::batch_execute()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);	

			auto string = object->Write(
				write_options, &write_batch);
			write_batch.Clear();

			return
				string.ok();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::begin_batch()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);	

			write_batch.Clear();

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::commit_batch()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);	

			return
				batch_execute();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::begin_transaction()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				transaction
			);		

			transaction = transaction_db->BeginTransaction(
				write_options
			);

			return
				transaction != nullptr;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::commit_transaction()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!transaction
			);	

			auto string = transaction->Commit();
			delete transaction;
			transaction = nullptr;

			return
				string.ok();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::rollback_transaction()
	{
		try
        {				
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!transaction
			);			

			auto string = transaction->Rollback();
			delete transaction;
			transaction = nullptr;

			return
				string.ok();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::close()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_3,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);	

			if (object != nullptr)
            {
                for (auto& [name, handle] : column_families)
                {
                    if (handle != nullptr)
                    {
                        object->DestroyColumnFamilyHandle(handle);
                    }
                }
            }
            column_families.clear();

            if (transaction != nullptr)
            {
                delete transaction;
                transaction = nullptr;
            }
            if (transaction_db != nullptr)
            {
                delete transaction_db;
                transaction_db = nullptr;
            }
            object = nullptr;

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::clear()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			close();

			rocksdb::Options options;
			rocksdb::Status status = rocksdb::DestroyDB(configurations.file_path, options);

			if (!status.ok())
			{
				return
					false;
			}			

			return
				open();
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		RocksDbDatabaseManager
			::open()
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			if (!std::filesystem::exists(configurations.file_path))
            {
                std::filesystem::create_directories(configurations.file_path);
            }

            status = rocksdb::TransactionDB::Open(
                options, txn_db_options, configurations.file_path, &transaction_db);

            if (!status.ok())
            {                                
                return
					false;
            }

            object = transaction_db;

			return
				true;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	rocksdb::ColumnFamilyHandle*
		RocksDbDatabaseManager
			::get_cf_handle(
				const std::string&
					name
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);	

            auto iterator = column_families.find(name);
            if (iterator != column_families.end())
            {
                return iterator->second;
            }
            if (object != nullptr)
            {
                return object->DefaultColumnFamily();
            }

			return
				nullptr;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				nullptr
			);
        }
	}
}

#endif

