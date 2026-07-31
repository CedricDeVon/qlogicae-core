#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextKeyPathManager\
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		TextKeyPathManagerConfigurationOverrideTest:
		public ::testing::Test
	{
	public:
		TextKeyPathManager
			manager;

		std::vector<std::string>
			sample_key_path_vector = {"root","child","leaf"};

		std::string
			sample_key_path_string = "root.child.leaf";

		std::string
			sample_delimiter = ".";

		TextKeyPathManagerConfigurationOverrideTest() = default;
	};

	class
		TextKeyPathManagerTest:
		public ::testing::Test
	{
	public:
		TextKeyPathManager
			manager;

		std::vector<std::string>
			sample_key_path_vector = {"root","child","leaf"};

		std::string
			sample_key_path_string = "root.child.leaf";

		std::string
			sample_delimiter = ".";

		TextKeyPathManagerTest() = default;
	};

	class
		TextKeyPathManagerParameterizedTest:
		public TextKeyPathManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,std::string>>
	{
	};
}

#endif
