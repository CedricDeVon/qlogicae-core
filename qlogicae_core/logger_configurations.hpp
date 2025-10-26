#pragma once

#include "time_zone.hpp"
#include "log_medium.hpp"
#include "time_format.hpp"

namespace QLogicaeCore
{
	struct LoggerConfigurations
	{
		std::string name = "";
		
		LogMedium log_medium =
			LogMedium::CONSOLE;

		TimeZone log_time_zone =
			TimeZone::LOCAL;

		TimeFormat log_format =
			TimeFormat::FULL_TIMESTAMP;		
		
		bool is_simplified =
			false;

		bool is_enabled =
			true;
		
		std::vector<std::string> output_paths =
			{};
		
		bool is_log_file_fragmentation_enabled =
			false;
		
		std::string log_file_fragmentation_output_folder_path =
			".qlogicae/logs";
		
		TimeFormat log_file_fragmentation_format =
			TimeFormat::DATE_DMY_SLASHED;


		bool is_log_file_collectivization_enabled =
			false;

		std::string log_file_collectivization_output_file_name =
			"all.log";

		std::string log_file_collectivization_output_folder_path =
			".qlogicae";
	};

	inline static LoggerConfigurations DEFAULT_LOGGER_CONFIGURATIONS;
}
