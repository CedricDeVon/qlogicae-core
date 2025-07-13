#pragma once

#include "pch.h"

#include "xml_file_io.hpp"
#include "abstract_file_io.hpp" 

namespace QLogicaeCore
{
    XmlFileIO::~XmlFileIO()
    {
    }

    XmlFileIO::XmlFileIO(const std::string_view& file_path)
        : AbstractFileIO(file_path)
    {
    }

    XmlFileIO::XmlFileIO(const std::string_view& file_path,
        const std::string_view& name)
        : AbstractFileIO(name, file_path)
    {
    }

    bool XmlFileIO::load()
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        if (_file_path.empty())
        {
            return false;
        }

        if (!std::filesystem::exists(_file_path))
        {
            return false;
        }

        pugi::xml_parse_result parse_result =
            _xml_document.load_file(_file_path.c_str());

        return parse_result;
    }

    bool XmlFileIO::save()
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        if (_file_path.empty())
        {
            return false;
        }

        return _xml_document.save_file(_file_path.c_str());
    }

    bool XmlFileIO::clear()
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        try
        {
            _xml_document.reset();
            
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool XmlFileIO::save_as(const std::string_view& file_path)
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        if (file_path.empty())
        {
            return false;
        }

        return _xml_document.save_file(file_path.data());
    }

    std::future<bool> XmlFileIO::load_async()
    {
        return std::async(std::launch::async,
            [this]()
            {
                return load();
            });
    }

    std::future<bool> XmlFileIO::save_async()
    {
        return std::async(std::launch::async,
            [this]()
            {
                return save();
            });
    }

    std::future<bool> XmlFileIO::clear_async()
    {
        return std::async(std::launch::async,
            [this]()
            {
                return clear();
            });
    }

    std::future<bool> XmlFileIO::save_as_async(
        const std::string_view& file_path)
    {
        return std::async(std::launch::async,
            [this, file_path]()
            {
                return save_as(file_path);
            });
    }

    pugi::xml_node XmlFileIO::_navigate_to_path(
        const std::vector<std::string>& key_path,
        bool create_missing) const
    {
        pugi::xml_node current_node = _xml_document;

        for (const std::string& key : key_path)
        {
            pugi::xml_node next_node = current_node.child(key.c_str());

            if (!next_node && create_missing)
            {
                next_node = current_node.append_child(key.c_str());
            }

            if (!next_node)
            {
                return pugi::xml_node();
            }

            current_node = next_node;
        }

        return current_node;
    }

    bool XmlFileIO::remove_value(
        const std::vector<std::string>& key_path)
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        if (key_path.empty())
        {
            return false;
        }

        std::vector<std::string> parent_path(
            key_path.begin(), key_path.end() - 1);

        std::string last_key = key_path.back();

        pugi::xml_node parent_node =
            _navigate_to_path(parent_path, false);

        if (!parent_node)
        {
            return false;
        }

        return parent_node.remove_child(last_key.c_str());
    }

    std::future<bool> XmlFileIO::remove_value_async(
        const std::vector<std::string>& key_path)
    {
        return std::async(std::launch::async,
            [this, key_path]()
            {
                return remove_value(key_path);
            });
    }

    std::future<bool> XmlFileIO::remove_values_async(
        const std::vector<std::vector<std::string>>& keys)
    {
        return std::async(std::launch::async,
            [this, keys]()
            {
                return remove_values(keys);
            });
    }

    bool XmlFileIO::remove_values(
        const std::vector<std::vector<std::string>>& keys)
    {
        for (const std::vector<std::string>& key_path : keys)
        {
            if (!remove_value(key_path))
            {
                return false;
            }
        }

        return true;
    }

    bool XmlFileIO::has_key(
        const std::vector<std::string>& key_path) const
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        if (key_path.empty())
        {
            return false;
        }

        pugi::xml_node node =
            _navigate_to_path(key_path, false);

        return static_cast<bool>(node);
    }

    std::vector<std::string> XmlFileIO::get_children(
        const std::vector<std::string>& key_path) const
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        std::vector<std::string> result;

        pugi::xml_node parent_node =
            _navigate_to_path(key_path, false);

        if (!parent_node)
        {
            return result;
        }

        for (pugi::xml_node child = parent_node.first_child();
            child;
            child = child.next_sibling())
        {
            result.push_back(child.name());
        }

        return result;
    }

    std::string XmlFileIO::get_root_name() const
    {

        pugi::xml_node root_node = _xml_document.first_child();

        if (!root_node)
        {
            return "";
        }

        return root_node.name();
    }

    bool XmlFileIO::set_root(const std::string& tag_name)
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        _xml_document.reset();

        pugi::xml_node root = _xml_document.append_child(tag_name.c_str());

        return static_cast<bool>(root);
    }

    bool XmlFileIO::save_with_indent(std::size_t indent_spaces)
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        if (_file_path.empty())
        {
            return false;
        }

        std::ofstream output_stream(_file_path);
        if (!output_stream.is_open())
        {
            return false;
        }

        std::string indent_string(indent_spaces, ' ');

        _xml_document.save(
            output_stream,
            indent_string.c_str(),
            pugi::format_indent | pugi::format_default);

        return true;
    }

    std::future<bool> XmlFileIO::has_key_async(
        const std::vector<std::string>& key_path) const
    {
        return std::async(std::launch::async,
            [this, key_path]()
            {
                return has_key(key_path);
            });
    }

    std::future<std::vector<std::string>>
        XmlFileIO::get_children_async(
            const std::vector<std::string>& key_path) const
    {
        return std::async(std::launch::async,
            [this, key_path]()
            {
                return get_children(key_path);
            });
    }

    std::future<std::string> XmlFileIO::get_root_name_async() const
    {
        return std::async(std::launch::async,
            [this]()
            {
                return get_root_name();
            });
    }

    std::future<bool> XmlFileIO::save_with_indent_async(
        std::size_t indent_spaces)
    {
        return std::async(std::launch::async,
            [this, indent_spaces]()
            {
                return save_with_indent(indent_spaces);
            });
    }

    std::vector<std::string>
        XmlFileIO::select_node_texts(
            const std::string& xpath) const
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        std::vector<std::string> texts;

        pugi::xpath_node_set result =
            _xml_document.select_nodes(xpath.c_str());

        for (const pugi::xpath_node& match : result)
        {
            const char* text = match.node().text().as_string();
            if (text && text[0] != '\0')
            {
                texts.emplace_back(text);
            }
        }

        return texts;
    }

    std::optional<std::string>
        XmlFileIO::select_node_text(
            const std::string& xpath) const
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        pugi::xpath_node_set result =
            _xml_document.select_nodes(xpath.c_str());

        if (result.empty())
        {
            return std::nullopt;
        }

        const char* text = result.first().node().text().as_string();

        if (text == nullptr || text[0] == '\0')
        {
            return std::nullopt;
        }

        return std::string(text);
    }

    bool XmlFileIO::validate_against_schema(const std::string& xsd_path) const
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        if (_file_path.empty())
        {
            return false;
        }

        xmlDocPtr doc = xmlReadFile(_file_path.c_str(), nullptr, 0);
        if (doc == nullptr)
        {
            return false;
        }

        xmlSchemaParserCtxtPtr parser_ctxt =
            xmlSchemaNewParserCtxt(xsd_path.c_str());
        if (parser_ctxt == nullptr)
        {
            xmlFreeDoc(doc);
            return false;
        }

        xmlSchemaPtr schema = xmlSchemaParse(parser_ctxt);
        xmlSchemaFreeParserCtxt(parser_ctxt);

        if (schema == nullptr)
        {
            xmlFreeDoc(doc);
            return false;
        }

        xmlSchemaValidCtxtPtr valid_ctxt =
            xmlSchemaNewValidCtxt(schema);
        if (valid_ctxt == nullptr)
        {
            xmlSchemaFree(schema);
            xmlFreeDoc(doc);
            return false;
        }

        int result = xmlSchemaValidateDoc(valid_ctxt, doc);

        xmlSchemaFreeValidCtxt(valid_ctxt);
        xmlSchemaFree(schema);
        xmlFreeDoc(doc);

        return result == 0;
    }

    std::future<bool> XmlFileIO::validate_against_schema_async(
        const std::string& xsd_path) const
    {
        return std::async(std::launch::async,
            [this, xsd_path]()
            {
                return validate_against_schema(xsd_path);
            });
    }

    std::future<std::optional<std::string>>
        XmlFileIO::select_node_text_async(
            const std::string& xpath) const
    {
        return std::async(std::launch::async,
            [this, xpath]()
            {
                return select_node_text(xpath);
            });
    }

    std::future<std::vector<std::string>>
        XmlFileIO::select_node_texts_async(
            const std::string& xpath) const
    {
        return std::async(std::launch::async,
            [this, xpath]()
            {
                return select_node_texts(xpath);
            });
    }

    std::vector<std::string> XmlFileIO::select_attributes(
        const std::string& xpath,
        const std::string& attribute_name) const
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        std::vector<std::string> results;

        pugi::xpath_node_set nodes =
            _xml_document.select_nodes(xpath.c_str());

        for (const pugi::xpath_node& xnode : nodes)
        {
            pugi::xml_attribute attr =
                xnode.node().attribute(attribute_name.c_str());

            if (attr && attr.value()[0] != '\0')
            {
                results.emplace_back(attr.value());
            }
        }

        return results;
    }

    std::optional<std::string> XmlFileIO::select_attribute(
        const std::string& xpath,
        const std::string& attribute_name) const
    {
        std::scoped_lock<std::mutex> lock(_mutex);

        pugi::xpath_node_set nodes =
            _xml_document.select_nodes(xpath.c_str());

        if (nodes.empty())
        {
            return std::nullopt;
        }

        pugi::xml_attribute attr =
            nodes.first().node().attribute(attribute_name.c_str());

        if (!attr || attr.value()[0] == '\0')
        {
            return std::nullopt;
        }

        return std::string(attr.value());
    }

    std::future<bool> XmlFileIO::set_root_async(
        const std::string& tag_name)
    {
        return std::async(std::launch::async,
            [this, tag_name]()
            {
                return set_root(tag_name);
            });
    }
}
