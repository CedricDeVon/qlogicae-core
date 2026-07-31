#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		UuidEnumManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class UuidEnumManagerTest:
		public ::testing::Test
	{
	public:
		UuidEnumManager manager;

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

	class UuidEnumManagerParameterizedTest:
		public UuidEnumManagerTest,
		public ::testing::WithParamInterface<std::pair<std::string,Uuid>>
	{
	};

	class UuidEnumManagerEnumToStringParameterizedTest:
		public UuidEnumManagerTest,
		public ::testing::WithParamInterface<Uuid>
	{
	};
}

#endif
