#pragma once

#include "pch.h"

namespace QLogicaeCore
{
	class RegularExpression
	{
	public:
		void clear_all_patterns();
		bool remove_pattern(const std::string&);
		bool has_pattern(const std::string&) const;
		std::string get_patterrn(const std::string&) const;
		bool add_pattern(const std::string&, const std::string&);
		bool match_named(const std::string&, const std::string&);
		bool match_direct(const std::string&, const std::string&);

		std::future<bool> match_named_async(
			const std::string&,
			const std::string&
		);
		std::future<bool> match_direct_async(
			const std::string&,
			const std::string&
		);

		static RegularExpression& get_instance();

	protected:
		mutable std::shared_mutex _mutex;
		std::unordered_map<std::string, std::pair<std::string, pcre2_code*>>
			_compiled_patterns;

		~RegularExpression();
		RegularExpression() = default;
		RegularExpression(const RegularExpression&) = delete;
		RegularExpression(RegularExpression&&) noexcept = default;
		RegularExpression& operator = (const RegularExpression&) = delete;
		RegularExpression& operator = (RegularExpression&&) noexcept = default;

		bool _do_match(
			const std::string& subject, pcre2_code* get_error_code) const;
	};

	inline static RegularExpression& REGULAR_EXPRESSION =
		RegularExpression::get_instance();
}
