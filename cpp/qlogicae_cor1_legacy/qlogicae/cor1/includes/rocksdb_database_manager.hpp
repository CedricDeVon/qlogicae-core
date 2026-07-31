#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RocksDbDatabaseManager \
	)

#include "rocksdb_database_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		RocksDbDatabaseManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RocksDbDatabaseManagerConfigurations>
    {
    public:        
		rocksdb::DB*
			object{};

		rocksdb::Options
			options;

		rocksdb::WriteOptions
			write_options;

		rocksdb::BlockBasedTableOptions
			table_options;

		rocksdb::TransactionDBOptions
			txn_db_options;

		rocksdb::Status
			status;

		rocksdb::WriteBatch
			write_batch;

		std::vector<std::string>
			cf_names;

		rocksdb::ReadOptions
			read_options;

		rocksdb::Transaction*
			transaction{};

		rocksdb::TransactionDB*
			transaction_db{};

		rocksdb::TransactionDBOptions
			txn_options;

		std::unique_ptr<const rocksdb::FilterPolicy>
			bloom_filter;

		std::unordered_map<std::string, rocksdb::ColumnFamilyHandle*>
			column_families;

		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_3
		);

		RocksDbDatabaseManager();

		~RocksDbDatabaseManager();

		bool
			construct();

		bool
			destruct();

		bool
			setup(
				const RocksDbDatabaseManagerConfigurations&
					new_configurations
			) override;

		bool
			is_path_found(
				const std::string&
					value
			);

		bool
			is_key_found(
				const std::string&
					value
			);

		bool
			remove_value(
				const std::string&
					value
			);

		bool
			create_column_family(
				const std::string&
					value
			);

		bool
			drop_column_family(
				const std::string&
					value
			);

		bool
			use_column_family(
				const std::string&
					value
			);

		bool
			create_backup(
				const std::string&
					value
			);

		bool
			restore_backup(
				const std::string&
					value
			);

		bool
			create_checkpoint(
				const std::string&
					value
			);

		std::string
			get_with_bounds(
				const std::string&
					value,
				const uint64_t&
					minimum,
				const uint64_t&
					maximum
			);

		rocksdb::ColumnFamilyHandle*
			get_cf_handle(
				const std::string&
					name
			);

		bool
			batch_execute();

		bool
			begin_batch();

		bool
			commit_batch();

		bool
			begin_transaction();

		bool
			commit_transaction();

		bool
			rollback_transaction();

		bool
			clear();

		bool
			open();

		bool
			close();

		template <typename Type> bool 
			set_value(
				const std::string&
					value,
				const Type&
					type
			);

		template <typename Type> bool 
			batch_set_value(
				const std::string&
					value,
				const Type&
					type
			);

		template <typename Type> bool 
			batch_remove_value(
				const std::string&
					value,
				const Type&
					type
			);

		template <typename Type> Type
			get_value(
				const std::string&
					value
			);

		template <typename Type> std::string
			serialize(
				const Type&
					value
			);

		template <typename Type> Type
			deserialize(
				const std::string&
					value
			);
    };    

    template <typename Type> Type
		RocksDbDatabaseManager
			::get_value(
				const std::string&
					key
			)
	{
		try
		{
			if
			(
				configurations
					.is_runtime_execution_disabled_for_feature_handling() ||				
				(
					configurations
						.is_edge_case_enabled_for_feature_handling() &&
					(
						key.empty()
					)
				)
			)
			{
				return
					Type {};
			}

			boost::unique_lock<boost::mutex>
				mutex_lock;
			if (configurations.is_thread_safety_enabled_for_feature_handling())
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						feature_handling_mutex_1
					);
			}

			std::string value;

			object->Get(read_options, key, &value);

			return
				value;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}

	template <typename Type> bool
		RocksDbDatabaseManager
			::set_value(
				const std::string&
					key,
				const Type&
					value
			)
	{
		try
		{			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				key.empty()
			);

			auto result_value = object->Put(
				write_options,
				key,
				serialize(value)
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

	template <typename Type> bool
		RocksDbDatabaseManager
			::batch_set_value(
				const std::string&
					key,
				const Type&
					value
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				key.empty()
			);

			write_batch.Put(key, serialize(value));

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

	template <typename Type> bool
		RocksDbDatabaseManager
			::batch_remove_value(
				const std::string&
					key,
				const Type&
					type
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				key.empty()
			);

			write_batch.Delete(key);

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

	template <typename Type> std::string
		RocksDbDatabaseManager
			::serialize(
				const Type&
					value
			)
	{
		try
		{			
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				value,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			return
				value;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	template <typename Type> Type
		RocksDbDatabaseManager
			::deserialize(
				const std::string&
					value
			)
	{
		try
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				value,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			return
				value;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type {}
			);
		}
	}
}

#endif
