#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonTextManager \
	)

#include "../includes/json_text_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	JsonTextManager
		::JsonTextManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<JsonTextManagerConfigurations>()
    {
        
    }

	bool
		JsonTextManager
			::is_text_valid(
				const std::string&
					json_text
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				json_text.empty()
			);

			rapidjson::Document document;

			return !document.Parse(json_text.c_str()).HasParseError();
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }		
	}

	bool
		JsonTextManager
			::is_key_path_valid(
				const std::string&
					json_text,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		try
        {
			if
			(
				configurations
					.is_runtime_execution_disabled_for_feature_handling() ||				
				(
					configurations
						.is_edge_case_enabled_for_feature_handling() &&
					(
						json_text.empty() ||
						key_path.empty()
					)
				)
			)
			{
				return
					false;
			}

			boost::unique_lock<boost::mutex>
				mutex_lock;
			if (configurations.is_thread_safety_enabled_for_feature_handling())
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						feature_handling_mutex_1
					);
			}

			rapidjson::Document document;

			if (document.Parse(json_text.c_str()).HasParseError())
			{
				return false;
			}

			rapidjson::Value* current = &document;

			for (const auto& key : key_path)
			{
				if (std::holds_alternative<std::string>(key))
				{
					if (!current->IsObject())
					{
						return false;
					}

					const std::string& k = std::get<std::string>(key);

					if (!current->HasMember(k.c_str()))
					{
						return false;
					}

					current = &(*current)[k.c_str()];
				}
				else
				{
					if (!current->IsArray())
					{
						return false;
					}

					size_t index = std::get<size_t>(key);

					if (index >= current->Size())
					{
						return false;
					}

					current = &(*current)[static_cast<rapidjson::SizeType>(index)];
				}
			}

			return true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }		
	}

	std::string
		JsonTextManager
			::get_raw_json(
				const std::string&
					json_text,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		try
        {
			if
			(
				configurations
					.is_runtime_execution_disabled_for_feature_handling() ||				
				(
					configurations
						.is_edge_case_enabled_for_feature_handling() &&
					(
						json_text.empty() ||
						key_path.empty()
					)
				)
			)
			{
				return
					"";
			}

			boost::unique_lock<boost::mutex>
				mutex_lock;
			if (configurations.is_thread_safety_enabled_for_feature_handling())
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						feature_handling_mutex_1
					);
			}

			rapidjson::Document document;

			if (document.Parse(json_text.c_str()).HasParseError())
			{
				return {};
			}

			rapidjson::Value* current = &document;

			for (const auto& key : key_path)
			{
				if (std::holds_alternative<std::string>(key))
				{
					if (!current->IsObject())
					{
						return {};
					}

					const std::string& k = std::get<std::string>(key);

					if (!current->HasMember(k.c_str()))
					{
						return {};
					}

					current = &(*current)[k.c_str()];
				}
				else
				{
					if (!current->IsArray())
					{
						return {};
					}

					size_t index = std::get<size_t>(key);

					if (index >= current->Size())
					{
						return {};
					}

					current = &(*current)[static_cast<rapidjson::SizeType>(index)];
				}
			}

			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			current->Accept(writer);

			return buffer.GetString();
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }		
	}

	std::string
		JsonTextManager
			::get_string(
				const std::string&
					json_text,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		try
        {
			if
			(
				configurations
					.is_runtime_execution_disabled_for_feature_handling() ||				
				(
					configurations
						.is_edge_case_enabled_for_feature_handling() &&
					(
						json_text.empty() ||
						key_path.empty()
					)
				)
			)
			{
				return
					"";
			}

			boost::unique_lock<boost::mutex>
				mutex_lock;
			if (configurations.is_thread_safety_enabled_for_feature_handling())
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						feature_handling_mutex_1
					);
			}

			rapidjson::Document document;

			if (document.Parse(json_text.c_str()).HasParseError())
			{
				return {};
			}

			rapidjson::Value* current = &document;

			for (const auto& key : key_path)
			{
				if (std::holds_alternative<std::string>(key))
				{
					if (!current->IsObject())
					{
						return {};
					}

					const std::string& k = std::get<std::string>(key);

					if (!current->HasMember(k.c_str()))
					{
						return {};
					}

					current = &(*current)[k.c_str()];
				}
				else
				{
					if (!current->IsArray())
					{
						return {};
					}

					size_t index = std::get<size_t>(key);

					if (index >= current->Size())
					{
						return {};
					}

					current = &(*current)[static_cast<rapidjson::SizeType>(index)];
				}
			}

			if (!current->IsString())
			{
				return {};
			}

			return std::string(current->GetString(), current->GetStringLength());
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }		
	}

	double
		JsonTextManager
			::get_double(
				const std::string&
					json_text,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
		{
		try
        {
			if
			(
				configurations
					.is_runtime_execution_disabled_for_feature_handling() ||				
				(
					configurations
						.is_edge_case_enabled_for_feature_handling() &&
					(
						json_text.empty() ||
						key_path.empty()
					)
				)
			)
			{
				return
					0.0;
			}

			boost::unique_lock<boost::mutex>
				mutex_lock;
			if (configurations.is_thread_safety_enabled_for_feature_handling())
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						feature_handling_mutex_1
					);
			}
	
			rapidjson::Document document;

			if (document.Parse(json_text.c_str()).HasParseError())
			{
				return 0.0;
			}

			rapidjson::Value* current = &document;

			for (const auto& key : key_path)
			{
				if (std::holds_alternative<std::string>(key))
				{
					if (!current->IsObject())
					{
						return 0.0;
					}

					const std::string& k = std::get<std::string>(key);

					if (!current->HasMember(k.c_str()))
					{
						return 0.0;
					}

					current = &(*current)[k.c_str()];
				}
				else
				{
					if (!current->IsArray())
					{
						return 0.0;
					}

					size_t index = std::get<size_t>(key);

					if (index >= current->Size())
					{
						return 0.0;
					}

					current = &(*current)[static_cast<rapidjson::SizeType>(index)];
				}
			}

			if (!current->IsNumber())
			{
				return 0.0;
			}

			return current->GetDouble();
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }		
	}

	bool
		JsonTextManager
			::get_boolean(
				const std::string&
					json_text,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		try
        {
			if
			(
				configurations
					.is_runtime_execution_disabled_for_feature_handling() ||				
				(
					configurations
						.is_edge_case_enabled_for_feature_handling() &&
					(
						json_text.empty() ||
						key_path.empty()
					)
				)
			)
			{
				return
					false;
			}

			boost::unique_lock<boost::mutex>
				mutex_lock;
			if (configurations.is_thread_safety_enabled_for_feature_handling())
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						feature_handling_mutex_1
					);
			}

			rapidjson::Document document;

			if (document.Parse(json_text.c_str()).HasParseError())
			{
				return false;
			}

			rapidjson::Value* current = &document;

			for (const auto& key : key_path)
			{
				if (std::holds_alternative<std::string>(key))
				{
					if (!current->IsObject())
					{
						return false;
					}

					const std::string& k = std::get<std::string>(key);

					if (!current->HasMember(k.c_str()))
					{
						return false;
					}

					current = &(*current)[k.c_str()];
				}
				else
				{
					if (!current->IsArray())
					{
						return false;
					}

					size_t index = std::get<size_t>(key);

					if (index >= current->Size())
					{
						return false;
					}

					current = &(*current)[static_cast<rapidjson::SizeType>(index)];
				}
			}

			if (!current->IsBool())
			{
				return false;
			}

			return current->GetBool();
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::nullptr_t
		JsonTextManager
			::get_null(
				const std::string&
					json_text,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		try
        {
			if
			(
				configurations
					.is_runtime_execution_disabled_for_feature_handling() ||				
				(
					configurations
						.is_edge_case_enabled_for_feature_handling() &&
					(
						json_text.empty() ||
						key_path.empty()
					)
				)
			)
			{
				return
					nullptr;
			}

			boost::unique_lock<boost::mutex>
				mutex_lock;
			if (configurations.is_thread_safety_enabled_for_feature_handling())
			{
				mutex_lock =
					boost::unique_lock<boost::mutex>
					(
						feature_handling_mutex_1
					);
			}

			rapidjson::Document document;

			if (document.Parse(json_text.c_str()).HasParseError())
			{
				return nullptr;
			}

			rapidjson::Value* current = &document;

			for (const auto& key : key_path)
			{
				if (std::holds_alternative<std::string>(key))
				{
					if (!current->IsObject())
					{
						return nullptr;
					}

					const std::string& k = std::get<std::string>(key);

					if (!current->HasMember(k.c_str()))
					{
						return nullptr;
					}

					current = &(*current)[k.c_str()];
				}
				else
				{
					if (!current->IsArray())
					{
						return nullptr;
					}

					size_t index = std::get<size_t>(key);

					if (index >= current->Size())
					{
						return nullptr;
					}

					current = &(*current)[static_cast<rapidjson::SizeType>(index)];
				}
			}

			if (!current->IsNull())
			{
				return nullptr;
			}

			return nullptr;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	bool
		JsonTextManager
			::is_text_valid()
	{
		return
			is_text_valid(
				configurations
					.json_text
			);
	}

	bool
		JsonTextManager
			::is_key_path_valid(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			is_key_path_valid(
				configurations
					.json_text,
				key_path
			);
	}

	std::string
		JsonTextManager
			::get_raw_json(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			get_raw_json(
				configurations
					.json_text,
				key_path
			);
	}

	std::string
		JsonTextManager
			::get_string(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			get_string(
				configurations
					.json_text,
				key_path
			);
	}

	double
		JsonTextManager
			::get_double(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			get_double(
				configurations
					.json_text,
				key_path
			);
	}

	bool
		JsonTextManager
			::get_boolean(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			get_boolean(
				configurations
					.json_text,
				key_path
			);
	}

	std::nullptr_t
		JsonTextManager
			::get_null(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			get_null(
				configurations
					.json_text,
				key_path
			);
	}
}

#endif
