#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		QLogicaeApplicationManager \
	)

#include "qlogicae_application_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		QLogicaeApplicationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<QLogicaeApplicationManagerConfigurations>
    {
    public:
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		QLogicaeApplicationManager();
		
		~QLogicaeApplicationManager();

		bool
			construct();

		bool
			destruct();

		bool
			setup(
				const QLogicaeApplicationManagerConfigurations&
					new_configurations
			);

		bool
            reset();
    };
}

#endif


/*

relative_private_qlogicae_folder_path =
	".qlogicae";

relative_public_qlogicae_folder_path =
	"qlogicae";

relative_application_name_folder_path =
	"qlogicae";

relative_application_version_name_folder_path =
	"v1.0.0";

relative_application_environment_name_folder_path =
	"development";

relative_log_folder_path =
	"log";

relative_log_date_folder_path =
	"date";

relative_log_level_folder_path =
	"level";

relative_all_log_file_path =
	"all.log";

relative_info_log_file_path =
	"info.log";

relative_debug_log_file_path =
	"debug.log";

relative_warning_log_file_path =
	"warning.log";

relative_success_log_file_path =
	"success.log";

relative_critical_log_file_path =
	"critical.log";

relative_error_log_file_path =
	"error.log";

relative_cache_folder_path =
	"cache";

relative_main_folder_path =
	"main";

relative_assets_folder_path =
	"assets";

relative_documentation_folder_path =
	"documentation";

relative_environment_json_file_path =
	"environment.json";

relative_license_txt_file_path =
	"LICENSE.txt";

relative_application_folder_path =
	"application";

relative_application_icon_file_path =
	"application.ico";

relative_qlogicae_json_file_path =
	"qlogicae.json";

relative_configurations_folder_path =
	"configurations";

relative_development_folder_path =
	"development";

relative_debug_folder_path =
	"debug";

relative_test_folder_path =
	"test";

relative_release_folder_path =
	"release";



std::string
	relative_windows_registry_software_qlogicae_folder_path;

relative_windows_registry_software_qlogicae_folder_path =
	"Software\\QLogicae";

std::string
	relative_private_qlogicae_folder_path;

std::string
	relative_public_qlogicae_folder_path;

std::string
	relative_application_name_folder_path;

std::string
	relative_application_version_name_folder_path;

std::string
	relative_application_environment_name_folder_path;

std::string
	relative_log_folder_path;

std::string
	relative_log_date_folder_path;

std::string
	relative_log_level_folder_path;

std::string
	relative_all_log_file_path;

std::string
	relative_info_log_file_path;

std::string
	relative_debug_log_file_path;

std::string
	relative_warning_log_file_path;

std::string
	relative_success_log_file_path;

std::string
	relative_critical_log_file_path;

std::string
	relative_error_log_file_path;

std::string
	relative_cache_folder_path;

std::string
	relative_main_folder_path;

std::string
	relative_assets_folder_path;

std::string
	relative_documentation_folder_path;

std::string
	relative_environment_json_file_path;

std::string
	relative_license_txt_file_path;

std::string
	relative_application_folder_path;

std::string
	relative_application_icon_file_path;

std::string
	relative_qlogicae_json_file_path;

std::string
	relative_configurations_folder_path;

std::string
	relative_development_folder_path;

std::string
	relative_debug_folder_path;

std::string
	relative_test_folder_path;

std::string
	relative_release_folder_path;



*/
