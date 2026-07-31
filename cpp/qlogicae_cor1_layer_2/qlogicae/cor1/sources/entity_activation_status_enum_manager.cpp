#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EntityActivationStatusEnumManager \
	)

#include "../includes/entity_activation_status_enum_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	EntityActivationStatusEnumManager
		::EntityActivationStatusEnumManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<EntityActivationStatusEnumManagerConfigurations>()
    {
        
    }

	std::string
		EntityActivationStatusEnumManager
			::convert_enum_to_string(
				const EntityActivationStatus&
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
				case (EntityActivationStatus::ACTIVE):
				{
					return
						"ACTIVE";
				}
				case (EntityActivationStatus::INACTIVE):
				{
					return
						"INACTIVE";
				}
				case (EntityActivationStatus::PENDING):
				{
					return
						"PENDING";
				}
				case (EntityActivationStatus::NONE):
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
		EntityActivationStatusEnumManager
			::convert_enum_to_string()
	{
		return
			convert_enum_to_string(
				configurations
					.type
			);
	}

	EntityActivationStatus
		EntityActivationStatusEnumManager
			::convert_string_to_enum(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				EntityActivationStatus::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);			

			if
			(
				value == "ACTIVE"
			)
			{
				return
					EntityActivationStatus
						::ACTIVE;
			}
			else if
			(
				value == "INACTIVE"
			)
			{
				return
					EntityActivationStatus
						::INACTIVE;
			}
			else if
			(
				value == "PENDING"
			)
			{
				return
					EntityActivationStatus
						::PENDING;
			}
			else if
			(
				value == "NONE"
			)
			{
				return
					EntityActivationStatus
						::NONE;
			}
			else
			{
				return
					EntityActivationStatus
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
				EntityActivationStatus::NONE
			);			
        }
	}

	EntityActivationStatus
		EntityActivationStatusEnumManager
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
