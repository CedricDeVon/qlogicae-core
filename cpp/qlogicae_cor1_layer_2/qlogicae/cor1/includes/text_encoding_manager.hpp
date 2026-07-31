#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextEncodingManager \
	)

#include "text_case.hpp"
#include "text_encoding.hpp"
#include "text_case_manager.hpp"
#include "text_encoding_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		TextEncodingManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextEncodingManagerConfigurations>
    {
    public:
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2
		);

		TextEncodingManager();

		std::string
			convert_text(
				const std::string&
					text,
				const TextEncoding&
					original_type,
				const TextEncoding&
					target_type
			);

		std::string
			convert_text(
				const std::string&
					text
			);

		std::string
			decode_base16(
				const std::string&
					input
			);

		std::string
			encode_base16(
				const std::string&
					input
			);

		std::string
			decode_base32(
				const std::string&
					input
			);

		std::string
			encode_base32(
				const std::string&
					input
			);

		std::string
			decode_base64(
				const std::string&
					input
			);

		std::string
			encode_base64(
				const std::string&
					input
			);

		std::string
			convert_enum_to_string(
				const TextEncoding&
					value,
				const TextCase&
					text_case
			);

		std::string
			convert_enum_to_string(
				const TextEncoding&
					value
			);

		std::string
			convert_enum_to_string();

		TextEncoding
			convert_string_to_enum(
				const std::string&
					value
			);

		TextEncoding
			convert_string_to_enum();

		// Unit Testing Required
		std::string
			convert_bytes_to_string(
				const std::vector<std::byte>&
					value
			);

		std::vector<std::byte>
			convert_string_to_bytes(
				const std::string&
					value
			);
    };
}

#endif
