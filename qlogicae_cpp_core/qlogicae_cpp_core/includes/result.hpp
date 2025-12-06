#pragma once

#include "result_status.hpp"

#include <string>

namespace QLogicaeCppCore
{
    template <
        typename ValueType = std::string
    >
    struct Result
    {
    public:        
        void get_value(
            ValueType& value
        );

        void set_value(
            const ValueType& value
        );

        void set_value(
            ValueType&& value
        );

        void get_status(
            ResultStatus& value
        );

        void is_status(
            bool& value,
            const ResultStatus& status
        );

        void is_status_good(
            bool& value
        );

        void is_status_bad(
            bool& value
        );

        void is_status_info(
            bool& value
        );

        void is_status_debug(
            bool& value
        );

        void is_status_warning(
            bool& value
        );

        void is_status_exception(
            bool& value
        );
        
        void is_status_error(
            bool& value
        );

        void is_status_safe(
            bool& value
        );

        void is_status_unsafe(
            bool& value
        );

        void set_status(
            const ResultStatus& value
        );

        void set_status_to_good();

        void set_status_to_bad();

        void set_status_to_info();

        void set_status_to_debug();

        void set_status_to_warning();

        void set_status_to_exception();

        void set_status_to_error();

        void get_message(
            std::string_view& value
        );

        void set_message(
            const std::string_view& value
        );

        void set_to_status_without_value(
            const ResultStatus& status
        );

        void set_to_status_without_value(
            const ResultStatus& status,
            const std::string_view& message
        );

        void set_to_status_with_value(
            const ResultStatus& status,
            const ValueType& value
        );

        void set_to_status_with_value(
            const ResultStatus& status,
            ValueType&& value
        );

        void set_to_status_with_value(
            const ResultStatus& status,
            const ValueType& value,
            const std::string_view& message
        );

        void set_to_status_with_value(
            const ResultStatus& status,
            ValueType&& value,
            const std::string_view& message
        );

        void set_to_good_status_without_value();

        void set_to_good_status_without_value(
            const std::string_view& message
        );

        void set_to_good_status_with_value(
            const ValueType& value
        );

        void set_to_good_status_with_value(
            ValueType&& value
        );

        void set_to_good_status_with_value(
            const ValueType& value,
            const std::string_view& message
        );

        void set_to_good_status_with_value(
            ValueType&& value,
            const std::string_view& message
        );

        void set_to_bad_status_without_value();

        void set_to_bad_status_without_value(
            const std::string_view& message
        );

        void set_to_bad_status_with_value(
            const ValueType& value
        );

        void set_to_bad_status_with_value(
            const ValueType& value,
            const std::string_view& message
        );

        void set_to_bad_status_with_value(
            ValueType&& value
        );
        
        void set_to_bad_status_with_value(
            ValueType&& value,
            const std::string_view& message
        );

    protected:
        ValueType _value;

        ResultStatus _status;

        std::string _message;
    };

    template <>
    struct Result<void>
    {
    public:        
        void get_status(
            ResultStatus& value
        );

        bool is_status(
            const ResultStatus& status
        );

        void is_status(
            bool& value,
            const ResultStatus& status
        );

        void is_status_good(
            bool& value
        );

        void is_status_bad(
            bool& value
        );

        void is_status_info(
            bool& value
        );

        void is_status_debug(
            bool& value
        );

        void is_status_warning(
            bool& value
        );

        void is_status_exception(
            bool& value
        );

        void is_status_error(
            bool& value
        );

        void is_status_safe(
            bool& value
        );

        void is_status_unsafe(
            bool& value
        );

        void set_status(
            const ResultStatus& value
        );

        void set_status_to_good();

        void set_status_to_bad();

        void set_status_to_info();

        void set_status_to_debug();

        void set_status_to_warning();

        void set_status_to_exception();

        void set_status_to_error();

        void get_message(
            std::string_view& value
        );

        void set_message(
            const std::string_view& value
        );

        void set_to_status_without_value(
            const ResultStatus& status
        );

        void set_to_status_without_value(
            const ResultStatus& status,
            const std::string_view& message
        );

        void set_to_good_status_without_value();

        void set_to_good_status_without_value(
            const std::string_view& message
        );

        void set_to_bad_status_without_value();

        void set_to_bad_status_without_value(
            const std::string_view& message
        );

    protected:
        ResultStatus _status;

        std::string _message;
    };

    template <typename ValueType>
    void Result<ValueType>::get_value(
        ValueType& value
    )
    {
        value = _value;
    }

