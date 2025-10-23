#include "pch.hpp"

#include "cli_io.hpp"

namespace QLogicaeCore
{
	CliIO::CliIO()
	{
		_is_scan_enabled = _is_print_enabled = true;
	}

	CliIO::~CliIO()
	{
		
	}

	bool CliIO::setup(
		const bool& is_scan_enabled,
		const bool& is_print_enabled
	)
	{
		try
		{
			Result<void> result;

			setup(
				result,
				is_scan_enabled,
				is_print_enabled
			);

			return result.is_status_safe();
		}
		catch (const std::exception& exception)
		{

		}
	}

	void CliIO::setup(
		Result<void>& result,
		const bool& is_scan_enabled,
		const bool& is_print_enabled
	)
	{
		_is_scan_enabled = is_scan_enabled;
		_is_print_enabled = is_print_enabled;

		result.set_to_good_status_without_value();
	}

	std::future<bool> CliIO::setup_async(
		const bool& is_scan_enabled,
		const bool& is_print_enabled
	)
	{
		std::promise<bool> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, promise = std::move(promise)]() mutable
			{
				promise.set_value(
					setup()
				);
			}
		);

		return future;
	}

	void CliIO::setup_async(
		Result<std::future<void>>& result,
		const bool& is_scan_enabled,
		const bool& is_print_enabled
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, is_scan_enabled, is_print_enabled, promise = std::move(promise)]() mutable
			{
				Result<void> result;

				setup(
					result,
					is_scan_enabled,
					is_print_enabled
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(
				future
			)
		);
	}

	bool CliIO::is_scan_enabled()
	{
		return _is_scan_enabled;
	}

	void CliIO::is_scan_enabled(
		Result<bool>& result)
	{
		result.set_to_good_status_with_value(
			_is_scan_enabled
		);
	}

	bool CliIO::is_print_enabled()
	{
		return _is_print_enabled;
	}

	void CliIO::is_print_enabled(
		Result<bool>& result)
	{
		result.set_to_good_status_with_value(
			_is_print_enabled
		);
	}

	void CliIO::set_scan_enabled(
		const bool& value
	)
	{
		_is_scan_enabled = value;
	}

	void CliIO::set_scan_enabled(
		Result<void>& result,
		const bool& value
	)
	{
		_is_scan_enabled = value;

		result.set_to_good_status_without_value();
	}

	void CliIO::set_print_enabled(
		const bool& value
	)
	{
		_is_print_enabled = value;
	}

	void CliIO::set_print_enabled(
		Result<void>& result,
		const bool& value
	)
	{
		_is_print_enabled = value;

		result.set_to_good_status_without_value();
	}

	std::string CliIO::builtin_scan()
	{
		try
		{
			std::scoped_lock lock(_mutex);

			Result<std::string> result;

			builtin_scan(
				result
			);

			return result.get_value();
		}
		catch (const std::exception& exception)
		{
			
		}		
	}

	void CliIO::builtin_scan(
		Result<std::string>& result
	)
	{
		std::string content;
		std::cin >> content;

		result.set_to_good_status_with_value(content);
	}

	std::string CliIO::scan()
	{
		try
		{
			std::scoped_lock lock(_mutex);

			Result<std::string> result;

			scan(
				result
			);

			return result.get_value();
		}
		catch (const std::exception& exception)
		{
			
		}
	}

	void CliIO::scan(
		Result<std::string>& result
	)
	{		
		std::string content;

		std::getline(std::cin, content);
		if (!content.empty() && content.back() == '\r')
		{
			content.pop_back();
		}

		result.set_to_good_status_with_value(content);
	}

	void CliIO::print(
		const std::string& text
	)
	{
		try
		{
			std::scoped_lock lock(_mutex);

			Result<void> result;

			print(
				result,
				text
			);
		}
		catch (const std::exception& exception)
		{

		}
	}

	void CliIO::print(
		Result<void>& result,
		const std::string& text
	)
	{		
		fast_io::io::print(fast_io::out(), text);

		result.set_to_good_status_without_value();
	}

	void CliIO::print_with_new_line(
		const std::string& text
	)
	{
		try
		{
			std::scoped_lock lock(_mutex);

			Result<void> result;

			print_with_new_line(
				result,
				text
			);
		}
		catch (const std::exception& exception)
		{

		}
	}

	void CliIO::print_with_new_line(
		Result<void>& result,
		const std::string& text
	)
	{		
		fast_io::io::println(fast_io::out(), text);

		result.set_to_good_status_without_value();
	}

	void CliIO::builtin_print_with_new_line(
		const std::string& text
	)
	{
		try
		{
			std::scoped_lock lock(_mutex);

			Result<void> result;

			builtin_print_with_new_line(
				result,
				text
			);
		}
		catch (const std::exception& exception)
		{

		}
	}

	void CliIO::builtin_print_with_new_line(
		Result<void>& result,
		const std::string& text
	)
	{
		std::cout << text;
	}

	void CliIO::builtin_print(
		const std::string& text
	)
	{
		try
		{
			std::scoped_lock lock(_mutex);

			Result<void> result;

			builtin_print(
				result,
				text
			);
		}
		catch (const std::exception& exception)
		{

		}
	}

	void CliIO::builtin_print(
		Result<void>& result,
		const std::string& text
	)
	{
		std::cout << text;

		result.set_to_good_status_without_value();
	}

	std::future<std::string> CliIO::scan_async()
	{
		std::promise<std::string> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, promise = std::move(promise)]() mutable
			{
				promise.set_value(
					scan()
				);
			}
		);

		return future;
	}

	void CliIO::scan_async(
		Result<std::future<std::string>>& result
	)
	{
		std::promise<std::string> promise;
		auto future = promise.get_future();
		
		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, promise = std::move(promise)]() mutable
			{
				Result<std::string> result;

				scan(result);

				promise.set_value(result.get_value());
			}
		);

		result.set_to_good_status_with_value(
			std::move(
				future
			)
		);
	}

	std::future<void> CliIO::print_with_new_line_async(
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, promise = std::move(promise)]() mutable
			{
				print_with_new_line();

				promise.set_value();
			}
		);

		return future;
	}

	void CliIO::print_with_new_line_async(
		Result<std::future<void>>& result,
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, promise = std::move(promise)]() mutable
			{
				Result<void> result;

				print_with_new_line(result);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(
				future
			)
		);
	}

	std::future<void> CliIO::builtin_print_with_new_line_async(
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, promise = std::move(promise)]() mutable
			{
				builtin_print_with_new_line();

				promise.set_value();
			}
		);

		return future;
	}

	void CliIO::builtin_print_with_new_line_async(
		Result<std::future<void>>& result,
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, promise = std::move(promise)]() mutable
			{
				Result<void> result;

				builtin_print_with_new_line(result);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(
				future
			)
		);
	}

	std::future<void> CliIO::print_async(
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, promise = std::move(promise)]() mutable
			{
				print(text);

				promise.set_value();
			}
		);

		return future;
	}

	void CliIO::print_async(
		Result<std::future<void>>& result,
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, promise = std::move(promise)]() mutable
			{
				Result<void> inner_result;

				print(inner_result, text);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(
				future
			)
		);
	}

	std::future<std::string> CliIO::builtin_scan_async()
	{
		std::promise<std::string> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, promise = std::move(promise)]() mutable
			{
				promise.set_value(
					builtin_scan()
				);
			}
		);

		return future;
	}

	void CliIO::builtin_scan_async(
		Result<std::future<std::string>>& result
	)
	{
		std::promise<std::string> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, promise = std::move(promise)]() mutable
			{
				Result<std::string> inner_result;

				builtin_scan(inner_result);

				promise.set_value(
					inner_result.get_value()
				);
			}
		);

		result.set_to_good_status_with_value(
			std::move(
				future
			)
		);
	}

	std::future<void> CliIO::builtin_print_async(
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, promise = std::move(promise)]() mutable
			{
				builtin_print(text);

				promise.set_value();
			}
		);

		return future;
	}

	void CliIO::builtin_print_async(
		Result<std::future<void>>& result,
		const std::string& text
	)
	{
		std::promise<void> promise;
		auto future = promise.get_future();

		boost::asio::post(
			UTILITIES.BOOST_ASIO_POOL,
			[this, text, promise = std::move(promise)]() mutable
			{
				Result<void> inner_result;

				builtin_print(
					inner_result,
					text
				);

				promise.set_value();
			}
		);

		result.set_to_good_status_with_value(
			std::move(
				future
			)
		);
	}

	CliIO& CliIO::get_instance()
	{
		static CliIO singleton;

		return singleton;
	}

	void CliIO::get_instance(
		Result<CliIO*>& result
	)
	{
		static CliIO singleton;

		result.set_to_good_status_with_value(
			&singleton
		);
	}
}

