#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		XmlFileIoManager \
	)

#include "xml_file_io_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		XmlFileIoManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<XmlFileIoManagerConfigurations>
    {
    public:		
		XmlFileIoManager();

		bool
			is_key_found(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path
			);

		std::vector<std::string>
			get_children(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path
			);

		std::string
			get_root_name(
				const std::string&
					file_path
			);

		bool
			set_root_name(
				const std::string&
					file_path,
				const std::string&
					tag_name
			);

		bool
			remove_attribute(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path,
				const std::string&
					attribute_name
			);

		bool
			remove_value(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path
			);

		std::string
			get_node_text(
				const std::string&
					file_path,
				const std::string&
					xpath
			);

		std::string
			get_attribute(
				const std::string&
					file_path,
				const std::string&
					xpath,
				const std::string&
					attribute_name
			);

		
		template<typename ValueType> ValueType
			get_attribute(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path,
				const std::string&
					attribute_name
			);

		template<typename ValueType> bool
			set_attribute(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path,
				const std::string&
					attribute_name,
				const ValueType&
					value
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

		template<typename ValueType> bool
			append_value(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path,
				const ValueType&
					value
			);




		bool
			is_key_found(
				const std::vector<std::string>&
					key_path
			);

		std::vector<std::string>
			get_children(
				const std::vector<std::string>&
					key_path
			);

		std::string
			get_root_name();

		bool
			set_root_name(
				const std::string&
					tag_name
			);

		bool
			remove_attribute(
				const std::vector<std::string>&
					key_path,
				const std::string&
					attribute_name
			);

		bool
			remove_value(
				const std::vector<std::string>&
					key_path
			);

		std::string
			get_node_text(
				const std::string&
					xpath
			);

		std::string
			get_attribute(
				const std::string&
					xpath,
				const std::string&
					attribute_name
			);

		template<typename ValueType> ValueType
			get_attribute(
				const std::vector<std::string>&
					key_path,
				const std::string&
					attribute_name
			);

		template<typename ValueType> bool
			set_attribute(
				const std::vector<std::string>&
					key_path,
				const std::string&
					attribute_name,
				const ValueType&
					value
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

		template<typename ValueType> bool
			append_value(
				const std::vector<std::string>&
					key_path,
				const ValueType&
					value
			);
    };

	template<typename ValueType> ValueType
		XmlFileIoManager
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
		
			pugi::xml_document doc;
			if (!doc.load_file(file_path.c_str()))
				return ValueType{};

			pugi::xml_node node = doc;
			for (const auto& key : key_path)
			{
				node = node.child(key.c_str());
				if (!node)
					return ValueType{};
			}

			const char* text = node.child_value();
			if constexpr (std::is_integral_v<ValueType>)
			{
				try { return static_cast<ValueType>(std::stoll(text)); }
				catch (...) { return ValueType{}; }
			}
			else if constexpr (std::is_floating_point_v<ValueType>)
			{
				try { return static_cast<ValueType>(std::stold(text)); }
				catch (...) { return ValueType{}; }
			}
			else if constexpr (std::is_same_v<ValueType, bool>)
			{
				std::string val = text ? text : "";
				if (val == "1" || val == "true") return true;
				if (val == "0" || val == "false") return false;
				return false;
			}
			else if constexpr (std::is_same_v<ValueType, std::string>)
				return std::string(text ? text : "");
			else
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

	template<typename ValueType> ValueType
		XmlFileIoManager
			::get_attribute(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path,
				const std::string&
					attribute_name
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
				std::filesystem::is_directory(file_path) ||
				!key_path.size() ||
				attribute_name.empty()
			);
		
			pugi::xml_document doc;
			if (!doc.load_file(file_path.c_str()))
				return ValueType{};

			pugi::xml_node node = doc;
			for (const auto& key : key_path)
			{
				node = node.child(key.c_str());
				if (!node)
					return ValueType{};
			}

			pugi::xml_attribute attr = node.attribute(attribute_name.c_str());
			if (!attr)
				return ValueType{};

			const char* text = attr.value();
			if constexpr (std::is_integral_v<ValueType>)
			{
				try { return static_cast<ValueType>(std::stoll(text)); }
				catch (...) { return ValueType{}; }
			}
			else if constexpr (std::is_floating_point_v<ValueType>)
			{
				try { return static_cast<ValueType>(std::stold(text)); }
				catch (...) { return ValueType{}; }
			}
			else if constexpr (std::is_same_v<ValueType, bool>)
			{
				std::string val = text ? text : "";
				if (val == "1" || val == "true") return true;
				if (val == "0" || val == "false") return false;
				return false;
			}
			else if constexpr (std::is_same_v<ValueType, std::string>)
				return std::string(text ? text : "");
			else
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
		XmlFileIoManager
			::set_attribute(
				const std::string&
					file_path,
				const std::vector<std::string>&
					key_path,
				const std::string&
					attribute_name,
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
				std::filesystem::is_directory(file_path) ||
				!key_path.size() ||
				attribute_name.empty()
			);
		
			pugi::xml_document doc;
			if (!doc.load_file(file_path.c_str()))
				return false;

			pugi::xml_node node = doc;
			for (const auto& key : key_path)
			{
				pugi::xml_node next = node.child(key.c_str());
				if (!next)
					next = node.append_child(key.c_str());
				node = next;
			}

			pugi::xml_attribute attr = node.attribute(attribute_name.c_str());
			if (!attr)
				attr = node.append_attribute(attribute_name.c_str());

			if constexpr (std::is_same_v<ValueType, std::string>)
				attr.set_value(value.c_str());
			else
				attr.set_value(std::to_string(value).c_str());

			return doc.save_file(file_path.c_str());
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	template<typename ValueType> bool
		XmlFileIoManager
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
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);
		
			pugi::xml_document doc;
			if (!doc.load_file(file_path.c_str()))
				return false;

			pugi::xml_node node = doc;
			for (const auto& key : key_path)
			{
				pugi::xml_node next = node.child(key.c_str());
				if (!next)
					next = node.append_child(key.c_str());
				node = next;
			}

			if constexpr (std::is_same_v<ValueType, std::string>)
				node.text().set(value.c_str());
			else
				node.text().set(std::to_string(value).c_str());

			return doc.save_file(file_path.c_str());
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	template<typename ValueType> bool
		XmlFileIoManager
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
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);
		
			pugi::xml_document doc;
			if (!doc.load_file(file_path.c_str()))
				return false;

			pugi::xml_node parent = doc;
			for (size_t i = 0; i < key_path.size() - 1; ++i)
			{
				pugi::xml_node next = parent.child(key_path[i].c_str());
				if (!next)
					next = parent.append_child(key_path[i].c_str());
				parent = next;
			}

			pugi::xml_node new_node = parent.append_child(key_path.back().c_str());
			if constexpr (std::is_same_v<ValueType, std::string>)
				new_node.text().set(value.c_str());
			else
				new_node.text().set(std::to_string(value).c_str());

			return doc.save_file(file_path.c_str());
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
		XmlFileIoManager
			::get_attribute(
				const std::vector<std::string>&
					key_path,
				const std::string&
					attribute_name
			)
	{
		return
			get_attribute(
				configurations
					.file_path,
				key_path,
				attribute_name
			);	
	}

	template<typename ValueType> bool
		XmlFileIoManager
			::set_attribute(
				const std::vector<std::string>&
					key_path,
				const std::string&
					attribute_name,
				const ValueType&
					value
			)
	{
		return
			set_attribute(
				configurations
					.file_path,
				key_path,
				attribute_name,
				value
			);	
	}

	template<typename ValueType> ValueType
		XmlFileIoManager
			::get_value(
				const std::vector<std::string>&
					key_path
			)
	{
		return
			get_value(
				configurations
					.file_path,
				key_path
			);	
	}

	template<typename ValueType> bool
		XmlFileIoManager
			::set_value(
				const std::vector<std::string>&
					key_path,
				const ValueType&
					value
			)
	{
		return
			set_value(
				configurations
					.file_path,
				key_path,
				value
			);	
	}

	template<typename ValueType> bool
		XmlFileIoManager
			::append_value(
				const std::vector<std::string>&
					key_path,
				const ValueType&
					value
			)
	{
		return
			append_value(
				configurations
					.file_path,
				key_path,
				value
			);	
	}
}

#endif
