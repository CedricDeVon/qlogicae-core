#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		AbstractClass \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	struct TestConfigurations:
		public AbstractConfigurations<TestConfigurations>
	{
	public:
		static TestConfigurations
			default_configurations;
	};

	TestConfigurations
	TestConfigurations
	::default_configurations;

	class TestClass:
		public AbstractClass<TestConfigurations>
	{
	public:
		TestClass()
		{
		}

		bool
			throwing_method()
		{
			throw std::runtime_error(
				std::string("exception")
			);
		}
	};

	class AbstractConfigurationsTest:
		public ::testing::Test
	{
	public:
		TestConfigurations
			configurations;
	};

	class AbstractConfigurationsParameterizedTest:
		public ::testing::TestWithParam<bool>
	{
	public:
		TestConfigurations
			configurations;
	};

	class AbstractClassTest:
		public ::testing::Test
	{
	public:
		TestClass
			instance;
	};

	class FailingTestClass:
		public AbstractClass<TestConfigurations>
	{
	public:
		bool
			handle_error_outputs(
				const std::exception&
			)
		{
			return
				false;
		}
	};
}

#endif
