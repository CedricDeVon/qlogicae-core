#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		AbstractConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	template <typename DerivedConfigurations> struct
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME
	{
	public:
		bool
			is_edge_case_handling_override_enabled =
				false;

		bool
			is_edge_case_handling_enabled =
				true;

		bool
			is_utility_edge_case_handling_enabled =
				true;

		bool
			is_feature_edge_case_handling_enabled =
				true;

		bool
			is_error_edge_case_handling_enabled =
				true;

		bool
			is_runtime_execution_handling_override_enabled =
				false;

		bool
			is_runtime_execution_handling_enabled =
				true;

		bool
			is_utility_runtime_execution_handling_enabled =
				true;

		bool
			is_feature_runtime_execution_handling_enabled =
				true;

		bool
			is_error_runtime_execution_handling_enabled =
				true;

		bool
			is_thread_safety_handling_override_enabled =
				false;

		bool
			is_thread_safety_handling_enabled =
				true;
			
		bool
			is_utility_thread_safety_handling_enabled =
				true;
			
		bool
			is_feature_thread_safety_handling_enabled =
				true;
			
		bool
			is_error_thread_safety_handling_enabled =
				true;

		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME();

		bool
			is_runtime_execution_enabled_for_utility_handling();

		bool
			is_runtime_execution_enabled_for_feature_handling();

		bool
			is_runtime_execution_enabled_for_error_handling();

		bool
			is_runtime_execution_disabled_for_utility_handling();

		bool
			is_runtime_execution_disabled_for_feature_handling();

		bool
			is_runtime_execution_disabled_for_error_handling();

		bool
			is_edge_case_enabled_for_utility_handling();

		bool
			is_edge_case_enabled_for_feature_handling();

		bool
			is_edge_case_enabled_for_error_handling();

		bool
			is_edge_case_disabled_for_utility_handling();

		bool
			is_edge_case_disabled_for_feature_handling();

		bool
			is_edge_case_disabled_for_error_handling();

		bool
			is_thread_safety_enabled_for_utility_handling();

		bool
			is_thread_safety_enabled_for_feature_handling();

		bool
			is_thread_safety_enabled_for_error_handling();

		bool
			is_thread_safety_disabled_for_utility_handling();

		bool
			is_thread_safety_disabled_for_feature_handling();

		bool
			is_thread_safety_disabled_for_error_handling();
	};

	template <typename DerivedConfigurations>
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME()
	{		
		is_edge_case_handling_override_enabled =
			false;

		is_edge_case_handling_enabled =
			true;

		is_feature_edge_case_handling_enabled =
			true;

		is_runtime_execution_handling_override_enabled =
			false;

		is_runtime_execution_handling_enabled =
			true;

		is_feature_runtime_execution_handling_enabled =
			true;

		is_thread_safety_handling_override_enabled =
			false;

		is_thread_safety_handling_enabled =
			true;
			
		is_feature_thread_safety_handling_enabled =
			true;

		is_utility_edge_case_handling_enabled =
			true;

		is_error_edge_case_handling_enabled =
			true;

		is_utility_runtime_execution_handling_enabled =
			true;

		is_error_runtime_execution_handling_enabled =
			true;

		is_utility_thread_safety_handling_enabled =
			true;			
			
		is_error_thread_safety_handling_enabled =
			true;
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_runtime_execution_enabled_for_utility_handling()
	{
		return
			(is_runtime_execution_handling_override_enabled) ?
				is_runtime_execution_handling_enabled :
				is_utility_runtime_execution_handling_enabled;
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_runtime_execution_enabled_for_feature_handling()
	{
		return
			(is_runtime_execution_handling_override_enabled) ?
				is_runtime_execution_handling_enabled :
				is_feature_runtime_execution_handling_enabled;
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_runtime_execution_enabled_for_error_handling()
	{		
		return
			(is_runtime_execution_handling_override_enabled) ?
				is_runtime_execution_handling_enabled :
				is_error_runtime_execution_handling_enabled;			
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_edge_case_enabled_for_utility_handling()
	{
		return
			(is_edge_case_handling_override_enabled) ?
				is_edge_case_handling_enabled :
				is_utility_edge_case_handling_enabled;
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_edge_case_enabled_for_feature_handling()
	{
		return
			(is_edge_case_handling_override_enabled) ?
				is_edge_case_handling_enabled :
				is_feature_edge_case_handling_enabled;
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_edge_case_enabled_for_error_handling()
	{		
		return
			(is_edge_case_handling_override_enabled) ?
				is_edge_case_handling_enabled :
				is_error_edge_case_handling_enabled;	
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_thread_safety_enabled_for_utility_handling()
	{
		return
			(is_thread_safety_handling_override_enabled) ?
				is_thread_safety_handling_enabled :
				is_utility_thread_safety_handling_enabled;
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_thread_safety_enabled_for_feature_handling()
	{
		return
			(is_thread_safety_handling_override_enabled) ?
				is_thread_safety_handling_enabled :
				is_feature_thread_safety_handling_enabled;
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_thread_safety_enabled_for_error_handling()
	{		
		return
			(is_thread_safety_handling_override_enabled) ?
				is_thread_safety_handling_enabled :
				is_error_thread_safety_handling_enabled;
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_runtime_execution_disabled_for_utility_handling()
	{
		return
			!is_runtime_execution_enabled_for_utility_handling();
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_runtime_execution_disabled_for_feature_handling()
	{
		return
			!is_runtime_execution_enabled_for_feature_handling();
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_runtime_execution_disabled_for_error_handling()
	{		
		return
			!is_runtime_execution_enabled_for_error_handling();
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_edge_case_disabled_for_utility_handling()
	{
		return
			!is_edge_case_enabled_for_utility_handling();
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_edge_case_disabled_for_feature_handling()
	{
		return
			!is_edge_case_enabled_for_feature_handling();
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_edge_case_disabled_for_error_handling()
	{		
		return
			!is_edge_case_enabled_for_error_handling();
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_thread_safety_disabled_for_utility_handling()
	{
		return
			!is_thread_safety_enabled_for_utility_handling();
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_thread_safety_disabled_for_feature_handling()
	{
		return
			!is_thread_safety_enabled_for_feature_handling();
	}

	template <typename DerivedConfigurations> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<DerivedConfigurations>
			::is_thread_safety_disabled_for_error_handling()
	{		
		return
			!is_thread_safety_enabled_for_error_handling();
	}
}

#endif
