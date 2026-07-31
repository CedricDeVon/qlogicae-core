#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		MutexManager \
	)

#include "../includes/mutex_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{           
	MutexManager
		::MutexManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<MutexManagerConfigurations>()
    {
        
    }

    bool
        MutexManager::lock_micro_mutex(
            const void*
				pointer,
            const std::string&
				name
        )
    {
       try
       {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				pointer == nullptr ||
				name.empty()
			);	

#ifdef _M_X64
            folly::MicroSpinLock*
                micro_spin_lock =
                &folly_micro_spin_lock_collection
                [
					std::pair
					{
						const_cast<void*>(
							pointer
						),
						name
					}
                ];

            micro_spin_lock->lock();
#endif

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
        MutexManager::lock_micro_mutex(
            const void*
				pointer
        )
    {
		return
			lock_micro_mutex(
				pointer,
				configurations.name
			);
    }

    bool
        MutexManager::unlock_micro_mutex(
            const void*
				pointer,
            const std::string&
				name
        )
    {
        try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				pointer == nullptr ||
				name.empty()
			);	

#ifdef _M_X64
			void*
				raw_pointer =
					const_cast<void*>(
						pointer
					);

            folly::MicroSpinLock*
                micro_spin_lock =
                &folly_micro_spin_lock_collection
                [
					std::pair
					{
						raw_pointer,
						name
					}
                ];

            micro_spin_lock->unlock();
#endif

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
        MutexManager::unlock_micro_mutex(
            const void*
	            pointer
        )
    {		
        return
			unlock_micro_mutex(
				pointer,
				configurations
					.name
			);
    }

    bool
		MutexManager
			::clear_all_collections()
	{
		try
		{			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);	

			mutex_collection
				.clear();

			timed_mutex_collection
				.clear();

			recursive_mutex_collection
				.clear();

			recursive_timed_mutex_collection
				.clear();

			shared_mutex_collection
				.clear();

			boost_mutex_collection
				.clear();

			boost_timed_mutex_collection
				.clear();

			boost_recursive_mutex_collection
				.clear();

			boost_recursive_timed_mutex_collection
				.clear();

			boost_shared_mutex_collection
				.clear();

#ifdef _M_X64
			folly_micro_spin_lock_collection
				.clear();
#endif

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
}

#endif
