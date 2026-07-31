#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerSourceEnumManager \
	)

#include "../includes/file_system_event_listener_source_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	FileSystemEventListenerSourceEnumManager
		::FileSystemEventListenerSourceEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileSystemEventListenerSourceEnumManagerConfigurations>()
    {
        
    }

	std::string
		FileSystemEventListenerSourceEnumManager
			::convert_enum_to_string(
				const FileSystemEventListenerSource&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				"NONE",
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);		

			switch (value)
			{
				case (FileSystemEventListenerSource::NATIVE):
				{
					return
						"NATIVE";
				}
				case (FileSystemEventListenerSource::SYNTHETIC):
				{
					return
						"SYNTHETIC";
				}
				case (FileSystemEventListenerSource::NONE):
				{
					return
						"NONE";
				}				
				default:
				{
					return
						"NONE";
				}
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {	
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				"NONE"
			);
        }
	}

	std::string
		FileSystemEventListenerSourceEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	FileSystemEventListenerSource
		FileSystemEventListenerSourceEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				FileSystemEventListenerSource::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);				

			if
			(
				value == "NATIVE"
			)
			{
				return
					FileSystemEventListenerSource
						::NATIVE;
			}
			else if
			(
				value == "SYNTHETIC"
			)
			{
				return
					FileSystemEventListenerSource
						::SYNTHETIC;
			}
			else
			{
				return
					FileSystemEventListenerSource
						::NONE;
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {		
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				FileSystemEventListenerSource::NONE
			);	
        }
	}

	FileSystemEventListenerSource
		FileSystemEventListenerSourceEnumManager
			::convert_string_to_enum()
	{
		return
			convert_string_to_enum(
				convert_enum_to_string(
					configurations
						.type
				)
			);
	}
}

#endif
