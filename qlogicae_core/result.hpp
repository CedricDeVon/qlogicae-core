#pragma once

#include "result_status.hpp"

#include <string>

namespace QLogicaeCore
{
    template <
        typename ValueType = std::string
    >
    struct Result
    {
    public:
        ValueType& get_value();

        void get_value(
            ValueType& value
        );

        void set_value(
            const ValueType& value
        );

        void set_value(
            ValueType&& value
        );

        ResultStatus get_status();

        void get_status(
            ResultStatus& value
        );
        
        bool is_status(
            ResultStatus& status
        );

        void is_status(
            bool& value,
            ResultStatus& status
        );

        bool is_status_good();

        void is_status_good(
            bool& value
        );

        bool is_status_bad();

        void is_status_bad(
            bool& value
        );

        bool is_status_info();

        void is_status_info(
            bool& value
        );

        bool is_status_debug();

        void is_status_debug(
            bool& value
        );

        bool is_status_warning();

        void is_status_warning(
            bool& value
        );

        bool is_status_exception();

        void is_status_exception(
            bool& value
        );

        bool is_status_error();
        
        void is_status_error(
            bool& value
        );

        bool is_status_safe();

        void is_status_safe(
            bool& value
        );

        bool is_status_unsafe();

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

        std::string get_message();

        void get_message(
            std::string& value
        );

        void set_message(
            const std::string& value
        );

        void set_to_status_without_value(
            const ResultStatus& status
        );

        void set_to_status_without_value(
            const ResultStatus& status,
            const std::string& message
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
            const std::string& message
        );

        void set_to_status_with_value(
            const ResultStatus& status,
            ValueType&& value,
            const std::string& message
        );

        void set_to_good_status_without_value();

        void set_to_good_status_without_value(
            const std::string& message
        );

        void set_to_good_status_with_value(
            const ValueType& value
        );
        
        void set_to_good_status_with_value(
            ValueType&& value
        );

        void set_to_good_status_with_value(
            const ValueType& value,
            const std::string& message
        );

        void set_to_good_status_with_value(
            ValueType&& value,
            const std::string& message
        );

        void set_to_bad_status_without_value();

        void set_to_bad_status_without_value(
            const std::string& message
        );

        void set_to_bad_status_with_value(
            const ValueType& value
        );

        void set_to_bad_status_with_value(
            const ValueType& value,
            const std::string& message
        );

        void set_to_bad_status_with_value(
            ValueType&& value
        );
        
        void set_to_bad_status_with_value(
            ValueType&& value,
            const std::string& message
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
        ResultStatus get_status();

        void get_status(
            ResultStatus& value
        );

        bool is_status(
            ResultStatus& status
        );

        void is_status(
            bool& value,
            ResultStatus& status
        );

        bool is_status_good();

        void is_status_good(
            bool& value
        );

        bool is_status_bad();

        void is_status_bad(
            bool& value
        );

        bool is_status_info();

        void is_status_info(
            bool& value
        );

        bool is_status_debug();

        void is_status_debug(
            bool& value
        );

        bool is_status_warning();

        void is_status_warning(
            bool& value
        );

        bool is_status_exception();

        void is_status_exception(
            bool& value
        );

        bool is_status_error();

        void is_status_error(
            bool& value
        );

        bool is_status_safe();

        void is_status_safe(
            bool& value
        );

        bool is_status_unsafe();

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

        std::string get_message();

        void get_message(
            std::string& value
        );

        void set_message(
            const std::string& value
        );

        void set_to_status_without_value(
            const ResultStatus& status
        );

        void set_to_status_without_value(
            const ResultStatus& status,
            const std::string& message
        );

        void set_to_good_status_without_value();

        void set_to_good_status_without_value(
            const std::string& message
        );

        void set_to_bad_status_without_value();

        void set_to_bad_status_without_value(
            const std::string& message
        );

    protected:
        ResultStatus _status;

        std::string _message;
    };

    template <typename ValueType>
    ValueType& Result<ValueType>::get_value()
    {
        return _value;
    }

    template <typename ValueType>
    void Result<ValueType>::get_value(
        ValueType& value
    )
    {
        value = _value;
    }

