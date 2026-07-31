#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		XmlFileIoManager \
	)

#include "../includes/xml_file_io_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{        	
	XmlFileIoManager
		::XmlFileIoManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<XmlFileIoManagerConfigurations>()
    {
        
    }

	bool
		XmlFileIoManager
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
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);
		
			pugi::xml_document doc;
			if (!doc.load_file(file_path.c_str()))
				return false;

			pugi::xml_node node = doc;
			for (const auto& key : key_path)
			{
				node = node.child(key.c_str());
				if (!node)
					return false;
			}

			return
				true;
        }
        catch
        (
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
            QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
        }
	}

	std::vector<std::string>
		XmlFileIoManager
			::get_children(
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
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);
		
			pugi::xml_document doc;
			if (!doc.load_file(file_path.c_str()))
				return {};

			pugi::xml_node node = doc;
			for (const auto& key : key_path)
			{
				node = node.child(key.c_str());
				if (!node)
					return {};
			}

			std::vector<std::string> children;
			for (pugi::xml_node child : node.children())
				children.push_back(child.name());

			return children;
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
		XmlFileIoManager
			::get_root_name(
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
		
			pugi::xml_document doc;
			if (!doc.load_file(file_path.c_str()))
				return "";

			return doc.first_child().name();
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
		XmlFileIoManager
			::set_root_name(
				const std::string&
					file_path,
				const std::string&
					tag_name
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
				tag_name.empty()
			);
		
			pugi::xml_document doc;
			if (!doc.load_file(file_path.c_str()))
				return false;

			pugi::xml_node root = doc.first_child();
			if (!root)
				return false;

			root.set_name(tag_name.c_str());

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

	bool
		XmlFileIoManager
			::remove_attribute(
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
				node = node.child(key.c_str());
				if (!node)
					return false;
			}

			if (!node.remove_attribute(attribute_name.c_str()))
				return false;

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

	bool
		XmlFileIoManager
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
				std::filesystem::is_directory(file_path) ||
				!key_path.size()
			);
		
			pugi::xml_document doc;
			if (!doc.load_file(file_path.c_str()))
				return false;

			pugi::xml_node parent = doc;
			for (size_t i = 0; i < key_path.size() - 1; ++i)
			{
				parent = parent.child(key_path[i].c_str());
				if (!parent)
					return false;
			}

			bool result = parent.remove_child(key_path.back().c_str());
			if (!result)
				return false;

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

	std::string
		XmlFileIoManager
			::get_node_text(
				const std::string&
					file_path,
				const std::string&
					xpath
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
				xpath.empty()
			);
		
			pugi::xml_document doc;
			if (!doc.load_file(file_path.c_str()))
				return "";

			pugi::xml_node node = doc.select_node(xpath.c_str()).node();
			if (!node)
				return "";

			return node.child_value();
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
		XmlFileIoManager
			::get_attribute(
				const std::string&
					file_path,
				const std::string&
					xpath,
				const std::string&
					attribute_name
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
				xpath.empty() ||
				attribute_name.empty()
			);
		
			pugi::xml_document doc;
			if (!doc.load_file(file_path.c_str()))
				return "";

			pugi::xml_node node = doc.select_node(xpath.c_str()).node();
			if (!node)
				return "";

			pugi::xml_attribute attr = node.attribute(attribute_name.c_str());
			if (!attr)
				return "";

			return attr.value();
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
		XmlFileIoManager
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

	std::vector<std::string>
		XmlFileIoManager
			::get_children(
				const std::vector<std::string>&
					key_path
			)
	{
		return
			get_children(
				configurations
					.file_path,
				key_path
			);
	}

	std::string
		XmlFileIoManager
			::get_root_name()
	{
		return
			get_root_name(
				configurations
					.file_path
			);
	}

	bool
		XmlFileIoManager
			::set_root_name(
				const std::string&
					tag_name
			)
	{
		return
			set_root_name(
				configurations
					.file_path,
				tag_name
			);
	}

	bool
		XmlFileIoManager
			::remove_attribute(
				const std::vector<std::string>&
					key_path,
				const std::string&
					attribute_name
			)
	{
		return
			remove_attribute(
				configurations
					.file_path,
				key_path,
				attribute_name
			);
	}

	bool
		XmlFileIoManager
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

	std::string
		XmlFileIoManager
			::get_node_text(
				const std::string&
					xpath
			)
	{
		return
			get_node_text(
				configurations
					.file_path,
				xpath
			);
	}

	std::string
		XmlFileIoManager
			::get_attribute(
				const std::string&
					xpath,
				const std::string&
					attribute_name
			)
	{
		return
			get_attribute(
				configurations
					.file_path,
				xpath,
				attribute_name
			);
	}
}

#endif
