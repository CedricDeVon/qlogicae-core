#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ConfigurationManager \
	)

#include "../includes/configuration_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{		
	TEST_F(ConfigurationManagerTest, Should_ConstructSuccessfully_When_NoException)
	{
		ASSERT_TRUE(manager.construct());
    }

    TEST_F(ConfigurationManagerTest, Should_DestructSuccessfully_When_NoException)
    {
        ASSERT_TRUE(manager.destruct());
    }

    TEST_F(ConfigurationManagerTest, Should_SetupConfigurationsCorrectly_When_ValidInput)
    {
        ConfigurationManagerConfigurations configurations;
        configurations.is_feature_runtime_execution_handling_enabled = true;
		configurations.is_thread_safety_handling_override_enabled = false;

		ASSERT_TRUE(manager.setup(configurations));
		ASSERT_TRUE(manager.configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_FALSE(manager.configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_ResetConfigurationsToDefault_When_Called)
	{
		ConfigurationManagerConfigurations configurations;
		configurations.is_thread_safety_handling_override_enabled = true;

		manager.setup(configurations);
		ASSERT_TRUE(manager.reset());
		ASSERT_TRUE(manager.configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_FALSE(manager.configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_UpdateDefaultConfigurations_When_SetupDefaultsCalled)
	{
		ConfigurationManagerConfigurationsTest defaults;
		defaults.is_feature_runtime_execution_handling_enabled = false;
		defaults.is_thread_safety_handling_override_enabled = true;

		manager.setup_defaults<ConfigurationManagerConfigurationsTest>(defaults);

		ASSERT_FALSE(ConfigurationManagerConfigurationsTest::default_configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_TRUE(ConfigurationManagerConfigurationsTest::default_configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_ResetDefaultConfigurations_When_ResetDefaultsCalled)
	{
		ConfigurationManagerConfigurationsTest temp;
		temp.is_feature_runtime_execution_handling_enabled = false;
		temp.is_thread_safety_handling_override_enabled = true;

		manager.setup_defaults(temp);
		manager.reset_defaults<ConfigurationManagerConfigurationsTest>();

		ASSERT_TRUE(ConfigurationManagerConfigurationsTest::default_configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_FALSE(ConfigurationManagerConfigurationsTest::default_configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_P(ConfigurationManagerParameterizedTest, Should_WorkCorrectly_ForAllBooleanCombinations)
	{
		auto [enabled, thread_safety] = GetParam();

		ConfigurationManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = enabled;
		configurations.is_thread_safety_handling_override_enabled = thread_safety;

		manager.setup(configurations);

		ASSERT_EQ(manager.configurations.is_feature_runtime_execution_handling_enabled, enabled);
		ASSERT_EQ(manager.configurations.is_thread_safety_handling_override_enabled, thread_safety);
	}

	INSTANTIATE_TEST_CASE_P(
		BooleanCombinations,
		ConfigurationManagerParameterizedTest,
		::testing::Values(
			std::make_tuple(true, true),
			std::make_tuple(true, false),
			std::make_tuple(false, true),
			std::make_tuple(false, false)
		)
	);

	TEST_F(ConfigurationManagerTest, Should_HandleSingletonAccessAcrossThreads_When_ThreadSafetyEnabled)
	{
		ConfigurationManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = true;
		configurations.is_thread_safety_handling_override_enabled = true;
		manager.setup(configurations);

		std::atomic<int> counter{ 0 };
		auto task = [&]()
			{
				ConfigurationManagerConfigurations conf;
				conf.is_feature_runtime_execution_handling_enabled = true;
				conf.is_thread_safety_handling_override_enabled = true;
				manager.setup(conf);
			};

		std::vector<std::thread> threads;
		for (int i = 0; i < 32; ++i)
		{
			threads.emplace_back(task);
		}

		for (auto& t : threads)
		{
			t.join();
		}

		ASSERT_TRUE(manager.configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_TRUE(manager.configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_HandleMultipleConcurrentSetupResetCalls_WithoutRaceConditions)
	{
		auto setup_reset_task = [&]()
			{
				ConfigurationManagerConfigurations conf;
				conf.is_feature_runtime_execution_handling_enabled = true;
				conf.is_thread_safety_handling_override_enabled = false;

				for (int i = 0; i < 100; ++i)
				{
					manager.setup(conf);
					manager.reset();
				}
			};

		std::vector<std::thread> threads;
		for (int i = 0; i < 8; ++i)
		{
			threads.emplace_back(setup_reset_task);
		}

		for (auto& t : threads)
		{
			t.join();
		}

		ASSERT_TRUE(manager.configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_FALSE(manager.configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_CompleteUnderStress_When_CalledManyTimes)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_feature_runtime_execution_handling_enabled = true;
		conf.is_thread_safety_handling_override_enabled = true;

		for (int i = 0; i < 1000; ++i)
		{
			manager.reset();
			manager.setup(conf);
		}

		ASSERT_TRUE(manager.configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_TRUE(manager.configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_HandleAsyncSetupReset_When_CalledViaStdAsync)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_feature_runtime_execution_handling_enabled = true;
		conf.is_thread_safety_handling_override_enabled = true;

		auto future2 = std::async(std::launch::async, [&]()
			{
				for (int i = 0; i < 100; ++i)
				{
					manager.reset();
				}
			});

		future2.get();

		auto future1 = std::async(std::launch::async, [&]()
			{
				for (int i = 0; i < 100; ++i)
				{
					manager.setup(conf);
				}
			});

		future1.get();

		ASSERT_TRUE(manager.configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_TRUE(manager.configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_HandleEmptyConfigurations_When_SetupCalledWithDefault)
	{
		ConfigurationManagerConfigurations default_conf;
		ASSERT_TRUE(manager.setup(default_conf));

		ASSERT_TRUE(manager.configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_FALSE(manager.configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_ReturnFalse_When_ConstructCalledWithRuntimeExecutionDisabled)
	{
		ConfigurationManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.configurations = configurations;

		ASSERT_FALSE(manager.construct());
	}

	TEST_F(ConfigurationManagerTest, Should_ReturnFalse_When_DestructCalledWithRuntimeExecutionDisabled)
	{
		ConfigurationManagerConfigurations configurations;
		configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.configurations = configurations;

		ASSERT_FALSE(manager.destruct());
	}

	TEST_F(ConfigurationManagerTest, Should_ReturnFalse_When_SetupDefaultsCalledWithFeatureRuntimeExecutionDisabled)
	{
		ConfigurationManagerConfigurationsTest configurations;
		ConfigurationManagerConfigurations new_configurations;
		new_configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.configurations = new_configurations;

		ASSERT_FALSE(manager.setup_defaults<ConfigurationManagerConfigurationsTest>(configurations));
	}

	TEST_F(ConfigurationManagerTest, Should_ReturnFalse_When_ResetDefaultsCalledWithFeatureRuntimeExecutionDisabled)
	{
		ConfigurationManagerConfigurationsTest configurations;
		ConfigurationManagerConfigurations new_configurations;
		new_configurations.is_feature_runtime_execution_handling_enabled = false;
		manager.configurations = new_configurations;

		ASSERT_FALSE(manager.reset_defaults<ConfigurationManagerConfigurationsTest>());
	}

	TEST_F(ConfigurationManagerTest, Should_HandleEdgeCaseFlagsCorrectly)
	{
		ConfigurationManagerConfigurations configurations;
		configurations.is_edge_case_handling_override_enabled = true;
		configurations.is_utility_edge_case_handling_enabled = true;
		configurations.is_feature_edge_case_handling_enabled = true;
		configurations.is_error_edge_case_handling_enabled = true;
		manager.configurations = configurations;

		ASSERT_TRUE(manager.configurations.is_edge_case_enabled_for_utility_handling());
		ASSERT_TRUE(manager.configurations.is_edge_case_enabled_for_feature_handling());
		ASSERT_TRUE(manager.configurations.is_edge_case_enabled_for_error_handling());
	}

	TEST_F(ConfigurationManagerTest, Should_HandleThreadSafetyFlagsCorrectly)
	{
		ConfigurationManagerConfigurations configurations;
		configurations.is_thread_safety_handling_override_enabled = true;
		configurations.is_utility_thread_safety_handling_enabled = false;
		configurations.is_feature_thread_safety_handling_enabled = false;
		configurations.is_error_thread_safety_handling_enabled = false;
		manager.configurations = configurations;

		ASSERT_TRUE(manager.configurations.is_thread_safety_enabled_for_utility_handling());
		ASSERT_TRUE(manager.configurations.is_thread_safety_enabled_for_feature_handling());
		ASSERT_TRUE(manager.configurations.is_thread_safety_enabled_for_error_handling());

		configurations.is_thread_safety_handling_override_enabled = false;
		manager.configurations = configurations;

		ASSERT_FALSE(manager.configurations.is_thread_safety_disabled_for_utility_handling() == false);
		ASSERT_FALSE(manager.configurations.is_thread_safety_disabled_for_feature_handling() == false);
		ASSERT_FALSE(manager.configurations.is_thread_safety_disabled_for_error_handling() == false);
	}

	TEST_F(ConfigurationManagerTest, Should_HandleExceptionsInConstructDestruct)
	{
		class ThrowingConfigurationManager : public ConfigurationManager
		{
		public:
			bool construct()
			{
				throw std::runtime_error("construct fail");
			}
			bool destruct()
			{
				throw std::runtime_error("destruct fail");
			}
		};

		ThrowingConfigurationManager throwing_manager;

		ASSERT_THROW(throwing_manager.construct(), std::runtime_error);
		ASSERT_THROW(throwing_manager.destruct(), std::runtime_error);
	}

	TEST_F(ConfigurationManagerTest, Should_HandleExceptionsInSetupResetDefaults)
	{
		ThrowingConfigurationManager throwing_manager;

		ASSERT_THROW(throwing_manager.setup_defaults<ConfigurationManagerConfigurations>({}), std::runtime_error);
		ASSERT_THROW(throwing_manager.reset_defaults<ConfigurationManagerConfigurations>(), std::runtime_error);
	}

	TEST_F(ConfigurationManagerTest, Should_HonorRuntimeExecutionOverrideFlag)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_runtime_execution_handling_override_enabled = true;
		conf.is_utility_runtime_execution_handling_enabled = false;

		manager.setup(conf);
		ASSERT_TRUE(manager.configurations.is_runtime_execution_enabled_for_utility_handling());
		ASSERT_FALSE(manager.configurations.is_runtime_execution_disabled_for_utility_handling());
	}

	TEST_F(ConfigurationManagerTest, Should_HonorEdgeCaseOverrideFlag)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_edge_case_handling_override_enabled = true;
		conf.is_utility_edge_case_handling_enabled = false;

		manager.setup(conf);
		ASSERT_TRUE(manager.configurations.is_edge_case_enabled_for_utility_handling());
		ASSERT_FALSE(manager.configurations.is_edge_case_disabled_for_utility_handling());
	}

	TEST_F(ConfigurationManagerTest, Should_HonorThreadSafetyOverrideFlag)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_thread_safety_handling_override_enabled = true;
		conf.is_feature_thread_safety_handling_enabled = false;

		manager.setup(conf);
		ASSERT_TRUE(manager.configurations.is_thread_safety_enabled_for_feature_handling());
		ASSERT_FALSE(manager.configurations.is_thread_safety_disabled_for_feature_handling());
	}

	TEST_P(ConfigurationManagerAllFlagsParameterizedTest, Should_HandleAllFlagCombinations)
	{
		ConfigurationManagerConfigurations conf = GetParam();
		manager.setup(conf);

		ASSERT_EQ(manager.configurations.is_runtime_execution_enabled_for_utility_handling(),
			conf.is_runtime_execution_handling_override_enabled || conf.is_utility_runtime_execution_handling_enabled);
		ASSERT_EQ(manager.configurations.is_runtime_execution_enabled_for_feature_handling(),
			conf.is_runtime_execution_handling_override_enabled || conf.is_feature_runtime_execution_handling_enabled);
		ASSERT_EQ(manager.configurations.is_runtime_execution_enabled_for_error_handling(),
			conf.is_runtime_execution_handling_override_enabled || conf.is_error_runtime_execution_handling_enabled);

		ASSERT_EQ(manager.configurations.is_edge_case_enabled_for_utility_handling(),
			conf.is_edge_case_handling_override_enabled || conf.is_utility_edge_case_handling_enabled);
		ASSERT_EQ(manager.configurations.is_edge_case_enabled_for_feature_handling(),
			conf.is_edge_case_handling_override_enabled || conf.is_feature_edge_case_handling_enabled);
		ASSERT_EQ(manager.configurations.is_edge_case_enabled_for_error_handling(),
			conf.is_edge_case_handling_override_enabled || conf.is_error_edge_case_handling_enabled);

		ASSERT_EQ(manager.configurations.is_thread_safety_enabled_for_utility_handling(),
			conf.is_thread_safety_handling_override_enabled || conf.is_utility_thread_safety_handling_enabled);
		ASSERT_EQ(manager.configurations.is_thread_safety_enabled_for_feature_handling(),
			conf.is_thread_safety_handling_override_enabled || conf.is_feature_thread_safety_handling_enabled);
		ASSERT_EQ(manager.configurations.is_thread_safety_enabled_for_error_handling(),
			conf.is_thread_safety_handling_override_enabled || conf.is_error_thread_safety_handling_enabled);
	}

	INSTANTIATE_TEST_CASE_P(
		AllFlagCombinations,
		ConfigurationManagerAllFlagsParameterizedTest,
		::testing::Values(
			ConfigurationManagerConfigurations{},
			[]() { ConfigurationManagerConfigurations c; c.is_runtime_execution_handling_override_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c; c.is_edge_case_handling_override_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c; c.is_thread_safety_handling_override_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c; c.is_runtime_execution_handling_override_enabled = true; c.is_edge_case_handling_override_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c; c.is_runtime_execution_handling_override_enabled = true; c.is_thread_safety_handling_override_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c; c.is_edge_case_handling_override_enabled = true; c.is_thread_safety_handling_override_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c; c.is_runtime_execution_handling_override_enabled = true; c.is_edge_case_handling_override_enabled = true; c.is_thread_safety_handling_override_enabled = true; return c; }()
		)
	);

	TEST_F(ConfigurationManagerTest, Should_ReturnSingletonInstanceCorrectly)
	{
		ConfigurationManager& instance1 = SingletonManager::get_singleton<ConfigurationManager>();
		ConfigurationManager& instance2 = SingletonManager::get_singleton<ConfigurationManager>();

		ASSERT_EQ(&instance1, &instance2);
	}

	TEST_F(ConfigurationManagerTest, Should_HandleSetupWithRuntimeExecutionDisabled)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_utility_runtime_execution_handling_enabled = false;
		conf.is_runtime_execution_handling_override_enabled = false;

		ASSERT_TRUE(manager.setup(conf));
		ASSERT_FALSE(manager.configurations.is_runtime_execution_enabled_for_utility_handling());
	}

	TEST_F(ConfigurationManagerTest, Should_HandleSetupWithEdgeCaseDisabled)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_utility_edge_case_handling_enabled = false;
		conf.is_edge_case_handling_override_enabled = false;

		manager.setup(conf);

		ASSERT_FALSE(manager.configurations.is_edge_case_enabled_for_utility_handling());
	}

	TEST_F(ConfigurationManagerTest, Should_HandleSetupWithThreadSafetyDisabled)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_utility_thread_safety_handling_enabled = false;
		conf.is_thread_safety_handling_override_enabled = false;

		manager.setup(conf);
		ASSERT_FALSE(manager.configurations.is_thread_safety_enabled_for_utility_handling());
	}

	TEST_F(ConfigurationManagerExceptionTest, Should_ReturnFalse_When_ConstructThrows)
	{
		struct ThrowingConfigManager : ConfigurationManager
		{
			bool construct()
			{
				throw std::runtime_error("error");
			}
		};

		ThrowingConfigManager throwing_manager;

		ASSERT_THROW(
			{
				bool result = throwing_manager.construct();
				ASSERT_FALSE(result);
			},
			std::runtime_error
		);
	}

	TEST_F(ConfigurationManagerExceptionTest, Should_ReturnFalse_When_DestructThrows)
	{
		struct ThrowingConfigManager : ConfigurationManager
		{
			bool destruct()
			{
				throw std::runtime_error("error");
			}
		};

		ThrowingConfigManager throwing_manager;

		ASSERT_THROW(
			{
				bool result = throwing_manager.destruct();
				ASSERT_FALSE(result);
			},
			std::runtime_error
		);
	}

	TEST_F(ConfigurationManagerExceptionTest, Should_ReturnFalse_When_ResetDefaultsThrows)
	{
		ThrowingDefaults throwing_manager;

		ASSERT_THROW(
			{
				ConfigurationManagerConfigurations config;

				throwing_manager.setup_defaults<ConfigurationManagerConfigurations>(config);
			},
			std::runtime_error
		);
	}

	TEST_F(ConfigurationManagerExceptionTest, Should_HandleConcurrentConstructDestructSetupReset_UnderHighThreadCount)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_feature_runtime_execution_handling_enabled = true;
		conf.is_thread_safety_handling_override_enabled = true;

		auto task = [&]()
			{
				for (int i = 0; i < 500; ++i)
				{
					manager.destruct();
					manager.reset();
					manager.construct();
					manager.setup(conf);
				}
			};

		std::vector<std::thread> threads;
		for (int i = 0; i < 64; ++i)
		{
			threads.emplace_back(task);
		}

		for (auto& t : threads)
		{
			t.join();
		}

		ASSERT_TRUE(manager.configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_TRUE(manager.configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerExceptionTest, Should_HandleFeatureAndErrorFlagsIndependently)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_feature_runtime_execution_handling_enabled = false;
		conf.is_error_runtime_execution_handling_enabled = true;
		conf.is_thread_safety_handling_override_enabled = true;

		manager.setup(conf);

		ASSERT_FALSE(manager.configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_TRUE(manager.configurations.is_error_runtime_execution_handling_enabled);
		ASSERT_TRUE(manager.configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerExceptionTest, Should_HandleEdgeCaseFlagsCorrectly)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_utility_edge_case_handling_enabled = true;
		conf.is_feature_edge_case_handling_enabled = false;
		conf.is_error_edge_case_handling_enabled = true;

		manager.setup(conf);

		ASSERT_TRUE(manager.configurations.is_utility_edge_case_handling_enabled);
		ASSERT_FALSE(manager.configurations.is_feature_edge_case_handling_enabled);
		ASSERT_TRUE(manager.configurations.is_error_edge_case_handling_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_HandleConcurrentSetupDefaultsResetDefaults_UnderMultipleThreads)
	{
		ConfigurationManagerConfigurationsTest defaults;
		defaults.is_feature_runtime_execution_handling_enabled = true;
		defaults.is_thread_safety_handling_override_enabled = true;

		auto task = [&]()
			{
				for (int i = 0; i < 100; ++i)
				{
					manager.setup_defaults(defaults);
					manager.reset_defaults<ConfigurationManagerConfigurationsTest>();
				}
			};

		std::vector<std::thread> threads;
		for (int i = 0; i < 16; ++i)
		{
			threads.emplace_back(task);
		}

		for (auto& t : threads)
		{
			t.join();
		}

		ASSERT_TRUE(ConfigurationManagerConfigurationsTest::default_configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_FALSE(ConfigurationManagerConfigurationsTest::default_configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_HandleAsyncSetupDefaultsResetDefaults_When_CalledViaStdAsync)
	{
		ConfigurationManagerConfigurationsTest defaults;
		defaults.is_feature_runtime_execution_handling_enabled = true;
		defaults.is_thread_safety_handling_override_enabled = true;

		auto future_reset = std::async(std::launch::async, [&]()
			{
				for (int i = 0; i < 100; ++i)
				{
					manager.reset_defaults<ConfigurationManagerConfigurationsTest>();
				}
			});

		auto future_setup = std::async(std::launch::async, [&]()
			{
				for (int i = 0; i < 100; ++i)
				{
					manager.setup_defaults(defaults);
				}
			});

		future_reset.get();
		future_setup.get();

		ASSERT_TRUE(ConfigurationManagerConfigurationsTest::default_configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_TRUE(ConfigurationManagerConfigurationsTest::default_configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_ReturnFalse_When_SetupDefaultsThrowsException)
	{
		ThrowingDefaultsManager throwing_manager;
		ConfigurationManagerConfigurations defaults;

		ASSERT_THROW({
			bool result = throwing_manager.setup_defaults(defaults);
			ASSERT_FALSE(result);
			}, std::runtime_error);
	}

	TEST_F(ConfigurationManagerTest, Should_ReturnFalse_When_ResetDefaultsThrowsException)
	{
		ThrowingDefaultsManager throwing_manager;

		ASSERT_THROW({
			bool result = throwing_manager.reset_defaults<ConfigurationManagerConfigurations>();
			ASSERT_FALSE(result);
			}, std::runtime_error
		);
	}

	TEST_P(ConfigurationManagerExhaustiveFlagsTest, Should_HandleAllBooleanFlagCombinationsExhaustively)
	{
		ConfigurationManagerConfigurations conf = GetParam();
		manager.setup(conf);

		ASSERT_EQ(manager.configurations.is_runtime_execution_enabled_for_utility_handling(),
			conf.is_runtime_execution_handling_override_enabled || conf.is_utility_runtime_execution_handling_enabled);
		ASSERT_EQ(manager.configurations.is_runtime_execution_enabled_for_feature_handling(),
			conf.is_runtime_execution_handling_override_enabled || conf.is_feature_runtime_execution_handling_enabled);
		ASSERT_EQ(manager.configurations.is_runtime_execution_enabled_for_error_handling(),
			conf.is_runtime_execution_handling_override_enabled || conf.is_error_runtime_execution_handling_enabled);

		ASSERT_EQ(manager.configurations.is_edge_case_enabled_for_utility_handling(),
			conf.is_edge_case_handling_override_enabled || conf.is_utility_edge_case_handling_enabled);
		ASSERT_EQ(manager.configurations.is_edge_case_enabled_for_feature_handling(),
			conf.is_edge_case_handling_override_enabled || conf.is_feature_edge_case_handling_enabled);
		ASSERT_EQ(manager.configurations.is_edge_case_enabled_for_error_handling(),
			conf.is_edge_case_handling_override_enabled || conf.is_error_edge_case_handling_enabled);

		ASSERT_EQ(manager.configurations.is_thread_safety_enabled_for_utility_handling(),
			conf.is_thread_safety_handling_override_enabled || conf.is_utility_thread_safety_handling_enabled);
		ASSERT_EQ(manager.configurations.is_thread_safety_enabled_for_feature_handling(),
			conf.is_thread_safety_handling_override_enabled || conf.is_feature_thread_safety_handling_enabled);
		ASSERT_EQ(manager.configurations.is_thread_safety_enabled_for_error_handling(),
			conf.is_thread_safety_handling_override_enabled || conf.is_error_thread_safety_handling_enabled);
	}

	INSTANTIATE_TEST_CASE_P(
		ExhaustiveFlagCombinations,
		ConfigurationManagerExhaustiveFlagsTest,
		::testing::Values(
			[]() { ConfigurationManagerConfigurations c{}; return c; }(),
			[]() { ConfigurationManagerConfigurations c{}; c.is_runtime_execution_handling_override_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c{}; c.is_edge_case_handling_override_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c{}; c.is_thread_safety_handling_override_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c{}; c.is_runtime_execution_handling_override_enabled = true; c.is_edge_case_handling_override_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c{}; c.is_runtime_execution_handling_override_enabled = true; c.is_thread_safety_handling_override_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c{}; c.is_edge_case_handling_override_enabled = true; c.is_thread_safety_handling_override_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c{}; c.is_runtime_execution_handling_override_enabled = true; c.is_edge_case_handling_override_enabled = true; c.is_thread_safety_handling_override_enabled = true; return c; }()
		)
	);

	TEST_F(ConfigurationManagerTest, Should_NotModifyDefaults_When_SetupDefaultsThrows)
	{
		ThrowingDefaultsManager throwing_manager;

		ConfigurationManagerConfigurationsTest saved_defaults = ConfigurationManagerConfigurationsTest::default_configurations;

		ASSERT_THROW(
			{
				ConfigurationManagerConfigurationsTest conf{};
				throwing_manager.setup_defaults(conf);
			}, std::runtime_error);

		ASSERT_EQ(saved_defaults.is_feature_runtime_execution_handling_enabled,
			ConfigurationManagerConfigurationsTest::default_configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_EQ(saved_defaults.is_thread_safety_handling_override_enabled,
			ConfigurationManagerConfigurationsTest::default_configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_HandleConcurrentSingletonAccessAndDefaultsModification)
	{
		ConfigurationManagerConfigurationsTest defaults;
		defaults.is_feature_runtime_execution_handling_enabled = true;
		defaults.is_thread_safety_handling_override_enabled = true;

		auto task = [&]()
			{
				for (int i = 0; i < 200; ++i)
				{
					auto& singleton = SingletonManager::get_singleton<ConfigurationManager>();
					singleton.setup_defaults(defaults);
					singleton.reset_defaults<ConfigurationManagerConfigurationsTest>();
				}
			};

		std::vector<std::thread> threads;
		for (int i = 0; i < 32; ++i)
			threads.emplace_back(task);

		for (auto& t : threads)
			t.join();

		ASSERT_TRUE(ConfigurationManagerConfigurationsTest::default_configurations.is_feature_runtime_execution_handling_enabled);
		ASSERT_FALSE(ConfigurationManagerConfigurationsTest::default_configurations.is_thread_safety_handling_override_enabled);
	}

	TEST_F(ConfigurationManagerTest, Should_DisableAllRuntimeExecution_When_AllFlagsFalseAndOverrideFalse)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_runtime_execution_handling_override_enabled = false;
		conf.is_utility_runtime_execution_handling_enabled = false;
		conf.is_feature_runtime_execution_handling_enabled = false;
		conf.is_error_runtime_execution_handling_enabled = false;

		manager.setup(conf);

		ASSERT_FALSE(manager.configurations.is_runtime_execution_enabled_for_utility_handling());
		ASSERT_FALSE(manager.configurations.is_runtime_execution_enabled_for_feature_handling());
		ASSERT_FALSE(manager.configurations.is_runtime_execution_enabled_for_error_handling());
	}

	TEST_F(ConfigurationManagerTest, Should_HandleExceptionWhenResetDefaultsThrows)
	{
		ThrowingResetDefaultsManager throwing_manager;

		ASSERT_THROW(
			{
				throwing_manager.reset_defaults<ConfigurationManagerConfigurations>();
			}, std::runtime_error);
	}

	TEST_F(ConfigurationManagerTest, Should_ValidateAtomicCounter_When_SingletonAccess)
	{
		std::atomic<int> counter{ 0 };
		auto task = [&counter]()
			{
				for (int i = 0; i < 100; ++i)
				{
					counter.fetch_add(1, std::memory_order_relaxed);
				}
			};

		std::vector<std::thread> threads;
		for (int i = 0; i < 8; ++i)
			threads.emplace_back(task);

		for (auto& t : threads)
			t.join();

		ASSERT_EQ(counter.load(std::memory_order_relaxed), 800);
	}

	TEST_F(ConfigurationManagerTest, Should_ReturnFalse_When_DestructCalledWithAllRuntimeDisabled)
	{
		ConfigurationManagerConfigurations conf;
		conf.is_runtime_execution_handling_override_enabled = false;
		conf.is_utility_runtime_execution_handling_enabled = false;
		conf.is_feature_runtime_execution_handling_enabled = false;
		conf.is_error_runtime_execution_handling_enabled = false;

		manager.configurations = conf;

		ASSERT_FALSE(manager.destruct());
	}

	TEST_F(ConfigurationManagerTest, Should_HandlePartiallyCorruptedConfiguration)
	{
		ConfigurationManagerConfigurations conf;
		memset(&conf, 0xFF, sizeof(ConfigurationManagerConfigurations));

		ASSERT_NO_THROW(manager.setup(conf));
		ASSERT_NO_THROW(manager.reset());
		ASSERT_NO_THROW(manager.construct());
		ASSERT_NO_THROW(manager.destruct());
	}

	TEST_F(ConfigurationManagerTest, Should_HandleAllHandlersSimultaneouslyUnderThreadedStress)
	{
		ConfigurationManagerConfigurationsTest conf;
		ConfigurationManagerConfigurations new_configurations;

		conf.is_runtime_execution_handling_override_enabled = true;
		conf.is_edge_case_handling_override_enabled = true;
		conf.is_thread_safety_handling_override_enabled = true;

		new_configurations.is_runtime_execution_handling_override_enabled = true;
		new_configurations.is_edge_case_handling_override_enabled = true;
		new_configurations.is_thread_safety_handling_override_enabled = true;

		auto task = [&]()
			{
				for (int i = 0; i < 200; ++i)
				{
					manager.reset_defaults<ConfigurationManagerConfigurationsTest>();
					manager.reset();
					manager.setup_defaults(conf);
					manager.setup(new_configurations);
				}
			};

		std::vector<std::thread> threads;
		for (int i = 0; i < 32; ++i)
			threads.emplace_back(task);

		for (auto& t : threads)
			t.join();

		ASSERT_TRUE(manager.configurations.is_runtime_execution_enabled_for_utility_handling());
		ASSERT_TRUE(manager.configurations.is_edge_case_enabled_for_feature_handling());
		ASSERT_TRUE(manager.configurations.is_thread_safety_enabled_for_error_handling());
	}

	TEST_F(ConfigurationManagerTest, Should_ContinueOperationAfterResetDefaultsThrows)
	{
		ThrowingResetDefaultsRecoveryManager throwing_manager;

		ASSERT_THROW(throwing_manager.reset_defaults<ConfigurationManagerConfigurationsTest>(), std::runtime_error);

		ConfigurationManagerConfigurations new_configurations;

		new_configurations.is_runtime_execution_handling_override_enabled = true;
		new_configurations.is_edge_case_handling_override_enabled = true;
		new_configurations.is_thread_safety_handling_override_enabled = true;

		ASSERT_TRUE(throwing_manager.construct());
		ASSERT_TRUE(throwing_manager.setup(new_configurations));
		ASSERT_TRUE(throwing_manager.destruct());
	}

	TEST_F(ConfigurationManagerTest, Should_ValidateAtomicCountersAcrossMultipleMethods)
	{

		ConfigurationManagerConfigurations new_configurations;

		new_configurations.is_runtime_execution_handling_override_enabled = true;
		new_configurations.is_edge_case_handling_override_enabled = true;
		new_configurations.is_thread_safety_handling_override_enabled = true;

		std::atomic<int> counter{ 0 };
		auto task = [&counter, &new_configurations, this]()
			{
				for (int i = 0; i < 100; ++i)
				{
					counter.fetch_add(1, std::memory_order_relaxed);

					ConfigurationManagerConfigurationsTest conf;
					conf.is_feature_runtime_execution_handling_enabled = true;
					conf.is_thread_safety_handling_override_enabled = true;

					manager.setup(new_configurations);
					manager.reset();
					manager.setup_defaults(conf);
					manager.reset_defaults<ConfigurationManagerConfigurationsTest>();
				}
			};

		std::vector<std::thread> threads;
		for (int i = 0; i < 8; ++i)
			threads.emplace_back(task);

		for (auto& t : threads)
			t.join();

		ASSERT_EQ(counter.load(std::memory_order_relaxed), 800);
	}

	TEST_P(ConfigurationManagerOverridesFalseTest, Should_HandleCombinedOverridesFalseWithEnabledFlags)
	{
		ConfigurationManagerConfigurations conf = GetParam();
		conf.is_runtime_execution_handling_override_enabled = false;
		conf.is_edge_case_handling_override_enabled = false;
		conf.is_thread_safety_handling_override_enabled = false;

		manager.setup(conf);

		ASSERT_EQ(manager.configurations.is_runtime_execution_enabled_for_utility_handling(),
			conf.is_utility_runtime_execution_handling_enabled);
		ASSERT_EQ(manager.configurations.is_runtime_execution_enabled_for_feature_handling(),
			conf.is_feature_runtime_execution_handling_enabled);
		ASSERT_EQ(manager.configurations.is_runtime_execution_enabled_for_error_handling(),
			conf.is_error_runtime_execution_handling_enabled);

		ASSERT_EQ(manager.configurations.is_edge_case_enabled_for_utility_handling(),
			conf.is_utility_edge_case_handling_enabled);
		ASSERT_EQ(manager.configurations.is_edge_case_enabled_for_feature_handling(),
			conf.is_feature_edge_case_handling_enabled);
		ASSERT_EQ(manager.configurations.is_edge_case_enabled_for_error_handling(),
			conf.is_error_edge_case_handling_enabled);

		ASSERT_EQ(manager.configurations.is_thread_safety_enabled_for_utility_handling(),
			conf.is_utility_thread_safety_handling_enabled);
		ASSERT_EQ(manager.configurations.is_thread_safety_enabled_for_feature_handling(),
			conf.is_feature_thread_safety_handling_enabled);
		ASSERT_EQ(manager.configurations.is_thread_safety_enabled_for_error_handling(),
			conf.is_error_thread_safety_handling_enabled);
	}

	INSTANTIATE_TEST_CASE_P(
		CombinedOverridesFalse,
		ConfigurationManagerOverridesFalseTest,
		::testing::Values(
			[]() { ConfigurationManagerConfigurations c{}; c.is_utility_runtime_execution_handling_enabled = true; c.is_feature_runtime_execution_handling_enabled = true; c.is_error_runtime_execution_handling_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c{}; c.is_utility_edge_case_handling_enabled = true; c.is_feature_edge_case_handling_enabled = true; c.is_error_edge_case_handling_enabled = true; return c; }(),
			[]() { ConfigurationManagerConfigurations c{}; c.is_utility_thread_safety_handling_enabled = true; c.is_feature_thread_safety_handling_enabled = true; c.is_error_thread_safety_handling_enabled = true; return c; }()
		)
	);
}

#endif
