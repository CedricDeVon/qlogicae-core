#include "pch.hpp"

#include "cli_io.hpp"

namespace QLogicaeCore
{
	CliIO::CliIO()
	{
		_is_scan_enabled = _is_print_enabled = true;
	}

	bool CliIO::is_scan_enabled() const
	{
		return _is_scan_enabled;
	}
	
	void CliIO::set_scan_enabled(
		const bool& value
	)
	{
		_is_scan_enabled = value;
	}
	
	bool CliIO::is_print_enabled() const
	{
		return _is_print_enabled;
	}
	
	void CliIO::set_print_enabled(
		const bool& value
	)
	{
		_is_print_enabled = value;
	}
	
	std::string CliIO::scan()
	{
		try
		{
			std::scoped_lock lock(_mutex);

			std::string result;

			std::getline(std::cin, result);
			if (!result.empty() && result.back() == '\r')
			{
				result.pop_back();
			}
			
			return result;
		}
		catch (const std::exception& exception)
		{
			std::cout << std::string("Exception at CliIO::scan(): ") + exception.what() << "\n";

			return "";
		}
		catch (...)
		{
			std::cout << "Exception at CliIO::scan(): " << "\n";

			return "";
		}
	}
	
	void CliIO::print(const std::string& text)
	{
		try
		{
			std::scoped_lock lock(_mutex);

			fast_io::io::print(fast_io::out(), text);
		}
		catch (const std::exception& exception)
		{
			std::cout << std::string("Exception at CliIO::print(): ") + exception.what() << "\n";
		}
	}
	
	std::future<std::string> CliIO::scan_async()
	{
		return std::async(
			std::launch::async,
				[this]() -> std::string
		{
			try
			{
				return scan();
			}
			catch (const std::exception& exception)
			{
				std::cout << std::string("Exception at CliIO::scan_async(): ") + exception.what() << "\n";

				return "";
			}
		});
	}

	void CliIO::print_with_new_line(
		const std::string& text
	)
	{
		try
		{
			std::scoped_lock lock(_mutex);

			fast_io::io::println(fast_io::out(), text);
		}
		catch (const std::exception& exception)
		{
			std::cout << std::string("Exception at CliIO::print_with_new_line(): ") + exception.what() << "\n";
		}
	}

	std::future<void> CliIO::print_with_new_line_async(
		const std::string& text
	)
	{
		return std::async(
			std::launch::async,
				[this, text]() -> void
		{
			try
			{
				print_with_new_line(text);
			}
			catch (const std::exception& exception)
			{
				std::cout << std::string("Exception at CliIO::print_with_new_line_async(): ") + exception.what() << "\n";
			}
		});
	}

	void CliIO::builtin_print_with_new_line(
		const std::string& text
	)
	{
		try
		{
			std::scoped_lock lock(_mutex);

			std::cout << text;
		}
		catch (const std::exception& exception)
		{
			std::cout << std::string("Exception at CliIO::builtin_print_with_new_line(): ") + exception.what() << "\n";
		}
	}

	std::future<void> CliIO::builtin_print_with_new_line_async(
		const std::string& text
	)
	{
		return std::async(
			std::launch::async,
				[this, text]() -> void
		{
			try
			{
				builtin_print_with_new_line(text);
			}
			catch (const std::exception& exception)
			{
				std::cout << std::string("Exception at CliIO::builtin_print_with_new_line_async(): ") + exception.what() << "\n";
			}
		});
	}
	
	std::future<void> CliIO::print_async(
		const std::string& text
	)
	{
		return std::async(
			std::launch::async,
				[this, text]() -> void
		{
			try
			{
				print(text);
			}
			catch (const std::exception& exception)
			{
				std::cout << std::string("Exception at CliIO::print_async(): ") + exception.what() << "\n";
			}
		});
	}

	std::future<std::string> CliIO::builtin_scan_async()
	{
		return std::async(
			std::launch::async,
				[this]() -> std::string
		{
			try
			{
				return builtin_scan();
			}
			catch (const std::exception& exception)
			{
				std::cout << std::string("Exception at CliIO::builtin_scan_async(): ") + exception.what() << "\n";

				return "";
			}
		});
	}

