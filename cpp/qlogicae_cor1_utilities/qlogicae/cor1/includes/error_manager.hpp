#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ErrorManager \
	)

#include "singleton_manager.hpp"
#include "error_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		ErrorManager
    {
    public:   
		ErrorManagerConfigurations
			configurations;

		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1
		);

		ErrorManager();

		~ErrorManager();

		bool
			construct();

		bool
			destruct();

		bool
			setup(
				const ErrorManagerConfigurations&
					new_configurations
			);

		bool
			reset();

		std::string
			transform_to_error_log(
				const std::string&
					title,
				const std::string&
					message
			);

		std::string
			transform_to_error_log(
				const std::string&
					message
			);

		std::string
			transform_to_error_log(
				const std::exception&
					exception
			);

		template <typename OutputType = bool> OutputType
			handle_error_outputs(
				const std::string&
					title,
				const std::string&
					message
			);

		template <typename OutputType = bool> OutputType
			handle_error_outputs(
				const std::string&
					message
			);

		template <typename OutputType = bool> OutputType
			handle_error_outputs(
				const std::exception&
					exception
			);

		template <typename OutputType = bool> OutputType
			handle_error_output_conditions(
				const std::string&
					error_log
			);

		template <typename OutputType = bool> OutputType
			handle_error_outputs_synchronously(
				const std::string&
					error_log
			);

		template <typename OutputType = bool> OutputType
			handle_error_outputs_asynchronously(
				const std::string&
					error_log
			);
    };        

	template <typename OutputType> OutputType
		ErrorManager
			::handle_error_outputs(
				const std::string&
					title,
				const std::string&
					message
			)
	{
		handle_error_output_conditions(
			transform_to_error_log(
				title,
				message
			)
		);

		return
			OutputType{};
	}

	template <typename OutputType> OutputType
		ErrorManager
			::handle_error_outputs(
				const std::string&
					message
			)
	{
		handle_error_output_conditions(
			transform_to_error_log(
				message
			)
		);

		return
			OutputType{};
	}

	template <typename OutputType> OutputType
		ErrorManager
			::handle_error_outputs(
				const std::exception&
					exception
			)
	{
		handle_error_output_conditions(
			transform_to_error_log(
				exception
			)
		);

		return
			OutputType{};
	}

	template <typename OutputType> OutputType
		ErrorManager
			::handle_error_output_conditions(
				const std::string&
					error_log	
			)
	{
		if
		(
			configurations
				.is_runtime_execution_disabled_for_feature_handling()
		)
		{
			return
				OutputType {};
		}

		if
		(
			configurations
				.is_asynchronous_output_enabled
		)
		{
			handle_error_outputs_asynchronously(
				error_log
			);
		}
		else
		{
			handle_error_outputs_synchronously(
				error_log
			);
		}

		return
			OutputType{};
	}

	template <typename OutputType> OutputType
		ErrorManager
			::handle_error_outputs_synchronously(
				const std::string&
					error_log
			)
	{		
		QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
		(
			OutputType {},
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
			QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
		);

		if
		(
			configurations
				.is_enable_output_override_enabled ||
			configurations
				.is_console_output_enabled
		)
		{
			fast_io::io::println(
				fast_io::out(),
				error_log
			);
		}

		if
		(
			configurations
				.is_enable_output_override_enabled ||
			configurations
				.is_file_output_enabled
		)
		{		
			for
			(
				const std::string&
					full_file_output_path :
					configurations
	
						.full_file_output_paths
			)
			{
				if (!std::filesystem::exists(full_file_output_path))
				{
					continue;
				}

				fast_io::native_file
					fast_io_native_file(
						full_file_output_path,
						fast_io::open_mode::app
					);

				fast_io::io::println(
					fast_io_native_file,
					error_log
				);
			}
		}

		if
		(
			configurations
				.is_enable_output_override_enabled ||
			configurations
				.is_gui_output_enabled
		)
		{

		}

		if
		(
			configurations
				.is_enable_output_override_enabled ||
			configurations
				.is_runtime_throw_output_enabled
		)
		{
			throw
				std::runtime_error(
					error_log
				);
		}

		return
			OutputType {};
	}

	template <typename OutputType> OutputType
		ErrorManager
			::handle_error_outputs_asynchronously(
				const std::string&
					error_log
			)
	{
		QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
		(
			OutputType {},
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
			QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
		);

		std::vector<std::future<void>>
			futures;

		if
		(
			configurations
				.is_asynchronous_console_output_enabled &&
			(configurations
				.is_enable_output_override_enabled ||
			configurations
				.is_console_output_enabled)
		)
		{
			futures.push_back(
				std::async(
					std::launch::async,
					[&]()
					{
						fast_io::io::println(
							fast_io::out(),
							error_log
						);
					}
				)
			);
		}

		if
		(
			configurations
				.is_asynchronous_file_output_enabled &&
			(configurations
				.is_enable_output_override_enabled ||
			configurations
				.is_file_output_enabled)
		)
		{
			for
			(
				const std::string&
					full_file_output_path :
					configurations
	
						.full_file_output_paths
			)
			{
				if (!std::filesystem::exists(full_file_output_path))
				{
					continue;
				}

				futures.push_back(
					std::async(
						std::launch::async,
						[&]()
						{						
							fast_io::native_file
								fast_io_native_file(
									full_file_output_path,
									fast_io::open_mode::app
								);

							fast_io::io::println(
								fast_io_native_file,
								error_log
							);
						}
					)
				);
			}
		}

		if
		(
			configurations
				.is_asynchronous_runtime_throw_output_enabled &&
			(configurations
				.is_enable_output_override_enabled ||
			configurations
				.is_gui_output_enabled)
		)
		{
			futures.push_back(
				std::async(
					std::launch::async,
					[&]()
					{
						
					}
				)
			);
		}

		if
		(
			configurations
				.is_asynchronous_runtime_throw_output_enabled &&
			(configurations
				.is_enable_output_override_enabled ||
			configurations
				.is_runtime_throw_output_enabled)
		)
		{
			futures.push_back(
				std::async(
					std::launch::async,
					[&]()
					{
						throw
							std::runtime_error(
								error_log
							);
					}
				)
			);
		}

		for
		(
			std::future<void>&
				future :
				futures
		)
		{
			future.get();
		}

		return
			OutputType{};
	}	
}

#endif
