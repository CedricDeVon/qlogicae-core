#include "pch.hpp"

#include "logger.hpp"

namespace QLogicaeCore
{	
	Logger::Logger()
	{
		_name = DEFAULT_LOGGER_CONFIGURATIONS.name;
		_log_medium = DEFAULT_LOGGER_CONFIGURATIONS.log_medium;
		_log_time_zone = DEFAULT_LOGGER_CONFIGURATIONS.log_time_zone;
		_log_format = DEFAULT_LOGGER_CONFIGURATIONS.log_format;
		_log_file_fragmentation_format = DEFAULT_LOGGER_CONFIGURATIONS.log_file_fragmentation_format;
		_is_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_enabled;
		_is_simplified = DEFAULT_LOGGER_CONFIGURATIONS.is_simplified;
		_is_log_file_fragmentation_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_log_file_fragmentation_enabled;
		_log_file_fragmentation_output_folder_path = DEFAULT_LOGGER_CONFIGURATIONS.log_file_fragmentation_output_folder_path;
		_is_log_file_collectivization_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_log_file_collectivization_enabled;
		_log_file_collectivization_output_file_name = DEFAULT_LOGGER_CONFIGURATIONS.log_file_collectivization_output_file_name;
		_log_file_collectivization_output_folder_path = DEFAULT_LOGGER_CONFIGURATIONS.log_file_collectivization_output_folder_path;
		_output_paths = DEFAULT_LOGGER_CONFIGURATIONS.output_paths;
	}

	Logger::~Logger()
	{

	}

	Logger::Logger(
		const bool& is_simplified
	)
	{
		_name = DEFAULT_LOGGER_CONFIGURATIONS.name;
		_log_medium = DEFAULT_LOGGER_CONFIGURATIONS.log_medium;
		_log_time_zone = DEFAULT_LOGGER_CONFIGURATIONS.log_time_zone;
		_log_format = DEFAULT_LOGGER_CONFIGURATIONS.log_format;
		_log_file_fragmentation_format = DEFAULT_LOGGER_CONFIGURATIONS.log_file_fragmentation_format;
		_is_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_enabled;
		_is_simplified = is_simplified;
		_is_log_file_fragmentation_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_log_file_fragmentation_enabled;
		_log_file_fragmentation_output_folder_path = DEFAULT_LOGGER_CONFIGURATIONS.log_file_fragmentation_output_folder_path;
		_is_log_file_collectivization_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_log_file_collectivization_enabled;
		_log_file_collectivization_output_file_name = DEFAULT_LOGGER_CONFIGURATIONS.log_file_collectivization_output_file_name;
		_log_file_collectivization_output_folder_path = DEFAULT_LOGGER_CONFIGURATIONS.log_file_collectivization_output_folder_path;
		_output_paths = DEFAULT_LOGGER_CONFIGURATIONS.output_paths;
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
		_log_time_zone = DEFAULT_LOGGER_CONFIGURATIONS.log_time_zone;
		_log_format = DEFAULT_LOGGER_CONFIGURATIONS.log_format;
		_log_file_fragmentation_format = DEFAULT_LOGGER_CONFIGURATIONS.log_file_fragmentation_format;
		_is_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_enabled;
		_is_simplified = is_simplified;
		_is_log_file_fragmentation_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_log_file_fragmentation_enabled;
		_log_file_fragmentation_output_folder_path = DEFAULT_LOGGER_CONFIGURATIONS.log_file_fragmentation_output_folder_path;
		_is_log_file_collectivization_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_log_file_collectivization_enabled;
		_log_file_collectivization_output_file_name = DEFAULT_LOGGER_CONFIGURATIONS.log_file_collectivization_output_file_name;
		_log_file_collectivization_output_folder_path = DEFAULT_LOGGER_CONFIGURATIONS.log_file_collectivization_output_folder_path;
		_output_paths = output_paths;
	}

	Logger::Logger(
		const LoggerConfigurations& configurations
	)
	{
		_name = configurations.name;
		_log_medium = configurations.log_medium;
		_log_time_zone = configurations.log_time_zone;
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
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::setup() - ") + exception.what()
			);

