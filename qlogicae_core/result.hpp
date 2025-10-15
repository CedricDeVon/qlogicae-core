#pragma once

#include <string>

namespace QLogicaeCore
{   
    template <
        typename DataType = std::string
    >
    struct Result
    {
    public:
        bool get_is_successful();

        void get_is_successful(
            bool& value
        );
        
        std::string get_message();

        void get_message(
            std::string& value
        );

        DataType& get_data();

        void get_data(
            DataType& value
        );

        void set_is_successful(
            const bool& value
        );

        void set_is_successful_to_true();

        void set_is_successful_to_false();

        void set_data(
            const DataType& value
        );
        
        void set_data(
            DataType&& value
        );

        void set_message(
            const std::string& value
        );

        void set_to_success();

        void set_to_success(
            const DataType& value
        );

        void set_to_success(
            DataType&& value
        );

        void set_to_failure();

        void set_to_failure(
            const DataType& value
        );

        void set_to_failure(
            DataType&& value
        );

        void set_to_success_with_message(
            const std::string& message
        );

        void set_to_success_with_message(
            const DataType& value,
            const std::string& message
        );

        void set_to_success_with_message(
            DataType&& value,
            const std::string& message
        );

        void set_to_failure_with_message(
            const std::string& message
        );

        void set_to_failure_with_message(
            const DataType& value,
            const std::string& message
        );

        void set_to_failure_with_message(
            DataType&& value,
            const std::string& message
        );

    protected:
        DataType _data;

        bool _is_successful = true;

        std::string _message = "";
    };

    template <
        typename DataType
    >
    bool Result<DataType>::get_is_successful()
    {
        return _is_successful;
    }
    
    template <
        typename DataType
    >
    void Result<DataType>::get_is_successful(
        bool& value
    )
    {
        value = _is_successful;
    }

    template <
        typename DataType
    >
    DataType& Result<DataType>::get_data()
    {
        return _data;
    }

    template <
        typename DataType
    >
    void Result<DataType>::get_data(
        DataType& value
    )
    {
        value = _data;
    }

    template <
        typename DataType
    >
    std::string Result<DataType>::get_message()
    {
        return _message;
    }

    template <
        typename DataType
    >
    void Result<DataType>::get_message(
        std::string& value
    )
    {
        value = _message;
    }

    template <
        typename DataType
    >
    void Result<DataType>::set_is_successful(
        const bool& value
    )
    {
        _is_successful = value;
    }

    template <
        typename DataType
    >
    void Result<DataType>::set_is_successful_to_true()
    {
        _is_successful = true;
    }

    template <
        typename DataType
    >
    void Result<DataType>::set_is_successful_to_false()
    {
        _is_successful = false;
    }

    template <
        typename DataType
    >
    void Result<DataType>::set_data(
        const DataType& value
    )
    {
        _data = value;
    }

    template <
        typename DataType
    >
    void Result<DataType>::set_message(
        const std::string& value
    )
    {
        _message = value;
    }

    template <
        typename DataType
    >
    void Result<DataType>::set_to_success()
    {
        set_is_successful_to_true();
    }

    template <
        typename DataType
    >
    void Result<DataType>::set_to_success(
        const DataType& value
    )
    {
        set_is_successful_to_true();
        set_data(value);
    }

    template <
        typename DataType
    >
    void Result<DataType>::set_to_failure()
    {
        set_is_successful_to_false();
    }

    template <
        typename DataType
    >
    void Result<DataType>::set_to_failure(
        const DataType& value
    )
    {
        set_is_successful_to_false();
        set_data(value);
    }

    template <typename DataType>
    void Result<DataType>::set_data(
        DataType&& value
    )
    {
        _data = std::move(value);
    }

    template <typename DataType>
    void Result<DataType>::set_to_success(
        DataType&& value
    )
    {
        set_is_successful_to_true();
        set_data(std::move(value));
    }

    template <typename DataType>
    void Result<DataType>::set_to_failure(
        DataType&& value
    )
    {
        set_is_successful_to_false();
        set_data(std::move(value));
    }


    template <typename DataType>
    void Result<DataType>::set_to_success_with_message(
        const std::string& message
    )
    {
        set_is_successful_to_true();
        set_message(message);
    }

    template <typename DataType>
    void Result<DataType>::set_to_success_with_message(
        const DataType& value,
        const std::string& message
    )
    {
        set_is_successful_to_true();
        set_data(value);
        set_message(message);
    }

    template <typename DataType>
    void Result<DataType>::set_to_success_with_message(
        DataType&& value,
        const std::string& message
    )
    {
        set_is_successful_to_true();
        set_data(std::move(value));
        set_message(message);
    }

    template <typename DataType>
    void Result<DataType>::set_to_failure_with_message(
        const std::string& message
    )
    {
        set_is_successful_to_false();
        set_message(message);
    }

    template <typename DataType>
    void Result<DataType>::set_to_failure_with_message(
        const DataType& value,
        const std::string& message
    )
    {
        set_is_successful_to_false();
        set_data(value);
        set_message(message);
    }   

    template <typename DataType>
    void Result<DataType>::set_to_failure_with_message(
        DataType&& value,
        const std::string& message
    )
    {
        set_is_successful_to_false();
        set_data(std::move(value));
        set_message(message);
    }

    template <>
    struct Result<void>
    {
    public:
        bool get_is_successful() const;

        void get_is_successful(
            bool& value
        ) const;
        
        void set_is_successful(
            const bool& value
        );

        void set_message(
            const std::string& value
        );

        void set_is_successful_to_true();
        
        void set_is_successful_to_false();
        
        void set_to_success();

        void set_to_failure();

        void set_to_success_with_message(
            const std::string& message
        );

        void set_to_failure_with_message(
            const std::string& message
        );

    private:
        bool _is_successful = true;

        std::string _message = "";
    };

}
