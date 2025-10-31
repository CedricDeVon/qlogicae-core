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
			true;
	
		bool is_log_format_enabled =
			true;

		LogMedium medium =
			LogMedium::CONSOLE;

		TimeZone time_zone =
			TimeZone::LOCAL;

		TimeFormat log_format =
			TimeFormat::FULL_TIMESTAMP;

		bool is_console_enabled =
			true;
		
		bool is_console_log_format_enabled =
			true;
		


		bool is_file_enabled =
			true;

		bool is_file_log_format_enabled =
			true;



		bool is_file_collectivization_enabled =
			true;

		bool is_file_collectivization_log_format_enabled =
			true;

		std::string file_collectivization_file_name =
			"all.log";

		std::string file_collectivization_folder_path =
			".qlogicae";

		

		bool is_file_fragmentation_enabled =
			true;
		
		bool is_file_fragmentation_log_format_enabled =
			true;

		TimeFormat file_fragmentation_file_name_format =
			TimeFormat::DATE_DMY_SLASHED;

		std::string file_fragmentation_folder_path =
			".qlogicae/logs";
		


		bool is_file_custom_enabled =
			true;

		bool is_file_custom_log_format_enabled =
			true;

		std::vector<std::string> file_custom_output_paths =
			{};		
	};

	inline static LoggerConfigurations DEFAULT_LOGGER_CONFIGURATIONS;
}
