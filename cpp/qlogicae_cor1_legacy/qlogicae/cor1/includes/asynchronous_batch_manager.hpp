#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		AsynchronousBatchManager \
	)

#include "asynchronous_batch_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		AsynchronousBatchManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<AsynchronousBatchManagerConfigurations>
    {
    public:		
		AsynchronousBatchManager();

		~AsynchronousBatchManager();

		bool
			construct();

		bool
			destruct();

		std::unordered_map<std::string, std::any>
			execute_await_batch(
				const std::unordered_map<std::string, std::function<std::any()>>&
					values
			);

		std::unordered_map<std::string, std::future<std::any>>
			execute_async_batch(
				const std::unordered_map<std::string, std::function<std::any()>>&
					values
			);
    };
}

#endif
