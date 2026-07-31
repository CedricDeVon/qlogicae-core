#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerMetadataFlagsEnumManager \
	)

#include "../includes/file_system_event_listener_metadata_flags_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	FileSystemEventListenerMetadataFlagsEnumManager
		::FileSystemEventListenerMetadataFlagsEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileSystemEventListenerMetadataFlagsEnumManagerConfigurations>()
    {
        
    }

	std::string
		FileSystemEventListenerMetadataFlagsEnumManager
			::convert_enum_to_string(
				const FileSystemEventListenerMetadataFlags&
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
				case (FileSystemEventListenerMetadataFlags::PERMISSIONS):
				{
					return
						"PERMISSIONS";
				}
				case (FileSystemEventListenerMetadataFlags::TIMESTAMP):
				{
					return
						"TIMESTAMP";
				}
				case (FileSystemEventListenerMetadataFlags::OWNERSHIP):
				{
					return
						"OWNERSHIP";
				}
				case (FileSystemEventListenerMetadataFlags::NONE):
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
		FileSystemEventListenerMetadataFlagsEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	FileSystemEventListenerMetadataFlags
		FileSystemEventListenerMetadataFlagsEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				FileSystemEventListenerMetadataFlags::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);				

			if
			(
				value == "PERMISSIONS"
			)
			{
				return
					FileSystemEventListenerMetadataFlags
						::PERMISSIONS;
			}
			else if
			(
				value == "TIMESTAMP"
			)
			{
				return
					FileSystemEventListenerMetadataFlags
						::TIMESTAMP;
			}
			else if
			(
				value == "OWNERSHIP"
			)
			{
				return
					FileSystemEventListenerMetadataFlags
						::OWNERSHIP;
			}
			else if
			(
				value == "NONE"
			)
			{
				return
					FileSystemEventListenerMetadataFlags
						::NONE;
			}
			else
			{
				return
					FileSystemEventListenerMetadataFlags
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
				FileSystemEventListenerMetadataFlags::NONE
			);	
        }
	}

	FileSystemEventListenerMetadataFlags
		FileSystemEventListenerMetadataFlagsEnumManager
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
