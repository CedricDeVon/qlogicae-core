#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		EntityActivationStatusEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class EntityActivationStatusEnumManagerTest:
		public ::testing::Test
	{
	public:
		EntityActivationStatusEnumManager manager;

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

	class EntityActivationStatusEnumManagerParameterizedTest:
		public EntityActivationStatusEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,EntityActivationStatus>>
	{
	};

	class EntityActivationStatusEnumManagerEnumToStringParameterizedTest:
		public EntityActivationStatusEnumManagerTest,
		public ::testing::WithParamInterface<EntityActivationStatus>
	{
	};
}

#endif
