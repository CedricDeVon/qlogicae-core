#pragma once

#include "pch.h"

#include "abstract_result.hpp"

namespace QLogicaeCore
{
    template <typename ValueType, typename MetaDataType = std::string>
    class GoodResult : public AbstractResult<ValueType, MetaDataType>
    {
    public:
        GoodResult(
            std::optional<ValueType> = std::nullopt,
            std::optional<MetaDataType> = std::nullopt
        );

        GoodResult(const GoodResult&) = delete;
        GoodResult(GoodResult&&) noexcept = default;
        GoodResult& operator=(const GoodResult&) = delete;
        GoodResult& operator=(GoodResult&&) noexcept = default;
    };

    template <typename ValueType, typename MetaDataType>
    QLogicaeCore::GoodResult<ValueType, MetaDataType>::GoodResult(
        std::optional<ValueType> value,
        std::optional<MetaDataType> metadata) :
            AbstractResult<ValueType, MetaDataType>(true, value, metadata)
    {
    }
}
