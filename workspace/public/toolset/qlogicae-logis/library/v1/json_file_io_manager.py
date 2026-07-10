import json
from typing import Any

from library.v1 import json_manager


class JsonFileIoManager:
    def read_file(self, file: Any) -> Any:
        return json.load(file) or {}

    def write_file(self, file: Any, data: Any) -> bool:
        json.dump(
            data,
            file,
            indent=json_manager.singleton.indent_count,
            ensure_ascii=json_manager.singleton.is_ascii_format_enabled,
        )

        return True


singleton = JsonFileIoManager()
