#include "pch.hpp"

#include "../includes/result.hpp"

#include <string>

namespace QLogicaeCppCore
{            
    ResultStatus Result<void>::get_status()
    {
        return _status;
    }

    void Result<void>::get_status(
        ResultStatus& value
    )
    {
        value = _status;
    }
    
    void Result<void>::set_status(
        const ResultStatus& value
    )
    {
        _status = value;
    }    

    void Result<void>::is_status(
        bool& value,
        const ResultStatus& status
    )
    {
        value = (_status == status);
    }

    void Result<void>::is_status_good(
        bool& value
    )
    {
        value = (_status == ResultStatus::GOOD);
    }

    void Result<void>::is_status_bad(
        bool& value
    )
    {
        value = (_status == ResultStatus::BAD);
    }

    void Result<void>::is_status_info(
        bool& value
    )
    {
        value = (_status == ResultStatus::INFO);
    }

    void Result<void>::is_status_debug(
        bool& value
    )
    {
        value = (_status == ResultStatus::DEBUG);
    }

    void Result<void>::is_status_warning(
        bool& value
    )
    {
        value = (_status == ResultStatus::WARNING);
    }

    void Result<void>::is_status_exception(
        bool& value
    )
    {
        value = (_status == ResultStatus::EXCEPTION);
    }

    void Result<void>::is_status_error(
        bool& value
    )
    {
        value = (_status == ResultStatus::ERROR_);
    }

    void Result<void>::is_status_safe(
        bool& value
    )
    {
        value = (_status == ResultStatus::GOOD ||
            _status == ResultStatus::INFO ||
            _status == ResultStatus::DEBUG);
    }

    void Result<void>::is_status_unsafe(
        bool& value
    )
    {
        value = (_status == ResultStatus::BAD ||
            _status == ResultStatus::WARNING ||
            _status == ResultStatus::ERROR_);
    }

    void Result<void>::set_status_to_good()
    {
        _status = ResultStatus::GOOD;
    }

    void Result<void>::set_status_to_bad()
    {
        _status = ResultStatus::BAD;
    }

    void Result<void>::set_status_to_info()
    {
        _status = ResultStatus::INFO;
    }

    void Result<void>::set_status_to_debug()
    {
        _status = ResultStatus::DEBUG;
    }

    void Result<void>::set_status_to_warning()
    {
        _status = ResultStatus::WARNING;
    }

    void Result<void>::set_status_to_exception()
    {
        _status = ResultStatus::EXCEPTION;
    }

    void Result<void>::set_status_to_error()
    {
        _status = ResultStatus::ERROR_;
    }

    std::string Result<void>::get_message()
    {
        return _message;
    }

    void Result<void>::get_message(
        std::string_view& value
    )
    {
        value = _message;
    }
    
    void Result<void>::set_message(
        const std::string_view& value
    )
    {
        _message = value;
    }
    
    void Result<void>::set_to_status_without_value(
        const ResultStatus& status
    )
    {
        set_status(status);
    }
    
    void Result<void>::set_to_status_without_value(
        const ResultStatus& status,
        const std::string_view& message
    )
    {
        set_status(status);
        set_message(message);
    }

    
    void Result<void>::set_to_good_status_without_value()
    {
        set_status_to_good();
    }
    
    void Result<void>::set_to_good_status_without_value(
        const std::string_view& message
    )
    {
        set_status_to_good();
        set_message(message);
    }

    
    void Result<void>::set_to_bad_status_without_value()
    {
        set_status_to_bad();
    }
    
    void Result<void>::set_to_bad_status_without_value(
        const std::string_view& message
    )
    {
        set_status_to_bad();
        set_message(message);
    }
}
