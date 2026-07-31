#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		JsonTextManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
    struct JsonValidationParameter
    {
    public:
        std::string json_text;
        bool expected_result;
    };

    struct JsonKeyPathParameter
    {
    public:
        std::string json_text;
        std::vector<std::variant<std::string,size_t>> key_path;
        bool expected_result;
    };

    struct JsonStringExtractionParameter
    {
    public:
        std::string json_text;
        std::vector<std::variant<std::string,size_t>> key_path;
        std::string expected_result;
    };

    struct JsonDoubleExtractionParameter
    {
    public:
        std::string json_text;
        std::vector<std::variant<std::string,size_t>> key_path;
        double expected_result;
    };

    struct JsonBooleanExtractionParameter
    {
    public:
        std::string json_text;
        std::vector<std::variant<std::string,size_t>> key_path;
        bool expected_result;
    };

    class JsonTextManagerTest:
        public ::testing::Test
    {
    public:
        JsonTextManagerTest()
        {
        }

        JsonTextManager manager;
    };

    class JsonTextManagerValidationParameterizedTest:
        public JsonTextManagerTest,
        public ::testing::WithParamInterface<JsonValidationParameter>
    {
    };

    class JsonTextManagerKeyPathParameterizedTest:
        public JsonTextManagerTest,
        public ::testing::WithParamInterface<JsonKeyPathParameter>
    {
    };

    class JsonTextManagerStringExtractionParameterizedTest:
        public JsonTextManagerTest,
        public ::testing::WithParamInterface<JsonStringExtractionParameter>
    {
    };

    class JsonTextManagerDoubleExtractionParameterizedTest:
        public JsonTextManagerTest,
        public ::testing::WithParamInterface<JsonDoubleExtractionParameter>
    {
    };

    class JsonTextManagerBooleanExtractionParameterizedTest:
        public JsonTextManagerTest,
        public ::testing::WithParamInterface<JsonBooleanExtractionParameter>
    {
    };
}

#endif
