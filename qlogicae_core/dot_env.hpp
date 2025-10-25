#pragma once

#include "result.hpp"
#include "utilities.hpp"

namespace QLogicaeCore
{
	class DotEnv
	{
	public:
		bool setup();
		
		std::future<bool> setup_async();

		void setup_async(
			const std::function<void(const bool& result)>& callback
		);

		void setup(
			Result<void>& result
		);

		void setup_async(
			Result<std::future<void>>& result
		);

		void setup_async(
			const std::function<void(Result<void>& result)>& callback
		);

		bool remove(
			const wchar_t* key
		);

		bool set(
			const wchar_t* key,
			const wchar_t* value
		);

		std::optional<std::wstring> get(
			const wchar_t* key
		);

		void remove(
			Result<bool>& result,
			const wchar_t* key
		);

		void set(
			Result<bool>& result,
			const wchar_t* key,
			const wchar_t* value
		);

		void get(
			Result<std::wstring>& result,
			const wchar_t* key
		);

		static DotEnv& get_instance();

		static void get_instance(
			Result<DotEnv*>& result
		);

	protected:
		DotEnv();

		~DotEnv();

		DotEnv(
			const DotEnv& instance
		) = delete;

		DotEnv(
			DotEnv&& instance
		) noexcept = delete;

		DotEnv& operator = (
			DotEnv&& instance
		) = delete;

		DotEnv& operator = (
			const DotEnv& instance
		) = delete;
	};

	inline static DotEnv& DOT_ENV =
		DotEnv::get_instance();
}
