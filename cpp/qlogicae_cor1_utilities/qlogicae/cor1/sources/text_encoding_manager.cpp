#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		TextEncodingManager \
	)

#include "../includes/text_encoding_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{	
    TextEncodingManager
		::TextEncodingManager() :
			QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<TextEncodingManagerConfigurations>()
	{
			
	}

	std::string
		TextEncodingManager
			::decode_base16(
				const std::string&
					input
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				input.size() % 2 != 0
			);	

			std::string output;
			output.resize(input.size() / 2);

			try
			{
				if (sodium_hex2bin(
					reinterpret_cast<unsigned char*>(&output[0]),
					output.size(),
					input.data(),
					input.size(),
					nullptr,
					nullptr,
					nullptr) != 0)
				{
					return "";
				}
			}
			catch (...)
			{
				return "";
			}

			return output;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();			
        }		
	}

	std::string
		TextEncodingManager
			::encode_base16(
				const std::string&
					input
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				input.empty()
			);			

			std::string output;
			output.resize(input.size() * 2 + 1);

			try
			{
				sodium_bin2hex(&output[0], output.size(),
					reinterpret_cast<const unsigned char*>(input.data()),
					input.size());
				output.pop_back();
				std::transform(output.begin(), output.end(), output.begin(),
					[](unsigned char c) { return std::toupper(c); });
			}
			catch (...)
			{
				return "";
			}			

			return output;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();				
        }		
	}

	std::string
		TextEncodingManager
			::decode_base32(
				const std::string& input
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				input.empty()
			);						

			try
			{
				using base32_codec = cppcodec::base32_rfc4648;
				std::vector<uint8_t> decoded_bytes =
					base32_codec::decode(input);

				return
					std::string(
						decoded_bytes.begin(),
						decoded_bytes.end()
					);
			}
			catch (...)
			{
				return "";
			}					
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();				
        }		
	}

	std::string
		TextEncodingManager
			::encode_base32(
				const std::string&
					input
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				input.empty()
			);						
			
			try
			{
				using base32_codec = cppcodec::base32_rfc4648;
				std::vector<uint8_t> binary_data(
					input.begin(), input.end());

				return
					base32_codec::encode(binary_data);
			}
			catch (...)
			{
				return "";
			}			
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();				
        }		
	}

	std::string
		TextEncodingManager
			::decode_base64(
				const std::string& input
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				input.empty()
			);						

			std::string output = input;
			size_t padding_needed = (4 - (output.size() % 4)) % 4;
			output.append(padding_needed, '=');
			size_t written = 0;

			try
			{
				if (sodium_base642bin(
					reinterpret_cast<unsigned char*>(&output[0]),
					output.size(),
					output.data(),
					output.size(),
					nullptr,
					&written,
					nullptr,
					sodium_base64_VARIANT_ORIGINAL) != 0)
				{
					return "";
				}
			}
			catch (...)
			{
				return "";
			}			

			output.resize(written);
			return output;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();				
        }		
	}

	std::string
		TextEncodingManager
			::encode_base64(
				const std::string& input
			)
	{
		try
        {		
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_2,
				input.empty()
			);						

			size_t encoded_size = sodium_base64_encoded_len(input.size(), sodium_base64_VARIANT_ORIGINAL);
			std::string output;
			output.resize(encoded_size);

			try
			{
				sodium_bin2base64(
					&output[0],
					output.size(),
					reinterpret_cast<const unsigned char*>(input.data()),
					input.size(),
					sodium_base64_VARIANT_ORIGINAL);
			}
			catch (...)
			{
				return "";
			}			

			output.pop_back(); 
			return output;
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();				
        }		
	}

	std::string
		TextEncodingManager
			::convert_text(
				const std::string&
					text,
				const TextEncoding&
					original_type,
				const TextEncoding&
					target_type
			)
	{
		try
        {					
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				text,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				text.empty() ||
				original_type == TextEncoding::NONE ||
				target_type == TextEncoding::NONE ||
				original_type == target_type
			);					

			std::string
				bytes;

			switch (original_type)
			{
				case TextEncoding::BASE16:
					bytes = decode_base16(text);
					break;

				case TextEncoding::BASE32:
					bytes = decode_base32(text);
					break;

				case TextEncoding::BASE64:
					bytes = decode_base64(text);
					break;

				default:
					return {};
			}

			if (bytes.empty())
			{
				return {};
			}

			switch (target_type)
			{
				case TextEncoding::BASE16:
					return encode_base16(bytes);

				case TextEncoding::BASE32:
					return encode_base32(bytes);

				case TextEncoding::BASE64:
					return encode_base64(bytes);

				default:
					return {};
			}
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				text
			);				
        }		
	}

	std::string
		TextEncodingManager
			::convert_bytes_to_string(
				const std::vector<std::byte>&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				!value.size()
			);	

			return
				{
					reinterpret_cast<const char*>(
						value.data()),
						value.size()
				};
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();				
        }		
	}

	std::vector<std::byte>
		TextEncodingManager
			::convert_string_to_bytes(
				const std::string&
					value
			)
	{
		try
        {					
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				value.empty()
			);			

			return
				{
					reinterpret_cast<const std::byte*>(value.data()),
					reinterpret_cast<const std::byte*>(value.data()) + value.size()
				};
        }
        catch
        (
            QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
        )
        {
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();		
        }		
	}
}

#endif
