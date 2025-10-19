#pragma once

#include "result.hpp"

#include <future>
#include <shared_mutex>

namespace QLogicaeCore
{
    class CliIO
    {
    public:
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

		std::future<std::string> scan_async();

		std::future<std::string> builtin_scan_async();

		std::future<void> print_async(
			const std::string& text = ""
		);

		std::future<void> builtin_print_async(
			const std::string& text = ""
		);

		std::future<void> print_with_new_line_async(
			const std::string& text = ""
		);

		std::future<void> builtin_print_with_new_line_async(
			const std::string& text = ""
		);

		static CliIO& get_instance();

		void setup(
			Result<void>& result,
			const bool& is_scan_enabled = true,
			const bool& is_print_enabled = true
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
			Result<std::string>& result);

		void builtin_scan(
			Result<std::string>& result);

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
			Result<std::future<std::string>>& result
		);

		void builtin_scan_async(
			Result<std::future<std::string>>& result
		);

		void print_async(
			Result< std::future<void>>& result,
			const std::string& text = ""
		);

		void builtin_print_async(
			Result<std::future<void>>& result,
			const std::string& text = ""
		);

		void print_with_new_line_async(
			Result<std::future<void>>& result,
			const std::string& text = ""
		);

		void builtin_print_with_new_line_async(
			Result<std::future<void>>& result,
			const std::string& text = ""
		);

		static void get_instance(
			Result<CliIO*>& result
		);

    protected:
        CliIO();

        ~CliIO() = default;

        CliIO(const CliIO& cli_io) = delete;

        CliIO(CliIO&& cli_io) noexcept = delete;

        CliIO& operator = (CliIO&& cli_io) = delete;

        CliIO& operator = (const CliIO& cli_io) = delete;
		
		bool _is_scan_enabled;
		
		bool _is_print_enabled;

		mutable std::mutex _mutex;		
    };

	inline static CliIO& CLI_IO = CliIO::get_instance();
}

