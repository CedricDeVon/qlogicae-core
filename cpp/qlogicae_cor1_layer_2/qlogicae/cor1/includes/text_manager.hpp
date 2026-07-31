#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextManager \
	)

#include "text_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TextManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextManagerConfigurations>
    {
    public:
		TextManager();

		~TextManager();

		bool
			construct();

		bool
			destruct();

		std::string
			replace_text_tokens(
				const std::string&
					text,
				const std::unordered_map<std::string, std::string>&
					dictionary
			);

		std::string
			replace_text_tokens(
				const std::string&
					text
			);

		std::vector<std::string>
			split_text(
				const std::string&
					text,
				const std::string&
					delimeter
			);	

		std::vector<std::string>
			split_text(
				const std::string&
					text
			);	

		template <typename InputType, typename OutputType> OutputType
			convert_text(
				InputType
					text
			);
	};

	template <typename InputType, typename OutputType> OutputType
		TextManager::
			convert_text(
				InputType
					text
			)
	{
		try
		{			
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				OutputType {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			using input_type  = std::decay_t<InputType>;
			using output_type = std::decay_t<OutputType>;

			if constexpr (
				std::is_same_v<output_type, std::string> ||
				std::is_same_v<output_type, std::wstring>
			)
			{
				if constexpr (
					std::is_same_v<input_type, std::wstring> ||
					std::is_same_v<input_type, wchar_t*> ||
					std::is_same_v<input_type, const wchar_t*>
				)
				{
					std::wstring wide =
						std::is_same_v<input_type, std::wstring>
							? text
							: (!text.empty() ? std::wstring(text) : std::wstring());

					if constexpr (std::is_same_v<output_type, std::wstring>)
					{
						return wide;
					}
					else
					{
						if (wide.empty())
						{
							return OutputType{};
						}

						int required_size =
							WideCharToMultiByte(
								CP_UTF8,
								0,
								wide.data(),
								static_cast<int>(wide.size()),
								nullptr,
								0,
								nullptr,
								nullptr
							);

						if (required_size <= 0)
						{
							return OutputType{};
						}

						std::string result(
							static_cast<std::size_t>(required_size),
							'\0'
						);

						WideCharToMultiByte(
							CP_UTF8,
							0,
							wide.c_str(),
							static_cast<int>(wide.size()),
							&result[0],
							required_size,
							nullptr,
							nullptr
						);

						return result;
					}
				}
				else if constexpr (
					std::is_same_v<input_type, std::string> ||
					std::is_same_v<input_type, char*> ||
					std::is_same_v<input_type, const char*>
				)
				{
					std::string narrow =
						std::is_same_v<input_type, std::string>
							? text
							: (!text.empty() ? std::string(text) : std::string());

					if constexpr (std::is_same_v<output_type, std::string>)
					{
						return narrow;
					}
					else
					{
						if (narrow.empty())
						{
							return OutputType{};
						}

						int required_size =
							MultiByteToWideChar(
								CP_UTF8,
								0,
								narrow.data(),
								static_cast<int>(narrow.size()),
								nullptr,
								0
							);

						if (required_size <= 0)
						{
							return OutputType{};
						}

						std::wstring result(
							static_cast<std::size_t>(required_size),
							L'\0'
						);

						MultiByteToWideChar(
							CP_UTF8,
							0,
							narrow.c_str(),
							static_cast<int>(narrow.size()),
							&result[0],
							required_size
						);

						return result;
					}
				}
				else
				{
					return OutputType{};
				}
			}
			else
			{
				return OutputType{};
			}
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				OutputType {}
			);
		}
	}
}

#endif
