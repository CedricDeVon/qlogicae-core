#pragma once

#include "result.hpp"

namespace QLogicaeCore
{
	class DotEnv
	{
	public:
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
		
		static DotEnv& get_instance();

		void setup(
			Result<void>& result
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

		static void get_instance(
			Result<DotEnv*>& result
		);

	protected:
		DotEnv();

		~DotEnv() = default;

		DotEnv(const DotEnv& dot_env) = delete;

		DotEnv(DotEnv&& dot_env) noexcept = delete;

		DotEnv& operator = (DotEnv&& dot_env) = delete;

		DotEnv& operator = (const DotEnv& dot_env) = delete;
	};

	inline static DotEnv& DOT_ENV = DotEnv::get_instance();
}
