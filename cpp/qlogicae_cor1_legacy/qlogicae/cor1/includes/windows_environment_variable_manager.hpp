#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsEnvironmentVariableManager \
	)

#include "windows_environment_variable_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	class
		WindowsEnvironmentVariableManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<WindowsEnvironmentVariableManagerConfigurations>
	{
	public:
		WindowsEnvironmentVariableManager();

		std::wstring
			get_value(
				const std::wstring&
					key
			);

		bool
			set_value(
				const std::wstring&
					key,
				const std::wstring&
					value
			);

		bool
			remove_value(
				const std::wstring&
					key
			);

		std::string
			get_value(
				const std::string&
					key
			);

		bool
			set_value(
				const std::string&
					key,
				const std::string&
					value
			);

		bool
			remove_value(
				const std::string&
					key
			);
	};
}

#endif
