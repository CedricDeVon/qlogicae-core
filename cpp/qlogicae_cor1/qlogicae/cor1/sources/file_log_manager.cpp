#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileLogManager \
	)

#include "../includes/file_log_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	FileLogManager
		::FileLogManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileLogManagerConfigurations>()
    {
        
    }

	FileLogManager
		::~FileLogManager()
    {
        destruct();
    }
	
	bool
		FileLogManager
			::destruct()
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			configurations
				.file_output_paths
					.clear();

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
		FileLogManager
			::reset()
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			configurations
				.file_output_paths
					.clear();

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

	std::string
		FileLogManager
			::get_file_output_path(
				const std::string&
					key
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				key
					.empty() ||
				!configurations
					.file_output_paths
						.contains(key) ||
				configurations
					.file_output_paths
						[key] == nullptr
			);

			return
				configurations
					.file_output_paths
						[key]();
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
		FileLogManager
			::is_file_output_path_found(
				const std::string&
					key
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				key.empty()
			);

			return
				configurations
					.file_output_paths
						.contains(key);
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
		FileLogManager
			::set_file_output_path(
				const std::string&
					key,
				const std::function<std::string()>&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				key.empty() ||
				value == nullptr
			);		

			configurations
				.file_output_paths
					[key] = value;

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
		FileLogManager
			::remove_file_output_path(
				const std::string&
					key
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				key.empty() ||
				!configurations
					.file_output_paths
						.contains(key)
			);		

			configurations
				.file_output_paths
					.erase(key);

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
		FileLogManager
			::log_formatted_text(
				const std::string&
					text,
				const LogLevel&
					log_level
			)
	{
		return
			log_raw_text(
				QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<TextLogManager>()					
					.convert_text(
						text,
						log_level
					)
			);
	}

	bool
		FileLogManager
			::log_formatted_text(
				const std::string&
					text
			)
	{
		return
			log_formatted_text(
				text,
				configurations
					.log_level
			);
	}

	bool
		FileLogManager
			::log_formatted_text()
	{
		return
			log_formatted_text(
				configurations
					.text,
				configurations
					.log_level
			);
	}
	
	bool
		FileLogManager
			::log_raw_text(
				const std::string&
					text
			)
	{
		try
        {		
			if
			(
				configurations
					.is_runtime_execution_disabled_for_feature_handling()
			)
			{
				return
					false;
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

			for
			(
				const auto
					[key, callback] :
				configurations
					.file_output_paths
			)
			{				
				std::string file_path =
					callback();

				if (file_path.empty())
				{
					continue;
				}

				fast_io::io::print(
					fast_io::obuf_file(
						file_path
					),
					text
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
		FileLogManager
			::log_raw_text()
	{
		return
			log_raw_text(
				configurations
					.text
			);
	}
}

#endif
