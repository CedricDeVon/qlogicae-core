#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonFileIoManager \
	)

#include "../includes/json_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	JsonFileIoManager
		::JsonFileIoManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<JsonFileIoManagerConfigurations>()
    {
        
    }

	std::unordered_map<std::string, std::any>
		JsonFileIoManager
			::execute_batch_operations(
				const std::unordered_map<std::string, JsonFileIoBatchOperationConfigurations>&
					batch_operations
			)	
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				batch_operations.empty()
			);

            return
				{};
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	rapidjson::Value*
		JsonFileIoManager
			::traverse(
				rapidjson::Document&
					document,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		rapidjson::Value* current = &document;

		for (const auto& key : key_path)
		{
			if (std::holds_alternative<std::string>(key))
			{
				const auto& name = std::get<std::string>(key);

				if (!current->IsObject())
					return nullptr;

				if (!current->HasMember(name.c_str()))
					return nullptr;

				current = &((*current)[name.c_str()]);
			}
			else
			{
				rapidjson::SizeType index =
					static_cast<rapidjson::SizeType>(
						std::get<size_t>(key)
						);

				if (!current->IsArray())
					return nullptr;

				if (index >= current->Size())
					return nullptr;

				current = &((*current)[index]);
			}
		}

		return current;
	}

	bool
		JsonFileIoManager
			::is_valid(
				const std::string&
					file_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path)
			);

			fast_io::native_file_loader file(file_path);

			rapidjson::Document doc;
			doc.Parse(file.data(), file.size());

			return !doc.HasParseError();
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
		JsonFileIoManager
			::is_key_path_valid(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);

			fast_io::native_file_loader file(file_path);

			rapidjson::Document doc;
			doc.Parse(file.data(), file.size());

			if (doc.HasParseError())
				return false;

			return traverse(doc, key_path) != nullptr;
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
		JsonFileIoManager
			::get_raw_json(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);

			fast_io::native_file_loader file(file_path);

			rapidjson::Document doc;
			doc.Parse(file.data(), file.size());

			if (doc.HasParseError())
				return {};

			auto* value = traverse(doc, key_path);
			if (!value)
				return {};

			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			value->Accept(writer);

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
		JsonFileIoManager
			::get_string(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);

			fast_io::native_file_loader file(file_path);

			rapidjson::Document doc;
			doc.Parse(file.data(), file.size());

			if (doc.HasParseError())
				return {};

			auto* value = traverse(doc, key_path);
			if (!value || !value->IsString())
				return {};

			return value->GetString();
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
		JsonFileIoManager
			::get_double(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);

			fast_io::native_file_loader file(file_path);

			rapidjson::Document doc;
			doc.Parse(file.data(), file.size());

			if (doc.HasParseError())
				return 0.0;

			auto* value = traverse(doc, key_path);
			if (!value || !value->IsNumber())
				return 0.0;

			return value->GetDouble();
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
		JsonFileIoManager
			::get_boolean(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);

			fast_io::native_file_loader file(file_path);

			rapidjson::Document doc;
			doc.Parse(file.data(), file.size());

			if (doc.HasParseError())
				return false;

			auto* value = traverse(doc, key_path);
			if (!value || !value->IsBool())
				return false;

			return value->GetBool();
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            return
				handle_error_outputs(
					exception
				);
        }
	}

	std::nullptr_t
		JsonFileIoManager
			::get_null(
				const std::string&
					file_path,
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		try
        {			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);

			fast_io::native_file_loader file(file_path);

			rapidjson::Document doc;
			doc.Parse(file.data(), file.size());

			if (doc.HasParseError())
				return nullptr;

			auto* value = traverse(doc, key_path);
			if (!value || !value->IsNull())
				return nullptr;

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

	bool JsonFileIoManager::set_raw_json(
		const std::string& file_path,
		const std::vector<std::variant<std::string, size_t>>& key_path,
		const std::string& value)
	{
		QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
			QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
		);

		std::ifstream input(file_path, std::ios::binary);
		if (!input)
			return false;

		std::string file_content((std::istreambuf_iterator<char>(input)),
			std::istreambuf_iterator<char>());
		input.close();

		rapidjson::Document doc;
		if (file_content.empty())
			doc.SetObject();
		else
			doc.Parse(file_content.c_str(), file_content.size());
		if (doc.HasParseError())
			return false;

		rapidjson::Document new_value;
		new_value.Parse(value.c_str(), value.size());
		if (new_value.HasParseError())
			return false;

		rapidjson::Value* current = &doc;
		for (const auto& key : key_path)
		{
			if (std::holds_alternative<std::string>(key))
			{
				const auto& name = std::get<std::string>(key);
				if (!current->IsObject())
					current->SetObject();
				if (!current->HasMember(name.c_str()))
				{
					rapidjson::Value k(name.c_str(), doc.GetAllocator());
					rapidjson::Value v(rapidjson::kObjectType);
					current->AddMember(std::move(k), std::move(v), doc.GetAllocator());
				}
				current = &((*current)[name.c_str()]);
			}
			else
			{
				rapidjson::SizeType index = static_cast<rapidjson::SizeType>(std::get<size_t>(key));
				if (!current->IsArray())
					current->SetArray();
				while (current->Size() <= index)
					current->PushBack(rapidjson::Value(rapidjson::kObjectType), doc.GetAllocator());
				current = &((*current)[index]);
			}
		}

		rapidjson::Value copy;
		copy.CopyFrom(new_value, doc.GetAllocator());
		*current = std::move(copy);

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		std::ofstream output(file_path, std::ios::binary | std::ios::trunc);
		if (!output)
			return false;

		output.write(buffer.GetString(), buffer.GetSize());
		output.close();

		return true;
	}

	bool JsonFileIoManager::append_raw_json(
		const std::string& file_path,
		const std::vector<std::variant<std::string, size_t>>& key_path,
		const std::string& value)
	{
		rapidjson::Document new_value;
		new_value.Parse(value.c_str(), value.size());
		if (new_value.HasParseError())
			return false;

		std::ifstream input(file_path, std::ios::binary);
		if (!input)
			return false;

		std::string file_content((std::istreambuf_iterator<char>(input)),
			std::istreambuf_iterator<char>());
		input.close();

		rapidjson::Document doc;
		if (file_content.empty())
			doc.SetObject();
		else
			doc.Parse(file_content.c_str(), file_content.size());
		if (doc.HasParseError())
			return false;

		rapidjson::Value* current = &doc;
		for (const auto& key : key_path)
		{
			if (std::holds_alternative<std::string>(key))
			{
				const auto& name = std::get<std::string>(key);
				if (!current->IsObject())
					current->SetObject();
				if (!current->HasMember(name.c_str()))
				{
					rapidjson::Value k(name.c_str(), doc.GetAllocator());
					rapidjson::Value v(rapidjson::kObjectType);
					current->AddMember(std::move(k), std::move(v), doc.GetAllocator());
				}
				current = &((*current)[name.c_str()]);
			}
			else
			{
				rapidjson::SizeType index = static_cast<rapidjson::SizeType>(std::get<size_t>(key));
				if (!current->IsArray())
					current->SetArray();
				while (current->Size() <= index)
					current->PushBack(rapidjson::Value(rapidjson::kObjectType), doc.GetAllocator());
				current = &((*current)[index]);
			}
		}

		rapidjson::Value copy;
		copy.CopyFrom(new_value, doc.GetAllocator());
		*current = std::move(copy);

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		std::ofstream output(file_path, std::ios::binary | std::ios::trunc);
		if (!output)
			return false;

		output.write(buffer.GetString(), buffer.GetSize());
		output.close();

		return true;
	}

	bool JsonFileIoManager::set_string(
		const std::string& file_path,
		const std::vector<std::variant<std::string, size_t>>& key_path,
		const std::string& value)
	{
		try
		{				
			std::ifstream input(file_path, std::ios::binary);
			if (!input)
				return false;

			std::string file_content((std::istreambuf_iterator<char>(input)),
				std::istreambuf_iterator<char>());
			input.close();

			rapidjson::Document doc;
			doc.Parse(file_content.c_str(), file_content.size());
			if (doc.HasParseError())
				return false;

			rapidjson::Value* current = &doc;
			for (const auto& key : key_path)
			{
				if (std::holds_alternative<std::string>(key))
				{
					const auto& name = std::get<std::string>(key);
					if (!current->IsObject())
						current->SetObject();
					if (!current->HasMember(name.c_str()))
					{
						rapidjson::Value key_val(name.c_str(), doc.GetAllocator());
						rapidjson::Value val(rapidjson::kObjectType);
						current->AddMember(std::move(key_val), std::move(val), doc.GetAllocator());
					}
					current = &((*current)[name.c_str()]);
				}
				else
				{
					rapidjson::SizeType index = static_cast<rapidjson::SizeType>(std::get<size_t>(key));
					if (!current->IsArray())
						current->SetArray();
					while (current->Size() <= index)
						current->PushBack(rapidjson::Value(rapidjson::kObjectType), doc.GetAllocator());
					current = &((*current)[index]);
				}
			}

			rapidjson::Value val;
			val.SetString(value.c_str(), doc.GetAllocator());
			*current = std::move(val);

			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			doc.Accept(writer);

			std::ofstream output(file_path, std::ios::binary | std::ios::trunc);
			if (!output)
				return false;

			output.write(buffer.GetString(), buffer.GetSize());
			output.close();

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

	bool JsonFileIoManager::append_string(
		const std::string& file_path,
		const std::vector<std::variant<std::string, size_t>>& key_path,
		const std::string& value)
	{
		try
		{			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				key_path.empty()
			);

			std::ifstream input(file_path, std::ios::binary);
			if (!input)
				return false;

			std::string file_content((std::istreambuf_iterator<char>(input)),
				std::istreambuf_iterator<char>());
			input.close();

			rapidjson::Document doc;
			if (file_content.empty())
				doc.SetObject();
			else
				doc.Parse(file_content.c_str(), file_content.size());
			if (doc.HasParseError())
				return false;

			rapidjson::Value* current = &doc;
			for (const auto& key : key_path)
			{
				if (std::holds_alternative<std::string>(key))
				{
					const auto& name = std::get<std::string>(key);
					if (!current->IsObject())
						current->SetObject();
					if (!current->HasMember(name.c_str()))
					{
						rapidjson::Value k(name.c_str(), doc.GetAllocator());
						rapidjson::Value v(rapidjson::kObjectType);
						current->AddMember(std::move(k), std::move(v), doc.GetAllocator());
					}
					current = &((*current)[name.c_str()]);
				}
				else
				{
					rapidjson::SizeType index = static_cast<rapidjson::SizeType>(std::get<size_t>(key));
					if (!current->IsArray())
						current->SetArray();
					while (current->Size() <= index)
						current->PushBack(rapidjson::Value(rapidjson::kObjectType), doc.GetAllocator());
					current = &((*current)[index]);
				}
			}

			rapidjson::Value string_value;
			string_value.SetString(value.c_str(), static_cast<rapidjson::SizeType>(value.length()), doc.GetAllocator());
			*current = std::move(string_value);

			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			doc.Accept(writer);

			std::ofstream output(file_path, std::ios::binary | std::ios::trunc);
			if (!output)
				return false;
			output.write(buffer.GetString(), buffer.GetSize());
			output.close();

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

	bool JsonFileIoManager::remove_value(
		const std::string& file_path,
		const std::vector<std::variant<std::string, size_t>>& key_path)
	{
		try
		{			
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_directory(file_path) ||
				key_path.empty()
			);

			std::ifstream input(file_path, std::ios::binary);
			if (!input)
				return false;

			std::string file_content((std::istreambuf_iterator<char>(input)),
				std::istreambuf_iterator<char>());
			input.close();

			rapidjson::Document doc;
			doc.Parse(file_content.c_str(), file_content.size());
			if (doc.HasParseError())
				return false;

			rapidjson::Value* current = &doc;
			for (size_t i = 0; i < key_path.size() - 1; ++i)
			{
				const auto& key = key_path[i];
				if (std::holds_alternative<std::string>(key))
				{
					const auto& name = std::get<std::string>(key);
					if (!current->IsObject() || !current->HasMember(name.c_str()))
						return false;
					current = &((*current)[name.c_str()]);
				}
				else
				{
					rapidjson::SizeType index = static_cast<rapidjson::SizeType>(std::get<size_t>(key));
					if (!current->IsArray() || index >= current->Size())
						return false;
					current = &((*current)[index]);
				}
			}

			const auto& last_key = key_path.back();
			if (std::holds_alternative<std::string>(last_key))
			{
				const auto& name = std::get<std::string>(last_key);
				if (!current->IsObject() || !current->HasMember(name.c_str()))
					return false;
				current->RemoveMember(name.c_str());
			}
			else
			{
				rapidjson::SizeType index = static_cast<rapidjson::SizeType>(std::get<size_t>(last_key));
				if (!current->IsArray() || index >= current->Size())
					return false;
				current->Erase(current->Begin() + index);
			}

			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			doc.Accept(writer);

			std::ofstream output(file_path, std::ios::binary | std::ios::trunc);
			if (!output)
				return false;
			output.write(buffer.GetString(), buffer.GetSize());
			output.close();

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

	bool
		JsonFileIoManager
			::is_valid()
	{
		return
			is_valid(
				configurations
					.file_path
			);
	}

	bool
		JsonFileIoManager
			::is_key_path_valid(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			is_key_path_valid(
				configurations
					.file_path,
				key_path
			);
	}

	std::string
		JsonFileIoManager
			::get_raw_json(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			get_raw_json(
				configurations
					.file_path,
				key_path
			);
	}

	std::string
		JsonFileIoManager
			::get_string(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			get_string(
				configurations
					.file_path,
				key_path
			);
	}

	double
		JsonFileIoManager
			::get_double(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			get_double(
				configurations
					.file_path,
				key_path
			);
	}

	bool
		JsonFileIoManager
			::get_boolean(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			get_boolean(
				configurations
					.file_path,
				key_path
			);
	}

	std::nullptr_t
		JsonFileIoManager
			::get_null(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			get_null(
				configurations
					.file_path,
				key_path
			);
	}

	bool
		JsonFileIoManager
			::set_raw_json(
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				const std::string&
					value
			)
	{
		return
			set_raw_json(
				configurations
					.file_path,
				key_path,
				value
			);
	}

	bool
		JsonFileIoManager
			::set_string(
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				const std::string&
					value
			)
	{
		return
			set_string(
				configurations
					.file_path,
				key_path,
				value
			);
	}

	bool
		JsonFileIoManager
			::append_raw_json(
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				const std::string&
					value
			)
	{
		return
			append_raw_json(
				configurations
					.file_path,
				key_path,
				value
			);
	}

	bool
		JsonFileIoManager
			::append_string(
				const std::vector<std::variant<std::string, size_t>>&
					key_path,
				const std::string&
					value
			)
	{
		return
			append_string(
				configurations
					.file_path,
				key_path,
				value
			);
	}

	bool
		JsonFileIoManager
			::remove_value(
				const std::vector<std::variant<std::string, size_t>>&
					key_path
			)
	{
		return
			remove_value(
				configurations
					.file_path,
				key_path
			);
	}
}

#endif
