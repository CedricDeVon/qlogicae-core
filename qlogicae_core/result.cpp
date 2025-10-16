#include "pch.hpp"

#include "result.hpp"

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
