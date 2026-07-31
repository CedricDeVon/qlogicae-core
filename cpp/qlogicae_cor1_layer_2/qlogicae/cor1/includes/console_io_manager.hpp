#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ConsoleIoManager \
	)

#include "console_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		ConsoleIoManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<ConsoleIoManagerConfigurations>
    {
    public:
		ConsoleIoManager();

		std::string
			scan();

		std::string
			builtin_scan();

		bool
			print(
				const std::string&
					text
			);

		bool
			builtin_print(
				const std::string&
					text
			);

		bool
			print_with_new_line(
				const std::string&
					text
			);

		bool
			builtin_print_with_new_line(
				const std::string&
					text
			);
	};
}

#endif
