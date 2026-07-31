#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TomlFileIoManager \
	)

#include "../includes/toml_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	TomlFileIoManager
		::TomlFileIoManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TomlFileIoManagerConfigurations>()
    {
        
    }
	
	std::unordered_map<std::string, std::any>
		TomlFileIoManager
			::execute_batch_operations(
				const std::unordered_map<std::string, TomlFileIoBatchOperationConfigurations>&
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

	bool
		TomlFileIoManager
			::is_key_found(
				const std::string&
					file_path,
				const std::vector<std::string>&
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
				std::filesystem::is_empty(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);

			toml::table doc;
			try { doc = toml::parse_file(file_path); }
			catch (...) { return false; }

			toml::node* node = &doc;
			for (const auto& key : key_path)
			{
				if (auto tbl = node->as_table())
				{
					node = tbl->get(key);
					if (!node)
						return false;
				}
				else
					return false;
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

	bool
		TomlFileIoManager
			::remove_value(
				const std::string&
					file_path,
				const std::vector<std::string>&
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
				std::filesystem::is_empty(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);

			toml::table doc;
			try { doc = toml::parse_file(file_path); }
			catch (...) { return false; }

			toml::node* node = &doc;
			for (size_t i = 0; i < key_path.size() - 1; ++i)
			{
				if (auto tbl = node->as_table())
				{
					node = tbl->get(key_path[i]);
					if (!node)
						return false;
				}
				else
					return false;
			}

			if (auto tbl = node->as_table())
			{
				if (!tbl->contains(key_path.back()))
					return false;

				tbl->erase(key_path.back());
				return save_toml_table(file_path, doc);
			}

            return
				false;
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
		TomlFileIoManager
			::save_toml_table(
				const std::string&
					file_path,
				const toml::table&
					doc
			)
	{
		std::ofstream ofs(file_path, std::ios::trunc);
		if (!ofs) return false;
		ofs << doc;

		return true;
	}

	bool
		TomlFileIoManager
			::is_key_found(
				const std::vector<std::string>&
					key_path
			)
	{
		return
			is_key_found(
				configurations
					.file_path,
				key_path
			);
	}

	bool
		TomlFileIoManager
			::remove_value(
				const std::vector<std::string>&
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
