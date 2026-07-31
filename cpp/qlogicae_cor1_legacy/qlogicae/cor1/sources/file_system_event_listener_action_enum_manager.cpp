#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEventListenerActionEnumManager \
	)

#include "../includes/file_system_event_listener_action_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	FileSystemEventListenerActionEnumManager
		::FileSystemEventListenerActionEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileSystemEventListenerActionEnumManagerConfigurations>()
    {
        
    }

	std::string
		FileSystemEventListenerActionEnumManager
			::convert_enum_to_string(
				const FileSystemEventListenerAction&
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
				case (FileSystemEventListenerAction::CREATED):
				{
					return
						"CREATED";
				}
				case (FileSystemEventListenerAction::DELETED):
				{
					return
						"DELETED";
				}
				case (FileSystemEventListenerAction::MODIFIED):
				{
					return
						"MODIFIED";
				}
				case (FileSystemEventListenerAction::RENAMED):
				{
					return
						"RENAMED";
				}
				case (FileSystemEventListenerAction::MOVED):
				{
					return
						"MOVED";
				}
				case (FileSystemEventListenerAction::METADATA_CHANGED):
				{
					return
						"METADATA_CHANGED";
				}
				case (FileSystemEventListenerAction::UNKNOWN):
				{
					return
						"UNKNOWN";
				}	
				case (FileSystemEventListenerAction::NONE):
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
		FileSystemEventListenerActionEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	FileSystemEventListenerAction
		FileSystemEventListenerActionEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				FileSystemEventListenerAction::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);				

			if
			(
				value == "CREATED"
			)
			{
				return
					FileSystemEventListenerAction
						::CREATED;
			}
			else if
			(
				value == "DELETED"
			)
			{
				return
					FileSystemEventListenerAction
						::DELETED;
			}
			else if
			(
				value == "MODIFIED"
			)
			{
				return
					FileSystemEventListenerAction
						::MODIFIED;
			}
			else if
			(
				value == "RENAMED"
			)
			{
				return
					FileSystemEventListenerAction
						::RENAMED;
			}
			else if
			(
				value == "MOVED"
			)
			{
				return
					FileSystemEventListenerAction
						::MOVED;
			}
			else if
			(
				value == "METADATA_CHANGED"
			)
			{
				return
					FileSystemEventListenerAction
						::METADATA_CHANGED;
			}
			else if
			(
				value == "UNKNOWN"
			)
			{
				return
					FileSystemEventListenerAction
						::UNKNOWN;
			}
			else
			{
				return
					FileSystemEventListenerAction
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
				FileSystemEventListenerAction::NONE
			);	
        }
	}

	FileSystemEventListenerAction
		FileSystemEventListenerActionEnumManager
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
