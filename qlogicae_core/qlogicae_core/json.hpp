#pragma once

#include "json_value.hpp"

#include <cstdint>

namespace QLogicaeCore
{
	struct Json;

    using JsonValuePointer =
        std::shared_ptr<Json>;

    using JsonValue = std::variant<
        std::nullptr_t,
        bool,
        int64_t,
        uint64_t,
        double,
        std::string,
        std::vector<JsonValuePointer>,
        std::map<std::string, JsonValuePointer>
    >;

    struct Json
    {
        JsonValue value;
        
        using Array =
            std::vector<JsonValuePointer>;

        using Object =
            std::map<std::string, JsonValuePointer>;
    };

    using JsonKey =
        std::variant<std::string_view, int>;

    using JsonPath =
        std::vector<JsonKey>;
}
