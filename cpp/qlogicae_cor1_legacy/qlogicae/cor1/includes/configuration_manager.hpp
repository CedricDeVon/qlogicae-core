#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ConfigurationManager \
	)

#include "configuration_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	class
		ConfigurationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ConfigurationManagerConfigurations>
	{
	public:
		ConfigurationManager();

		template <typename TypeConfigurations> bool
			setup_defaults(
				const TypeConfigurations&
					new_configurations
			);

		template <typename TypeConfigurations> bool
			reset_defaults();
	};

	template <typename TypeConfigurations> bool
		ConfigurationManager
			::setup_defaults(
				const TypeConfigurations&
					new_configurations
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			QLOGICAE_COR1__BASE__HPP_CPP__RESET_TO_DEFAULT_CONFIGURATIONS_TEMPLATE
			(
				TypeConfigurations
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

	template <typename TypeConfigurations> bool
		ConfigurationManager
			::reset_defaults()
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			QLOGICAE_COR1__BASE__HPP_CPP__RESET_TO_INITIAL_CONFIGURATIONS_TEMPLATE
			(
				TypeConfigurations
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