			return false;
		}
	}

	void Logger::setup(
		Result<void>& result
	)
	{
		_name = DEFAULT_LOGGER_CONFIGURATIONS.name;
		_log_medium = DEFAULT_LOGGER_CONFIGURATIONS.log_medium;
		_log_time_zone = DEFAULT_LOGGER_CONFIGURATIONS.log_time_zone;
		_log_format = DEFAULT_LOGGER_CONFIGURATIONS.log_format;
		_log_file_fragmentation_format = DEFAULT_LOGGER_CONFIGURATIONS.log_file_fragmentation_format;
		_is_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_enabled;
		_is_simplified = DEFAULT_LOGGER_CONFIGURATIONS.is_simplified;
		_is_log_file_fragmentation_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_log_file_fragmentation_enabled;
		_log_file_fragmentation_output_folder_path = DEFAULT_LOGGER_CONFIGURATIONS.log_file_fragmentation_output_folder_path;
		_is_log_file_collectivization_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_log_file_collectivization_enabled;
		_log_file_collectivization_output_file_name = DEFAULT_LOGGER_CONFIGURATIONS.log_file_collectivization_output_file_name;
		_log_file_collectivization_output_folder_path = DEFAULT_LOGGER_CONFIGURATIONS.log_file_collectivization_output_folder_path;
		_output_paths = DEFAULT_LOGGER_CONFIGURATIONS.output_paths;

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
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::setup() - ") + exception.what()
			);

			return false;
		}
	}

	void Logger::setup(
		Result<void>& result,
		const bool& is_simplified
	)
	{
		_name = DEFAULT_LOGGER_CONFIGURATIONS.name;
		_log_medium = DEFAULT_LOGGER_CONFIGURATIONS.log_medium;
		_log_time_zone = DEFAULT_LOGGER_CONFIGURATIONS.log_time_zone;
		_log_format = DEFAULT_LOGGER_CONFIGURATIONS.log_format;
		_log_file_fragmentation_format = DEFAULT_LOGGER_CONFIGURATIONS.log_file_fragmentation_format;
		_is_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_enabled;
		_is_simplified = is_simplified;
		_is_log_file_fragmentation_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_log_file_fragmentation_enabled;
		_log_file_fragmentation_output_folder_path = DEFAULT_LOGGER_CONFIGURATIONS.log_file_fragmentation_output_folder_path;
		_is_log_file_collectivization_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_log_file_collectivization_enabled;
		_log_file_collectivization_output_file_name = DEFAULT_LOGGER_CONFIGURATIONS.log_file_collectivization_output_file_name;
		_log_file_collectivization_output_folder_path = DEFAULT_LOGGER_CONFIGURATIONS.log_file_collectivization_output_folder_path;
		_output_paths = DEFAULT_LOGGER_CONFIGURATIONS.output_paths;

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
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::setup() - ") + exception.what()
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
		_log_time_zone = DEFAULT_LOGGER_CONFIGURATIONS.log_time_zone;
		_log_format = DEFAULT_LOGGER_CONFIGURATIONS.log_format;
		_log_file_fragmentation_format = DEFAULT_LOGGER_CONFIGURATIONS.log_file_fragmentation_format;
		_is_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_enabled;
		_is_simplified = is_simplified;
		_is_log_file_fragmentation_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_log_file_fragmentation_enabled;
		_log_file_fragmentation_output_folder_path = DEFAULT_LOGGER_CONFIGURATIONS.log_file_fragmentation_output_folder_path;
		_is_log_file_collectivization_enabled = DEFAULT_LOGGER_CONFIGURATIONS.is_log_file_collectivization_enabled;
		_log_file_collectivization_output_file_name = DEFAULT_LOGGER_CONFIGURATIONS.log_file_collectivization_output_file_name;
		_log_file_collectivization_output_folder_path = DEFAULT_LOGGER_CONFIGURATIONS.log_file_collectivization_output_folder_path;
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
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::setup() - ") + exception.what()
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
		_log_time_zone = configurations.log_time_zone;
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

	void Logger::log_timestamp(
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
			
			log_timestamp(
				result,
				text,
				log_level,
				is_enabled,
				is_simplified
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::log_timestamp() - ") + exception.what()
			);

		}
	}

	void Logger::log_timestamp(
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
			_to_log_format(
				string_result,
				text,
				log_level
			);
		}

		switch (_log_medium)
		{
			case LogMedium::ALL:
			{
				log_to_console(
					result,
					string_result.get_value()
				);

				if (!_output_paths.empty())
				{
					log_to_output_files_async(
						future_void_result_2,
						string_result.get_value()
					);
				}
				if (_is_log_file_fragmentation_enabled)
				{
					log_to_fragmentation_file_async(
						future_void_result_3,
						string_result.get_value()
					);
				}
				if (_is_log_file_collectivization_enabled)
				{
					log_to_collectivization_file_async(
						future_void_result_4,
						string_result.get_value()
					);
				}

				break;
			}
			case LogMedium::CONSOLE:
			{
				log_to_console(
					result,
					string_result.get_value()
				);

				break;
			}
			case LogMedium::FILE:
			{
				if (!_output_paths.empty())
				{
					log_to_output_files_async(
						future_void_result_2,
						string_result.get_value()
					);
				}
				if (_is_log_file_fragmentation_enabled)
				{
					log_to_fragmentation_file_async(
						future_void_result_3,
						string_result.get_value()
					);
				}
				if (_is_log_file_collectivization_enabled)
				{
					log_to_collectivization_file_async(
						future_void_result_4,
						string_result.get_value()
					);
				}
				break;
			}
		}

		result.set_to_good_status_without_value();
	}

	void Logger::log_timestamp(
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		try
		{
			std::scoped_lock lock(_mutex);

			Result<void> result;

			log_timestamp(
				result,
				text,
				configurations
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::log_timestamp() - ") + exception.what()
			);
		}
	}

	void Logger::log_timestamp(
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
			_to_log_format(
				string_result,
				text,
				log_level
			);
		}

		switch (_log_medium)
		{
		case LogMedium::ALL:
		{
			log_to_console(
				result,
				string_result.get_value()
			);

			if (!_output_paths.empty())
			{
				log_to_output_files_async(
					future_void_result_2,
					string_result.get_value()
				);
			}
			if (_is_log_file_fragmentation_enabled)
			{
				log_to_fragmentation_file_async(
					future_void_result_3,
					string_result.get_value()
				);
			}
			if (_is_log_file_collectivization_enabled)
			{
				log_to_collectivization_file_async(
					future_void_result_4,
					string_result.get_value()
				);
			}

			break;
		}
		case LogMedium::CONSOLE:
		{
			log_to_console(
				result,
					string_result.get_value()
				);

				break;
			}
			case LogMedium::FILE:
			{
				if (!_output_paths.empty())
				{
					log_to_output_files_async(
						future_void_result_2,
						string_result.get_value()
					);
				}
				if (_is_log_file_fragmentation_enabled)
				{
					log_to_fragmentation_file_async(
						future_void_result_3,
						string_result.get_value()
					);
				}
				if (_is_log_file_collectivization_enabled)
				{
					log_to_collectivization_file_async(
						future_void_result_4,
						string_result.get_value()
					);
				}
				break;
			}
		}

		result.set_to_good_status_without_value();
	}

	std::future<void> Logger::log_timestamp_async(
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
				log_timestamp(
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

	void Logger::log_timestamp_async(
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

				log_timestamp(
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

	std::future<void> Logger::log_timestamp_async(
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
				log_timestamp(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_timestamp_async(
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

				log_timestamp(
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

	void Logger::log_timestamp_async(
		const std::function<void()>& callback,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_timestamp(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_async(
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

				log_timestamp(
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

	void Logger::log_timestamp_async(
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
				log_timestamp(
					text,
					log_level,
					is_enabled,
					is_simplified
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_async(
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

				log_timestamp(
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

	void Logger::log_timestamp_info(
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		log_timestamp(
			text,
			configurations
		);
	}

	void Logger::log_timestamp_info(
		Result<void>& result,
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		log_timestamp(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_timestamp_info_async(
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
				log_timestamp_info(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_timestamp_info_async(
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

				log_timestamp_info(
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

	void Logger::log_timestamp_info_async(
		const std::function<void()>& callback,
		const std::string& text,
		const InfoLogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_timestamp_info(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_info_async(
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

				log_timestamp_info(
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

	void Logger::log_timestamp_success(
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		log_timestamp(
			text,
			configurations
		);
	}

	void Logger::log_timestamp_success(
		Result<void>& result,
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		log_timestamp(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_timestamp_success_async(
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
				log_timestamp_success(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_timestamp_success_async(
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

				log_timestamp_success(
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

	void Logger::log_timestamp_success_async(
		const std::function<void()>& callback,
		const std::string& text,
		const SuccessLogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_timestamp_success(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_success_async(
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

				log_timestamp_success(
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

	void Logger::log_timestamp_warning(
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		log_timestamp(
			text,
			configurations
		);
	}

	void Logger::log_timestamp_warning(
		Result<void>& result,
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		log_timestamp(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_timestamp_warning_async(
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
				log_timestamp_warning(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_timestamp_warning_async(
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

				log_timestamp_warning(
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

	void Logger::log_timestamp_warning_async(
		const std::function<void()>& callback,
		const std::string& text,
		const WarningLogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_timestamp_warning(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_warning_async(
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

				log_timestamp_warning(
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

	void Logger::log_timestamp_exception(
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		log_timestamp(
			text,
			configurations
		);
	}

	void Logger::log_timestamp_exception(
		Result<void>& result,
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		log_timestamp(
			result,
			text,
			configurations
		);
	}

	std::future<void> Logger::log_timestamp_exception_async(
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
				log_timestamp_exception(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_timestamp_exception_async(
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

				log_timestamp_exception(
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

	void Logger::log_timestamp_exception_async(
		const std::function<void()>& callback,
		const std::string& text,
		const ExceptionLogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_timestamp_exception(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_exception_async(
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

				log_timestamp_exception(
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

	void Logger::handle_exception(
		const std::string& origin,
		const std::string& message
	)
	{		
		std::scoped_lock lock(_mutex);

		Result<void> result;

		handle_exception(
			result,
			origin,
			message
		);
	}

	std::future<void> Logger::handle_exception_async(
		const std::string& origin,
		const std::string& message
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, origin, message,
			promise = std::move(promise)]() mutable
			{
				handle_exception(
					origin,
					message
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::handle_exception_async(
		const std::function<void()>& callback,
		const std::string& origin,
		const std::string& message
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, origin, message]() mutable
			{
				handle_exception(
					origin,
					message
				);

				callback();
			}
		);
	}

	void Logger::handle_exception(
		Result<void>& result,
		const std::string& origin,
		const std::string& message
	)
	{		
		Result<std::string> string_result;
		Result<std::future<void>> future_void_result;

		_to_log_format(
			string_result,
			"" + origin + " - " + message,
			LogLevel::EXCEPTION
		);

		log_to_output_files_async(
			future_void_result,
			string_result.get_value()
		);

		log_to_fragmentation_file_async(
			future_void_result,
			string_result.get_value()
		);

		log_to_collectivization_file_async(
			future_void_result,
			string_result.get_value()
		);

		result.set_to_good_status_without_value();
	}

	void Logger::handle_exception_async(
		Result<std::future<void>>& result,
		const std::string& origin,
		const std::string& message
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, origin, message,
			promise = std::move(promise)]() mutable
			{
				Result<void> result;

				handle_exception(
					result,
					origin,
					message
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::handle_exception_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& origin,
		const std::string& message
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, origin, message]() mutable
			{
				Result<void> result;

				handle_exception(
					result,
					origin,
					message
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_timestamp_to_console_and_file(
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		try
		{
			Result<void> result;

			log_timestamp_to_console_and_file(
				result,
				text,
				configurations
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::log_timestamp_to_console_and_file() - ") + exception.what()
			);
		}
	}

	std::future<void> Logger::log_timestamp_to_console_and_file_async(
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
				log_timestamp_to_console_and_file(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_timestamp_to_console_and_file_async(
		const std::function<void()>& callback,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_timestamp_to_console_and_file(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_to_console_and_file(
		Result<void>& result,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		Result<std::string> string_result;
		Result<std::future<void>> future_void_result;

		_to_log_format(
			string_result,
			text,
			configurations.log_level
		);

		log_to_console(
			result,
			string_result.get_value()
		);

		log_to_output_files_async(
			future_void_result,
			string_result.get_value()
		);

		log_to_fragmentation_file_async(
			future_void_result,
			string_result.get_value()
		);

		log_to_collectivization_file_async(
			future_void_result,
			string_result.get_value()
		);

		result.set_to_good_status_without_value();
	}

	void Logger::log_timestamp_to_console_and_file_async(
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

				log_timestamp_to_console_and_file(
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

	void Logger::log_timestamp_to_console_and_file_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				Result<void> result;

				log_timestamp_to_console_and_file(
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

	void Logger::log_timestamp_to_files(
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		try
		{
			Result<void> result;

			log_timestamp_to_files(
				result,
				text,
				configurations
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::log_timestamp_to_files() - ") + exception.what()
			);
		}
	}

	std::future<void> Logger::log_timestamp_to_files_async(
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
				log_timestamp_to_files(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_timestamp_to_files_async(
		const std::function<void()>& callback,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_timestamp_to_files(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_to_files(
		Result<void>& result,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		Result<std::string> string_result;
		Result<std::future<void>> future_void_result;

		_to_log_format(
			string_result,
			text,
			configurations.log_level
		);

		log_to_output_files_async(
			future_void_result,
			string_result.get_value()
		);

		log_to_fragmentation_file_async(
			future_void_result,
			string_result.get_value()
		);

		log_to_collectivization_file_async(
			future_void_result,
			string_result.get_value()
		);

		result.set_to_good_status_without_value();
	}

	void Logger::log_timestamp_to_files_async(
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

				log_timestamp_to_files(
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

	void Logger::log_timestamp_to_files_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				Result<void> result;

				log_timestamp_to_files(
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

	void Logger::log_timestamp_to_console(
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		try
		{
			Result<void> result;

			log_timestamp_to_console(
				result,
				text,
				configurations
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::log_timestamp_to_console() - ") + exception.what()
			);
		}
	}

	std::future<void> Logger::log_timestamp_to_console_async(
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
				log_timestamp_to_console(
					text,
					configurations
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_timestamp_to_console_async(
		const std::function<void()>& callback,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				log_timestamp_to_console(
					text,
					configurations
				);

				callback();
			}
		);
	}

	void Logger::log_timestamp_to_console(
		Result<void>& result,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		Result<std::string> string_result;
		Result<std::future<void>> future_void_result;

		_to_log_format(
			string_result,
			text,
			configurations.log_level
		);

		log_to_console_async(
			future_void_result,
			string_result.get_value()
		);

		result.set_to_good_status_without_value();
	}

	void Logger::log_timestamp_to_console_async(
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

				log_timestamp_to_console(
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

	void Logger::log_timestamp_to_console_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text,
		const LogConfigurations& configurations
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, callback, text, configurations]() mutable
			{
				Result<void> result;

				log_timestamp_to_console(
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

	void Logger::log_to_console(
		const std::string& text
	)
	{
		try
		{
			Result<void> result;

			log_to_console(
				result,
				text
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::log_to_console() - ") + exception.what()
			);
		}
	}

	std::future<void> Logger::log_to_console_async(
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
				log_to_console(
					text
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_to_console_async(
		const std::function<void()>& callback,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback]() mutable
			{
				log_to_console(
					text
				);

				callback();
			}
		);
	}

	void Logger::log_to_console(
		Result<void>& result,
		const std::string& text
	)
	{
		fast_io::io::print(fast_io::out(), text);

		result.set_to_good_status_without_value();
	}

	void Logger::log_to_console_async(
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

				log_to_console(
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

	void Logger::log_to_console_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback]() mutable
			{
				Result<void> result;

				log_to_console(
					result,
					text
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_to_files(
		const std::string& text
	)
	{
		try
		{
			Result<void> result;

			log_to_files(
				result,
				text
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::log_to_files() - ") + exception.what()
			);
		}
	}

	std::future<void> Logger::log_to_files_async(
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
				log_to_files(
					text
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_to_files_async(
		const std::function<void()>& callback,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback]() mutable
			{
				log_to_files(
					text
				);

				callback();
			}
		);
	}

	void Logger::log_to_files(
		Result<void>& result,
		const std::string& text
	)
	{
		Result<std::string> string_result;
		Result<std::future<void>> future_void_result;

		log_to_output_files_async(
			future_void_result,
			string_result.get_value()
		);

		log_to_fragmentation_file_async(
			future_void_result,
			string_result.get_value()
		);

		log_to_collectivization_file_async(
			future_void_result,
			string_result.get_value()
		);

		result.set_to_good_status_without_value();
	}

	void Logger::log_to_files_async(
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

				log_to_files(
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

	void Logger::log_to_files_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback]() mutable
			{
				Result<void> result;

				log_to_files(
					result,
					text
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_to_collectivization_file(
		const std::string& text
	)
	{
		try
		{
			Result<void> result;

			log_to_collectivization_file(
				result,
				text
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::log_to_collectivization_file() - ") + exception.what()
			);
		}
	}

	void Logger::log_to_collectivization_file(
		Result<void>& result,
		const std::string& text
	)
	{
		fast_io::obuf_file append_file(
			_log_file_collectivization_output_file_path,
			fast_io::open_mode::app
		);

		fast_io::io::print(
			append_file,
			text
		);

		append_file.close();

		result.set_to_good_status_without_value();
	}

	std::future<void> Logger::log_to_collectivization_file_async(
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
				log_to_collectivization_file(
					text
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_to_collectivization_file_async(
		const std::function<void()>& callback,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback]() mutable
			{
				log_to_collectivization_file(
					text
				);

				callback();
			}
		);
	}
	
	void Logger::log_to_collectivization_file_async(
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

				log_to_collectivization_file(
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

	void Logger::log_to_collectivization_file_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback]() mutable
			{
				Result<void> result;

				log_to_collectivization_file(
					result,
					text
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_to_fragmentation_file(
		const std::string& text
	)
	{
		try
		{
			Result<void> result;

			log_to_fragmentation_file(
				result,
				text
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::log_to_fragmentation_file() - ") + exception.what()
			);
		}
	}

	std::future<void> Logger::log_to_fragmentation_file_async(
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
				log_to_fragmentation_file(
					text
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_to_fragmentation_file_async(
		const std::function<void()>& callback,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback]() mutable
			{
				log_to_fragmentation_file(
					text
				);

				callback();
			}
		);
	}

	void Logger::log_to_fragmentation_file(
		Result<void>& result,
		const std::string& text
	)
	{
		Result<std::string> string_result;

		_generate_log_fragmentation_file_path(
			string_result
		);

		fast_io::obuf_file append_file(
			string_result.get_value(),
			fast_io::open_mode::app
		);

		fast_io::io::print(
			append_file,
			text
		);

		append_file.close();

		result.set_to_good_status_without_value();
	}

	void Logger::log_to_fragmentation_file_async(
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

				log_to_fragmentation_file(
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

	void Logger::log_to_fragmentation_file_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback]() mutable
			{
				Result<void> result;

				log_to_fragmentation_file(
					result,
					text
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_to_file(
		const std::string& path,
		const std::string& text
	)
	{
		try
		{
			Result<void> result;

			log_to_file(
				result,
				path,
				text
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::log_to_file() - ") + exception.what()
			);
		}
	}

	std::future<void> Logger::log_to_file_async(
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
				log_to_file(
					path,
					text
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_to_file_async(
		const std::function<void()>& callback,
		const std::string& path,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, path, text, callback]() mutable
			{
				log_to_file(
					path,
					text
				);

				callback();
			}
		);
	}

	void Logger::log_to_file(
		Result<void>& result,
		const std::string& path,
		const std::string& text
	)
	{		
		fast_io::obuf_file append_file(
			path,
			fast_io::open_mode::app
		);

		fast_io::io::print(
			append_file,
			text
		);

		append_file.close();		
	}

	void Logger::log_to_file_async(
		Result<std::future<void>>& result,
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
				Result<void> result;

				log_to_file(
					result,
					path,
					text
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(future)
		);
	}

	void Logger::log_to_file_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& path,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, path, text, callback]() mutable
			{
				Result<void> result;

				log_to_file(
					result,
					path,
					text
				);

				callback(
					result
				);
			}
		);
	}

	void Logger::log_to_output_files(
		const std::string& text
	)
	{
		try
		{
			Result<void> result;

			log_to_output_files(
				result,
				text
			);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::log_to_output_files() - ") + exception.what()
			);
		}
	}

	std::future<void> Logger::log_to_output_files_async(
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
				log_to_output_files(
					text
				);

				promise.set_value();
			}
		);

		return future;
	}

	void Logger::log_to_output_files_async(
		const std::function<void()>& callback,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback]() mutable
			{
				log_to_output_files(
					text
				);

				callback();
			}
		);
	}

	void Logger::log_to_output_files(
		Result<void>& result,
		const std::string& text
	)
	{
		if (_output_paths.empty())
		{
			return;
		}

		for (const auto& output_path :
			_output_paths)
		{
			log_to_file(
				output_path,
				text
			);
		}

		result.set_to_good_status_without_value();
	}

	void Logger::log_to_output_files_async(
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

				log_to_output_files(
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

	void Logger::log_to_output_files_async(
		const std::function<void(Result<void>& result)>& callback,
		const std::string& text
	)
	{
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, callback]() mutable
			{
				Result<void> result;

				log_to_output_files(
					result,
					text
				);

				callback(
					result
				);
			}
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
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::_generate_log_fragmentation_file_path() - ") + exception.what()
			);
		}
	}

	void Logger::_generate_log_fragmentation_file_path(
		Result<std::string>& result
	)
	{
		result.set_to_good_status_with_value(
			_log_file_fragmentation_output_folder_path +
				"\\" + _time_now(_log_file_fragmentation_format) + ".log"
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
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::_generate_log_collectivization_file_path() - ") + exception.what()
			);
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

	std::string Logger::_to_log_format(
		const std::string& text,
		const LogLevel& log_level
	)
	{
		try
		{
			Result<std::string> string_result;

			_to_log_format(
				string_result,
				text,
				log_level
			);

			return string_result.get_value();
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::_to_log_format() - ") + exception.what()
			);
		}
	}

	void Logger::_to_log_format(
		Result<std::string>& result,
		const std::string& text,
		const LogLevel& log_level
	)
	{
		_time_now(
			result,
			_log_format
		);
		result.get_value().reserve(256);
		result.set_value(			
			(_name.empty()) ? "" : ("[" + _name + "] [") +
			result.get_value() +
			"] [" +
			UTILITIES.LOG_LEVEL_ENUMS_2.at(log_level) +
			"]\t" +
			text +
			"\n"
		);
		result.set_status_to_good();
	}


	std::string Logger::_time_now(
		const TimeFormat& time_format
	)
	{
		try
		{
			Result<std::string> string_result;

			_time_now(
				string_result,
				time_format
			);

			return string_result.get_value();
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(
				std::string("QLogicaeCore::Logger::_time_now() - ") + exception.what()
			);
		}
	}

	void Logger::_time_now(
		Result<std::string>& result,
		const TimeFormat& format
	)
	{
		std::tm tm{};
		absl::Time now_time = absl::Now();
		std::time_t system_time = std::chrono::system_clock::to_time_t(
			std::chrono::system_clock::now()
		);
		absl::Duration since_epoch = now_time - absl::UnixEpoch();
		const char* time_format = UTILITIES.get_format_string(format);
		if (_log_time_zone == TimeZone::UTC)
		{
			gmtime_s(&tm, &system_time);
		}
		else
		{
			localtime_s(&tm, &system_time);
		}

		switch (format)
		{
			case TimeFormat::UNIX:
			{
				result.set_to_good_status_with_value(
					absl::StrCat(
						absl::ToUnixSeconds(
							now_time
						)
					)
				);

				break;
			}
			case TimeFormat::ISO8601:
			case TimeFormat::SECOND_LEVEL_TIMESTAMP:
			case TimeFormat::HOUR_12:
			case TimeFormat::HOUR_24:
			case TimeFormat::DATE_DASHED:
			case TimeFormat::DATE_MDY_SLASHED:
			case TimeFormat::DATE_DMY_SLASHED:
			case TimeFormat::DATE_DMY_SPACED:
			case TimeFormat::DATE_VERBOSE:
			{
				char format_buffer[32];

				std::strftime(
					format_buffer,
					64,
					time_format,
					&tm
				);

				result.set_to_good_status_with_value(
					format_buffer
				);
				break;		
			}
			case TimeFormat::MILLISECOND_LEVEL_TIMESTAMP:
			{
				char format_buffer[32];
				char millisecond_buffer[4];

				std::strftime(
					format_buffer,
					64,
					time_format,
					&tm
				);
				std::snprintf(
					millisecond_buffer,
					4,
					"%03d",
					static_cast<int>(
						absl::ToInt64Milliseconds(since_epoch) % 1000
					)
				);

				result.set_to_good_status_with_value(
					std::string(format_buffer) +
					"." +
					millisecond_buffer
				);

				break;
			}
			case TimeFormat::MICROSECOND_LEVEL_TIMESTAMP:
			{
				char format_buffer[32];
				char millisecond_buffer[4];
				char microseconds_buffer[4];

				std::strftime(
					format_buffer,
					64,
					time_format,
					&tm
				);
				std::snprintf(
					millisecond_buffer,
					4,
					"%03d",
					static_cast<int>(
						absl::ToInt64Milliseconds(since_epoch) % 1000
					)
				);
				std::snprintf(
					microseconds_buffer,
					4,
					"%03d",
					static_cast<int>(
						absl::ToInt64Microseconds(since_epoch) % 1000
					)
				);

				result.set_to_good_status_with_value(
					std::string(format_buffer) +
					"." +
					millisecond_buffer +
					":" +
					microseconds_buffer
				);

				break;
			}
			case TimeFormat::FULL_TIMESTAMP:
			{
				char format_buffer[32];
				char millisecond_buffer[4];
				char microseconds_buffer[4];
				char nanoseconds_buffer[4];

				std::strftime(
					format_buffer,
					64,
					time_format,
					&tm
				);
				std::snprintf(
					millisecond_buffer,
					4,
					"%03d",
					static_cast<int>(
						absl::ToInt64Milliseconds(since_epoch) % 1000
						)
				);			
				std::snprintf(
					microseconds_buffer,
					4,
					"%03d",
					static_cast<int>(
						absl::ToInt64Microseconds(since_epoch) % 1000
						)
				);
				std::snprintf(
					nanoseconds_buffer,
					4,
					"%03d",
					static_cast<int>(
						absl::ToInt64Nanoseconds(since_epoch) % 1000
						)
				);

				result.set_to_good_status_with_value(
					std::string(format_buffer) +
					"." +
					millisecond_buffer +
					":" +
					microseconds_buffer +
					":" +
					nanoseconds_buffer
				);
			
				break;
			}
			case TimeFormat::FULL_DASHED_TIMESTAMP:
			{
				char format_buffer[32];
				char millisecond_buffer[4];
				char microseconds_buffer[4];
				char nanoseconds_buffer[4];

				std::strftime(
					format_buffer,
					64,
					time_format,
					&tm
				);
				std::snprintf(
					millisecond_buffer,
					4,
					"%03d",
					static_cast<int>(
						absl::ToInt64Milliseconds(since_epoch) % 1000
						)
				);
				std::snprintf(
					microseconds_buffer,
					4,
					"%03d",
					static_cast<int>(
						absl::ToInt64Microseconds(since_epoch) % 1000
						)
				);
				std::snprintf(
					nanoseconds_buffer,
					4,
					"%03d",
					static_cast<int>(
						absl::ToInt64Nanoseconds(since_epoch) % 1000
						)
				);

				result.set_to_good_status_with_value(
					std::string(format_buffer) +
					"." +
					millisecond_buffer +
					"-" +
					microseconds_buffer +
					"-" +
					nanoseconds_buffer
				);

				break;
			}
			case TimeFormat::MILLISECOND_MICROSECOND_NANOSECOND:
			{
				result.set_to_good_status_with_value(
					absl::StrCat(
						"ms: ", absl::ToInt64Milliseconds(since_epoch),
						", us: ", absl::ToInt64Microseconds(since_epoch),
						", ns: ", absl::ToInt64Nanoseconds(since_epoch)
					)
				);

				break;
			}
			default:
			{
				result.set_to_good_status_with_value(
					"Invalid TimeFormat"
				);

				break;
			}
		}		
	}
}
