#pragma once

namespace QLogicaeCore
{
    template <typename ValueType,
        typename MetaDataType = std::string>
    class AbstractResult
    {
    public:
        virtual ~AbstractResult() = default;

        AbstractResult(
            const AbstractResult& abstract_result) = delete;

        AbstractResult(
            AbstractResult&& abstract_result) noexcept = default;

        AbstractResult& operator=(
            const AbstractResult& abstract_result) = delete;

        AbstractResult& operator=(
            AbstractResult&& abstract_result) noexcept = default;

        bool has_value() const;

        bool has_metadata() const;

        bool is_status_good() const;

        const std::optional<ValueType>& get_value() const;

        const std::optional<MetaDataType>& get_metadata() const;

    protected:
        const bool _state;
        const std::optional<ValueType> _value;
        const std::optional<MetaDataType> _metadata;

        AbstractResult(bool state = false,
            std::optional<ValueType> value = std::nullopt,
            std::optional<MetaDataType> metadata = std::nullopt
        );
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
    bool AbstractResult<ValueType, MetaDataType>::is_status_good() const
    {
        return _state;
    }

    template <typename ValueType, typename MetaDataType>
    bool AbstractResult<ValueType, MetaDataType>::has_value() const
    {
        return _value.has_value();
    }

    template <typename ValueType, typename MetaDataType>
    bool AbstractResult<ValueType, MetaDataType>::has_metadata() const
    {
        return _metadata.has_value();
    }

    template <typename ValueType, typename MetaDataType>
    const std::optional<ValueType>&
        AbstractResult<ValueType, MetaDataType>::get_value() const
    {
        return _value;
    }

    template <typename ValueType, typename MetaDataType>
    const std::optional<MetaDataType>&
        AbstractResult<ValueType, MetaDataType>::get_metadata() const
    {
        return _metadata;
    }
}
