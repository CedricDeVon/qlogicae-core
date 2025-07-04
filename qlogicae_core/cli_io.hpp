#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    class CliIO
    {
    public:
		bool is_scan_enabled() const;
		bool is_print_enabled() const;
		void set_scan_enabled(const bool&);
		void set_print_enabled(const bool&);

		std::string scan() const;
		std::string builtin_scan() const;
		void print(const std::string_view& = "");
		void builtin_print(const std::string_view& = "");
		void print_with_new_line(const std::string_view& = "");
		void builtin_print_with_new_line(const std::string_view& = "");

		std::future<std::string> scan_async() const;
		std::future<std::string> builtin_scan_async() const;
		std::future<void> print_async(const std::string_view& = "");
		std::future<void> builtin_print_async(const std::string_view& = "");
		std::future<void> print_with_new_line_async(const std::string_view& = "");
		std::future<void> builtin_print_with_new_line_async(const std::string_view& = "");

		static CliIO& instance();

    protected:
		bool _is_scan_enabled;
		bool _is_print_enabled;
		mutable std::mutex _mutex;
		
        CliIO();
        ~CliIO() = default;
        CliIO(const CliIO&) = delete;
        CliIO(CliIO&&) noexcept = delete;
        CliIO& operator = (CliIO&&) = delete;
        CliIO& operator = (const CliIO&) = delete;
    };
}
