#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ConfigurationManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	struct
		ConfigurationManagerConfigurationsTest:
		AbstractConfigurations<ConfigurationManagerConfigurationsTest>
	{
	public:
		ConfigurationManagerConfigurationsTest();

		static ConfigurationManagerConfigurationsTest
			default_configurations;

		static ConfigurationManagerConfigurationsTest
			initial_configurations;
	};

	ConfigurationManagerConfigurationsTest
	::ConfigurationManagerConfigurationsTest():
		AbstractConfigurations<ConfigurationManagerConfigurationsTest>()
	{

	}

	ConfigurationManagerConfigurationsTest
	ConfigurationManagerConfigurationsTest
	::default_configurations;

	ConfigurationManagerConfigurationsTest
	ConfigurationManagerConfigurationsTest
	::initial_configurations;

	class ConfigurationManagerTest: public ::testing::Test
	{
	public:
		ConfigurationManager manager;

		void
			SetUp() override
		{
			manager.construct();
			manager.reset();
		}

		void
			TearDown() override
		{
			manager.destruct();
			manager.reset();
		}
	};

	class ConfigurationManagerParameterizedTest:
		public ConfigurationManagerTest,
		public ::testing::WithParamInterface<std::tuple<bool,bool>>
	{
	};

	class ThrowingConfigurationManager: public ConfigurationManager
	{
	public:
		template <typename TypeConfigurations> bool setup_defaults(const TypeConfigurations&)
		{
			throw std::runtime_error("setup_defaults fail");
		}

		template <typename TypeConfigurations> bool reset_defaults()
		{
			throw std::runtime_error("reset_defaults fail");
		}
	};

	class ConfigurationManagerAllFlagsParameterizedTest:
		public ConfigurationManagerTest,
		public ::testing::WithParamInterface<ConfigurationManagerConfigurations>
	{
	};

	class ConfigurationManagerExceptionTest: public ::testing::Test
	{
	public:
		ConfigurationManager manager;

		void
			SetUp()
		{
			manager.construct();
			manager.reset();
		}

		void
			TearDown()
		{
			manager.destruct();
			manager.reset();
		}
	};

	struct ThrowingDefaults: ConfigurationManager
	{
		template <typename T>
		bool setup_defaults(const T&)
		{
			throw std::runtime_error("error");
		}
	};

	struct ThrowingDefaultsManager: ConfigurationManager
	{
		template <typename T>
		bool setup_defaults(const T&)
		{
			throw std::runtime_error("error");
		}

		template <typename T>
		bool reset_defaults()
		{
			throw std::runtime_error("error");
		}
	};

	class ConfigurationManagerExhaustiveFlagsTest:
		public ConfigurationManagerTest,
		public ::testing::WithParamInterface<ConfigurationManagerConfigurations>
	{
	};

	struct ThrowingResetDefaultsManager: ConfigurationManager
	{
		template <typename T>
		bool reset_defaults()
		{
			throw std::runtime_error("reset_defaults fail");
		}
	};

	struct ThrowingResetDefaultsRecoveryManager: ConfigurationManager
	{
		template <typename T>
		bool reset_defaults()
		{
			throw std::runtime_error("reset_defaults fail");
		}
	};

	class ConfigurationManagerOverridesFalseTest:
		public ConfigurationManagerTest,
		public ::testing::WithParamInterface<ConfigurationManagerConfigurations>
	{
	};
}

#endif
