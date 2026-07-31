#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		WindowsRegistryManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		WindowsRegistryManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<WindowsRegistryManagerConfigurations>
	{
	public:	
		HKEY
			root_key =
				HKEY_CURRENT_USER;

		std::wstring
			sub_key =
				L"Software\\App";

		std::wstring
			name_key =
				L"Data";

		WindowsRegistryManagerConfigurations();
	};
}

#endif
