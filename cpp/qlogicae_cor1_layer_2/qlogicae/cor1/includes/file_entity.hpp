#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		FileEntity \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
	struct
		FileEntity
	{	
		std::string
			file_name =
				"";

		std::string
			file_path =
				"";

		std::string
			mime_type =
				"";		

		std::string
			cid =
				"";
	};
}

#endif
