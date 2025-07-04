#pragma once

#include "pch.h"

#include "abstract_result.hpp"

namespace QLogicaeCore
{
    template <typename ValueType, typename MetaDataType = std::string>
    class BadResult : public AbstractResult<ValueType, MetaDataType>
    {
    public:
        BadResult(
            std::optional<ValueType> = std::nullopt,
            std::optional<MetaDataType> = std::nullopt
        );
    };

    template <typename ValueType, typename MetaDataType>
    QLogicaeCore::BadResult<ValueType, MetaDataType>::BadResult(
        std::optional<ValueType> value,
        std::optional<MetaDataType> metadata) :
            AbstractResult<ValueType, MetaDataType>(false, value, metadata)
    {

    }
}

