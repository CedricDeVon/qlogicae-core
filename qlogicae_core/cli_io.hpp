#pragma once

#include "result.hpp"
#include "logger.hpp"
#include "utilities.hpp"

#include <boost/asio.hpp>

#include <future>
#include <shared_mutex>

namespace QLogicaeCore
{
    class CliIO
    {
    public:
		bool setup(
			const bool& is_scan_enabled = true,
			const bool& is_print_enabled = true
		);

		std::future<bool> setup_async(
			const bool& is_scan_enabled = true,
			const bool& is_print_enabled = true,
			const std::function<void(const bool& result)>& callback =
				[](const bool& result) {}
		);

		void setup(
			Result<void>& result,
			const bool& is_scan_enabled = true,
			const bool& is_print_enabled = true
		);

		void setup_async(
			Result<std::future<void>>& result,
			const bool& is_scan_enabled = true,
			const bool& is_print_enabled = true,
			const std::function<void(Result<void>& result)>& callback =
				[](Result<void>& result) {}
		);

		bool is_scan_enabled();

		bool is_print_enabled();

		void set_scan_enabled(
			const bool& value
		);

		void set_print_enabled(
			const bool& value
		);

		std::string scan();

		std::string builtin_scan();

		void print(
			const std::string& text = ""
		);

		void builtin_print(
			const std::string& text = ""
		);

		void print_with_new_line(
			const std::string& text = ""
		);

		void builtin_print_with_new_line(
			const std::string& text = ""
		);

		std::future<std::string> scan_async(
			const std::function<void(const std::string& result)>& callback =
				[](const std::string& result) {}
		);

		std::future<std::string> builtin_scan_async(
			const std::function<void(const std::string& result)>& callback =
				[](const std::string& result) {}
		);

		std::future<void> print_async(
			const std::string& text = "",
			const std::function<void()>& callback =
				[]() {}
		);

		std::future<void> builtin_print_async(
			const std::string& text = "",
			const std::function<void()>& callback =
				[]() {}
		);

		std::future<void> print_with_new_line_async(
			const std::string& text = "",
			const std::function<void()>& callback =
				[]() {}
		);

		std::future<void> builtin_print_with_new_line_async(
			const std::string& text = "",
			const std::function<void()>& callback =
				[]() {}
		);

		void is_scan_enabled(
			Result<bool>& result
		);

		void is_print_enabled(
			Result<bool>& result
		);

		void set_scan_enabled(
			Result<void>& result,
			const bool& value
		);

		void set_print_enabled(
			Result<void>& result,
			const bool& value
		);

		void scan(
			Result<std::string>& result
		);

		void builtin_scan(
			Result<std::string>& result
		);

		void print(
			Result<void>& result,
			const std::string& text = ""
		);

		void builtin_print(
			Result<void>& result,
			const std::string& text = ""
		);

		void print_with_new_line(
			Result<void>& result,
			const std::string& text = ""
		);

		void builtin_print_with_new_line(
			Result<void>& result,
			const std::string& text = ""
		);

		void scan_async(
			Result<std::future<std::string>>& result,
			const std::function<void(const std::string& result)>& callback =
				[](const std::string& result) {}
		);

		void builtin_scan_async(
			Result<std::future<std::string>>& result,
			const std::function<void(const std::string& result)>& callback =
				[](const std::string& result) {}
		);

		void print_async(
			Result<std::future<void>>& result,
			const std::string& text = "",
			const std::function<void(Result<void> result)>& callback =
				[](Result<void> result) {}
		);

		void builtin_print_async(
			Result<std::future<void>>& result,
			const std::string& text = "",
			const std::function<void(Result<void> result)>& callback =
				[](Result<void> result) {}
		);

		void print_with_new_line_async(
			Result<std::future<void>>& result,
			const std::string& text = "",
			const std::function<void(Result<void> result)>& callback =
				[](Result<void> result) {}
		);

		void builtin_print_with_new_line_async(
			Result<std::future<void>>& result,
			const std::string& text = "",
			const std::function<void(Result<void> result)>& callback =
				[](Result<void> result) {}
		);

		static CliIO& get_instance();

		static void get_instance(
			Result<CliIO*>& result
		);

    protected:
        CliIO();

        ~CliIO();

        CliIO(
			const CliIO& instance
		) = delete;

        CliIO(
			CliIO&& instance
		) noexcept = delete;

        CliIO& operator = (
			CliIO&& instance
		) = delete;

        CliIO& operator = (
			const CliIO& instance
		) = delete;
		
		bool _is_scan_enabled;
		
		bool _is_print_enabled;

		mutable std::mutex _mutex;		
    };
	
	inline static CliIO& CLI_IO =
		CliIO::get_instance();
}

