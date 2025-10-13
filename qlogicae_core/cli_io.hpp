#pragma once

#include "result.hpp"

#include <future>
#include <shared_mutex>

namespace QLogicaeCore
{
    class CliIO
    {
    public:
		bool is_scan_enabled() const;

		bool is_print_enabled() const;

		void set_scan_enabled(const bool& value);

		void set_print_enabled(const bool& value);

		std::string scan();

		std::string builtin_scan();

		void print(
			const std::string_view& text = ""
		);

		void builtin_print(
			const std::string_view& text = ""
		);

		void print_with_new_line(
			const std::string_view& text = ""
		);

		void builtin_print_with_new_line(
			const std::string_view& text = ""
		);

		std::future<std::string> scan_async();

		std::future<std::string> builtin_scan_async();

		std::future<void> print_async(
			const std::string_view& text = ""
		);

		std::future<void> builtin_print_async(
			const std::string_view& text = ""
		);

		std::future<void> print_with_new_line_async(
			const std::string_view& text = ""
		);

		std::future<void> builtin_print_with_new_line_async(
			const std::string_view& text = ""
		);

		static CliIO& get_instance();

		void is_scan_enabled(Result<bool>& result) const;

		void is_print_enabled(Result<bool>& result) const;

		void set_scan_enabled(Result<void>& result,const bool& value);

		void set_print_enabled(Result<void>& result,const bool& value);

		void scan(Result<std::string>& result);

		void builtin_scan(Result<std::string>& result);

		void print(Result<void>& result,
			const std::string_view& text = ""
		);

		void builtin_print(Result<void>& result,
			const std::string_view& text = ""
		);

		void print_with_new_line(Result<void>& result,
			const std::string_view& text = ""
		);

		void builtin_print_with_new_line(Result<void>& result,
			const std::string_view& text = ""
		);

		void scan_async(Result<std::future<std::string>>& result);

		void builtin_scan_async(Result<std::future<std::string>>& result);

		void print_async(Result< std::future<void>>& result,
			const std::string_view& text = ""
		);

		void builtin_print_async(Result<std::future<void>>& result,
			const std::string_view& text = ""
		);

		void print_with_new_line_async(Result<std::future<void>>& result,
			const std::string_view& text = ""
		);

		void builtin_print_with_new_line_async(Result<std::future<void>>& result,
			const std::string_view& text = ""
		);

		static void get_instance(Result<CliIO*>& result);

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

