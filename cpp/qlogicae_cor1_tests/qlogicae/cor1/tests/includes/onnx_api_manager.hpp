#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		OnnxApiManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
#ifdef _M_X64			
	class OnnxApiManagerTest: public ::testing::Test
	{
	public:
		OnnxApiManagerTest()
		{
			manager.configurations.model_path = "model.onnx";
			manager.configurations.enable_cuda = false;
			manager.setup();
		}

		OnnxApiManagerConfigurations configurations;
		OnnxApiManager manager;
	};

	class OnnxApiManagerStressTest
		: public OnnxApiManagerTest,
		public ::testing::WithParamInterface<size_t>
	{
	};
#endif
}

#endif
