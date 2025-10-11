#include "pch.h"

#include "qlogicae_core/xml_file_io.hpp"

namespace QLogicaeCoreTest
{
    class XmlFileIOTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            std::ofstream file("test.xml");
            file << "<root>"
                << "<item id=\"1\">Alpha</item>"
                << "<item id=\"2\">Beta</item>"
                << "</root>";
        }

        void TearDown() override
        {
            std::remove("test.xml");
            std::remove("copy.xml");
        }
    };

    class XmlFileIOParamTest : public ::testing::TestWithParam<std::string> {
    protected:
        void SetUp() override {
            std::ofstream file("test.xml");
            file << "<root><item id=\"1\">123</item><item id=\"2\">456</item></root>";
        }
        void TearDown() override {
            std::remove("test.xml");
        }
    };

    TEST_F(XmlFileIOTest, Should_Extract_Node_Text_With_XPath)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        auto text = xml.select_node_text("/root/item");
        ASSERT_TRUE(text.has_value());
        ASSERT_EQ(text.value(), "Alpha");

        auto all = xml.select_node_texts("/root/item");
        ASSERT_EQ(all.size(), 2);
        ASSERT_EQ(all[1], "Beta");
    }

    TEST_F(XmlFileIOTest, Should_Extract_Attributes_With_XPath)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        auto id = xml.select_attribute("/root/item", "id");
        ASSERT_TRUE(id.has_value());
        ASSERT_EQ(id.value(), "1");

        auto ids = xml.select_attributes("/root/item", "id");
        ASSERT_EQ(ids.size(), 2);
        ASSERT_EQ(ids[1], "2");
    }

    TEST_F(XmlFileIOTest, Should_Return_Empty_Optional_On_Missing_Attribute)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        auto attr = xml.select_attribute("/root/item", "missing");
        ASSERT_FALSE(attr.has_value());
    }

    TEST_F(XmlFileIOTest, Should_GetRootName_Correctly)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        ASSERT_EQ(xml.get_root_name(), "root");
    }

    TEST_F(XmlFileIOTest, Should_SetRootName_And_Persist)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.set_root("newroot"));
        ASSERT_TRUE(xml.save());

        ASSERT_TRUE(xml.load());
        ASSERT_EQ(xml.get_root_name(), "newroot");
    }

    TEST_F(XmlFileIOTest, Should_Save_With_Indentation)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        ASSERT_TRUE(xml.save_with_indent(4));
    }

    TEST_F(XmlFileIOTest, Should_Validate_Against_XSD_Schema)
    {
        std::ofstream xsd("schema.xsd");
        xsd << R"(<?xml version="1.0"?>
        <xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">
            <xs:element name="root">
                <xs:complexType>
                    <xs:sequence>
                        <xs:element name="item" maxOccurs="unbounded">
                            <xs:complexType>
                                <xs:simpleContent>
                                    <xs:extension base="xs:string">
                                        <xs:attribute name="id" type="xs:int"/>
                                    </xs:extension>
                                </xs:simpleContent>
                            </xs:complexType>
                        </xs:element>
                    </xs:sequence>
                </xs:complexType>
            </xs:element>
        </xs:schema>)";
        xsd.close();

        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        ASSERT_TRUE(xml.validate_against_schema("schema.xsd"));

        std::remove("schema.xsd");
    }

    TEST_F(XmlFileIOTest, Should_AsyncXPathAttribute_Match_Sync)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        auto async_result = xml.select_node_text_async("/root/item");
        ASSERT_EQ(async_result.get().value_or(""), "Alpha");
    }

    TEST_F(XmlFileIOTest, Should_AsyncValidate_Within_TwoSeconds)
    {
        std::ofstream xsd("schema.xsd");
        xsd << R"(<?xml version="1.0"?>
        <xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">
            <xs:element name="root">
                <xs:complexType>
                    <xs:sequence>
                        <xs:element name="item" maxOccurs="unbounded">
                            <xs:complexType>
                                <xs:simpleContent>
                                    <xs:extension base="xs:string">
                                        <xs:attribute name="id" type="xs:int"/>
                                    </xs:extension>
                                </xs:simpleContent>
                            </xs:complexType>
                        </xs:element>
                    </xs:sequence>
                </xs:complexType>
            </xs:element>
        </xs:schema>)";
        xsd.close();

        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        auto result = xml.validate_against_schema_async("schema.xsd");
        ASSERT_TRUE(result.wait_for(std::chrono::seconds(2)) == std::future_status::ready);
        ASSERT_TRUE(result.get());

        std::remove("schema.xsd");
    }

    TEST_F(XmlFileIOTest, Should_Clear_Synchronously)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());
        ASSERT_TRUE(xml.clear());
        ASSERT_TRUE(xml.save());
        ASSERT_TRUE(xml.get_root_name().empty());
    }

    TEST_F(XmlFileIOTest, Should_Clear_Asynchronously)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());
        auto future = xml.clear_async();
        ASSERT_TRUE(future.get());
        xml.save();
        xml.load();
        ASSERT_TRUE(xml.get_root_name().empty());
    }

    TEST_F(XmlFileIOTest, Should_SaveAs_To_NewFile)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());
        ASSERT_TRUE(xml.save_as("copy.xml"));
        std::ifstream copy("copy.xml");
        ASSERT_TRUE(copy.is_open());
        std::string content((std::istreambuf_iterator<char>(copy)),
            std::istreambuf_iterator<char>());
        ASSERT_NE(content.find("item"), std::string::npos);
    }

    TEST_F(XmlFileIOTest, Should_Get_All_Item_Values)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());
        auto values = xml.get_all_values<std::string>({ "root", "item" });
        ASSERT_EQ(values.size(), 2);
        ASSERT_EQ(values[0], "Alpha");
        ASSERT_EQ(values[1], "Beta");
    }

    TEST_F(XmlFileIOTest, Should_Set_Multiple_Values)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        xml.clear();
        xml.set_root("root");

        std::unordered_map<std::vector<std::string>, std::string,
            QLogicaeCore::VectorStringHash, std::equal_to<std::vector<std::string>>> entries = {
                {{"root", "user", "name"}, "Alice"},
                {{"root", "user", "email"}, "alice@example.com"}
        };

        ASSERT_TRUE(xml.set_values(entries));
        ASSERT_TRUE(xml.save());
        ASSERT_TRUE(xml.load());

        auto name = xml.get_value<std::string>({ "root", "user", "name" });
        auto email = xml.get_value<std::string>({ "root", "user", "email" });
        ASSERT_TRUE(name.has_value());
        ASSERT_TRUE(email.has_value());
        ASSERT_EQ(name.value(), "Alice");
        ASSERT_EQ(email.value(), "alice@example.com");
    }

    TEST_F(XmlFileIOTest, Should_ReturnFalse_When_HasKey_Missing)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());
        ASSERT_FALSE(xml.has_key({ "root", "not_found" }));
    }

    TEST_F(XmlFileIOTest, Should_Get_All_Child_Node_Names)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());
        auto children = xml.get_children({ "root" });
        ASSERT_EQ(children.size(), 2);
        ASSERT_EQ(children[0], "item");
        ASSERT_EQ(children[1], "item");
    }

    TEST_F(XmlFileIOTest, Should_Fail_SetAttribute_On_MissingNode)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());
        bool result = xml.set_attribute({ "root", "not_exist" }, "attr", "value");
        ASSERT_FALSE(result);
    }

    TEST_F(XmlFileIOTest, Should_ReturnFalse_When_Loading_InvalidFile)
    {
        QLogicaeCore::XmlFileIO xml("nonexistent.xml");
        ASSERT_FALSE(xml.load());
    }

    TEST_F(XmlFileIOTest, Should_Handle_Malformed_XML_Gracefully)
    {
        std::ofstream file("malformed.xml");
        file << "<root><item></root>";
        file.close();

        QLogicaeCore::XmlFileIO xml("malformed.xml");
        ASSERT_FALSE(xml.load());

        std::remove("malformed.xml");
    }

    TEST_F(XmlFileIOTest, Should_ReturnFalse_When_Validating_Invalid_XSD)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());
        ASSERT_FALSE(xml.validate_against_schema("invalid.xsd"));
    }

    TEST_P(XmlFileIOParamTest, Should_Convert_Text_To_TypedValue)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        if (GetParam() == "int")
        {
            auto values = xml.get_all_values<int>({ "root", "item" });
            ASSERT_EQ(values[0], 123);
        }
        else if (GetParam() == "string")
        {
            auto values = xml.get_all_values<std::string>({ "root", "item" });
            ASSERT_EQ(values[1], "456");
        }
    }

    INSTANTIATE_TEST_CASE_P(TypeVariants, XmlFileIOParamTest,
        ::testing::Values("int", "string"));

    TEST_F(XmlFileIOTest, Should_Handle_Concurrent_Async_Access)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        xml.set_root("root");

        std::vector<std::thread> threads;

        for (int i = 0; i < 1000; ++i)
        {
            threads.emplace_back([&xml, i]()
                {
                    std::string key = "key" + std::to_string(i);
                    xml.set_value({ "root", key }, "value");
                    auto result = xml.get_value<std::string>({ "root", key });
                    ASSERT_EQ(result.value_or(""), "value");
                });
        }

        for (auto& t : threads)
        {
            t.join();
        }
    }

    TEST_F(XmlFileIOTest, Should_SetAttributeAsync_And_GetAttributeAsync)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        xml.set_root("root");

        ASSERT_TRUE(xml.set_attribute_async<std::string>(
            { "root" }, "attr", "val").get());

        auto val = xml.get_attribute_async<std::string>({ "root" }, "attr").get();
        ASSERT_TRUE(val.has_value());
        ASSERT_EQ(val.value(), "val");
    }

    TEST_F(XmlFileIOTest, Should_GetChildrenAsync_Match_Sync)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        auto sync = xml.get_children({ "root" });
        auto async = xml.get_children_async({ "root" }).get();
        ASSERT_EQ(sync, async);
    }

    TEST_F(XmlFileIOTest, Should_Reject_Empty_KeyPath)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        ASSERT_FALSE(xml.set_value({}, "val"));
        ASSERT_EQ(xml.get_value<std::string>({}), std::nullopt);
        ASSERT_FALSE(xml.remove_value({}));
    }

    TEST_F(XmlFileIOTest, Should_Reject_Extremely_Long_Tags)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        std::string long_tag(10000, 'a');

        ASSERT_FALSE(xml.set_value({ long_tag }, "value"));
    }

    TEST_F(XmlFileIOTest, Should_Fail_GetAttributeAsync_When_PathMissing)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        auto result = xml.get_attribute_async<std::string>(
            { "root", "missing" }, "id").get();

        ASSERT_FALSE(result.has_value());
    }

    TEST_F(XmlFileIOTest, Should_AppendValue_Synchronously)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());
        ASSERT_TRUE(xml.append_value<std::string>(
            { "root", "item" }, "Gamma"));

        auto values = xml.get_all_values<std::string>({ "root", "item" });
        ASSERT_EQ(values.size(), 3);
        ASSERT_EQ(values[2], "Gamma");
    }

    TEST_F(XmlFileIOTest, Should_AppendValue_Asynchronously)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        ASSERT_TRUE(xml.load());

        ASSERT_TRUE(xml.append_value_async<std::string>(
            { "root", "item" }, "Delta").get());

        auto values = xml.get_all_values<std::string>({ "root", "item" });
        ASSERT_EQ(values.back(), "Delta");
    }

    TEST_F(XmlFileIOTest, Should_SetValuesAsync_Correctly)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        xml.clear();
        xml.set_root("root");

        std::unordered_map<std::vector<std::string>, std::string,
            QLogicaeCore::VectorStringHash, std::equal_to<std::vector<std::string>>> batch = {
                {{"root", "async1"}, "one"},
                {{"root", "async2"}, "two"},
        };

        ASSERT_TRUE(xml.set_values_async(batch).get());

        ASSERT_EQ(xml.get_value<std::string>({ "root", "async1" }).value_or(""), "one");
        ASSERT_EQ(xml.get_value<std::string>({ "root", "async2" }).value_or(""), "two");
    }

    TEST_F(XmlFileIOTest, Should_RemoveMultipleKeysAsync)
    {
        QLogicaeCore::XmlFileIO xml("test.xml");
        xml.set_root("root");

        xml.set_value({ "root", "k1" }, "v1");
        xml.set_value({ "root", "k2" }, "v2");
        xml.set_value({ "root", "k3" }, "v3");

        std::vector<std::vector<std::string>> keys = {
            { "root", "k1" },
            { "root", "k3" }
        };

        ASSERT_TRUE(xml.remove_values_async(keys).get());

        ASSERT_FALSE(xml.get_value<std::string>({ "root", "k1" }).has_value());
        ASSERT_TRUE(xml.get_value<std::string>({ "root", "k2" }).has_value());
        ASSERT_FALSE(xml.get_value<std::string>({ "root", "k3" }).has_value());
    }
}

