#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TomlFileIoManager \
	)

#include "toml_file_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TomlFileIoManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TomlFileIoManagerConfigurations>
    {
    public:		
		TomlFileIoManager();

		bool
			is_key_found(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path
			);

		template<typename ValueType> ValueType
			get_value(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path
			);

		template<typename ValueType> bool
			set_value(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path,
				const ValueType&
					value
			);

		bool
			remove_value(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path
			);

		bool
			is_key_found(
				const std::vector<std::string>&
					key_path
			);

		template<typename ValueType> ValueType
			get_value(
				const std::vector<std::string>&
					key_path
			);

		template<typename ValueType> bool
			set_value(
				const std::vector<std::string>&
					key_path,
				const ValueType&
					value
			);

		bool
			remove_value(
				const std::vector<std::string>&
					key_path
			);

		bool
			save_toml_table(
				const std::string&
					file_path,
				const toml::table&
					doc
			);
    };

	template<typename ValueType> ValueType
		TomlFileIoManager
			::get_value(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path
			)
	{
		try
        {			
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				ValueType {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				std::filesystem::is_empty(file_path) ||
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);

			toml::table doc;
			try { doc = toml::parse_file(file_path); }
			catch (...) { return ValueType{}; }

			toml::node* node = &doc;
			for (const auto& key : key_path)
			{
				auto tbl = node->as_table();
				if (!tbl) return ValueType{};
				node = tbl->get(key);
				if (!node) return ValueType{};
			}

			if constexpr (std::is_same_v<ValueType, std::string>)
			{
				if (auto val = node->value<std::string>()) return *val;
			}
			else if constexpr (std::is_same_v<ValueType, std::vector<double>>)
			{
				if (auto arr = node->as_array())
				{
					std::vector<double> vec;
					for (const auto& item : *arr)
					{
						if (auto v = item.value<double>()) vec.push_back(*v);
					}
					return vec;
				}
			}
			else if constexpr (std::is_same_v<ValueType, std::vector<std::string>>)
			{
				if (auto arr = node->as_array())
				{
					std::vector<std::string> vec;
					for (const auto& item : *arr)
					{
						if (auto v = item.value<std::string>()) vec.push_back(*v);
					}
					return vec;
				}
			}
			else if constexpr (std::is_integral_v<ValueType>)
			{
				if (auto val = node->value<int64_t>()) return static_cast<ValueType>(*val);
			}
			else if constexpr (std::is_floating_point_v<ValueType>)
			{
				if (auto val = node->value<double>()) return static_cast<ValueType>(*val);
			}
			
			else if constexpr (std::is_same_v<ValueType, std::vector<int>>)
			{
				if (auto arr = node->as_array())
				{
					std::vector<int> vec;
					for (const auto& item : *arr)
					{
						if (auto v = item.value<int64_t>()) vec.push_back(static_cast<int>(*v));
					}
					return vec;
				}
			}

			return ValueType{};
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				ValueType {}
			);
        }
	}

	template<typename ValueType> bool
		TomlFileIoManager
			::set_value(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path,
				const ValueType&
					value
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
			for (size_t i = 0; i < key_path.size(); ++i)
			{
				const auto& key = key_path[i];
				auto tbl = node->as_table();
				if (!tbl) return false;

				if (i + 1 == key_path.size())
				{
					if constexpr (std::is_same_v<ValueType, std::string>) tbl->insert_or_assign(key, value);
					else if constexpr (std::is_integral_v<ValueType>) tbl->insert_or_assign(key, static_cast<int64_t>(value));
					else if constexpr (std::is_floating_point_v<ValueType>) tbl->insert_or_assign(key, static_cast<double>(value));
					else if constexpr (std::is_same_v<ValueType, std::vector<int>>)
					{
						toml::array arr;
						for (auto v : value) arr.push_back(static_cast<int64_t>(v));
						tbl->insert_or_assign(key, arr);
					}
					else if constexpr (std::is_same_v<ValueType, std::vector<double>>)
					{
						toml::array arr;
						for (auto v : value) arr.push_back(static_cast<double>(v));
						tbl->insert_or_assign(key, arr);
					}
					else if constexpr (std::is_same_v<ValueType, std::vector<std::string>>)
					{
						toml::array arr;
						for (const auto& v : value) arr.push_back(v);
						tbl->insert_or_assign(key, arr);
					}
					else return false;
				}
				else
				{
					if (!tbl->contains(key)) tbl->insert_or_assign(key, toml::table{});
					node = tbl->get(key);
					if (!node) return false;
				}
			}

			return save_toml_table(file_path, doc);
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	template<typename ValueType> ValueType
		TomlFileIoManager
			::get_value(
				const std::vector<std::string>&
					key_path
			)
	{
		return
			get_value<ValueType>(
				configurations
					.file_path,
				key_path
			);	
	}

	template<typename ValueType> bool
		TomlFileIoManager
			::set_value(
				const std::vector<std::string>&
					key_path,
				const ValueType&
					value
			)
	{
		return
			set_value<ValueType>(
				configurations
					.file_path,
				key_path,
				value
			);	
	}
}

#endif


/*		
	template<typename ValueType> bool
		append_value(
			const std::string&
				file_path,
			const std::vector<std::string>&
				key_path,
			const ValueType&
				value
		);

	template<typename ValueType> bool
		TomlFileIoManager
			::append_value(
				const std::vector<std::string>&
					key_path,
				const ValueType&
					value
			)
	{
		return
			append_value<ValueType>(
				configurations
					.file_path,
				key_path,
				value
			);	
	}
		
		template<typename ValueType> bool
			append_value(
				const std::vector<std::string>&
					key_path,
				const ValueType&
					value
			);


	template<typename ValueType> bool
		TomlFileIoManager
			::append_value(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path,
				const ValueType&
					value
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				file_path.empty() ||
				!std::filesystem::exists(file_path) ||
				!key_path.size()
			);

			toml::table doc;
			doc = toml::parse_file(file_path);

			toml::node* node = &doc;

			for(size_t i = 0; i < key_path.size(); ++i)
			{
				const auto& key = key_path[i];
				auto tbl = node->as_table();
				if(!tbl) return false;

				if(i + 1 == key_path.size())
				{
					if(!tbl->contains(key))
					{
						tbl->insert_or_assign(key,toml::array{});
					}

					auto child = tbl->get(key);
					if(!child) return false;

					auto arr = child->as_array();
					if(!arr) return false;

					if constexpr(std::is_same_v<ValueType,int>)
					{
						arr->push_back(static_cast<int64_t>(value));
					} else if constexpr(std::is_same_v<ValueType,double>)
					{
						arr->push_back(static_cast<double>(value));
					} else if constexpr(std::is_same_v<ValueType,std::string>)
					{
						arr->push_back(value);
					} else
					{
						return false;
					}
				} else
				{
					if(!tbl->contains(key))
					{
						return false;
					}

					node = tbl->get(key);
					if(!node || !node->is_table())
					{
						return false;
					}
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


*/