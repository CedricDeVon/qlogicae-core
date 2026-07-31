#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		AbstractClass \
	)

#include "error_manager.hpp"
#include "singleton_manager.hpp"
#include "abstract_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    template <typename AbstractConfigurationsType> class
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME
    {
    public:
		QLOGICAE_COR1__INSTANCE__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1
		);

		AbstractConfigurationsType
			configurations;

		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME();

		~QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME();

        bool
            construct();

		bool
            destruct();

		virtual bool
            setup(
				const AbstractConfigurationsType&
					new_configurations
			);

		virtual bool
            reset();

		template <typename OutputType = bool> OutputType
			handle_error_outputs(
				const std::string&
					title,
				const std::string&
					message
			);

		template <typename OutputType = bool> OutputType
			handle_error_outputs(
				const std::string&
					message
			);

		template <typename OutputType = bool> OutputType
			handle_error_outputs(
				const std::exception&
					exception
			);

		template <typename OutputType = bool> OutputType
			handle_callback_wrapper(
				const std::function<void()>&
					callback
			);
    };

	template <typename AbstractConfigurationsType>
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<AbstractConfigurationsType>
			::QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME()
    {
		construct();
    }

	template <typename AbstractConfigurationsType>
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<AbstractConfigurationsType>
			::~QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME()
    {
		destruct();
    }

	template <typename AbstractConfigurationsType> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<AbstractConfigurationsType>
			::construct()
	{	
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	template <typename AbstractConfigurationsType> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<AbstractConfigurationsType>
			::destruct()
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	template <typename AbstractConfigurationsType> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<AbstractConfigurationsType>
			::setup(
				const AbstractConfigurationsType&
					new_configurations
			)
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			configurations =
				new_configurations;

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}

	template <typename AbstractConfigurationsType> bool
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<AbstractConfigurationsType>
			::reset()
	{
		try
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			configurations =
				{};

			return
				true;
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__IMPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE();
		}
	}
	
	template <typename AbstractConfigurationsType>
	template <typename OutputType> OutputType
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<AbstractConfigurationsType>
			::handle_error_outputs(
				const std::string&
					title,
				const std::string&
					message
			)
	{
		QLOGICAE_COR1__BASE__HPP_CPP__EDGE_CASE_GUARD_TEMPLATE
		(
			OutputType{},
			QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
		);
	
		QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<ErrorManager>()
			.handle_error_outputs<void>(
				title,
				message
			);

		return
			OutputType{};
	}

	template <typename AbstractConfigurationsType>
	template <typename OutputType> OutputType
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<AbstractConfigurationsType>
			::handle_error_outputs(
				const std::string&
					message
			)
	{	
		QLOGICAE_COR1__BASE__HPP_CPP__EDGE_CASE_GUARD_TEMPLATE
		(
			OutputType{},
			QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
		);
	
		QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<ErrorManager>()
			.handle_error_outputs<void>(
				message
			);

		return
			OutputType{};
	}

	template <typename AbstractConfigurationsType>
	template <typename OutputType> OutputType
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<AbstractConfigurationsType>
			::handle_error_outputs(
				const std::exception&
					QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_NAME
			)
	{
		QLOGICAE_COR1__BASE__HPP_CPP__EDGE_CASE_GUARD_TEMPLATE
		(
			OutputType{},
			QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
		);
	
		QLOGICAE_COR1__BASE__HPP_CPP__GET_SINGLETON_TEMPLATE<ErrorManager>()
			.handle_error_outputs<void>(
				QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_NAME
			);

		return
			OutputType{};
	}

	template <typename AbstractConfigurationsType>
	template <typename OutputType> OutputType
		QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<AbstractConfigurationsType>
			::handle_callback_wrapper(
				const std::function<void()>&
					callback
			)
	{		
		try
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__PRE_EXECUTION_GUARD_TEMPLATE
			(
				OutputType {},
				QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1,
				QLOGICAE_COR1__BASE__HPP_CPP__EMPTY_EDGE_CASES
			);

			callback();

			return
				OutputType {};
		}
		catch
		(
			QLOGICAE_COR1__BASE__HPP_CPP__TRY_CATCH_EXCEPTION_PARAMETER
		)
		{
			QLOGICAE_COR1__EXPLICIT__HPP_CPP__CATCH_CODE_TEMPLATE
			(
				OutputType {}
			);
		}	
	}
}

#endif
