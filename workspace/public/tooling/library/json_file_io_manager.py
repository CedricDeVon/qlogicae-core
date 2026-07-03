import json
from typing import Any


class JsonFileIoManager:
    def is_valid(self, file: Any) -> bool:
        return any(
            suffix in {".json"}
            for suffix in file.suffixes
        )

    def read(self, file: Any) -> int:
        return json.load(file) or {}


singleton = JsonFileIoManager()
