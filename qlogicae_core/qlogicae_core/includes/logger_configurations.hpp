#pragma once

#include "time_zone.hpp"
#include "log_medium.hpp"
#include "time_format.hpp"

#include <string>

namespace QLogicaeCore
{
	struct LoggerConfigurations
	{
		std::string name = "";
		
		bool is_enabled =
			false;
	
		bool is_format_enabled =
			false;

		LogMedium medium =
			LogMedium::CONSOLE;

		TimeZone time_zone =
			TimeZone::LOCAL;

		TimeFormat format =
			TimeFormat::FULL_TIMESTAMP;

		bool is_console_enabled =
			false;
		
		bool is_console_format_enabled =
			false;	

		bool is_file_enabled =
			false;

		bool is_file_format_enabled =
			false;

		bool is_file_collectivization_enabled =
			false;

		bool is_file_collectivization_format_enabled =
			false;

		std::string relative_root_folder_path =
			"";

		std::string file_collectivization_file_name =
			"all.log";

		std::string file_collectivization_file_path =
			"";

		std::string file_collectivization_folder_path =
			"";		

		bool is_file_fragmentation_enabled =
			false;
		
		bool is_file_fragmentation_format_enabled =
			false;

		TimeFormat file_fragmentation_file_name_format =
			TimeFormat::DATE_DASHED;

		std::string file_fragmentation_folder_path =
			"";		

		std::string file_exception_file_name =
			"exception.log";

		std::string file_exception_folder_path =
			"";

		std::string file_exception_file_path =
			"";

		bool is_file_custom_enabled =
			false;

		bool is_file_custom_format_enabled =
			false;

		std::vector<std::string> file_custom_output_paths =
			{};		
	};

	inline static LoggerConfigurations DEFAULT_LOGGER_CONFIGURATIONS;
}
