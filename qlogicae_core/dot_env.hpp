#pragma once

#include "pch.h"

namespace QLogicaeCore
{
	class DotEnv
	{
	public:
		bool remove(const wchar_t*);
		bool set(const wchar_t*, const wchar_t*);
		std::optional<std::wstring> get(const wchar_t*);
		
		static DotEnv& get_instance();

	protected:
		DotEnv();
		~DotEnv() = default;
		DotEnv(const DotEnv&) = delete;
		DotEnv(DotEnv&&) noexcept = delete;
		DotEnv& operator = (DotEnv&&) = delete;
		DotEnv& operator = (const DotEnv&) = delete;
	};

	inline static DotEnv& DOT_ENV = DotEnv::get_instance();
}

