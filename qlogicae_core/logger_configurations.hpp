#pragma once

#include "log_medium.hpp"
#include "time_format.hpp"

namespace QLogicaeCore
{
	struct LoggerConfigurations
	{
		std::string name = "";
		
		LogMedium log_medium =
			LogMedium::CONSOLE;
		
		TimeFormat log_format =
			TimeFormat::FULL_TIMESTAMP;		
		
		bool is_simplified =
			false;
		
		std::vector<std::string> output_paths =
			{};
		
		bool is_log_file_fragmentation_enabled =
			false;
		
		std::string log_file_fragmentation_output_folder_path =
			"";
		
		TimeFormat log_file_fragmentation_format =
			TimeFormat::DATE_DMY_SLASHED;
	};
}
