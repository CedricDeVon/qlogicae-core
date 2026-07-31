#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileSystemEntityEnumManager \
	)

#include "../includes/file_system_entity_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	FileSystemEntityEnumManager
		::FileSystemEntityEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<FileSystemEntityEnumManagerConfigurations>()
    {
        
    }

	std::string
		FileSystemEntityEnumManager
			::convert_enum_to_string(
				const FileSystemEntity&
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
				case (FileSystemEntity::ALL):
				{
					return
						"ALL";
				}
				case (FileSystemEntity::FOLDER):
				{
					return
						"FOLDER";
				}
				case (FileSystemEntity::FILE):
				{
					return
						"FILE";
				}
				case (FileSystemEntity::NONE):
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
		FileSystemEntityEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	FileSystemEntity
		FileSystemEntityEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				FileSystemEntity::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);				

			if
			(
				value == "ALL"
			)
			{
				return
					FileSystemEntity
						::ALL;
			}
			else if
			(
				value == "FOLDER"
			)
			{
				return
					FileSystemEntity
						::FOLDER;
			}
			else if
			(
				value == "FILE"
			)
			{
				return
					FileSystemEntity
						::FILE;
			}
			else if
			(
				value == "NONE"
			)
			{
				return
					FileSystemEntity
						::NONE;
			}
			else
			{
				return
					FileSystemEntity
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
				FileSystemEntity::NONE
			);	
        }
	}

	FileSystemEntity
		FileSystemEntityEnumManager
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
