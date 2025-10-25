#include "pch.hpp"

#include "logger.hpp"

namespace QLogicaeCore
{	
	Logger::Logger()
	{
		_name = "";
		_log_medium = LogMedium::CONSOLE;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;
		_is_enabled = true;
		_is_simplified = false;
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_log_file_collectivization_output_file_name = "";
		_is_log_file_collectivization_enabled = false;
		_log_file_collectivization_output_folder_path = "";
		_output_paths = {};
	}
	
	Logger::~Logger()
	{
		
	}

	Logger::Logger(
		const bool& is_simplified
	)
	{
		_name = "";
		_log_medium = LogMedium::CONSOLE;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;
		_is_enabled = true;
		_is_simplified = is_simplified;
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_is_log_file_collectivization_enabled = false;
		_log_file_collectivization_output_file_name = "";
		_log_file_collectivization_output_folder_path = "";
		_log_file_collectivization_output_file_path = "";
		_output_paths = {};
	}

	Logger::Logger(
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool& is_simplified
	)
	{
		_name = name;
		_log_medium = medium;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;
		_is_enabled = true;
		_is_simplified = is_simplified;
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_is_log_file_collectivization_enabled = false;
		_log_file_collectivization_output_file_name = "";
		_log_file_collectivization_output_folder_path = "";
		_log_file_collectivization_output_file_path = "";
		_output_paths = output_paths;
	}

	Logger::Logger(
		const LoggerConfigurations& configurations
	)
	{
		_name = configurations.name;
		_log_medium = configurations.log_medium;
		_log_format = configurations.log_format;
		_log_file_fragmentation_format = configurations.log_file_fragmentation_format;
		_is_enabled = configurations.is_enabled;
		_is_simplified = configurations.is_simplified;
		_is_log_file_fragmentation_enabled = configurations.is_log_file_fragmentation_enabled;
		_log_file_fragmentation_output_folder_path = configurations.log_file_fragmentation_output_folder_path;
		_is_log_file_collectivization_enabled = configurations.is_log_file_collectivization_enabled;
		_log_file_collectivization_output_file_name = configurations.log_file_collectivization_output_file_name;
		_log_file_collectivization_output_folder_path = configurations.log_file_collectivization_output_folder_path;
		_output_paths = configurations.output_paths;

		if (_is_log_file_collectivization_enabled)
		{
			_log_file_collectivization_output_file_path =
				_generate_log_collectivization_file_path();
		}
	}

	bool Logger::setup()
	{
		try
		{
			Result<void> result;

			setup(result);

			return result.is_status_safe();
		}
		catch (const std::exception& exception)
		{
			Result<std::future<void>> result;

			force_log_to_console_and_file_async(
				result,
				"Logger::setup()",
				exception
			);

			return false;
		}
	}

	void Logger::setup(
		Result<void>& result
	)
	{
		_name = "";
		_log_medium = LogMedium::CONSOLE;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;
		_is_enabled = true;
		_is_simplified = false;
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_log_file_collectivization_output_file_name = "";
		_is_log_file_collectivization_enabled = false;
		_log_file_collectivization_output_folder_path = "";
		_output_paths = {};

		result.set_to_good_status_without_value();
	}

	bool Logger::setup(
		const bool& is_simplified
	)
	{
		try
		{
			Result<void> result;

			setup(
				result,
				is_simplified
			);

			return result.is_status_safe();
		}
		catch (const std::exception& exception)
		{
			force_log_to_console_and_file_async(
				"Logger::setup()",
				exception
			);

			return false;
		}
	}

	void Logger::setup(
		Result<void>& result,
		const bool& is_simplified
	)
	{
		_name = "";
		_log_medium = LogMedium::CONSOLE;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;
		_is_enabled = true;
		_is_simplified = is_simplified;
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_is_log_file_collectivization_enabled = false;
		_log_file_collectivization_output_file_name = "";
		_log_file_collectivization_output_folder_path = "";
		_log_file_collectivization_output_file_path = "";
		_output_paths = {};

		result.set_to_good_status_without_value();
	}

