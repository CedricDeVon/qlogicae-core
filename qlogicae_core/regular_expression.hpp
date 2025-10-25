#pragma once

#include "result.hpp"
#include "utilities.hpp"

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#include <string>
#include <vector>

namespace QLogicaeCore
{
	class RegularExpression
	{
	public:
		bool setup();

		void setup(
			Result<void>& result
		);

		std::future<bool> setup_async();

		void setup_async(
			const std::function<void(const bool& result)>& callback
		);

		void setup_async(
			Result<std::future<void>>& result
		);

		void setup_async(
			const std::function<void(Result<void>& result)>& callback
		);

		void clear_all_patterns();
		
		bool remove_pattern(
			const std::string& name
		);
		
		bool has_pattern(
			const std::string& name
		);
		
		std::string get_patterrn(
			const std::string& value
		);
		
		bool add_pattern(
			const std::string& name,
			const std::string& pattern
		);
		
		bool match_named(
			const std::string& name,
			const std::string& pattern
		);
		
		bool match_direct(
			const std::string& name,
			const std::string& pattern
		);

		std::future<bool> match_named_async(
			const std::string& name,
			const std::string& pattern
		);

		std::future<bool> match_direct_async(
			const std::string& name,
			const std::string& pattern
		);

		void clear_all_patterns(
			Result<void>& result
		);

		void remove_pattern(
			Result<bool>& result,
			const std::string& name
		);

		void has_pattern(
			Result<bool>& result,
			const std::string& name
		);

		void get_patterrn(
			Result<std::string>& result,
			const std::string& value
		);

		void add_pattern(
			Result<void>& result,
			const std::string& name,
			const std::string& pattern
		);

		void match_named(
			Result<bool>& result,
			const std::string& name,
			const std::string& pattern
		);

		void match_direct(
			Result<bool>& result,
			const std::string& name,
			const std::string& pattern
		);

		void match_named_async(
			Result<std::future<bool>>& result,
			const std::string& name,
			const std::string& pattern
		);

		void match_direct_async(
			Result<std::future<bool>>& result,
			const std::string& name,
			const std::string& pattern
		);

		static RegularExpression& get_instance();

		static void get_instance(
			Result<RegularExpression*>& result
		);

	protected:
		RegularExpression();

		~RegularExpression();		
		
		RegularExpression(
			const RegularExpression& instance
		) = delete;
		
		RegularExpression(
			RegularExpression&& instance
		) noexcept = default;
		
		RegularExpression& operator = (
			const RegularExpression& instance
		) = delete;
		
		RegularExpression& operator = (
			RegularExpression&& instance
		) noexcept = default;

		mutable std::shared_mutex _mutex;

		std::unordered_map<std::string, std::pair<std::string, pcre2_code*>>
			_compiled_patterns;

		bool _do_match(
			const std::string& subject, pcre2_code* get_error_code);
	};

	inline static RegularExpression& REGULAR_EXPRESSION =
		RegularExpression::get_instance();
}