    template <typename ValueType>
    void Result<ValueType>::is_status(
        bool& value,
        const ResultStatus& status
    )
    {
        value = (_status == status);
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_good(
        bool& value
    )
    {
        value = (_status == ResultStatus::GOOD);
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_bad(
        bool& value
    )
    {
        value = (_status == ResultStatus::BAD);
    }
    
    template <typename ValueType>
    void Result<ValueType>::is_status_info(
        bool& value
    )
    {
        value = (_status == ResultStatus::INFO);
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_debug(
        bool& value
    )
    {
        value = (_status == ResultStatus::DEBUG);
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_warning(
        bool& value
    )
    {
        value = (_status == ResultStatus::WARNING);
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_exception(
        bool& value
    )
    {
        value = (_status == ResultStatus::EXCEPTION);
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_error(
        bool& value
    )
    {
        value = (_status == ResultStatus::ERROR_);
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_safe(
        bool& value
    )
    {
        value = (_status == ResultStatus::GOOD ||
            _status == ResultStatus::INFO ||
            _status == ResultStatus::DEBUG);
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_unsafe(
        bool& value
    )
    {
        value = (_status == ResultStatus::BAD ||
            _status == ResultStatus::WARNING ||
            _status == ResultStatus::ERROR_);
    }

    template <typename ValueType>
    void Result<ValueType>::set_value(
        const ValueType& value
    )
    {
        _value = value;
    }

    template <typename ValueType>
    void Result<ValueType>::set_value(
        ValueType&& value
    )
    {
        _value = std::move(value);
    }

    template <typename ValueType>
    void Result<ValueType>::get_status(
        ResultStatus& value
    )
    {
        value = _status;
    }

    template <typename ValueType>
    void Result<ValueType>::set_status(
        const ResultStatus& value
    )
    {
        _status = value;
    }

    template <typename ValueType>
    void QLogicaeCppCore::Result<ValueType>::set_message(
        const std::string_view& value
    )
    {
        _message = value;
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_good()
    {
        set_status(ResultStatus::GOOD);
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_bad()
    {
        set_status(ResultStatus::BAD);
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_info()
    {
        set_status(ResultStatus::INFO);
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_debug()
    {
        set_status(ResultStatus::DEBUG);
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_warning()
    {
        set_status(ResultStatus::WARNING);
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_exception()
    {
        set_status(ResultStatus::EXCEPTION);
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_error()
    {
        set_status(ResultStatus::ERROR_);
    }

    template <typename ValueType>
    void Result<ValueType>::get_message(
        std::string_view& value
    )
    {
        value = _message;
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_status_without_value(
        const ResultStatus& status
    )
    {
        set_status(status);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_status_without_value(
        const ResultStatus& status,
        const std::string_view& message
    )
    {
        set_status(status);
        set_message(message);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_status_with_value(
        const ResultStatus& status,
        const ValueType& value
    )
    {
        set_status(status);
        set_value(value);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_status_with_value(
        const ResultStatus& status,
        ValueType&& value
    )
    {
        set_status(status);
        set_value(std::move(value));
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_status_with_value(
        const ResultStatus& status,
        const ValueType& value,
        const std::string_view& message
    )
    {
        set_status(status);
        set_value(value);
        set_message(message);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_status_with_value(
        const ResultStatus& status,
        ValueType&& value,
        const std::string_view& message
    )
    {
        set_status(status);
        set_value(std::move(value));
        set_message(message);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_good_status_without_value()
    {
        set_status_to_good();
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_good_status_without_value(
        const std::string_view& message
    )
    {
        set_status_to_good();
        set_message(message);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_good_status_with_value(
        const ValueType& value
    )
    {
        set_status_to_good();
        set_value(value);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_good_status_with_value(
        ValueType&& value
    )
    {
        set_status_to_good();
        set_value(std::move(value));
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_good_status_with_value(
        const ValueType& value,
        const std::string_view& message
    )
    {
        set_status_to_good();
        set_value(value);
        set_message(message);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_good_status_with_value(
        ValueType&& value,
        const std::string_view& message
    )
    {
        set_status_to_good();
        set_value(std::move(value));
        set_message(message);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_bad_status_without_value()
    {
        set_status_to_bad();
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_bad_status_without_value(
        const std::string_view& message
    )
    {
        set_status_to_bad();
        set_message(message);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_bad_status_with_value(
        const ValueType& value
    )
    {
        set_status_to_bad();
        set_value(value);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_bad_status_with_value(
        ValueType&& value
    )
    {
        set_status_to_bad();
        set_value(std::move(value));
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_bad_status_with_value(
        const ValueType& value,
        const std::string_view& message
    )
    {
        set_status_to_bad();
        set_value(value);
        set_message(message);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_bad_status_with_value(
        ValueType&& value,
        const std::string_view& message
    )
    {
        set_status_to_bad();
        set_value(std::move(value));
        set_message(message);
    } 
}
