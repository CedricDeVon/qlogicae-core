#pragma once

#include "result.hpp"
#include "instance_manager.hpp"

namespace QLogicaeCppCore
{
	class RegularExpressionManager
	{
	public:
		RegularExpressionManager();

		~RegularExpressionManager();

		RegularExpressionManager(
			const RegularExpressionManager& instance
		) = delete;

		RegularExpressionManager(
			RegularExpressionManager&& instance
		) noexcept = default;

		RegularExpressionManager& operator = (
			const RegularExpressionManager& instance
			) = delete;

		RegularExpressionManager& operator = (
			RegularExpressionManager&& instance
			) noexcept = default;

		void clear_all_patterns(
			Result<bool>& result
		);

		void remove_pattern(
			Result<bool>& result,
			const std::string_view& name
		);

		void has_pattern(
			Result<bool>& result,
			const std::string_view& name
		);

		void get_patterrn(
			Result<std::string>& result,
			const std::string_view& value
		);

		void add_pattern(
			Result<bool>& result,
			const std::string_view& name,
			const std::string_view& pattern
		);

		void match_named(
			Result<bool>& result,
			const std::string_view& name,
			const std::string_view& pattern
		);

		void match_direct(
			Result<bool>& result,
			const std::string_view& name,
			const std::string_view& pattern
		);

	protected:		
		mutable std::shared_mutex _mutex;

		std::unordered_map<std::string, std::pair<std::string, pcre2_code*>>
			_compiled_patterns;

		void _do_match(
			Result<bool>& result,
			const std::string_view& subject,
			pcre2_code* get_error_code
		);
	};

	inline static RegularExpressionManager& REGULAR_EXPRESSION_MANAGER =
		INSTANCE_MANAGER.get_instance<RegularExpressionManager>();
}