    template <typename ValueType>
    bool Result<ValueType>::is_status(
        ResultStatus& status
    )
    {
        return _status == status;
    }

    template <typename ValueType>
    void Result<ValueType>::is_status(
        bool& value,
        ResultStatus& status
    )
    {
        value = (_status == status);
    }

    template <typename ValueType>
    bool Result<ValueType>::is_status_good()
    {
        return _status == ResultStatus::GOOD;
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_good(
        bool& value
    )
    {
        value = (_status == ResultStatus::GOOD);
    }

    template <typename ValueType>
    bool Result<ValueType>::is_status_bad()
    {
        return _status == ResultStatus::BAD;
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_bad(
        bool& value
    )
    {
        value = (_status == ResultStatus::BAD);
    }

    template <typename ValueType>
    bool Result<ValueType>::is_status_info()
    {
        return _status == ResultStatus::INFO;
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_info(
        bool& value
    )
    {
        value = (_status == ResultStatus::INFO);
    }

    template <typename ValueType>
    bool Result<ValueType>::is_status_debug()
    {
        return _status == ResultStatus::DEBUG;
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_debug(
        bool& value
    )
    {
        value = (_status == ResultStatus::DEBUG);
    }

    template <typename ValueType>
    bool Result<ValueType>::is_status_warning()
    {
        return _status == ResultStatus::WARNING;
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_warning(
        bool& value
    )
    {
        value = (_status == ResultStatus::WARNING);
    }

    template <typename ValueType>
    bool Result<ValueType>::is_status_exception()
    {
        return _status == ResultStatus::EXCEPTION;
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_exception(
        bool& value
    )
    {
        value = (_status == ResultStatus::EXCEPTION);
    }

    template <typename ValueType>
    bool Result<ValueType>::is_status_error()
    {
        return _status == ResultStatus::ERROR_;
    }

    template <typename ValueType>
    void Result<ValueType>::is_status_error(
        bool& value
    )
    {
        value = (_status == ResultStatus::ERROR_);
    }

    template <typename ValueType>
    bool Result<ValueType>::is_status_safe()
    {
        return (_status == ResultStatus::GOOD ||
            _status == ResultStatus::INFO ||
            _status == ResultStatus::DEBUG);
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
    bool Result<ValueType>::is_status_unsafe()
    {
        return (_status == ResultStatus::BAD ||
            _status == ResultStatus::WARNING ||
            _status == ResultStatus::ERROR_);
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
    ResultStatus Result<ValueType>::get_status()
    {
        return _status;
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
    void Result<ValueType>::set_status_to_good()
    {
        set_status(ResultStatus::GOOD);
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_bad()
    {
        set_status(ResultStatus::GOOD);
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_info()
    {
        set_status(ResultStatus::GOOD);
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_debug()
    {
        set_status(ResultStatus::GOOD);
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_warning()
    {
        set_status(ResultStatus::GOOD);
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_exception()
    {
        set_status(ResultStatus::GOOD);
    }

    template <typename ValueType>
    void Result<ValueType>::set_status_to_error()
    {
        set_status(ResultStatus::ERROR_);
    }

    template <typename ValueType>
    std::string Result<ValueType>::get_message()
    {
        return _message;
    }

    template <typename ValueType>
    void Result<ValueType>::get_message(
        std::string& value
    )
    {
        value = _message;
    }

    template <typename ValueType>
    void Result<ValueType>::set_message(
        const std::string& value
    )
    {
        _message = value;
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
        const std::string& message
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
        const std::string& message
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
        const std::string& message
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
        const std::string& message
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
        const std::string& message
    )
    {
        set_status_to_good();
        set_value(value);
        set_message(message);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_good_status_with_value(
        ValueType&& value,
        const std::string& message
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
        const std::string& message
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
        const std::string& message
    )
    {
        set_status_to_bad();
        set_value(value);
        set_message(message);
    }

    template <typename ValueType>
    void Result<ValueType>::set_to_bad_status_with_value(
        ValueType&& value,
        const std::string& message
    )
    {
        set_status_to_bad();
        set_value(std::move(value));
        set_message(message);
    } 
}
