#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextCaseManager \
	)

#include "../includes/text_case_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{   
    TextCaseManager
		::TextCaseManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextCaseManagerConfigurations>()
	{
				
	}
	
	std::string
		TextCaseManager
			::convert_text(
				const std::string&
					text,
				const TextCase&
					target_type
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				text,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				text.empty() ||
				target_type == TextCase::NONE
			);				

			std::string result = text;
			if (configurations.is_specified_length_enabled)
			{
				result.resize(
					configurations.specified_length
				);
			}

			switch (target_type)
			{
				case TextCase::LOWERCASE:
				{					
					for (char& character : result)
					{
						character =
								static_cast<char>(
									std::tolower(static_cast<unsigned char>(
										character
									)
								)
							);
					}

					return result;
				}

				case TextCase::UPPERCASE:
				{
					for (char& character : result)
					{
						character =
								static_cast<char>(
									std::toupper(static_cast<unsigned char>(
										character
									)
								)
							);
					}

					return result;
				}

				case TextCase::CAPITALIZE:
				{
					bool done = false;

					for (char& character : result)
					{
						if (std::isalpha(static_cast<unsigned char>(character)))
						{
							character =
								static_cast<char>(
									std::toupper(static_cast<unsigned char>(
										character
									)
								)
							);
							done = true;
							break;
						}
					}

					return result;
				}

				case TextCase::TITLE:
				{
					bool capitalize_next = true;

					for (char& character : result)
					{
						if (std::isspace(static_cast<unsigned char>(character)))
						{
							capitalize_next = true;
							continue;
						}

						if (capitalize_next && std::isalpha(static_cast<unsigned char>(character)))
						{
							character =
								static_cast<char>(
									std::toupper(static_cast<unsigned char>(character))
								);
								capitalize_next = false;
							}
						else
						{
							character =
								static_cast<char>(
									std::tolower(static_cast<unsigned char>(character))
								);
							}
						}

					return result;
				}

				case TextCase::SENTENCE:
				{
					bool capitalize_next = true;

					for (char& character : result)
					{
						if (capitalize_next && std::isalpha(static_cast<unsigned char>(character)))
						{
							character =
								static_cast<char>(
									std::toupper(static_cast<unsigned char>(character))
								);
								capitalize_next = false;
							}
						else
						{
							character =
								static_cast<char>(
									std::tolower(static_cast<unsigned char>(character))
								);
							}

						if (character == '.' || character == '!' || character == '?')
						{
							capitalize_next = true;
						}
					}

					return result;
				}

				default:
				{
					return result;
				}
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				text
			);
        }
	}
		
	std::string
		TextCaseManager
			::convert_text(
				const std::string&
					text
			)
	{
		return
			convert_text(
				text,
				configurations
					.target_type
			);
	}
}

#endif