	bool Logger::setup(
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool& is_simplified
	)
	{
		try
		{
			Result<void> result;

			setup(
				result,
				name,
				medium,
				output_paths,
				is_simplified
			);

			return result.is_status_safe();
		}
		catch (const std::exception& exception)
		{
			force_log_to_console_and_file_async(
				"Logger::setup()",
				exception
			);

			return false;
		}
	}

	void Logger::setup(
		Result<void>& result,
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool& is_simplified
	)
	{
		_name = name;
		_log_medium = medium;
		_log_format = TimeFormat::FULL_TIMESTAMP;
		_log_file_fragmentation_format = TimeFormat::DATE_DMY_SLASHED;
		_is_enabled = true;
		_is_simplified = is_simplified;
		_is_log_file_fragmentation_enabled = false;
		_log_file_fragmentation_output_folder_path = "";
		_is_log_file_collectivization_enabled = false;
		_log_file_collectivization_output_file_name = "";
		_log_file_collectivization_output_folder_path = "";
		_log_file_collectivization_output_file_path = "";
		_output_paths = output_paths;

		result.set_to_good_status_without_value();
	}

	bool Logger::setup(
		const LoggerConfigurations& configurations
	)
	{
		try
		{
			Result<void> void_result;

			setup(
				void_result,
				configurations
			);

			return void_result.is_status_safe();
		}
		catch (const std::exception& exception)
		{
			force_log_to_console_and_file_async(
				"Logger::setup()",
				exception
			);

			return false;
		}
	}

	void Logger::setup(
		Result<void>& result,
		const LoggerConfigurations& configurations
	)
	{
		_name = configurations.name;
		_log_medium = configurations.log_medium;
		_log_format = configurations.log_format;
		_log_file_fragmentation_format = configurations.log_file_fragmentation_format;
		_is_enabled = configurations.is_enabled;
		_is_simplified = configurations.is_simplified;
		_is_log_file_fragmentation_enabled = configurations.is_log_file_fragmentation_enabled;
		_log_file_fragmentation_output_folder_path = configurations.log_file_fragmentation_output_folder_path;
		_is_log_file_collectivization_enabled = configurations.is_log_file_collectivization_enabled;
		_log_file_collectivization_output_file_name = configurations.log_file_collectivization_output_file_name;
		_log_file_collectivization_output_folder_path = configurations.log_file_collectivization_output_folder_path;		
		_output_paths = configurations.output_paths;

		if (_is_log_file_collectivization_enabled)
		{
			_log_file_collectivization_output_file_path =
				_generate_log_collectivization_file_path();
		}
		
		result.set_to_good_status_without_value();
	}

