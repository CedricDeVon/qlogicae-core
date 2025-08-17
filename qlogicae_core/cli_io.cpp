#pragma once

#include "pch.h"

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
	
	void CliIO::set_scan_enabled(const bool& value)
	{
		_is_scan_enabled = value;
	}
	
	bool CliIO::is_print_enabled() const
	{
		return _is_print_enabled;
	}
	
	void CliIO::set_print_enabled(const bool& value)
	{
		_is_print_enabled = value;
	}
	
	std::string CliIO::scan()
	{
		try
		{
			std::scoped_lock lock(_mutex);

			std::string result;
			fast_io::io::scan(result);

			return result;
		}
		catch (const std::exception& exception)
		{
			std::cout << std::string("Exception at CliIO::scan(): ") + exception.what() << "\n";

			return builtin_scan();
		}
		catch (...)
		{
			std::cout << "Exception at CliIO::scan(): " << "\n";

			return builtin_scan();
		}
	}
	
	void CliIO::print(const std::string_view& text)
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
		return std::async(std::launch::async, [this]() -> std::string
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

	void CliIO::print_with_new_line(const std::string_view& text)
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
		const std::string_view& text)
	{
		return std::async(std::launch::async, [this, text]() -> void
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

	void CliIO::builtin_print_with_new_line(const std::string_view& text)
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
		const std::string_view& text)
	{
		return std::async(std::launch::async, [this, text]() -> void
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
	
	std::future<void> CliIO::print_async(const std::string_view& text)
	{
		return std::async(std::launch::async, [this, text]() -> void
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
		return std::async(std::launch::async, [this]() -> std::string
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
		const std::string_view& text)
	{
		return std::async(std::launch::async, [this, text]() -> void
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
		const std::string_view& text)
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
}

