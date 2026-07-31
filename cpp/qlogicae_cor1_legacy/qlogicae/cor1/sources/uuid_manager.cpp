#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		UuidManager \
	)

#include "../includes/uuid_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    UuidManager
		::UuidManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<UuidManagerConfigurations>()
	{
		
	}

	bool
		UuidManager
			::is_valid(
				const Uuid&
					type,
				const std::string&
					value
			)
	{
		try
		{			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				type == Uuid::NONE ||
				value.empty()
			);		

			switch (type)
			{
				case (Uuid::V4):
				{
					boost::uuids::string_generator
						generator;
					try
					{
						boost::uuids::uuid uuid =
							generator(value);

						return
							uuid.version() == boost::uuids::uuid::version_random_number_based;
					}
					catch (...)
					{
						return
							false;
					}
				}
				default:
				{
					return
						false;
				}
			}
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
		UuidManager
			::is_valid(
				const std::string&
					value
			)
	{
		return
			is_valid(
				configurations
					.type,
				value
			);
	}

	std::string
		UuidManager
			::generate_uuid(
				const Uuid&
					type
			)
	{
		try
		{			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				type == Uuid::NONE
			);

			switch (type)
			{
				case (Uuid::V4):
				{
					return
						boost::uuids::to_string(
							boost::uuids::random_generator()()
						);
				}
				default:
				{
					return
						"";
				}
			}			
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
		UuidManager
			::generate_uuid()
	{		
		return
			generate_uuid(
				configurations
					.type					
			);
	}
}

#endif
