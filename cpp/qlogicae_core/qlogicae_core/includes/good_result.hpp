#pragma once

#include "abstract_result.hpp"

namespace QLogicaeCore
{
    template <typename ValueType, typename MetaDataType = std::string>
    class GoodResult :
        public AbstractResult<ValueType, MetaDataType>
    {
    public:
        GoodResult(
            std::optional<ValueType> value= std::nullopt,
            std::optional<MetaDataType> metadata = std::nullopt
        );

        GoodResult(const GoodResult& good_result) = delete;

        GoodResult(GoodResult&& good_result) noexcept = default;

        GoodResult& operator=(const GoodResult& good_result) = delete;

        GoodResult& operator=(GoodResult&& good_result) noexcept = default;
    };

    template <typename ValueType, typename MetaDataType>
    QLogicaeCore::GoodResult<ValueType, MetaDataType>::GoodResult(
        std::optional<ValueType> value,
        std::optional<MetaDataType> metadata) :
            AbstractResult<ValueType, MetaDataType>(
                true, value, metadata
            )
    {

    }
}

