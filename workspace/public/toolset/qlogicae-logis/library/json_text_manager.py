import json
from typing import Any

from library import json_manager


class JsonTextManager:
    def is_valid(self, value: str) -> bool:
        try:
            json.loads(value)
            return True
            
        except json.JSONDecodeError:
            return False

    def convert_to_object(self, value: str) -> Any:
        return json.loads(value)

    def convert_to_string(self, value: Any) -> str:
        return json.dumps(
            value,
            indent=json_manager.singleton.indent_count,
            ensure_ascii=json_manager.singleton.is_ascii_format_enabled,
        )


singleton = JsonTextManager()
