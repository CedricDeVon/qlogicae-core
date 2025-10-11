#include "pch.hpp"

#include "json_visitor.hpp"

namespace QLogicaeCore
{
	bool convert_to_rapidjson_value(
		const Json& source,
		rapidjson::Value& target,
		rapidjson::Document::AllocatorType& allocator)
	{
		std::visit(JsonVisitor{ target, allocator }, source.value);

		return true;
	}
}