	std::future<bool> Logger::setup_async()
	{
		std::promise<bool> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, 
				promise = std::move(promise)]() mutable
			{
				promise.set_value(
					setup()
				);
			}
		);

		return future;
	}

	void Logger::setup_async(
		const std::function<void(const bool& result)>& callback
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback]() mutable
			{
				callback(
					setup()
				);
			}
		);
	}

	void Logger::setup_async(
		Result<std::future<void>>& result
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, 
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				setup(result);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::setup_async(
		const std::function<void(Result<void>& result)>& callback
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback]() mutable
			{
				Result<void> result;

				setup(result);

				callback(
					result
				);
			}
		);
	}

	std::future<bool> Logger::setup_async(
		const bool& is_simplified
	)
	{
		std::promise<bool> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, is_simplified, 
				promise = std::move(promise)]() mutable
			{
				promise.set_value(
					setup(
						is_simplified
					)
				);
			}
		);

		return future;
	}

	void Logger::setup_async(
		const std::function<void(const bool& result)>& callback,
		const bool& is_simplified
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, is_simplified]() mutable
			{
				callback(
					setup(
						is_simplified
					)
				);
			}
		);
	}

	void Logger::setup_async(
		Result<std::future<void>>& result,
		const bool& is_simplified
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, is_simplified, 
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				setup(
					result,
					is_simplified
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::setup_async(
		const std::function<void(Result<void>& result)>& callback,
		const bool& is_simplified
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, is_simplified]() mutable
			{
				Result<void> result;

				setup(
					result,
					is_simplified
				);

				callback(
					result
				);
			}
		);
	}

	std::future<bool> Logger::setup_async(
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool& is_simplified
	)
	{
		std::promise<bool> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, name, medium, output_paths, is_simplified, 
				promise = std::move(promise)]() mutable
			{
				promise.set_value(
					setup(
						name,
						medium,
						output_paths,
						is_simplified
					)
				);
			}
		);

		return future;
	}

	void Logger::setup_async(
		const std::function<void(const bool& result)>& callback,
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool& is_simplified
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, name, medium, output_paths, is_simplified]() mutable
			{
				callback(
					setup(
						name,
						medium,
						output_paths,
						is_simplified
					)
				);
			}
		);
	}

	void Logger::setup_async(
		Result<std::future<void>>& result,
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool& is_simplified
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, name, medium, output_paths, is_simplified, 
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				setup(
					result,
					name,
					medium,
					output_paths,
					is_simplified
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::setup_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& name,
		const LogMedium& medium,
		const std::vector<std::string>& output_paths,
		const bool& is_simplified		
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, name, medium, output_paths, is_simplified, callback]() mutable
			{
				Result<void> result;

				setup(
					result,
					name,
					medium,
					output_paths,
					is_simplified
				);

				callback(
					result
				);
			}
		);
	}

	std::future<bool> Logger::setup_async(
		const LoggerConfigurations& configurations
	)
	{
		std::promise<bool> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, configurations, 
				promise = std::move(promise)]() mutable
			{				
				promise.set_value(
					setup(
						configurations
					)
				);
			}
		);

		return future;
	}

	void Logger::setup_async(
		const std::function<void(const bool& result)>& callback,
		const LoggerConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, configurations]() mutable
			{
				callback(
					setup(
						configurations
					)
				);
			}
		);
	}

	void Logger::setup_async(
		Result<std::future<void>>& result,
		const LoggerConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, configurations, 
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				setup(
					result,
					configurations
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::setup_async(
		const std::function<void(Result<void>& result)>& callback,
		const LoggerConfigurations& configurations		
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, configurations, callback]() mutable
			{
				Result<void> result;

				setup(
					result,
					configurations
				);

				callback(
					result
				);
			}
		);
	}

	bool Logger::get_is_simplified()
	{
		return _is_simplified;
	}

	void Logger::get_is_simplified(
		Result<bool>& result
	)
	{
		result.set_to_good_status_with_value(
			_is_simplified
		);
	}

	void Logger::set_is_simplified(
		const bool& value
	)
	{
		_is_simplified = value;
	}

	void Logger::set_is_simplified(
		Result<void>& result,
		const bool& value
	)
	{
		_is_simplified = value;

		result.set_to_good_status_without_value();
	}

	bool Logger::get_is_enabled()
	{
		return _is_enabled;
	}

	void Logger::get_is_enabled(
		Result<bool>& result
	)
	{
		result.set_to_good_status_with_value(
			_is_enabled
		);
	}

	void Logger::set_is_enabled(
		const bool& value
	)
	{
		_is_enabled = value;
	}

	void Logger::set_is_enabled(
		Result<void>& result,
		const bool& value
	)
	{
		_is_enabled = value;

		result.set_to_good_status_without_value();
	}

	std::string Logger::get_name()
	{
		return _name;
	}

	void Logger::get_name(
		Result<std::string>& result
	)
	{
		result.set_to_good_status_with_value(
			_name
		);
	}

	LogMedium Logger::get_medium()
	{
		return _log_medium;
	}

	void Logger::get_medium(
		Result<LogMedium>& result
	)
	{
		result.set_to_good_status_with_value(
			_log_medium
		);
	}

	std::vector<std::string> Logger::get_output_paths()
	{
		return _output_paths;
	}

	void Logger::get_output_paths(
		Result<std::vector<std::string>>& result
	)
	{
		result.set_to_good_status_with_value(
			_output_paths
		);
	}

	void Logger::log(
		const std::string& text,
		const LogLevel& log_level,
		const bool& is_enabled,
		const bool& is_simplified
	)
	{
		try
		{	
			std::scoped_lock lock(_mutex);

			Result<void> result;
			
			log(
				result,
				text,
				log_level,
				is_enabled,
				is_simplified
			);
		}
		catch (const std::exception& exception)
		{
			force_log_to_console_and_file_async(
				"Logger::log()",
				exception
			);
		}
	}

	void Logger::log(
		Result<void>& result,
		const std::string& text,
		const LogLevel& log_level,
		const bool& is_enabled,
		const bool& is_simplified
	)
	{		
		if ((!is_enabled || !_is_enabled) ||
			_log_medium == LogMedium::NONE
		)
		{
			return result.set_to_good_status_without_value();
		}
		
		Result<std::string> string_result;
		Result<std::future<void>> future_void_result_1;
		Result<std::future<void>> future_void_result_2;
		Result<std::future<void>> future_void_result_3;
		Result<std::future<void>> future_void_result_4;
		
		if (is_simplified || _is_simplified)
		{
			string_result.set_value(
				text
			);
		}
		else
		{
			TRANSFORMER.to_log_format(
				string_result,
				text,
				log_level,
				_log_format
			);
		}

		switch (_log_medium)
		{
			case LogMedium::ALL:
			{
				CLI_IO.print_async(
					future_void_result_1,
					string_result.get_value()
				);

				if (!_output_paths.empty())
				{
					_log_to_output_files_async(
						future_void_result_2,
						string_result.get_value()
					);
				}
				if (_is_log_file_fragmentation_enabled)
				{
					_log_to_fragmentation_file_async(
						future_void_result_3,
						string_result.get_value()
					);
				}
				if (_is_log_file_collectivization_enabled)
				{
					_log_to_collectivization_file_async(
						future_void_result_4,
						string_result.get_value()
					);
				}

				break;
			}
			case LogMedium::CONSOLE:
			{
				CLI_IO.print_async(
					future_void_result_1,
					string_result.get_value()
				);

				break;
			}
			case LogMedium::FILE:
			{
				if (!_output_paths.empty())
				{
					_log_to_output_files_async(
						future_void_result_2,
						string_result.get_value()
					);
				}
				if (_is_log_file_fragmentation_enabled)
				{
					_log_to_fragmentation_file_async(
						future_void_result_3,
						string_result.get_value()
					);
				}
				if (_is_log_file_collectivization_enabled)
				{
					_log_to_collectivization_file_async(
						future_void_result_4,
						string_result.get_value()
					);
				}
				break;
			}
		}

		result.set_to_good_status_without_value();
	}

	void Logger::log(
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		try
		{			
			std::scoped_lock lock(_mutex);

			Result<void> result;

			log(
				result,
				text,
				configurations
			);
		}
		catch (const std::exception& exception)
		{
			force_log_to_console_and_file(
				"Logger::log()",
				exception
			);
		}
	}

	void Logger::log(
		Result<void>& result,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{		
		LogLevel log_level = configurations.log_level;
		bool is_enabled = configurations.is_enabled;
		bool is_simplified = configurations.is_simplified;

		if ((!is_enabled || !_is_enabled) ||
			_log_medium == LogMedium::NONE
			)
		{
			return result.set_to_good_status_without_value();
		}

		Result<std::string> string_result;
		Result<std::future<void>> future_void_result_1;
		Result<std::future<void>> future_void_result_2;
		Result<std::future<void>> future_void_result_3;
		Result<std::future<void>> future_void_result_4;

		if (is_simplified || _is_simplified)
		{
			string_result.set_value(
				text
			);
		}
		else
		{
			TRANSFORMER.to_log_format(
				string_result,
				text,
				log_level,
				_log_format
			);
		}

		switch (_log_medium)
		{
			case LogMedium::ALL:
			{
				CLI_IO.print_async(
					future_void_result_1,
					string_result.get_value()
				);

				if (!_output_paths.empty())
				{
					_log_to_output_files_async(
						future_void_result_2,
						string_result.get_value()
					);
				}
				if (_is_log_file_fragmentation_enabled)
				{
					_log_to_fragmentation_file_async(
						future_void_result_3,
						string_result.get_value()
					);
				}
				if (_is_log_file_collectivization_enabled)
				{
					_log_to_collectivization_file_async(
						future_void_result_4,
						string_result.get_value()
					);
				}

				break;
			}
			case LogMedium::CONSOLE:
			{
				CLI_IO.print_async(
					future_void_result_1,
					string_result.get_value()
				);

				break;
			}
			case LogMedium::FILE:
			{
				if (!_output_paths.empty())
				{
					_log_to_output_files_async(
						future_void_result_2,
						string_result.get_value()
					);
				}
				if (_is_log_file_fragmentation_enabled)
				{
					_log_to_fragmentation_file_async(
						future_void_result_3,
						string_result.get_value()
					);
				}
				if (_is_log_file_collectivization_enabled)
				{
					_log_to_collectivization_file_async(
						future_void_result_4,
						string_result.get_value()
					);
				}
				break;
			}
		}

		result.set_to_good_status_without_value();
	}

	std::future<void> Logger::log_async(
		const std::string& text,
		const LogLevel& log_level,
		const bool& is_enabled,
		const bool& is_simplified
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, log_level, is_enabled, is_simplified,				
				promise = std::move(promise)]() mutable
			{
				log(
					text,
					log_level,
					is_enabled,
					is_simplified
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const LogLevel& log_level,
		const bool& is_enabled,
		const bool& is_simplified
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, log_level, is_enabled, is_simplified,
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				log(
					result,
					text,
					log_level,
					is_enabled,
					is_simplified
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	std::future<void> Logger::log_async(
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
				promise = std::move(promise)]() mutable
			{
				log(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				setup(result);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::log_async(
		const std::function<void()>& callback,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback, configurations]() mutable
			{
				Result<void> result;

				log(
					result,
					text,
					configurations
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_async(
		const std::function<void()>& callback,
		const std::string& text,
		const LogLevel& log_level,
		const bool& is_enabled,
		const bool& is_simplified
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, log_level, is_enabled, is_simplified]() mutable
			{
				log(
					text,
					log_level,
					is_enabled,
					is_simplified
				);

				callback();
			}
		);
	}

	void Logger::log_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const LogLevel& log_level,
		const bool& is_enabled,
		const bool& is_simplified
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, log_level, is_enabled, is_simplified]() mutable
			{
				Result<void> result;

				log(
					result,
					text,
					log_level,
					is_enabled,
					is_simplified
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_info(
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		log(
			text,
			configurations
		);
	}

	void Logger::log_info(
		Result<void>& result,
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		log(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_info_async(
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
				promise = std::move(promise)]() mutable
			{
				log_info(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_info_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				log_info(
					result,
					text,
					configurations
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::log_info_async(
		const std::function<void()>& callback,
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_info(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_info_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations, callback]() mutable
			{
				Result<void> result;

				log_info(
					result,
					text,
					configurations
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_success(
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		log(
			text,
			configurations
		);
	}

	void Logger::log_success(
		Result<void>& result,
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		log(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_success_async(
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
				promise = std::move(promise)]() mutable
			{
				log_success(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_success_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				log_success(
					result,
					text,
					configurations
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::log_success_async(
		const std::function<void()>& callback,
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_success(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_success_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations, callback]() mutable
			{
				Result<void> result;

				log_success(
					result,
					text,
					configurations
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_warning(
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		log(
			text,
			configurations
		);
	}

	void Logger::log_warning(
		Result<void>& result,
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		log(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_warning_async(
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
				promise = std::move(promise)]() mutable
			{
				log_warning(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_warning_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				log_warning(
					result,
					text,
					configurations
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::log_warning_async(
		const std::function<void()>& callback,
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_warning(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_warning_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations, callback]() mutable
			{
				Result<void> result;

				log_warning(
					result,
					text,
					configurations
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_exception(
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		log(
			text,
			configurations
		);
	}

	void Logger::log_exception(
		Result<void>& result,
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		log(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_exception_async(
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
				promise = std::move(promise)]() mutable
			{
				log_exception(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_exception_async(
		Result<std::future<void>>& result,
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations,
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				log_exception(
					result,
					text,
					configurations
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::log_exception_async(
		const std::function<void()>& callback,
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_exception(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_exception_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, configurations, callback]() mutable
			{
				Result<void> result;

				log_exception(
					result,
					text,
					configurations
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::force_log_to_console_and_file(
		const std::string& origin,
		const std::exception& exception
	)
	{
		try
		{
			Result<void> result;

			force_log_to_console_and_file(
				result,
				origin,
				exception
			);
		}
		catch (const std::exception& exception)
		{
			
		}
	}

	std::future<void> Logger::force_log_to_console_and_file_async(
		const std::string& origin,
		const std::exception& exception
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, origin, exception,
				promise = std::move(promise)]() mutable
			{
				force_log_to_console_and_file(
					origin,
					exception
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::force_log_to_console_and_file_async(
		const std::function<void()>& callback,
		const std::string& origin,
		const std::exception& exception
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, origin, exception]() mutable
			{
				force_log_to_console_and_file(
					origin,
					exception
				);

				callback();
			}
		);
	}

	void Logger::force_log_to_console_and_file(
		Result<void>& result,
		const std::string& origin,
		const std::exception& exception
	)
	{
		Result<std::string> string_result;
		Result<std::future<void>> future_void_result;

		TRANSFORMER.to_exception_text_format(
			string_result,
			origin,
			exception.what()
		);

		CLI_IO.print(
			result,
			string_result.get_value()
		);

		_log_to_fragmentation_file_async(
			future_void_result,
			string_result.get_value()
		);

		_log_to_collectivization_file_async(
			future_void_result,
			string_result.get_value()
		);

		result.set_to_good_status_without_value();
	}

	void Logger::force_log_to_console_and_file_async(
		Result<std::future<void>>& result,
		const std::string& origin,
		const std::exception& exception
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, origin, exception, 
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				force_log_to_console_and_file(
					result,
					origin,
					exception
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::force_log_to_console_and_file_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& origin,
		const std::exception& exception
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, origin, exception]() mutable
			{
				Result<void> result;

				force_log_to_console_and_file(
					result,
					origin,
					exception
				);

				callback(
					result
				);
			}
		);
	}

	Logger& Logger::get_instance()
	{
		static Logger instance;

		return instance;
	}

	void Logger::get_instance(
		Result<Logger*>& result
	)
	{
		static Logger instance;

		result.set_to_good_status_with_value(
			&instance
		);
	}

	void Logger::_log_to_collectivization_file(
		const std::string& text
	)
	{
		try
		{
			Result<void> result;

			_log_to_collectivization_file(
				result,
				text
			);
		}
		catch (const std::exception& exception)
		{

		}
	}

	void Logger::_log_to_collectivization_file(
		Result<void>& result,
		const std::string& text
	)
	{
 		TextFileIO text_file_io;

		Result<bool> bool_result;
		
		text_file_io.set_file_path(
			result,
			_log_file_collectivization_output_file_path
		);
		text_file_io.append(
			bool_result,
			text
		);

		result.set_to_good_status_without_value();
	}

	std::future<void> Logger::_log_to_collectivization_file_async(
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, 
				promise = std::move(promise)]() mutable
			{
				_log_to_collectivization_file(
					text
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::_log_to_collectivization_file_async(
		Result<std::future<void>>& result,
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, 
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				_log_to_collectivization_file(
					result,
					text
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::_log_to_fragmentation_file(
		const std::string& text
	)
	{
		try
		{
			Result<void> result;

			_log_to_fragmentation_file(
				result,
				text
			);
		}
		catch (const std::exception& exception)
		{

		}
	}

	void Logger::_log_to_fragmentation_file(
		Result<void>& result,
		const std::string& text
	)
	{
 		TextFileIO text_file_io;

		Result<bool> bool_result;
		Result<std::string> string_result;

		_generate_log_fragmentation_file_path(
			string_result
		);

		text_file_io.set_file_path(
			result,
			string_result.get_value()
		);
		text_file_io.append(
			bool_result,
			text
		);

		result.set_to_good_status_without_value();
	}

	std::future<void> Logger::_log_to_fragmentation_file_async(
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, 
				promise = std::move(promise)]() mutable
			{
				_log_to_fragmentation_file(
					text
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::_log_to_fragmentation_file_async(
		Result<std::future<void>>& result,
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, 
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				_log_to_fragmentation_file(
					result,
					text
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::_log_to_file(
		const std::string& path,
		const std::string& text
	)
	{
		try
		{
			Result<void> result;

			_log_to_file(
				result,
				path,
				text
			);
		}
		catch (const std::exception& exception)
		{

		}
	}

	void Logger::_log_to_file(
		Result<void>& result,
		const std::string& path,
		const std::string& text
	)
	{
 		TextFileIO text_file_io;

		Result<bool> bool_result;

		text_file_io.set_file_path(
			result,
			path
		);
		text_file_io.append(
			bool_result,
			text
		);
	}

	std::future<void> Logger::_log_to_file_async(
		const std::string& path,
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, path, text, 
				promise = std::move(promise)]() mutable
			{
				_log_to_file(
					path,
					text
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::_log_to_output_files(
		const std::string& text
	)
	{
		try
		{
			Result<void> result;

			_log_to_output_files(
				result,
				text
			);
		}
		catch (const std::exception& exception)
		{

		}
	}

	std::future<void> Logger::_log_to_output_files_async(
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, 
				promise = std::move(promise)]() mutable
			{				
				_log_to_output_files(
					text
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::_log_to_output_files(
		Result<void>& result,
		const std::string& text
	)
	{
		for (const auto& output_path :
			_output_paths)
		{
			_log_to_file(
				output_path,
				text
			);
		}

		result.set_to_good_status_without_value();
	}

	std::future<void> Logger::_log_to_output_files_async(
		Result<std::future<void>>& result,
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, 
				promise = std::move(promise)]() mutable
			{
				Result<void> result;

				_log_to_output_files(
					result,
					text
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	std::string Logger::_generate_log_fragmentation_file_path()
	{
		try
		{
			Result<std::string> result;

			_generate_log_fragmentation_file_path(
				result
			);

			return result.get_value();
		}
		catch (const std::exception& exception)
		{

		}
	}

	void Logger::_generate_log_fragmentation_file_path(
		Result<std::string>& result
	)
	{
		result.set_to_good_status_with_value(
			_log_file_fragmentation_output_folder_path +
				"\\" + TIME.now(_log_file_fragmentation_format) + ".log"
		);
	}

	std::string Logger::_generate_log_collectivization_file_path()
	{
		try
		{
			Result<std::string> result;

			_generate_log_collectivization_file_path(
				result
			);

			return result.get_value();
		}
		catch (const std::exception& exception)
		{

		}
	}

	void Logger::_generate_log_collectivization_file_path(
		Result<std::string>& result
	)
	{
		result.set_to_good_status_with_value(
			_log_file_collectivization_output_folder_path +
			"\\" + _log_file_collectivization_output_file_name
		);
	}
}
