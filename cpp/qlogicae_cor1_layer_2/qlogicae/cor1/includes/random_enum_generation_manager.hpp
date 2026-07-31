#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RandomEnumGenerationManager \
	)

#include "random_seed_generation_manager.hpp"
#include "random_enum_generation_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		RandomEnumGenerationManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<RandomEnumGenerationManagerConfigurations>
    {
    public:
		RandomEnumGenerationManager();

		template <typename Type> Type
			generate_enum(
				const Type&
					minimum,
				const Type&
					maximum,
				const std::unordered_set<Type>&
					excluded
			);

		template <typename Type> Type
			generate_enum(
				const Type&
					minimum,
				const Type&
					maximum
			);

		template <typename Type> Type
			generate_enum(
				const Type&
					maximum,
				const std::unordered_set<Type>&
					excluded
			);

		template <typename Type> Type
			generate_enum(
				const Type&
					maximum
			);

		template <typename Type> Type
			generate_enum(
				const std::unordered_set<Type>&
					excluded
			);

		template <typename Type> Type
			generate_enum();
	};

	template <typename Type> Type
		RandomEnumGenerationManager
			::generate_enum(
				const Type&
					minimum,
				const Type&
					maximum,
				const std::unordered_set<Type>&
					excluded
				)
    {
        try
        {			
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				Type::NONE,
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			std::optional<std::underlying_type_t<Type>>
				last =
					std::nullopt;

			std::underlying_type_t<Type> min_value =
				static_cast<std::underlying_type_t<Type>>(
					minimum
				);

			std::underlying_type_t<Type> max_value =
				static_cast<std::underlying_type_t<Type>>(
					maximum
				);

			std::underlying_type_t<Type> next;

			if (!last.has_value())
			{
				next = min_value;

			}
			else
			{
				next = last.value() + 1;

				if (next > max_value)
				{
					next = min_value;
				}
			}

			std::underlying_type_t<Type> start = next;

			do
			{
				Type candidate = static_cast<Type>(next);
				if (excluded.find(candidate) == excluded.end())
				{
					last = next;

					return
						candidate;
				}

				next++;

				if (next > max_value)
				{
					next = min_value;
				}

			}
			while
			(
				next != start
			); 

			return
				Type::NONE;
        }
        catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				Type::NONE
			);
		}
	}    

	template <typename Type> Type
		RandomEnumGenerationManager
			::generate_enum(
				const Type&
					minimum,
				const Type&
					maximum
			)
    {
        return
			generate_enum<Type>(
				minimum,
				maximum,
				{}
			);
    }

    template <typename Type> Type
		RandomEnumGenerationManager
			::generate_enum(
				const Type&
					maximum,
				const std::unordered_set<Type>&
					excluded
			)
    {
        return
			generate_enum<Type>(
				static_cast<Type>(0),
				maximum,
				excluded
			);
    }

    template <typename Type> Type
		RandomEnumGenerationManager
			::generate_enum(
				const Type&
					maximum
			)
    {
        return
			generate_enum<Type>(
				static_cast<Type>(0),
				maximum,
				{}
			);
    }

    template <typename Type> Type
		RandomEnumGenerationManager
			::generate_enum(
				const std::unordered_set<Type>&
					excluded
			)
    {
        return
			generate_enum<Type>(
				static_cast<Type>(0),
				static_cast<Type>(Type::NONE),
				excluded
			);
    }

	template <typename Type> Type
		RandomEnumGenerationManager
			::generate_enum()
	{
		return
			generate_enum<Type>(
				static_cast<Type>(0),
				static_cast<Type>(Type::NONE),
				{}
			);
	}
}

#endif
