#include "pch.hpp"

#include "../includes/result.hpp"

#include <string>

namespace QLogicaeCore
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
    
    bool Result<void>::is_status(
        ResultStatus& status
    )
    {
        return _status == status;
    }

    void Result<void>::is_status(
        bool& value,
        ResultStatus& status
    )
    {
        value = (_status == status);
    }

    bool Result<void>::is_status_good()
    {
        return _status == ResultStatus::GOOD;
    }

    void Result<void>::is_status_good(
        bool& value
    )
    {
        value = (_status == ResultStatus::GOOD);
    }

    bool Result<void>::is_status_bad()
    {
        return _status == ResultStatus::BAD;
    }

    void Result<void>::is_status_bad(
        bool& value
    )
    {
        value = (_status == ResultStatus::BAD);
    }

    bool Result<void>::is_status_info()
    {
        return _status == ResultStatus::INFO;
    }

    void Result<void>::is_status_info(
        bool& value
    )
    {
        value = (_status == ResultStatus::INFO);
    }

    bool Result<void>::is_status_debug()
    {
        return _status == ResultStatus::DEBUG;
    }

    void Result<void>::is_status_debug(
        bool& value
    )
    {
        value = (_status == ResultStatus::DEBUG);
    }

    bool Result<void>::is_status_warning()
    {
        return _status == ResultStatus::WARNING;
    }

    void Result<void>::is_status_warning(
        bool& value
    )
    {
        value = (_status == ResultStatus::WARNING);
    }

    bool Result<void>::is_status_exception()
    {
        return _status == ResultStatus::EXCEPTION;
    }

    void Result<void>::is_status_exception(
        bool& value
    )
    {
        value = (_status == ResultStatus::EXCEPTION);
    }

    bool Result<void>::is_status_error()
    {
        return _status == ResultStatus::ERROR_;
    }

    void Result<void>::is_status_error(
        bool& value
    )
    {
        value = (_status == ResultStatus::ERROR_);
    }

    bool Result<void>::is_status_safe()
    {
        return (_status == ResultStatus::GOOD ||
            _status == ResultStatus::INFO ||
            _status == ResultStatus::DEBUG);
    }

    void Result<void>::is_status_safe(
        bool& value
    )
    {
        value = (_status == ResultStatus::GOOD ||
            _status == ResultStatus::INFO ||
            _status == ResultStatus::DEBUG);
    }

    bool Result<void>::is_status_unsafe()
    {
        return (_status == ResultStatus::BAD ||
            _status == ResultStatus::WARNING ||
            _status == ResultStatus::ERROR_);
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
        set_status(ResultStatus::GOOD);
    }
    
    void Result<void>::set_status_to_bad()
    {
        set_status(ResultStatus::GOOD);
    }
    
    void Result<void>::set_status_to_info()
    {
        set_status(ResultStatus::GOOD);
    }
    
    void Result<void>::set_status_to_debug()
    {
        set_status(ResultStatus::GOOD);
    }
    
    void Result<void>::set_status_to_warning()
    {
        set_status(ResultStatus::GOOD);
    }
    
    void Result<void>::set_status_to_exception()
    {
        set_status(ResultStatus::GOOD);
    }
    
    void Result<void>::set_status_to_error()
    {
        set_status(ResultStatus::ERROR_);
    }
    
    std::string Result<void>::get_message()
    {
        return _message;
    }
    
    void Result<void>::get_message(
        std::string& value
    )
    {
        value = _message;
    }
    
    void Result<void>::set_message(
        const std::string& value
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
        const std::string& message
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
        const std::string& message
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
        const std::string& message
    )
    {
        set_status_to_bad();
        set_message(message);
    }
}
