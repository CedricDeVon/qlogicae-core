#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ConsoleLogManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class ConsoleLogManagerTest:
		public ::testing::Test
	{
	public:
		ConsoleLogManagerTest()
		{
		}

		ConsoleLogManager manager;

		void SetUp() override
		{
			ConsoleLogManagerConfigurations configurations;
			configurations.is_feature_runtime_execution_handling_enabled =
				true;
			configurations.is_feature_edge_case_handling_enabled =
				true;
			configurations.is_feature_thread_safety_handling_enabled =
				false;
			configurations.text = "default";
			configurations.log_level = LogLevel::INFO;
			manager.setup(configurations);
		}
	};

	class ConsoleLogManagerParameterizedTest:
		public ConsoleLogManagerTest,
		public ::testing::WithParamInterface<std::string>
	{
	public:
		ConsoleLogManagerParameterizedTest()
		{
		}
	};

	class ConsoleLogManagerLogLevelParameterizedTest:
		public ConsoleLogManagerTest,
		public ::testing::WithParamInterface<LogLevel>
	{
	};
}

#endif
