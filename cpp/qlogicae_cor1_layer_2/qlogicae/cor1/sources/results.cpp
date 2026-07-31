#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Results \
	)

#include "../includes/results.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{            
    ResultsStatus
        Results<void>
			::get_status()
    {
        return _status;
    }

    void
        Results<void>
			::get_status(
				ResultsStatus&
					value
			)
    {
        value = _status;
    }

    void
        Results<void>
			::set_status(
				const ResultsStatus&
					value
			)
    {
        _status = value;
    }

    bool
        Results<void>
			::is_status(
				const ResultsStatus&
					status
			)
    {
        return _status == status;
    }

    void
        Results<void>
			::is_status(
				bool&
					value,
				const ResultsStatus&
					status
			)
    {
        value = (_status == status);
    }

    bool
        Results<void>
			::is_status_good()
    {
        return _status == ResultsStatus::GOOD;
    }

    void
        Results<void>
			::is_status_good(
				bool&
					value
			)
    {
        value = (_status == ResultsStatus::GOOD);
    }

    bool
        Results<void>
			::is_status_bad()
    {
        return _status == ResultsStatus::BAD;
    }

    void
        Results<void>
			::is_status_bad(
				bool&
					value
			)
    {
        value = (_status == ResultsStatus::BAD);
    }

    bool
        Results<void>
			::is_status_info()
    {
        return _status == ResultsStatus::INFO;
    }

    void
        Results<void>
			::is_status_info(
				bool& value
			)
    {
        value = (_status == ResultsStatus::INFO);
    }

    bool
        Results<void>
			::is_status_debug()
    {
        return _status == ResultsStatus::DEBUG;
    }

    void
        Results<void>
			::is_status_debug(
				bool& value
			)
    {
        value = (_status == ResultsStatus::DEBUG);
    }

    bool
        Results<void>
			::is_status_warning()
    {
        return _status == ResultsStatus::WARNING;
    }

    void
        Results<void>
			::is_status_warning(
				bool&
					value
			)
    {
        value = (_status == ResultsStatus::WARNING);
    }

    bool
        Results<void>
			::is_status_exception()
    {
        return _status == ResultsStatus::EXCEPTION;
    }

    void
        Results<void>
			::is_status_exception(
				bool&
					value
			)
    {
        value = (_status == ResultsStatus::EXCEPTION);
    }

    bool
        Results<void>
			::is_status_error()
    {
        return _status == ResultsStatus::ERROR_TYPE;
    }

    void
        Results<void>
			::is_status_error(
				bool&
					value
			)
    {
        value = (_status == ResultsStatus::ERROR_TYPE);
    }

    bool
        Results<void>
			::is_status_safe()
    {
        return (_status == ResultsStatus::GOOD ||
            _status == ResultsStatus::INFO ||
            _status == ResultsStatus::DEBUG);
    }

    void
        Results<void>
			::is_status_safe(
				bool&
					value
			)
    {
        value = (_status == ResultsStatus::GOOD ||
            _status == ResultsStatus::INFO ||
            _status == ResultsStatus::DEBUG);
    }

    bool
        Results<void>
			::is_status_unsafe()
    {
        return (_status == ResultsStatus::BAD ||
            _status == ResultsStatus::WARNING ||
            _status == ResultsStatus::EXCEPTION ||
            _status == ResultsStatus::ERROR_TYPE);
    }

    void
        Results<void>
			::is_status_unsafe(
				bool&
					value
			)
    {
        value = (_status == ResultsStatus::BAD ||
            _status == ResultsStatus::WARNING ||
            _status == ResultsStatus::EXCEPTION ||
            _status == ResultsStatus::ERROR_TYPE);
    }

    void
        Results<void>
			::set_status_to_good()
    {
        set_status(ResultsStatus::GOOD);
    }

    void
        Results<void>
			::set_status_to_bad()
    {
        set_status(ResultsStatus::BAD);
    }

    void
        Results<void>
			::set_status_to_info()
    {
        set_status(ResultsStatus::INFO);
    }

    void
        Results<void>
			::set_status_to_debug()
    {
        set_status(ResultsStatus::DEBUG);
    }

    void
        Results<void>
			::set_status_to_warning()
    {
        set_status(ResultsStatus::WARNING);
    }

    void
        Results<void>
			::set_status_to_exception()
    {
        set_status(ResultsStatus::EXCEPTION);
    }

    void
        Results<void>
			::set_status_to_error()
    {
        set_status(ResultsStatus::ERROR_TYPE);
    }

    std::string
        Results<void>
			::get_message()
    {
        return _message;
    }

    void
        Results<void>
			::get_message(
				std::string_view&
					value
			)
    {
        value = _message;
    }

    void
        Results<void>
			::set_message(
				const std::string_view&
					value
			)
    {
        _message = value;
    }

    void
        Results<void>
			::set_to_status_without_value(
				const ResultsStatus&
					status
			)
    {
        set_status(status);
    }

    void
        Results<void>
			::set_to_status_without_value(
				const ResultsStatus&
					status,
				const std::string_view&
					message
			)
    {
        set_status(status);
        set_message(message);
    }

    void
        Results<void>
			::set_to_good_status_without_value()
    {
        set_status_to_good();
    }

    void
        Results<void>
			::set_to_good_status_without_value(
				const std::string_view&
					message
			)
    {
        set_status_to_good();
        set_message(message);
    }

    void
        Results<void>
			::set_to_bad_status_without_value()
    {
        set_status_to_bad();
    }

    void
        Results<void>
			::set_to_bad_status_without_value(
				const std::string_view&
					message
			)
    {
        set_status_to_bad();
        set_message(message);
    }
}

#endif
