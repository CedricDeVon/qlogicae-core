#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Results \
	)

#include "results_status.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    template <typename ValueType = std::string> struct
        Results
    {
    public:        
        ValueType&
            get_value();

        void
            get_value(
                ValueType&
                    value
            );

        void
            get_value( 
                ValueType&&
                    value
            );

        void
            set_value(
                const ValueType&
                    value
            );

        void
            set_value(
                ValueType&&
                    value
            );

        ResultsStatus
            get_status();

        void
            get_status(
                ResultsStatus&
                    value
            );

        bool
            is_status(
                const ResultsStatus&
                    status
            );

        void
            is_status(
                bool&
                    value,
                const ResultsStatus&
                    status
            );

        bool
            is_status_good();

        void
            is_status_good(
                bool&
                    value
        );

        bool
            is_status_bad();
        
        void
            is_status_bad(
                bool&
                    value
            );

        bool
            is_status_info();
        
        void
            is_status_info(
                bool&
                    value
            );

        bool
            is_status_debug();
        
        void
            is_status_debug(
                bool&
                    value
            );

        bool
            is_status_warning();
        
        void
            is_status_warning(
                bool&
                    value
            );
        
        bool
            is_status_exception();

        void
            is_status_exception(
                bool&
                    value
            );

        bool
            is_status_error();
        
        void
            is_status_error(
                bool&
                    value
            );

        bool
            is_status_safe();

        void
            is_status_safe(
                bool&
                    value
            );
        
        bool
            is_status_unsafe();

        void
            is_status_unsafe(
                bool&
                    value
            );

        void
            set_status(
                const ResultsStatus&
                value
            );

        void
            set_status_to_good();

        void
            set_status_to_bad();

        void
            set_status_to_info();

        void
            set_status_to_debug();

        void
            set_status_to_warning();

        void
            set_status_to_exception();

        void
            set_status_to_error();

        void
            set_to_status_without_value(
                const ResultsStatus&
                    status
            );

        void
            set_to_status_without_value(
                const ResultsStatus&
                    status,
                const std::string_view&
                    message
            );

        void
            set_to_status_with_value(
                const ResultsStatus&
                    status,
                const ValueType&
                    value
            );

        void
            set_to_status_with_value(
                const ResultsStatus&
                    status,
                ValueType&&
                    value
            );

        void
            set_to_status_with_value(
                const ResultsStatus&
                    status,
                const ValueType&
                    value,
                const std::string_view&
                    message
            );

        void
            set_to_status_with_value(
                const ResultsStatus&
                    status,
                ValueType&&
                    value,
                const std::string_view&
                    message
            );

        void
            set_to_good_status_without_value();

        void
            set_to_good_status_without_value(
                const std::string_view&
                    message
            );

        void
            set_to_good_status_with_value(
                const ValueType& value
            );

        void
            set_to_good_status_with_value(
                ValueType&& value
            );

        void
            set_to_good_status_with_value(
                const ValueType&
                    value,
                const std::string_view&
                    message
            );

        void
            set_to_good_status_with_value(
                ValueType&&
                    value,
                const std::string_view&
                    message
            );

        void
            set_to_bad_status_without_value();

        void
            set_to_bad_status_without_value(
                const std::string_view&
                    message
            );

        void
            set_to_bad_status_with_value(
                const ValueType&
                    value
            );

        void
            set_to_bad_status_with_value(
                const ValueType&
                    value,
                const std::string_view&
                    message
            );

        void
            set_to_bad_status_with_value(
                ValueType&&
                    value
            );
        
        void
            set_to_bad_status_with_value(
                ValueType&&
                    value,
                const std::string_view&
                    message
            );

        std::string
            get_message();

        void
            get_message(
                std::string_view&
                    value
            );

        void
            set_message(
                const std::string_view&
                    value
            );

        ValueType
            _value;

        ResultsStatus
            _status;

        std::string
            _message;
    };

    template <> struct
        Results<void>
    {
    public:
        ResultsStatus
            get_status();

        void
            get_status(
                ResultsStatus&                                    
                    value
            );  

        bool
            is_status(
                const ResultsStatus&
                    status
            );

        void
            is_status(
                bool& 
                    value,
                const ResultsStatus&
                    status
            );  

        bool
            is_status_good();

        void
            is_status_good(
                bool& 
                    value
            );

        bool
            is_status_bad();

        void
            is_status_bad(
                bool& 
                    value
            );

        bool
            is_status_info();

        void
            is_status_info(
                bool& 
                    value
            );

        bool
            is_status_debug();

        void
            is_status_debug(
                bool& 
                    value
            );

        bool
            is_status_warning();

        void
            is_status_warning(
                bool& 
                    value
            );

        bool
            is_status_exception();

        void
            is_status_exception(
                bool& 
                    value
            );

        bool
            is_status_error();

        void
            is_status_error(
                bool& 
                    value
            );

        bool
            is_status_safe();

        void
            is_status_safe(
                bool& 
                    value
            );

        bool
            is_status_unsafe();

        void
            is_status_unsafe(
                bool& 
                    value
            );

        void
            set_status(
                const ResultsStatus&                                    
                    value
        );

        void
            set_status_to_good();

        void
            set_status_to_bad();

        void
            set_status_to_info();

        void
            set_status_to_debug();

        void
            set_status_to_warning();

        void
            set_status_to_exception();

        void
            set_status_to_error();

        std::string
            get_message();

        void
            get_message(
                std::string_view& 
                    value
            );

        void
            set_message(
                const std::string_view& 
                    value
            );

        void
            set_to_status_without_value(
                const ResultsStatus&
                    status
            );

        void
            set_to_status_without_value(
                const ResultsStatus&
                    status,
                const std::string_view&
                    message
            );

        void
            set_to_good_status_without_value();

        void
            set_to_good_status_without_value(
                const std::string_view&
                    message
            );

        void
            set_to_bad_status_without_value();

        void
            set_to_bad_status_without_value(
                const std::string_view&
                    message
            );

        ResultsStatus
            _status;

        std::string
            _message;
    };

    template <typename ValueType> ValueType&
        Results<ValueType>::get_value()
    {
        return _value;
    }

    template <typename ValueType> void
        Results<ValueType>::get_value(
            ValueType&
                value
        )
    {
        value = _value;
    }

    template <typename ValueType> void
        Results<ValueType>::get_value(
            ValueType&&
                value
        )
    {
        value = std::move(_value);
    }

    template <typename ValueType> bool
        Results<ValueType>::is_status(
            const ResultsStatus&
                status
        )
    {
        return _status == status;
    }
    
    template <typename ValueType> void
        Results<ValueType>::is_status(
            bool&
                value,
            const ResultsStatus&
                status
        )
    {
        value = (_status == status);
    }

    template <typename ValueType> bool
        Results<ValueType>::is_status_good()
    {
        return _status == ResultsStatus::GOOD;
    }

    template <typename ValueType> bool
        Results<ValueType>::is_status_bad()
    {
        return _status == ResultsStatus::BAD;
    }

    template <typename ValueType> bool
        Results<ValueType>::is_status_info()
    {
        return _status == ResultsStatus::INFO;
    }

    template <typename ValueType> bool
        Results<ValueType>::is_status_debug()
    {
        return _status == ResultsStatus::DEBUG;
    }

    template <typename ValueType> bool
        Results<ValueType>::is_status_warning()
    {
        return _status == ResultsStatus::WARNING;
    }

    template <typename ValueType> bool
        Results<ValueType>::is_status_exception()
    {
        return _status == ResultsStatus::EXCEPTION;
    }

    template <typename ValueType> bool
        Results<ValueType>::is_status_error()
    {
        return _status == ResultsStatus::ERROR_TYPE;
    }

    template <typename ValueType> bool
        Results<ValueType>::is_status_safe()
    {
        return _status == ResultsStatus::GOOD ||
            _status == ResultsStatus::INFO ||
            _status == ResultsStatus::DEBUG;
    }

    template <typename ValueType> bool
        Results<ValueType>::is_status_unsafe()
    {
        return _status == ResultsStatus::BAD ||
            _status == ResultsStatus::WARNING ||
            _status == ResultsStatus::ERROR_TYPE;
    }

    template <typename ValueType> void
        Results<ValueType>::is_status_good(
            bool&
                value
        )
    {
        value = (_status == ResultsStatus::GOOD);
    }

    template <typename ValueType> void
        Results<ValueType>::is_status_bad(
        bool&
            value
    )
    {
        value = (_status == ResultsStatus::BAD);
    }
    
    template <typename ValueType> void
        Results<ValueType>::is_status_info(
            bool&
                value
        )
    {
        value = (_status == ResultsStatus::INFO);
    }

    template <typename ValueType> void
        Results<ValueType>::is_status_debug(
            bool&
                value
        )
    {
        value = (_status == ResultsStatus::DEBUG);
    }

    template <typename ValueType> void
        Results<ValueType>::is_status_warning(
            bool&
                value
        )
    {
        value = (_status == ResultsStatus::WARNING);
    }

    template <typename ValueType> void
        Results<ValueType>::is_status_exception(
            bool&
                value
        )
    {
        value = (_status == ResultsStatus::EXCEPTION);
    }

    template <typename ValueType> void
        Results<ValueType>::is_status_error(
            bool&
                value
        )
    {
        value = (_status == ResultsStatus::ERROR_TYPE);
    }

    template <typename ValueType> void
        Results<ValueType>::is_status_safe(
            bool&
                value
        )
    {
        value = (_status == ResultsStatus::GOOD ||
            _status == ResultsStatus::INFO ||
            _status == ResultsStatus::DEBUG);
    }

    template <typename ValueType> void
        Results<ValueType>::is_status_unsafe(
            bool&
                value
        )
    {
        value = (_status == ResultsStatus::BAD ||
            _status == ResultsStatus::WARNING ||
            _status == ResultsStatus::ERROR_TYPE);
    }

    template <typename ValueType> void
        Results<ValueType>::set_value(
            const ValueType&
                value
        )
    {
        _value = value;
    }

    template <typename ValueType> void
        Results<ValueType>::set_value(
            ValueType&&
                value
        )
    {
        _value = std::move(value);
    }

    template <typename ValueType>
        ResultsStatus
            Results<ValueType>::get_status()
    {
        return _status;
    }

    template <typename ValueType> void
        Results<ValueType>::get_status(
            ResultsStatus&
                value
        )
    {
        value = _status;
    }

    template <typename ValueType> void
        Results<ValueType>::set_status(
            const ResultsStatus&
                value
        )
    {
        _status = value;
    }

    template <typename ValueType> void
		Results<ValueType>::set_message(
			const std::string_view&
				value
		)
    {
        _message = value;
    }

    template <typename ValueType> void
        Results<ValueType>::set_status_to_good()
    {
        set_status(ResultsStatus::GOOD);
    }

    template <typename ValueType> void
        Results<ValueType>::set_status_to_bad()
    {
        set_status(ResultsStatus::BAD);
    }

    template <typename ValueType> void
        Results<ValueType>::set_status_to_info()
    {
        set_status(ResultsStatus::INFO);
    }

    template <typename ValueType> void
        Results<ValueType>::set_status_to_debug()
    {
        set_status(ResultsStatus::DEBUG);
    }

    template <typename ValueType> void
        Results<ValueType>::set_status_to_warning()
    {
        set_status(ResultsStatus::WARNING);
    }

    template <typename ValueType> void
        Results<ValueType>::set_status_to_exception()
    {
        set_status(ResultsStatus::EXCEPTION);
    }

    template <typename ValueType> void
        Results<ValueType>::set_status_to_error()
    {
        set_status(ResultsStatus::ERROR_TYPE);
    }

    template <typename ValueType>
        std::string Results<ValueType>::get_message()
    {
        return _message;
    }

    template <typename ValueType> void
        Results<ValueType>::get_message(
            std::string_view&
                value
        )
    {
        value = _message;
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_status_without_value(
            const ResultsStatus&
                status
        )
    {
        set_status(status);
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_status_without_value(
            const ResultsStatus&
                status,
            const std::string_view&
                message
        )
    {
        set_status(status);
        set_message(message);
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_status_with_value(
            const ResultsStatus&
                status,
            const ValueType&
                value
        )
    {
        set_status(status);
        set_value(value);
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_status_with_value(
            const ResultsStatus&
                status,
            ValueType&&
                value
        )
    {
        set_status(status);
        set_value(std::move(value));
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_status_with_value(
            const ResultsStatus&
                status,
            const ValueType&
                value,
            const std::string_view&
                message
        )
    {
        set_status(status);
        set_value(value);
        set_message(message);
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_status_with_value(
            const ResultsStatus&
                status,
            ValueType&&
                value,
            const std::string_view&
                message
        )
    {
        set_status(status);
        set_value(std::move(value));
        set_message(message);
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_good_status_without_value()
    {
        set_status_to_good();
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_good_status_without_value(
            const std::string_view&
                message
        )
    {
        set_status_to_good();
        set_message(message);
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_good_status_with_value(
           const ValueType&
                value
        )
    {
        set_status_to_good();
        set_value(value);
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_good_status_with_value(
            ValueType&&
                value
        )
    {
        set_status_to_good();
        set_value(std::move(value));
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_good_status_with_value(
            const ValueType&
                value,
            const std::string_view&
                message
        )
    {
        set_status_to_good();
        set_value(value);
        set_message(message);
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_good_status_with_value(
            ValueType&&
                value,
            const std::string_view&
                message
        )
    {
        set_status_to_good();
        set_value(std::move(value));
        set_message(message);
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_bad_status_without_value()
    {
        set_status_to_bad();
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_bad_status_without_value(
            const std::string_view&
                message
        )
    {
        set_status_to_bad();
        set_message(message);
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_bad_status_with_value(
            const ValueType&
                value
        )
    {
        set_status_to_bad();
        set_value(value);
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_bad_status_with_value(
            ValueType&&
                value
        )
    {
        set_status_to_bad();
        set_value(std::move(value));
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_bad_status_with_value(
            const ValueType&
                value,
            const std::string_view&
                message
        )
    {
        set_status_to_bad();
        set_value(value);
        set_message(message);
    }

    template <typename ValueType> void
        Results<ValueType>::set_to_bad_status_with_value(
            ValueType&&
                value,
            const std::string_view&
                message
        )
    {
        set_status_to_bad();
        set_value(std::move(value));
        set_message(message);
    } 
}

#endif
