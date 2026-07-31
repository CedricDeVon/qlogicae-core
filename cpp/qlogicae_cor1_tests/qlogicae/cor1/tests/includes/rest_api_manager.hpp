#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RestApiManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class RestApiManagerTest:
		public ::testing::Test
	{
	public:
		RestApiManager manager_instance;

		RestApiManagerTest()
		{
			RestApiManagerConfigurations
				configurations;

			configurations.base_url =
				"http://127.0.0.1";

			manager_instance.setup(
				configurations
			);
		}

		RestApiManagerResponse
			execute_get(
				const std::string&
				path
			)
		{
			return
				manager_instance
				.execute_get_request(
					path
				);
		}
	};

	class RestApiManagerParameterizedTest:
		public RestApiManagerTest,
		public ::testing::WithParamInterface<std::string>
	{
	public:
		RestApiManagerParameterizedTest()
		{
		}
	};

	class RestApiManagerEmptyPathParameterizedTest:
		public RestApiManagerTest,
		public ::testing::WithParamInterface<int>
	{
	};
}

#endif
