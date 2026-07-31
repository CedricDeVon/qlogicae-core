#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ValueExtractorManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	template <typename T>
	class ValueExtractorManagerTest: public ::testing::Test
	{
	public:
		ValueExtractorManager<T> manager;

		ValueExtractorManagerTest() = default;

		~ValueExtractorManagerTest() override = default;

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

	struct CustomStruct
	{
		int a = 1;
		bool operator==(const CustomStruct& other) const { return a == other.a; }
	};

	using ValueTypes = ::testing::Types<int,double,std::string,std::vector<int>>;

	using AdditionalTypes = ::testing::Types<int,double,std::string,std::vector<int>,CustomStruct>;

	using ValueTypesAdditional = ::testing::Types<int,double,std::string,std::vector<int>>;
}

#endif
