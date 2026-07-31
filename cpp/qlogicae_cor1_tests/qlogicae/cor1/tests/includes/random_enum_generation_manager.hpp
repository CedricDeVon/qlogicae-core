#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomEnumGenerationManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	enum class TestEnum
	{
		NONE,
		ALPHA,
		BETA,
		GAMMA,
		DELTA
	};

	struct RandomEnumGenerationManagerTestParam
	{
		TestEnum minimum;
		TestEnum maximum;
		std::unordered_set<TestEnum> excluded;
		TestEnum expected;
	};

	class RandomEnumGenerationManagerTest:
		public ::testing::Test
	{
	public:
		RandomEnumGenerationManager manager;

		RandomEnumGenerationManagerTest()
		{
		}
	};

	class RandomEnumGenerationManagerParameterizedTest:
		public RandomEnumGenerationManagerTest,
		public ::testing::WithParamInterface<RandomEnumGenerationManagerTestParam>
	{
	public:
		RandomEnumGenerationManagerParameterizedTest()
		{
		}
	};

	class RandomEnumGenerationManagerErrorInjectionTest:
		public RandomEnumGenerationManagerTest
	{
	public:
		class ErrorManagerMock
		{
		public:
			template <typename OutputType>
			OutputType handle_error_outputs(const std::exception&)
			{
				return OutputType{};
			}
		};

		RandomEnumGenerationManager manager_with_mock;
	};
}

#endif
