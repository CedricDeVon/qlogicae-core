#pragma once

namespace QLogicaeCore
{   
    template <
        typename DataType = std::string
    >
    struct Result
    {
    public:
        bool get_is_successful();

        DataType& get_data();

        void set_is_successful_to_true();

        void set_is_successful_to_false();

        void set_data(
            const DataType& value
        );

        void set_to_success();

        void set_to_success(
            const DataType& value
        );

        void set_to_failure();

        void set_to_failure(
            const DataType& value
        );

    private:
        bool _is_successful = true;

        DataType _data;
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
    DataType& Result<DataType>::get_data()
    {
        return _data;
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
}
