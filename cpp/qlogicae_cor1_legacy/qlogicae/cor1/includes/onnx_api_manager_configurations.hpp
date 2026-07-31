#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		OnnxApiManagerConfigurations \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    struct
		OnnxApiManagerConfigurations :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CONFIGURATIONS_NAME<OnnxApiManagerConfigurations>
    {
	public:
		std::string
			model_path =
				"";

		bool
			enable_cuda =
				false;

		int
			device_id =
				1;

		OnnxApiManagerConfigurations();
    };    
}

#endif