	std::future<void> CliIO::builtin_print_async(
		const std::string& text
	)
	{
		return std::async(
			std::launch::async,
				[this, text]() -> void
		{
			try
			{
				builtin_print(text);
			}
			catch (const std::exception& exception)
			{
				std::cout << std::string("Exception at CliIO::builtin_print_async(): ") + exception.what() << "\n";
			}
		});
	}

	void CliIO::builtin_print(
		const std::string& text)
	{
		std::cout << text;
	}

	std::string CliIO::builtin_scan()
	{
		std::string result;
		std::cin >> result;

		return result;
	}

	CliIO& CliIO::get_instance()
	{
		static CliIO singleton;

		return singleton;
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

	void CliIO::is_scan_enabled(
		Result<bool>& result) const
	{
		result.set_to_good_status_with_value(
			_is_scan_enabled
		);
	}

	void CliIO::is_print_enabled(
		Result<bool>& result) const
	{
		result.set_to_good_status_with_value(
			_is_print_enabled
		);
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
		Result<void>& result,
		const bool& value
	)
	{
		_is_print_enabled = value;

		result.set_to_good_status_without_value();
	}

	void CliIO::scan(Result<std::string>& result)
	{
		std::scoped_lock lock(_mutex);

		std::string content;

		std::getline(std::cin, content);
		if (!content.empty() && content.back() == '\r')
		{
			content.pop_back();
		}

		result.set_to_good_status_with_value(content);
	}

	void CliIO::builtin_scan(Result<std::string>& result)
	{
		std::string content;
		std::cin >> content;

		result.set_to_good_status_with_value(content);
	}

	void CliIO::print(Result<void>& result,
		const std::string& text
	)
	{
		std::scoped_lock lock(_mutex);

		fast_io::io::print(fast_io::out(), text);
	}

	void CliIO::builtin_print(
		Result<void>& result,
		const std::string& text
	)
	{
		std::cout << text;

		result.set_to_good_status_without_value();
	}

	void CliIO::print_with_new_line(
		Result<void>& result,
		const std::string& text
	)
	{
		std::scoped_lock lock(_mutex);

		fast_io::io::println(fast_io::out(), text);
	}

	void CliIO::builtin_print_with_new_line(
		Result<void>& result,
		const std::string& text
	)
	{
		std::scoped_lock lock(_mutex);

		std::cout << text;
	}

	void CliIO::scan_async(
		Result<std::future<std::string>>& result)
	{
		result.set_to_good_status_with_value(std::async(
			std::launch::async, [this]() -> std::string
			{
				Result<std::string> result;
				scan(result);

				return result.get_value();
			}
		));
	}

	void CliIO::builtin_scan_async(
		Result<std::future<std::string>>& result)
	{
		result.set_to_good_status_with_value(
			std::async(std::launch::async,
			[this]() -> std::string
			{
				Result<std::string> result;
				builtin_scan(result);

				return result.get_value();
			}
		));
	}

	void CliIO::print_async(
		Result<std::future<void>>& result,
		const std::string& text
	)
	{
		result.set_to_good_status_with_value(
			std::async(std::launch::async,
			[this, text]() -> void
			{
				Result<void> result;
				
				print(result, text);				
			}
		));
	}

	void CliIO::builtin_print_async(
		Result<std::future<void>>& result,
		const std::string& text
	)
	{
		result.set_to_good_status_with_value(
			std::async(std::launch::async,
			[this, text]() -> void
			{
				Result<void> result;
				
				builtin_print(result, text);
			}
		));
	
	}

	void CliIO::print_with_new_line_async(
		Result<std::future<void>>& result,
		const std::string& text
	)
	{
		result.set_to_good_status_with_value(
			std::async(std::launch::async,
			[this, text]() -> void
			{
				Result<void> result;

				print_with_new_line(result, text);
			}
		));
	}

	void CliIO::builtin_print_with_new_line_async(
		Result<std::future<void>>& result,
		const std::string& text
	)
	{
		result.set_to_good_status_with_value(
			std::async(std::launch::async,
			[this, text]() -> void
			{
				Result<void> result;
				
				builtin_print_with_new_line(result, text);
			}
		));
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

