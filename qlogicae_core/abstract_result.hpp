#pragma once

namespace QLogicaeCore
{    
    template <typename ValueType,
        typename MetaDataType = std::string>
    class AbstractResult
    {
    public:
        virtual ~AbstractResult() = default;
        
        AbstractResult(bool state = false,
            std::optional<ValueType> value = std::nullopt,
            std::optional<MetaDataType> metadata = std::nullopt
        );

        AbstractResult(
            const AbstractResult& instance
        ) = delete;

        AbstractResult(
            AbstractResult&& instance
        ) noexcept = default;

        AbstractResult& operator=(
            const AbstractResult& instance
        ) = delete;

        AbstractResult& operator=(
            AbstractResult&& instance
        ) noexcept = default;

        bool has_value();

        bool has_metadata();

        bool is_status_good();

        const std::optional<ValueType>& get_value();

        const std::optional<MetaDataType>& get_metadata();

    protected:
        const bool _state;

        const std::optional<ValueType> _value;

        const std::optional<MetaDataType> _metadata;        
    };

    template <typename ValueType, typename MetaDataType>
    AbstractResult<ValueType, MetaDataType>::AbstractResult(
        bool state,
        std::optional<ValueType> value,
        std::optional<MetaDataType> metadata) :
            _state(state),
            _value(std::move(value)),
            _metadata(std::move(metadata))
    {
    }

    template <typename ValueType, typename MetaDataType>
    bool AbstractResult<ValueType, MetaDataType>::is_status_good()
    {
        return _state;
    }

    template <typename ValueType, typename MetaDataType>
    bool AbstractResult<ValueType, MetaDataType>::has_value()
    {
        return _value.has_value();
    }

    template <typename ValueType, typename MetaDataType>
    bool AbstractResult<ValueType, MetaDataType>::has_metadata()
    {
        return _metadata.has_value();
    }

    template <typename ValueType, typename MetaDataType>
    const std::optional<ValueType>&
        AbstractResult<ValueType, MetaDataType>::get_value()
    {
        return _value;
    }

    template <typename ValueType, typename MetaDataType>
    const std::optional<MetaDataType>&
        AbstractResult<ValueType, MetaDataType>::get_metadata()
    {
        return _metadata;
    }
}