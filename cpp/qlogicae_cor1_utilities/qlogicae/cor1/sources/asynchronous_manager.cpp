#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		AsynchronousManager \
	)

#include "../includes/asynchronous_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	boost::asio::io_context
		AsynchronousManager::io_context;

	boost::asio::strand<decltype(AsynchronousManager::io_context.get_executor())>
		AsynchronousManager::io_strand(
			AsynchronousManager::io_context.get_executor());

	boost::asio::executor_work_guard<boost::asio::io_context::executor_type>
		AsynchronousManager::work_guard =
			boost::asio::make_work_guard(
				AsynchronousManager::io_context
			);

	std::vector<std::thread>
		AsynchronousManager::thread_workers;

	std::shared_ptr<boost::asio::thread_pool>
		AsynchronousManager
			::main_thread_pool =
				nullptr;

	std::shared_ptr<boost::asio::thread_pool>
		AsynchronousManager
			::temporary_thread_pool =
				nullptr;



    AsynchronousManager
		::AsynchronousManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<AsynchronousManagerConfigurations>()
    {
        construct();
    }

    AsynchronousManager
		::~AsynchronousManager()
    {
		destruct();
    }

    bool
        AsynchronousManager
			::construct()
    {
        try
        {						
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			begin_io_workers();

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
        AsynchronousManager
			::destruct()
    {
        try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			return
				complete_io_workers() ||
				complete_all_threads();
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
		AsynchronousManager
			::begin_one_thread(
				const std::function<void()>&
					callback
			)
    {
        try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				callback == nullptr
			);

            if (main_thread_pool == nullptr)
            {
                main_thread_pool =
                    std::make_shared<boost::asio::thread_pool>(
                        std::thread::hardware_concurrency()
                    );
            }

            boost::asio::post(
                *main_thread_pool,
                [this, callback]()
                {
                    try
                    {
                        callback();
                    }
                    catch
                    (
                        const std::exception&
                            exception
                    )
                    {
						handle_error_outputs(
							exception
						);
                    }
                }
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
		AsynchronousManager
			::begin_io_workers()
    {
        try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);
		
			size_t
				count =
					std::thread::hardware_concurrency() * 2;
			while (--count)
			{
				thread_workers.emplace_back(
					[]
					{
						io_context.run();
					}
				);
			}

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
		AsynchronousManager
			::complete_all_threads()
    {
        try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			temporary_thread_pool =
				main_thread_pool;

			main_thread_pool.reset();

			if (temporary_thread_pool)
			{
				temporary_thread_pool->join();
            }

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
		AsynchronousManager
			::complete_io_workers()
    {
        try
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);
		
			work_guard.reset();
			io_context.stop();
			for
			(
				auto&
					thread_worker :
					thread_workers
			)
			{
				if (thread_worker.joinable())
				{
					thread_worker.join();
				}
			}					
			thread_workers.clear();

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
		AsynchronousManager
			::co_spawn_strand_async(
				const std::function<void()>&
					implementation_method
		)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				implementation_method == nullptr
			);

			boost::asio::co_spawn(
				io_strand,
				[this, implementation_method]()
					-> boost::asio::awaitable<void>
				{
					try
					{
						implementation_method();

						co_return;
					}
					catch
					(
						const std::exception&
							exception
					)
					{
						handle_error_outputs(
							exception
						);

						co_return;
					}						
				},
				boost::asio::detached
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
		AsynchronousManager
			::post_thread_async(
				const std::function<void()>&
					implementation_method
		)
	{
		try
        {   
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				implementation_method == nullptr
			);

            if (main_thread_pool == nullptr)
            {
                main_thread_pool =
                    std::make_shared<boost::asio::thread_pool>(
                        std::thread::hardware_concurrency()
                    );
            }

			boost::asio::post(
                *main_thread_pool,
                [this, implementation_method]()
				{
					try
					{
						implementation_method();
                    }
                    catch
                    (
                        const std::exception&
                            exception
                    )
                    {
						handle_error_outputs(
							exception
						);
                    }
                }
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
		AsynchronousManager
			::dispatch_thread_async(
				const std::function<void()>&
					implementation_method
		)
	{
		try
        {       
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				implementation_method == nullptr
			);

            if (main_thread_pool == nullptr)
            {
                main_thread_pool =
                    std::make_shared<boost::asio::thread_pool>(
                        std::thread::hardware_concurrency()
                    );
            }

			boost::asio::dispatch(
                *main_thread_pool,
                [this, implementation_method]()
				{
					try
					{
						implementation_method();
                    }
                    catch
                    (
                        const std::exception&
                            exception
                    )
                    {
						handle_error_outputs(
							exception
						);
                    }
                }
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
}

#endif
