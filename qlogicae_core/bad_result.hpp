#pragma once

#include "abstract_result.hpp"

namespace QLogicaeCore
{
    template <
        typename ValueType,
        typename MetaDataType = std::string>
    class BadResult :
        public AbstractResult<ValueType, MetaDataType>
    {
    public:
        BadResult(
            std::optional<ValueType> value = std::nullopt,
            std::optional<MetaDataType> metadata = std::nullopt
        );

        BadResult(const BadResult& bad_result) = delete;

        BadResult(BadResult&& bad_result) noexcept = default;

        BadResult& operator=(const BadResult& bad_result) = delete;

        BadResult& operator=(BadResult&& bad_result) noexcept = default;
    };

    template <typename ValueType, typename MetaDataType>
    QLogicaeCore::BadResult<ValueType, MetaDataType>::BadResult(
        std::optional<ValueType> value,
        std::optional<MetaDataType> metadata) :
            AbstractResult<ValueType, MetaDataType>(false, value, metadata)
    {

    }
}

